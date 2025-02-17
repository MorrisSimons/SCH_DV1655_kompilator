#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include "symbol_table.h"

Class::Class(std::string name, std::string type): Record(name, type, "Class") {
  this->variables = std::unordered_map<std::string, Variable*>();
  this->methods = std::unordered_map<std::string, Method*>();
}

void Class::add_variable(Variable* variable) {
  this->variables[variable->get_id()] = variable;
}

void Class::add_method(Method* method) {
  this->methods[method->get_id()] = method;
}

Record* Class::lookup_variable(std::string id) {
  if(variables.find(id) != variables.end()) {
    return variables[id];
  }
  return NULL;
}

Method* Class::lookup_method(std::string id) {
  if(methods.find(id) != methods.end()) {
      return (Method*)methods[id];
  }
  return NULL;
}

Method::Method(std::string name, std::string type): Record(name, type, "Method") {}

void Method::add_parameter(Parameter *parameter) {
    this->parameters[parameter->get_id()].push_back(parameter);
}

void Method::add_variable(Variable *variable) {
    this->variables[variable->get_id()].push_back(variable);
}

int Method::get_parameters_size() {
    int count = 0;
    for (auto i = this->parameters.begin(); i != this->parameters.end(); i++) {
        count += i->second.size();
    }
    return count;
}

std::vector<Parameter*> Method::get_parameters(){
    std::vector<Parameter*> parameters;
    for (auto i = this->parameters.begin(); i != this->parameters.end(); i++) {
        for (auto j = i->second.begin(); j != i->second.end(); j++) {
            parameters.push_back(*j);
        }
    }

    std::sort(parameters.begin(), parameters.end(), [](const Parameter* a, const Parameter* b) {
        return a->idx < b->idx;
    });

    return parameters;
}

Parameter::Parameter(std::string name, std::string type, int idx): Record(name, type, "Parameter") {
  this->idx = idx;
}

Record::Record(std::string id, std::string type, std::string record) {
  this->id = id;
  this->type = type;
  this->record = record;
  }

std::string Record::get_id() {
  return this->id;
}

void Record::set_id(std::string id) {
  this->id = id;
}

std::string Record::get_type() {
  return this->type;
}

void Record::set_type(std::string type) {
  this->type = type;
}

std::string Record::get_record() {
  return this->record;
}

void Record::set_record(std::string record) {
  this->record = record;
}

void Record::print_record() {
  std::cout << this->record << "(" << this->type << ", " << this->id << ")" << std::endl;
}

Scope::Scope(Scope *parent, std::string name, Record* record){
  this->parent_scope = parent;
  this->scope_name = name;
  this->scope_record = record;
};

void Scope::add_record(Record *record){
  this->records[record->get_id()] = record;
}

Scope* Scope::get_parent(){
  return this->parent_scope;
}

Scope* Scope::next_child(std::string name, Record* record){
  // look for the next child scope
  Scope* next_child;
  if(next == children_scopes.size()){
    next_child = new Scope(this, name, record);
    children_scopes.push_back(next_child);
  } else {
    next_child = children_scopes[next];
  }
  next++;
  return next_child;
}

Scope* Scope::get_child(std::string name){
  for(auto i = children_scopes.begin(); i != children_scopes.end(); i++){
    if((*i)->get_scope_name() == name){
      return *i;
    }
  }
  return NULL;
}

Record* Scope::lookup(std::string key, std::string type){
  // get the record from the current scope
  if(records.find(key) != records.end()){
    if(type != ""){
      if(records[key]->get_record() == type){
        return records[key];
      }
    } else { return records[key];}
  }
  
  if(parent_scope == NULL){
    return NULL;
  }

  return parent_scope->lookup(key, type);
}

Record* Scope::get_scope_record(){
  return this->scope_record;
}

std::string Scope::get_scope_name(){
  return this->scope_name;
}

