#pragma once

#include <web/Controller.h>
using namespace yazi::web;

namespace yazi {
namespace app {

class User : public Controller
{
public:
    void profile(const Request & req, Response & resp);
};

}
}