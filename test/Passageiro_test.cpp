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
