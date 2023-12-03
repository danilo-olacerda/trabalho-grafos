#include "stdio.h"
// #include "../include/Graph.h"
#include <iostream>
#include <fstream>
#include <string>
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
// int main()
// {
//     int order = 6;

//     Graph *graph = new Graph();

//     graph->addNode(1);
// }

char Escolha(char option)
{
    char c=option;
    cout<<"As seguintes funcionalidades estão disponiveis, escolha uma delas ou 's' para sair"<<endl;
    cout<<"para algumas escolhas, vai ser preciso escolher vertices como parametro(posteriormente)"<<endl<<endl;
    cout<<"a: Fecho transitivo direto de um vértice"<<endl;
    cout<<"b: Fecho transitivo indireto de um vértice"<<endl;
    cout<<"c: O caminho mínimo entre dois vértices usando algoritmo de Djkstra "<<endl;
    cout<<"d: O caminho mínimo entre dois vértices usando algoritmo de Floyd"<<endl;
    cout<<"e: Uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim;"<<endl;
    cout<<"f: Uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Kruskal"<<endl;
    cout<<"g: A árvore dada pela ordem de caminhamento em profundidade destacando as arestas de retorno"<<endl;
    cout<<"h: Uma ordenação topológica em D ou a informação de que D não é um grafo acíclico direcionado"<<endl;
    cout<<"i: O raio, o diâmetro, o centro e a periferia do grafo"<<endl;
    cout<<"j: O conjunto de vértices de articulação"<<endl;
    cin>>c;
    cout<<endl;


    return c;
}
void imprimeSaida(char escolha)
{
    // char necessário para adicionar ao arquivo qual das funcionalidades foi usada antes de adicionar o resultado
    char salvar;
    cout<<"deseja salvar esse resultado? (s = sim / n = nao)"<<endl;
    cin>>salvar;
    if(salvar=='s')
    {
        cout<<"resultado salvo!"<<endl;
        //adicionar no arquivo de saída
    }
}
int main()
{
    char option;
    int saida=0;

    
    // Nome do arquivo, para criar novo
    std::string arquivo = "teste.txt";

    // Abrir o arquivo para escrita
    std::ofstream arquivo_saida(arquivo);

    // Verificar se o arquivo foi aberto
    if (!arquivo_saida.is_open()) {
        std::cerr << "Erro ao criar o arquivo." << std::endl;
        return 1; // Saída com erro
    }

    // Escrever o conteúdo do arquivo
    arquivo_saida << "Arq saída de grafos" << std::endl;
    arquivo_saida << "Teste de operações" << std::endl;

    // Fechar o arquivo
    arquivo_saida.close();

    //Verificar
    std::cout << "Arquivo \"" << arquivo << "\" criado com sucesso." << std::endl;


    cout << "Arquivo carregado, escolha uma das funcionalidades: " << endl;

    // while (saida==0)
    // {
    //     option=Escolha(option);
    
    // switch (option)
    // {
    // case 'a':
    //     /*Parâmetro: um Id de um vértice de um grafo direcionado;
    //     Saída: o fecho transitivo direto deste vértice. 
        
    //     imprimeSaida(option)*/
    //     break;
    // case 'b':
    //     /* Parâmetro: um Id de um vértice de um grafo direcionado;
    //     Saída: o fecho transitivo indireto deste vértice. 
        
    //     imprimeSaida(option)*/
    //     break;
    // case 'c':
    //     /*  Parâmetro: dois IDs de vértices do grafo;
    //         Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Djkstra; 
            
    //         imprimeSaida(option)*/
    //     break;
    // case 'd':
    //     /*  Parâmetro: dois IDs de vértices do grafo;
    //         Saída: o caminho mínimo entre estes dois vértices usando algoritmo de Floyd; 
            
    //         imprimeSaida(option)*/
    //     break;
    // case 'e':
    //     /*  Parâmetro: um subconjunto X de vértices do grafo;
    //         Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim; 
            
    //         imprimeSaida(option)*/
    //     break;
    // case 'f':
    //     /*  Parâmetro: um subconjunto X de vértices do grafo;
    //         Saída: uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de
    //         Kruskal; 
            
    //         imprimeSaida(option)*/
    //     break;
    // case 'g':
    //     /*  Parâmetro: um ID de vértice;
    //         Saída: a árvore dada pela ordem de caminhamento em profundidade a partir de nó dado parâmetro,
    //         destacando as arestas de retorno; 
            
    //         imprimeSaida(option)*/
    //     break;
    // case 'h':
    //     /*  Parâmetro: o próprio grafo acíclico direcionado D;
    //         Saída: uma ordenação topológica em D ou a informação de que D não é um grafo acíclico
    //         direcionado.
         
    //      imprimeSaida(option)
    //      */
    //     break;
    // case 'i':
    //     /*  Parâmetro: o grafo (direcionado ou não direcionado) ponderado nas arestas
    //         Saída: O raio, o diâmetro, o centro e a periferia do grafo.
            
    //         imprimeSaida(option)
    //         */
    //     break;
    // case 'j':
    //     /*  Parâmetro: o grafo não direcionado
    //         Saída: O conjunto de vértices de articulação.
            
    //         imprimeSaida(option)
    //         */
    //     break;                
    // case 's':
    //     saida = 1;
    //     cout<<"encerrando"<<endl;
    //     break;

    // default:
    //     saida=1;
    //     break;
    // }
    //     if(saida!=1)
    //         cout << "deseja executar mais alguma funcionalidade? " << endl;
    // }
    return 0;
}