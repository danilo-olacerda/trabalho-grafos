#include "../include/Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
using namespace std;

/*
    Obs1: Ajustar a leitura de acordo com a semÂntica do arquivo do T2

    Obs2:
    •./execGrupoX <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>, onde
    < arquivo_entrada> é o nome do arquivo que contém as informações do grafo, < arquivo_saida> é o arquivo
    onde será gravado o grafo armazenado na memória ao término

        - Obs2.1: as Opc serão do tipo int 0 ou 1, 0 para não e 1 para sim. Executar a criação do grafo de acordo com o solicitado.

    Obs3: Após cada saída das funcionalidas, o usuário terá a opção de salvar ou não o resultado no arquivo de saída

    Obs4: A main vai ser uma rotina de leitura do arquivo e após isso um while com switch case aguardando o usuário escolher entre as funcionalidades ou interromper a execução

*/

char Escolha(char option)
{
    char c = option;
    cout << "As seguintes funcionalidades estao disponiveis, escolha uma delas ou 's' para sair" << endl;
    cout << "para algumas escolhas, vai ser preciso escolher vertices como parametro (posteriormente)" << endl
         << endl;
    cout << "a: Fecho transitivo direto de um vertice" << endl;
    cout << "b: Fecho transitivo indireto de um vertice" << endl;
    cout << "c: O caminho minimo entre dois vertices usando algoritmo de Djkstra " << endl;
    cout << "d: O caminho minimo entre dois vertices usando algoritmo de Floyd" << endl;
    cout << "e: Uma arvore Geradora Minima sobre o subgrafo vertice-induzido por X usando o algoritmo de Prim;" << endl;
    cout << "f: Uma arvore Geradora Minima sobre o subgrafo vertice-induzido por X usando o algoritmo de Kruskal" << endl;
    cout << "g: A arvore dada pela ordem de caminhamento em profundidade destacando as arestas de retorno" << endl;
    cout << "h: Uma ordenacao topologica em D ou a informacao de que D nao eh um grafo aciclico direcionado" << endl;
    cout << "i: O raio, o diametro, o centro e a periferia do grafo" << endl;
    cout << "j: O conjunto de vertices de articulacao" << endl;
    cin >> c;
    cout << endl;

    return c;
}
void imprimeSaida(char escolha)
{
    cout << escolha;
    // char necessário para adicionar ao arquivo qual das funcionalidades foi usada antes de adicionar o resultado
    char salvar;
    cout << "deseja salvar esse resultado? (s = sim / n = nao)" << endl;
    cin >> salvar;
    if (salvar == 's')
    {
        cout << "resultado salvo!" << endl;
        // adicionar no arquivo de saída
    }
}

