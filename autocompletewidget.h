#ifndef AUTOCOMPLETEWIDGET_H
#define AUTOCOMPLETEWIDGET_H

#include "trie.h"
#include <QWidget>
#include <QListWidgetItem>

class AutocompleteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutocompleteWidget(const Trie& trie, QWidget *parent = nullptr);

signals:
    void locationSelect(const QString& name, const QVector<long long>& nodeIds);
private slots:
    void onTextChanged(const QString& text);
    void onItemClicked(QListWidgetItem* item);
private:
    void showPopup();
    void hidePopup();
    void updateSuggestions(const QString& text);

    const Trie& trie;

    QLineEdit* lineEdit;
    QListWidget* popup;

    std::vector<std::pair<std::string, std::vector<long long>>> currentResults;
};

#endif // AUTOCOMPLETEWIDGET_H
