#pragma once

#include <socket/Socket.h>
using namespace yazi::socket;

#include <thread/Task.h>
using namespace yazi::thread;

#include <task/HttpTask.h>
using namespace yazi::task;

namespace yazi {
namespace task {

class TaskFactory
{
public:
    static Task * create(Socket * socket)
    {
        return new HttpTask(socket);
    }
};

}}