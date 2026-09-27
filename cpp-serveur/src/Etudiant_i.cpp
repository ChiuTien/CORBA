#include "./../include/Etudiant_i.h"

#include <iostream>

Etudiant_i::Etudiant_i(){
    e.num = 0;
    e.nom = CORBA::string_dup("");
    e.prenom = CORBA::string_dup("");
}

Etudiant_i::~Etudiant_i(){}

void Etudiant_i::creerEtudiant(const Ecole::InfoEtudiant& etudiant) {
    e.num = etudiant.num;
    e.nom = etudiant.nom;
    e.prenom = etudiant.prenom;

    std::cout << "[SERVANT]: Etudiant sauvegarder" << std::endl;
}

void Etudiant_i::supprimerEtudiant(CORBA::Long num_e) {
    if(num_e == e.num) {
        std::cout << "[SERVANT]: Etudiant supprimer" << std::endl;
    }
}

Ecole::InfoEtudiant* Etudiant_i::recupererEtudiant(CORBA::Long num_e) {
    if(num_e != e.num) {
        std::cout << "[SERVANT]: Etudiant introuvable" << std::endl;
    } else {
        return &e;
    }
}