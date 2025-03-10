#!/usr/bin/env bash

PROGRAM=$1
OUTPUT="/tmp/output.txt"

# Positive

# Decodes HTML
$PROGRAM < input.txt > $OUTPUT
if ! cmp output.txt $OUTPUT; then
  echo "Decode HTML test failed"
  exit 1
fi

# Handles empty stdin

echo "All tests finished correctly"
exit 0
