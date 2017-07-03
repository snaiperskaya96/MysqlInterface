//
// Created by Jury Verrigni on 30/06/2017.
//

#include <algorithm>
#include <unistd.h>
#include <iostream>
#include <Util/Util.h>
#include <arpa/inet.h>
#include <Util/Ini/INIReader.h>
#include "Server.h"

void MysqlListener::Server::StartServer()
{
    ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ListenSocket < 0) {
        std::string Error = "Error opening the socket (socket() returned status ";
        Error += std::to_string(ListenSocket) + ")";
        ErrorAndExit(Error.c_str());
    }

    bzero((char *) &ServerAddress, sizeof(ServerAddress));
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = INADDR_ANY;
    ServerAddress.sin_port = htons(ListenPort);

    int BindResult = bind(ListenSocket, (struct sockaddr*) &ServerAddress, sizeof(ServerAddress));
    if (BindResult < 0) {
        std::string Error = "Error while binding the socket (bind() returned status ";
        Error += std::to_string(BindResult) + ")";
        ErrorAndExit(Error.c_str());
    }

    listen(ListenSocket, 5);

    socklen_t SocketLength = sizeof(ClientAddress);
    while(int ClientSocket = accept(ListenSocket, (struct sockaddr*) &ClientAddress, &SocketLength)) {
        if (ClientSocket < 0) {
            std::cout << "Error while trying to accept connection from client. Not aborting" << std::endl;
            continue;
        }
        std::cout << "Got connection from " << inet_ntoa(ClientAddress.sin_addr) << ":"
                  << std::to_string(ntohs(ClientAddress.sin_port)) << std::endl;
        Socket* NewSocket = new Socket(ClientSocket);
        ActiveConnections.push_back(NewSocket);
    }
}

bool MysqlListener::Server::Init()
{
    if (bInitialized) return true;
    INIReader Reader("./config.ini");
    if (Reader.ParseError() < 0) {
        ErrorAndExit("Can't load 'config.ini'");
        return false;
    }
    ListenPort = (int) Reader.GetInteger("server", "listening-port", 9999);
    ServerThread = std::thread(&MysqlListener::Server::StartServer, this);
    bInitialized = true;
    return true;
}

bool MysqlListener::Server::IsAlive() {
    return bInitialized;
}

void MysqlListener::Server::CloseConnection(MysqlListener::Socket* ClientSocket)
{
    close(ClientSocket->GetClientSocket());
    ActiveConnections.erase(std::remove(ActiveConnections.begin(), ActiveConnections.end(), ClientSocket), ActiveConnections.end());
}
