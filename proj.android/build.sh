#!/bin/bash

cd "$(dirname "$0")"

./build_native.sh
if [ $? -ne 0 ]; then echo "error: build native failed";exit 1;fi

ant debug
