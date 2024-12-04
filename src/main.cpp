#include "cadastrotripulacao.h"
#include "cadastrovoo.h"
#include "baixareserva.h"
#include "cadastropassageiro.h"
#include "reserva.h"
#include "pesquisa.h"
#include "cadastroassento.h"


using namespace std;

int main() {
        GerenciadorVoos gerenciador;
        gerenciador.ler_dados_arquivos();
    
        int opcao1;
       
        do {
            cout << "\n=== Sistema de Gestão de Voos ===\n";
            cout << "1. Cadastrar Passageiro\n";
            cout << "2. Cadastrar Tripulante\n";
            cout << "3. Cadastrar Voo\n";
            cout << "4. Listar Voos\n";
            cout << "5. Reserva\n"; 
            cout << "6. Baixa em Reserva\n";  
            cout << "7. Pesquisa\n";
            cout << "8. Programa de Fidelidade\n";
            cout << "0. Sair\n";
            cout << "Escolha uma opção: ";
            ler_inteiro(opcao1); 
    
            switch (opcao1) {
                case 1: {
                    CadastroPassageiro cadastro;
                    Passageiro passageiro;
                    bool sucesso = false;
                    do {
                        cout << "Digite o Nº código do passageiro: ";
                        ler_inteiro(passageiro.codigo); 
    
                        bool codigoExistente = false;
                        for (const auto& p : gerenciador.get_passageiros()) {
                            if (p.codigo == passageiro.codigo) {
                                cout << "Erro: Já existe um passageiro com esse código!\n";
                                codigoExistente = true;
                                break;
                            }
                        }
    
                        if (codigoExistente) {
                            cout << "Digite um número maior que 1 para continuar ou Digite 0 para voltar ao menu principal.\n";
                            ler_inteiro(passageiro.codigo);
                            if (passageiro.codigo == 0) break;
                            continue;
                        }
    
                        cout << "Digite o nome do passageiro: ";
                        cin.ignore();
                        cin.getline(passageiro.nome, sizeof(passageiro.nome));
                        cout << "Digite o endereço do passageiro: ";
                        cin.getline(passageiro.endereco, sizeof(passageiro.endereco));
                        cout << "Digite o Nº de telefone do passageiro:\n(31) ";
                        ler_inteiro(passageiro.telefone);  
                        pedir_quantidade_voos(passageiro);
    
                        sucesso = cadastro.cadastrar("passageiros.bin", passageiro);
                        if (sucesso) {
                            cout << "Passageiro cadastrado com sucesso!\n";
                            gerenciador.ler_dados_arquivos();
                        } else {
                            cout << "Esse código já está em uso, utilize outro código.\n";
                        }
                    } while (!sucesso);
                    break;
                }
    
                case 2: {
                    cadastrarTripulante();
                    break;
                }
    
                case 3: {
                    gerenciador.cadastrar_voo();
                    break;
                }
    
                case 4: {
                    gerenciador.listar_voos();
                    break;
                }
    
                case 5: {
                    gerenciador.cadastrarReserva();  
                    break;
                }
    
                case 6: {
                    gerenciador.baixar_reserva(); 
                    break;
                }
    
                case 7: {
                    int opcao, codigo;
                    do {
                        cout << "\n=== Sistema de Pesquisa ===\n";
                        cout << "1. Buscar Passageiro\n";
                        cout << "2. Buscar Tripulante\n";
                        cout << "0. Voltar\n";
                        cout << "Escolha uma opção: ";
                        ler_inteiro(opcao); 
    
                        switch (opcao) {
                            case 1:
                                cout << "Digite o código do passageiro: ";
                                ler_inteiro(codigo);
                                gerenciador.buscar_passageiro(codigo);
                                break;
    
                            case 2:
                                cout << "Digite o código do tripulante: ";
                                ler_inteiro(codigo);
                                gerenciador.buscar_tripulante(codigo);
                                break;
    
                            case 0:
                                cout << "Voltando ao menu principal...\n";
                                break;
    
                            default:
                                cout << "Opção inválida! Tente novamente.\n";
                        }
                    } while (opcao != 0);
                    break;
                }
    
                case 8: {
                    int codigo;
                    cout << "\n=== Programa de Fidelidade ===\n";
                    cout << "Digite o código do passageiro: ";
                    ler_inteiro(codigo);
                    gerenciador.atualizar_pontos_fidelidade(codigo);
                    break;
                }
    
                case 0:
                    cout << "Saindo do sistema...\n";
                    break;
    
                default:
                    cout << "Opção inválida! Tente novamente.\n";
            }
        } while (opcao1 != 0);
    
        return 0;
    }