#!/usr/bin/env bash

PROGRAM=$0

# Преобразует число из одной системы счисления в другое
$PROGRAM 1F 16 10
echo "$OUTPUT"
if "$OUTPUT" != "31"; then
  echo "Test 1F => 10 failed"
  exit 1
fi