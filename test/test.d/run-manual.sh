#!/bin/bash

# Run a manual test
# === Unimplemented ===

# Usage: run_test_manual PROGRAM TEST
# Run an interactive manual test with a pr file.
function run_test_manual ()
{
  # Collect the args
  local args=$(get_setting ${tstfile} "args")
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

