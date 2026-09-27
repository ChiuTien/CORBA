cd build/
rm -rf *

if cmake ..; then
    if make; then
        clear
        ./client -ORBInitRef NameService=corbaloc::localhost:1209/NameService
    else 
        echo "Erreur lors du make"
    fi
else 
    echo "Erreur lors du cmake"
fi