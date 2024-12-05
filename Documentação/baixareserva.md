# Estrutura: CompanhiaAerea

Gerencia as operações de uma companhia aérea, incluindo reservas de voos e gerenciamento de assentos.

## Atributos:
- `arquivoAssentos` (string): Nome do arquivo binário que armazena os dados dos assentos.
- `arquivoReservas` (string): Nome do arquivo binário que armazena os dados das reservas.

## Funções:

### `bool assentoDisponivel(int codigoVoo, int numeroAssento)`
Verifica se um assento está disponível para reserva.

#### Parâmetros:
- `codigoVoo` (int): Código do voo.
- `numeroAssento` (int): Número do assento.

#### Retorno:
- `bool`: `true` se o assento está disponível, `false` caso contrário.

#### Funcionamento:
- Lê o arquivo `assentos.dat`.
- Localiza o assento correspondente ao código do voo e número informado.
- Retorna a disponibilidade com base no status do assento.

---

### `bool reservaDuplicada(int codigoVoo, int numeroAssento)`
Verifica se já existe uma reserva para um assento específico.

#### Parâmetros:
- `codigoVoo` (int): Código do voo.
- `numeroAssento` (int): Número do assento.

#### Retorno:
- `bool`: `true` se já há uma reserva, `false` caso contrário.

#### Funcionamento:
- Lê o arquivo `reservas.dat`.
- Verifica se há uma reserva existente para o assento no voo indicado.

---

### `void ocuparAssento(int codigoVoo, int numeroAssento)`
Marca um assento como ocupado.

#### Parâmetros:
- `codigoVoo` (int): Código do voo.
- `numeroAssento` (int): Número do assento.

#### Funcionamento:
- Abre o arquivo `assentos.dat` em modo leitura e escrita.
- Localiza o assento correspondente e atualiza seu status para ocupado.

---

### `void adicionarReserva(vector<Voo>& voos, int codigoVoo, int numeroAssento, int codigoPassageiro)`
Adiciona uma nova reserva para um passageiro.

#### Parâmetros:
- `voos` (vector<Voo>&): Lista de voos disponíveis.
- `codigoVoo` (int): Código do voo.
- `numeroAssento` (int): Número do assento.
- `codigoPassageiro` (int): Código do passageiro.

#### Funcionamento:
- Verifica a disponibilidade do assento.
- Checa se já existe uma reserva para o assento.
- Cria uma nova reserva e salva no arquivo `reservas.dat`.
- Atualiza o status do assento para ocupado.

---

### `void baixarReserva(vector<Voo>& voos, int codigoVoo, int numeroAssento, int codigoPassageiro)`
Remove uma reserva existente e libera o assento.

#### Parâmetros:
- `voos` (vector<Voo>&): Lista de voos disponíveis.
- `codigoVoo` (int): Código do voo.
- `numeroAssento` (int): Número do assento.
- `codigoPassageiro` (int): Código do passageiro.

#### Funcionamento:
- Lê o arquivo `reservas.dat` e remove a reserva correspondente.
- Atualiza o arquivo removendo a reserva.
- Marca o assento como disponível.
- Exibe o valor da tarifa do voo correspondente.

---

### `void liberarAssento(int codigoVoo, int numeroAssento)`
Marca um assento como disponível novamente.

#### Parâmetros:
- `codigoVoo` (int): Código do voo.
- `numeroAssento` (int): Número do assento.

#### Funcionamento:
- Abre o arquivo `assentos.dat` em modo leitura e escrita.
- Localiza o assento correspondente e atualiza seu status para disponível.

---

### `int obterEntradaNumerica()`
Lê e valida a entrada numérica do usuário.

#### Retorno:
- `int`: Valor numérico fornecido pelo usuário.

#### Funcionamento:
- Solicita a entrada do usuário.
- Verifica se é um número válido, tratando erros de entrada.
- Retorna o número válido.

---

### Função Principal: `int main()`
Gerencia o menu principal da aplicação.

#### Funcionamento:
- Exibe opções do menu para o usuário.
- Permite adicionar reservas, baixar reservas ou exibir voos.
- Processa as entradas do usuário e invoca as funções correspondentes.
