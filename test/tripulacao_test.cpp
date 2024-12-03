#include <gtest/gtest.h>
#include "../src/cadastrotripulacao.h" 

TEST(TripulacaoTest, GerarCodigoTripulacao) {
    int codigo = gerarCodigoTripulacao();
    EXPECT_GT(codigo, 0) << "O código gerado deve ser maior que 0";
}

TEST(TripulacaoTest, LerTripulacao) {
    std::vector<Tripulacao> tripulantes = lerTripulacao();
    EXPECT_FALSE(tripulantes.empty()) << "Não há tripulantes cadastrados";
}
