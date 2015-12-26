#!/bin/bash

# Run a automatic test.
# === Unimplemented ===
# Usage:
# run-auto.sh PROGRAM TEST
#   Assumes currant directory is the test directory.
#   Runs the TEST for PROGRAM as an automatic test.

# run_test_*
#   The test functions all run tests, they all have the same interface and
# accomplish the same general task. The all run a test using a test program,
# how they differ is how they run this test.
#   By same interface I mean the arguments and exit codes follow the same
# standard, input and output will vary.
# Usage: run_test_* PROGRAM TEST
# Exit Codes:
# 0 - Test successful
# 1 - Test failed but no errors?
# 2 - Test error
# 3 - Set up error (missing files, etc.)
# 4 - Fault occured

# Get the test directory.
TEST_DIR=$( pwd )

# Usage: run_test_auto PROGRAM TEST
# Runs an auto test with in, out & err files.
function run_test_auto ()
{
  # Collect the args
  local args=$(get_setting ${tstfile} "args")
  if [ $? -gt 1 ]; then
    echo "ERROR: Multiple instances of 'args' for the argument list."
    return 3
  fi

  # Create a temp file
  tempfileindex mk out
  tempfileindex mk err

  local ecode=

  # Run the program with redirects.
  if [ -e $errfile ]; then
    # stdout and stderr to different files.
    $1/$1 $args 1> ${templist[out]} 2> ${templist[err]}
    ecode=$?
  else
    # stdout and stderr to the same file.
    $1/$1 $args &> ${templist[out]}
    ecode=$?
  fi

  # Run a comparison between the expected and actual output.
  # I need a solution to allow the output to be compared with an empty !!!
  #   file. Possibly have some blank special file.
  tempfileindex mk diff
  diff ${templist[out]} ${outfile} > ${templist[diff]}

  local pass=$?

  #if [ -e $errfile ]; then
  #  tempfileindex mk derr
  #  diff ${templist[err]} ${errfile} > ${templist[derr]}
  #fi

  # Save test results
  # Check for the results of the comparison.
  # A difference was detected.
  if [ $pass -eq 1 ]; then
    echo "Test failed: diffrence detected in output:" > $resfile
    cat ${templist[diff]} >> $resfile
    echo "Test $2 for $1 failed"

  # No difference between the files was found.
  else
    echo $pass_mark > $resfile
    echo "Test $2 for $1 passed"
  fi

  tempfileindex rm diff
  tempfileindex rm out
  tempfileindex rm err
  if [ -e $errfile ]; then
    tempfileindex rm derr
  fi

  return $pass
}
