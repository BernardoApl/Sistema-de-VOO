
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits> 

using namespace std;

struct Voo {
    int codigoVoo;        // Código único do voo
    string dataHora;      // Data e hora do voo
    string origem;        // Origem do voo
    string destino;       // Destino do voo
    int codigoAviao;      // Código do avião
    int codigoPiloto;     // Código do piloto
    int codigoCopiloto;   // Código do copiloto
    int codigoComissario; // Código do comissário
    bool status;          // Status do voo: ativo ou inativo
    double tarifa;        // Tarifa do voo
};

struct Assento {
    int numeroAssento; // Número do assento
    int codigoVoo;     // Código do voo associado
    bool status;       // Status do assento: ocupado (true) ou livre (false)
};

struct Reserva {
    int codigoVoo;        // Código do voo associado
    int numeroAssento;    // Número do assento reservado
    int codigoPassageiro; // Código do passageiro
};

class CompanhiaAerea {
private:
    string arquivoAssentos = "assentos.dat"; // Arquivo para armazenar assentos
    string arquivoReservas = "reservas.dat"; // Arquivo para armazenar reservas

public:
    // Verifica se o assento está disponível
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
                return !assento.status; // Retorna true se o assento estiver livre
            }
        }

        file.close();
        return false; // Assento não encontrado
    }

    // Verifica se já existe uma reserva para o assento no voo
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
                return true; // Já existe uma reserva para este assento no voo
            }
        }

        file.close();
        return false; // Não existe reserva para este assento no voo
    }

    // Atualiza o status do assento no arquivo de assentos para ocupado
    void ocuparAssento(int codigoVoo, int numeroAssento) {
        fstream file(arquivoAssentos, ios::binary | ios::in | ios::out);
        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo de assentos.\n";
            return;
        }

        Assento assento;
        while (file.read(reinterpret_cast<char *>(&assento), sizeof(Assento))) {
            if (assento.codigoVoo == codigoVoo && assento.numeroAssento == numeroAssento) {
                assento.status = true; // Marca o assento como ocupado
                file.seekp(-static_cast<int>(sizeof(Assento)), ios::cur);
                file.write(reinterpret_cast<const char *>(&assento), sizeof(Assento));
                break;
            }
        }

        file.close();
    }

    // Função para adicionar um passageiro à reserva de um voo
    void adicionarReserva(vector<Voo>& voos, int codigoVoo, int numeroAssento, int codigoPassageiro) {
        // Procurar pelo voo desejado
        for (auto& voo : voos) {
            if (voo.codigoVoo == codigoVoo) {
                // Verificar se o assento está disponível
                if (!assentoDisponivel(codigoVoo, numeroAssento)) {
                    cout << "Assento indisponível ou não encontrado.\n";
                    return;
                }

                // Verificar se já existe uma reserva para o assento
                if (reservaDuplicada(codigoVoo, numeroAssento)) {
                    cout << "Reserva duplicada! Este assento já está reservado.\n";
                    return;
                }

                // Cria a reserva
                Reserva novaReserva = {codigoVoo, numeroAssento, codigoPassageiro};

                ofstream file(arquivoReservas, ios::binary | ios::app);
                if (!file.is_open()) {
                    cout << "Erro ao abrir o arquivo de reservas.\n";
                    return;
                }

                file.write(reinterpret_cast<const char*>(&novaReserva), sizeof(Reserva));
                file.close();

                // Atualiza o status do assento
                ocuparAssento(codigoVoo, numeroAssento);

                cout << "Reserva do passageiro " << codigoPassageiro << " realizada com sucesso para o voo " << codigoVoo << " no assento " << numeroAssento << endl;
                return;
            }
        }

        cout << "Voo não encontrado!\n";
    }

    // Função para remover um passageiro da reserva de um voo
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
                // Atualiza o status do assento para livre
                liberarAssento(codigoVoo, numeroAssento);
                // Calcular o valor total a ser pago, se necessário
                for (auto& voo : voos) {
                    if (voo.codigoVoo == codigoVoo) {
                        cout << "Valor a ser pago: R$ " << voo.tarifa << endl;
                    }
                }
                continue; // Remove a reserva
            }
            reservas.push_back(reserva);
        }

        file.close();

        // Reescrever o arquivo sem a reserva removida
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

    // Atualiza o status do assento no arquivo de assentos para livre
    void liberarAssento(int codigoVoo, int numeroAssento) {
        fstream file(arquivoAssentos, ios::binary | ios::in | ios::out);
        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo de assentos.\n";
            return;
        }

        Assento assento;
        while (file.read(reinterpret_cast<char *>(&assento), sizeof(Assento))) {
            if (assento.codigoVoo == codigoVoo && assento.numeroAssento == numeroAssento) {
                assento.status = false; // Marca o assento como livre
                file.seekp(-static_cast<int>(sizeof(Assento)), ios::cur);
                file.write(reinterpret_cast<const char *>(&assento), sizeof(Assento));
                break;
            }
        }

        file.close();
    }

    // Função para garantir que a entrada seja um número válido
    int obterEntradaNumerica() {
        int valor;
        while (true) {
            cin >> valor;
            if(cin.fail()) {
                cin.clear(); // Limpa o estado de erro
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a linha inválida
                cout << "Digite um número válido: ";
            } else {
                return valor;
            }
        }
    }
};

int main() {
    CompanhiaAerea companhia;

    vector<Voo> voos; // Aqui você pode adicionar voos conforme necessário

    int opcao;
    do {
    
        cout << "5. Baixa em Reserva\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        opcao = companhia.obterEntradaNumerica(); // Função que valida a entrada

        switch(opcao) {
            case 5: {
                int opcaoReserva;
                cout << "\nMenu de Reservas:\n";
                cout << "1. Adicionar reserva\n";
                cout << "2. Baixar reserva\n";
                cout << "3. Exibir lista de voos\n";
                cout << "0. Voltar\n";
                cout << "Escolha uma opção: ";
                opcaoReserva = companhia.obterEntradaNumerica(); // Função que valida a entrada

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
