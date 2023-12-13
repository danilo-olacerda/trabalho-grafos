#include "../include/Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
using namespace std;

#include <cmath>
#include <algorithm>

struct Vertice {
    int numero;
    float coordenadaX;
    float coordenadaY;
    int demanda;

    Vertice(int num, float x, float y, int dem) : numero(num), coordenadaX(x), coordenadaY(y), demanda(dem) {}
};

struct Veiculo {
    int capacidade;
    vector<int> rota;

    Veiculo(int cap) : capacidade(cap) {}
};

struct Grafo {
    int numVertices;
    vector<Vertice> vertices;

    Grafo() : numVertices(0) {}

    void adicionarVertice(int num, float x, float y, int dem) {
        vertices.emplace_back(num, x, y, dem);
        numVertices++;
    }
};

double calcularDistancia(const Vertice& v1, const Vertice& v2) {
    return sqrt(pow(v1.coordenadaX - v2.coordenadaX, 2) + pow(v1.coordenadaY - v2.coordenadaY, 2));
}

bool compararDemandasDecrescente(const Vertice& v1, const Vertice& v2) {
    return v1.demanda > v2.demanda;
}

void resolverCVRPserie(const Grafo& grafo, int capacidadeVeiculo, int numVeiculos, ofstream& arquivo_saida) {
    int numVertices = grafo.numVertices;
    cout <<"entrou na resolver"<< endl;
    cout << endl;
    vector<Vertice> verticesOrdenados = grafo.vertices;
    sort(verticesOrdenados.begin() + 1, verticesOrdenados.end(), compararDemandasDecrescente);

    vector<bool> visitado(numVertices, false);
    vector<Veiculo> veiculos;

    // Inicializa os veículos com capacidadeVeiculo
    for (int i = 0; i < numVeiculos; ++i) {
        veiculos.emplace_back(capacidadeVeiculo);
    }

    // Inicializa o veículo na origem (vértice 0)
    int veiculoAtual = 0;
    int capacidadeAtual = 0;
    int verticeAtual = 0;

    while (true) {
        veiculos[veiculoAtual].rota.push_back(verticeAtual);
        visitado[verticeAtual] = true;
        capacidadeAtual += grafo.vertices[verticeAtual].demanda;

        auto it = find_if(verticesOrdenados.begin(), verticesOrdenados.end(), [verticeAtual](const Vertice& v) {
            return v.numero == verticeAtual;
        });

        verticesOrdenados.erase(it);

        int proximoVertice = -1;
        double menorDistancia = numeric_limits<double>::max();

        for (const Vertice& v : verticesOrdenados) {
            if (!visitado[v.numero] && capacidadeAtual + v.demanda <= veiculos[veiculoAtual].capacidade) {
                double distancia = calcularDistancia(grafo.vertices[verticeAtual], v);
                if (distancia < menorDistancia) {
                    menorDistancia = distancia;
                    proximoVertice = v.numero;
                }
            }
        }

        if (proximoVertice == -1) {
            capacidadeAtual = 0;
            proximoVertice = 0;
            veiculos[veiculoAtual].rota.push_back(proximoVertice);

            // Se todos os veículos tiverem sido usados, termina
            if (verticesOrdenados.empty() || veiculoAtual == veiculos.size() - 1) {
                break;
            }

            // Passa para o próximo veículo
            veiculoAtual++;
        }

        verticeAtual = proximoVertice;
    }

    // Imprime as rotas e a distância total
    double distanciaTotal = 0.0;
    for (const Veiculo& veiculo : veiculos) {
        cout << "Rota do Veiculo: ";
        arquivo_saida << "Rota do Veiculo: ";
        for (int v : veiculo.rota) {
            cout << v << " ";
            arquivo_saida << v << " ";
        }
        cout << endl;
        arquivo_saida << endl;

        // Calcula a distância da rota
        for (int i = 0; i < veiculo.rota.size() - 1; ++i) {
            distanciaTotal += calcularDistancia(grafo.vertices[veiculo.rota[i]], grafo.vertices[veiculo.rota[i + 1]]);
        }
    }

    cout << "Distancia total percorrida em serie: " << distanciaTotal << endl;
    arquivo_saida << "Distancia total percorrida em serie: " << distanciaTotal << endl;
    
}

