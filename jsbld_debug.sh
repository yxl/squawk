#!/bin/bash

./d.sh jvmenv
./d.sh copyphoneme
./d.sh
./d.sh -mac rom cldc
cp squawk squawk.bc && emcc squawk.bc -s TOTAL_MEMORY=167772160 --embed-file squawk.suite --pre-js pre.js -o squawk.js
node squawk.js
