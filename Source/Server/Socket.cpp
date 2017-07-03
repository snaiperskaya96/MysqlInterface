//
// Created by Jury Verrigni on 03/07/2017.
//

#include "Socket.h"
#include "Server.h"
#include <unistd.h>
#include <iostream>
#include <JSONValue.h>
#include <Mysql/Mysql.h>

MysqlListener::Socket::Socket(int ClientSocketAddress)
{
    ClientSocket = ClientSocketAddress;
    SocketThread = std::thread(&Socket::Run, this);
}

void MysqlListener::Socket::Run() {
    char* Buffer = (char*) malloc(1024);
    ssize_t ReceivedDataCount;
    while (true) {
        ReceivedDataCount = read(ClientSocket, Buffer, 1023);
        if (ReceivedDataCount < 0) {
            std::cout << "Received invalid data from " << std::to_string(ClientSocket) << std::endl;
            continue;
        }

        std::string ReceivedData(Buffer, (unsigned long) ReceivedDataCount);
        if (ReceivedData == "\r" || ReceivedData == "\r\n") break;

        JSONValue* Data = JSON::Parse(Buffer);
        if (Data == NULL) {
            std::cout << "Received invalid JSON data from " << std::to_string(ClientSocket) << std::endl;
            continue;
        }

        ProcessJson(Data);
    }
    free(Buffer);
    Server::GetInstance().CloseConnection(this);
}


void MysqlListener::Socket::ProcessJson(JSONValue* Data)
{
    // We always want an object structured like:
    // {action: "", data: {}}
    if (!Data->IsObject()) return;
    JSONObject Root = Data->AsObject();

    if (Root.find(L"action") == Root.end() || !Root[L"action"]->IsString()) return;
    if (Root.find(L"data") == Root.end() || !Root[L"data"]->IsObject()) return;

    std::wstring Action = Root[L"action"]->AsString();

    if (Action == L"login") {
        HandleLogin(Root[L"data"]->AsObject());
    }
}

void MysqlListener::Socket::HandleLogin(JSONObject Data)
{
    JSONObject Response;

    if (Data.find(L"username") == Data.end() || !Data[L"username"]->IsString()) return;
    if (Data.find(L"password") == Data.end() || !Data[L"password"]->IsString()) return;

    bool Success = Mysql::GetInstance().Login(
            WString2String(Data[L"username"]->AsString()),
            WString2String(Data[L"password"]->AsString())
    );

    Response[L"status"] = new JSONValue(Success);

    JSONValue* Value = new JSONValue(Response);
    Write(WString2String(JSON::Stringify(Value)) + '\n');

    delete Value;
}

void MysqlListener::Socket::Write(std::string Response)
{
    write(ClientSocket, Response.c_str(), Response.size());
}
