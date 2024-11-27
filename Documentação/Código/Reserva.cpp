#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Voo
{
    int codigoVoo;        // Código único do voo
    string dataHora;      // Data e hora do voo no formato string
    string origem;        // Origem do voo
    string destino;       // Destino do voo
    int codigoAviao;      // Código do avião
    int codigoPiloto;     // Código do piloto responsável
    int codigoCopiloto;   // Código do copiloto responsável
    int codigoComissario; // Código do comissário responsável
    bool status;          // Status do voo: true (ativo) ou false (inativo)
    double tarifa;        // Tarifa do voo
};

struct Assento
{
    int numeroAssento; // Número do assento
    int codigoVoo;     // Código do voo associado
    bool status;       // Status do assento: true (ocupado) ou false (livre)
};

struct Reserva
{
    int codigoVoo;        // Código do voo associado
    int numeroAssento;    // Número do assento reservado
    int codigoPassageiro; // Código do passageiro que fez a reserva
};

class CompanhiaAerea
{
private:
    string arquivoAssentos = "assentos.dat"; // Arquivo para armazenar assentos
    string arquivoReservas = "reservas.dat"; // Arquivo para armazenar reservas

public:
    // Verifica se o assento está disponível
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
                return !assento.status; // Retorna true se o assento estiver livre
            }
        }

        file.close();
        return false; // Assento não encontrado
    }

    // Verifica se já existe uma reserva para o assento no voo
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
                return true; // Já existe uma reserva para este assento no voo
            }
        }

        file.close();
        return false; // Não existe reserva para este assento no voo
    }

    // Atualiza o status do assento no arquivo de assentos para ocupado
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
                assento.status = true; // Marca o assento como ocupado
                file.seekp(-static_cast<int>(sizeof(Assento)), ios::cur);
                file.write(reinterpret_cast<const char *>(&assento), sizeof(Assento));
                break;
            }
        }

        file.close();
    }

    // Cadastra uma nova reserva
    void cadastrarReserva()
    {
        int codigoVoo, numeroAssento, codigoPassageiro;

        cout << "Digite o codigo do voo: ";
        cin >> codigoVoo;

        cout << "Digite o numero do assento: ";
        cin >> numeroAssento;

        cout << "Digite o codigo do passageiro: ";
        cin >> codigoPassageiro;

        // Verifica se o assento está disponível
        if (!assentoDisponivel(codigoVoo, numeroAssento))
        {
            cout << "Assento indisponivel ou nao encontrado.\n";
            return;
        }

        // Verifica se a reserva já existe
        if (reservaDuplicada(codigoVoo, numeroAssento))
        {
            cout << "Reserva duplicada! Este assento ja esta reservado.\n";
            return;
        }

        // Cria a reserva
        Reserva novaReserva = {codigoVoo, numeroAssento, codigoPassageiro};

        ofstream file(arquivoReservas, ios::binary | ios::app);
        if (!file.is_open())
        {
            cout << "Erro ao abrir o arquivo de reservas.\n";
            return;
        }

        file.write(reinterpret_cast<const char *>(&novaReserva), sizeof(Reserva));
        file.close();

        // Atualiza o status do assento
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
