#pragma once

#include "./../../generated/Ecole.hh"

class Etudiant_i : public virtual POA_Ecole::Etudiant{
    private:
        Ecole::InfoEtudiant e;
    public:
        Etudiant_i();
        virtual ~Etudiant_i();

        void creerEtudiant(const Ecole::InfoEtudiant& e) override;
        void supprimerEtudiant(CORBA::Long num) override;
        Ecole::InfoEtudiant* recupererEtudiant(CORBA::Long num) override;
};