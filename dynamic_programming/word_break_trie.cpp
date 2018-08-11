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
        bool exists(std::string word);
	void print_tree(std::map<char, Node*> tree);
    	void print();

  protected:
    Node head;
    std::vector<Node*> children;
    std::vector<string> trie_dict;
};

Trie::Trie(std::vector<std::string> words){
  result = "";
  vector<string> *new_dict = &trie_dict;
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

bool Trie::exists(std::string word){

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

std::string WordBreak(std::string word, Trie *trie){

  int length = word.size();

	if(trie->exists(word)) return word;

	if(trie->found_words.find(word) != trie->found_words.end())
		return trie->found_words[word];



	for(int i=1; i<length; i++){
		std::string prefix = word.substr(0, i);

		if(trie->exists(prefix)){
			std::string suffix = word.substr(i, length);
			std::string segment = WordBreak(suffix, trie);

			if(!segment.empty()){
				return prefix + " " + segment;
			}
		}
	}

	trie->found_words[word] = "";
	return "";
}


int main(int argc, char** argv) {

    std::vector<std::string> dictionary = {"mobile","samsung","sam","sung",
                            "man","mango", "icecream","and",
                            "go","i","love","ice","cream"};


    Trie trie(dictionary);

    std::string input_string = "sungilovesamsung";

    std::string result = WordBreak(input_string, &trie);

    std::cout<<result<<std::endl;

    return 0;
}
