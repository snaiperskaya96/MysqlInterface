//
// Created by Jury Verrigni on 03/07/2017.
//

#ifndef MYSQLLISTENER_SOCKET_H
#define MYSQLLISTENER_SOCKET_H

#include <thread>
#include <JSONValue.h>

namespace MysqlListener {
    class Socket {
    private:
        int ClientSocket;
        std::thread SocketThread;
    public:
        Socket(int ClientSocketAddress);
        int GetClientSocket() const { return ClientSocket; }
    private:
        void Run();
        void ProcessJson(JSONValue *Data);
        void HandleLogin(JSONObject Data);
        void Write(std::string Response);
    };
}

#endif //MYSQLLISTENER_SOCKET_H
