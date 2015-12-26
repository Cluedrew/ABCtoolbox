#!/bin/bash

# === Unimpemented ===

# Header for the test harness for the ABC Tool Box.
# Usage:
# test.sh [OPTION...] PROGRAM [TEST]
# test.sh LONG_OPTION
# test.sh --call=MODUAL [ARGS...]



### Directory Management

# This script should always be placed in the test directory: ABCtoolbox/test
# This line gets the full path to that directory.
TEST_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Grab the currant directory, the one the user is in.
USER_DIR=$( pwd )

# Most of the sub-moduals assume that the pwd is the TEST_DIR so make it so.
cd $TEST_DIR



### OPTION Management

### Delagate to modual

### Usage & Help
