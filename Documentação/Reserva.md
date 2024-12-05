# Sistema de Reservas de Assentos em Voos

Este programa implementa um sistema básico para gerenciar reservas de assentos em voos de uma companhia aérea. Ele verifica disponibilidade, detecta reservas duplicadas e registra novas reservas em arquivos binários.

---

## Estrutura do Programa

### Classe `CompanhiaAerea`

Responsável pela lógica de reservas e controle de assentos.

**Atributos**:
- **`arquivoAssentos`**: Nome do arquivo binário contendo informações de assentos (`assentos.dat`).
- **`arquivoReservas`**: Nome do arquivo binário contendo informações de reservas (`reservas.dat`).

---

### Métodos Principais

#### `bool assentoDisponivel(int codigoVoo, int numeroAssento)`
- Verifica se o assento especificado está disponível para um voo.
- Lê os dados do arquivo `assentos.dat`.
  - **Retorna `true`**: Se o assento está **livre** (`status == false`).
  - **Retorna `false`**: Se o assento está ocupado ou não existe.

---

#### `bool reservaDuplicada(int codigoVoo, int numeroAssento)`
- Verifica se já existe uma reserva para o assento em determinado voo.
- Lê os dados do arquivo `reservas.dat`.
  - **Retorna `true`**: Se uma reserva já existe.
  - **Retorna `false`**: Caso contrário.

---

#### `void ocuparAssento(int codigoVoo, int numeroAssento)`
- Marca o assento como ocupado no arquivo `assentos.dat`.
- Lê o arquivo em modo leitura/escrita e altera o valor do campo `status` para `true`.

---

#### `void cadastrarReserva()`
- Processo para cadastro de uma nova reserva:
  1. Solicita ao usuário:
     - **Código do voo**
     - **Número do assento**
     - **Código do passageiro**
  2. Verifica disponibilidade do assento usando `assentoDisponivel()`.
  3. Checa duplicidade da reserva com `reservaDuplicada()`.
  4. Grava os dados da nova reserva no arquivo `reservas.dat`.
  5. Atualiza o arquivo `assentos.dat` para marcar o assento como ocupado.
  6. Exibe mensagens de sucesso ou erro.

---

### Estruturas de Dados

#### `Assento`
Armazena os dados de um assento em um voo:
- **`int codigoVoo`**: Código do voo.
- **`int numeroAssento`**: Número do assento.
- **`bool status`**: Indica se o assento está ocupado (`true`) ou livre (`false`).

#### `Reserva`
Armazena os dados de uma reserva:
- **`int codigoVoo`**: Código do voo.
- **`int numeroAssento`**: Número do assento reservado.
- **`int codigoPassageiro`**: Código único do passageiro.

---

## Função Principal (`main`)

Implementa o menu principal do sistema:
1. **Opção 1 - Cadastrar Reserva**:
   - Chama o método `cadastrarReserva()` para realizar o processo de reserva.
2. **Opção 0 - Sair**:
   - Encerra o programa.

---

## Fluxo de Execução

1. O programa lê dados dos arquivos binários `assentos.dat` e `reservas.dat`.
2. Permite ao usuário:
   - Cadastrar reservas com validação de disponibilidade e duplicidade.
3. Atualiza os arquivos conforme necessário:
   - Adiciona uma nova reserva ao arquivo `reservas.dat`.
   - Marca o assento como ocupado no arquivo `assentos.dat`.

---

## Melhorias Possíveis

1. **Validação de Entradas**:
   - Garantir que o usuário insira apenas valores válidos.
2. **Tratamento de Exceções**:
   - Implementar manipulação robusta de erros no acesso e manipulação de arquivos.
3. **Criação Automática de Arquivos**:
   - Garantir que os arquivos binários sejam criados automaticamente se não existirem.
4. **Interface de Usuário**:
   - Melhorar a clareza e usabilidade do menu.

---

Este sistema é funcional e segue boas práticas básicas de manipulação de arquivos e lógica binária. Ele pode ser ampliado com recursos adicionais para gerenciar mais funcionalidades da companhia aérea.