int main1(int argc, char *argv[])
{
    cout << argc << argv << endl;
    char option = 'a';
    int saida = 0;

    system("cls");

    // Nome do arquivo, para criar novo
    string arquivo = "output.txt";

    // Abrir o arquivo para escrita
    ofstream arquivo_saida(arquivo);

    // Verificar se o arquivo foi aberto
    if (!arquivo_saida.is_open())
    {
        cerr << "Erro ao criar o arquivo." << endl;
        return 1; // Saída com erro
    }

    // Escrever o conteúdo do arquivo
    arquivo_saida << "Arq saída de grafos" << endl;
    arquivo_saida << "Teste de operações" << endl;

    // Fechar o arquivo
    arquivo_saida.close();

    // Verificar
    cout << "Arquivo \"" << arquivo << "\" criado com sucesso." << endl;

    while (saida == 0)
    {
        option = Escolha(option);

        switch (option)
        {
        case 'a':
            /*Parâmetro: um Id de um vértice de um grafo direcionado;
            Saída: o fecho transitivo direto deste vértice.

            imprimeSaida(option)*/
            break;
        case 'b':
            /* Parâmetro: um Id de um vértice de um grafo direcionado;
            Saída: o fecho transitivo indireto deste vértice.

            imprimeSaida(option)*/
            break;
        case 'c':
            /*  Parâmetro: dois IDs de vértices do grafo;
                Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Djkstra;

                imprimeSaida(option)*/
            break;
        case 'd':
            /*  Parâmetro: dois IDs de vértices do grafo;
                Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Floyd;

                imprimeSaida(option)*/
            break;
        case 'e':
            /*  Parâmetro: um subconjunto X de vértices do grafo;
                Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim;

                imprimeSaida(option)*/
            break;
        case 'f':
            /*  Parâmetro: um subconjunto X de vértices do grafo;
                Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de
                Kruskal;

                imprimeSaida(option)*/
            break;
        case 'g':
            /*  Parâmetro: um ID de vértice;
                Saída: a árvore dada pela ordem de caminhamento em profundidade a partir de nó dado parâmetro,
                destacando as arestas de retorno;

                imprimeSaida(option)*/
            break;
        case 'h':
            /*  Parâmetro: o próprio grafo acíclico direcionado D;
                Saída: uma ordenação topológica em D ou a informação de que D não é um grafo acíclico
                direcionado.

             imprimeSaida(option)
             */
            break;
        case 'i':
            /*  Parâmetro: o grafo (direcionado ou não direcionado) ponderado nas arestas
                Saída: O raio, o diâmetro, o centro e a periferia do grafo.

                imprimeSaida(option)
                */
            break;
        case 'j':
            /*  Parâmetro: o grafo não direcionado
                Saída: O conjunto de vértices de articulação.

                imprimeSaida(option)
                */
            break;
        case 's':
            saida = 1;
            cout << "Execucao finalizada." << endl;
            break;

        default:
            saida = 1;
            break;
        }
        if (saida != 1)
            cout << "Deseja executar mais alguma funcionalidade ? " << endl;
    }
    return 0;
}

int main2(int argc, char *argv[]) {

    cout << argc << argv << endl;

    int control;
    int k;
    int gold1=0;
    
    // Nome do arquivo de entrada
    string nome_do_arquivo_entrada = "X280.txt";

    // Abrir o arquivo de entrada para leitura
    ifstream arquivo_entrada(nome_do_arquivo_entrada);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo_entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1; // Saída com erro
    }

    // Nome do arquivo de saída
    string nome_do_arquivo_saida = "Golden1saida.txt";

    // Abrir o arquivo de saída para escrita
    ofstream arquivo_saida(nome_do_arquivo_saida,ofstream::out | ofstream::trunc);

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
        cout<<control<<k<<endl;
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
    
    arquivo_saida << linha << endl;

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
    {   k=0; //Mudar
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
    int q;
    getline(arquivo_entrada, linha);
    getline(arquivo_entrada, linha);
    istringstream iss_Capacity(linha.substr(10)); // Ignorando "Dimension: "
    iss_Capacity >> q;
    arquivo_saida << "Capacidade: " << q << endl;
    
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
        Xcoord [i] = x;
        Ycoord [i] = y;
        cout<< i << " "<< x << " "<< y  << " "<< endl;

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
        cap [i] = c;
    }

    // Leitura do depósito
    getline(arquivo_entrada, linha);
    cout<< linha << endl;
    getline(arquivo_entrada, linha);
    istringstream iss(linha);
    iss >> Xcoord[0];
    getline(arquivo_entrada, linha);
    istringstream iss2(linha);
    iss2 >> Ycoord[0];
    cap[0]=-1;

    // imprime todos os dados

    for(int j=0; j<=n; j++)
    {
        cout<< j <<" "<< Xcoord[j]<< " " << Ycoord[j]<< " " << cap [j]<< endl;

    }

    // Fechar os arquivos
    arquivo_entrada.close();
    arquivo_saida.close();

    cout << "Leitura e processamento concluidos com sucesso." << endl;

    return 0; // Saída bem-sucedida
}

int main(int argc, char *argv[])
{

    argc = 3; // para testar a main1

    if (argc == 3)
    {
        main1(argc, argv);
    }
    else if (argc == 7)
    {
        main2(argc, argv);
    } else {
        cout << "Números de argumentos inválidos." << endl;
    }


    return 0;
}