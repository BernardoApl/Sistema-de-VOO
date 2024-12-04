#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "tripulacao.h" 

using namespace std;

// Teste de escrita e leitura de tripulação
TEST(TripulacaoTest, SalvarELerTripulacao) {
    // Criar um tripulante
    Tripulacao tripulante;
    tripulante.codigo = 1;
    tripulante.nome = "João Silva";
    tripulante.telefone = "123456789";
    tripulante.cargo = "1"; // Piloto

    // Salvar o tripulante
    salvarTripulacao(tripulante);

    // Ler os tripulantes do arquivo
    vector<Tripulacao> tripulantes = lerTripulacao();

    // Verificar se o tripulante foi salvo e lido corretamente
    ASSERT_EQ(tripulantes.size(), 1);
    EXPECT_EQ(tripulantes[0].codigo, 1);
    EXPECT_EQ(tripulantes[0].nome, "João Silva");
    EXPECT_EQ(tripulantes[0].telefone, "123456789");
    EXPECT_EQ(tripulantes[0].cargo, "1");
}

// Teste para listar tripulantes por cargo
TEST(TripulacaoTest, ExibirTripulantesPorCargo) {
    // Criar e salvar tripulantes
    Tripulacao piloto;
    piloto.codigo = 1;
    piloto.nome = "João Silva";
    piloto.telefone = "123456789";
    piloto.cargo = "1"; // Piloto
    salvarTripulacao(piloto);

    Tripulacao copiloto;
    copiloto.codigo = 2;
    copiloto.nome = "Maria Oliveira";
    copiloto.telefone = "987654321";
    copiloto.cargo = "2"; // Co-piloto
    salvarTripulacao(copiloto);

    testing::internal::CaptureStdout();
    exibirTripulantesPorCargo("1");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("João Silva"), string::npos); 
}


//Caso de testes do cadastro de passageiro
#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "passageiro.h"  

using namespace std;

// Teste de cadastro de passageiro
TEST(PassageiroTest, CadastroPassageiro) {
    // Criar um novo passageiro
    Passageiro passageiro;
    passageiro.codigo = 1;
    passageiro.nome = "Carlos Almeida";
    passageiro.telefone = "123456789";
    passageiro.documento = "12345678901";
    passageiro.email = "carlos@email.com";

    // Salvar o passageiro
    salvarPassageiro(passageiro);

    // Ler os passageiros do arquivo
    vector<Passageiro> passageiros = lerPassageiros();

    // Verificar se o passageiro foi salvo e lido corretamente
    ASSERT_EQ(passageiros.size(), 1);
    EXPECT_EQ(passageiros[0].codigo, 1);
    EXPECT_EQ(passageiros[0].nome, "Carlos Almeida");
    EXPECT_EQ(passageiros[0].telefone, "123456789");
    EXPECT_EQ(passageiros[0].documento, "12345678901");
    EXPECT_EQ(passageiros[0].email, "carlos@email.com");
}

#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "voo.h"  

using namespace std;

// Teste de cadastro de voo
TEST(VooTest, CadastroVoo) {
    // Criar um novo voo
    Voo voo;
    voo.codigo = 1;
    voo.origem = "São Paulo";
    voo.destino = "Rio de Janeiro";
    voo.dataHora = "2024-12-05 10:00";
    voo.capacidade = 100;

    // Salvar o voo
    salvarVoo(voo);

    // Ler os voos do arquivo
    vector<Voo> voos = lerVoos();

    // Verificar se o voo foi salvo e lido corretamente
    ASSERT_EQ(voos.size(), 1);
    EXPECT_EQ(voos[0].codigo, 1);
    EXPECT_EQ(voos[0].origem, "São Paulo");
    EXPECT_EQ(voos[0].destino, "Rio de Janeiro");
    EXPECT_EQ(voos[0].dataHora, "2024-12-05 10:00");
    EXPECT_EQ(voos[0].capacidade, 100);
}

#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "reserva.h"  

using namespace std;

// Teste de reserva de passageiro
TEST(ReservaTest, ReservaPassageiro) {
    // Criar um passageiro
    Passageiro passageiro;
    passageiro.codigo = 1;
    passageiro.nome = "Carlos Almeida";
    passageiro.telefone = "123456789";
    passageiro.documento = "12345678901";
    passageiro.email = "carlos@email.com";

    // Criar um voo
    Voo voo;
    voo.codigo = 1;
    voo.origem = "São Paulo";
    voo.destino = "Rio de Janeiro";
    voo.dataHora = "2024-12-05 10:00";
    voo.capacidade = 100;

    // Realizar a reserva
    Reserva reserva;
    reserva.codigoPassageiro = 1;
    reserva.codigoVoo = 1;
    reserva.status = "Reservado";

    salvarReserva(reserva);

    // Verificar se a reserva foi salva corretamente
    vector<Reserva> reservas = lerReservas();
    ASSERT_EQ(reservas.size(), 1);
    EXPECT_EQ(reservas[0].codigoPassageiro, 1);
    EXPECT_EQ(reservas[0].codigoVoo, 1);
    EXPECT_EQ(reservas[0].status, "Reservado");
}

#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "reserva.h"  

using namespace std;

