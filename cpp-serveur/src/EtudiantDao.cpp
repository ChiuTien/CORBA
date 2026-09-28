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

void EtudiantDao::modifierEtudiant(const Ecole::InfoEtudiant& e, CORBA::Long numero) {
    try {
        std::unique_ptr<sql::PreparedStatement> pmnt(
            dbManager->getConnect()->prepareStatement("UPDATE etudiants SET nom=?, prenom=? WHERE num=?")
        );
        pmnt->setString(1,std::string(e.nom));
        pmnt->setString(2,std::string(e.prenom));
        pmnt->setInt(3,numero);

        pmnt->executeUpdate();

        pmnt->close();
        dbManager->disconnect();
    } catch (sql::SQLException& ex) {
        std::cerr << "[BDD ERROR] Erreur modification: " << ex.what() << std::endl;
    }
}

Ecole::InfoEtudiant* EtudiantDao::obtenirEtudiant(CORBA::Long numero) {
    Ecole::InfoEtudiant* etudiant = new Ecole::InfoEtudiant();
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt (
            dbManager->getConnect()->prepareStatement("SELECT * FROM etudiants WHERE num = ?")
        );
        pstmt->setInt(1,numero);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if(res->next()) {
            etudiant->num = res->getInt("num");
            etudiant->nom = CORBA::string_dup(res->getString("nom").c_str());
            etudiant->prenom = CORBA::string_dup(res->getString("prenom").c_str());
        } else {
            std::cout << "[BDD] Aucun étudiant trouvé avec le numéro: " << numero << std::endl;
            delete etudiant;
            return nullptr;
        }
    } catch(sql::SQLException& e) {
        std::cerr << "[BDD ERROR] Erreur recuperation: " << e.what() << std::endl;
        delete etudiant;
    }
    return etudiant;
}

Ecole::ListeEtudiants* EtudiantDao::obtenirTousLesEtudiants() {
    Ecole::ListeEtudiants_var liste = new Ecole::ListeEtudiants();
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            dbManager->getConnect()->prepareStatement("SELECT * FROM etudiants")
        );
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        int index = 0;
        while(res->next()) {
            liste->length(index+1);
            
            liste[index].num = res->getInt("num");
            liste[index].nom = CORBA::string_dup(res->getString("nom").c_str());
            liste[index].prenom = CORBA::string_dup(res->getString("prenom").c_str());

            index++;
        }
    } catch (sql::SQLException& e) {
        std::cerr << "[BDD ERROR] Erreur recuperation: " << e.what() << std::endl;
    }
    return liste._retn();
}