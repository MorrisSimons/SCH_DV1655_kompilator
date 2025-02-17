#include <string>
#include <iterator>
#include "semantic.h"
#include "Node.h"
#include <iostream>
#include "symbol_table.h"


std::string semanticTraversal(Node *root, SymbolTable *symboltable){
	// ----------------- Scope Divers ----------------------
  if(root->type == "MainClass" ||  root->type == "ClassDeclaration" ){
    symboltable->enter_scope(root->value);
    for(auto i=root->children.begin(); i!=root->children.end(); i++) {
      semanticTraversal(*i, symboltable);
    }
    symboltable->exit_scope();
  }
  else if(root->type == "MethodDeclaration"){//
    symboltable->enter_scope(root->value);
    Node* method_body = root->children.back();
    for(auto i = method_body->children.begin(); i != method_body->children.end(); i++){
      semanticTraversal(*i, symboltable);
    }symboltable->exit_scope();
    return "null";
  }

  else if(root->type == "Return"){
    Record* method = symboltable->get_method();
    if(method == NULL) return "Undefined";
    std::string return_type = semanticTraversal(root->children.front(), symboltable);

    if(method->get_type() != return_type){
      std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Method '" << method->get_id() << "' expects '" << method->get_type() << "' return type, got '" << return_type << "'" << std::endl;
    }

    return method->get_type();
  }

  // ------------------ Expressions -----------------------------

  else if(root->type == "MethodCallExpression"){
    std::string first_child_type = semanticTraversal(root->children.front(), symboltable);
    Class* lhs_class = (Class*)symboltable->lookup(first_child_type, std::vector<std::string>{"Class"});

    if(lhs_class == NULL) {return "Undefined";}

    Node* rhs_actual = (*std::next(root->children.begin(), 1));
    Method* dec_method = lhs_class->lookup_method(rhs_actual->value);

    if(dec_method == NULL){
      std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Method is not declared" << std::endl;
      return "Undefined";
    }

    std::vector<Parameter*> target_params = dec_method->get_parameters();
    std::list<Node*> actual_params = root->children.back()->children;

    if(target_params.size() != actual_params.size()){
      std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Method '" << rhs_actual->value << "' expects '" << target_params.size() << "' argument(s), got '" << actual_params.size() << "'" << std::endl;
    }

    auto actual_param_it = actual_params.begin();
    for (size_t i = 0; i < target_params.size(); ++i, ++actual_param_it) {
      if(actual_param_it == actual_params.end()) break;
      std::string actual_param_type = semanticTraversal(*actual_param_it, symboltable);
      if (actual_param_type == "Identifier") {actual_param_type = target_params[i]->get_id();}
      if (actual_param_type != target_params[i]->get_type()) {
        std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Method '" << rhs_actual->value << "' expects '" << target_params[i]->get_type() << "' for argument '" << target_params[i]->get_id() << "', got '" << actual_param_type << "'" << std::endl;
			}
    }

    return dec_method->get_type();
  }

  else if(root->type == "OrExpression" || root->type == "AndExpression" || root->type == "EqExpression"){
		std::string first_child_type = semanticTraversal(root->children.front(), symboltable);
		std::string second_child_type = semanticTraversal(root->children.back(), symboltable);
		if(second_child_type != "Boolean" || first_child_type != "Boolean") {
			std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Operation '" << root->type << "' expects 'Boolean' for arguments '" << root->children.back()->value << "' and '" << root->children.front()->value << "', got '" << second_child_type << "' and '" << first_child_type << "'" << std::endl;
		}
		return "Boolean";
	}

  else if( root->type == "MulExpression" || root->type == "DivExpression" || root->type == "AddExpression" || root->type == "SubExpression"){
    std::string first_child_type = semanticTraversal(root->children.front(), symboltable);
    std::string second_child_type = semanticTraversal(root->children.back(), symboltable);
    if(first_child_type != "Int" && second_child_type != "Int") std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Operation '" << root->type << "' expects 'Int' for arguments '" << root->children.front()->value << "' and '" << root->children.back()->value  << "', got '" << first_child_type << "' and '" << second_child_type << "'" << std::endl;
    else if(first_child_type != "Int") std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Operation '" << root->type << "' expects 'Int' for argument '" << root->children.front()->value << "', got '" << first_child_type << "'" << std::endl;
    else if(second_child_type != "Int") std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Operation '" << root->type << "' expects 'Int' for argument '" << root->children.back()->value << "', got '" << second_child_type << "'" << std::endl;
    return "Int";
  }

  else if(root->type == "GreaterThanExpression" || root->type == "LessThanExpression"){
    std::string first_child_type = semanticTraversal(root->children.front(), symboltable);
    std::string second_child_type = semanticTraversal(root->children.back(), symboltable);
    if(first_child_type != "Int" || second_child_type != "Int"){
			std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Operation '" << root->type << "' expects 'Int' for arguments '" <<  root->children.front()->value << "' and '" << root->children.back()->value << "', got '" << first_child_type << "' and '" << second_child_type << "'" << std::endl;
		}
    return "Boolean";
  }
  else if(root->type == "NotExpression"){
    std::string first_child_type = semanticTraversal(root->children.front(), symboltable);

    if(first_child_type != "Boolean") std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Operation '" << root->type << "' expects 'Boolean' for argument '" << root->children.front()->value << "', got '" << first_child_type << "'" << std::endl;
    return "Boolean";
  }
  else if(root->type == "Expression"){
    return semanticTraversal(root->children.front(), symboltable);
  }
    else if(root->type == "ThisExpression"){
    Record* this_record = symboltable->get_scope()->get_this();
    if (this_record != NULL) {
      return this_record->get_id();
    } else {
      return "Undefined";
    }
  }

  // ------------- Array ----------------

  else if(root->type == "ArrayAccess"){
    std::string first_child = semanticTraversal(root->children.front(), symboltable);
    std::string second_child = semanticTraversal(root->children.back(), symboltable);

    if(first_child != "IntArray") {
      std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: ArrayAccess expects 'IntArray' for array, got '" << first_child << "'" << std::endl;
      return "Undefined";
    };
    if(second_child != "Int") {
      std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: ArrayAccess expects 'Int' for index, got '" << second_child << "'" << std::endl;
      return "Undefined";
    };

    return "Int";
  }
  else if(root->type == "ArrayLength"){
    std::string lhs = semanticTraversal(root->children.front(), symboltable);
    if(lhs != "IntArray") std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Array type expected, got '" << lhs << "'" << std::endl;
    return "Int";
  }
  // --------------- Statements -------------------------
  else if(root->type == "ArrayAssignStatement"){
    std::string first_child = semanticTraversal(root->children.front(), symboltable);
    std::string second_child = semanticTraversal((*std::next(root->children.begin(), 1)), symboltable);
    std::string third_child = semanticTraversal(root->children.back(), symboltable);

    if(first_child != "IntArray") std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: ArrayAssignStatement expects 'IntArray' for array, got '" << first_child << "'" << std::endl;
    if(second_child != "Int") std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: ArrayAssignStatement expects 'Int' for index, got '" << second_child << "'" << std::endl;
    if(third_child != "Int") std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: ArrayAssignStatement expects 'Int' for value, got '" << third_child << "'" << std::endl;

    return "null";
  }
  else if(root->type == "AssignStatement"){
    std::string first_child_type = semanticTraversal(root->children.front(), symboltable);
    std::string second_child_type = semanticTraversal(root->children.back(), symboltable);
    if (first_child_type != second_child_type) {
      std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: AssignStatement expects '" << first_child_type << "' for variable '" << root->children.front()->value << "', got '" << second_child_type << "'" << std::endl;
    }
    return "null";
  }
  else if(root->type == "WhileStatement" || root->type == "IfStatement" || root->type == "IfElseStatement"){
    Node* first_child = (*std::next(root->children.begin(), 1));
    semanticTraversal(root->children.front(), symboltable);
    semanticTraversal(first_child, symboltable);
		if (root->type == "IfElseStatement") {
			Node* second_child = (*std::next(root->children.begin(), 2));
			semanticTraversal(second_child, symboltable);
			}
    return "null";
  }
  else if(root->type == "PrintlnStatement"){
    Node* child = root->children.front();
    if(child->type == "Identifier"){
      Record* identifier = symboltable->lookup(child->value);
      if(identifier == NULL) std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Variable '" << child->value << "' is not defined" << std::endl;
    }
    std::string print_type = semanticTraversal(root->children.front(), symboltable);// check type
    return "null";
  }
  else if(root->type == "NewArray"){
    std::string array_type = semanticTraversal(root->children.front(), symboltable);
    if(array_type != "Int") std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Array type expected, got '" << array_type << "'" << std::endl;
    return "IntArray";
  }
  else if(root->type == "NewObject"){
    Class* new_class = (Class*)symboltable->lookup(root->value, std::vector<std::string>{"Class"});


    if(new_class == NULL){std::cerr << "@error at line " << std::to_string(root->lineno) << ". Semantic error: Class '" << root->value << "' is not defined" << std::endl;
      return "Undefined";
    }
    return new_class->get_id();
  }
  
  else if(root->type == "Identifier"){ //
    Record* identifier = symboltable->lookup(root->value);
    if (identifier == nullptr) {
      return "Undefined";
    } else {
      return identifier->get_type();
    }
  }
  else if(root->type == "IntLiteral" || root->type == "SubIntLiteral" || root->type == "Int"){return "Int";}
  else if(root->type == "TrueExpression" || root->type == "FalseExpression"){return "Boolean";}
	else if(root->type == "Variable"){return root->value;}
  else {
    for(auto i = root->children.begin(); i != root->children.end(); i++){
      semanticTraversal(*i, symboltable);
    }
		return root->value;
  }
  return root->value;
};