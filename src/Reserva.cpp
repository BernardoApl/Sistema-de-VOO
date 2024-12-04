#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "reserva.h"

using namespace std;

class CompanhiaAerea
{
private:
    string arquivoAssentos = "assentos.dat"; 
    string arquivoReservas = "reservas.dat"; 

public:
    bool assentoDisponivel(int codigoVoo, int numeroAssento)
    {
        ifstream file(arquivoAssentos, ios::binary);
        if (!file.is_open())
        {
            cout << "Erro ao abrir o arquivo de assentos.\n";
            return false;
        }

        Assento assento;
        while (file.read(reinterpret_cast<char *>(&assento), sizeof(Assento)))
        {
            if (assento.codigoVoo == codigoVoo && assento.numeroAssento == numeroAssento)
            {
                file.close();
                return !assento.status; 
            }
        }

        file.close();
        return false; 
    }

    bool reservaDuplicada(int codigoVoo, int numeroAssento)
    {
        ifstream file(arquivoReservas, ios::binary);
        if (!file.is_open())
        {
            cout << "Erro ao abrir o arquivo de reservas.\n";
            return false;
        }

        Reserva reserva;
        while (file.read(reinterpret_cast<char *>(&reserva), sizeof(Reserva)))
        {
            if (reserva.codigoVoo == codigoVoo && reserva.numeroAssento == numeroAssento)
            {
                file.close();
                return true; 
            }
        }

        file.close();
        return false; 
    }

    void ocuparAssento(int codigoVoo, int numeroAssento)
    {
        fstream file(arquivoAssentos, ios::binary | ios::in | ios::out);
        if (!file.is_open())
        {
            cout << "Erro ao abrir o arquivo de assentos.\n";
            return;
        }

        Assento assento;
        while (file.read(reinterpret_cast<char *>(&assento), sizeof(Assento)))
        {
            if (assento.codigoVoo == codigoVoo && assento.numeroAssento == numeroAssento)
            {
                assento.status = true; 
                file.seekp(-static_cast<int>(sizeof(Assento)), ios::cur);
                file.write(reinterpret_cast<const char *>(&assento), sizeof(Assento));
                break;
            }
        }

        file.close();
    }

    void cadastrarReserva()
    {
        int codigoVoo, numeroAssento, codigoPassageiro;

        cout << "Digite o codigo do voo: ";
        cin >> codigoVoo;

        cout << "Digite o numero do assento: ";
        cin >> numeroAssento;

        cout << "Digite o codigo do passageiro: ";
        cin >> codigoPassageiro;

        if (!assentoDisponivel(codigoVoo, numeroAssento))
        {
            cout << "Assento indisponivel ou nao encontrado.\n";
            return;
        }

        if (reservaDuplicada(codigoVoo, numeroAssento))
        {
            cout << "Reserva duplicada! Este assento ja esta reservado.\n";
            return;
        }

        Reserva novaReserva = {codigoVoo, numeroAssento, codigoPassageiro};

        ofstream file(arquivoReservas, ios::binary | ios::app);
        if (!file.is_open())
        {
            cout << "Erro ao abrir o arquivo de reservas.\n";
            return;
        }

        file.write(reinterpret_cast<const char *>(&novaReserva), sizeof(Reserva));
        file.close();

        ocuparAssento(codigoVoo, numeroAssento);

        cout << "Reserva cadastrada com sucesso!\n";
    }
};

int main()
{
    CompanhiaAerea companhia;

    int opcao;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Cadastrar reserva\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            companhia.cadastrarReserva();
            break;
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opcao invalida!\n";
        }
    } while (opcao != 0);

    return 0;
}
