#!/bin/bash

# Handler for temperary files.
# === Unimplemented ===

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

