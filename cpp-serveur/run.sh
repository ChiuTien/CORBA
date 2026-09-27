
SOURCE="../idl/Ecole.idl"
DESTINATION="../generated"

omniidl -bcxx -C "$DESTINATION" "$SOURCE"

cd build/

rm -rf *

if cmake ..; then
    if make; then
        clear
        ./exec -ORBInitRef NameService=corbaloc::localhost:1209/NameService
    else 
        echo "Erreur lors du MAKE"
    fi
else 
    echo "Erreur lors du CMAKE"
fi