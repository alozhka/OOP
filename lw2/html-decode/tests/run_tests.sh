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
OUTPUT=$($PROGRAM < /dev/null)
if [ "$OUTPUT" != "" ]; then
  echo "Empty input test failed. Got $OUTPUT"
  exit 1
fi

echo "All tests finished correctly"
exit 0
