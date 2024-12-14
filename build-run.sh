#!/bin/bash


CLANG_BIN="/home/rrm/installed-programs/llvm/bin/clang++"
LLVM_CONFIG="/home/rrm/installed-programs/llvm/bin/llvm-config"

# Main file
MAIN_CPP="eva-llvm.cpp"
# Output file
OUT_EXE="exe"

if [ ! -f "$CLANG_BIN" ]; then
    echo "Error: clang++ no encontrado en la ruta especificada: $CLANG_BIN"
    exit 1
fi

if [ ! -f "$LLVM_CONFIG" ]; then
    echo "Error: llvm-config no encontrado en la ruta especificada: $LLVM_CONFIG"
    exit 1
fi

echo "Compiling $MAIN_CPP ..."

$CLANG_BIN -g -O3 "$MAIN_CPP" `$LLVM_CONFIG --cxxflags --ldflags --system-libs --libs core` -o "$OUT_EXE"

echo "$OUT_EXE generated."

# Run
./exe

# Execute generated IR
#lli ./exe
