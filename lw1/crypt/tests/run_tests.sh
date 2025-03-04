#!/usr/bin/env bash

PROGRAM=$1
OUTPUT="/tmp/output.txt"


### Positive

# Prints help
#OUTPUT_MESSAGE=$($PROGRAM crypt less args)
#HELP_MESSAGE="Usage: crypt crypt <input file> <output file> <key>
#crypt decrypt <input file> <output file> <key>
#"
#if [ "$OUTPUT_MESSAGE" != "$HELP_MESSAGE" ]; then
#  echo "Prints help test failed. Expected $HELP_MESSAGE, got $OUTPUT_MESSAGE"
#  exit 1
#fi


### Negative
INVALID_KEY="Invalid key"
KEY_OUT_OF_RANGE="Key must be in range [0, 255]"
INVALID_OPERATION="Unsupported operation"

# Invalid key
OUTPUT_MESSAGE=$($PROGRAM crypt input.txt output.txt 10a)
if [ "$OUTPUT_MESSAGE" != "$INVALID_KEY" ]; then
  echo "Invalid key test failed. Got $OUTPUT_MESSAGE"
  exit 1
fi

# Key is out of range
OUTPUT_MESSAGE=$($PROGRAM crypt input.txt output.txt 1455)
if [ "$OUTPUT_MESSAGE" != "$KEY_OUT_OF_RANGE" ]; then
  echo "Key out of range test failed. Got $OUTPUT_MESSAGE"
  exit 1
fi

# Key is out of range
OUTPUT_MESSAGE=$($PROGRAM invalid input.txt output.txt 254)
if [ "$OUTPUT_MESSAGE" != "$INVALID_OPERATION" ]; then
  echo "Unsupported operation test failed. Got $OUTPUT_MESSAGE"
  exit 1
fi

echo "All tests finished correctly"