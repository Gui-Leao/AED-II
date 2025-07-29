# Mini SGBD com B-Tree e B+ Tree

Este projeto implementa um mini banco de dados em C, utilizando B-Tree e B+ Tree como índices para registros de alunos.

## Como funciona

- Os registros de alunos (id, nome, idade) são armazenados em um único arquivo: `DB/alunos.txt`.
- O índice pode ser uma B-Tree tradicional ou uma B+ Tree, escolhida ao iniciar o programa.
- Suporta comandos para inserir, buscar, imprimir, consultar por intervalo de id (range) e por idade (age).

## Como compilar

No terminal, execute:

```
make
```

## Como rodar

```
./programa
```
Ao iniciar, escolha o tipo de árvore: `btree` ou `bplustree`.

## Comandos disponíveis

- `insert` — Insere um novo aluno (id, nome, idade)
- `search <id>` — Busca aluno pelo id
- `print` — Imprime a árvore por níveis
- `range <start> <end>` — Imprime registros no intervalo de ids
- `age <min_age>` — Imprime registros com idade acima do valor
- `in-order` — Imprime ids em ordem (apenas B-Tree)

