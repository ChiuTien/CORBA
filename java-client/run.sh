#!/bin/bash

# Configuration Java 8
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export PATH=$JAVA_HOME/bin:$PATH

echo "=== Nettoyage et création du dossier de sortie ==="
rm -rf bin
mkdir -p bin

echo "=== Compilation ==="
# On passe explicitement TOUS les fichiers .java de Ecole/ ET Main.java
javac -d bin Ecole/*.java Main.java

if [ $? -eq 0 ]; then
    echo "=== Compilation réussie ! Lancement du client Java ==="
    java -cp bin Main -ORBInitialHost localhost -ORBInitialPort 1209
else
    echo "[ERREUR] Échec de la compilation."
    exit 1
fi