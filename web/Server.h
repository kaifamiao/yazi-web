#pragma once

#include <string>
#include <functional>
using namespace std;

#include <utility/Singleton.h>
using namespace yazi::utility;

#include <web/Request.h>
#include <web/Response.h>

namespace yazi {
namespace web {

typedef std::function<void(const Request &, Response &)> server_handler;

class Server
{
    friend class Singleton<Server>;
public:
    void listen(const string & ip, int port);
    void start();

    void set_threads(int threads);
    void set_connects(int connects);
    void set_wait_time(int wait_time);

    void bind(const string & path, server_handler handler);
    string handle(const Request & req);

private:
    Server();
    ~Server();
    string page_not_found() const;

private:
    string m_ip;
    int m_port;
    int m_threads;
    int m_connects;
    int m_wait_time;
    string m_root_path;
    std::map<string, server_handler> m_handlers;
};

}}
