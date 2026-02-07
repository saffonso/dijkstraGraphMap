#include "dataloader.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <iostream>

DataLoader::DataLoader(const std::string& path) : dataPath(path) {}

bool DataLoader::loadNodes(Graph& graph) {
    QString filePath = QString::fromStdString(dataPath + "/nodes.json");
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Erro ao abrir " << filePath.toStdString() << std::endl;
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    
    if (parseError.error != QJsonParseError::NoError) {
        std::cerr << "Erro ao parsear nodes.json: " << parseError.errorString().toStdString() << std::endl;
        return false;
    }
    
    if (!doc.isArray()) {
        std::cerr << "nodes.json não contém um array" << std::endl;
        return false;
    }
    
    QJsonArray nodesArray = doc.array();
    for (const QJsonValue& value : std::as_const(nodesArray)) {
        QJsonObject node = value.toObject();
        long long id = static_cast<long long>(node["id"].toDouble());
        double x = node["x"].toDouble();
        double y = node["y"].toDouble();
        graph.addNode(id, x, y);
    }
    
    std::cout << "Carregados " << graph.getNodeCount() << " nodos." << std::endl;
    return true;
}

bool DataLoader::loadEdges(Graph& graph) {
    QString filePath = QString::fromStdString(dataPath + "/edges.json");
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Erro ao abrir " << filePath.toStdString() << std::endl;
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    
    if (parseError.error != QJsonParseError::NoError) {
        std::cerr << "Erro ao parsear edges.json: " << parseError.errorString().toStdString() << std::endl;
        return false;
    }
    
    if (!doc.isArray()) {
        std::cerr << "edges.json não contém um array" << std::endl;
        return false;
    }
    
    QJsonArray edgesArray = doc.array();
    size_t edgeCount = 0;
    for (const QJsonValue& value : std::as_const(edgesArray)) {
        QJsonObject edge = value.toObject();
        long long u = static_cast<long long>(edge["u"].toDouble());
        long long v = static_cast<long long>(edge["v"].toDouble());
        double length = edge["data"].toObject()["length"].toDouble();
        
        graph.addEdge(u, v, length);
        edgeCount++;
    }
    
    std::cout << "Carregadas " << edgeCount << " arestas." << std::endl;
    return true;
}

// Lê label_to_nodes.json e retorna o JSON
QJsonObject DataLoader::loadLabelToNodes() {
    QString filePath = QString::fromStdString(dataPath + "/label_to_nodes.json");
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Erro ao abrir " << filePath.toStdString() << std::endl;
        return QJsonObject();  // Retorna JSON vazio
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    
    if (parseError.error != QJsonParseError::NoError) {
        std::cerr << "Erro ao parsear label_to_nodes.json: " << parseError.errorString().toStdString() << std::endl;
        return QJsonObject();  // Retorna JSON vazio em caso de erro
    }
    
    if (!doc.isObject()) {
        std::cerr << "label_to_nodes.json não contém um objeto" << std::endl;
        return QJsonObject();
    }
    
    QJsonObject labelsJson = doc.object();
    std::cout << "JSON carregado com " << labelsJson.size() << " entradas." << std::endl;
    return labelsJson;
}

// Popula a Trie com dados do JSON
void DataLoader::makeTrie(Trie& trie, const QJsonObject& labelsJson) {
    if (labelsJson.isEmpty()) {
        std::cerr << "JSON vazio, não foi possível popular a Trie." << std::endl;
        return;
    }
    
    size_t count = 0;
    for (auto it = labelsJson.begin(); it != labelsJson.end(); ++it) {
        std::string label = it.key().toStdString();  // Nome do cruzamento
        std::vector<long long> nodeIds;
        
        // Extrai todos os IDs associados ao label
        QJsonArray idsArray = it.value().toArray();
        for (const QJsonValue& id : std::as_const(idsArray)) {
            nodeIds.push_back(static_cast<long long>(id.toDouble()));
        }
        
        // Insere na Trie
        trie.insert(label, nodeIds);
        count++;
    }
    
    std::cout << "Trie populada com " << count << " nomes." << std::endl;
}

// Carrega label_to_nodes.json e popula a Trie diretamente (usa os dois acima)
bool DataLoader::loadAndPopulateTrie(Trie& trie) {
    QJsonObject labelsJson = loadLabelToNodes();  // Lê o JSON
    
    if (labelsJson.isEmpty()) {
        return false;
    }
    
    makeTrie(trie, labelsJson);  // Popula a Trie
    return true;
}


bool DataLoader::loadNodesToLabel(std::unordered_map<long long, std::string>& nodesToLabel) {
    QString filePath = QString::fromStdString(dataPath + "/nodes_to_label.json");
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Erro ao abrir " << filePath.toStdString() << std::endl;
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    
    if (parseError.error != QJsonParseError::NoError) {
        std::cerr << "Erro ao parsear nodes_to_label.json: " << parseError.errorString().toStdString() << std::endl;
        return false;
    }
    
    if (!doc.isObject()) {
        std::cerr << "nodes_to_label.json não contém um objeto" << std::endl;
        return false;
    }
    
    QJsonObject labelsJson = doc.object();
    for (auto it = labelsJson.begin(); it != labelsJson.end(); ++it) {
        long long nodeId = it.key().toLongLong();
        std::string label = it.value().toString().toStdString();
        nodesToLabel[nodeId] = label;
    }
    
    std::cout << "Carregados " << nodesToLabel.size() << " mapeamentos ID->label." << std::endl;
    return true;
}
