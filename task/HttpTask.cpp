#include <task/HttpTask.h>
using namespace yazi::task;

#include <utility/Logger.h>
#include <utility/Singleton.h>
using namespace yazi::utility;

#include <socket/SocketHandler.h>
using namespace yazi::socket;

#include <web/Server.h>
using namespace yazi::web;


HttpTask::HttpTask(Socket * socket) : Task(socket)
{
}

HttpTask::~HttpTask()
{
}

void HttpTask::run()
{
    SocketHandler * handler = Singleton<SocketHandler>::instance();

    Socket * socket = static_cast<Socket *>(m_data);
    debug("http task run: socket=%x", socket);

    char buf[recv_buff_size] = {0};
    int len = socket->recv(buf, recv_buff_size);
    if (len > 0)
    {
        debug("recv msg len: %d msg data: %s", len, buf);

        Request req;
        req.parse(buf, len);
        req.show();

        Server * server = Singleton<Server>::instance();
        string output = server->handle(req);
        socket->send(output.c_str(), output.size());
        handler->attach(socket);
    }
    else
    {
        debug("http task socket closed by peer");
        handler->remove(socket);
    }
}

void HttpTask::destroy()
{
    debug("task destory");
    delete this;
}
