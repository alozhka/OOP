#!/usr/bin/env bash
echo

PROGRAM=$1
OUTPUT_FILE="/tmp/output.txt"

# Выводит help
OUTPUT=$($PROGRAM -h)
if [ "$OUTPUT" != "Usage: invert <input_file>" ]; then
  echo "Prints help test failed. Got $OUTPUT"
  exit 1
fi

# Преобразует матрицу через файл
$PROGRAM convert1/input.txt > $OUTPUT_FILE
if ! cmp convert1/output.txt $OUTPUT_FILE ; then
  echo "1. Converting matrix from file test failed"
  exit 1
fi
$PROGRAM convert2/input.txt > $OUTPUT_FILE
if ! cmp convert2/output.txt $OUTPUT_FILE ; then
  echo "2. Converting matrix from file test failed"
  exit 1
fi

# Преобразует матрицу через stdin
$PROGRAM < convert2/input.txt > $OUTPUT_FILE
if ! cmp convert2/output.txt $OUTPUT_FILE ; then
  echo "Converting matrix from stdin test failed"
  exit 1
fi

### Negative

# Нельзя инвертировать матрицу с нулевым детерминантом
OUTPUT=$($PROGRAM not_invertible/input.txt)
if [ "$OUTPUT" != "Not-invertible" ]; then
  echo "Converting zero determinant matrix test failed. Got $OUTPUT"
  exit 1
fi

# Матрица должна иметь только числа
OUTPUT=$($PROGRAM invalid_format/input.txt)
if [ "$OUTPUT" != "Invalid matrix" ]; then
  echo "Converting invalid matrix test failed. Got $OUTPUT"
  exit 1
fi

printf "\nAll tests finished correctly.\n\n"
exit 0