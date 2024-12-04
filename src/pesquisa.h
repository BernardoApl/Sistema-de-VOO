#ifndef PESQUISA_H
#define PESQUISA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

struct Passageiro {
    int codigo;
    char nome[100];
    char endereco[200];
    int telefone;
    int quantidade_voos;
    int pontos_fidelidade;
};

struct Voo {
    int numero;
    char data[20];
    char origem[50];
    char destino[50];
    vector<int> passageiros;
    vector<int> tripulantes;
};

struct Tripulacao {
    int codigo;
    string nome;
    string telefone;
    string cargo; // 1 - piloto, 2 - co-piloto, 3 - comissario
};

vector<Tripulacao> lerTripulacao();

template <typename T>
bool ler_inteiro(T& num);

class GerenciadorVoos {
public:
    void ler_dados_arquivos();
    void buscar_passageiro(int codigo);
    void listar_voos_passageiro(int codigo_passageiro);
    void buscar_tripulante(int codigo);
    void cadastrar_voo();
    void listar_voos();
    const vector<Passageiro>& get_passageiros() const;
    void atualizar_pontos_fidelidade(int codigo_passageiro);

private:
    vector<Passageiro> passageiros;
    vector<Voo> voos;
};

#endif 
