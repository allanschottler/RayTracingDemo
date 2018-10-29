make clean && make
DEPENDENCIES=/local/allanws/v3o2/dependencies/ext
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEPENDENCIES/OSG/lib/Linux64e6:$DEPENDENCIES/freeglut/lib/Linux64e6:$DEPENDENCIES/glew/lib/Linux64e6
./bin/dojo
