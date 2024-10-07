#ifndef __QLC_BUFFER_H
#define __QLC_BUFFER_H
#include <unistd.h>
#include <vector>
#include <string>
#include <algorithm> //std::copy
//这个文件是用来将所读到的 或者所需要写入发送的数据放到一个缓存区里面 因为内核发送数据很慢
//所以我们需要写到buffer  这样才能提高效率
namespace qlc{
//这个buffer的构造是这样的 | prepend    |    read   | write     |
//                        |      readindex   writeindex        |

class Buffer{
public:
    static const size_t kCheapPrepend = 8;//prepend的长度
    static const size_t kInitialSize = 1024;
    explicit Buffer(size_t initialSize = kInitialSize)
        : buffer_(kCheapPrepend + initialSize)//buffer有多少长度
        , readerIndex_(kCheapPrepend)
        , writerIndex_(kCheapPrepend)
    {

    }
    size_t readableBytes() const 
    {
        return writerIndex_ - readerIndex_;
    } 
    size_t writableBytes() const
    {
        return buffer_.size() - writerIndex_;
    }
    size_t prependableBytes() const
    {
        return readerIndex_;//可读数据之前的空间有多少
    }
    // 返回缓冲区中可读数据的起始地址
    const char* peek() const
    {
        return begin() + readerIndex_;
    }
    void retrieve(size_t len)
    {
        if (len < readableBytes())
        {
            readerIndex_ += len; // 应用只读取了刻度缓冲区数据的一部分，就是len，还剩下readerIndex_ += len -> writerIndex_
        }
        else   // len == readableBytes()
        {
            retrieveAll();
        }
    }
    void retrieveAll()
    {
        readerIndex_ = writerIndex_ = kCheapPrepend;//读取完全部的数据了
    }
    // 把onMessage函数上报的Buffer数据，转成string类型的数据返回
    std::string retrieveAllAsString()
    {
        return retrieveAsString(readableBytes()); // 应用可读取数据的长度
    }
    std::string retrieveAsString(size_t len)
    {
        std::string result(peek(), len);
        retrieve(len); // 上面一句把缓冲区中可读的数据，已经读取出来，这里肯定要对缓冲区进行复位操作
        return result;
    }
    void ensureWriteableBytes(size_t len)//看看我想写len长度的buffer长度够不够
    {
        if (writableBytes() < len)
        {
            makeSpace(len); // 扩容函数
        }
    }
    // 把[data, data+len]内存上的数据，添加到writable缓冲区当中
    void append(const char *data, size_t len)
    {
        ensureWriteableBytes(len);
        std::copy(data, data+len, beginWrite());
        writerIndex_ += len;
    }
    char* beginWrite()
    {
        return begin() + writerIndex_;
    }
    const char* beginWrite() const
    {
        return begin() + writerIndex_;
    }
    // 从fd上读取数据
    ssize_t readFd(int fd, int* saveErrno);
    // 通过fd发送数据
    ssize_t writeFd(int fd, int* saveErrno);
private:
    char* begin()
    {
        return &*buffer_.begin();  // vector底层数组首元素的地址，也就是数组的起始地址
    }
    const char* begin() const
    {
        return &*buffer_.begin();
    }
    void makeSpace(size_t len)
    {
        if (writableBytes() + prependableBytes() < len + kCheapPrepend)
        {
            buffer_.resize(writerIndex_ + len);
        }
        else
        {
            size_t readalbe = readableBytes();
            std::copy(begin() + readerIndex_, 
                    begin() + writerIndex_,
                    begin() + kCheapPrepend);
            readerIndex_ = kCheapPrepend;
            writerIndex_ = readerIndex_ + readalbe;
        }
    }
    std::vector<char> buffer_;
    size_t readerIndex_;//开始读的位置
    size_t writerIndex_;//开始写的位置

};
}


#endif