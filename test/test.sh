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
# 2 - ???
# 3 - Interupted.
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
#   ( ) Help option (-h)
#   ( ) Something to help you write the test files
#   ( ) Poll the test type (-p)
#   ( ) Check to see if the test is up to data / passed (-q)
#   ( ) List off all tests (-l)
#   ( ) Get the string that is in passed result files (-s)
#   ( ) Option to force running a test (-t)

##############################################################################
############################### IMPLEMENTATION ###############################

echo "Not yet implemented"
exit 0

# Varibles____________________________________________________________________
# Or global varibles if you would like.

# Temperary file names.
# Possibly replace with an assositive array (map).
tempout=
temperr=
tempdiff=

# Creating all the test file names.
prefix=$1/$2
tstfile=${prefix}.tst
infile =${prefix}.in
outfile=${prefix}.out
errfile=${prefix}.err
prfile =${prefix}.pr
resfile=${prefix}.res

# Creating the program's name.
program=$1/$1

# If a .res file contains this followed by a newline, the test passed.
pass_mark=_PASS_

# Editor, when asked for feedback the program will use this editor.
editor=nano

# Functions___________________________________________________________________
# Helper Functions are in this section.

# Safe Exit if the program is shut down early.
# $1: exit code
# $2: error message (optional, nothing printed if left out)
function safe_exit ()
{
  # For all non-empty temp file names, delete the file.
  for tempfile in ${tempout} ${temperr} ${tempdiff}; do
    rm ${tempfile}
  done

  # Print last error message.
  if [ 1 < $# ]; then
    echo $2 1>&2
  fi

  exit $1
}
trap "safe_exit 3" SIGHUP SIGINT SIGTERM

# File Check: see if a file exists and what permitions we have for it.
function file_check ()
{
  # File exists
  # Read permition
  # Write permition
  # Execute permition
}

# Ask Question: Ask a yes or no question and return the result.
function ask_question ()
{
  # Although this could be made more generic all the times I'm going to use
  # it for now are exactly the same. Looks for some variants of yes and no,
  # it will try a few times if it doesn't work it will return no. Well 2.

  # Exit Codes:
  # 0: answer is one of (y,yes).
  # 1: answer is one of (n,no,).
  # 2: too many tries.

  local tries=0

  # Ask the question, get the answer.
  echo ${1} " (y/n): "
  read
  # Check the answer
  until ;
  {
    # Try to get the answer again.
    echo "Please enter yes (y) or no (n,): "
    read
  }

  # If the answer is positive than exit 0.
  # If the answer is negaive then exit 1.
  # On a time out exit 2.
}

# Setting Get: Return part of a line from a file.
# This function is to read in options from the .tst file, but it can
# be used in other cases. Echos the result of the read.
function setting_get ()
{
  local rresult=$(grep -E -e -f ${1} ${2})
}

# Functions___________________________________________________________________
# For each major options from main.

# Usage: run_test_auto PROGRAM TEST
# Runs an auto test with in, out & err files.
function run_test_auto ()
{
  # Create a temp file
  tempout=$(mktemp abc-test.XXXXX --tmpdir=/tmp)
  temperr=$(mktemp abc-test.XXXXX --tmpdir=/tmp)

  # Run the program with redirects.
  # $(program) $(call) < $(infile) > $(tempout) 2>

  tempdiff=$(mktemp abc-test.XXXXX --tmpdir=/tmp)
  diff -q -y $(tempout) $(outfile) > $(tempdiff)

  # Save test results

}

# Usage: run_test_manual PRAGRAM TEST
# Run an interactive manual test with a pr file.
function run_test_manual ()
{
  echo "not yet implemented"
  # Prompt the user.
  $(< $prfile)

  # If postive, run the program.
  if ask_question "Would you like to run this test?"; then
    # Run the test.
    ${1}/${2}

    # Ask for pass/fail.

    # If pass, record the success.
    if ask_question "Did the program pass the test?"; then
      echo ${pass_mark} > ${resfile}
    # If fail, ask for feedback.
    else
      # Overwright the old test results.
      echo "Notes on failed test ${2} for ${1} .\n\n" > ${resfile}
      # Get feed back.
      ${editor} ${resfile}
    fi
  fi
}

# Main Code___________________________________________________________________

# Set Up

# Set the present working directory.
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
# Stole that line.

# Analzye the test file.
# Is it an "auto" or "manual" test?
test=$(setting_get ${tstfile} "Test Type:")
# What is the expected exit code?
code=$(setting_get ${tstfile} "Exit Code:")
# Arguments to pass to the call. (Whole call?)
call=$(setting_get ${tstfile} "Call Args:")

# Main Body

if [ ${test} = auto ]; then
  run_test_auto ${1} ${2}

elif [ ${test} = manual ]; then
  run_test_manual ${1} ${2}

else
  # Invalid test peramiter.
  echo "Test was not specified 'auto' or 'manual'."
  exit 1

# Getting the pass_mark
#elif [[  ]]; then
#  echo ${pass_mark}

fi

# Program completed.
