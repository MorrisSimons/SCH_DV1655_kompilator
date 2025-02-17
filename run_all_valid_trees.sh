#!/bin/bash

# Paths
TEST_DIR="test_files/valid"
OUTPUT_DIR="test_files/tree_output"

# Ensure the output directory exists
mkdir -p "$OUTPUT_DIR"

# Compile the compiler
echo "Compiling the compiler..."
make clean
make
if [ $? -ne 0 ]; then
  echo "Error: Compilation failed."
  exit 1
fi
echo "Compiler compiled successfully."

# Loop through all .java files in the test directory
echo "Processing Java files..."
for file in "$TEST_DIR"/*.java; do
  base_name=$(basename "$file" .java)
  echo "Processing $base_name.java..."

  # Run the compiler on the file
  ./compiler "$file"
  if [ $? -ne 0 ]; then
    echo "Error: Compilation failed for $file"
    continue
  fi

  # Run make tree to generate tree.pdf
  make tree
	
	


  # Check if tree.pdf was generated
  if [ -f "pdf/tree.pdf" ]; then
    # Move and rename the generated PDF to the output directory
    mv "pdf/tree.pdf" "$OUTPUT_DIR/tree_${base_name}.pdf"
    echo "Tree PDF saved to $OUTPUT_DIR/tree_${base_name}.pdf"
  else
    echo "Warning: tree.pdf not found for $base_name.java"
  fi
	make symbol_tree
	if [ -f "pdf/symbol_tree.pdf" ]; then
		# Move and rename the generated PDF to the output directory
		mv "pdf/symbol_tree.pdf" "$OUTPUT_DIR/symbol_tree${base_name}.pdf"
		echo "Tree Symbol PDF saved to $OUTPUT_DIR/symbol_tree${base_name}.pdf"
	else
		echo "Warning: symbol_tree.pdf not found for $base_name.java"
	fi
	make cfg_pdf
	if [ -f "pdf/cfg_pdf.pdf" ]; then
		# Move and rename the generated PDF to the output directory
		mv "pdf/cfg_pdf.pdf" "$OUTPUT_DIR/cfg_${base_name}.pdf"
		echo "CFG PDF saved to $OUTPUT_DIR/cfg_${base_name}.pdf"
	else
		echo "Warning: cfg_pdf.pdf not found for $base_name.java"
	fi

  # Clean up generated files
  rm -f tree.dot
	rm -f symbol_tree.dot
	rm -f cfg.dot
done

echo "All files processed. Outputs saved in $OUTPUT_DIR."