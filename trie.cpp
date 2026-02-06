#include "trie.h"

Trie::Trie() :root(std::make_unique<TrieNode>) {}

void Trie::insert(const std::string& word, long nodeId){
    TrieNode* current = root.get();

    for(char c : word){
        if(current->children.find(c) == current->children.end()){
            current->children[c] = std::make_unique<TrieNode>;
        }
        current = current->children[c].get();
    }

    current->isEndOfWord = true;
    current->nodeId = nodeId;
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

void Trie::collectWords(TrieNode *node, std::string &prefix, std::vector<std::pair<std::string, long>> &results, int maxResults){
    if(results.size() >= static_cast<size_t>(maxResults)){
        return;
    }

    if(node->isEndOfWord){
        results.emplace_back(prefix, node->nodeId);
    }

    for(const auto& pair : node->children){
        if(results.size() >= static_cast<size_t>(maxResults)){
            break;
        }
        collectWords(pair.second.get(), prefix + pair.first, results, maxResults);
    }
}

