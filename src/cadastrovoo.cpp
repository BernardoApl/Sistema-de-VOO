#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "cadastrovoo.h"

using namespace std;

void salvarVoo(const Voos &voo) {
  ofstream arquivo("voos.dat", ios::binary | ios::app);
  if (!arquivo) {
    cerr << "Erro ao abrir o arquivo para escrita!" << endl;
    return;
  }
  size_t tamanho;

  arquivo.write(reinterpret_cast<const char *>(&voo.codigo),
                sizeof(voo.codigo));

  tamanho = voo.data.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.data.data(), tamanho);

  tamanho = voo.hora.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.hora.data(), tamanho);

  tamanho = voo.origem.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.origem.data(), tamanho);

  tamanho = voo.destino.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.destino.data(), tamanho);

  tamanho = voo.codigoAviao.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.codigoAviao.data(), tamanho);

  tamanho = voo.codigoPiloto.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.codigoPiloto.data(), tamanho);

  tamanho = voo.codigoCopiloto.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.codigoCopiloto.data(), tamanho);

  tamanho = voo.codigoComissario.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.codigoComissario.data(), tamanho);

  arquivo.write(reinterpret_cast<const char *>(&voo.tarifa),
                sizeof(voo.tarifa));

  arquivo.close();
}

vector<Voos> lerVoos() {
  vector<Voos> voos;
  ifstream arquivo("voos.dat", ios::binary);
  if (!arquivo) {
    cerr << "Erro ao abrir o arquivo para leitura!" << endl;
    return voos;
  }

  Voos voo;
  size_t tamanho;
  string buffer;

  while (
      arquivo.read(reinterpret_cast<char *>(&voo.codigo), sizeof(voo.codigo))) {
    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.data = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.hora = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.origem = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.destino = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.codigoAviao = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.codigoPiloto = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.codigoCopiloto = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.codigoComissario = buffer;

    arquivo.read(reinterpret_cast<char *>(&voo.tarifa), sizeof(voo.tarifa));

    voos.push_back(voo);
  }

  arquivo.close();
  return voos;
}


void exibirVoos() {
  vector<Voos> voos = lerVoos();
  if (voos.empty()) {
    cout << "Nenhum voo encontrado." << endl;
    return;
  }

  cout << "Voos cadastrados:" << endl;
  for (const auto &voo : voos) {
    cout << "Código: " << voo.codigo << endl;
    cout << "Data: " << voo.data << endl;
    cout << "Hora: " << voo.hora << endl;
    cout << "Origem: " << voo.origem << endl;
    cout << "Destino: " << voo.destino << endl;
    cout << "Código do Avião: " << voo.codigoAviao << endl;
    cout << "Código do Piloto: " << voo.codigoPiloto << endl;
    cout << "Código do Copiloto: " << voo.codigoCopiloto << endl;
    cout << "Código do Comissário: " << voo.codigoComissario << endl;
    cout << "Tarifa: " << voo.tarifa << endl;
    cout << "------------------------" << endl;
  }
}

int gerarCodigoVoo() {
  int codigoVoo = 1;
  vector<Voos> voo = lerVoos();
  for (const auto &v : voo) {
    if (v.codigo >= codigoVoo) {
      codigoVoo = v.codigo + 1;
    }
  }
  return codigoVoo;
}

void cadastrarVoo() {
  Voos voo;
  cout << "Digite os dados do voo:" << endl;
  voo.codigo = gerarCodigoVoo();
  cin.ignore();
  cout << "Data (dd/mm/yyyy): ";
  getline(cin, voo.data);
  cout << "Hora (hh:mm): ";
  getline(cin, voo.hora);
  cout << "Origem: ";
  getline(cin, voo.origem);
  cout << "Destino: ";
  getline(cin, voo.destino);
  cout << "Código do Avião: ";
  getline(cin, voo.codigoAviao);
  exibirTripulantesPorCargo("1");
  cout << "Código do Piloto: ";
  getline(cin, voo.codigoPiloto);
  exibirTripulantesPorCargo("2");
  cout << "Código do Copiloto: ";
  getline(cin, voo.codigoCopiloto);
  exibirTripulantesPorCargo("3");
  cout << "Código do Comissário: ";
  getline(cin, voo.codigoComissario);
  cout << "Tarifa: ";
  cin >> voo.tarifa;

  salvarVoo(voo);
  cout << "Voo cadastrado com sucesso!" << endl;
}
