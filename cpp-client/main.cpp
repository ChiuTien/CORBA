#include <iostream>
#include <omniORB4/CORBA.h>
#include <omniORB4/Naming.hh> 
#include "./../generated/Ecole.hh"

void testClient(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    try {
        CORBA::ORB_var orb = CORBA::ORB_init(argc,argv);

        CORBA::Object_var objName = orb->resolve_initial_references("NameService");
        CosNaming::NamingContext_var nameContexte = CosNaming::NamingContext::_narrow(objName);

        if(CORBA::is_nil(nameContexte)) {
            std::cout << "[CLIENT] Impossible de trouver le name contexte" << std::endl;
            return 1;
        }

        CosNaming::Name nameEtudiant;
        nameEtudiant.length(1);
        nameEtudiant[0].id = CORBA::string_dup("EtudiantServiceJava");
        nameEtudiant[0].kind = CORBA::string_dup("");

        CORBA::Object_var objEtudiant = nameContexte->resolve(nameEtudiant);
        Ecole::Etudiant_var etudiant = Ecole::Etudiant::_narrow(objEtudiant);

        Ecole::InfoEtudiant info;
        info.num = 50;
        info.nom = CORBA::string_dup("NY AVO");
        info.prenom = CORBA::string_dup("PD");

        etudiant->sauvegarderEtudiant(info);

    } catch (CORBA::Exception& ex) {
        std::cerr << "[CLIENT] " << ex._rep_id() << std::endl;
    }
}

void testClient(int argc, char* argv[]) {
    try {
        // 1. Initialisation de l'ORB
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

        // 2. Récupération du NameService
        CORBA::Object_var nameServiceObj = orb->resolve_initial_references("NameService");
        CosNaming::NamingContext_var nameContext = CosNaming::NamingContext::_narrow(nameServiceObj);

        if (CORBA::is_nil(nameContext)) {
            std::cerr << "Erreur : Impossible de contacter le NameService !" << std::endl;
            return;
        }

        // 3. Recherche du service par son nom
        CosNaming::Name name;
        name.length(1);
        name[0].id   = CORBA::string_dup("EtudiantService");
        name[0].kind = CORBA::string_dup("");

        std::cout << "[CLIENT] Recherche du service 'EtudiantService'..." << std::endl;
        CORBA::Object_var obj = nameContext->resolve(name);

        // 4. Transtypage (Narrowing) vers l'interface spécifique Ecole::Etudiant
        Ecole::Etudiant_var etudiant = Ecole::Etudiant::_narrow(obj);

        if (CORBA::is_nil(etudiant)) {
            std::cerr << "Erreur : La référence récupérée est nulle !" << std::endl;
            return;
        }

        std::cout << "[CLIENT] Connexion établie via NameService !" << std::endl << std::endl;

        // --- APPELS DES MÉTHODES IDL ---
        
        // Exemple : Sauvegarder un étudiant
        Ecole::InfoEtudiant e;
        e.nom = CORBA::string_dup("CHIU CHRISTIAN");
        e.prenom = CORBA::string_dup("HATSARANA AURELIE");
        
        etudiant->sauvegarderEtudiant(e);
        std::cout << "[CLIENT] Appel 'sauvegarderEtudiant' exécuté." << std::endl;

        // Exemple : Récupérer tous les étudiants
        Ecole::ListeEtudiants_var liste = etudiant->obtenirTousLesEtudiants();
        std::cout << "[CLIENT] Nombre d'étudiants en BDD : " << liste->length() << std::endl;

        orb->destroy();

    } catch (const CosNaming::NamingContext::NotFound& ex) {
        std::cerr << "[ERROR] Service non trouvé dans l'annuaire." << std::endl;
    } catch (const CORBA::Exception& ex) {
        std::cerr << "[CORBA ERROR] Exception Client : " << ex._name() << std::endl;
    }
}