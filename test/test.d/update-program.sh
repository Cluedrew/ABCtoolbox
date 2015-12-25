#!/bin/bash

# Update a testing program if needed. That is if it uses any tools newer
# than itself.
# === Unimplemented ===

# make format return codes?
# 0 - No errors, updated successfully.
# 1 - Requires update (-q --query)
# 2 - Error occured

# Comp Tool Time
# Usage: comp_tool_time FILE TOOL...
# Compare the time stamp of a FILE against the output files for a set of
#   TOOLs. The output files being the public header and library file in the
#   include directory.
# EXIT: 0 - FILE is up to date
#       1 - FILE is outdated
function comp_tool_time ()
{
  # Path to the include directory where the finished tools are.
  local td=$DIR/../include

  local compfile=$1
  shift 1

  for tool; do
    if [ $compfile -ot $td/$tool.hpp -o $compfile -ot $td/lib$tool.a ]; then
      return 1
    fi
  done

  return 0
}

# Update Program
# Usage: update_program PROGRAM
# Make sure a program is newer than the tools it tests, if not try to update
#   it so that it is newer. Requires pt varibles to be set.
# Exit Codes:
# 0 - No update nessary or program successfully updated
# 1 - Program out of date and not updated
function update_program ()
{
  # Get the number of flags/settings for the update methods.
  local uwm=$(get_flag $configfile "update-with-make")
  local ubc=$(grep -Ec "^update:" $configfile)
  echo uwm:$uwm ubc:$ubc

  local needs_update=no
  if comp_tool_time $1/$1 $(get_setting $1/config "tools"); then
    local sourcefile=
    for sourcefile in $(get_setting $1/config "source-files"); do
      if [ $execfile -ot $1/$sourcefile ]; then
        needs_update=yes
      fi
    done
  else
    needs_update=yes
  fi

  if [ 1 -eq $(($uwm+$ubc)) ]; then
    # Update by calling a makefile (soft & hard updates)
    if [ 1 == $uwm ]; then
      if [ "yes" == $needs_update ]; then
        make -B -C $1 && return 0 || return 1
      else
        make -C $1 && return 0 || return 1
      fi

    # Update with a custom command
    else
      if [ yes == $needs_update ]; then
        # Decend into the directory and run the command.
        local command=$(get_setting $1/config "update")
        echo "${command}"
        cd $1 && $command && cd $DIR && return 0 || return 1
      else
        return 0
      fi
    fi

  # If there isn't excactly one update method send out an error.
  elif [ 0 -eq $(($uwm+$ubc)) ]; then
    echo "No update method specified"
  else
    echo "Conflicting update methods"
  fi
  echo "Please have ONE of: the update-with-make flag or the update setting"
  echo "in $1/config to specify the auto update method."
  return 1
}
