#pragma once

#include <string>
using namespace std;

#include <socket/Socket.h>

namespace yazi {
namespace socket {

class ServerSocket : public Socket
{
public:
    ServerSocket();
    ServerSocket(const string &ip, int port);
    virtual ~ServerSocket();
};

}}
