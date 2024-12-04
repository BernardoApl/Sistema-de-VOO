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
