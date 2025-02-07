#!/bin/bash
set -e

rm -rf ./build-arm

mkdir ./build-arm
cd ./build-arm

../configure --target-list=arm-linux-user
make -j$(nproc)