#!/usr/bin/env bash

PROGRAM=$1

# Преобразует число из одной системы счисления в другое
OUTPUT=("$PROGRAM" 16 10 1F)
if "$OUTPUT" != "31"; then
  echo "Test 1F(16) => 31(10) failed"
  exit 1
fi