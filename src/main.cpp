    #include <iostream>
    #include <fstream> 
    #include <vector>   
    #include <string>   
    #include <algorithm> 
    #include <limits>
    
    using namespace std;
    
    struct Passageiro {
        int codigo;
        char nome[100];        
        char endereco[200];
        int telefone;
        int quantidade_voos;    
        int pontos_fidelidade; 
    };
    
    struct Voo {
        int numero;            
        char data[20];         
        char origem[50];       
        char destino[50];      
        vector<int> passageiros; 
        vector<int> tripulantes; 
    };
    
    struct Tripulacao {
        int codigo;
        string nome;
        string telefone;
        string cargo; // 1 - piloto, 2 - co-piloto, 3 - comissário
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
    
    
    void salvarTripulacao(const Tripulacao &tripulacao) {
      ofstream arquivo("tripulacao.dat", ios::binary | ios::app);
      if (!arquivo) {
        cerr << "Erro ao abrir o arquivo para escrita!" << endl;
        return;
      }
      size_t tamanho;
    
      arquivo.write(reinterpret_cast<const char *>(&tripulacao.codigo),
                    sizeof(tripulacao.codigo));
    
      tamanho = tripulacao.nome.size();
      arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
      arquivo.write(tripulacao.nome.data(), tamanho);
    
      tamanho = tripulacao.telefone.size();
      arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
      arquivo.write(tripulacao.telefone.data(), tamanho);
    
      tamanho = tripulacao.cargo.size();
      arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
      arquivo.write(tripulacao.cargo.data(), tamanho);
    
      arquivo.close();
    }
    
    vector<Tripulacao> lerTripulacao() {
      vector<Tripulacao> tripulantes;
      ifstream arquivo("tripulacao.dat", ios::binary);
      if (!arquivo) {
        cerr << "Erro ao abrir o arquivo para leitura!" << endl;
        return tripulantes;
      }
    
      Tripulacao tripulacao;
      size_t tamanho;
      string buffer;
    
      while (arquivo.read(reinterpret_cast<char *>(&tripulacao.codigo),
                          sizeof(tripulacao.codigo))) {
        arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
        buffer.resize(tamanho);
        arquivo.read(&buffer[0], tamanho);
        tripulacao.nome = buffer;
    
        arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
        buffer.resize(tamanho);
        arquivo.read(&buffer[0], tamanho);
        tripulacao.telefone = buffer;
    
        arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
        buffer.resize(tamanho);
        arquivo.read(&buffer[0], tamanho);
        tripulacao.cargo = buffer;
    
        tripulantes.push_back(tripulacao);
      }
    
      arquivo.close();
      return tripulantes;
    }
    
    
    
    
    void exibirTripulantesPorCargo(const string &cargoDesejado) {
      string cargo;
      if (cargoDesejado == "1") {
        cargo = "Piloto";
      } else if (cargoDesejado == "2") {
        cargo = "Co-piloto";
      } else {
        cargo = "Comissario";
      }
      vector<Tripulacao> tripulantes = lerTripulacao();
      vector<Tripulacao> filtrados;
    
      for (const auto &tripulante : tripulantes) {
        if (tripulante.cargo == cargoDesejado) {
          filtrados.push_back(tripulante);
        }
      }
    
      if (filtrados.empty()) {
        cout << "Nenhum " << cargo << " encontrado." << endl;
        return;
      }
      cout << "------------------------" << endl;
      cout << "     Tripulantes com cargo " << cargo << ":" << endl;
      for (const auto &tripulante : filtrados) {
        cout << "     Código: " << tripulante.codigo << endl;
        cout << "     Nome: " << tripulante.nome << endl;
        cout << "     Telefone: " << tripulante.telefone << endl;
        cout << "------------------------" << endl;
      }
    }
    
    int gerarCodigoTripulacao() {
      int codigoTripulacao = 1;
      vector<Tripulacao> tripulacao = lerTripulacao();
      for (const auto &t : tripulacao) {
        if (t.codigo >= codigoTripulacao) {
          codigoTripulacao = t.codigo + 1;
        }
      }
      return codigoTripulacao;
    }
    
    void cadastrarTripulante() {
      Tripulacao tripulacao;
      tripulacao.codigo = gerarCodigoTripulacao();
      cout << "Nome: ";
      cin.ignore();
      getline(cin, tripulacao.nome);
      cout << "Cargo (1)Piloto (2)Co-piloto (3)Comissario: ";
      getline(cin, tripulacao.cargo);
      cout << "Telefone: ";
      getline(cin, tripulacao.telefone);
      salvarTripulacao(tripulacao);
      cout << "Tripulante castrado com sucesso!" << endl;
    }
    
    template <typename T>
    bool ler_inteiro(T& num) {
        while (!(cin >> num)) {
            cout << "Entrada inválida. Digite somente numeros." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        return true;
    }
    
    class GerenciadorVoos {
    public:
        void ler_dados_arquivos();
        void buscar_passageiro(int codigo);
        void listar_voos_passageiro(int codigo_passageiro);
        void buscar_tripulante(int codigo);
        void cadastrar_voo(); 
        void listar_voos(); 
        void baixar_reserva(); 
        void cadastrarReserva(); 
        const vector<Passageiro>& get_passageiros() const; 
        void atualizar_pontos_fidelidade(int codigo_passageiro);
    
    private:
        vector<Passageiro> passageiros;
        vector<Voo> voos;
    };
    
    void GerenciadorVoos::cadastrar_voo() {
        Voo novo_voo;
        cout << "Digite o número do voo: ";
        ler_inteiro(novo_voo.numero);
    
        cout << "Digite a data do voo (DD/MM/AAAA): ";
        cin.ignore();
        cin.getline(novo_voo.data, sizeof(novo_voo.data));
    
        cout << "Digite a origem do voo: ";
        cin.getline(novo_voo.origem, sizeof(novo_voo.origem));
    
        cout << "Digite o destino do voo: ";
        cin.getline(novo_voo.destino, sizeof(novo_voo.destino));
    
        voos.push_back(novo_voo);
    

        ofstream arquivo_voos("voos.bin", ios::binary | ios::app);
        if (arquivo_voos.is_open()) {
            arquivo_voos.write(reinterpret_cast<const char*>(&novo_voo), sizeof(Voo));
            arquivo_voos.close();
            cout << "Voo cadastrado com sucesso!" << endl;
        } else {
            cerr << "Erro ao salvar o voo no arquivo." << endl;
        }
    }
    void GerenciadorVoos::cadastrarReserva() {
        int codigoVoo, codigoPassageiro, numeroAssento;
    
        cout << "Digite o código do voo: ";
        ler_inteiro(codigoVoo);
    
        cout << "Digite o código do passageiro: ";
        ler_inteiro(codigoPassageiro);
    
        cout << "Digite o número do assento: ";
        ler_inteiro(numeroAssento);
    

        Reserva novaReserva;
        novaReserva.codigoVoo = codigoVoo;
        novaReserva.codigoPassageiro = codigoPassageiro;
        novaReserva.numeroAssento = numeroAssento;
    
        for (auto& voo : voos) {
            if (voo.numero == codigoVoo) {
                voo.passageiros.push_back(codigoPassageiro);  
                break;
            }
        }
    
        ofstream arquivo_reservas("reservas.bin", ios::binary | ios::app);
        if (arquivo_reservas.is_open()) {
            arquivo_reservas.write(reinterpret_cast<const char*>(&novaReserva), sizeof(Reserva));
            arquivo_reservas.close();
            cout << "Reserva cadastrada com sucesso!" << endl;
        } else {
            cerr << "Erro ao salvar a reserva no arquivo." << endl;
        }
    }
    
    void GerenciadorVoos::listar_voos() {
        if (voos.empty()) {
            cout << "Nenhum voo cadastrado." << endl;
            return;
        }
    
        for (const Voo& voo : voos) {
            cout << "--------------------------------" << endl;
            cout << "Número do Voo: " << voo.numero << endl;
            cout << "Data: " << voo.data << endl;
            cout << "Origem: " << voo.origem << endl;
            cout << "Destino: " << voo.destino << endl;
            cout << "--------------------------------" << endl;
        }
    }
    
    
    
    
    void GerenciadorVoos::buscar_tripulante(int codigo) {
        vector<Tripulacao> tripulantes = lerTripulacao(); 
    
        for (const Tripulacao& tripulante : tripulantes) {
            if (tripulante.codigo == codigo) {
                string cargo;
                if (tripulante.cargo == "1") {
                    cargo = "Piloto";
                } else if (tripulante.cargo == "2") {
                    cargo = "Co-piloto";
                } else {
                    cargo = "Comissário";
                }
    
                cout << "Tripulante encontrado: " << endl;
                cout << "Código: " << tripulante.codigo << endl;
                cout << "Nome: " << tripulante.nome << endl;
                cout << "Telefone: " << tripulante.telefone << endl;
                cout << "Cargo: " << cargo << endl;
                return;
            }
        }
    
        cout << "Código de tripulante não encontrado." << endl;
    }
    class CadastroPassageiro {
    public:
        bool cadastrar(const string& arquivo, const Passageiro& passageiro) {
            if (passageiro.codigo <= 0 || passageiro.nome[0] == '\0' || passageiro.endereco[0] == '\0' || passageiro.telefone <= 0) {
                cerr << "Dados inválidos." << endl;
                return false;
            }
    
            ofstream outfile(arquivo, ios::binary | ios::app);
            if (!outfile.is_open()) {
                cerr << "Erro ao abrir o arquivo " << arquivo << endl;
                return false;
            }
    
            outfile.write(reinterpret_cast<const char*>(&passageiro), sizeof(Passageiro));
            outfile.close();
            return true;
        }
    };
    
    
    void GerenciadorVoos::ler_dados_arquivos() {
        passageiros.clear();
        voos.clear();
    
        ifstream arquivo_passageiros("passageiros.bin", ios::binary);
        if (arquivo_passageiros.is_open()) {
            Passageiro passageiro;
            while (arquivo_passageiros.read(reinterpret_cast<char*>(&passageiro), sizeof(Passageiro))) {
                passageiros.push_back(passageiro);
            }
            arquivo_passageiros.close();
        }
    
        ifstream arquivo_voos("voos.bin", ios::binary);
        if (arquivo_voos.is_open()) {
            Voo voo;
            while (arquivo_voos.read(reinterpret_cast<char*>(&voo), sizeof(Voo))) {
                voos.push_back(voo);
            }
            arquivo_voos.close();
        }
    }
    
    
    void GerenciadorVoos::buscar_passageiro(int codigo) {
        for (const Passageiro& passageiro : passageiros) {
            if (passageiro.codigo == codigo) {
                cout << "Passageiro encontrado: " << endl;
                cout << "Nome: " << passageiro.nome << endl;
                cout << "Endereço: " << passageiro.endereco << endl;
                cout << "Telefone: " << passageiro.telefone << endl;
                cout << "Quantidade de voos: " << passageiro.quantidade_voos << endl;
    
                return;
            }
        }
        cout << "Codigo de Passageiro não encontrado." << endl;
    }
    
    void GerenciadorVoos::listar_voos_passageiro(int codigo_passageiro) {
        bool encontrou_voo = false;
    
        for (const Voo& voo : voos) {
            if (find(voo.passageiros.begin(), voo.passageiros.end(), codigo_passageiro) != voo.passageiros.end()) {
                cout << "Voo encontrado:" << endl;
                cout << "Número do Voo: " << voo.numero << endl;
                cout << "Data: " << voo.data << endl;
                cout << "Origem: " << voo.origem << endl;
                cout << "Destino: " << voo.destino << endl;
                cout << "--------------------------------" << endl;
                encontrou_voo = true;
            }
        }
    
        if (!encontrou_voo) {
            cout << "Nenhum voo encontrado para o passageiro com código " << codigo_passageiro << "." << endl;
        }
    }
    
    void GerenciadorVoos::atualizar_pontos_fidelidade(int codigo_passageiro) {
        bool encontrou = false; 
        for (Passageiro& passageiro : passageiros) {
            if (passageiro.codigo == codigo_passageiro) {
                encontrou = true; 
                passageiro.pontos_fidelidade = passageiro.quantidade_voos * 10; 
                cout << "O passageiro de código " << codigo_passageiro << " tem " 
                     << passageiro.pontos_fidelidade << " pontos" << endl; 
                break;
            }
        }
    
        if (!encontrou) { 
            cerr << "Erro: Não existe um passageiro com o código " << codigo_passageiro << " ainda." << endl;
        }
    }
    
    
    
    const vector<Passageiro>& GerenciadorVoos::get_passageiros() const {
        return passageiros;
    }
    
    void pedir_quantidade_voos(Passageiro& passageiro) {
        while (true) {
            cout << "Quantos voos o passageiro realizou? ";
            if (ler_inteiro(passageiro.quantidade_voos) && passageiro.quantidade_voos >= 0) {
                break;
            } else {
                cout << "Entrada inválida. Digite somente numeros inteiro não negativo." << endl;
            }    
        }
    }
        void GerenciadorVoos::baixar_reserva() {
            int codigo_passageiro, numero_voo;
            cout << "Digite o número do voo para realizar a baixa: ";
            ler_inteiro(numero_voo);
    
            auto voo = find_if(voos.begin(), voos.end(), [numero_voo](const Voo& v) {
                return v.numero == numero_voo;
            });
    
            if (voo != voos.end()) {
                cout << "Passageiros no voo " << numero_voo << ":\n";
                for (int codigo : voo->passageiros) {
                    cout << "Código do passageiro: " << codigo << endl;
                }
    
                cout << "Digite o código do passageiro que deseja remover: ";
                ler_inteiro(codigo_passageiro);
    
                auto it = find(voo->passageiros.begin(), voo->passageiros.end(), codigo_passageiro);
                if (it != voo->passageiros.end()) {
                    voo->passageiros.erase(it);  
                    cout << "Passageiro removido do voo com sucesso!" << endl;
    
                    ofstream arquivo_voos("voos.bin", ios::binary);
                    if (arquivo_voos.is_open()) {
                        for (const Voo& v : voos) {
                            arquivo_voos.write(reinterpret_cast<const char*>(&v), sizeof(Voo));
                        }
                        arquivo_voos.close();
                        cout << "Voo atualizado com sucesso no arquivo." << endl;
                    } else {
                        cerr << "Erro ao salvar os dados de voos." << endl;
                    }
                } else {
                    cout << "Passageiro não encontrado no voo." << endl;
                }
            } else {
                cout << "Voo não encontrado." << endl;
            }
        }
    
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
    