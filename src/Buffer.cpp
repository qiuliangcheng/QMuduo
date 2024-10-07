#include "Buffer.h"
#include <errno.h>
#include <sys/uio.h>

namespace qlc{
ssize_t Buffer::readFd(int fd, int *saveErrno)
{
    char extrastack[65536]={0};
    struct iovec vec[2];
    const size_t writable=writableBytes();
    vec[0].iov_base=beginWrite();
    vec[0].iov_len=writableBytes();
    vec[1].iov_base = extrastack;
    vec[1].iov_len = sizeof(extrastack);
    const int iovcnt = (writable < sizeof(extrastack)) ? 2 : 1;
    const ssize_t n = ::readv(fd, vec, iovcnt);
    if(n<0){
        *saveErrno=errno;
    }else if(n<=(ssize_t)writable){
        writerIndex_ += n;
    }else{
        writerIndex_ = buffer_.size();//这个写满了 然后另一部分写到了另一边去了
        append(extrastack,n-writable);
    }
    return n;
}
//从buffer的readindex中把可以读的部分写到那里面去
ssize_t Buffer::writeFd(int fd, int *saveErrno)
{
    ssize_t n = ::write(fd, peek(), readableBytes());
    if (n < 0)
    {
        *saveErrno = errno;
    }
    return n;
}
}