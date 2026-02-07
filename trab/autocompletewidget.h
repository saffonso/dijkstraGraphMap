#ifndef AUTOCOMPLETEWIDGET_H
#define AUTOCOMPLETEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QVector>
#include "trie.h"

class AutocompleteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AutocompleteWidget(const Trie& trie, QWidget *parent = nullptr);

signals:
    void locationSelected(const QString& name, const QVector<long long>& nodeIds);

private slots:
    void onTextChanged(const QString& text);
    void onItemClicked(QListWidgetItem* item);

private:
    void showPopup();
    void hidePopup();
    void updateSuggestions(const QString& text);

    const Trie& m_trie;
    
    QLineEdit* m_lineEdit;
    QListWidget* m_popup;
    
    // Store results for selection
    std::vector<std::pair<std::string, std::vector<long long>>> m_currentResults;
};

#endif // AUTOCOMPLETEWIDGET_H
