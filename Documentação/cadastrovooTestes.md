
### Resultado Esperado:
O programa exibe a mensagem de erro corretamente e não tenta acessar dados inexistentes.

---

## 6. Teste de Arquivo Corrompido

### Objetivo:
Verificar o comportamento do programa ao tentar ler um arquivo corrompido.

### Procedimentos:
1. Crie um arquivo `voos.dat` manualmente com dados inválidos (não-binários ou incompletos).
2. Chame a função `lerVoos`.
3. Observe o comportamento do programa.

### Resultado Esperado:
O programa não trava e exibe uma mensagem de erro adequada.

---

## 7. Teste de Sobrescrita do Arquivo

### Objetivo:
Garantir que os novos voos são adicionados ao arquivo sem sobrescrever os existentes.

### Procedimentos:
1. Cadastre um voo.
2. Verifique se o voo está no arquivo.
3. Cadastre outro voo.
4. Leia os voos com `lerVoos` e verifique se ambos os voos estão na lista.

### Resultado Esperado:
O arquivo contém todos os voos cadastrados, sem sobrescrita.

---

## 8. Teste de Cadastro com Campos Vazios

### Objetivo:
Verificar como o programa lida com campos vazios no cadastro de voos.

### Procedimentos:
1. Cadastre um voo com um ou mais campos em branco.
2. Leia os voos do arquivo.
3. Verifique se os campos vazios foram gravados corretamente.

### Resultado Esperado:
Os campos vazios são gravados como strings vazias, sem erros.

---

## 9. Teste de Tarifa Negativa

### Objetivo:
Garantir que o sistema valida tarifas negativas no cadastro de voos.

### Procedimentos:
1. Cadastre um voo com uma tarifa negativa.
2. Leia os voos do arquivo.
3. Verifique se o programa rejeitou ou gravou a tarifa negativa.

### Resultado Esperado:
O programa deve impedir o cadastro de tarifas negativas (adicionar validação se necessário).

---

## 10. Teste de Dados Extensos

### Objetivo:
Verificar o comportamento do programa ao cadastrar voos com strings longas.

### Procedimentos:
1. Cadastre um voo com valores muito longos para os campos de origem, destino, etc.
2. Leia os voos do arquivo.
3. Verifique se os dados longos foram gravados e lidos corretamente.

### Resultado Esperado:
O programa deve gravar e recuperar os dados extensos corretamente.

---

## 11. Teste de Concorrência

### Objetivo:
Testar se o sistema funciona corretamente em cenários de múltiplos acessos ao arquivo.

### Procedimentos:
1. Simule dois processos cadastrando voos simultaneamente.
2. Verifique se os voos de ambos os processos aparecem no arquivo.

### Resultado Esperado:
Todos os voos devem ser salvos sem conflitos ou perda de dados.