Record* Scope::get_this(){
  // get class record from current scope
  Scope* current_scope = this;
  Record* scope_record = current_scope->get_scope_record();

  while(current_scope != nullptr){
    if(scope_record != NULL && scope_record->get_type() == "Class"){
      return scope_record;
    }

    current_scope = current_scope->get_parent();
    scope_record = current_scope->get_scope_record();
  }

  return NULL;
}

Variable::Variable(std::string name, std::string type): Record(name, type, "Variable") {}

void Scope::reset_scope(){
  next = 0;
  for(int i = 0; i < children_scopes.size(); i++){
    children_scopes[i]->reset_scope();
  }
}

void Scope::printScopeTree(int &count, std::ofstream *outStream) {
    // print the current scope
    int id = count;
    *outStream << "n" << id << " [label=\"Symbol table: (" << this->scope_name << ")\\n";
    for (auto i = records.begin(); i != records.end(); i++) {
        *outStream << "ID:" << i->second->get_id() << ";  RecordType: "<< i->second->get_record() <<"; Return type: " << i->second->get_type()<<  "\\n";
    }
    *outStream << "\"];" << std::endl;

    for (auto i : this->children_scopes){
        int n = ++count;
        i->printScopeTree(count, outStream);
        *outStream << "n" << id << " -> n" << n << std::endl;
    }
}

SymbolTable::SymbolTable() {
  root = new Scope(NULL, "Global", NULL);
  current = root;
}

Scope* SymbolTable::get_scope(){
  return current;
}

void SymbolTable::create_scope(std::string name, Record* record){
  current = current->next_child(name, record);
}

void SymbolTable::enter_scope(std::string name){
  Scope* scope = current->get_child(name);
  if(scope != nullptr){ current = scope; }
}

void SymbolTable::exit_scope() {
  if(current->get_parent() != nullptr){ current = current->get_parent(); }
}

void SymbolTable::add_record(Record *record) { current->add_record(record); }

Record* SymbolTable::lookup(std::string key, const std::vector<std::string>& types) {
  // If types vector is empty, perform a single type lookup
  if (types.empty()) { return current->lookup(key); }

  // Otherwise, check for a match in multiple types
  for (const auto& type : types) {
    Record* record = current->lookup(key, type);
    if (record != nullptr) { return record; }
  }
  return nullptr;
}


Record* SymbolTable::get_method(){
  Scope* scope = current;
  while(scope != NULL){
    Record* record = scope->lookup(scope->get_scope_name(), "Method");
    if(record != NULL){ return record; }
    scope = scope->get_parent();
  }
  return NULL;
}

void SymbolTable::reset_table() {
  root->reset_scope();
  current = root;
}

void SymbolTable::generate_tree() {
  std::ofstream file;
  file.open("symbol_tree.dot");
  int count = 0;
  file << "digraph {" << std::endl;
  root->printScopeTree(count, &file);
  file << "}" << std::endl;
  file.close();
}

