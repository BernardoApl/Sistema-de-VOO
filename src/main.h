#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>


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

struct Assento {
    int numeroAssento;
    int codigoVoo;
    bool status;
};

struct Reserva {
    int codigoVoo;
    int numeroAssento;
    int codigoPassageiro;
};

struct Reserva
{
    int codigoVoo;        
    int numeroAssento;    
    int codigoPassageiro; 
};

class CompanhiaAerea {
private:
    string arquivoAssentos = "assentos.dat";
    string arquivoReservas = "reservas.dat";

    void ocuparAssento(int codigoVoo, int numeroAssento);
    void liberarAssento(int codigoVoo, int numeroAssento);

public:
    bool assentoDisponivel(int codigoVoo, int numeroAssento);

    bool reservaDuplicada(int codigoVoo, int numeroAssento);

    void adicionarReserva(vector<Voo>& voos, int codigoVoo, int numeroAssento, int codigoPassageiro);

    void baixarReserva(vector<Voo>& voos, int codigoVoo, int numeroAssento, int codigoPassageiro);

    int obterEntradaNumerica();
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

void salvarTripulacao(const Tripulacao &tripulacao);
vector<Tripulacao> lerTripulacao();
void exibirTripulantes();
void exibirTripulantesPorCargo(const string &cargoDesejado);
int gerarCodigoTripulacao();
void cadastrarTripulante();

void salvarVoo(const Voos &voo);
vector<Voos> lerVoos();
void exibirVoos();
int gerarCodigoVoo();
void cadastrarVoo();

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

void pedir_quantidade_voos(Passageiro& passageiro);

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
