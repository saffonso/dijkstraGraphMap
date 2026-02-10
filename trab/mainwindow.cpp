#include "mainwindow.h"

MainWindow::MainWindow(const Trie& trie, QWidget *parent)
    : QWidget(parent), m_trie(trie)
{
    // Create layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    // Title label
    QLabel *titleLabel = new QLabel("Busca de Locais - Pelotas", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    
    // Search field with autocomplete
    QLabel *searchLabel = new QLabel("Digite para buscar:", this);
    m_autocompleteWidget = new AutocompleteWidget(m_trie, this);
    
    // Selected location info display
    QLabel *infoLabel = new QLabel("Local selecionado:", this);
    m_selectedInfoDisplay = new QTextEdit(this);
    m_selectedInfoDisplay->setReadOnly(true);
    m_selectedInfoDisplay->setPlaceholderText("Selecione um local da lista de sugestões para ver os detalhes...");
    m_selectedInfoDisplay->setMaximumHeight(150);
    
    // Add widgets to layout
    layout->addWidget(titleLabel);
    layout->addSpacing(10);
    layout->addWidget(searchLabel);
    layout->addWidget(m_autocompleteWidget);
    layout->addSpacing(20);
    layout->addWidget(infoLabel);
    layout->addWidget(m_selectedInfoDisplay);
    layout->addStretch();
    
    setLayout(layout);
    
    // Connect signals
    connect(m_autocompleteWidget, &AutocompleteWidget::locationSelected, 
            this, &MainWindow::onLocationSelected);
    
    // Window settings
    setWindowTitle("Sistema de Navegação - Pelotas");
    resize(600, 400);
}

void MainWindow::onLocationSelected(const QString& name, const QVector<long long>& nodeIds)
{
    QString output;
    output += QString("📍 Local: %1\n\n").arg(name);
    output += QString("🔢 Número de nós: %1\n\n").arg(nodeIds.size());
    output += QString("🆔 IDs dos nós:\n");
    
    for (int i = 0; i < nodeIds.size(); i++) {
        output += QString("   • %1").arg(nodeIds[i]);
        if (i < nodeIds.size() - 1) {
            output += "\n";
        }
    }
    
    m_selectedInfoDisplay->setPlainText(output);
    
    // Auto-close window after selection
    close();
}
