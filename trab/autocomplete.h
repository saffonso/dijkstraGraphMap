#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "trie.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <conio.h>  // Para _getch() no Windows

class InteractiveAutocomplete {
private:
    const Trie& trie;
    
    // Limpa a área de sugestões
    void clearSuggestions(int count) {
        for (int i = 0; i < count + 1; i++) {
            std::cout << "\033[2K\033[1A";  // Limpa linha e sobe
        }
        std::cout << "\r";
    }
    
    // Mostra sugestões
    void showSuggestions(const std::vector<std::pair<std::string, std::vector<long long>>>& suggestions, int selected) {
        if (suggestions.empty()) {
            std::cout << "\n  (Nenhuma sugestao encontrada)" << std::endl;
            return;
        }
        
        std::cout << "\n";
        for (size_t i = 0; i < suggestions.size(); i++) {
            if (i == selected) {
                std::cout << "  > " << suggestions[i].first << " <" << std::endl;
            } else {
                std::cout << "    " << suggestions[i].first << std::endl;
            }
        }
    }
    
public:
    InteractiveAutocomplete(const Trie& t) : trie(t) {}
    
    // Retorna nome selecionado e seus IDs
    std::pair<std::string, std::vector<long long>> getInput(const std::string& prompt) {
        std::cout << prompt;
        std::string input;
        int selected = 0;
        std::vector<std::pair<std::string, std::vector<long long>>> suggestions;
        int lastSuggestionsCount = 0;
        
        while (true) {
            char ch = _getch();
            
            // Enter - confirma seleção
            if (ch == '\r' || ch == '\n') {
                if (!suggestions.empty() && selected < suggestions.size()) {
                    if (lastSuggestionsCount > 0) {
                        clearSuggestions(lastSuggestionsCount);
                    }
                    std::cout << suggestions[selected].first << std::endl;
                    return suggestions[selected];
                } else if (!input.empty()) {
                    if (lastSuggestionsCount > 0) {
                        clearSuggestions(lastSuggestionsCount);
                    }
                    std::cout << input << std::endl;
                    // Tentar buscar exatamente o que foi digitado
                    auto exactSuggestions = trie.autocomplete(input, 1);
                    if (!exactSuggestions.empty()) {
                        return exactSuggestions[0];
                    }
                }
                return {"", {}};
            }
            
            // Backspace
            if (ch == '\b' && !input.empty()) {
                input.pop_back();
                std::cout << "\b \b";
                
                if (lastSuggestionsCount > 0) {
                    clearSuggestions(lastSuggestionsCount);
                }
                
                suggestions = trie.autocomplete(input, 10);
                selected = 0;
                showSuggestions(suggestions, selected);
                lastSuggestionsCount = suggestions.size();
                continue;
            }
            
            // Setas (teclas especiais começam com 0 ou 224)
            if (ch == 0 || ch == -32) {
                ch = _getch();
                
                if (ch == 72 && selected > 0) {  // Seta para cima
                    selected--;
                    if (lastSuggestionsCount > 0) {
                        clearSuggestions(lastSuggestionsCount);
                    }
                    showSuggestions(suggestions, selected);
                    lastSuggestionsCount = suggestions.size();
                } else if (ch == 80 && selected < suggestions.size() - 1) {  // Seta para baixo
                    selected++;
                    if (lastSuggestionsCount > 0) {
                        clearSuggestions(lastSuggestionsCount);
                    }
                    showSuggestions(suggestions, selected);
                    lastSuggestionsCount = suggestions.size();
                }
                continue;
            }
            
            // Caracteres normais
            if (ch >= 32 && ch <= 126) {
                input += ch;
                std::cout << ch;
                
                if (lastSuggestionsCount > 0) {
                    clearSuggestions(lastSuggestionsCount);
                }
                
                suggestions = trie.autocomplete(input, 10);
                selected = 0;
                showSuggestions(suggestions, selected);
                lastSuggestionsCount = suggestions.size();
            }
        }
    }
};

#endif // AUTOCOMPLETE_H
