#!/bin/sh

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G Ninja -B cmake-build-debug
cmake --build cmake-build-debug
ln -fnPs cmake-build-debug/compile_commands.json compile_commands.json
