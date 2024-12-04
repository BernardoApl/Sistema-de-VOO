#ifndef CADASTROVOO_H
#define CADASTROVOO_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Voos {
  int codigo;
  string data; // dd/mm/yyyy
  string hora; // hh:mm
  string origem;
  string destino;
  string codigoAviao;
  string codigoPiloto;
  string codigoCopiloto;
  string codigoComissario;
  double tarifa;
};

void salvarVoo(const Voos &voo);
vector<Voos> lerVoos();
void exibirVoos();
int gerarCodigoVoo();
void cadastrarVoo();

#endif