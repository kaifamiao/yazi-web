#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <stdexcept>
using namespace std;

#include <utility/Singleton.h>
using namespace yazi::utility;

#include <reflect/ClassField.h>
#include <reflect/ClassMethod.h>

namespace yazi {
namespace reflect {

class Object
{
public:
    Object();
    virtual ~Object();

    void set_class_name(const string & className);
    const string & get_class_name() const;

    int get_field_count();
    ClassField * get_field(int pos);
    ClassField * get_field(const string & fieldName);

    template <typename T>
    void get(const string & fieldName, T & value);

    template <typename T>
    void set(const string & fieldName, const T & value);
    void set(const string & fieldName, const char * value);
    
    template <typename R = void, typename ...Args>
    R call(const string & methodName, Args&... args);

private:
    string m_className;
};

typedef Object * (*create_object)(void);

class ClassFactory
{
    friend class Singleton<ClassFactory>;
public:
    // reflect class
    void register_class(const string & className, create_object method);
    Object * create_class(const string & className);

    // reflect class field
    void register_class_field(const string & className, const string & fieldName, const string & fieldType, size_t offset);
    int get_class_field_count(const string & className);
    ClassField * get_class_field(const string & className, int pos);
    ClassField * get_class_field(const string & className, const string & fieldName);

    // reflect class method
    void register_class_method(const string & className, const string &methodName, uintptr_t method);
    int get_class_method_count(const string & className);
    ClassMethod * get_class_method(const string & className, int pos);
    ClassMethod * get_class_method(const string & className, const string & methodName);

private:
    ClassFactory() {}
    ~ClassFactory() {}

private:
    std::map<string, create_object> m_classMap;
    std::map<string, std::vector<ClassField *>> m_classFields;
    std::map<string, std::vector<ClassMethod *>> m_classMethods;
};

template <typename T>
void Object::get(const string & fieldName, T & value)
{
    ClassField * field = Singleton<ClassFactory>::instance()->get_class_field(m_className, fieldName);
    if (field == nullptr)
    {
        return;
    }
    size_t offset = field->offset();
    value = *((T *)((unsigned char *)(this) + offset));
}

template <typename T>
void Object::set(const string & fieldName, const T & value)
{
    ClassField * field = Singleton<ClassFactory>::instance()->get_class_field(m_className, fieldName);
    if (field != nullptr)
    {
        return;
    }
    size_t offset = field->offset();
    *((T *)((unsigned char *)(this) + offset)) = value;
}

template <typename R, typename ...Args>
R Object::call(const string & methodName, Args&... args)
{
    ClassFactory * factory = Singleton<ClassFactory>::instance();
    ClassMethod * method = factory->get_class_method(m_className, methodName);
    if (method == nullptr)
    {
        ostringstream os;
        os << "reflect method " << methodName << " not exists";
        throw std::logic_error(os.str());
    }
    auto func = method->method();
    typedef std::function<R(decltype(this), Args&...)> class_method;
    return (*((class_method *)func))(this, args...);
}

}
}