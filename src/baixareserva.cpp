
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits> 
#include "baixareserva.h"

using namespace std;

class CompanhiaAerea {
private:
    string arquivoAssentos = "assentos.dat"; 
    string arquivoReservas = "reservas.dat"; 

public:
    bool assentoDisponivel(int codigoVoo, int numeroAssento) {
        ifstream file(arquivoAssentos, ios::binary);
        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo de assentos.\n";
            return false;
        }

        Assento assento;
        while (file.read(reinterpret_cast<char *>(&assento), sizeof(Assento))) {
            if (assento.codigoVoo == codigoVoo && assento.numeroAssento == numeroAssento) {
                file.close();
                return !assento.status; 
            }
        }

        file.close();
        return false; 
    }

    bool reservaDuplicada(int codigoVoo, int numeroAssento) {
        ifstream file(arquivoReservas, ios::binary);
        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo de reservas.\n";
            return false;
        }

        Reserva reserva;
        while (file.read(reinterpret_cast<char *>(&reserva), sizeof(Reserva))) {
            if (reserva.codigoVoo == codigoVoo && reserva.numeroAssento == numeroAssento) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    void ocuparAssento(int codigoVoo, int numeroAssento) {
        fstream file(arquivoAssentos, ios::binary | ios::in | ios::out);
        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo de assentos.\n";
            return;
        }

        Assento assento;
        while (file.read(reinterpret_cast<char *>(&assento), sizeof(Assento))) {
            if (assento.codigoVoo == codigoVoo && assento.numeroAssento == numeroAssento) {
                assento.status = true; 
                file.seekp(-static_cast<int>(sizeof(Assento)), ios::cur);
                file.write(reinterpret_cast<const char *>(&assento), sizeof(Assento));
                break;
            }
        }

        file.close();
    }

    void adicionarReserva(vector<Voo>& voos, int codigoVoo, int numeroAssento, int codigoPassageiro) {
        for (auto& voo : voos) {
            if (voo.codigoVoo == codigoVoo) {
                if (!assentoDisponivel(codigoVoo, numeroAssento)) {
                    cout << "Assento indisponível ou não encontrado.\n";
                    return;
                }

                if (reservaDuplicada(codigoVoo, numeroAssento)) {
                    cout << "Reserva duplicada! Este assento já está reservado.\n";
                    return;
                }

                Reserva novaReserva = {codigoVoo, numeroAssento, codigoPassageiro};

                ofstream file(arquivoReservas, ios::binary | ios::app);
                if (!file.is_open()) {
                    cout << "Erro ao abrir o arquivo de reservas.\n";
                    return;
                }

                file.write(reinterpret_cast<const char*>(&novaReserva), sizeof(Reserva));
                file.close();

                ocuparAssento(codigoVoo, numeroAssento);

                cout << "Reserva do passageiro " << codigoPassageiro << " realizada com sucesso para o voo " << codigoVoo << " no assento " << numeroAssento << endl;
                return;
            }
        }

        cout << "Voo não encontrado!\n";
    }

    void baixarReserva(vector<Voo>& voos, int codigoVoo, int numeroAssento, int codigoPassageiro) {
        ifstream file(arquivoReservas, ios::binary);
        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo de reservas.\n";
            return;
        }

        Reserva reserva;
        vector<Reserva> reservas;
        while (file.read(reinterpret_cast<char*>(&reserva), sizeof(Reserva))) {
            if (reserva.codigoVoo == codigoVoo && reserva.numeroAssento == numeroAssento && reserva.codigoPassageiro == codigoPassageiro) {
                cout << "Reserva removida com sucesso!\n";
                liberarAssento(codigoVoo, numeroAssento);
                for (auto& voo : voos) {
                    if (voo.codigoVoo == codigoVoo) {
                        cout << "Valor a ser pago: R$ " << voo.tarifa << endl;
                    }
                }
                continue;
            }
            reservas.push_back(reserva);
        }

        file.close();

        ofstream outFile(arquivoReservas, ios::binary);
        if (!outFile.is_open()) {
            cout << "Erro ao abrir o arquivo de reservas para escrita.\n";
            return;
        }

        for (const auto& r : reservas) {
            outFile.write(reinterpret_cast<const char*>(&r), sizeof(Reserva));
        }

        outFile.close();
    }

    void liberarAssento(int codigoVoo, int numeroAssento) {
        fstream file(arquivoAssentos, ios::binary | ios::in | ios::out);
        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo de assentos.\n";
            return;
        }

        Assento assento;
        while (file.read(reinterpret_cast<char *>(&assento), sizeof(Assento))) {
            if (assento.codigoVoo == codigoVoo && assento.numeroAssento == numeroAssento) {
                assento.status = false; 
                file.seekp(-static_cast<int>(sizeof(Assento)), ios::cur);
                file.write(reinterpret_cast<const char *>(&assento), sizeof(Assento));
                break;
            }
        }

        file.close();
    }

    int obterEntradaNumerica() {
        int valor;
        while (true) {
            cin >> valor;
            if(cin.fail()) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); /
                cout << "Digite um número válido: ";
            } else {
                return valor;
            }
        }
    }
};

int main() {
    CompanhiaAerea companhia;

    vector<Voo> voos;

    int opcao;
    do {
    
        cout << "5. Baixa em Reserva\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        opcao = companhia.obterEntradaNumerica();

        switch(opcao) {
            case 5: {
                int opcaoReserva;
                cout << "\nMenu de Reservas:\n";
                cout << "1. Adicionar reserva\n";
                cout << "2. Baixar reserva\n";
                cout << "3. Exibir lista de voos\n";
                cout << "0. Voltar\n";
                cout << "Escolha uma opção: ";
                opcaoReserva = companhia.obterEntradaNumerica();

                switch(opcaoReserva) {
                    case 1: {
                        int codigoVoo, numeroAssento, codigoPassageiro;
                        cout << "Digite o código do voo: ";
                        cin >> codigoVoo;
                        cout << "Digite o número do assento: ";
                        cin >> numeroAssento;
                        cout << "Digite o código do passageiro: ";
                        cin >> codigoPassageiro;

                        companhia.adicionarReserva(voos, codigoVoo, numeroAssento, codigoPassageiro);
                        break;
                    }
                    case 2: {
                        int codigoVoo, numeroAssento, codigoPassageiro;
                        cout << "Digite o código do voo: ";
                        cin >> codigoVoo;
                        cout << "Digite o número do assento: ";
                        cin >> numeroAssento;
                        cout << "Digite o código do passageiro: ";
                        cin >> codigoPassageiro;

                        companhia.baixarReserva(voos, codigoVoo, numeroAssento, codigoPassageiro);
                        break;
                    }
                    case 3: {
                        cout << "\nLista de voos:\n";
                        for (const auto& voo : voos) {
                            cout << "Voo " << voo.codigoVoo << " - " << voo.origem << " -> " << voo.destino << " - Tarifa: R$ " << voo.tarifa << endl;
                        }
                        break;
                    }
                    case 0:
                        cout << "Voltando...\n";
                        break;
                    default:
                        cout << "Opção inválida! Tente novamente.\n";
                }
                break;
            }
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 2);

    return 0;
}
