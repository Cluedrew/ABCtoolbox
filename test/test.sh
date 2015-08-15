#! /bin/bash

# Testing harness for the ABC tool box.

# Add usage, help, checks and so on.
# echo $0 (program) (test)
# Usage:
#   $0 PROGRAM TEST
#   $0 OPTION...
#   $0 LONG_OPTION

# Exit Codes:
# 0 - Success
# 1 - File Read Error (Missing, Bad Permitions, Incorrect Formating)
# 2 - ???
# 3 - Interupted.
# 4 - Fault occured, program aborted.

# Setting up a Test:__________________________________________________________
# First you must create a test program. This must be located in a subdirectory
# of the [test] directory and the program must have the same name as the
# subdirectory.
# This is controlled from a config file, litterally called config, put into
# the subdirectory with the program.

# NOTE: When ever writing any commands in the test files, remember that the
#   test harness will change the working directory to the test subdirectory.

# Then you need to create the test files.

# Test files:
# *.tst : Test specification.
# *.in  : Test input, auto tests only.
# *.out : Expected output, auto tests only, empty if ommited.
# *.err : Expected error output.
# *.pr  : Prompt file, prompts user, manual tests only.
# *.res : Results file, system generated.

# There are three main tags on error messages:
# ERROR: this is an error message, usually from incorrect usage.
# FAULT: The error shouldn't be able to come up, check the code.
# WARN: Non-critical error, a hicup noticable only because it might mean
#       a more critical error occured elsewhere.

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

# Check List__________________________________________________________________
# { } Not yet complete.
# {?} Complete, but untested or buggy.
# {-} Finished and tested.
# Note that I only test for proper use, the system is not very robust.
#   This is especially true for the internals.
#
# ( ) General Set Up
#   ( ) Argument Checking
#   ( ) File Checking
#     ( ) Check for source files
#     ( ) Check for destination file
#     ( ) Check for extra files?
#   ( ) Check configuration file
#   ( ) Read in test paramiters
#     (-) get_setting helper function
#     (-) get_flag helper function
#   ( ) Decend into the program directories to run code.
# ( ) Auto Test Set Up
#   ( ) Create Temp Files
#     (-) tempfileindex helper function
#   ( ) Call Function with various redirects
#   ( ) Preform Diff
#   ( ) Save Results
# ( ) Manual Test Set Up
#   ( ) Prompt User and allow the test to skip
#     (-) ask_question helper function.
#   ( ) Call Program
#   ( ) Get & Save Results
#     ( ) Open the editor
# (?) Safe Exit
#   (-) Remove Temp files
#   (-) Report if failure was during testing.
#   (?) Clean interupt of tests.
# ( ) Extras:
#   ( ) Help option (-h)
#   ( ) Something to help you write the test files
#   ( ) Poll the test type (-p)
#   ( ) Check to see if the test is up to data / passed (-q)
#   ( ) List off all tests (-l)
#   ( ) Get the string that is in passed result files (--pass-mark)
#   ( ) Option to force running a test (-t)
#   ( ) Check (and maybe set) the editor used for results (--editor)
#   ( ) Run some subset of tests (--run-all)

# Table of Implementation_____________________________________________________
# Variables: Set up of the global variables.
#            I'm not actually sure if they have to come first in bash.
# Functions: All function declarations, there are two function sections.
#         1: Contains helpers that preform some particular task.
#         2: Contains outtakes from main for ogriniation (and safe_exit).
# Main Code: The first code that is really run. Mainly for working through
#            options from the command line.

# BUGS________________________________________________________________________
# safe_exit interupt doesn't kick in right away. I think that may be because
# the things that are going on don't accept the signal and so the script waits
# for them to be complete.

##############################################################################
############################### IMPLEMENTATION ###############################

# Variables___________________________________________________________________
# Or global varibles if you would like.

# Get the directory this script is in.
# Should always be one above the test program directories.
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
# Stole that line.

# Where is the caller calling from (in case we have to go back)
CDIR=$(pwd)



# Program and Test name, left blank if not given.
declare prog_n= test_n=

# Temperary file names.
declare -A templist

# !!! These may all have to be updated depending on the usage. !!!
# Creating all the test file names.
prefix=$1/$2
tstfile=${prefix}.tst
infile=${prefix}.in
outfile=${prefix}.out
errfile=${prefix}.err
prfile=${prefix}.pr
resfile=${prefix}.res

# Possible storage for test files.
declare -A flst
# All the types of test files.
testfiletypes="in out err pr res"
for type in ${testfiletypes}; do
  flst[$type]=$prefix.$type
done

