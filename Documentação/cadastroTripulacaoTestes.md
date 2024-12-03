# Testes de Funcionalidade para Cadastro e Gestão de Tripulantes

## Teste 1: Cadastrar um Novo Tripulante
**Objetivo:** Testar o processo de cadastro de um tripulante.

### Entradas:
- Nome: "João Silva"
- Cargo: "1" (Piloto)
- Telefone: "123456789"

### Resultado Esperado:
O tripulante deve ser salvo corretamente no arquivo `tripulacao.dat` com o código gerado automaticamente.

### Passos:
1. Execute a função `cadastrarTripulante()`.
2. Insira os dados no prompt de entrada.
3. Verifique o arquivo `tripulacao.dat` para garantir que as informações foram salvas corretamente.

---

## Teste 2: Listar Todos os Tripulantes Cadastrados
**Objetivo:** Verificar se os tripulantes cadastrados são corretamente exibidos.

### Entradas:
Suponha que no arquivo `tripulacao.dat` existam dois tripulantes:
- João Silva, Piloto
- Maria Souza, Comissária

### Resultado Esperado:
A função `exibirTripulantes()` deve listar todos os tripulantes, exibindo seus dados como nome, cargo e telefone.

### Passos:
1. Execute a função `exibirTripulantes()`.
2. Verifique a saída no console.

---

## Teste 3: Filtrar Tripulantes por Cargo (Piloto)
**Objetivo:** Testar a filtragem de tripulantes por cargo.

### Entradas:
- Cargo desejado: "1" (Piloto)
- Suponha que o arquivo `tripulacao.dat` tenha três tripulantes: João Silva (Piloto), Maria Souza (Comissária) e Pedro Almeida (Co-piloto).

### Resultado Esperado:
A função `exibirTripulantesPorCargo("1")` deve listar apenas os tripulantes com o cargo "Piloto".

### Passos:
1. Execute a função `exibirTripulantesPorCargo("1")`.
2. Verifique a saída no console para garantir que apenas os Pilotos sejam listados.

---

## Teste 4: Filtrar Tripulantes por Cargo (Comissário)
**Objetivo:** Testar a filtragem de tripulantes por cargo.

### Entradas:
- Cargo desejado: "3" (Comissário)
- Suponha que o arquivo `tripulacao.dat` tenha dois tripulantes: João Silva (Piloto) e Maria Souza (Comissária).

### Resultado Esperado:
A função `exibirTripulantesPorCargo("3")` deve listar apenas os tripulantes com o cargo "Comissário".

### Passos:
1. Execute a função `exibirTripulantesPorCargo("3")`.
2. Verifique a saída no console para garantir que apenas os Comissários sejam listados.

---

## Teste 5: Gerar Código de Tripulante Único
**Objetivo:** Testar a geração do código único para tripulante.

### Entradas:
Suponha que já existam tripulantes com os códigos 1, 2, e 3.

### Resultado Esperado:
A função `gerarCodigoTripulacao()` deve gerar o próximo código disponível (neste caso, 4).

### Passos:
1. Execute a função `gerarCodigoTripulacao()`.
2. Verifique se o código gerado é 4.

---

## Teste 6: Salvar Dados de Tripulante com Nome e Cargo Vazio
**Objetivo:** Testar o comportamento ao tentar salvar um tripulante com dados incompletos.

### Entradas:
- Nome: ""
- Cargo: "" (vazio)
- Telefone: ""

### Resultado Esperado:
O sistema deve salvar o tripulante com dados vazios ou pode haver uma validação de erro (dependendo da implementação).

### Passos:
1. Execute a função `cadastrarTripulante()` e insira dados vazios.
2. Verifique se o sistema permite o cadastro ou exibe uma mensagem de erro.

---

## Teste 7: Arquivo de Tripulação Vazio
**Objetivo:** Testar a leitura de um arquivo vazio.

### Entradas:
- O arquivo `tripulacao.dat` está vazio.

### Resultado Esperado:
A função `lerTripulacao()` deve retornar um vetor vazio, e a função `exibirTripulantes()` deve exibir "Nenhum tripulante encontrado."

### Passos:
1. Execute a função `exibirTripulantes()`.
2. Verifique a saída no console. A mensagem "Nenhum tripulante encontrado" deve ser exibida.

---

## Teste 8: Arquivo Corrompido ou Inexistente
**Objetivo:** Testar o comportamento do sistema quando o arquivo `tripulacao.dat` não existe ou está corrompido.

### Entradas:
- O arquivo `tripulacao.dat` não existe ou está corrompido.

### Resultado Esperado:
O sistema deve exibir uma mensagem de erro ao tentar ler ou escrever no arquivo (por exemplo, "Erro ao abrir o arquivo para leitura!" ou "Erro ao abrir o arquivo para escrita!").

### Passos:
1. Apague ou corrompa o arquivo `tripulacao.dat`.
2. Execute as funções `lerTripulacao()` ou `salvarTripulacao()` e verifique se o sistema exibe a mensagem de erro correta.

---

## Teste 9: Validação de Entradas no Cadastro de Tripulante
**Objetivo:** Testar se o sistema valida a entrada dos dados de cadastro.

### Entradas:
- Nome: "Ana"
- Cargo: "4" (inválido)
- Telefone: "abcdef"

### Resultado Esperado:
O sistema deve identificar que o cargo "4" é inválido e/ou o telefone contém caracteres não numéricos, e pedir ao usuário para corrigir a entrada.

### Passos:
1. Execute a função `cadastrarTripulante()` e insira entradas inválidas.
2. Verifique se o sistema fornece uma validação adequada ou solicita correção.
