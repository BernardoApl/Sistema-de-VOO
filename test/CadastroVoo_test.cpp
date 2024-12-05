#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "../src/main.h" 

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
