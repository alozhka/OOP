#!/usr/bin/env bash

PROGRAM=$1
OUTPUT="/tmp/output.txt"
OUTPUT1="/tmp/output1.txt"


### Positive

# Prints help
OUTPUT_MESSAGE=$($PROGRAM use less args)
if [ "$OUTPUT_MESSAGE" != "Usage: crypt <crypt|decrypt> <input file> <output file> <key>" ]; then
  echo "Prints help test failed. Got $OUTPUT_MESSAGE"
  exit 1
fi

# Crypts and decrypts data
$PROGRAM crypt crypt/input.txt $OUTPUT 98
cmp crypt/input.txt $OUTPUT > /dev/null
if [ ! $? ]; then
 echo "Crypting test failed"
 exit 1
fi
$PROGRAM decrypt $OUTPUT $OUTPUT1 98
if ! cmp crypt/input.txt $OUTPUT1 ; then
  echo "Decrypting test failed"
  exit 1
fi


### Negative

# Разные файлы при разных ключах

# Invalid key
OUTPUT_MESSAGE=$($PROGRAM crypt input.txt output.txt 10a)
if [ "$OUTPUT_MESSAGE" != "Invalid key" ]; then
  echo "Invalid key test failed. Got $OUTPUT_MESSAGE"
  exit 1
fi

# Key is out of range
OUTPUT_MESSAGE=$($PROGRAM crypt input.txt output.txt 1455)
if [ "$OUTPUT_MESSAGE" != "Key must be in range [0, 255]" ]; then
  echo "Key out of range test failed. Got $OUTPUT_MESSAGE"
  exit 1
fi

# Unsupported operation
OUTPUT_MESSAGE=$($PROGRAM invalid input.txt output.txt 254)
if [ "$OUTPUT_MESSAGE" != "Unsupported operation" ]; then
  echo "Unsupported operation test failed. Got $OUTPUT_MESSAGE"
  exit 1
fi

# Cannot open input file
OUTPUT_MESSAGE=$($PROGRAM crypt file/not/exists output.txt 254)
if [ "$OUTPUT_MESSAGE" != "Cannot open input file" ]; then
  echo "Invalid input file test failed. Got $OUTPUT_MESSAGE"
  exit 1
fi

echo "All tests finished correctly"