void treeTraversal(Node* node, SymbolTable* symbol_table) {
if (node->type == "Global") {
  // Global has two children: MainClass and ClassDeclarationList

  auto main_class = (*std::next(node->children.begin(), 0));
  auto class_declaration_list = (*std::next(node->children.begin(), 1));
  
  auto main_class_declaration = new Class(main_class->value, "Class");
  symbol_table->add_record(main_class_declaration);

  //the children of the class declaration list are ClassDeclaration
  std::for_each(class_declaration_list->children.begin(), class_declaration_list->children.end(), [&](auto& child) {
    if (symbol_table->lookup(child->value) != NULL) {
      std::cerr << "@error at line " << to_string(child->lineno) << ".  Symboltable error: Class '" << child->value << "' is already declared" << std::endl;
    }
    auto class_declaration = new Class(child->value, "Class");
    symbol_table->add_record(class_declaration);
  });

  //create scope for main class
  symbol_table->create_scope(main_class->value, symbol_table->lookup(main_class->value));
  treeTraversal(main_class, symbol_table);
  symbol_table->exit_scope();

  //create scope for class declarations
  std::for_each(class_declaration_list->children.begin(), class_declaration_list->children.end(), [&](auto& child) {
    symbol_table->create_scope(child->value, symbol_table->lookup(child->value));
    treeTraversal(child, symbol_table);
    symbol_table->exit_scope();
  });

}
else if (node->type == "VarDeclaration" || node->type == "TypeIdentifier") {
  // VarDeclaration has two children: TypeIdentifier and Identifier
  // TypeIdentifier has two children: Type and Identifier  
    Node* type = node->children.front();
    Node* name = node->children.back();
    Record* variable;
    std::vector<std::string> types;
    if (node->type == "VarDeclaration") {
      types = {"Parameter", "Variable"};
    } else {
      types = {"Parameter"};
    }

    variable = symbol_table->lookup(name->value, types);

    if (variable != NULL) {
      std::cerr << "@error at line " << to_string(node->lineno) << ".  Symboltable error: " << node->type << " '" << name->value << "' is already declared" << std::endl;
    }

    // Check if the type is a custom type
    if (type->type == "Identifier") {
      Record* custom_type = symbol_table->lookup(type->value);

      if (custom_type == NULL) {
      std::cerr << "@error at line " << to_string(type->lineno) << ".  Symboltable error: Type '" << type->value << "' is undefined" << std::endl;
      } else {
       if (node->type == "VarDeclaration") {
          symbol_table->add_record(new Variable(name->value, type->value));
        } else {symbol_table->add_record(new Parameter(name->value, type->value));}
      }
    } 
    else {
      if (node->type == "VarDeclaration") {
      symbol_table->add_record(new Variable(name->value, type->type));
      } else { symbol_table->add_record(new Parameter(name->value, type->type));}
      }
    } 
else if (node->type == "ClassDeclaration" || node->type == "MainClass") {
  std::for_each(node->children.begin(), node->children.end(), [&](auto& child) {
    treeTraversal(child, symbol_table);
  });

} 
else if (node->type == "MethodDeclaration") {
  // MethodDeclaration has three children: TypeIdentifier, Identifier, and MethodBody
  Record* existing_method = symbol_table->lookup(node->value, std::vector<std::string>{"Method"});
  if (existing_method != NULL) {
    std::cerr << "@error at line " << to_string(node->lineno) << ".  Symboltable error: Method '" << node->value << "' is already declared" << std::endl;
  }
  
  Node* type_node = (*std::next(node->children.begin(), 0));
  // content of the method
  Node* body_node = node->children.back();
  
  Node* return_node = node->children.back()->children.back()->children.front();
  // parameters of the method
  Node* param_node = *(std::prev(node->children.end(), 2));

  std::string return_type;
  if (type_node->type == "Identifier") {
    return_type = type_node->value;
  } else {
    return_type = type_node->type;
  }
  Method* method = new Method(node->value, return_type);
  Class* current_class = dynamic_cast<Class*>(symbol_table->get_scope()->get_scope_record());
  if (current_class) { current_class->add_method(method); }

  symbol_table->add_record(method);
  symbol_table->create_scope(node->value, method);
  
  // goin into TypeIdentifier
  treeTraversal(param_node, symbol_table);

  int idx = 0;
  std::for_each(param_node->children.begin(), param_node->children.end(), [&](auto& child) {
    Node* type_node = child->children.front();
    std::string type;
    if (type_node->type == "Identifier") { type = type_node->value; } 
    else { type = type_node->type; }
    method->add_parameter(new Parameter(child->children.back()->value, type, idx++));
  });
  std::for_each(body_node->children.begin(), std::prev(body_node->children.end()), [&](auto& child) { 
    treeTraversal(child, symbol_table); 
    });

  if (return_node->type == "Identifier") {   
    Record* return_record = symbol_table->lookup(return_node->value);
    if (return_record == NULL) {
      std::cerr << "@error at line " << to_string(return_node->lineno) << ".  Symboltable error: Return type '" << return_node->value << "' is undefined" << std::endl;
    }
  }
  symbol_table->exit_scope();
} 
  
  else {
    for (auto i = node->children.begin(); i != node->children.end(); i++) {
      treeTraversal(*i, symbol_table);
    }
  }
}