#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_DIR=$( dirname $SCRIPT_DIR)

cd $PROJECT_DIR
if [ -d flatbuffers ]
then
  echo "$PROJECT_DIR/flatbuffers already exists"
else
  git clone --depth 1 --branch v2.0.5 git@github.com:google/flatbuffers.git
fi

cd flatbuffers
if [ -e $PROJECT_DIR/flatbuffers/flatc ]
then
  echo "$PROJECT_DIR/flatbuffers/flatc already exists"
else
  cmake .
  if [ $? -ne 0 ]
  then
    echo "cmake failed"
    exit 1
  fi
  make
  if [ $? -ne 0 ]
  then
    echo "make failed"
    exit 1
  fi
fi

if [ ! -e $PROJECT_DIR/flatbuffers/flatc ]
then
  echo "setup.sh failed: $PROJECT_DIR/flatbuffers/flatc is missing"
else
  echo "setup.sh passed: found flatc"
fi
