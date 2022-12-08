#pragma once

#include <reflect/ClassFactory.h>

namespace yazi {
namespace reflect {

class ClassRegister
{
public:
    ClassRegister(const string & className, create_object method)
    {
        // register class
        Singleton<ClassFactory>::instance()->register_class(className, method);
    }

    ClassRegister(const string & className, const string & fieldName, const string & fieldType, uintptr_t offset)
    {
        // register class field
        Singleton<ClassFactory>::instance()->register_class_field(className, fieldName, fieldType, offset);
    }

    ClassRegister(const string & className, const string & methodName, uintptr_t method)
    {
        // register class method
        Singleton<ClassFactory>::instance()->register_class_method(className, methodName, method);
    }
};

#define REGISTER_CLASS(className)                                       \
    Object * createObject##className()                                  \
    {                                                                   \
        Object * obj = new className();                                 \
        obj->set_class_name(#className);                                \
        return obj;                                                     \
    }                                                                  	\
    ClassRegister classRegister##className(#className, createObject##className)

#define REGISTER_CLASS_FIELD(className, fieldName, fieldType) \
    className className##fieldName; \
    ClassRegister classRegister##className##fieldName(#className, #fieldName, #fieldType, (size_t)(&(className##fieldName.fieldName)) - (size_t)(&className##fieldName))

#define REGISTER_CLASS_METHOD(className, methodName, returnType, ...) \
    std::function<returnType(className *, ##__VA_ARGS__)> className##methodName##method = &className::methodName; \
    ClassRegister classRegister##className##methodName(#className, #methodName, (uintptr_t)&(className##methodName##method))

}
}