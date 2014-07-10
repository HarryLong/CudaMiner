#!/bin/bash

for i in {500..1000000..1000}; do
  ./inputFileWriter 500 500 ${i} "/home/harry/Documents/cudaminer_inputfiles/"
  # echo "./inputFileWriter ${i} ${i} 5000 /home/harry/Documents/cudaminer_inputfiles/ --optimal-path=off"

done
