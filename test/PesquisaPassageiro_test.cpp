#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "../src/main.h" 

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
