#!/usr/bin/env bash

# for each test schema
# generate library for languages
# run tests within the languages
# (optional: run tests across languages)
TESTS=( send_recv_test )

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_DIR=$( dirname $SCRIPT_DIR)

SCHEMA_DIR=$PROJECT_DIR/bin/test_schema

# first run setup script
$PROJECT_DIR/scripts/setup.sh


FAIL_COUNT=0
FAILED_TESTS=""

for schema in $SCHEMA_DIR/*.fbs; do
  schema_base=$(basename -- "$schema")
  echo "======"
  echo "Running tests for $schema_base"
  for test_name in "${TESTS[@]}"
  do
    echo "======"
    echo "Testing $test_name with schema $schema_base"
    test_output=$($PROJECT_DIR/tests/$test_name/run.sh)
    ret=$?
    echo -e "$test_output"
    if [[ "$ret" -ne 0 ]]
    then
      echo "$test_name failed with $ret failures"
      FAIL_COUNT=$((FAIL_COUNT+ret))
      FAILED_TESTS="${FAILED_TESTS}\n-----\nFrom ${test_name}:\n${test_output}"
    else
      echo "$test_name passed"
    fi
  done
done


echo "======"
if [[ "$FAIL_COUNT" -gt 0 ]]
then
  echo "$FAIL_COUNT tests have failed."
  echo -e "Failed example: $FAILED_TESTS"
else
  echo "All tests passed."
fi
