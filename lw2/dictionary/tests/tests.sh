#!/usr/bin/env bash

PROGRAM=$1
OUTPUT="/tmp/output.txt"


### Positive

# Prints data from dictionary file
$PROGRAM data/initial.txt < commands/print.txt > $OUTPUT
if ! cmp expected/prints_cat.txt $OUTPUT; then
  echo "Prints data test failed"
  exit 1
fi

# Adds data and prints it, no save
$PROGRAM data/initial.txt < commands/print_and_add.txt > $OUTPUT
if ! cmp expected/prints_cat_and_add_meat.txt $OUTPUT; then
  echo "Prints and add data test failed"
  exit 1
fi

# Add data, prints it and saves
cp data/initial.txt data/data.txt
$PROGRAM data/initial.txt < commands/print_add_save.txt > $OUTPUT
if ! cmp expected/print_add_save.txt $OUTPUT; then
  echo "Saved data output test failed"
  exit 1
fi
if ! cmp expected/updated_dict.txt data/data.txt; then
  echo "New dictionary save test failed"

fi

### Negative

# Cannot open file that not exists
OUT=$($PROGRAM file/not/exists)
if [ "$OUT" != "Не удалось открыть входной файл" ]; then
  echo "Invalid input file test failed. Got $OUT"
fi

echo "All test finished correctly"
