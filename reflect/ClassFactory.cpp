#include <reflect/ClassFactory.h>
using namespace yazi::reflect;

Object::Object() : m_className("")
{
}

Object::~Object()
{
}

void Object::set_class_name(const string & className)
{
    m_className = className;
}

const string & Object::get_class_name() const
{
    return m_className;
}

int Object::get_field_count()
{
    return Singleton<ClassFactory>::instance()->get_class_field_count(m_className);
}

ClassField * Object::get_field(int pos)
{
    return Singleton<ClassFactory>::instance()->get_class_field(m_className, pos);
}

ClassField * Object::get_field(const string & fieldName)
{
    return Singleton<ClassFactory>::instance()->get_class_field(m_className, fieldName);
}

void Object::set(const string & fieldName, const char * value)
{
    ClassField * field = Singleton<ClassFactory>::instance()->get_class_field(m_className, fieldName);
    size_t offset = field->offset();
    *((string *)((unsigned char *)(this) + offset)) = string(value);
}

void ClassFactory::register_class(const string & className, create_object method)
{
    m_classMap[className] = method;
}

Object * ClassFactory::create_class(const string & className)
{
    auto it = m_classMap.find(className);
    if (it == m_classMap.end())
    {
        return nullptr;
    }
    return it->second();
}

void ClassFactory::register_class_field(const string & className, const string & fieldName, const string & fieldType, size_t offset)
{
    m_classFields[className].push_back(new ClassField(fieldName, fieldType, offset));
}

int ClassFactory::get_class_field_count(const string & className)
{
    return m_classFields[className].size();
}

ClassField * ClassFactory::get_class_field(const string & className, int pos)
{
    int size = m_classFields[className].size();
    if (pos < 0 || pos >= size)
    {
        return nullptr;
    }
    return m_classFields[className][pos];
}

ClassField * ClassFactory::get_class_field(const string & className, const string & fieldName)
{
    auto fields = m_classFields[className];
    for (auto it = fields.begin(); it != fields.end(); it++)
    {
        if ((*it)->name() == fieldName)
        {
            return *it;
        }
    }
    return nullptr;
}

void ClassFactory::register_class_method(const string & className, const string &methodName, uintptr_t method)
{
    m_classMethods[className].push_back(new ClassMethod(methodName, method));
}

int ClassFactory::get_class_method_count(const string & className)
{
    return m_classMethods[className].size();
}

ClassMethod * ClassFactory::get_class_method(const string & className, int pos)
{
    int size = m_classMethods[className].size();
    if (pos < 0 || pos >= size)
    {
        return nullptr;
    }
    return m_classMethods[className][pos];
}

ClassMethod * ClassFactory::get_class_method(const string & className, const string & methodName)
{
    auto methods = m_classMethods[className];
    for (auto it = methods.begin(); it != methods.end(); it++)
    {
        if ((*it)->name() == methodName)
        {
            return *it;
        }
    }
    return nullptr;
}
