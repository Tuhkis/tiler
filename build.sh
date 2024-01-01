#!/bin/bash

RED="\e[31m"
GREEN="\e[32m"
NORM="\e[0m"

CC=clang
if ! command -v clang &> /dev/null; then
  CC=gcc
fi
INC="-I./src -I./external"
CFLAGS="-pipe -Wall -Wpedantic -Werror -Ofast -mavx -maes -msse4.1 -march=x86-64 -std=c89 -ansi -Wno-comment -Wno-visibility ${INC}"
LFLAGS="-lSDL2 -lm"
SRC=src
BIN=bin
OUT=tiler.out
FILES=($(find ${SRC}/*.c))
FILES_LEN=${#FILES[@]}

mkdir -p ${BIN}

build_file () {
  if ! ${CC} ${CFLAGS} -c $1 -o "${BIN}/${1//\//_}.o"; then
    echo -e "${RED}failed to compile $1.${NORM}"
    exit 1
  fi
  COMPILED=($(find ${BIN}/*.o))
  COMPILED_LEN=${#COMPILED[@]}
  echo -e "${GREEN}[$(((COMPILED_LEN * 100) / (FILES_LEN)))%]${NORM} Compiled $1"
  exit 0
}

echo "Building..."
for i in "${!FILES[@]}"; do
  build_file "${FILES[i]}" &
done

wait $(jobs -p)
can_compile=$?

if test ${can_compile} -eq 0; then
  echo "linking..."
  if $(${CC} ${BIN}/*.o ${LFLAGS} -o ${BIN}/${OUT}); then
    echo "stripping..."
    strip ${BIN}/${OUT}
  fi
fi

echo "cleaning..."
rm -rf ${BIN}/*.o
echo -e "${GREEN}done."