// Teste de baixa de reserva
TEST(ReservaTest, BaixaReserva) {
    // Criar uma reserva
    Reserva reserva;
    reserva.codigoPassageiro = 1;
    reserva.codigoVoo = 1;
    reserva.status = "Reservado";

    salvarReserva(reserva);

    // Realizar a baixa
    baixarReserva(1);

    // Verificar se a reserva foi removida
    vector<Reserva> reservas = lerReservas();
    ASSERT_EQ(reservas.size(), 0);  
}

//pesquisa passageiro 
#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "passageiro.h"  

using namespace std;

// Teste de busca de passageiro
TEST(PesquisaTest, BuscaPassageiro) {
    // Criar um passageiro
    Passageiro passageiro;
    passageiro.codigo = 1;
    passageiro.nome = "Carlos Almeida";
    passageiro.telefone = "123456789";
    passageiro.documento = "12345678901";
    passageiro.email = "carlos@email.com";

    salvarPassageiro(passageiro);

    // Realizar a busca
    Passageiro encontrado = buscaPassageiro(1);

    // Verificar se o passageiro foi encontrado corretamente
    EXPECT_EQ(encontrado.codigo, 1);
    EXPECT_EQ(encontrado.nome, "Carlos Almeida");
    EXPECT_EQ(encontrado.telefone, "123456789");
    EXPECT_EQ(encontrado.documento, "12345678901");
    EXPECT_EQ(encontrado.email, "carlos@email.com");
}

#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "tripulacao.h"  

using namespace std;

// Teste de busca de tripulante
TEST(PesquisaTest, BuscaTripulante) {
    // Criar um tripulante
    Tripulacao tripulante;
    tripulante.codigo = 1;
    tripulante.nome = "João Silva";
    tripulante.telefone = "123456789";
    tripulante.cargo = "Piloto";

    salvarTripulacao(tripulante);

    // Realizar a busca
    Tripulacao encontrado = buscaTripulante(1);

    // Verificar se o tripulante foi encontrado corretamente
    EXPECT_EQ(encontrado.codigo, 1);
    EXPECT_EQ(encontrado.nome, "João Silva");
    EXPECT_EQ(encontrado.telefone, "123456789");
    EXPECT_EQ(encontrado.cargo, "Piloto");
}

//Caso de testes programa de fidalidade

#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "passageiro.h" 

using namespace std;

// Teste de cadastro no programa de fidelidade
TEST(ProgramaFidelidadeTest, CadastroProgramaFidelidade) {
    // Criar um passageiro
    Passageiro passageiro;
    passageiro.codigo = 1;
    passageiro.nome = "João Silva";
    passageiro.telefone = "123456789";
    passageiro.email = "joao@exemplo.com";

    // Adicionar o passageiro ao programa de fidelidade
    adicionarFidelidade(passageiro);

    // Verificar se o passageiro foi cadastrado corretamente no programa de fidelidade
    // Supondo que a função "consultarPontos" retorna o número de pontos de um passageiro
    int pontos = consultarPontos(passageiro.codigo);
    EXPECT_EQ(pontos, 0);  // Passageiro recém cadastrado, não tem pontos ainda
}

// Teste de acumulação de pontos
TEST(ProgramaFidelidadeTest, AcumularPontos) {
    // Criar um passageiro
    Passageiro passageiro;
    passageiro.codigo = 1;
    passageiro.nome = "João Silva";
    passageiro.telefone = "123456789";
    passageiro.email = "joao@exemplo.com";

    // Adicionar o passageiro ao programa de fidelidade
    adicionarFidelidade(passageiro);

    // Acumular pontos após uma reserva
    acumularPontos(passageiro.codigo, 100);

    // Verificar se os pontos foram corretamente acumulados
    int pontos = consultarPontos(passageiro.codigo);
    EXPECT_EQ(pontos, 100);  
}

// Teste de resgatar pontos
TEST(ProgramaFidelidadeTest, ResgatarPontos) {
    // Criar um passageiro
    Passageiro passageiro;
    passageiro.codigo = 1;
    passageiro.nome = "João Silva";
    passageiro.telefone = "123456789";
    passageiro.email = "joao@exemplo.com";

    // Adicionar o passageiro ao programa de fidelidade
    adicionarFidelidade(passageiro);

    // Acumular pontos
    acumularPontos(passageiro.codigo, 200);

    // Resgatar pontos para um benefício (digamos que o mínimo para resgatar é 100 pontos)
    bool resgatado = resgatarPontos(passageiro.codigo, 100);

    // Verificar se a operação de resgatar foi bem-sucedida
    EXPECT_TRUE(resgatado);  
    int pontos = consultarPontos(passageiro.codigo);
    EXPECT_EQ(pontos, 100);  
}

// Teste de consulta de pontos
TEST(ProgramaFidelidadeTest, ConsultarPontos) {
    // Criar um passageiro
    Passageiro passageiro;
    passageiro.codigo = 1;
    passageiro.nome = "João Silva";
    passageiro.telefone = "123456789";
    passageiro.email = "joao@exemplo.com";

    // Adicionar o passageiro ao programa de fidelidade
    adicionarFidelidade(passageiro);

    // Acumular pontos
    acumularPontos(passageiro.codigo, 50);

    // Verificar se a consulta de pontos retorna o valor correto
    int pontos = consultarPontos(passageiro.codigo);
    EXPECT_EQ(pontos, 50);  // O passageiro deve ter 50 pontos
}

