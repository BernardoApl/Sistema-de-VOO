#ifndef TRIPULACAO_H
#define TRIPULACAO_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct Tripulacao {
  int codigo;
  string nome;
  string telefone;
  string cargo; // 1 - piloto, 2 - co-piloto, 3 - comissario
};

void salvarTripulacao(const Tripulacao &tripulacao);
vector<Tripulacao> lerTripulacao();
void exibirTripulantes();
void exibirTripulantesPorCargo(const string &cargoDesejado);
int gerarCodigoTripulacao();
void cadastrarTripulante();

#endif
