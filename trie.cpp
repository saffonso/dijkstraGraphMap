#include "trie.h"

Trie::Trie() :root(std::make_unique<TrieNode>()) {}

void Trie::insert(const std::string& word){
    TrieNode* current = root.get();

    for(char c : word){
        if(current->children.find(c) == current->children.end()){
            current->children[c] = std::make_unique<TrieNode>();
        }
        current = current->children[c].get();
    }

    current->isEndOfWord = true;
}

bool Trie::search(const std::string& word)  {
    TrieNode* current = root.get();

    for(char c : word){
        if(current->children.find(c) == current->children.end()){
            return false;
        }
        current = current->children.find(c)->second.get();
    }

    return current->isEndOfWord;
}

void Trie::
