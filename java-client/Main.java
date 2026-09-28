import org.omg.CORBA.ORB;
import org.omg.CosNaming.NamingContextExt;
import org.omg.CosNaming.NamingContextExtHelper;

import Ecole.Etudiant;
import Ecole.EtudiantHelper;
import Ecole.InfoEtudiant;

public class Main {
    public static void main(String[] args) {
        try {
            // 1. Initialisation standard de l'ORB sans forcer de props rigides
            ORB orb = ORB.init(args, null);

            // 2. Résolution du NameService via une URL corbaloc explicite (omniNames)
            // Format : corbaloc:iiop:HOST:PORT/NameService
            org.omg.CORBA.Object objRef = orb.string_to_object("corbaloc:iiop:127.0.0.1:1209/NameService");
            NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);

            System.out.println("[CLIENT JAVA] Connexion au NameService réussie !");

            // 3. Résolution du service "EtudiantService" enregistré par le serveur C++
            String name = "EtudiantServiceJava";
            Etudiant etudiantService = EtudiantHelper.narrow(ncRef.resolve_str(name));

            if (etudiantService == null) {
                System.err.println("[CLIENT JAVA] Impossible de trouver le service : " + name);
                return;
            }

            System.out.println("[CLIENT JAVA] Service 'EtudiantService' résolu avec succès !");

            // --- TEST 1 : Sauvegarde ---
            InfoEtudiant nouvelEtudiant = new InfoEtudiant();
            nouvelEtudiant.num = 201;
            nouvelEtudiant.nom = "CHIU TIEN";
            nouvelEtudiant.prenom = "MANDRESY";

            System.out.println("\n[CLIENT JAVA] Envoi de l'étudiant...");
            etudiantService.sauvegarderEtudiant(nouvelEtudiant);
            System.out.println("[CLIENT JAVA] Sauvegarde effectuée !");

            // --- TEST 2 : Récupération ---
            System.out.println("\n[CLIENT JAVA] Récupération de la liste...");
            InfoEtudiant[] liste = etudiantService.obtenirTousLesEtudiants();

            System.out.println("[CLIENT JAVA] Reçu " + liste.length + " étudiant(s) :");
            for (InfoEtudiant e : liste) {
                System.out.println("  -> [" + e.num + "] " + e.nom + " " + e.prenom);
            }

        } catch (Exception e) {
            System.err.println("[CLIENT JAVA ERROR] ");
            e.printStackTrace();
        }
    }
}