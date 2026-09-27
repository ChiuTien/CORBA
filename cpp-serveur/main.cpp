#include <iostream>

#include <omniORB4/CORBA.h>
#include <omniORB4/Naming.hh> 

#include "./include/Etudiant_i.h"

void lancementServeur(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    try {
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

        CORBA::Object_var objPOA = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(objPOA);

        PortableServer::POAManager_var pmn = poa->the_POAManager();
        pmn->activate();

        CORBA::Object_var objNAME = orb->resolve_initial_references("NameService");
        CosNaming::NamingContext_var nameContext = CosNaming::NamingContext::_narrow(objNAME);

        if(CORBA::is_nil(nameContext)) {
            std::cerr << "[SERVEUR] : Impossible d'obtenir le Name Context" << std::endl;
        }

        Etudiant_i* servant = new Etudiant_i();
        Ecole::Etudiant_var ref_etu = servant->_this();

        CosNaming::Name name;
        name.length(1);
        name[0].id = CORBA::string_dup("EtudiantService");
        name[0].kind = CORBA::string_dup("");

        nameContext->rebind(name, ref_etu);

        std::cout << "[SERVEUR] : Lancement du serveur " << std::endl;

        orb->run();

        poa->destroy(true, true);
        orb->destroy();

    } catch (CORBA::Exception& ex) {
        std::cerr << "[SERVEUR] " << ex._rep_id() << std::endl;
        return 1;
    }
}

void lancementServeur(int argc, char* argv[]) {
    try{
        // INITIALISATION ORB
        CORBA::ORB_var orb = CORBA::ORB_init(argc,argv);

        // OBTENTION DE LA REFERENCE AU ROOTPOA
        CORBA::Object_var objPOA = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(objPOA);

        //ACTIVATION DU POA MANAGER
        PortableServer::POAManager_var pman = poa->the_POAManager();
        pman->activate();

        //INSTANCIATION DU SERVANT
        Etudiant_i* servant = new Etudiant_i();

        //ACTIVATION DU SERVANT ET RECUPERATION DE LA REFERENCE D'OBJET CORBA
        Ecole::Etudiant_var etudiant_ref = servant->_this();

        //ENREGISTREMENT DE L'OBJET DANS LE NAMINGSERVICE
        CORBA::Object_var objNaming = orb->resolve_initial_references("NameService");
        CosNaming::NamingContext_var namingContext = CosNaming::NamingContext::_narrow(objNaming);

        if(CORBA::is_nil(namingContext)) {
            std::cout << "[SERVEUR] Impossible d'obtenir le NamingContext. " << std::endl;
            return;
        }

        //CONSTRUCTION DU NOM SOUS LEQUEL L'OBJET SERA ENREGISTRER
        CosNaming::Name name;
        name.length(1);
        name[0].id = CORBA::string_dup("ServiceEtudiant");
        name[0].kind = CORBA::string_dup("");

        //ASSOCIATION DU NOM A LA REFERENCE CORBA
        namingContext->rebind(name, etudiant_ref);

        std::cout << "[SERVEUR] Serveur CORBA initialise et enregistre sous 'ServiceEtudiant'." << std::endl;
        std::cout << "[SERVEUR] En attente des requetes des clients..." << std::endl;

        //LANCEMENT DE L'ECOUTE DU SERVEUR
        orb->run();

        //NETTOYAGE EN CAS D'ARRET
        poa->destroy(true, true);
        orb->destroy();
    } catch(const CORBA::Exception& ex){
        std::cerr << "[EXCEPTION CORBA] " << ex._rep_id() << std::endl;  
        return;  
    }
}