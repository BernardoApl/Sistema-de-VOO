# Estrutura: GerenciadorVoos

Gerencia informações de passageiros, voos e o programa de fidelidade, incluindo operações de leitura e atualização de dados.

## Estruturas:

### `Passageiro`
Armazena os dados de um passageiro.

- `int codigo`: Código único do passageiro.
- `char nome[100]`: Nome do passageiro.
- `char endereco[200]`: Endereço do passageiro.
- `int telefone`: Telefone do passageiro.
- `int quantidade_voos`: Quantidade de voos realizados pelo passageiro.
- `int pontos_fidelidade`: Pontos acumulados no programa de fidelidade.

---

### `Voo`
Representa um voo.

- `int numero`: Número do voo.
- `char data[20]`: Data do voo.
- `char origem[50]`: Origem do voo.
- `char destino[50]`: Destino do voo.
- `vector<int> passageiros`: Lista de códigos dos passageiros associados ao voo.
- `vector<int> tripulantes`: Lista de códigos dos tripulantes associados ao voo.

---

### `Tripulacao`
Armazena os dados de um membro da tripulação.

- `int codigo`: Código único do tripulante.
- `string nome`: Nome do tripulante.
- `string telefone`: Telefone do tripulante.
- `string cargo`: Cargo do tripulante.

---

## Métodos:

### `ler_dados_arquivos()`
Carrega os dados dos arquivos binários de passageiros e voos.

#### Funcionamento:
- Limpa os vetores `passageiros` e `voos`.
- Lê registros binários dos arquivos `passageiros.bin` e `voos.bin`.
- Popula os vetores correspondentes.

---

### `atualizar_pontos_fidelidade(int codigo_passageiro)`
Atualiza os pontos de fidelidade de um passageiro com base nos voos realizados.

#### Parâmetros:
- `codigo_passageiro`: Código do passageiro cujos pontos serão atualizados.

#### Funcionamento:
- Procura o passageiro pelo código.
- Calcula os pontos de fidelidade multiplicando o número de voos realizados por 10.
- Exibe os pontos acumulados ou uma mensagem de erro se o passageiro não for encontrado.

---

### `const vector<Passageiro>& get_passageiros() const`
Retorna uma referência constante ao vetor de passageiros.

---

### `pedir_quantidade_voos(Passageiro& passageiro)`
Solicita ao usuário a quantidade de voos realizados por um passageiro.

#### Parâmetros:
- `passageiro`: Referência ao objeto Passageiro a ser atualizado.

#### Funcionamento:
- Valida a entrada para garantir que seja um número inteiro não negativo.

---

## Função Principal: `int main()`

Gerencia o menu do programa, incluindo o programa de fidelidade.

### Opções do Menu:
1. **Programa de Fidelidade:** Atualiza os pontos de fidelidade de um passageiro ao informar o código.
2. **Sair:** Encerra o programa.

#### Fluxo:
- Exibe o menu principal.
- Solicita a opção do usuário e executa a funcionalidade correspondente.
- Valida entradas para evitar erros.
