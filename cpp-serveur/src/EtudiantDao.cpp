#include "./../include/EtudiantDao.h"

#include <cppconn/prepared_statement.h>

EtudiantDao::EtudiantDao() {
    dbManager = new DatabaseManager();
}
EtudiantDao::~EtudiantDao() {}

void EtudiantDao::sauvegarderEtudiant(const Ecole::InfoEtudiant& e) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            dbManager->getConnect()->prepareStatement("INSERT INTO etudiants(nom, prenom) VALUES(?,?)")
        );
        pstmt->setString(1,std::string(e.nom));
        pstmt->setString(2,std::string(e.prenom));

        pstmt->executeUpdate();

        pstmt->close();

        dbManager->disconnect();
    } catch (sql::SQLException& e) {
        std::cerr << "[BDD ERROR] Erreur sauvegarde: " << e.what() << std::endl;
    }
}

void EtudiantDao::supprimerEtudiant(CORBA::Long numero) {
    try {  
        std::unique_ptr<sql::PreparedStatement> pstmt (
            dbManager->getConnect()->prepareStatement("DELETE FROM etudiants WHERE num = ?")
        );
        pstmt->setInt(1,numero);

        pstmt->executeUpdate();

        pstmt->close();

        dbManager->disconnect();
    } catch (sql::SQLException& e) {
        std::cerr << "[BDD ERROR] Erreur suppression: " << e.what() << std::endl;
    }
}

Ecole::InfoEtudiant* EtudiantDao::obtenirEtudiant(CORBA::Long numero) {

}

Ecole::ListeEtudiants* EtudiantDao::obtenirTousLesEtudiants() {

}