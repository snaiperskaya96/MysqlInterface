//
// Created by Jury Verrigni on 03/07/2017.
//

#include "Mysql.h"
#include <cppconn/prepared_statement.h>
#include <Util/Sha256/Sha256.h>

MysqlListener::Mysql::Mysql()
{
    INIReader Reader("./config.ini");
    if (Reader.ParseError() < 0) {
        ErrorAndExit("Can't load 'config.ini'");
        return;
    }

    std::string Host = "tcp://" + Reader.Get("mysql", "host", "127.0.0.1") + ":" + Reader.Get("mysql", "port", "3306");

    Driver = get_driver_instance();
    Connection = Driver->connect(Host, Reader.Get("mysql", "username", "root"), Reader.Get("mysql", "password", "root"));
    Connection->setSchema(Reader.Get("mysql", "schema", "ue4"));
}


bool MysqlListener::Mysql::Login(std::string Username, std::string Password)
{
    bool Valid = false;
    sql::PreparedStatement* PreparedStatement = Connection->prepareStatement("SELECT * FROM users WHERE username = ? LIMIT 1");
    PreparedStatement->setString(1, Username);
    sql::ResultSet* Result = PreparedStatement->executeQuery();

    while(Result->next()) {
        std::string RetrievedPassword = Result->getString("password");
        if (sha256(Password) == RetrievedPassword) {
            Valid = true;
        }
    }

    delete PreparedStatement;
    delete Result;

    return Valid;
}
