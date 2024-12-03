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

class CompanhiaAerea
{
private:
    string arquivoVoos = "voos.dat";         // Arquivo para armazenar voos
    string arquivoAssentos = "assentos.dat"; // Arquivo para armazenar assentos

public:
    // Verifica se um voo existe e está ativo no arquivo de voos
    bool vooExiste(int codigo)
    {
        ifstream file(arquivoVoos, ios::binary); // Abre o arquivo de voos em modo binário
        if (!file.is_open())
        { // Verifica se o arquivo foi aberto com sucesso
            cout << "Erro ao abrir o arquivo de voos.\n";
            return false; // Retorna falso caso não consiga abrir
        }

        Voo voo; // Declara um objeto Voo para leitura
        while (file.read(reinterpret_cast<char *>(&voo), sizeof(Voo)))
        {
            // Lê os dados de um voo do arquivo
            if (voo.codigoVoo == codigo && voo.status)
            {
                // Verifica se o código do voo coincide e se ele está ativo
                file.close(); // Fecha o arquivo antes de retornar
                return true;  // Retorna verdadeiro se o voo existe e está ativo
            }
        }

        file.close(); // Fecha o arquivo após a leitura
        return false; // Retorna falso se o voo não foi encontrado ou está inativo
    }

    // Cadastra os assentos de um voo
    void cadastrarAssentos()
    {
        int codigoVoo;
        cout << "Digite o codigo do voo: ";
        cin >> codigoVoo;

        if (!vooExiste(codigoVoo))
        { // Verifica se o voo existe e está ativo
            cout << "Voo nao encontrado ou nao esta ativo.\n";
            return;
        }

        int quantidadeAssentos;
        cout << "Digite a quantidade de assentos para o voo " << codigoVoo << ": ";
        cin >> quantidadeAssentos;

        vector<Assento> assentos;
        for (int i = 1; i <= quantidadeAssentos; ++i)
        {
            assentos.push_back({i, codigoVoo, false}); // Cria assentos com status livre
        }

        // Salva os assentos no arquivo binário
        ofstream file(arquivoAssentos, ios::binary | ios::app);
        if (!file.is_open())
        {
            cout << "Erro ao abrir o arquivo de assentos.\n";
            return;
        }

        for (const auto &assento : assentos)
        {
            file.write(reinterpret_cast<const char *>(&assento), sizeof(Assento));
        }

        file.close();
        cout << "Assentos cadastrados com sucesso para o voo " << codigoVoo << ".\n";
    }
};

int main()
{
    CompanhiaAerea companhia;

    int opcao;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Cadastrar assentos para um voo\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            companhia.cadastrarAssentos();
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
