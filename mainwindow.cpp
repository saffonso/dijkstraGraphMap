#include "mainwindow.h"
#include <QWidget>
#include <qboxlayout.h>
#include <QLabel>

MainWindow::MainWindow(const Trie& trie, QWidget *parent)  : QWidget(parent), trie(trie) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Busca de Locais - Pelotas", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel *searchLabel = new QLabel("Digite para buscar:", this);
    autocompleteWidget = new AutocompleteWidget(trie, this);

    QLabel *infoLabel = new QLabel("Local selecionado:", this);
    selectedInfoDisplay = new QTextEdit(this);
    selectedInfoDisplay->setReadOnly(true);
    selectedInfoDisplay->setPlaceholderText("Selecione um local da lista de sugestões para ver os detalhes...");
    selectedInfoDisplay->setMaximumHeight(150);

    layout->addWidget(titleLabel);
    layout->addSpacing(10);
    layout->addWidget(searchLabel);
    layout->addWidget(autocompleteWidget);
    layout->addSpacing(20);
    layout->addWidget(infoLabel);
    layout->addWidget(selectedInfoDisplay);
    layout->addStretch();

    setLayout(layout);

    connect(autocompleteWidget, &::AutocompleteWidget::locationSelect,
            this, &MainWindow::onLocationSelected);

    setWindowTitle("Sistema de Navegação - Pelotas");
    resize(600, 400);
}

void MainWindow::onLocationSelected(const QString& name, const QVector<long long>& nodeIds)
{
    QString output;
    output += QString("Local: %1\n\n").arg(name);

    for (int i = 0; i < nodeIds.size(); i++) {
        output += QString("   • %1").arg(nodeIds[i]);
        if (i < nodeIds.size() - 1) {
            output += "\n";
        }
    }

    selectedInfoDisplay->setPlainText(output);
}
