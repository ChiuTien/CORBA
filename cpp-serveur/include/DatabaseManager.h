#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>

class DatabaseManager {
    private:
        sql::mysql::MySQL_Driver* driver = nullptr;
        sql::Connection* co = nullptr;

    public:
        DatabaseManager();
        ~DatabaseManager();

        sql::Connection* getConnect();

        void disconnect();
};