#ifndef TRIE_H
#define TRIE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class TrieNode{
public:
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    bool isEndOfWord;

    TrieNode(): isEndOfWord(false){}
};

class Trie
{
private:
    std::unique_ptr<TrieNode> root;

public:
    Trie();

    void insert(const std::string& word);

    bool search(const std::string& word);

    std::vector<std::string> autocomplete(const std::string& prefix, int maxResults = 5) const;
};

#endif // TRIE_H
