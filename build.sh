#!/bin/sh

cmake -B build
make -C build -j4
./build/bin/main