# Creating the program's name.
program=$1/$1

# If a .res file contains this followed by a newline, the test passed.
pass_mark=_PASS_

# Editor, when asking for feedback the program will use this editor.
editor=nano

# Functions_1_________________________________________________________________
# Helper Functions are in this section.

# Idea: make it accept multiple indexes so to group together calls.        !!!

# Make a temp file and add it to templist at INDEX.
# tempfileindex COMMAND INDEX
# COMMAND : mk - create a new temp file and store it in INDEX
#           rm - delete a temp file and clear it from INDEX
# Exit Codes:
#  0 - Success, file was created/distoyed for INDEX
#  1 - INDEX already is in the given state, as in it was empty for rm and
#      full for make. It is now in the proper state but for the wrong reason.
#  2 - Operation failed, INDEX is in the incorrect state.
function tempfileindex
{
  # I might through in a section to create a temp directory...
  # Actually a single temp directory might work better than a lot
  # of temp files. But then I need a way for the directory name as well.

  # Bad function call: Wrong number of arguments.
  if [ $# -ne 2 ]; then
    echo "FAULT: invalid call tempfileindex needs two peramiters."
    exit 4

  # Make a new file at INDEX
  elif [ "mk" == $1 ]; then
    if [ -z ${templist[$2]+def} ]; then
      local newtemp=$(mktemp --tmpdir=/tmp abc-$2.XXXXX)
      if [ 0 == $? ]; then
        templist[$2]=${newtemp}
      else
        return 2
      fi
    else
      return 1
    fi

  # remove the file at INDEX
  elif [ "rm" == $1 ]; then
    if [ -z ${templist[$2]+def} ]; then
      return 1
    else
      rm ${templist[$2]} && unset templist[$2] || return 2
    fi

  # Bad function call: COMMAND not recongnized.
  else
    echo "FAULT: invalid tempfileindex COMMAND ${1}"
    exit 4
  fi
}

# File Check: see if a file exists and what permitions we have for it.
# Usage: file_check FILE STATE
# Because this is not a script in its own right, it only covers the cases
#   used in the script.
# STATE: source, file exists and can be read from.
#        dest,   file does not exist or can be written to.
function file_check ()
{
  # source file check
  if [ source == ${2} ]; then
    if [ -r ${1} ]; then
      return 0
    elif [ -e ${1} ]; then
      echo "ERROR: No read permitions for ${1}"
      return 1
    else
      echo "ERROR: File ${1} does not exist"
      return 1
    fi

  # dest file check
  elif [ dest == ${2} ]; then
    if [ -e ${1} -a ! -w ${1} ]; then
      echo "ERROR: Cannot write to ${1}"
      return 1
    else
      return 0
    fi
  fi

  # invalid option
  echo "FAULT in file_check, invalid file state ${2} for ${1}"
  exit 4
}

# Ask Question: Ask a yes or no question and return the result.
# Usage: ask_question PROMPT...
# Asks a question using the text in PROMPT followed by " (y/n): " before
#   asking for the answer. If then answer is not reconized another question
#   is echoed with prompt replaced by text explaining the input.
# Exit Codes:
# 0: Answer is y.
# 1: Answer is n.
# 2: Too many tries.
function ask_question ()
{
  local tries=1
  local ans=ndef

  # Ask the question, get the answer.
  read -p "$* (y/n): " ans
  # Check the answer
  until [ ${tries} -ge 3 -o "${ans}" == "y" -o "${ans}" == "n" ]; do
    # Try to get the answer again.
    read -p "Please enter yes (y) or no (n): " ans
    tries=$(( ${tries} + 1 ))
  done

  # If the answer is positive than return 0.
  if [ "${ans}" == "y" ]; then
    return 0
  # If the answer is negaive then return 1.
  elif [ "${ans}" == "n" ]; then
    return 1
  # Otherwise, it must have been a time out.
  else
    return 2
  fi
}

# Get Setting: Return part of a line from a file.
# Usage: get_setting FILE... LINEMARK
# Read each FILE in turn until one contains a line beginning with LINEMARK.
#  If such a line is found echos the rest of that line and returns 0.
#  If no such line is found nothing is echoed and 1 is returned.
#  If multiple lines are found in the same file the function will not echo
#  anything due to the conflict and will return the number of lines found.
function get_setting ()
{
  # Check for valid use.
  if [ 1 -ge $# ]; then
    echo "FAULT: get_setting requires atleast one argument."
    exit 4
  fi

  local lines=

  while [ $# -gt 1 ]; do
    # Find the number of matches.
    lines=$(grep -Ec "^${!#}" $1)

    # One match: print result and finish
    if [ "$lines" -eq 1 ]; then
      local tempresult=$(grep -E "^${!#}" $1)
      echo ${tempresult#${!#}}
      return 0
    # No matches: Try the next file.
    elif [ "$lines" -eq 0 ]; then
      shift 1
    # Multiple matches: return conflict result
    else
      return $lines
    fi
  done
  # No matches for the setting found.
  return 1
}

# Get Flag: Seach for a partular word in a file.
# Usage: get_flag FILE FLAG
# Check the for FLAG in FILE. Flags must take up an entire word. Returns 0
#  if the flag is found, 1 otherwise. Echos the number of flags found.
function get_flag ()
{
  local flags=$(grep -Ecw "$2" $1)
  echo $flags
  if [ "$flags" -gt 0 ]; then
    return 0
  else
    return 1
  fi
}

# Poll Test Status: Check the results of a test.
# Usage: poll_test_status PROGRAM TEST
# There are a lot of things this function could check. The most basic are
#   wheither or not a test is uptodate and wheither or not it passed or failed
#   the last time it was run. Checking to see if the test exists or not could
#   also be used. Also the type of test.
function poll_test_status ()
{
  # All appearing letters: ... I need to think about this system.
  # Dd? Rr MAx Pf Uo

  # Check to see if the test is defined
  # (Maybe print out error messages for this one?)
  local defined=
  #file_check source $DIR/$1/$2
  if [ -d $DIR/$1 -a -r $DIR/$1/$2 ]; then
    defined=D
  else
    defined=d
  fi

  # Is the test ready to run?
  local ready=
  if [ -e $DIR/$1/$1 ]; then
    ready=R
  else
    ready=r
  fi

  # What is the test type?
  local tsttype=$(get_setting $DIR/$1/$2 "Test Type:")
  if [ auto == "$tsttype" ]; then
    tsttype=A
  elif [ manual == "$tsttype" ]; then
    tsttype=M
  else
    tsttype=x
  fi
  return 0
}



# Functions_2_________________________________________________________________
# For each major options from main.

# Safe Exit if the program is shut down early. This one is important.
# Usage: safe_exit [EXIT_CODE [ERROR_MSG]]
# The script will clean up, exit with EXIT_CODE (0 if ommited) and optionally
#   print ERROR_MSG before it exits.
function safe_exit ()
{
  # Delete all temp files that still exist.
  for tempfile in ${!templist[@]}; do
    tempfileindex rm ${tempfile}
  done

  # Print last error message.
  if [ 2 -eq $# ]; then
    echo $2 1>&2
  fi

  exit $1
}
trap "safe_exit 3 'ERROR: forced quit from testing'" SIGHUP SIGINT SIGTERM



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

# Usage: run_test_auto PROGRAM TEST
# Runs an auto test with in, out & err files.
function run_test_auto ()
{
  # Collect the args
  local args=$(get_setting ${tstfile} "args:")
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

# Usage: run_test_manual PRAGRAM TEST
# Run an interactive manual test with a pr file.
function run_test_manual ()
{
  # Collect the args
  local args=$(get_setting ${tstfile} "args:")
  if [ $? -gt 1 ]; then
    echo "ERROR: Multiple instances of 'args' for the argument list."
  fi

  # Prompt the user.
  $(< $prfile)

  # If postive, run the program.
  if ask_question "Would you like to run this test?"; then
    # Run the test.
    $1/$2

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
# Change to the script's directory so we can cut down on the length of names.
cd $DIR



# Main Body
if [ 0 == $# ]; then
  echo "Usage: ..."

# Getting the pass_mark
elif [[ --pass-mark == "$1" ]]; then
  echo ${pass_mark}

# Getting the editor
elif [[ --editor == "$1" ]]; then
  echo ${editor}

# Run a single test.
elif [ 2 == $# ]; then
  # Analzye the test file.
  # Is it an "auto" or "manual" test?
  test=$(get_setting ${tstfile} "Test Type:")
  # What is the expected exit code?
  code=$(get_setting ${tstfile} "Exit Code:")
  # Arguments to pass to the call. (Whole call?)
  call=$(get_setting ${tstfile} "Call Args:")

  if [ ${test} = auto ]; then
    run_test_auto ${1} ${2}

  elif [ ${test} = manual ]; then
    run_test_manual ${1} ${2}

  else
    # Invalid test peramiter.
    echo "Test was not specified 'auto' or 'manual'."
    safe_exit 1
  fi

# Does not match any usage.
else
  echo "Usage: ..."

fi

# Program completed.
safe_exit 0
