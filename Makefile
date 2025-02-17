CXX = g++
CXXFLAGS = -g -w -std=c++14 -I. -I$(OUTPUT_DIR)

OUTPUT_DIR = ./output
PDF_DIR = ./pdf
CLEAN_DIR1 = ./test_files/a3_cfg_output
CLEAN_DIR2 = ./test_files/in_a3_output
CLEAN_DIR3 = ./test_files/tree_output

SOURCES = main.cc symbol_table.cc semantic.cc instruction.cc code_generator.cc cfg.cc tac.cc
HEADERS = $(wildcard *.h) $(wildcard cfg/*.h)

OBJECTS = $(patsubst %.cc,$(OUTPUT_DIR)/%.o,$(SOURCES))

all: $(OUTPUT_DIR) compiler interpreter

$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)

compiler: $(OUTPUT_DIR)/parser.tab.o $(OUTPUT_DIR)/lex.yy.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

interpreter: interpreter.cc
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OUTPUT_DIR)/%.o: %.cc $(HEADERS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTPUT_DIR)/parser.tab.cc $(OUTPUT_DIR)/parser.tab.hh: parser.yy | $(OUTPUT_DIR)
	bison -d -o $(OUTPUT_DIR)/parser.tab.cc parser.yy

$(OUTPUT_DIR)/lex.yy.c: lexer.flex $(OUTPUT_DIR)/parser.tab.hh | $(OUTPUT_DIR)
	flex -o $(OUTPUT_DIR)/lex.yy.c lexer.flex

$(OUTPUT_DIR)/lex.yy.o: $(OUTPUT_DIR)/lex.yy.c $(OUTPUT_DIR)/parser.tab.hh | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c $(OUTPUT_DIR)/lex.yy.c -o $@

$(OUTPUT_DIR)/parser.tab.o: $(OUTPUT_DIR)/parser.tab.cc $(OUTPUT_DIR)/parser.tab.hh | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c $(OUTPUT_DIR)/parser.tab.cc -o $@

$(PDF_DIR):
	@mkdir -p $(PDF_DIR)

move_dot_files:
	@mv -f *.dot $(OUTPUT_DIR)/ 2>/dev/null || true

tree: $(OUTPUT_DIR)/tree.dot $(PDF_DIR)/tree.pdf

$(OUTPUT_DIR)/tree.dot: | move_dot_files

$(PDF_DIR)/tree.pdf: $(OUTPUT_DIR)/tree.dot | $(PDF_DIR)
	dot -Tpdf $(OUTPUT_DIR)/tree.dot -o $@

symbol_tree: $(OUTPUT_DIR)/symbol_tree.dot $(PDF_DIR)/symbol_tree.pdf

$(OUTPUT_DIR)/symbol_tree.dot: | move_dot_files

$(PDF_DIR)/symbol_tree.pdf: $(OUTPUT_DIR)/symbol_tree.dot | $(PDF_DIR)
	dot -Tpdf $(OUTPUT_DIR)/symbol_tree.dot -o $@

cfg_pdf: $(OUTPUT_DIR)/cfg.dot $(PDF_DIR)/cfg_pdf.pdf

$(OUTPUT_DIR)/cfg.dot: | move_dot_files

$(PDF_DIR)/cfg_pdf.pdf: $(OUTPUT_DIR)/cfg.dot | $(PDF_DIR)
	dot -Tpdf $(OUTPUT_DIR)/cfg.dot -o $@

make all_trees: 
	@make tree
	@make symbol_tree
	@make cfg_pdf
clean:
	rm -f compiler interpreter
	rm -rf $(OUTPUT_DIR) $(PDF_DIR)
	rm -f make_clean.log make.log clean.log run_all_cfg.log 
	rm -rf $(CLEAN_DIR1)/*
	rm -rf $(CLEAN_DIR2)/*
	rm -rf $(CLEAN_DIR3)/*
	rm -f output.bc symbol_tree.dot tree.dot cfg.dot
	

.PHONY: all clean tree symbol_tree cfg_pdf move_dot_files
