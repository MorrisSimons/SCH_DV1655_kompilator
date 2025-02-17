#!/bin/bash

# Paths
TEST_DIR="test_files/assignment3_valid"
OUTPUT_DIR="test_files/in_a3_output"
EXPECTED_DIR="test_files/in_a3_validoutput"  # Directory where expected outputs are stored

# Ensure the output directory exists
if [ ! -d "$OUTPUT_DIR" ]; then
  echo "Error: Output directory $OUTPUT_DIR does not exist."
  exit 1
fi

# Colors for output
GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m" # No Color

# Loop through all .java files in the test directory
echo "Comparing outputs..."
for file in "$TEST_DIR"/*.java; do
  # Extract the base name of the file (e.g., A.java -> A)
  base_name=$(basename "$file" .java)

  # Path to the generated output file
  generated_file="$OUTPUT_DIR/${base_name}_facit.txt"

  # Path to the expected output file
  expected_file="$EXPECTED_DIR/${base_name}_facit.txt"

  # Check if the expected output file exists
  if [ ! -f "$expected_file" ]; then
    echo -e "${RED}[ FAIL ]${NC} : Expected output file for $base_name not found in $EXPECTED_DIR"
    continue
  fi

  # Compare the generated output with the expected output
  diff_output=$(diff -u "$expected_file" "$generated_file")
  if [ $? -eq 0 ]; then
    echo -e "${GREEN}[ PASS ]${NC} : Output matches for $base_name"
  else
    echo -e "${RED}[ FAIL ]${NC} : Output differs for $base_name"
    echo "$diff_output"
  fi
done

echo "Comparison completed."
