# Estrutura: Tripulação

Representa as informações de um membro da tripulação.

## Atributos:
- `codigo` (int): Código único do tripulante.
- `nome` (string): Nome do tripulante.
- `telefone` (string): Número de telefone do tripulante.
- `cargo` (string): Cargo do tripulante, codificado como:
  - 1: Piloto.
  - 2: Co-piloto.
  - 3: Comissário.

## Funções:

### `void salvarTripulacao(const Tripulacao &tripulacao)`
Salva as informações de um tripulante no arquivo binário `tripulacao.dat`.

#### Parâmetros:
- `tripulacao` (const `Tripulacao &`): Objeto representando o tripulante a ser salvo.

#### Funcionamento:
- Abre o arquivo no modo binário e de apêndice.
- Grava os dados do tripulante (código, nome, telefone e cargo) no arquivo.
- Fecha o arquivo ao final.

---

### `vector<Tripulacao> lerTripulacao()`
Lê os dados dos tripulantes do arquivo binário e os retorna em um vetor.

#### Retorno:
- `vector<Tripulacao>`: Vetor contendo os tripulantes cadastrados.

#### Funcionamento:
- Abre o arquivo no modo binário.
- Lê os dados sequencialmente (código, nome, telefone e cargo) e os armazena em objetos do tipo `Tripulacao`.
- Adiciona cada tripulante ao vetor.
- Retorna o vetor contendo todos os tripulantes.

---

### `void exibirTripulantes()`
Exibe todos os tripulantes cadastrados no console.

#### Funcionamento:
- Lê todos os tripulantes usando a função `lerTripulacao`.
- Para cada tripulante, traduz o código do cargo para o respectivo nome (Piloto, Co-piloto ou Comissário) e exibe suas informações formatadas no console.

---

### `void exibirTripulantesPorCargo(const string &cargoDesejado)`
Exibe tripulantes filtrados por cargo.

#### Parâmetros:
- `cargoDesejado` (const `string &`): Código do cargo a ser filtrado (1, 2 ou 3).

#### Funcionamento:
- Lê os tripulantes usando a função `lerTripulacao`.
- Filtra os tripulantes cujo cargo corresponde ao desejado.
- Exibe as informações formatadas dos tripulantes filtrados no console.

---

### `int gerarCodigoTripulacao()`
Gera um código único para um novo tripulante.

#### Retorno:
- `int`: O próximo código disponível, incrementado com base no maior código já existente.

#### Funcionamento:
- Lê todos os tripulantes cadastrados.
- Determina o maior código existente e retorna um valor incrementado.

---

### `void cadastrarTripulante()`
Solicita os dados do tripulante ao usuário e salva no arquivo.

#### Funcionamento:
- Gera um código único para o tripulante usando `gerarCodigoTripulacao`.
- Solicita nome, cargo e telefone ao usuário.
- Salva o tripulante no arquivo usando a função `salvarTripulacao`.

- Para cada voo, exibe suas informações formatadas, incluindo:
- Código do voo.
- Data e hora.
- Origem e destino.
- Tripulação associada (avião, piloto, copiloto e comissário).
- Tarifa.

---

### `int gerarCodigoVoo()`
Gera um código único para um novo voo.

#### Retorno:
- `int`: O próximo código disponível, incrementado com base no maior código já existente.

#### Funcionamento:
- Lê os voos cadastrados no arquivo usando `lerVoos`.
- Determina o maior código já registrado e retorna um valor incrementado.

---

### `void cadastrarVoo()`
Permite cadastrar um novo voo solicitando as informações ao usuário.

#### Funcionamento:
1. Gera um código único para o voo usando `gerarCodigoVoo`.
2. Solicita os seguintes dados ao usuário:
 - Data e hora.
 - Origem e destino.
 - Identificações de tripulação (avião, piloto, copiloto e comissário).
 - Tarifa.
3. Chama a função `salvarVoo` para salvar os dados no arquivo.
4. Exibe uma mensagem de sucesso ao final:
