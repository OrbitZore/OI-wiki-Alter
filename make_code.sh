#!/bin/bash
baseD=$(dirname $0)/docs/sol
codeD=$baseD/code/$1
exampleD=$baseD/examples/$1
fp=${@:2}
if [ -d $codeD ] && [ -d $exampleD ]; then 
code=$codeD/${fp}.cpp
in=$exampleD/${fp}.in
ans=$exampleD/${fp}.ans
touch $code $in $ans
code -r $code $in $ans
else
  echo "No such directory!"
	echo $codeD
fi

