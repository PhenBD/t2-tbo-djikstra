# Projeto de Cálculo de RTT em Redes

Este projeto implementa um programa em C para calcular a inflação do RTT (Round-Trip Time) em redes. O programa lê dados de entrada de arquivos, cria uma estrutura de rede, calcula o RTT e escreve os resultados em arquivos de saída.

## Estrutura do Projeto

A estrutura do projeto é organizada da seguinte forma:

├── .gitignore
├── input/ 
│ ├── N10_S3_C3_M3.txt 
│ ├── N100_S20_C30_M5.txt 
│ ├── N1000_S50_C300_M10.txt 
│ ├── N10000_S50_C300_M10.txt 
│ └── N5.txt 
├── output/ 
│ └── (arquivos de saída)
├── headers/ 
│ ├── edge.h 
│ ├── forward_list.h 
│ ├── graph.h 
│ ├── item.h 
│ ├── pq.h 
│ ├── rede.h 
│ └── vertex.h 
├── objects/ 
│ ├── edge.o 
│ ├── forward_list.o 
│ ├── graph.o 
│ ├── item.o 
│ ├── main.o 
│ ├── pq.o 
│ ├── rede.o 
│ └── vertex.o 
├── source/
│ ├── edge.c 
│ ├── forward_list.c 
│ ├── graph.c 
│ ├── item.c 
│ ├── main.c
│ ├── pq.c
│ ├── rede.c
│ └── vertex.c
├── main.c 
├── makefile 
└── trab2

### Descrição dos Diretórios e Arquivos

- **.vscode/**: Configurações específicas do Visual Studio Code.
- **answer/**: Arquivos de solução gerados pelo programa.
- **headers/**: Arquivos de cabeçalho (.h) com definições de estruturas e funções.
- **input/**: Arquivos de entrada com dados da rede.
- **objects/**: Arquivos objeto (.o) gerados durante a compilação.
- **output/**: Arquivos de saída com os resultados calculados.
- **source/**: Arquivos fonte (.c) com a implementação das funções.
- **main.c**: Arquivo principal que contém a função `main`.
- **makefile**: Script de automação para compilar o projeto.
- **trab2**: Executável gerado após a compilação.

## Compilação e Execução

### Compilação

Para compilar o projeto, utilize o [`makefile`](command:_github.copilot.openRelativePath?%5B%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fhome%2Fpedro%2Ft2-tbo%2Fmakefile%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%5D "t2-tbo/makefile") fornecido. No terminal, execute o comando:

```sh
make
```

### Execução

Para executar o programa, utilize o seguinte comando:

```sh
./trab2 <caminho_para_arquivo_de_entrada> <caminho_para_arquivo_de_saida>
```

Por exemplo:

```sh
./trab2 input/N10_S3_C3_M3.txt output/N10_S3_C3_M3-solution.txt
```

## Funções Principais

### main
A função principal do programa. Lê os argumentos da linha de comando, abre os arquivos de entrada e saída, mede o tempo de execução das funções principais e imprime os resultados.

### rede_create_from_file

Cria uma estrutura de Rede a partir de um arquivo de entrada.
```C
Rede *rede_create_from_file(FILE *input);
```

### rede_calc_inflacao_RTT
Calcula a inflação do RTT para cada conexão na Rede e escreve os resultados em um arquivo de saída.

```C
void rede_calc_inflacao_RTT(Rede *r, FILE *output);
```

### rede_destroy
Libera a memória alocada para a estrutura de Rede.

```C
void rede_destroy(Rede *r);
```

## Contribuição
Se você deseja contribuir com este projeto, sinta-se à vontade para abrir um pull request ou relatar problemas na seção de issues.

## Licença
Este projeto está licenciado sob a MIT License.