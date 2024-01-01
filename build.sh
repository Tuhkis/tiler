#!/bin/bash

RED="\e[31m"
GREEN="\e[32m"
NORM="\e[0m"

CC=clang
if ! command -v clang &> /dev/null; then
  CC=gcc
fi
INC="-I./src -I./external $(sdl2-config --cflags)"
LFLAGS="-lm $(sdl2-config --libs)"
SRC=src
BIN=bin
OUT=tiler
OUT_TYPE="out"
FILES=($(find ${SRC}/*.c))
FILES_LEN=${#FILES[@]}
STD="-Wall -Wpedantic -Werror -std=c89 -ansi"

if [[ $* == *windows* ]]; then
  CC="x86_64-w64-mingw32-gcc"
  INC="-I./src -I./external -Iexternal/windows/SDL2-2.28.5/x86_64-w64-mingw32/include"
  OUT_TYPE="exe"
  STD=""
  LFLAGS="-Lexternal/windows/SDL2-2.28.5/x86_64-w64-mingw32/lib -lm -lmingw32 -lSDL2main -lSDL2 -mwindows"
  cp external/windows/SDL2-2.28.5/x86_64-w64-mingw32/bin/SDL2.dll ${BIN}
fi

CFLAGS="-pipe -Ofast -mavx -maes -msse4.1 -march=x86-64 ${STD} -Wno-comment -Wno-visibility ${INC}"


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
  if $(${CC} ${BIN}/*.o ${LFLAGS} -o ${BIN}/${OUT}.${OUT_TYPE}); then
    echo "stripping..."
    strip ${BIN}/${OUT}.${OUT_TYPE}
  fi
fi

echo "cleaning..."
rm -rf ${BIN}/*.o
echo -e "${GREEN}done."

