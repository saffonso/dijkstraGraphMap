#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class TrieNode {
public:
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    std::unique_ptr<TrieNode> root;
    
    // Função auxiliar para coletar palavras a partir de um nó
    void collectWords(TrieNode* node, const std::string& prefix, 
                      std::vector<std::string>& results, int maxResults) const;

public:
    Trie();
    
    // Insere uma palavra na Trie
    void insert(const std::string& word);
    
    // Verifica se uma palavra existe na Trie
    bool search(const std::string& word) const;
    
    // Retorna sugestões de autocomplete (até maxResults)
    std::vector<std::string> autocomplete(const std::string& prefix, int maxResults = 5) const;
};

#endif // TRIE_H