void resolverCVRPparalelo(const Grafo& grafo, int capacidadeVeiculo, int numVeiculos, ofstream& arquivo_saida) {
    int numVertices = grafo.numVertices;

    cout <<"entrou na resolver paralelo"<< endl;

    vector<Vertice> verticesOrdenados = grafo.vertices;
    sort(verticesOrdenados.begin() + 1, verticesOrdenados.end(), compararDemandasDecrescente);

    vector<bool> visitado(numVertices, false);
    vector<Veiculo> veiculos;

    // Inicializa os veículos com capacidadeVeiculo
    for (int i = 0; i < numVeiculos; ++i) {
        veiculos.emplace_back(capacidadeVeiculo);
    }

    // Inicializa os veículos na origem (vértice 0)
    for (int i = 0; i < numVeiculos; ++i) {
        veiculos[i].rota.push_back(0);
        visitado[0] = true;
    }

    int veiculoAtual = 0;

    // Distribui os vértices entre os veículos
    for (const Vertice& v : verticesOrdenados) {
        if (!visitado[v.numero]) {
            // Verifica qual veículo tem a menor carga atual
            int menorCapacidade = veiculos[0].capacidade;
            int veiculoEscolhido = 0;

            for (int i = 1; i < numVeiculos; ++i) {
                if (veiculos[i].capacidade < menorCapacidade) {
                    menorCapacidade = veiculos[i].capacidade;
                    veiculoEscolhido = i;
                }
            }

            // Adiciona o vértice ao veículo escolhido
            veiculos[veiculoEscolhido].rota.push_back(v.numero);
            visitado[v.numero] = true;
            veiculos[veiculoEscolhido].capacidade += v.demanda;
        }
    }

    // Adiciona o depósito ao final de cada rota
    for (int i = 0; i < numVeiculos; ++i) {
        veiculos[i].rota.push_back(0);
    }

    // Imprime as rotas e a distância total
    double distanciaTotal = 0.0;
    for (const Veiculo& veiculo : veiculos) {
        cout << "Rota do Veiculo: ";
        arquivo_saida << "Rota do Veiculo: ";
        for (int v : veiculo.rota) {
            cout << v << " ";
            arquivo_saida << v << " ";
        }
        cout << endl;
        arquivo_saida << endl;

        // Calcula a distância da rota
        for (int i = 0; i < veiculo.rota.size() - 1; ++i) {
            distanciaTotal += calcularDistancia(grafo.vertices[veiculo.rota[i]], grafo.vertices[veiculo.rota[i + 1]]);
        }
    }
    cout << "Distancia total percorrida em paralelo: " << distanciaTotal << endl;
    arquivo_saida << "Distancia total percorrida em paralelo: " << distanciaTotal << endl;
}

void capInstancia(vector<int>& cap)
{
    int demandaTotal=0;
    for(int i=0;i<cap.size();i++)
    {
        demandaTotal += cap[i];
    }

    cout<< endl<< "demanda total da instancia: " << demandaTotal << endl;
    cout<<endl;
}

int main1(int argc, char *argv[])
{
    // cout << argc << argv << endl;
    // char option = 'a';
    // int saida = 0;

    // system("cls");

    // // Nome do arquivo, para criar novo
    // string arquivo = "output.txt";

    // // Abrir o arquivo para escrita
    // ofstream arquivo_saida(arquivo);

    // // Verificar se o arquivo foi aberto
    // if (!arquivo_saida.is_open())
    // {
    //     cerr << "Erro ao criar o arquivo." << endl;
    //     return 1; // Saída com erro
    // }

    // // Escrever o conteúdo do arquivo
    // arquivo_saida << "Arq saída de grafos" << endl;
    // arquivo_saida << "Teste de operações" << endl;

    // // Fechar o arquivo
    // arquivo_saida.close();

    // // Verificar
    // cout << "Arquivo \"" << arquivo << "\" criado com sucesso." << endl;

    // while (saida == 0)
    // {
    //     option = Escolha(option);

    //     switch (option)
    //     {
    //     case 'a':
    //         /*Parâmetro: um Id de um vértice de um grafo direcionado;
    //         Saída: o fecho transitivo direto deste vértice.

    //         imprimeSaida(option)*/
    //         break;
    //     case 'b':
    //         /* Parâmetro: um Id de um vértice de um grafo direcionado;
    //         Saída: o fecho transitivo indireto deste vértice.

    //         imprimeSaida(option)*/
    //         break;
    //     case 'c':
    //         /*  Parâmetro: dois IDs de vértices do grafo;
    //             Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Djkstra;

    //             imprimeSaida(option)*/
    //         break;
    //     case 'd':
    //         /*  Parâmetro: dois IDs de vértices do grafo;
    //             Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Floyd;

    //             imprimeSaida(option)*/
    //         break;
    //     case 'e':
    //         /*  Parâmetro: um subconjunto X de vértices do grafo;
    //             Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim;

    //             imprimeSaida(option)*/
    //         break;
    //     case 'f':
    //         /*  Parâmetro: um subconjunto X de vértices do grafo;
    //             Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de
    //             Kruskal;

    //             imprimeSaida(option)*/
    //         break;
    //     case 'g':
    //         /*  Parâmetro: um ID de vértice;
    //             Saída: a árvore dada pela ordem de caminhamento em profundidade a partir de nó dado parâmetro,
    //             destacando as arestas de retorno;

    //             imprimeSaida(option)*/
    //         break;
    //     case 'h':
    //         /*  Parâmetro: o próprio grafo acíclico direcionado D;
    //             Saída: uma ordenação topológica em D ou a informação de que D não é um grafo acíclico
    //             direcionado.

    //          imprimeSaida(option)
    //          */
    //         break;
    //     case 'i':
    //         /*  Parâmetro: o grafo (direcionado ou não direcionado) ponderado nas arestas
    //             Saída: O raio, o diâmetro, o centro e a periferia do grafo.

    //             imprimeSaida(option)
    //             */
    //         break;
    //     case 'j':
    //         /*  Parâmetro: o grafo não direcionado
    //             Saída: O conjunto de vértices de articulação.

    //             imprimeSaida(option)
    //             */
    //         break;
    //     case 's':
    //         saida = 1;
    //         cout << "Execucao finalizada." << endl;
    //         break;

    //     default:
    //         saida = 1;
    //         break;
    //     }
    //     if (saida != 1)
    //         cout << "Deseja executar mais alguma funcionalidade ? " << endl;
    // }
    // return 0;
}

