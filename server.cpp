#include <iostream>
using namespace std;

#include <web/Server.h>
using namespace yazi::web;

#include <app/controllers.h>

void hello(const Request & req, Response & resp)
{
    string name = req.get("name");
    string age = req.get("age");
    string host = req.user_host();
    resp.html("hello, " + name + "," + age + "," + host);
}

void reply(const Request & req, Response & resp)
{
    string name = req.post("name");
    int age = req.post("age");
    
    Json json;
    json["name"] = name;
    json["age"] = age;
    resp.json(json.str());
}

int main()
{
    Server * server = Singleton<Server>::instance();
    server->listen("", 8080);
    server->bind("/hello", hello);
    server->bind("/reply", reply);
    server->start();
    return 0;
}
