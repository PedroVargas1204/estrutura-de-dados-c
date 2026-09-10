# TAD Matriz — Unidade 5

%c  →  1 caractere
%s  →  string
%d  →  inteiro
%f  →  número decimal

Uma associação visual:

C → Character → %c
S → String    → %s
F → Float     → %f
D → Decimal   → %d

gcc -std=c99 -Wall -Wvla -Werror -g -lm ex02.c -o ex02



📌 Strings — funções str
Função	O que faz	🧠 Macete
strlen()	tamanho	LENgth = comprimento
strcmp()	compara	CMP = compare
strcpy()	copia	CPY = copy
strcat()	junta	CAT = concatenate
strlen → "quantos?"
strcmp → "iguais?"
strcpy → "copia!"
strcat → "cola!"



📌 strcmp() — MUITO IMPORTANTE
strcmp(a, b)

   0       → iguais
  < 0      → a vem antes de b
  > 0      → a vem depois de b






📌 malloc × calloc × realloc — o lote

Função	Na analogia	🧠 Macete
malloc	lote usado, com entulho do morador anterior	Memory = só o espaço, sem faxina
calloc	lote limpo, entregue zerado	Clear = a imobiliária limpou
realloc	reforma: amplia ou te muda de lote	REdo = refaz o tamanho
free	devolve o lote à prefeitura	um só para os três

📌 Detalhes que caem em prova

Situação	🧠 Macete
malloc(5 * sizeof(int))	você diz o total: "20 metros"
calloc(5, sizeof(int))	você diz quantos × tamanho: "5 cômodos de 4m"
lote do malloc tem lixo	ler antes de gravar = ver entulho alheio
calloc custa a limpeza	vai mobiliar tudo? a faxina foi desperdício
realloc devolve endereço	pode ter te mudado de lote — sempre guarde o retorno
passar de v[4]	não tem cerca: você escreve no terreno do vizinho

⚠️ p = realloc(p, ...) — usar o endereço velho é apontar para um lote que não é mais seu.


📌 Operadores lógicos

Operador	O que faz	🧠 Macete
&&	E	os dois têm que ser verdade
||	OU	basta um ser verdade
!	NÃO	inverte o que veio
%	resto da divisão	resto 0 = divisão exata


⚠️ malloc usa *, calloc usa ,

📌 Ponteiros

Símbolo	O que faz	🧠 Macete
&x	pega o endereço	& = "onde mora"
*p	acessa o valor lá	* = "abre e vê"
v[i]	= *(v + i)	colchete é atalho
v	= &v[0]	nome de vetor já é endereço



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


