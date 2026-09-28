#!/bin/bash

# Java 8
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export PATH=$JAVA_HOME/bin:$PATH

echo "=== Nettoyage et compilation du Serveur Java ==="
rm -rf bin
mkdir -p bin

javac -d bin Ecole/*.java EtudiantServiceImpl.java Main.java

if [ $? -eq 0 ]; then
    echo "=== Compilation réussie ! Démarrage du Serveur Java ==="
    java -cp bin Main
else
    echo "[ERREUR] Échec de la compilation."
    exit 1
fi