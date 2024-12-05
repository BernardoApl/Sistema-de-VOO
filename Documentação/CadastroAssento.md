# Estrutura: CompanhiaAerea

Gerencia o cadastro de assentos para voos em uma companhia aérea.

## Atributos:
- `arquivoVoos` (string): Nome do arquivo binário que armazena os dados dos voos.
- `arquivoAssentos` (string): Nome do arquivo binário que armazena os dados dos assentos.

## Funções:

### `bool vooExiste(int codigo)`
Verifica se um voo com o código especificado existe.

#### Parâmetros:
- `codigo` (int): Código do voo a ser verificado.

#### Retorno:
- `bool`: `true` se o voo existe, `false` caso contrário.

#### Funcionamento:
- Lê o arquivo `voos.dat`.
- Percorre os registros para verificar se o código do voo está presente.
- Retorna `true` se o voo é encontrado; caso contrário, `false`.

---

### `void cadastrarAssentos()`
Cadastra assentos para um voo existente.

#### Funcionamento:
- Solicita ao usuário o código do voo e a quantidade de assentos.
- Verifica se o voo existe usando a função `vooExiste`.
- Cria objetos `Assento` com base na quantidade informada.
- Salva os assentos no arquivo `assentos.dat`.

---

### Função Principal: `int main()`
Gerencia o menu principal da aplicação.

#### Funcionamento:
- Exibe opções do menu para o usuário.
- Permite cadastrar assentos para um voo.
- Processa as entradas do usuário e invoca as funções correspondentes.
