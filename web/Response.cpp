#include <web/Response.h>
using namespace yazi::web;

#include <fstream>
#include <sstream>
using std::ostringstream;

Response::Response() : m_code(200)
{
}

Response::~Response()
{
}

void Response::code(int code)
{
    m_code = code;
}

void Response::html(const string & data)
{
    m_type = HTML;
    m_data = data;
}

void Response::json(const string & data)
{
    m_type = JSON;
    m_data = data;
}

string Response::data() const
{
    ostringstream os;
    os << "HTTP/1.1 " << m_code << " OK\r\n";
    switch (m_type)
    {
        case HTML:
            os << "Content-Type: text/html; charset: utf-8\r\n";
            break;
        case JSON:
            os << "Content-Type: application/json; charset: utf-8\r\n";
            break;
        default:
            break;
    }
    os << "Content-Length: " << m_data.size() << "\r\n\r\n";
    os << m_data << "\r\n";
    return os.str();
}

string Response::page_not_found() const
{
    string body =  "<!DOCTYPE html> \
                    <html> \
                        <head> \
                            <meta charset=\"utf-8\"> \
                            <title>yazi-web</title> \
                        </head> \
                        <body> \
                            <h1 style=\"text-align: center;\">404 Page Not Found</h1> \
                            <p style=\"text-align: center;\">request not matched</p> \
                        </body> \
                    </html>";
    ostringstream os;
    os << "HTTP/1.1 404 Not Found\r\n";
    os << "Content-Type: text/html; charset: UTF-8\r\n";
    os << "Content-Length: " << body.size() << "\r\n\r\n";
    os << body << "\r\n";
    return os.str();
}