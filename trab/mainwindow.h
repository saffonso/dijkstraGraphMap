#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include "trie.h"
#include "autocompletewidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(const Trie& trie, QWidget *parent = nullptr);

private slots:
    void onLocationSelected(const QString& name, const QVector<long long>& nodeIds);

private:
    const Trie& m_trie;
    
    AutocompleteWidget *m_autocompleteWidget;
    QTextEdit *m_selectedInfoDisplay;
};

#endif // MAINWINDOW_H
