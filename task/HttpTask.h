#pragma once

#include <thread/Task.h>
using namespace yazi::thread;

#include <socket/Socket.h>
using namespace yazi::socket;

namespace yazi {
namespace task {

const uint32_t recv_buff_size = 1024;

class HttpTask : public Task
{
public:
    HttpTask(Socket * socket);
    virtual ~HttpTask();

    virtual void run();
    virtual void destroy();
};

}}
