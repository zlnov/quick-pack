#!/usr/bin/env bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_DIR=$( dirname $( dirname $( dirname $( dirname $SCRIPT_DIR )) ))
CPP_INCLUDE_DIR=$PROJECT_DIR/cpp/build/include
SHARED_LIB_DIR=$PROJECT_DIR/cpp/build
FB_INCLUDE_DIR=$PROJECT_DIR/flatbuffers/include
FB_GENERATED_INCLUDE_DIR=$PROJECT_DIR/cpp/build/include/flatbuffers
cd $SCRIPT_DIR

g++ main.cpp -I$CPP_INCLUDE_DIR -I$FB_INCLUDE_DIR -I$FB_GENERATED_INCLUDE_DIR -L$SHARED_LIB_DIR -lquick_pack -o test_run.out
if [ $? -ne 0 ]
then
  echo "g++ build failed"
  exit 1
fi

./test_run.out
