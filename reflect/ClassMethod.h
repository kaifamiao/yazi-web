#pragma once

#include <string>
using namespace std;

namespace yazi {
namespace reflect {

class ClassMethod
{
public:
    ClassMethod() : m_name(""), m_method(0) {}
    ClassMethod(const string & name, uintptr_t method) : m_name(name), m_method(method) {}
    ~ClassMethod() {}

    const string & name()
    {
        return m_name;
    }

    uintptr_t method()
    {
        return m_method;
    }

private:
    string m_name;
    uintptr_t m_method;
};

}
}