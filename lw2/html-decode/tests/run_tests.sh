#!/usr/bin/env bash

PROGRAM=$1
OUTPUT="/tmp/output.txt"

# Decodes HTML
$PROGRAM < input.txt > $OUTPUT
if ! cmp output.txt $OUTPUT; then
  echo "Decode HTML test failed"
  exit 1
fi

echo "All tests finished correctly"
exit 0
