#!/usr/bin/env bash
echo

PROGRAM=$1
OUTPUT_FILE="/tmp/output.txt"

# Выводит help
OUTPUT=$($PROGRAM -h)
if [ "$OUTPUT" != "Usage: invert <input_file>" ]; then
  echo "1. Prints help test failed. Got $OUTPUT"
fi

# Преобразует матрицу
$PROGRAM test1/input.txt > $OUTPUT_FILE
if ! cmp test1/output.txt $OUTPUT_FILE ; then
  echo "1. Converting matrix test failed"
fi

printf "\nAll tests are executed. See errors above.\n\n"
exit 0