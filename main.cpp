#include <iostream>
#include <Server/Server.h>

int main() {
    MysqlListener::Server& Listener = MysqlListener::Server::GetInstance();
    Listener.Init();
    while (Listener.IsAlive()) {
        getchar();
    }
    return 0;
}