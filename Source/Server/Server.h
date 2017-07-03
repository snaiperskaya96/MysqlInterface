//
// Created by Jury Verrigni on 30/06/2017.
//

#ifndef MYSQLLISTENER_SERVER_H
#define MYSQLLISTENER_SERVER_H


#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include "Socket.h"

namespace MysqlListener {
    class Server
    {
    private:
        std::thread ServerThread;
        bool bInitialized;
        int ListenSocket;
        int ListenPort;
        struct sockaddr_in ServerAddress, ClientAddress;
        std::vector<Socket*> ActiveConnections;

    public:
        static Server& GetInstance()
        {
            static Server Instance;
            return Instance;
        }

        Server(Server const&) = delete;             // Copy construct
        Server(Server&&) = delete;                  // Move construct
        Server& operator=(Server const&) = delete;  // Copy assign
        Server& operator=(Server &&) = delete;      // Move assign

        bool Init();
        bool IsAlive();
        void CloseConnection(Socket* ClientSocket);

        ~Server()
        {
            for (Socket* Sock : ActiveConnections) CloseConnection(Sock);
        }
    protected:
        Server()
        {
            bInitialized = false;
            ActiveConnections = std::vector<Socket*>();
        }

    private:
        void StartServer();
    };
}



#endif //MYSQLLISTENER_SERVER_H
