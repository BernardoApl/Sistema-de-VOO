#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Tripulacao {
  int codigo;
  string nome;
  string telefone;
  string cargo; // 1 - piloto, 2 - co-piloto, 3 - comissario
};

struct Voos {
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

void salvarVoo(const Voos &voo) {
  ofstream arquivo("voos.dat", ios::binary | ios::app);
  if (!arquivo) {
    cerr << "Erro ao abrir o arquivo para escrita!" << endl;
    return;
  }
  size_t tamanho;

  arquivo.write(reinterpret_cast<const char *>(&voo.codigo),
                sizeof(voo.codigo));

  tamanho = voo.data.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.data.data(), tamanho);

  tamanho = voo.hora.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.hora.data(), tamanho);

  tamanho = voo.origem.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.origem.data(), tamanho);

  tamanho = voo.destino.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.destino.data(), tamanho);

  tamanho = voo.codigoAviao.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.codigoAviao.data(), tamanho);

  tamanho = voo.codigoPiloto.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.codigoPiloto.data(), tamanho);

  tamanho = voo.codigoCopiloto.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.codigoCopiloto.data(), tamanho);

  tamanho = voo.codigoComissario.size();
  arquivo.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));
  arquivo.write(voo.codigoComissario.data(), tamanho);

  arquivo.write(reinterpret_cast<const char *>(&voo.tarifa),
                sizeof(voo.tarifa));

  arquivo.close();
}

vector<Voos> lerVoos() {
  vector<Voos> voos;
  ifstream arquivo("voos.dat", ios::binary);
  if (!arquivo) {
    cerr << "Erro ao abrir o arquivo para leitura!" << endl;
    return voos;
  }

  Voos voo;
  size_t tamanho;
  string buffer;

  while (
      arquivo.read(reinterpret_cast<char *>(&voo.codigo), sizeof(voo.codigo))) {
    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.data = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.hora = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.origem = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.destino = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.codigoAviao = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.codigoPiloto = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.codigoCopiloto = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    voo.codigoComissario = buffer;

    arquivo.read(reinterpret_cast<char *>(&voo.tarifa), sizeof(voo.tarifa));

    voos.push_back(voo);
  }

  arquivo.close();
  return voos;
}

void exibirTripulantes() {
  string cargo;

  vector<Tripulacao> tripulantes = lerTripulacao();
  if (tripulantes.empty()) {
    cout << "Nenhum tripulante encontrado." << endl;
    return;
  }

  cout << "Tripulantes cadastrados:" << endl;
  for (const auto &tripulante : tripulantes) {
    if (tripulante.cargo == "1") {
      cargo = "Piloto";
    } else if (tripulante.cargo == "2") {
      cargo = "Co-piloto";
    } else {
      cargo = "Comissario";
    }
    cout << "Código: " << tripulante.codigo << endl;
    cout << "Nome: " << tripulante.nome << endl;
    cout << "Telefone: " << tripulante.telefone << endl;
    cout << "Cargo: " << cargo << endl;
    cout << "------------------------" << endl;
  }
}

void exibirVoos() {
  vector<Voos> voos = lerVoos();
  if (voos.empty()) {
    cout << "Nenhum voo encontrado." << endl;
    return;
  }

  cout << "Voos cadastrados:" << endl;
  for (const auto &voo : voos) {
    cout << "Código: " << voo.codigo << endl;
    cout << "Data: " << voo.data << endl;
    cout << "Hora: " << voo.hora << endl;
    cout << "Origem: " << voo.origem << endl;
    cout << "Destino: " << voo.destino << endl;
    cout << "Código do Avião: " << voo.codigoAviao << endl;
    cout << "Código do Piloto: " << voo.codigoPiloto << endl;
    cout << "Código do Copiloto: " << voo.codigoCopiloto << endl;
    cout << "Código do Comissário: " << voo.codigoComissario << endl;
    cout << "Tarifa: " << voo.tarifa << endl;
    cout << "------------------------" << endl;
  }
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

int gerarCodigoVoo() {
  int codigoVoo = 1;
  vector<Voos> voo = lerVoos();
  for (const auto &v : voo) {
    if (v.codigo >= codigoVoo) {
      codigoVoo = v.codigo + 1;
    }
  }
  return codigoVoo;
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

void cadastrarVoo() {
  Voos voo;
  cout << "Digite os dados do voo:" << endl;
  voo.codigo = gerarCodigoVoo();
  cin.ignore();
  cout << "Data (dd/mm/yyyy): ";
  getline(cin, voo.data);
  cout << "Hora (hh:mm): ";
  getline(cin, voo.hora);
  cout << "Origem: ";
  getline(cin, voo.origem);
  cout << "Destino: ";
  getline(cin, voo.destino);
  cout << "Código do Avião: ";
  getline(cin, voo.codigoAviao);
  exibirTripulantesPorCargo("1");
  cout << "Código do Piloto: ";
  getline(cin, voo.codigoPiloto);
  exibirTripulantesPorCargo("2");
  cout << "Código do Copiloto: ";
  getline(cin, voo.codigoCopiloto);
  exibirTripulantesPorCargo("3");
  cout << "Código do Comissário: ";
  getline(cin, voo.codigoComissario);
  cout << "Tarifa: ";
  cin >> voo.tarifa;

  salvarVoo(voo);
  cout << "Voo cadastrado com sucesso!" << endl;
}

void menu() {
  int opcao;
  do {
    cout << "1. Cadastrar Tripulante" << endl;
    cout << "2. Listar Tripulantes" << endl;
    cout << "3. Cadastrar Voos" << endl;
    cout << "4. Listar Voos" << endl;
    cout << "0. Sair" << endl;
    cout << "Escolha uma opcao: ";
    cin >> opcao;

    switch (opcao) {
    case 1:
      cadastrarTripulante();
      break;
    case 2:
      exibirTripulantes();
      break;
    case 3:
      cadastrarVoo();
      break;
    case 4:
      exibirVoos();
    case 0:
      cout << "Saindo..." << endl;
      break;
    default:
      cout << "Opção inválida!" << endl;
    }
  } while (opcao != 0);
}

int main() {
  menu();
  return 0;
}
