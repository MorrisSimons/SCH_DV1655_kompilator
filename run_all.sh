#!/bin/bash

# Paths
TEST_DIR="test_files/assignment3_valid"
OUTPUT_DIR="test_files/in_a3_output"

# Ensure the output directory exists
mkdir -p "$OUTPUT_DIR"

# Clean the output directory by removing all existing files
echo "Cleaning the output directory..."
if [ -d "$OUTPUT_DIR" ]; then
    rm -f "$OUTPUT_DIR"/*
    echo "Existing output files removed."
else
    echo "Output directory does not exist. Creating it..."
    mkdir -p "$OUTPUT_DIR"
    echo "Output directory created."
fi


# Compile the compiler
echo "Compiling the compiler..."
make
if [ $? -ne 0 ]; then
  echo "Error: Compilation failed."
  exit 1
fi
echo "Compiler compiled successfully."

# Loop through all .java files in the test directory
echo "Processing Java files..."
for file in "$TEST_DIR"/*.java; do
  # Extract the base name of the file (e.g., A.java -> A)
  base_name=$(basename "$file" .java)

  echo "Processing $base_name.java..."

  # Run the compiler
  ./compiler "$file"
  if [ $? -ne 0 ]; then
    echo "Error: Compilation failed for $file"
    continue
  fi

  # Run the interpreter and save the output
  ./interpreter > "$OUTPUT_DIR/${base_name}_facit.txt"
  if [ $? -ne 0 ]; then
    echo "Error: Execution failed for $file"
    continue
  fi

  echo "Output for $base_name.java saved to $OUTPUT_DIR/${base_name}_facit.txt"
done

echo "All files processed. Outputs saved in $OUTPUT_DIR."
