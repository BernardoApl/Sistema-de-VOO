#ifndef CADASTROTRIPULACAO_H
#define CADASTROTRIPULACAO_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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