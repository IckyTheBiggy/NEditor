
if [ "$1" == "--rebuild" ]; then
    echo "Rebuilding"
    rm -rf Build
fi

mkdir Build
cd Build
cmake ..
make
./SmoothEditor