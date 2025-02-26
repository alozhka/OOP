#!/usr/bin/env bash
echo

PROGRAM=$1
OUTPUT_FILE="/tmp/output.txt"

# Выводит help
OUTPUT=$($PROGRAM -h)
if [ "$OUTPUT" != "Usage: invert <input_file>" ]; then
  echo "1. Prints help test failed. Got $OUTPUT"
fi

# Преобразует матрицу через файл
$PROGRAM test1/input.txt > $OUTPUT_FILE
if ! cmp test1/output.txt $OUTPUT_FILE ; then
  echo "2. Converting matrix test failed"
fi
$PROGRAM test2/input.txt > $OUTPUT_FILE
if ! cmp test2/output.txt $OUTPUT_FILE ; then
  echo "3. Converting matrix test failed"
fi

# Преобразует матрицу через stdin
$PROGRAM < test1/input.txt > $OUTPUT_FILE
if ! cmp test1/output.txt $OUTPUT_FILE ; then
  echo "4. Converting matrix test failed"
fi

### Negative

# Нельзя инвертировать матрицу с нулевым детерминантом
OUTPUT=$($PROGRAM test3/input.txt)
if [ "$OUTPUT" != "Not-invertible" ]; then
  echo "3. Converting zero determinant matrix test failed. Got $OUTPUT"
fi

# Матрица должна иметь только числа
OUTPUT=$($PROGRAM test4/input.txt)
if [ "$OUTPUT" != "Invalid matrix" ]; then
  echo "4. Converting zero determinant matrix test failed. Got $OUTPUT"
fi

printf "\nAll tests are executed. See errors above.\n\n"
exit 0