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
