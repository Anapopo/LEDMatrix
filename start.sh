#!/usr/bin/env bash
bin="LEDMatrix";

if [ -f "$bin" ]; then
  rm $bin
  echo "Cleanup old files..."
fi
echo "Compiling..."
g++ LEDMatrix.cpp -o $bin -std=c++11 -pthread -lwiringPi -lm
echo "Starting..."
sudo ./$bin
