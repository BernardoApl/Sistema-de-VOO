#include <gtest/gtest.h>
#include "../src/cadastrovoo.h"

TEST(CadastroVooTest, GerarCodigoVoo) {
    int codigo = gerarCodigoVoo();
    EXPECT_GT(codigo, 0) << "O código do voo deve ser maior que 0";
}

TEST(CadastroVooTest, LerVoos) {
    std::vector<Voos> voos = lerVoos();
    EXPECT_FALSE(voos.empty()) << "Nenhum voo encontrado no arquivo!";
}

TEST(CadastroVooTest, SalvarELerVoo) {
    Voos voo;
    voo.codigo = gerarCodigoVoo();
    voo.data = "01/12/2024";
    voo.hora = "14:30";
    voo.origem = "São Paulo";
    voo.destino = "Rio de Janeiro";
    voo.codigoAviao = "A123";
    voo.codigoPiloto = "P001";
    voo.codigoCopiloto = "C001";
    voo.codigoComissario = "CM001";
    voo.tarifa = 299.99;

    salvarVoo(voo);

    std::vector<Voos> voos = lerVoos();

    auto it = std::find_if(voos.begin(), voos.end(), [&voo](const Voos &v) {
        return v.codigo == voo.codigo;
    });

    ASSERT_NE(it, voos.end()) << "Voo não encontrado após salvamento!";
    EXPECT_EQ(it->data, voo.data);
    EXPECT_EQ(it->hora, voo.hora);
    EXPECT_EQ(it->origem, voo.origem);
    EXPECT_EQ(it->destino, voo.destino);
    EXPECT_EQ(it->codigoAviao, voo.codigoAviao);
    EXPECT_EQ(it->codigoPiloto, voo.codigoPiloto);
    EXPECT_EQ(it->codigoCopiloto, voo.codigoCopiloto);
    EXPECT_EQ(it->codigoComissario, voo.codigoComissario);
    EXPECT_DOUBLE_EQ(it->tarifa, voo.tarifa);
}

TEST(CadastroVooTest, ExibirVoos) {
    testing::internal::CaptureStdout(); 
    exibirVoos();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Código"), std::string::npos) << "Campos principais ausentes na exibição de voos!";
}

TEST(CadastroVooTest, ArquivoInexistente) {
    remove("voos.dat");

    std::vector<Voos> voos = lerVoos();

    EXPECT_TRUE(voos.empty()) << "Nenhum voo deve ser lido quando o arquivo não existe!";
}
