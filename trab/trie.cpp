#include "trie.h"

Trie::Trie() : root(std::make_unique<TrieNode>()) {}

void Trie::insert(const std::string& word) {
    TrieNode* current = root.get();
    
    for (char c : word) {
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = std::make_unique<TrieNode>();
        }
        current = current->children[c].get();
    }
    
    current->isEndOfWord = true;
}

bool Trie::search(const std::string& word) const {
    TrieNode* current = root.get();
    
    for (char c : word) {
        auto it = current->children.find(c);
        if (it == current->children.end()) {
            return false;
        }
        current = it->second.get();
    }
    
    return current->isEndOfWord;
}

void Trie::collectWords(TrieNode* node, const std::string& prefix, 
                        std::vector<std::string>& results, int maxResults) const {
    if (results.size() >= static_cast<size_t>(maxResults)) {
        return;
    }
    
    if (node->isEndOfWord) {
        results.push_back(prefix);
    }
    
    for (const auto& pair : node->children) {
        if (results.size() >= static_cast<size_t>(maxResults)) {
            break;
        }
        collectWords(pair.second.get(), prefix + pair.first, results, maxResults);
    }
}

std::vector<std::string> Trie::autocomplete(const std::string& prefix, int maxResults) const {
    std::vector<std::string> results;
    TrieNode* current = root.get();
    
    // Navega até o nó do prefixo
    for (char c : prefix) {
        auto it = current->children.find(c);
        if (it == current->children.end()) {
            return results; // Prefixo não existe
        }
        current = it->second.get();
    }
    
    // Coleta palavras a partir do nó do prefixo
    collectWords(current, prefix, results, maxResults);
    
    return results;
}
