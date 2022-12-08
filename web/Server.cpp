#include <web/Server.h>
using namespace yazi::web;

#include <fstream>
#include <sstream>
using std::ostringstream;

#include <utility/System.h>
#include <utility/Logger.h>
#include <utility/IniFile.h>
#include <utility/Singleton.h>
#include <utility/Str.h>
using namespace yazi::utility;

#include <thread/TaskDispatcher.h>
using namespace yazi::thread;

#include <socket/SocketHandler.h>
using namespace yazi::socket;

#include <reflect/ClassFactory.h>
using namespace yazi::reflect;

Server::Server()
{
    System * sys = Singleton<System>::instance();
    sys->init();

    // init logger
    Logger::instance()->open(sys->get_root_path() + "/log/server.log");

    m_root_path = sys->get_root_path();

    // init inifile
    IniFile * ini = Singleton<IniFile>::instance();
    ini->load(sys->get_root_path() + "/config/server.ini");

    m_ip = (string)(*ini)["server"]["ip"];
    m_port = (*ini)["server"]["port"];
    m_threads = (*ini)["server"]["threads"];
    m_connects = (*ini)["server"]["max_conn"];
    m_wait_time = (*ini)["server"]["wait_time"];
}

Server::~Server()
{
}

void Server::listen(const string & ip, int port)
{
    m_ip = ip;
    m_port = port;
}

void Server::start()
{
    // init the thread pool and task queue
    TaskDispatcher * dispatcher = Singleton<TaskDispatcher>::instance();
    dispatcher->init(m_threads);

    // init the socket handler
    SocketHandler * socket_handler = Singleton<SocketHandler>::instance();
    socket_handler->listen(m_ip, m_port);
    socket_handler->handle(m_connects, m_wait_time);
}

void Server::set_threads(int threads)
{
    m_threads = threads;
}

void Server::set_connects(int connects)
{
    m_connects = connects;
}

void Server::set_wait_time(int wait_time)
{
    m_wait_time = wait_time;
}

void Server::bind(const string & path, server_handler handler)
{
    m_handlers[path] = handler;
}

string Server::handle(const Request & req)
{
    const string & path = req.path();
    std::map<string, server_handler>::iterator it = m_handlers.find(path);
    if (it != m_handlers.end())
    {
        Response resp;
        it->second(req, resp);
        return resp.data();
    }

    string classname;
    string methodname;
    std::vector<string> arr;
    Str::split(arr, Str::trim(path, " /"), '/');
    if (arr.size() == 0)
    {
        classname = "Index";
        methodname = "index";
    }
    else if (arr.size() == 1)
    {
        classname = Str::capitalize(arr[0]);
        methodname = "index";
    }
    else if (arr.size() == 2)
    {
        classname = Str::capitalize(arr[0]);
        methodname = arr[1];
    }
    ClassFactory * factory = Singleton<ClassFactory>::instance();
    Object * ctrl = factory->create_class(classname);
    if (ctrl == nullptr)
    {
        Response resp;
        return resp.page_not_found();
    }
    try
    {
        Response resp;
        ctrl->call(methodname, req, resp);
        delete ctrl;
        return resp.data();
    }
    catch (std::exception & e)
    {
        Response resp;
        resp.code(404);
        ostringstream os;
        os << "<h1 style=\"text-align: center;\">404 Page Not Found</h1><p style=\"text-align: center;\">" << e.what() << "</p>";
        resp.html(os.str());
        delete ctrl;
        return resp.data();
    }
}
