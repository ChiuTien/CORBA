SOURCE="idl/Ecole.idl"
DESTINATION1="java-serveur/"
DESTINATION2="java-client"

idlj -fall -td "$DESTINATION1" "$SOURCE"
idlj -fall -td "$DESTINATION2" "$SOURCE"