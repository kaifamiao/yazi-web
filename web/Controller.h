#pragma once

#include <web/Request.h>
#include <web/Response.h>

#include <reflect/ClassRegister.h>
using namespace yazi::reflect;

namespace yazi {
namespace web {

class Controller : public Object
{
public:
    Controller() {}
    virtual ~Controller() {}
};

}
}