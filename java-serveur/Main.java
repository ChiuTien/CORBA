import org.omg.CORBA.ORB;
import org.omg.CosNaming.NamingContextExt;
import org.omg.CosNaming.NamingContextExtHelper;
import org.omg.PortableServer.POA;
import org.omg.PortableServer.POAHelper;

public class Main {
    public static void main(String[] args) {
        try {
            // 1. Initialisation de l'ORB Java
            ORB orb = ORB.init(args, null);

            // 2. Récupération et activation du RootPOA
            POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
            rootpoa.the_POAManager().activate();

            // 3. Instanciation de l'implémentation du service CSV
            EtudiantServiceImpl etudiantServant = new EtudiantServiceImpl();
            org.omg.CORBA.Object ref = rootpoa.servant_to_reference(etudiantServant);

            // 4. Connexion à omniNames via l'URL corbaloc
            org.omg.CORBA.Object objRef = orb.string_to_object("corbaloc:iiop:127.0.0.1:1209/NameService");
            NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);

            // 5. Enregistrement de l'objet sous le nom "EtudiantService"
            String name = "EtudiantServiceJava";
            ncRef.rebind(ncRef.to_name(name), ref);

            System.out.println("[SERVEUR JAVA] Service 'EtudiantService' enregistré dans omniNames !");
            System.out.println("[SERVEUR JAVA] Serveur prêt et en attente des requêtes clients...");

            // 6. Boucle d'écoute pour maintenir le serveur actif
            orb.run();

            rootpoa.destroy(true, true);
            orb.destroy();

        } catch (Exception e) {
            System.err.println("[SERVEUR JAVA ERROR] Échec du démarrage du serveur :");
            e.printStackTrace();
        }
    }
}
