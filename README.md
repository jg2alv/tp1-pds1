# Ordenação de Sistemas Solares

Programa de linha de comando desenvolvido em C que lê dados astronômicos hierárquicos e classifica sistemas solares de acordo com uma sequência de critérios de comparação.

Este projeto foi desenvolvido individualmente para a disciplina **Programação e Desenvolvimento de Software I (PDS1)** da **Universidade Federal de Minas Gerais**, durante o segundo semestre de 2023.

## Visão geral

Cada sistema solar contém informações sobre sua estrela, seus planetas e suas luas. O programa processa essa estrutura hierárquica e ordena os sistemas do mais interessante para o menos interessante.

A classificação segue estes critérios, em ordem:

1. Maior raio da estrela
2. Maior quantidade de planetas
3. Maior raio de planeta
4. Maior quantidade total de luas
5. Maior raio de lua
6. Menor tempo de descoberta

Cada critério funciona como desempate para o critério anterior.

## Implementação

O projeto utiliza estruturas aninhadas em C para representar sistemas solares, planetas e luas:

- `Sistema` armazena o nome do sistema, o tempo de descoberta, o raio da estrela e seus planetas.
- `Planeta` armazena o nome do planeta, seu raio e suas luas.
- `Lua` armazena o nome da lua e seu raio.

A implementação também inclui:

- Alocação dinâmica de memória para os dados hierárquicos
- Leitura de dados a partir de arquivos
- Função de comparação com múltiplos critérios
- Funções auxiliares para o cálculo de métricas planetárias e lunares
- Algoritmo recursivo de ordenação in-place inspirado no Quicksort
- Rotina de particionamento baseada no último elemento de cada intervalo

As rotinas de ordenação e particionamento são denominadas `bromerosort` e `ritacao`, seguindo a terminologia utilizada no enunciado original do trabalho.

## Formato da entrada

O executável recebe inicialmente, por meio da entrada padrão, o caminho para o arquivo que será processado.

O arquivo indicado deve seguir esta estrutura hierárquica:

```text
N

T S R P

p r L

l q
```

Em que:

- `N` é a quantidade de sistemas solares.
- `T` é o tempo de descoberta do sistema.
- `S` é o nome do sistema.
- `R` é o raio de sua estrela.
- `P` é a quantidade de planetas do sistema.
- `p` é o nome de um planeta.
- `r` é o raio do planeta.
- `L` é a quantidade de luas associadas ao planeta.
- `l` é o nome de uma lua.
- `q` é o raio da lua.

O registro de planeta é repetido `P` vezes para cada sistema, enquanto o registro de lua é repetido `L` vezes para cada planeta.

O enunciado admite:

- Até 1.000.000 de sistemas solares
- Até 100 planetas por sistema
- Até 100 luas por planeta
- Nomes com até 100 caracteres

## Saída

O programa escreve o nome de um sistema solar por linha, ordenando-os do sistema mais interessante para o menos interessante.

```text
SistemaMaisInteressante
SegundoSistemaMaisInteressante
SistemaMenosInteressante
```

## Compilação

É necessário possuir um compilador C, como GCC ou Clang.

Utilizando GCC:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o ordenacao-sistemas-solares
```

Utilizando Clang:

```bash
clang -std=c11 -Wall -Wextra -pedantic main.c -o ordenacao-sistemas-solares
```

## Execução

Passe o caminho do arquivo de entrada para o programa por meio da entrada padrão:

```bash
echo "caminho/para/o/arquivo-de-entrada" | ./ordenacao-sistemas-solares
```

Também é possível executar o programa e, em seguida, digitar o caminho do arquivo:

```bash
./ordenacao-sistemas-solares
```

O repositório inclui arquivos compactados contendo casos de entrada e suas respectivas saídas esperadas.

## Contexto acadêmico

Este projeto explora conceitos fundamentais da programação em C, incluindo:

- Estruturas e modelos de dados aninhados
- Ponteiros
- Alocação dinâmica de memória
- Manipulação de arquivos
- Recursão
- Funções de comparação personalizadas
- Algoritmos de ordenação in-place