int main2(int argc, char *argv[]) {
    
        vector<string> ArqsEntrada = {"A34.txt", "A48.txt", "B34.txt", "B50.txt", "Golden1.txt", "Golden17.txt", "X101.txt", "X280.txt", "M101.txt", "M151.txt"};


    for(int c=0;c<10;c++)
    {

    cout << argc << argv << endl;

    int control;
    int k;
    int gold1=0;
    
    // Nome do arquivo de entrada
    string nome_do_arquivo_entrada = ArqsEntrada[c];

    // Abrir o arquivo de entrada para leitura
    ifstream arquivo_entrada(nome_do_arquivo_entrada);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo_entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1; // Saída com erro
    }

    // Nome do arquivo de saída
    string nome_do_arquivo_saida = "Guloso3.txt";

    // Abrir o arquivo de saída para escrita
    //ofstream arquivo_saida(nome_do_arquivo_saida,ofstream::out | ofstream::trunc);
      ofstream arquivo_saida(nome_do_arquivo_saida,ios::app);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo_saida.is_open()) {
        cerr << "Erro ao abrir o arquivo de saida." << endl;
        return 1; // Saída com erro
    }
    // Leitura e impressão do nome da instância
    string linha;
    string instancia;
    getline(arquivo_entrada, linha);

    size_t firstNonWhiteSpace = linha.find_first_not_of(" \t");
    size_t lastNonWhiteSpace = linha.find_last_not_of(" \t");

    // Verificar se a linha é não vazia
    if (firstNonWhiteSpace != string::npos && lastNonWhiteSpace != string::npos) {
    // Extrair a parte significativa da linha
    instancia = linha.substr(firstNonWhiteSpace, lastNonWhiteSpace - firstNonWhiteSpace + 1);
    cout<<instancia<<endl;}
    cout<< linha<<endl;
    // Filtrando qual instância será lida
    if (linha == "NAME : A-n34-k5" || linha=="NAME : A-n48-k7" || linha=="NAME : B-n34-k5"|| linha=="NAME : B-n50-k8") 
    {
        cout << "Leitura AB" << endl;
        control=0;
        cout<<control<<endl;
    } 
    else if (linha == "NAME : M-n101-k10" || linha == "NAME : M-n151-k12") 
    {
        control=2;
        cout << "Leitura M" << endl;
        cout<<control<<endl;
    } 
    else if (linha.find("n101-k25") != string::npos)
    {
            cout << "Leitura X k25" << endl;
            k=25;
            control=1;
            cout<<control<<k<<endl;
    }
    else if( linha.find("280-k17")!= string::npos) 
    {
        cout << "Leitura X k17" << endl;
        k=17;
        control=1;
        cout<<control<<" "<<k<<endl;
    } 
    else if (linha == "NAME : Golden_1")
    {
            cout << "Leitura Golden k9" << endl;
            k=9;
            control=1;
            gold1=1;
            cout<<control<<k<<endl;
    }
    else if( linha == "NAME : Golden_17") 
    {
        cout << "Leitura Golden k22" << endl;
        k=22;
        control=1;
        cout<<control<<k<<endl;
    } 
    else 
    {
        cout << "Nao e possivel ler essa instancia" << endl;
        cout << linha <<  endl;
        return 1;
    }
    
    //Passa pro arquivo de saída a instancia lida

    arquivo_saida << endl << linha << endl;

    // Leitura do inteiro "No of trucks"
    if(control==0)
    {
        k=0;
        getline(arquivo_entrada, linha);
        istringstream iss_K(linha.substr(39)); // Ignorando "No of trucks: "
        iss_K >> k;
        arquivo_saida << "Valor de k: " << k << endl;
    }
    else if(control==1)
    {   //Mudar
        getline(arquivo_entrada, linha);
        arquivo_saida << "Valor de K: " << k << endl;
    }
    else
    {
        getline(arquivo_entrada, linha);
        istringstream iss_K(linha.substr(45)); // Ignorando "No of trucks: "
        iss_K >> k;
        arquivo_saida << "Valor de K: " << k << endl;
    }
    
    
      // Leitura do campo "Dimension"
    int n;
    getline(arquivo_entrada, linha);
    getline(arquivo_entrada, linha);
    istringstream iss_Dimension(linha.substr(11)); // Ignorando "Dimension: "
    iss_Dimension >> n;
    arquivo_saida << "Valor de n: " << n << endl;

     // Leitura do campo "CAPACITY"
    int capacidadeVeiculo;
    getline(arquivo_entrada, linha);
    getline(arquivo_entrada, linha);
    istringstream iss_Capacity(linha.substr(10)); // Ignorando "Dimension: "
    iss_Capacity >> capacidadeVeiculo;
    arquivo_saida << "Capacidade: " << capacidadeVeiculo << endl;
    
    // Leitura dos coordenadas a partir de "NODE_COORD_SECTION"

    if(gold1==1) // corrige a leitura da instancia golden 1
    {getline(arquivo_entrada, linha);}

    getline(arquivo_entrada, linha);

     vector<float> Xcoord(n);
     vector<float> Ycoord(n);
     vector<int> cap(n);

    int i;
    float x,y;
    
    for(int j=0;j<n;j++)
    {
        getline(arquivo_entrada, linha);
        istringstream iss(linha);
        //::cout<< linha << endl;
        iss >> i >> x >> y; // vai preencher todos os nós de 1 até n, o 0 vai ser o deposito
        Xcoord [i-1] = x;
        Ycoord [i-1] = y;
        // cout<< i << " "<< x << " "<< y  << " "<< endl;

    }

    // Leitura das demandas a partir de "Demand_Section"
    getline(arquivo_entrada, linha);
    cout<< linha << endl;
    for(int j=0;j<n;j++)
    {
        int c;
        getline(arquivo_entrada, linha);
        istringstream iss(linha);
        //cout<< linha << endl;
        iss >> i >> c; // vai preencher todos os nós de 1 até n, o 0 vai ser o deposito

        cap [i-1] = c;
    }

    // Leitura do depósito
    // getline(arquivo_entrada, linha);
    // cout<< linha << endl;
    // getline(arquivo_entrada, linha);
    // istringstream iss(linha);
    // iss >> Xcoord[0];
    // getline(arquivo_entrada, linha);
    // istringstream iss2(linha);
    // iss2 >> Ycoord[0];
    // cap[0]=0;

    // imprime todos os dados

    for(int j=0; j<n; j++)
    {
       cout<< j <<" "<< Xcoord[j]<< " " << Ycoord[j]<< " " << cap [j]<< endl;

    }

    //Algoritmo Guloso:

    Grafo grafo;

    // Adiciona os vértices conforme necessário, incluindo o depósito como primeiro vértice

    for(int j=0; j<n; j++)
    {
       grafo.adicionarVertice (j,Xcoord[j],Ycoord[j],cap [j]);

    }
    // Adiciona os vértices conforme necessário, incluindo o depósito como primeiro vértice

    capInstancia(cap);

    resolverCVRPparalelo(grafo, capacidadeVeiculo, k,arquivo_saida);
    resolverCVRPserie(grafo, capacidadeVeiculo, k,arquivo_saida);
    

    //Verifica a Solução

    
    // Fechar os arquivos
    arquivo_entrada.close();
    arquivo_saida.close();

    cout << "Leitura e processamento concluidos com sucesso." << endl;
    }
    return 0; // Saída bem-sucedida
    
}

int main(int argc, char *argv[])
{

    argc = 3; // para testar a main1

    if (argc == 7)
    {
        main1(argc, argv);
    }
    else if (argc == 3)
    {
        main2(argc, argv);
    } else {
        cout << "Números de argumentos inválidos." << endl;
    }


    return 0;
}