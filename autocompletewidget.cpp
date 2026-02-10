#include "autocompletewidget.h"
#include "trie.h"
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTimer>

AutocompleteWidget::AutocompleteWidget(const Trie &trie, QWidget *parent)
    : QWidget(parent), trie(trie)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("Digite para buscar locais...");

    int ONE_HUNDRED_AND_FIFT_MS = 150;

    debounceTimer = new QTimer(this);
    debounceTimer->setSingleShot(true);
    debounceTimer->setInterval(ONE_HUNDRED_AND_FIFT_MS);

    popup = new QListWidget(this);
    popup->setFocusPolicy(Qt::NoFocus);
    popup->setMouseTracking(true);
    popup->setMaximumHeight(200);
    popup->hide();

    popup->setStyleSheet(
        "QListWidget {"
        "   border: 1px solid #ccc;"
        "   background-color: white;"
        "   selection-background-color: #0078d4;"
        "}"
        "QListWidget::item {"
        "   padding: 8px;"
        "   border-bottom: 1px solid #eee;"
        "   color: black;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #e5f3ff;"
        "}"
        );

    layout->addWidget(lineEdit);
    layout->addWidget(popup);
    setLayout(layout);

    connect(lineEdit, &QLineEdit::textChanged, this, &AutocompleteWidget::onTextChanged);
    connect(popup, &QListWidget::itemClicked, this, &AutocompleteWidget::onItemClicked);
    connect(debounceTimer, &QTimer::timeout, this, &AutocompleteWidget::performAutocomplete);
}
void AutocompleteWidget::onTextChanged(const QString& text)
{
    debounceTimer->stop();

    if (text.isEmpty()) {
        hidePopup();
        currentResults.clear();
        return;
    }

    currentText = text;
    debounceTimer->start();
}

void AutocompleteWidget::performAutocomplete(){
    if(currentText.isEmpty()){
        return;
    }

    updateSuggestions(currentText);
}

void AutocompleteWidget::updateSuggestions(const QString& text)
{
    auto results = trie.autocomplete(text.toStdString(), 5);

    currentResults = std::move(results);

    popup->clear();

    if (currentResults.empty()) {
        hidePopup();
        return;
    }

    for (const auto& [name, nodeIds] : currentResults) {
        QString displayText = QString::fromStdString(name);
        popup->addItem(displayText);
    }

    showPopup();
}

void AutocompleteWidget::showPopup()
{
    if (popup->count() == 0) {
        hidePopup();
        return;
    }

    int popupHeight = 236;

    popup->setMinimumHeight(popupHeight);
    popup->setMaximumHeight(popupHeight);
    popup->show();
    popup->raise();
    popup->update();
}

void AutocompleteWidget::hidePopup()
{
    popup->hide();
}

void AutocompleteWidget::onItemClicked(QListWidgetItem* item)
{
    int index = popup->row(item);

    if (index >= 0 && index < static_cast<int>(currentResults.size())) {
        const auto& [name, nodeIds] = currentResults[index];

        debounceTimer->stop();
        hidePopup();

        lineEdit->blockSignals(true);
        lineEdit->setText(QString::fromStdString(name));

        QVector<long long> qNodeIds;
        for (long long id : nodeIds) {
            qNodeIds.append(id);
        }

        emit locationSelect(QString::fromStdString(name), qNodeIds);

        hidePopup();
    }
}
