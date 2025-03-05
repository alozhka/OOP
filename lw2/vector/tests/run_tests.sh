#!/usr/bin/env bash

PROGRAM=$1

###### Positive

# Process numbers
OUTPUT=$($PROGRAM < input/1.txt)
if [ "$OUTPUT" != "3.000 6.000 9.000" ]; then
  echo "Processing numbers test 1 failed. Got $OUTPUT"
  exit 1
fi
OUTPUT=$($PROGRAM < input/2.txt)
if [ "$OUTPUT" != "-12.250 -7.000 -3.500 3.500" ]; then
  echo "Processing numbers test 2 failed. Got $OUTPUT"
  exit 1
fi


###### Negative

# Invalid number format
OUTPUT=$($PROGRAM < invalid/not-number.txt)
if [ "$OUTPUT" != "ERROR" ]; then
  echo "Invalid number format test failed. Got $OUTPUT"
  exit 1
fi

echo "All tests finished correctly"