#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "../src/main.h"  
 
using namespace std;

// Teste de programa de fidelidade
TEST(FidelidadeTest, AcumularPontos) {
    // Criar um passageiro
    Passageiro passageiro;
    passageiro.codigo = 1;
    passageiro.nome = "Carlos Almeida";
    passageiro.telefone = "123456789";
    passageiro.documento = "12345678901";
    passageiro.email = "carlos@email.com";

    salvarPassageiro(passageiro);

    // Acumular pontos
    acumularPontos(1, 100);
    int pontos = consultarPontos(1);

    // Verificar se os pontos foram acumulados corretamente
    EXPECT_EQ(pontos, 100);
}

TEST(FidelidadeTest, ResgatarPontos) {
    // Criar um passageiro
    Passageiro passageiro;
    passageiro.codigo = 1;
    passageiro.nome = "Carlos Almeida";
    passageiro.telefone = "123456789";
    passageiro.documento = "12345678901";
    passageiro.email = "carlos@email.com";

    salvarPassageiro(passageiro);

    // Acumular pontos
    acumularPontos(1, 100);

    // Resgatar pontos
    resgatarPontos(1, 50);
    int pontos = consultarPontos(1);

    // Verificar se os pontos foram resgatados corretamente
    EXPECT_EQ(pontos, 50);
}
