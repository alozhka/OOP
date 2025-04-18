#!/usr/bin/env bash

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

# Формат матрицы должен быть 3х3
OUTPUT=$($PROGRAM invalid_format/4x3matrix.txt)
if [ "$OUTPUT" != "Invalid matrix format" ]; then
  echo "1. Converting invalid matrix format test failed. Got $OUTPUT"
  exit 1
fi
OUTPUT=$($PROGRAM invalid_format/2x4matrix.txt)
if [ "$OUTPUT" != "Invalid matrix format" ]; then
  echo "2. Converting invalid matrix format test failed. Got $OUTPUT"
  exit 1
fi

# Матрица должна иметь только числа
OUTPUT=$($PROGRAM invalid_format/not_only_numbers.txt)
if [ "$OUTPUT" != "Invalid matrix" ]; then
  echo "Converting invalid matrix test failed. Got $OUTPUT"
  exit 1
fi
OUTPUT=$($PROGRAM invalid_format/not_only_numbers1.txt)
if [ "$OUTPUT" != "Invalid matrix" ]; then
  echo "Converting invalid matrix test failed. Got $OUTPUT"
  exit 1
fi

# Не открывается входной файл
OUTPUT=$($PROGRAM file/not/exists)
if [ "$OUTPUT" != "Cannot open input file: file/not/exists" ]; then
  echo "Input file not exists test failed. Got $OUTPUT"
  exit 1
fi

echo "All tests finished correctly."
exit 0