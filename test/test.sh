#! /bin/bash

# Testing harness for the ABC tool box.

echo "Not yet implemented"
exit 0

# echo $0 [program] [test]

# Creating all the file names.
prefix=$1/$2
tstfile=${prefix}.tst
infile =${prefix}.in
outfile=${prefix}.out
prfile =${prefix}.pr
resfile=${prefix}.res

test=grep -E -e "Test:" -f ${prefix}.tst
code=grep -E -e "Exit Code:" -f ${prefix}.tst
call=grep -E -e "Call:" -f ${prefix}.tst

if [ ${test} = auto ]; then
  # Create a temp directory
  # Redirect the output to it
elif [ ${test} = manual ]; then
  # Prompt the user.
else
  # Invalid test peramiter.
fi
