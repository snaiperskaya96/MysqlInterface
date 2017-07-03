//
// Created by Jury Verrigni on 03/07/2017.
//

#ifndef MYSQLLISTENER_MYSQL_H
#define MYSQLLISTENER_MYSQL_H

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <Util/Ini/INIReader.h>
#include <Util/Util.h>

namespace MysqlListener {
    class Mysql
    {
    private:
        sql::Driver* Driver;
        sql::Connection* Connection;
        std::string UsersTable;

    public:
        static Mysql& GetInstance()
        {
            static Mysql Instance;
            return Instance;
        }

        Mysql(Mysql const&) = delete;             // Copy construct
        Mysql(Mysql&&) = delete;                  // Move construct
        Mysql& operator=(Mysql const&) = delete;  // Copy assign
        Mysql& operator=(Mysql &&) = delete;      // Move assign

        bool Login(std::string Username, std::string Password);

    protected:
        Mysql();


    };
}


#endif //MYSQLLISTENER_MYSQL_H
