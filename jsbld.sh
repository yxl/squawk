#!/bin/bash

./d.sh jvmenv
./d.sh copyphoneme
./d.sh
./d.sh -prod -mac -o2 rom cldc
cp squawk squawk.bc && emcc squawk.bc -O3 -s TOTAL_MEMORY=167772160 --preload-file squawk.suite --pre-js pre.js -o index.html
firefox index.html
