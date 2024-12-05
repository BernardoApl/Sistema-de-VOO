#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "cadastroassento.h"

using namespace std;

class CompanhiaAerea
{
private:
    string arquivoVoos = "voos.dat";         
    string arquivoAssentos = "assentos.dat"; 

public:
    bool vooExiste(int codigo)
    {
        ifstream file(arquivoVoos, ios::binary);
        if (!file.is_open())
        { 
            cout << "Erro ao abrir o arquivo de voos.\n";
            return false;
        }

        Voo voo; 
        while (file.read(reinterpret_cast<char *>(&voo), sizeof(Voo)))
        {
            if (voo.codigoVoo == codigo)
            {
                file.close(); 
                return true;  /
            }
        }

        file.close(); 
        return false; 
    }

    void cadastrarAssentos()
    {
        int codigoVoo;
        cout << "Digite o codigo do voo: ";
        cin >> codigoVoo;

        if (!vooExiste(codigoVoo))
        { 
            cout << "Voo nao encontrado ou nao esta ativo.\n";
            return;
        }

        int quantidadeAssentos;
        cout << "Digite a quantidade de assentos para o voo " << codigoVoo << ": ";
        cin >> quantidadeAssentos;

        vector<Assento> assentos;
        for (int i = 1; i <= quantidadeAssentos; ++i)
        {
            assentos.push_back({i, codigoVoo, false}); 
        }

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
