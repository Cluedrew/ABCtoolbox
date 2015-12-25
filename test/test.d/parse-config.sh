#!/bin/bash

# Get information from a configuration file.
# === Unimplemented ===

# Get Setting: Return part of a line from a file.
# Usage: get_setting [FILE...] LINEMARK
# Read each FILE in turn until one contains a line beginning with `LINEMARK:'.
#  If such a line is found echos the rest of that line and returns 0.
#  If no such line is found nothing is echoed and 1 is returned.
#  If multiple lines are found in the same file the function will not echo
#  anything due to the conflict and will return the number of lines found.
# Currantly just assumes the FILE(s) exist. ???
function get_setting ()
{
  # Check for valid use.
  if [ 0 -eq $# ]; then
    echo "FAULT: get_setting requires at least a LINEMARK."
    exit 4
  fi

  local lines=

  while [ $# -gt 1 ]; do
    # Find the number of matches.
    lines=$(grep -Ec "^${!#}:" $1)

    # One match: print result and finish
    if [ "$lines" -eq 1 ]; then
      local tempresult=$(grep -E "^${!#}:" $1)
      echo ${tempresult#${!#}:}
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
# Currantly assumes FILE exists and is readable. ???
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
