#ifndef __QLC_CAllBACK_H
#define __QLC_CAllBACK_H
#include <functional>
#include <memory>
namespace qlc{
class TcpConnection;
class Timestamp;
class Buffer;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using ConnectionCallback = std::function<void (const TcpConnectionPtr&)>;
using CloseCallback = std::function<void (const TcpConnectionPtr&)>;
using WriteCompleteCallback = std::function<void (const TcpConnectionPtr&)>;
using MessageCallback = std::function<void (const TcpConnectionPtr&,
                                        Buffer*,
                                        Timestamp)>;
using HighWaterMarkCallback = std::function<void (const TcpConnectionPtr&, size_t)>;
//上面这些是创立一个新连接所获得的一些回调函数





}
#endif