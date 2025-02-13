#!/usr/bin/bash

# Печатает help
echo begin PrintsHelp
../cmake-build-debug/replace -h
echo end PrintsHelp

# Стандартная обработка
echo begin ReplaceString
../cmake-build-debug/replace replace/input.txt replace/output.txt 123 123123
echo end ReplaceString
