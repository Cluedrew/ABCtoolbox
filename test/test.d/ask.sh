# ash.sh: Ask a yes or no question and return the result.
# Usage: ask.sh PROMPT...
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

ask_question $*
return $?
