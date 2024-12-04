#ifndef RESERVA_H
#define RESERVA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Voo {
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


struct Assento
{
    int numeroAssento; 
    int codigoVoo;    
    bool status; 
};

struct Reserva
{
    int codigoVoo;        
    int numeroAssento;    
    int codigoPassageiro; 
};

class CompanhiaAerea
{
private:
    string arquivoAssentos = "assentos.dat"; 
    string arquivoReservas = "reservas.dat"; 

public:
    bool assentoDisponivel(int codigoVoo, int numeroAssento);

    bool reservaDuplicada(int codigoVoo, int numeroAssento);

    void ocuparAssento(int codigoVoo, int numeroAssento);

    void cadastrarReserva();
};

#endif
