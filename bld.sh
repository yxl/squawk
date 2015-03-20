#!/bin/bash

./d.sh jvmenv
./d.sh copyphoneme
./d.sh
./d.sh -prod -mac -o2 rom cldc
./squawk com.sun.squawk.Test
