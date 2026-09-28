import Ecole.EtudiantPOA;
import Ecole.InfoEtudiant;
import Ecole.EtudiantNonTrouver;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class EtudiantServiceImpl extends EtudiantPOA {

    private final String CSV_FILE = "etudiants.csv";
    private final String DELIMITER = ",";

    public EtudiantServiceImpl() {
        // Crée le fichier CSV avec un en-tête s'il n'existe pas encore
        File file = new File(CSV_FILE);
        if (!file.exists()) {
            try (PrintWriter pw = new PrintWriter(new FileWriter(file))) {
                pw.println("num,nom,prenom");
                System.out.println("[SERVEUR JAVA] Fichier " + CSV_FILE + " créé.");
            } catch (IOException e) {
                System.err.println("[SERVEUR JAVA ERROR] Impossible de créer le fichier CSV : " + e.getMessage());
            }
        }
    }

    @Override
    public synchronized void sauvegarderEtudiant(InfoEtudiant e) {
        List<InfoEtudiant> liste = lireTousDepuisCSV();
        boolean metAUjour = false;

        // Si l'étudiant existe déjà, on met à jour ses données
        for (int i = 0; i < liste.size(); i++) {
            if (liste.get(i).num == e.num) {
                liste.set(i, e);
                metAUjour = true;
                break;
            }
        }

        // Sinon, on l'ajoute à la liste
        if (!metAUjour) {
            liste.add(e);
        }

        ecrireTousDansCSV(liste);
        System.out.println("[SERVEUR JAVA] Étudiant sauvegardé dans le CSV : " + e.nom + " " + e.prenom);
    }

    @Override
    public synchronized void supprimerEtudiant(int numero) throws EtudiantNonTrouver {
        List<InfoEtudiant> liste = lireTousDepuisCSV();
        boolean supprime = liste.removeIf(e -> e.num == numero);

        if (!supprime) {
            throw new EtudiantNonTrouver("Étudiant avec le numéro " + numero + " introuvable pour suppression.");
        }

        ecrireTousDansCSV(liste);
        System.out.println("[SERVEUR JAVA] Étudiant N°" + numero + " supprimé du CSV.");
    }

    @Override
    public synchronized InfoEtudiant obtenirEtudiant(int numere) throws EtudiantNonTrouver {
        List<InfoEtudiant> liste = lireTousDepuisCSV();

        for (InfoEtudiant e : liste) {
            if (e.num == numere) {
                return e;
            }
        }

        throw new EtudiantNonTrouver("Étudiant avec le numéro " + numere + " introuvable.");
    }

    @Override
    public synchronized InfoEtudiant[] obtenirTousLesEtudiants() {
        List<InfoEtudiant> liste = lireTousDepuisCSV();
        return liste.toArray(new InfoEtudiant[0]);
    }

    // --- MÉTHODES UTILITAIRES POUR GÉRER LE FICHIER CSV ---

    private List<InfoEtudiant> lireTousDepuisCSV() {
        List<InfoEtudiant> liste = new ArrayList<>();
        File file = new File(CSV_FILE);

        if (!file.exists()) {
            return liste;
        }

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            boolean isHeader = true;

            while ((line = br.readLine()) != null) {
                if (isHeader) { // Ignorer la première ligne (en-tête)
                    isHeader = false;
                    continue;
                }

                String[] data = line.split(DELIMITER);
                if (data.length >= 3) {
                    InfoEtudiant e = new InfoEtudiant();
                    e.num = Integer.parseInt(data[0].trim());
                    e.nom = data[1].trim();
                    e.prenom = data[2].trim();
                    liste.add(e);
                }
            }
        } catch (IOException | NumberFormatException ex) {
            System.err.println("[SERVEUR JAVA ERROR] Erreur de lecture CSV : " + ex.getMessage());
        }

        return liste;
    }

    private void ecrireTousDansCSV(List<InfoEtudiant> liste) {
        try (PrintWriter pw = new PrintWriter(new FileWriter(CSV_FILE, false))) {
            pw.println("num,nom,prenom"); // En-tête
            for (InfoEtudiant e : liste) {
                pw.println(e.num + DELIMITER + e.nom + DELIMITER + e.prenom);
            }
        } catch (IOException ex) {
            System.err.println("[SERVEUR JAVA ERROR] Erreur d'écriture CSV : " + ex.getMessage());
        }
    }
}