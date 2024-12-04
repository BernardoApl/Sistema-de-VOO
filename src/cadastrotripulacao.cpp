#include "cadastrotripulacao.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void salvarTripulacao(const Tripulacao &tripulacao) {
  ofstream arquivo("tripulacao.dat", ios::binary | ios::app);
  if (!arquivo) {
    cerr << "Erro ao abrir o arquivo para escrita!" << endl;
    return;
  }
  size_t tamanho;

  arquivo.write(reinterpret_cast<const char *>(&tripulacao.codigo),
                sizeof(tripulacao.codigo));

  tamanho = tripulacao.nome.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(tripulacao.nome.data(), tamanho);

  tamanho = tripulacao.telefone.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(tripulacao.telefone.data(), tamanho);

  tamanho = tripulacao.cargo.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(tripulacao.cargo.data(), tamanho);

  arquivo.close();
}

vector<Tripulacao> lerTripulacao() {
  vector<Tripulacao> tripulantes;
  ifstream arquivo("tripulacao.dat", ios::binary);
  if (!arquivo) {
    cerr << "Erro ao abrir o arquivo para leitura!" << endl;
    return tripulantes;
  }

  Tripulacao tripulacao;
  size_t tamanho;
  string buffer;

  while (arquivo.read(reinterpret_cast<char *>(&tripulacao.codigo),
                      sizeof(tripulacao.codigo))) {
    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    tripulacao.nome = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    tripulacao.telefone = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    tripulacao.cargo = buffer;

    tripulantes.push_back(tripulacao);
  }

  arquivo.close();
  return tripulantes;
}

void exibirTripulantes() {
  string cargo;

  vector<Tripulacao> tripulantes = lerTripulacao();
  if (tripulantes.empty()) {
    cout << "Nenhum tripulante encontrado." << endl;
    return;
  }

  cout << "Tripulantes cadastrados:" << endl;
  for (const auto &tripulante : tripulantes) {
    if (tripulante.cargo == "1") {
      cargo = "Piloto";
    } else if (tripulante.cargo == "2") {
      cargo = "Co-piloto";
    } else {
      cargo = "Comissario";
    }
    cout << "Código: " << tripulante.codigo << endl;
    cout << "Nome: " << tripulante.nome << endl;
    cout << "Telefone: " << tripulante.telefone << endl;
    cout << "Cargo: " << cargo << endl;
    cout << "------------------------" << endl;
  }
}

void exibirTripulantesPorCargo(const string &cargoDesejado) {
  string cargo;
  if (cargoDesejado == "1") {
    cargo = "Piloto";
  } else if (cargoDesejado == "2") {
    cargo = "Co-piloto";
  } else {
    cargo = "Comissario";
  }
  vector<Tripulacao> tripulantes = lerTripulacao();
  vector<Tripulacao> filtrados;

  for (const auto &tripulante : tripulantes) {
    if (tripulante.cargo == cargoDesejado) {
      filtrados.push_back(tripulante);
    }
  }

  if (filtrados.empty()) {
    cout << "Nenhum " << cargo << " encontrado." << endl;
    return;
  }
  cout << "------------------------" << endl;
  cout << "     Tripulantes com cargo " << cargo << ":" << endl;
  for (const auto &tripulante : filtrados) {
    cout << "     Código: " << tripulante.codigo << endl;
    cout << "     Nome: " << tripulante.nome << endl;
    cout << "     Telefone: " << tripulante.telefone << endl;
    cout << "------------------------" << endl;
  }
}

int gerarCodigoTripulacao() {
  int codigoTripulacao = 1;
  vector<Tripulacao> tripulacao = lerTripulacao();
  for (const auto &t : tripulacao) {
    if (t.codigo >= codigoTripulacao) {
      codigoTripulacao = t.codigo + 1;
    }
  }
  return codigoTripulacao;
}

void cadastrarTripulante() {
  Tripulacao tripulacao;
  tripulacao.codigo = gerarCodigoTripulacao();
  cout << "Nome: ";
  cin.ignore();
  getline(cin, tripulacao.nome);
  cout << "Cargo (1)Piloto (2)Co-piloto (3)Comissario: ";
  getline(cin, tripulacao.cargo);
  cout << "Telefone: ";
  getline(cin, tripulacao.telefone);
  salvarTripulacao(tripulacao);
  cout << "Tripulante castrado com sucesso!" << endl;
}