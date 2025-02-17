#!/bin/bash

# Path to your lexer test program
LEXER_TEST="./lexer_test"

# Directory containing test files
TEST_DIR="test_files"

# Loop through each file in the test directory
for file in "$TEST_DIR"/*; do
  if [ -f "$file" ]; then
    echo "Running lexer test for $file"
    $LEXER_TEST "$file"
    echo "-----------------------------------"
  fi
done
