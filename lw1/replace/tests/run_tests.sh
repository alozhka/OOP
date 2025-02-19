#!/bin/bash

PROGRAM="$1"
TMPDIR="/tmp"

# Печатает help
$PROGRAM -h > "$TMPDIR"/prints-help.txt
if ! cmp -s "prints-help.txt" "$TMPDIR"/prints-help.txt; then
  echo "Prints help test failed"
  exit 1
fi

# Replace в файле
$PROGRAM replace/input.txt "$TMPDIR"/output.txt 123 123123
if ! cmp -s "replace/output.txt" "$TMPDIR"/output.txt; then
  echo "Replace test failed"
  exit 1
fi

# Replace через stdin со множеством строк
$PROGRAM < long_text/input.txt > "$TMPDIR"/output.txt
if ! cmp -s long_text/output.txt "$TMPDIR"/output.txt; then
  echo "Replace multiple lines failed"
  exit 1;
fi

echo "All tests finished correctly"
