#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "autocompletewidget.h"
#include <QWidget>
#include <QTextEdit>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(const Trie& trie, QWidget *parent = nullptr);

private slots:
    void onLocationSelected(const QString& name, const QVector<long long>& nodeIds);

private:
    const Trie& trie;

    AutocompleteWidget *autocompleteWidget;
    QTextEdit *selectedInfoDisplay;
};

#endif // MAINWINDOW_H
