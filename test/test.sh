#! /bin/bash

# Testing harness for the ABC tool box.

# Add usage, help, checks and so on.
# echo $0 (program) (test)

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

# The *.tst file:
# This file must have three particular lines in it, all of which begin with
# a label and then have some option.
# "Test Type:" must be followed with either auto or manual. This controls
# whether or not the script will run an interactive test or not. An auto test
# is not interactive, the program is run, given input from the *.in file and
# the output is compared to the contents of a *.out file. If they actual and
# expected output differ than the test fails. In a manual test the user is
# first prompted with intstruction from the *.pr file, they can skip the test
# if they want here. If they continue the test the program and then when the
# program ends they are asked for their opition. The auto tests are usually
# favoured over the manual tests, but if there is some interaction and display
# that at text file/diff can't analyse then the manual tests are an option.
# "Exit Code:" Followed by a number. If the program does not exit with this
# value than the test fails and this error is added to the other results.
# "Call Args:" Add to the command line argument that calls the program.
# <program>/<program> {Call Args}

# Check List:
# ( ) Auto Test Set Up
#   ( ) Create Temp Files
#   ( ) Call Function with various redirects
#   ( ) Preform Diff
#   ( ) Save Results
# ( ) Manual Test Set Up
#   ( ) Prompt User and allow the test to skip
#   ( ) Call Program
#   ( ) Get & Save Results
# ( ) Argument Checking
# ( ) File Checking
#   ( ) Check for needed files
#   ( ) Check for read permistions
#   ( ) Check for extra files?
# ( ) Safe Exit
#   ( ) Remove Temp files
#   ( ) Report if falure was during testing.
# ( ) Extras:
#   ( ) Help option
#   ( ) Something to help you right the test files
#   ( ) Poll wheither the test is auto or manual

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
# Creating the program's name.
program=$1/$1

# Is it an "auto" or "manual" test?
test=grep -E -e "Test Type:" -f ${tstfile}
# What is the expected exit code?
code=grep -E -e "Exit Code:" -f ${tstfile}
# Arguments to pass to the call. (Whole call?)
call=grep -E -e "Call Args:" -f ${tstfile}

if [ ${test} = auto ]; then
  # Create a temp file
  # Redirect the output to it

  # $(program) $(call) < $(infile) > $(tempout)
  # diff $(tempout) $(outfile) > $(tempdiff)

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
