#! /bin/bash

# Testing harness for the ABC tool box.

# Add usage, help, checks and so on.
# echo $0 [program] [test]

# Test files:
# *.tst : Test specification.
# *.in  : Test input, auto tests only.
# *.out : Expected output, auto tests only, empty if ommited.
# *.pr  : Prompt file, prompts user, manual tests only.
# *.res : Results file, system generated.

# Exit Codes:
# 0 - Success
# 1 - File Read Error (Missing, Bad Permitions, Incorrect Formating)
# ? - ???

##############################################################################
############################### IMPLEMENTATION ###############################

echo "Not yet implemented"
exit 0

# Set the present working directory.
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
# Stole that line.

# Creating all the file names.
prefix=$1/$2
tstfile=${prefix}.tst
infile =${prefix}.in
outfile=${prefix}.out
prfile =${prefix}.pr
resfile=${prefix}.res

# Is it an "auto" or "manual" test?
test=grep -E -e "Test Type:" -f ${tstfile}
# What is the expected exit code?
code=grep -E -e "Exit Code:" -f ${tstfile}
# Arguments to pass to the call. (Whole call?)
call=grep -E -e "Call Args:" -f ${tstfile}

if [ ${test} = auto ]; then
  # Create a temp file
  # Redirect the output to it
elif [ ${test} = manual ]; then
  # Prompt the user.
  # If postive, run the program.
  # Ask for pass/fail.
  # If fail, ask for feedback.
else
  # Invalid test peramiter.
  echo "Test was not specified 'auto' or 'manual'."
  exit 1
fi
