#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include "../src/main.h" 

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
