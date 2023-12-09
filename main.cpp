#include "stdio.h"
// #include "../include/Graph.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <sstream>
#include <cstring>

int main() {
    
    // Nome do arquivo de entrada
    std::string nome_do_arquivo_entrada = "M101.txt";

    // Abrir o arquivo de entrada para leitura
    std::ifstream arquivo_entrada(nome_do_arquivo_entrada);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo_entrada.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
        return 1; // Saída com erro
    }

    // Nome do arquivo de saída
    std::string nome_do_arquivo_saida = "M101saida.txt";

    // Abrir o arquivo de saída para escrita
    std::ofstream arquivo_saida(nome_do_arquivo_saida,std::ofstream::out | std::ofstream::trunc);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo_saida.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saida." << strerror(errno) << std::endl;
        return 1; // Saída com erro
    }
    // Leitura e impressão do nome da instância
    std::string linha;
    std::getline(arquivo_entrada, linha);

    // Filtrando qual instância será lida
    if (linha == "NAME : A-n34-k5" || linha=="NAME : A-n48-k7" || linha=="NAME : B-n34-k5"|| linha=="NAME : B-n50-k8") 
    {
        std::cout << "Leitura AB" << std::endl;
        int control=0;
        std::cout<<control<<std::endl;
    } 
    else if (linha == "NAME : M-n101-k10" || linha == "NAME : M-n151-k12") 
    {
        int control=2;
        std::cout << "Leitura M" << std::endl;
        std::cout<<control<<std::endl;
    } 
    else if (linha == "NAME : 	X-n101-k25")
    {
            std::cout << "Leitura X k25" << std::endl;
            int k=25;
            int control=1;
            std::cout<<control<<k<<std::endl;
    }
    else if( linha == "NAME : 	X-n280-k17") 
    {
        std::cout << "Leitura X k17" << std::endl;
        int k=17;
        int control=1;
        std::cout<<control<<k<<std::endl;
    } 
    else if (linha == "NAME : Golden_1")
    {
            std::cout << "Leitura Golden k9" << std::endl;
            int k=9;
            int control=1;
            std::cout<<control<<k<<std::endl;
    }
    else if( linha == "NAME : Golden_17") 
    {
        std::cout << "Leitura Golden k22" << std::endl;
        int k=22;
        int control=1;
        std::cout<<control<<k<<std::endl;
    } 
    else 
    {
        std::cout << "Não e possivel ler essa instancia" << std::endl;
        return 1;
    }
    
    arquivo_saida << linha << std::endl;

    // Leitura do inteiro "No of trucks"
    if(control==0)
    {
        int K=0;
        std::getline(arquivo_entrada, linha);
        std::istringstream iss_K(linha.substr(39)); // Ignorando "No of trucks: "
        iss_K >> K;
        arquivo_saida << "Valor de K: " << K << std::endl;
    }
    else if(control==1)
    {   
        int k=0;
        std::getline(arquivo_entrada, linha);
        arquivo_saida << "Valor de K: " << K << std::endl;
    }
    else
    {
        int k=0;
        std::getline(arquivo_entrada, linha);
        std::istringstream iss_K(linha.substr(45)); // Ignorando "No of trucks: "
        iss_K >> K;
        arquivo_saida << "Valor de K: " << K << std::endl;
    }
    
    
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

    std::cout << "Leitura e processamento concluidos com sucesso." << std::endl;

    return 0; // Saída bem-sucedida
}
