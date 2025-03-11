#!/usr/bin/env bash

PROGRAM=$1


# Positive

# Преобразует число из одной системы счисления в другое
OUTPUT=$($PROGRAM 16 10 1F)
if [ "$OUTPUT" != "31" ]; then
  echo "Test 1F(16) => 31(10) failed. Got $OUTPUT"
  exit 1
fi

# Граничное основание
OUTPUT=$($PROGRAM 36 10 ZZ)
if [ "$OUTPUT" != "1295" ]; then
  echo "Test ZZ(36) => 1295(10) failed. Got $OUTPUT"
  exit 1
fi
OUTPUT=$($PROGRAM 2 10 1010)
if [ "$OUTPUT" != "10" ]; then
  echo "Test 1010(2) => 10(10) failed. Got $OUTPUT"
  exit 1
fi

# Граничные значения
OUTPUT=$($PROGRAM 10 10 2147483647)
if [ "$OUTPUT" != "2147483647" ]; then
  echo "Test 2147483647(10) => 2147483647(10) failed. Got $OUTPUT"
fi
OUTPUT=$($PROGRAM 10 10 -2147483648)
if [ "$OUTPUT" != "-2147483648" ]; then
  echo "Test -2147483648(10) => -2147483648(10) failed. Got $OUTPUT"
fi


### Negative

# Число с основанием, больше указанного
OUTPUT=$($PROGRAM 11 16 1B)
if [ "$OUTPUT" != "The number must be with base 11, got B" ]; then
  echo "Test unsupported number from base. Got $OUTPUT"
fi

# Переполнение числа
OUTPUT=$($PROGRAM 10 10 2147483648)
if [ "$OUTPUT" != "Reached overflow" ]; then
  echo "Test positive integer overflow. Expected exit code 1. Got $OUTPUT"
fi
OUTPUT=$($PROGRAM 10 10 -2147483649)
if [ "$OUTPUT" != "Reached overflow" ]; then
  echo "Test negative integer overflow. Expected exit code 1. Got $OUTPUT"
fi


# Неподдерживаемое основание
OUTPUT=$($PROGRAM 37 10 ZZ)
if [ "$OUTPUT" != "The radix should be in the range from 2 to 36" ]; then
  echo "Test unsupported upper limit failed. Got $OUTPUT"
fi
OUTPUT=$($PROGRAM 1 10 1010)
if [ "$OUTPUT" != "The radix should be in the range from 2 to 36" ]; then
  echo "Test unsupported lower limit failed. Got $OUTPUT"
fi

# Не все аргументы предоставлены
OUTPUT=$($PROGRAM)
if [ ! $? ]; then
  echo "Test with no args. Expected exit code 1. Got $?"
fi
OUTPUT=$($PROGRAM 1)
if [ ! $? ]; then
  echo "Test with 1 arg. Expected exit code 1. Got $?"
fi
OUTPUT=$($PROGRAM 1 2)
if [ ! $? ]; then
  echo "Test with 2 args. Expected exit code 1. Got $?"
fi

echo "All tests executed, see errors above"
exit 0