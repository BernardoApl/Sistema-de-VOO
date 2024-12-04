#ifndef CADASTROASSENTO_H
#define CADASTROASSENTO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Voo
{
    int codigoVoo;        
    string dataHora;      
    string origem;      
    string destino;       
    int codigoAviao;    
    int codigoPiloto;     
    int codigoCopiloto;   
    int codigoComissario; 
    bool status;          
    double tarifa;       
};

struct Assento
{
    int numeroAssento; 
    int codigoVoo;     
    bool status;       
};

class CompanhiaAerea
{
private:
    string arquivoVoos = "voos.dat";         
    string arquivoAssentos = "assentos.dat"; 

public:
    bool vooExiste(int codigo);
    void cadastrarAssentos();
};

#endif 
