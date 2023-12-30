#!/bin/bash
CC=clang
if ! command -v clang &> /dev/null; then
  CC=gcc
fi
CFLAGS="-pipe -Wall -Wpedantic -Werror -Ofast -mavx -maes -msse4.1 -march=x86-64 -std=c89 -ansi"
LFLAGS="-lSDL2"
SRC=src
BIN=bin
OUT=tiler.out
FILES=($(find ${SRC}/*.c))

mkdir -p ${BIN}

echo "Building..."
can_compile=true
for i in "${!FILES[@]}"; do
  FILE="${FILES[i]}"
  if ! ${CC} ${CFLAGS} -c ${FILE} -o "${BIN}/${FILE//\//_}.o"; then
    echo "failed to compile file ${FILE}."
    can_compile=false
    break
  fi
done

if ${can_compile}; then
  echo "linking..."
  if $(${CC} ${BIN}/*.o ${LFLAGS} -o ${BIN}/${OUT}); then
    echo "stripping..."
    strip ${BIN}/${OUT}
  fi
fi

echo "cleaning..."
rm ${BIN}/*.o
echo "done. Have fun!"

