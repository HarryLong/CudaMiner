#!/bin/bash

for i in {500..20000..500}; do
  ./inputFileWriter ${i} ${i} 5000 "/home/harry/Documents/cudaminer_inputfiles/"
  # echo "./inputFileWriter ${i} ${i} 5000 /home/harry/Documents/cudaminer_inputfiles/ --optimal-path=off"

done
