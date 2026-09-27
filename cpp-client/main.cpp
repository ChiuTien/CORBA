#include <iostream>

#include <omniORB4/Naming.hh>

#include "./../generated/Ecole.hh" 

int main(int argc, char* argv[]) {
    try {
        // 1. Initialiser l'ORB Client
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

        // 2. Obtenir la référence au Naming Service
        CORBA::Object_var objNaming = orb->resolve_initial_references("NameService");
        CosNaming::NamingContext_var namingContext = CosNaming::NamingContext::_narrow(objNaming);

        if (CORBA::is_nil(namingContext)) {
            std::cerr << "[CLIENT ERREUR] Impossible d'accéder au Naming Service." << std::endl;
            return 1;
        }

        // 3. Spécifier le nom de l'objet enregistré par le serveur ("ServiceEtudiant")
        CosNaming::Name name;
        name.length(1);
        name[0].id   = CORBA::string_dup("EtudiantService");
        name[0].kind = CORBA::string_dup("");

        std::cout << "[CLIENT] Recherche du service 'EtudiantService' dans l'annuaire..." << std::endl;
        CORBA::Object_var objDistant = namingContext->resolve(name);

        // 4. Instancier le Stub via le _narrow()
        Ecole::Etudiant_var serviceEtudiant = Ecole::Etudiant::_narrow(objDistant);

        if (CORBA::is_nil(serviceEtudiant)) {
            std::cerr << "[CLIENT ERREUR] L'objet distant n'est pas une instance d'Etudiant valide." << std::endl;
            return 1;
        }

        std::cout << "[CLIENT] Connecté au serveur avec succès !" << std::endl << std::endl;

        // -------------------------------------------------------------
        // 5. Utilisation des méthodes distantes
        // -------------------------------------------------------------

        // --- A. Création d'un étudiant ---
        Ecole::InfoEtudiant nouveauEtudiant;
        nouveauEtudiant.num    = 101;
        nouveauEtudiant.nom    = CORBA::string_dup("Rabe");
        nouveauEtudiant.prenom = CORBA::string_dup("Soa");

        std::cout << "[CLIENT] Appel de creerEtudiant (Num: 101, Nom: Rabe, Prénom: Soa)..." << std::endl;
        serviceEtudiant->creerEtudiant(nouveauEtudiant);

        // --- B. Récupération des informations de l'étudiant ---
        std::cout << "[CLIENT] Appel de recupererEtudiant (Num: 101)..." << std::endl;
        Ecole::InfoEtudiant_var etuRecupere = serviceEtudiant->recupererEtudiant(101);

        std::cout << "[CLIENT] Informations reçues du serveur :" << std::endl;
        std::cout << "  - Numéro : " << etuRecupere->num << std::endl;
        std::cout << "  - Nom    : " << etuRecupere->nom << std::endl;
        std::cout << "  - Prénom : " << etuRecupere->prenom << std::endl;

        // --- C. Suppression de l'étudiant ---
        std::cout << "[CLIENT] Appel de supprimerEtudiant (Num: 101)..." << std::endl;
        serviceEtudiant->supprimerEtudiant(101);
        std::cout << "[CLIENT] Étudiant supprimé avec succès." << std::endl;

        // 6. Fermeture propre de l'ORB
        orb->destroy();

    } catch (const CosNaming::NamingContext::NotFound&) {
        std::cerr << "[CLIENT ERREUR] Le service 'ServiceEtudiant' n'a pas été trouvé dans le Naming Service." << std::endl;
        return 1;
    } catch (const CORBA::Exception& ex) {
        std::cerr << "[CLIENT EXCEPTION CORBA] " << ex._rep_id() << std::endl;
        return 1;
    }


    return 0;
}