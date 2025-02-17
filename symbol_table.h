#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>
#include "Node.h"

class Record {
  protected:
    std::string id;
    std::string type;
    std::string record;
  public:
    Record(std::string id, std::string type, std::string record);
    virtual ~Record() {}
    std::string get_id();
    std::string get_type();
    std::string get_record();
    int get_lineno();
    void set_id(std::string id);
    void set_type(std::string type);
    void set_record(std::string record);
    void print_record();
};

class Variable: public Record {
public:
  Variable(std::string name, std::string type);
};

class Parameter: public Record {
public:
  int idx;
  Parameter(std::string name, std::string type, int idx = -1);
};


class Method: public Record {
  protected:
    std::unordered_map<std::string, std::vector<Parameter*>> parameters;
    std::unordered_map<std::string, std::vector<Variable*>> variables;
  public:
    Method(std::string name, std::string type);
    void add_parameter(Parameter *parameter);
    void add_variable(Variable *variable);
    int get_parameters_size();
    std::vector<Parameter*> get_parameters();
};


class Class: public Record {
  protected:
    std::unordered_map<std::string, Variable*> variables;
    std::unordered_map<std::string, Method*> methods;
  public:
    Class(std::string name, std::string type);
    void add_variable(Variable* variable);
    void add_method(Method* method);
    Record* lookup_variable(std::string id);
    Method* lookup_method(std::string id);
};

class Scope {
  int next = 0;
  Scope* parent_scope;
  Record* scope_record;

  public:
    std::vector<Scope*> children_scopes;
    std::unordered_map<std::string, Record*> records;
    std::string scope_name;
    
    Scope(Scope *parent, std::string name, Record* record);
    void add_record(Record *record);
    Scope* get_parent();
    Scope* next_child(std::string name, Record* record);
    Scope* get_child(std::string name);
    Record* lookup(std::string key, std::string type = "");
    Record* get_scope_record();
    std::string get_scope_name();
    Record* get_this();
    void reset_scope();
    void printScopeTree(int &count, ofstream *outStream);
};


class SymbolTable {
  Scope *root;
  Scope *current;

  public:
    SymbolTable();
    Scope* get_scope();
    void create_scope(std::string name, Record* record);
    void enter_scope(std::string name);
    void exit_scope();
    void add_record(Record *record);
    Record* lookup(std::string key, const std::vector<std::string>& types = {});
    Record* get_method();
    void reset_table();
    void generate_tree();
};





void treeTraversal(Node* root, SymbolTable* table);

#endif