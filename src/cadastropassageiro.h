#ifndef CADASTROPASSAGEIRO_H
#define CADASTROPASSAGEIRO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

struct Passageiro {
    int codigo;
    char nome[100];
    char endereco[200];
    int telefone;
    int quantidade_voos;
};

class CadastroPassageiro {
public:
    std::vector<Passageiro> carregar_passageiros(const std::string& arquivo);

    bool cadastrar(const std::string& arquivo, const Passageiro& passageiro);
};

template <typename T>
bool ler_inteiro(T& num) {
    while (!(std::cin >> num)) {
        std::cout << "Entrada inválida. Digite somente números." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return true;
}

#endif 
