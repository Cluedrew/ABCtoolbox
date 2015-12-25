#!/bin/bash

# === Unimpemented ===
# === Will replace currant test.sh when read. ===

# Header for the test harness for the ABC Tool Box.

# This script should always be placed in the test directory ?/ABCtoolbox/test
# This line gets the full path to that directory.
TEST_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
# Most of the sub-moduals assume that the pwd is the TEST_DIR so make it so.
cd $TEST_DIR
