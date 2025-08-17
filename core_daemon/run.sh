#!/bin/bash

set -e

cmake -S . -B build
cmake --build build

sudo ./build/pibot 9000

