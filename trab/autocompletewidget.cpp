#include "autocompletewidget.h"
#include <QKeyEvent>

AutocompleteWidget::AutocompleteWidget(const Trie& trie, QWidget *parent)
    : QWidget(parent), m_trie(trie)
{
    // Create main layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);
    
    // Create line edit
    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setPlaceholderText("Digite para buscar locais (Ex: Praça, Rua...)");
    
    // Create list widget (NOT a popup, just a normal widget)
    m_popup = new QListWidget(this);
    m_popup->setFocusPolicy(Qt::NoFocus);  // Never takes focus
    m_popup->setMouseTracking(true);
    m_popup->setMaximumHeight(200);
    m_popup->hide();
    
    // Style the list
    m_popup->setStyleSheet(
        "QListWidget {"
        "   border: 1px solid #ccc;"
        "   background-color: white;"
        "   selection-background-color: #0078d4;"
        "   selection-color: white;"
        "}"
        "QListWidget::item {"
        "   padding: 8px;"
        "   border-bottom: 1px solid #eee;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #e5f3ff;"
        "}"
    );
    
    // Add to layout in order
    layout->addWidget(m_lineEdit);
    layout->addWidget(m_popup);
    setLayout(layout);
    
    // Connect signals
    connect(m_lineEdit, &QLineEdit::textChanged, this, &AutocompleteWidget::onTextChanged);
    connect(m_popup, &QListWidget::itemClicked, this, &AutocompleteWidget::onItemClicked);
}

void AutocompleteWidget::onTextChanged(const QString& text)
{
    if (text.isEmpty()) {
        hidePopup();
        return;
    }
    
    updateSuggestions(text);
}

void AutocompleteWidget::updateSuggestions(const QString& text)
{
    // Call Trie autocomplete function
    m_currentResults = m_trie.autocomplete(text.toStdString(), 10);
    
    m_popup->clear();
    
    if (m_currentResults.empty()) {
        hidePopup();
        return;
    }
    
    // Add results to popup
    for (const auto& [name, nodeIds] : m_currentResults) {
        QString displayText = QString::fromStdString(name);
        
        // Add node IDs count as additional info
        if (!nodeIds.empty()) {
            displayText += QString(" (%1 nó%2)")
                .arg(nodeIds.size())
                .arg(nodeIds.size() > 1 ? "s" : "");
        }
        
        m_popup->addItem(displayText);
    }
    
    showPopup();
}

void AutocompleteWidget::showPopup()
{
    if (m_popup->count() == 0) {
        hidePopup();
        return;
    }
    
    // Calculate height based on number of items (approximately 30px per item)
    int itemHeight = 35;
    int visibleItems = qMin(m_popup->count(), 6);  // Show max 6 items
    int popupHeight = visibleItems * itemHeight;
    
    m_popup->setMinimumHeight(popupHeight);
    m_popup->setMaximumHeight(popupHeight);
    m_popup->show();
    m_popup->raise();  // Bring to front
    m_popup->update();  // Force repaint
}

void AutocompleteWidget::hidePopup()
{
    m_popup->hide();
}

void AutocompleteWidget::onItemClicked(QListWidgetItem* item)
{
    int index = m_popup->row(item);
    
    if (index >= 0 && index < static_cast<int>(m_currentResults.size())) {
        const auto& [name, nodeIds] = m_currentResults[index];
        
        // Update line edit with selected text
        m_lineEdit->setText(QString::fromStdString(name));
        
        // Convert std::vector to QVector
        QVector<long long> qNodeIds;
        for (long long id : nodeIds) {
            qNodeIds.append(id);
        }
        
        // Emit signal with selection
        emit locationSelected(QString::fromStdString(name), qNodeIds);
        
        hidePopup();
    }
}


