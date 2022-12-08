#include <app/Index.h>
using namespace yazi::app;

REGISTER_CLASS(Index);
REGISTER_CLASS_METHOD(Index, show, void, const Request &, Response &);
REGISTER_CLASS_METHOD(Index, index, void, const Request &, Response &);

void Index::index(const Request & req, Response & resp)
{
    resp.html("<h1 style=\"text-align: center;\">yazi-web</h1><p style=\"text-align: center;\">a lightweight c++ web mvc framework</p>");
}

void Index::show(const Request & req, Response & resp)
{
    resp.html("index-show");
}