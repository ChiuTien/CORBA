
SOURCE="../idl/Ecole.idl"
DESTINATION="generated/"

omniidl -bcxx -C "$DESTINATION" "$SOURCE"

cd build/

rm -rf *

if cmake ..; then
    if make; then
        clear
        ./exec -ORBInitRef NameService=corbaloc::localhost:2809/NameService
    else 
        echo "Erreur lors du MAKE"
    fi
else 
    echo "Erreur lors du CMAKE"
fi