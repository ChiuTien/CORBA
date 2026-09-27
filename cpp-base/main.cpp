#include <iostream>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

int main() {
    try {
        // 1. Initialisation du driver
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        
        // 2. Connexion au serveur MySQL (hôte, utilisateur, mot de passe)
        std::unique_ptr<sql::Connection> con(
            driver->connect("tcp://127.0.0.1:3306", "root", "root")
        );

        // 3. Sélection de la base de données
        con->setSchema("sys"); // ou le nom de votre BDD

        // 4. Exécution d'une requête SQL
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(
            stmt->executeQuery("SELECT VERSION() AS version")
        );

        // 5. Lecture des résultats
        while (res->next()) {
            std::cout << "Version de MySQL : " << res->getString("version") << std::endl;
        }

    } catch (sql::SQLException &e) {
        std::cerr << "[Erreur MySQL] Code : " << e.getErrorCode() 
                  << " | " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
