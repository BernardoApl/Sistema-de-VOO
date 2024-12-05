# Estrutura: Sistema de Pesquisa de Tripulação e Passageiros

Este sistema permite pesquisar passageiros e tripulantes registrados em arquivos binários, utilizando códigos únicos para identificar os registros.

---

## Funções e Métodos

### Funções Gerais

#### `lerTripulacao()`
Lê os dados da tripulação a partir do arquivo binário **`tripulacao.dat`**.

- Retorna um `vector<Tripulacao>` contendo os dados da tripulação.
- Cada membro da tripulação possui:
  - Código (`int`).
  - Nome (`string`).
  - Telefone (`string`).
  - Cargo (`string`).

---

### Classe: `GerenciadorVoos`

#### `ler_dados_arquivos()`
Lê os dados dos passageiros e voos de arquivos binários:
- **`passageiros.bin`**: Popula o vetor `passageiros`.
- **`voos.bin`**: Popula o vetor `voos`.

---

#### `buscar_passageiro(int codigo)`
Busca um passageiro pelo código único fornecido.

- Exibe:
  - Nome, endereço, telefone, e quantidade de voos realizados.
- Exibe mensagem de erro se o código não for encontrado.

---

#### `buscar_tripulante(int codigo)`
Busca um membro da tripulação pelo código único fornecido.

- Exibe:
  - Nome, telefone, e cargo do tripulante (interpretado como Piloto, Co-piloto ou Comissário).
- Exibe mensagem de erro se o código não for encontrado.

---

### Template Auxiliar

#### `template <typename T> bool ler_inteiro(T& num)`
Garante a entrada de números válidos pelo usuário.

---

### Estruturas de Dados

#### `Tripulacao`
Armazena os dados de um tripulante.
- **`int codigo`**: Código único do tripulante.
- **`string nome`**: Nome do tripulante.
- **`string telefone`**: Telefone do tripulante.
- **`string cargo`**: Identificação do cargo.

#### `Passageiro`
Representa os dados de um passageiro.
- **`int codigo`**: Código único.
- **`char nome[100]`**: Nome.
- **`char endereco[200]`**: Endereço.
- **`int telefone`**: Telefone.
- **`int quantidade_voos`**: Quantidade de voos realizados.

---

## Função Principal: `int main()`

Gerencia o sistema de pesquisa de passageiros e tripulação.

### Menu Principal:
1. **Pesquisa**:
   - Submenu para buscar passageiros ou tripulantes.
2. **Sair**:
   - Encerra o programa.

#### Submenu de Pesquisa:
- **Buscar Passageiro**:
  - Solicita o código e exibe os dados correspondentes.
- **Buscar Tripulante**:
  - Solicita o código e exibe os dados correspondentes.
- **Voltar**:
  - Retorna ao menu principal.
