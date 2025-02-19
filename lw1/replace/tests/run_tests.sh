#!/bin/bash

PROGRAM="$1"
TMPDIR="/tmp"

##### Positive #####

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

# Не зацикливается с пустой строкой поиска
$PROGRAM < empty_search_string/input.txt > "$TMPDIR"/output.txt
if ! cmp -s empty_search_string/output.txt "$TMPDIR"/output.txt; then
  echo "Replace empty search string failed"
  exit 1;
fi

###### Negative #####

# Не открывается входной файл
if $PROGRAM file/not/exists "$TMPDIR"/not-exists temp temp1 > "$TMPDIR/output.txt" ; then
    echo "Replace from file no args: expected returning 0"
    exit 1
fi
if ! cmp -s error.txt "$TMPDIR"/output.txt ; then
  echo "Replace from file no args: expected ERROR"
  exit 1
fi

# Через stdin нет аргументов
if ! $PROGRAM < less_args/nothing.txt > "$TMPDIR"/output.txt ; then
    echo "Replace from stdin no args: expected returning 0"
    exit 1
fi
if ! cmp -s error.txt "$TMPDIR"/output.txt ; then
  echo "Replace from stdin no args: expected ERROR"
  exit 1
fi

# Через stdin только 1 аргумент
if ! $PROGRAM < less_args/only1.txt > "$TMPDIR"/output.txt ; then
    echo "Replace from stdin 1 arg: expected returning true"
    exit 1
fi
if ! cmp -s error.txt "$TMPDIR"/output.txt ; then
  echo "Replace from stdin 1 args: expected ERROR"
  exit 1
fi

# Через stdin только 2 аргумента
if ! $PROGRAM < less_args/only2.txt > "$TMPDIR"/output.txt ; then
    echo "Replace from stdin 2 args: expected returning true"
    exit 1
fi
if ! cmp -s error.txt "$TMPDIR"/output.txt ; then
  echo "Replace from stdin 2 args: expected ERROR"
  exit 1
fi

echo "All tests finished correctly"
