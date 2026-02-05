Trabalho Final: Sistema de Navegação Viária com Autocomplete e Caminho Mínimo
1. Visão Geral e Objetivos
O objetivo deste trabalho é consolidar os conhecimentos adquiridos ao longo do semestre através da implementação de uma aplicação prática que resolve um problema real de sistemas de informações geográficas (GIS).

Os discentes deverão implementar um sistema capaz de carregar a malha viária da cidade de Pelotas (extraída do OpenStreetMap), permitindo ao usuário buscar interseções de ruas através de um sistema de autocompletar eficiente (Trie) e calcular a melhor rota entre dois pontos utilizando algoritmos de grafos (Dijkstra).

Objetivos Pedagógicos:

Manipulação de estruturas de dados avançadas (Árvores Digitais/Tries).

Representação e manipulação de Grafos Direcionados e Ponderados.

Implementação do algoritmo de Dijkstra com fila de prioridade.

Uso de ferramentas de desenvolvimento profissionais (IDE Qt Creator).

2. Formação dos Grupos
O trabalho deve ser realizado em trios ou, no máximo, quartetos.

Grupos menores ou individuais só serão permitidos em casos excepcionais e mediante autorização prévia do professor.

3. Descrição do Problema
O sistema deve operar em três etapas principais:

Carregamento de Dados: Ler arquivos JSON contendo a topologia da cidade (nodos e arestas).

Interação com Usuário (Busca): Permitir que o usuário digite o nome de um local (interseção) e o sistema sugira completamentos possíveis instantaneamente.

Processamento (Navegação): Após o usuário selecionar uma Origem e um Destino, o sistema deve calcular o caminho de menor custo (distância) respeitando o sentido das vias.

3.1. A Base de Dados
Serão fornecidos quatro arquivos JSON extraídos via OSMNX:

edges.json: Contém as arestas do grafo (ruas).

nodes.json: Contém os vértices (interseções/geolocalização).

label_to_nodes.json: Mapeia nomes de interseções para IDs de nodos.

nodes_to_label.json: Mapeia IDs de nodos para nomes legíveis.

4. Requisitos de Implementação
4.1. Estruturas de Dados e Algoritmos
Grafo: Listas de Adjacência (Direcionado e Ponderado).

Trie: Para o autocomplete de nomes de ruas.

Dijkstra: Com Fila de Prioridade (Heap) para cálculo de rota $O(E + V \log V)$.

4.2. Ferramentas de Desenvolvimento (Obrigatório)
IDE: O desenvolvimento deve ser realizado utilizando a IDE Qt Creator.

Gerenciamento de Projeto: É obrigatório o uso de arquivos de projeto nativos da IDE (ex: .pro com qmake ou CMakeLists.txt configurado via Qt Creator). O projeto deve estar corretamente configurado para que o professor possa abri-lo, compilá-lo e executá-lo diretamente pelo Qt Creator sem necessidade de configurações manuais complexas.

5. Requisitos de Entrega
O pacote de entrega deve conter:

Pasta do Projeto: Todos os arquivos de código (.cpp, .h) e o arquivo de projeto do Qt Creator (.pro ou CMakeLists.txt).

README.md: Arquivo contendo:

Nomes dos integrantes.

Instruções de como abrir e rodar o projeto no Qt Creator.

Descrição resumida das estruturas.

Scripts de Dependências: (Se necessário) Instruções para instalação de bibliotecas externas.

6. Avaliação e Defesa
Data de Início das Apresentações: 09/12, durante o horário da aula.

Critérios de Avaliação:

Funcionalidade (Autocomplete e Dijkstra).

Qualidade do código e uso correto das estruturas.

Documentação e facilidade de compilação via Qt Creator.

Arguição Oral: Todos os membros do grupo devem dominar todo o código apresentado.

⚠️ Política Anti-Plágio e "Vibe Coding"
Fica estritamente proibida a prática de "vibe coding" (uso indiscriminado de código gerado por IA ou copiado de fontes externas sem o devido entendimento, crítica ou adaptação).

Arguição Individual: Durante a apresentação, os alunos serão arguidos individualmente sobre trechos específicos do código.

Se um aluno não souber explicar o funcionamento de uma função, estrutura ou algoritmo presente no seu trabalho, a nota do componente ou de todo o grupo poderá ser penalizada. O objetivo é avaliar a compreensão e a capacidade de implementação dos discentes.

7. Seção Bônus: Interface Gráfica com Qt (+10%)
Para incentivar o desenvolvimento de aplicações completas, será concedido um bônus de 10% na nota final para grupos que implementarem uma Interface Gráfica de Usuário (GUI).

Requisitos do Bônus:

A interface deve ser construída utilizando os recursos visuais do Qt.

Funcionalidades: Entrada de texto com dropdown de sugestões (Trie), visualização do mapa e da rota.

Recurso Recomendado: Recomenda-se fortemente o uso do Qt Location Plugin para OpenStreetMap para renderização do mapa (https://doc.qt.io/qt-6/location-plugin-osm.html).

8. Dicas do Professor
Qt Creator: Familiarizem-se cedo com a IDE. Ela possui excelentes ferramentas de debugging e visualização de memória que ajudarão muito com os ponteiros da Trie e do Grafo.

Parsing de JSON: Usem bibliotecas prontas (nlohmann/json ou as próprias bibliotecas do Qt QJsonDocument).

Múltiplos Nodos: Lembrem-se que um nome de rua pode estar ligado a vários IDs de nodos.

Memória: Usem Listas de Adjacência. Monitore o consumo de memória.

Validação: Testem o sistema com rotas conhecidas para garantir que o Dijkstra está respeitando o sentido das ruas.