#include "./../include/DatabaseManager.h"

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager() {
    disconnect();
}

sql::Connection* DatabaseManager::getConnect() {
    if(co == nullptr || co->isClosed()) {
        driver = sql::mysql::get_mysql_driver_instance();
        co = driver->connect("127.0.0.1","root","root");
        co->setSchema("Corba_cpp");
    }
    return co;
}

void DatabaseManager::disconnect() {
    if(co != nullptr) {
        if(!co->isClosed()) {
            co->close();
        }
        delete co;
        co = nullptr;
    }
}