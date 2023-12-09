#include "stdio.h"
// #include "../include/Graph.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <sstream>

int main() {
    // Nome do arquivo de entrada
    std::string nome_do_arquivo_entrada = "B34.txt";

    // Abrir o arquivo de entrada para leitura
    std::ifstream arquivo_entrada(nome_do_arquivo_entrada);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo_entrada.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
        return 1; // Saída com erro
    }

    // Nome do arquivo de saída
    std::string nome_do_arquivo_saida = "B34saida.txt";

    // Abrir o arquivo de saída para escrita
    std::ofstream arquivo_saida(nome_do_arquivo_saida);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo_saida.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saida." << std::endl;
        return 1; // Saída com erro
    }

    // Leitura e impressão do nome da instância
    std::string linha;
    std::getline(arquivo_entrada, linha);
    arquivo_saida << linha << std::endl;

    // Leitura do inteiro "No of trucks"
    int K;
    std::getline(arquivo_entrada, linha);
    std::istringstream iss_K(linha.substr(39)); // Ignorando "No of trucks: "
    iss_K >> K;
    arquivo_saida << "Valor de K: " << K << std::endl;

      // Leitura do campo "Dimension"
    int n;
    std::getline(arquivo_entrada, linha);
    std::getline(arquivo_entrada, linha);
    std::istringstream iss_Dimension(linha.substr(11)); // Ignorando "Dimension: "
    iss_Dimension >> n;
    arquivo_saida << "Valor de n: " << n << std::endl;

     // Leitura do campo "CAPACITY"
    int q;
    std::getline(arquivo_entrada, linha);
    std::getline(arquivo_entrada, linha);
    std::istringstream iss_Capacity(linha.substr(10)); // Ignorando "Dimension: "
    iss_Capacity >> q;
    arquivo_saida << "Capacidade: " << q << std::endl;
    
    // Leitura dos coordenadas a partir de "NODE_COORD_SECTION"

    getline(arquivo_entrada, linha);
    
    int Xcoord[n];
    int Ycoord[n];
    int cap[n];
    int i,x,y;
    
    for(int j=0;j<n;j++)
    {
        std::getline(arquivo_entrada, linha);
        std::istringstream iss(linha);
        //::cout<< linha << std::endl;
        iss >> i >> x >> y; // vai preencher todos os nós de 1 até n, o 0 vai ser o deposito
        Xcoord [i] = x;
        Ycoord [i] = y;
    }

    // Leitura das demandas a partir de "Demand_Section"
    getline(arquivo_entrada, linha);
    std::cout<< linha << std::endl;
    for(int j=0;j<n;j++)
    {
        int c;
        std::getline(arquivo_entrada, linha);
        std::istringstream iss(linha);
        //std::cout<< linha << std::endl;
        iss >> i >> c; // vai preencher todos os nós de 1 até n, o 0 vai ser o deposito
        cap [i] = c;
    }

    // Leitura do depósito
    getline(arquivo_entrada, linha);
    std::cout<< linha << std::endl;
    getline(arquivo_entrada, linha);
    std::istringstream iss(linha);
    iss >> Xcoord[0];
    getline(arquivo_entrada, linha);
    std::istringstream iss2(linha);
    iss2 >> Ycoord[0];
    cap[0]=-1;

    // imprime todos os dados

    for(int j=0; j<=n; j++)
    {
        std::cout<< j <<" "<< Xcoord[j]<< " " << Ycoord[j]<< " " << cap [j]<< std::endl;

    }

    // Fechar os arquivos
    arquivo_entrada.close();
    arquivo_saida.close();

    std::cout << "Leitura e processamento concluídos com sucesso." << std::endl;

    return 0; // Saída bem-sucedida
}
