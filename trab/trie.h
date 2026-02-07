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
    std::vector<long long> nodeIds;  // IDs dos nós do grafo
    
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    std::unique_ptr<TrieNode> root;
    
    // Função auxiliar para coletar palavras a partir de um nó
    void collectWords(TrieNode* node, const std::string& prefix, 
                      std::vector<std::pair<std::string, std::vector<long long>>>& results, 
                      int maxResults) const;

public:
    Trie();
    
    // Insere uma palavra na Trie com seus IDs
    void insert(const std::string& word, const std::vector<long long>& nodeIds);
    
    // Verifica se uma palavra existe na Trie
    bool search(const std::string& word) const;
    
    // Retorna sugestões de autocomplete com IDs (até maxResults)
    std::vector<std::pair<std::string, std::vector<long long>>> autocomplete(
        const std::string& prefix, int maxResults = 5) const;
};

#endif // TRIE_H
