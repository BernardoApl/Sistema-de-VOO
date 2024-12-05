# Estrutura: CadastroPassageiro

Gerencia o cadastro de passageiros, incluindo a leitura e escrita de dados no arquivo binário.

## Funções:

### `vector<Passageiro> carregar_passageiros(const string& arquivo)`
Carrega os dados de passageiros armazenados em um arquivo binário.

#### Parâmetros:
- `arquivo` (const `string&`): Nome do arquivo binário de onde os passageiros serão carregados.

#### Retorno:
- `vector<Passageiro>`: Vetor contendo todos os passageiros lidos do arquivo.

#### Funcionamento:
- Abre o arquivo em modo binário.
- Lê os registros sequencialmente, adicionando-os ao vetor.
- Fecha o arquivo e retorna o vetor preenchido.

---

### `bool cadastrar(const string& arquivo, const Passageiro& passageiro)`
Registra um novo passageiro no arquivo binário.

#### Parâmetros:
- `arquivo` (const `string&`): Nome do arquivo onde o passageiro será registrado.
- `passageiro` (const `Passageiro&`): Estrutura com os dados do passageiro a ser cadastrado.

#### Retorno:
- `bool`: `true` se o cadastro for realizado com sucesso, `false` caso contrário.

#### Funcionamento:
- Valida os dados do passageiro para garantir que não estão vazios ou inválidos.
- Abre o arquivo em modo binário de apêndice.
- Escreve os dados do passageiro no arquivo.
- Fecha o arquivo e retorna o status da operação.

---

### Template: `bool ler_inteiro(T& num)`
Valida a entrada do usuário para aceitar somente números inteiros.

#### Parâmetros:
- `num` (T&): Referência para armazenar o número lido.

#### Retorno:
- `bool`: Sempre retorna `true` após validar e corrigir a entrada.

#### Funcionamento:
- Lê a entrada do usuário.
- Limpa o buffer e solicita nova entrada caso o valor informado seja inválido.

---

### Função Principal: `int main()`
Gerencia o menu principal do sistema de cadastro de passageiros.

#### Funcionamento:
- Exibe as opções do menu principal para o usuário.
- Permite cadastrar novos passageiros, verificando se o código do passageiro já existe.
- Solicita e valida os dados do passageiro, como nome, endereço e telefone.
- Utiliza a função `cadastrar` para salvar os dados no arquivo.
- Lê os dados dos passageiros previamente cadastrados para evitar duplicações.
