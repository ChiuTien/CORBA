#pragma once

#include "./../../generated/Ecole.hh"

#include "DatabaseManager.h"

class EtudiantDao : virtual public POA_Ecole::Etudiant{
    private:
        DatabaseManager* dbManager;
    public:
        EtudiantDao();
        ~EtudiantDao();

        void sauvegarderEtudiant(const Ecole::InfoEtudiant& e) override;
        void supprimerEtudiant(CORBA::Long numero) override;

        Ecole::InfoEtudiant* obtenirEtudiant(CORBA::Long numero) override;

        Ecole::ListeEtudiants* obtenirTousLesEtudiants() override;
};