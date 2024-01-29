#!/bin/bash

RED="\e[31m"
GREEN="\e[32m"
NORM="\e[0m"

STD="-Wall -Wpedantic -Werror -std=c89 -ansi"
CC=clang
if ! command -v clang &> /dev/null; then
  STD="-Wall -Wpedantic -Werror"
  CC=gcc
fi
INC="-I./src -I./external $(sdl2-config --cflags)"
LFLAGS="-lm $(sdl2-config --libs)"
SRC=src
BIN=bin
mkdir -p ${BIN}
OUT=tiler
OUT_TYPE="out"
# Non-posix-compliance, I choose you!!!!!
FILES=($(find ${SRC}/*.c))
FILES_LEN=${#FILES[@]}

if [[ $* == *windows* ]]; then
  echo "Windooz time!!"
  CC="x86_64-w64-mingw32-gcc"
  INC="-I./src -I./external -Iexternal/windows/SDL2-2.28.5/x86_64-w64-mingw32/include"
  OUT_TYPE="exe"
  STD=""
  LFLAGS="-Lexternal/windows/SDL2-2.28.5/x86_64-w64-mingw32/lib -lm -lmingw32 -lSDL2main -lSDL2 -mwindows"
  cp external/windows/SDL2-2.28.5/x86_64-w64-mingw32/bin/SDL2.dll ${BIN}
fi
if [[ $* == *clean* ]]; then
  echo "Cleaning time!!"
  rm -rf ${BIN}
  printf "${GREEN}done.\n"
  exit 0
fi
CFLAGS="-pipe -Ofast -mavx -maes -msse4.1 -march=x86-64 ${STD} -Wno-comment -Wno-visibility ${INC}"

build_file () {
  if ! ${CC} ${CFLAGS} -c $1 -o "${BIN}/${1//\//_}.o"; then
    printf "${RED}failed to compile $1.${NORM}\n"
    exit 1
  fi
  COMPILED=($(find ${BIN}/*.o))
  COMPILED_LEN=${#COMPILED[@]}
  printf "${GREEN}[$(((COMPILED_LEN * 100) / (FILES_LEN)))%c]${NORM} Compiled $1\n" "%"
  exit 0
}

echo "Building..."
i=0
while [ "$i" -lt ${FILES_LEN} ]; do
  build_file "${FILES[i]}" &
  i=$((i+1))
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
printf "${GREEN}done.\n"

