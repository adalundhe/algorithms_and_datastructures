#ifndef __TRIE_H_INCLUDES__
#define __TRIE_H_INCLUDES__

#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <iostream>

constexpr int ALPHABET_SIZE = 26;

struct Node {
  char character;
  std::map<char, Node*> children;
};

class Trie{
  public:
	std::map<std::string, std::string> found_words;
	std::string result;
	Trie() { head.character = -1; };
        Trie(std::vector<std::string> words);
        ~Trie();
        void insert(std::string word);
        bool exists(const std::string word);
        bool charexists(const char c);
        bool isend(const char c);
        char get(const char query);
	void print_tree(std::map<char, Node*> tree);
    	void print();

  protected:
    Node head;
    std::vector<Node*> children;
    std::vector<std::string> trie_dict;
};

Trie::Trie(std::vector<std::string> words){
  result = "";
  std::vector<std::string> *new_dict = &trie_dict;
	*new_dict = words;

  for(auto const &word : words){
      insert(word);
   }
}

Trie::~Trie(){
  for(auto &node : children){
    delete node;
  }
}


void Trie::insert(std::string const word){

  std::map<char, Node*> *current_tree = &head.children;
  std::map<char, Node*>::iterator node_iterator;

  for(auto const &c : word){

    if((node_iterator = current_tree->find(c)) != current_tree->end()){
      current_tree = &node_iterator->second->children;
      continue;
    }

    if(node_iterator == current_tree->end()){

      Node* new_node = new Node();

      new_node->character = c;
      (*current_tree)[c] = new_node;

      current_tree = &new_node->children;

      children.push_back(new_node);

    }

  }

}

bool Trie::exists(const std::string word){

   std::map<char, Node*> *current_tree = &head.children;
   std::map<char, Node*>::iterator node_iterator;

   int counter = 0;

   for(auto const &c : word){

     if((node_iterator = current_tree->find(c)) == current_tree->end()) return false;

     current_tree = &node_iterator->second->children;

     counter++;
   }

   return true;

}

void Trie::print_tree(std::map<char, Node*> tree) {
  if (tree.empty()) {
    return;
  }

  for (std::map<char, Node*>::iterator it=tree.begin(); it!=tree.end(); ++it) {
    std::cout << it->first << std::endl;
    print_tree(it->second->children);
  }
}

void Trie::print() {
  std::map<char, Node*> current_tree = head.children;
  print_tree(current_tree);
}

bool Trie::charexists(const char c){
  std::map<char, Node*> *current_tree = &head.children;
  std::map<char, Node*>::iterator node_iterator;

  return current_tree->find(c) != current_tree->end();
}

bool Trie::isend(const char c){
  std::map<char, Node*> *current_tree = &head.children;
  std::map<char, Node*>::iterator node_iterator;

  return (node_iterator = current_tree->find(c)) == current_tree->end();
}

char Trie::get(const char query){
  std::map<char, Node*> *current_tree = &head.children;
  char result = current_tree->find(query)->first;
  return result;
}

#endif
