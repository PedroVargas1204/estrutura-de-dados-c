# TAD Matriz — Unidade 5

## Enunciado
Faça um TAD que representa uma matriz de reais e que suporte as
operações mais comuns para matrizes como multiplicação, adição, etc.

## Status
Funcionando. Compila limpo com `-Wall -Werror`.

## Arquivos
- `matriz.h` — interface: a struct e os protótipos
- `matriz.c` — implementação: os algoritmos
- `cliente_matriz.c` — a main que usa o TAD
- `Makefile` — compilação

## Como rodar
No WSL Ubuntu:

```
make
./cliente_matriz
```

## Conceitos usados
- `struct` + `typedef`
- TAD: separação cliente / interface / implementação
- Include guard (`#ifndef`)
- Compilação separada e Makefile

## O que aprendi
- Guardar `linhas` e `colunas` dentro da struct resolve o problema
  de ter que passar `n` separado em toda função.
- Struct copia com `=` e pode ser retornada por `return`.
  Vetor não faz nenhuma das duas coisas.
- A versão dos slides não valida dimensões: somar uma 2x3 com uma
  2x2 produz números plausíveis e errados, sem nenhum aviso.
- Truque: usar `linhas = 0` (valor impossível) para sinalizar erro
  sem precisar de ponteiros.

## Dúvidas
- [ ] por que `matriz_invalida` é `static`?
- [ ] por que `sizeof(Matriz)` dá 80 KB mesmo para uma matriz 2x2?