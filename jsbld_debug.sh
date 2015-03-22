#!/bin/bash

./d.sh jvmenv
./d.sh copyphoneme
./d.sh
./d.sh -mac rom cldc
cp squawk squawk.bc && emcc squawk.bc -O2 -s TOTAL_MEMORY=33554432 --embed-file squawk.suite --pre-js pre.js -o squawk.js
node squawk.js
