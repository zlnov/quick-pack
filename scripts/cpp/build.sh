#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_DIR=$( dirname $( dirname $SCRIPT_DIR ))
CPPSRC_DIR=$PROJECT_DIR/cpp/src
SHARED_LIB_DIR=$PROJECT_DIR/cpp/build


# ensure fb build is run
$PROJECT_DIR/scripts/cpp/fb_build.rb
if [ $? -ne 0 ]
then
  echo "fb_build.rb failed"
  exit 1
fi

# test cmake for existance
command -v cmake
if [ $? -ne 0 ]
then
  echo "cmake missing"
  exit 1
fi

# run cmake
cmake $PROJECT_DIR/cpp
if [ $? -ne 0 ]
then
  echo "cmake failed"
  exit 1
fi

# run make clean
cd $PROJECT_DIR/cpp
make clean
if [ $? -ne 0 ]
then
  echo "make clean failed"
  exit 1
fi

# run make
cd $PROJECT_DIR/cpp
make
if [ $? -ne 0 ]
then
  echo "make failed"
  exit 1
fi

CPP_INCLUDE_DIR=$PROJECT_DIR/cpp/build/include
mkdir -p $CPP_INCLUDE_DIR
for i in $(find $CPPSRC_DIR -name \*.hpp); do
    newfile="${i/"$CPPSRC_DIR"/"$CPP_INCLUDE_DIR"}"
    mkdir -p $(dirname $newfile)
    cp $i $newfile
done

sudo ldconfig $SHARED_LIB_DIR
