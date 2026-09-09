# MC-202 — Estrutura de Dados em C
# Material de estudo consolidado — Unidades 2 a 5

> **Disciplina:** MC-202 (Estruturas de Dados), Unicamp — Prof. Rafael C. S. Schouery.
> **Origem:** transformação didática dos slides "Curso de C, Partes 1 a 4" (unidades 2, 3, 4 e 5).
> **Método:** cada conceito segue o caminho *ideia simples → explicação técnica → analogia com correspondência explícita → código linha a linha → o que acontece na memória → complexidade → erros comuns*, fechando com uma lista "o que eu preciso saber deste tópico".
> **Verificação:** todos os códigos citados foram compilados com `gcc -std=c99 -Wall -Werror -Wvla -g` e executados. As saídas, medições (`sizeof`, endereços, contagens de iteração) e bugs apontados são resultados reais, não suposições.

---

## ⚠️ Leia isto primeiro (contexto para retomar o estudo)

**O que este documento cobre:** a linguagem C — desde a sintaxe básica até `struct` e Tipos Abstratos de Dados.

**O que este documento AINDA NÃO cobre**, porque não apareceu no material da disciplina até aqui:

- ponteiros e alocação dinâmica (`malloc`, `calloc`, `realloc`, `free`)
- listas encadeadas, pilhas, filas, árvores, grafos
- recursão, algoritmos de busca e de ordenação
- análise assintótica formal (notação Big-O como teoria)

Complexidades aparecem aqui de forma **aplicada** — O(1) para acesso a vetor, O(n) para percurso, O(n²) para matriz, O(n³) para multiplicação de matrizes — mas sem o formalismo, que vem depois.

**A tabela comparativa de estruturas de dados** (vetor × lista encadeada × pilha × fila × árvore) **não existe neste documento**, e isso é deliberado: até a Unidade 5 a única estrutura apresentada foi o vetor (e a matriz). Escrevê-la agora seria inventar conteúdo que a disciplina ainda não deu.

**O fio condutor do curso**, que atravessa todas as partes: *vetores em C têm tamanho fixo e não sabem o próprio tamanho.* Praticamente tudo que vem depois — `'\0'`, structs com membro `linhas`, TADs, e mais adiante ponteiros e listas — são respostas a essa limitação.

---

## Índice

### PARTE 1 — Fundamentos da linguagem (Unidade 2, slides 1–18)
- 0. O que este material é (e o que não é)
- 1. Por que C? Compilado × interpretado; as flags do `gcc`
- 2. Tipagem estática
- 3. Tipos de dados e o tipo `int`; operadores; `a++` × `++a`
- 4. Funções, `void` e protótipos
- 5. Blocos, chaves e o ponto e vírgula
- 6. Condicionais; `=` × `==`
- 7. Variáveis e o **lixo de memória**
- 8. Laços `while`, `do…while`, `for`
- 9. A função `main`
- 10. `printf`
- 11. **`scanf` e o operador `&` — primeira aula de endereços de memória**
- 12. O programa completo e o `#include`
- 13. Refatoração e formas compactas
- 14. Exercício: número primo (com 3 bugs analisados)
- Consolidação: tabela Python → C; os 8 erros mais comuns

### PARTE 2 — Vetores, escopo e passagem de parâmetros (Unidade 2, slides 19–34)
- 15. Vetores: memória contígua, acesso O(1)
- 16. Vetores como parâmetros; por que o `n` é obrigatório
- 17. **Acesso fora dos limites** — segfault ou corrupção silenciosa
- 18. Escopo: variáveis globais, locais e *shadowing*
- 19. 🔑 **A grande revelação:** por que uma função modifica um vetor mas não um `int`
- 20. Exercício: produto de Hadamard e produto escalar
- Consolidação: complexidades, vantagens e desvantagens do vetor

### PARTE 3 — Reais, casting, `#define` e matrizes (Unidade 3)
- 21. Método Babilônico de raiz quadrada
- 22. `float` × `double`; **por que nunca comparar reais com `==`**
- 23. O código em C e o `do…while` (com 2 bugs comprovados)
- 24. A diretiva `#define`
- 25. Conversão de tipos e casting; `(int)` trunca
- 26. **A tabela de divisão inteira × real** (ouro para prova)
- 27. Matrizes: ordem *row-major* e a fórmula do endereço
- 28. As três funções de matriz; multiplicação O(n³)
- 29. Exercício: aplicação financeira
- 30. Exercício: matriz de permutação

### PARTE 4 — `char`, ASCII e strings (Unidade 4)
- 31. O tipo `char` e a tabela ASCII (com 1 erro factual dos slides)
- 32. Cifra de César; aritmética modular (com 2 bugs comprovados)
- 33. Operadores lógicos e curto-circuito
- 34. 🔑 **Strings: vetores de `char` terminados em `'\0'`**
- 35. Busca de padrão com coringa; `%s` × `fgets`; o problema do `\n` no buffer
- 36. A biblioteca `string.h`; **por que não se compara string com `==`**
- 37. Tipos inteiros: `short`, `long`, `unsigned`
- 38. Exercícios: copiar, reverter e comparar strings
- **🎓 Fechamento do bloco "linguagem C": mapa mental, 15 pegadinhas, e 20 QUESTÕES COM GABARITO COMENTADO**

### PARTE 5 — `struct`, `typedef` e TAD (Unidade 5)
- 39. O problema do centroide
- 40. `struct`: agrupando dados; **por que `a = b` funciona com struct e não com vetor**
- 41. `typedef`
- 42. Números complexos e a reflexão sobre **abstração**
- 43. 🔑 **Tipo Abstrato de Dados:** cliente, interface, implementação
- 44. Arquivos `.h` e `.c`
- 45. Compilação separada e Makefile
- 46. Vantagens do TAD e o `#ifndef`
- 47. 🎯 **Exercício: TAD de Matrizes** — solução dos slides, análise crítica e versão melhorada

### APÊNDICE — Leitura linha a linha do TAD Matriz
- A1 a A8. Explicação detalhada de `matriz.h`, `matriz.c` e `cliente_matriz.c`

---


<div style="page-break-after: always"></div>

# MC-202 — Curso de C, Parte 1
## Aula completa e comentada — **PARTE 1: A linguagem C — Fundamentos**

> Material-base: slides "MC-202 — Curso de C — Parte 1", Rafael C. S. Schouery (Unicamp).
> Esta parte cobre os slides 1 a 18 da Unidade 2.

---

# 0. Antes de tudo: o que ESTE material é (e o que ele não é)

Você me pediu para dar atenção especial a `struct`, ponteiros, `malloc`/`free`, listas encadeadas, pilhas, filas, árvores, recursão, ordenação e Big-O.

**Aviso importante e honesto: nada disso está nestes slides.**

Este é o slide-deck de *abertura* da disciplina. Ele é uma **ponte de Python para C** — ensina a sintaxe e o modelo mental da linguagem para quem já sabe programar em Python. Estrutura de dados propriamente dita vem nas unidades seguintes.

O que os slides realmente cobrem:

| Bloco | Assuntos |
|---|---|
| Fundamentos da linguagem | compilado × interpretado, tipagem estática, tipos, funções, protótipos, blocos, `;` |
| Controle de fluxo | `if`/`else`/`else if`, `while`, `do...while`, `for` |
| Variáveis | declaração, inicialização, **lixo de memória** |
| Entrada e saída | `printf`, `scanf`, o operador `&`, `#include <stdio.h>` |
| Compilação | `gcc` e suas flags |
| Vetores | declaração, tamanho fixo, acesso, passagem para funções, acesso inválido |
| Escopo | variáveis globais, locais, sobreposição de escopo |
| Passagem de parâmetros | por cópia (escalares) × comportamento de vetores |

Existe **um único momento** em que os slides tocam em ponteiros: o `&` do `scanf`. Os slides dizem "por enquanto, não se esqueça do `&`" e adiam a explicação. **Eu não vou adiar** — vou te explicar endereço de memória agora, porque sem isso o `&` vira decoreba, e decoreba desmorona na prova.

Isso conecta direto com o que você vai precisar depois: ponteiros, `malloc` e listas encadeadas são todos construídos em cima do conceito de *endereço de memória*. Quem entende endereço aqui, na Parte 1, tem a vida muito mais fácil na unidade de ponteiros.

---

# 1. Por que C? Compilado × Interpretado

## 1.1 A ideia simples

Você escreve código em uma linguagem que humanos leem. O computador só entende números binários (instruções de máquina). Alguém precisa traduzir. Existem duas estratégias de tradução:

- **Interpretar**: traduzir *enquanto executa*, linha por linha, toda vez que o programa roda.
- **Compilar**: traduzir *uma vez só*, antes, gerando um arquivo pronto. Depois é só executar.

Python interpreta. C compila.

## 1.2 Analogia: o intérprete e o livro traduzido

Imagine que você escreveu um livro em português e quer que um japonês leia.

- **Estratégia intérprete (Python):** você contrata um tradutor simultâneo. Toda vez que o japonês quer ler o livro, o tradutor senta ao lado dele e vai traduzindo em voz alta, frase por frase. Vantagem: você pode mudar o livro a qualquer momento e o tradutor lê a versão nova. Desvantagem: é lento (traduz tudo de novo toda vez) e o japonês *sempre* precisa do tradutor por perto.
- **Estratégia compilador (C):** você contrata um tradutor profissional que traduz o livro inteiro, uma vez, e imprime uma edição em japonês. Vantagem: o japonês lê rápido e **não precisa mais do tradutor**. Desvantagem: se você mudar uma vírgula no original, precisa mandar traduzir e imprimir tudo de novo.

**Correspondência com o conceito técnico:**

| Analogia | Conceito |
|---|---|
| Livro em português | Seu código-fonte (`programa.c`) |
| Tradutor profissional | Compilador (`gcc`) |
| Edição impressa em japonês | Executável (`./programa`) |
| Tradutor simultâneo | Interpretador (`python3`) |
| "Não precisa mais do tradutor" | O executável roda sozinho |
| Erro de gramática pego na tradução | **Erro de compilação** |

Note o último item, que é o mais importante na prática: o tradutor profissional lê o livro inteiro antes de imprimir e **reclama de todos os erros de gramática antes de gerar o produto final**. O tradutor simultâneo só descobre o erro quando chega naquela frase.

É por isso que em C um erro de sintaxe na linha 300 impede o programa *inteiro* de rodar, mesmo que a linha 300 nunca fosse executada. Em Python, o mesmo erro só apareceria se a execução chegasse lá.

## 1.3 Para que isso serve na prática

C é usado onde **desempenho e controle sobre a memória** importam: sistemas operacionais, drivers, bancos de dados, jogos, sistemas embarcados. E é a linguagem clássica para ensinar estrutura de dados justamente porque ela **não esconde a memória de você**. Em Python, quando você faz `lista.append(x)`, alguém realoca memória por você. Em C, esse "alguém" vai ser você. É por isso que a disciplina é em C.

## 1.4 Compilando (slide 15)

```
gcc -std=c99 -Wall -Wvla -Werror -g -lm programa.c -o programa
```

Depois: `./programa`

Cada flag, e por que ela existe:

| Flag | O que faz | Por que a disciplina usa |
|---|---|---|
| `-std=c99` | Usa o padrão C99 da linguagem | Permite `for (int i = 0; ...)` — declarar a variável dentro do `for`. No C89 isso era proibido. |
| `-Wall` | Liga muitos avisos (*warnings*) | Pega bugs prováveis: variável não usada, variável usada sem inicializar, `%d` com argumento errado |
| `-Wvla` | Avisa sobre *variable length arrays* | VLA é `int v[n];` com `n` variável. A disciplina não quer que você use isso |
| `-Werror` | **Transforma todo warning em erro** | Te obriga a corrigir os avisos em vez de ignorar. Duro, mas salva você de bugs |
| `-g` | Inclui informação de depuração | Permite usar `gdb` (depurador) e `valgrind` (detector de erro de memória). Você vai amar o `valgrind` quando chegar em `malloc` |
| `-lm` | Liga a biblioteca matemática | Necessário para `sqrt`, `pow`, `sin`… |
| `-o programa` | Define o nome do executável | Sem isso, o gcc gera um arquivo chamado `a.out` |

> **Detalhe (não é essencial, mas é bom saber):** por convenção, `-lm` deveria vir *depois* do arquivo `.c`, porque o linker resolve símbolos na ordem em que os argumentos aparecem. Em sistemas Linux modernos (glibc ≥ 2.34) a libm foi fundida na libc e a ordem não importa mais, então a linha do slide funciona. Mas se um dia você ver `undefined reference to 'sqrt'`, tente mover o `-lm` para o final.

## ✅ O que eu preciso saber deste tópico

- Explicar a diferença entre compilar e interpretar, e uma consequência prática de cada uma.
- Saber que o compilador vê o programa **inteiro** antes de gerar o executável, e por isso erros de sintaxe são pegos antes da execução.
- Saber o que é `gcc`, o que é o `.c`, o que é o executável, e o papel do `-o`.
- Saber que `-Werror` significa que qualquer warning **impede** a compilação.

---

# 2. Tipagem estática: a diferença mental mais importante entre Python e C

## 2.1 A ideia simples

Em Python:

```python
x = 5
x = "agora sou texto"   # perfeitamente legal
```

Em C, isso é **impossível**. Uma variável em C nasce com um tipo e morre com o mesmo tipo. Você declara `int x;` e `x` será um inteiro para sempre.

## 2.2 A explicação técnica

Os slides dizem:

> A linguagem C é **estaticamente tipada**: os tipos das variáveis estão definidos no código. Ao contrário do Python, que é **dinamicamente tipado** — objetos têm tipo, mas variáveis não.

Essa última frase é a chave, e vale destrinchar porque é sutil:

- **Em Python**, a variável é apenas um *nome* que aponta para um objeto na memória. O objeto `5` sabe que é um inteiro; o nome `x` não sabe de nada. Reatribuir `x` só faz o nome apontar para outro objeto.
- **Em C**, a variável **é** um pedaço de memória com tamanho fixo, reservado no momento da declaração, e o tipo determina (a) quantos bytes são reservados e (b) como esses bytes devem ser interpretados.

## 2.3 Analogia: o nome no objeto × o compartimento etiquetado

**Python** é como um armário de objetos com **etiquetas adesivas**. Cada objeto tem sua própria natureza (um número, um texto). A etiqueta `x` é um post-it que você cola no objeto. Quer que `x` seja outra coisa? Descole o post-it e cole em outro objeto. O post-it não tem forma nem tamanho.

**C** é como uma **caixa de ferramentas com compartimentos moldados**. Quando você declara `int x;`, você reserva um compartimento com exatamente 4 bytes, com formato de inteiro. Não dá para colocar um texto ali — não cabe e não tem o formato certo. O compartimento *é* a variável.

**Correspondência:**

| Analogia | Conceito |
|---|---|
| Post-it colado em um objeto | Nome de variável em Python (uma referência) |
| Compartimento moldado de 4 bytes | Variável `int` em C (memória de verdade) |
| Tamanho e formato do compartimento | O tipo, decidido em tempo de compilação |
| Trocar o post-it de objeto | Reatribuir variável em Python |
| Não conseguir encaixar a peça errada | Erro de tipo em C, pego pelo compilador |

Essa analogia vai ser **reaproveitada em toda a disciplina**. Um vetor será uma fileira de compartimentos idênticos e grudados. Um ponteiro será um compartimento que guarda o *número do endereço* de outro compartimento. Guarde-a.

## 2.4 Por que isso é bom (e não só uma chatice)

1. **Velocidade.** O compilador já sabe que `a + b` são dois inteiros de 4 bytes, então gera direto a instrução de soma de inteiros. Python precisa, em tempo de execução, descobrir o tipo de `a`, o tipo de `b`, e decidir qual soma usar.
2. **Erros pegos cedo.** Passar um texto para uma função que espera um inteiro vira erro de compilação, não um crash em produção.
3. **Controle de memória.** Você sabe exatamente quantos bytes cada coisa ocupa. Isso é *pré-requisito* para tudo que vem na disciplina.

## ✅ O que eu preciso saber deste tópico

- Definir tipagem estática × dinâmica, e dar um exemplo em código de cada.
- Explicar por que "em Python objetos têm tipo, mas variáveis não".
- Explicar que em C o tipo determina **quantos bytes** a variável ocupa.

---

# 3. Tipos de dados e o tipo `int`

## 3.1 Os tipos básicos (slide 4)

Os slides citam `int`, `float`, `double`, `char`. Vale a tabela completa dos que você usará:

| Tipo | Guarda | Tamanho típico | Formato no `printf` |
|---|---|---|---|
| `int` | Inteiro | 4 bytes (32 bits) | `%d` |
| `float` | Real, precisão simples | 4 bytes | `%f` |
| `double` | Real, precisão dupla | 8 bytes | `%lf` (leitura) / `%f` (impressão) |
| `char` | Um caractere / inteiro pequeno | 1 byte | `%c` |
| `long` / `long long` | Inteiro grande | 8 bytes | `%ld` / `%lld` |

## 3.2 O tipo `int` em detalhe (slide 5)

Os slides dizem:

> O tipo `int` armazena números inteiros, usualmente de 32 bits, i.e., números em [−2³¹, 2³¹ − 1], mas depende do compilador…

Isso está **correto e bem colocado**. Vale expandir o "depende do compilador", porque é um ponto que cai em prova conceitual:

- O padrão C **não fixa** o tamanho de `int`. Ele garante apenas um mínimo de 16 bits.
- Na esmagadora maioria das máquinas que você vai usar (Linux/Windows/macOS x86-64), `int` tem 32 bits.
- 32 bits com sinal ⇒ faixa de **−2 147 483 648 a 2 147 483 647**.

**Isto é radicalmente diferente de Python.** Em Python, `2**200` funciona. Em C, se você ultrapassa 2 147 483 647 em um `int`, ocorre **overflow**: o valor "dá a volta" e vira negativo. Ninguém te avisa. O programa não quebra — ele só passa a produzir números errados.

Repare que isso já é um problema no código de exemplo dos próprios slides: a função `potencia(a, b)` calcula aᵇ em um `int`. Com `a = 2, b = 40` o resultado correto é 1 099 511 627 776, que não cabe em 32 bits, e o programa imprime lixo silenciosamente. Não é um erro dos slides (é um programa didático), mas é um comportamento que você precisa reconhecer.

## 3.3 Operações (slide 5)

| Operação | Significado |
|---|---|
| `a + b`, `a - b`, `a * b` | soma, subtração, multiplicação |
| `a / b` | **divisão inteira** — `8 / 5` é `1` |
| `a % b` | resto da divisão — `8 % 5` é `3` |
| `a += b` | o mesmo que `a = a + b` (idem `-=`, `*=`, `/=`, `%=`) |
| `a++` / `++a` | incrementa `a` em 1 |
| `a--` / `--a` | decrementa `a` em 1 |

### ⚠️ Armadilha nº 1 dos slides: `a++` e `++a` **não** são a mesma coisa

Os slides afirmam:

> `a++` — o mesmo que `a += 1`
> `++a` — o mesmo que `a += 1`

**Como comando isolado numa linha, isso é verdade.** `a++;` e `++a;` fazem exatamente a mesma coisa. Mas a afirmação é **incompleta e enganosa**, porque `a++` e `++a` são *expressões*, e como expressões elas têm valores diferentes:

- `a++` (**pós-incremento**): devolve o valor **antigo** de `a`, e depois incrementa.
- `++a` (**pré-incremento**): incrementa **primeiro**, e devolve o valor **novo**.

Eu compilei e rodei para você confirmar:

```c
int a = 5, x;
x = a++;    /* x vale 5, a vale 6 */

a = 5;
x = ++a;    /* x vale 6, a vale 6 */
```

**Regra prática para lembrar:** o `++` "acontece" na ordem em que está escrito. `a++` → primeiro entrega o `a`, depois soma. `++a` → primeiro soma, depois entrega o `a`.

**Isso cai em prova.** É clássico dar um trecho com `v[i++]` ou `printf("%d", a++)` e pedir a saída.

### ⚠️ Armadilha nº 2: divisão inteira e o sinal

`8 / 5` é `1` em C, não `1.6`. Se ambos os operandos são inteiros, a divisão é inteira e a parte fracionária é **descartada**. Para obter `1.6` você precisa que pelo menos um lado seja real: `8.0 / 5`.

E aqui está uma pegadinha que os slides não mencionam e que morde quem vem de Python — **com números negativos, C e Python discordam**:

| Expressão | C (C99) | Python 3 |
|---|---|---|
| `-8 / 5` | `-1` | `-2` |
| `-8 % 5` | `-3` | `2` |

Motivo: C trunca **em direção ao zero** (−1,6 → −1). Python arredonda **para baixo** (−1,6 → −2). Consequentemente o resto tem o sinal do dividendo em C, e o sinal do divisor em Python.

**Consequência prática que já derrubou muita gente:** em C, `x % 2 == 1` **não** é um teste confiável de "x é ímpar", porque para `x = -7` o resultado é `-1`, não `1`. Use `x % 2 != 0`.

## ✅ O que eu preciso saber deste tópico

- Citar os tipos básicos e o que cada um guarda.
- Saber a faixa de um `int` de 32 bits e o que é overflow.
- Explicar por que `8 / 5` dá `1` e como obter `1.6`.
- **Explicar a diferença entre `a++` e `++a` com um exemplo.**
- Saber que `x % 2 == 1` é um teste ruim para ímpar em C.

---

# 4. Funções em C

## 4.1 A ideia simples

Uma função é um pedacinho de programa com nome, que recebe dados, faz algo e devolve um resultado. Isso é igual em Python e C. **O que muda é que em C você precisa declarar os tipos de tudo**: o tipo de cada parâmetro e o tipo do retorno.

## 4.2 O código do slide 4, lado a lado

**Python:**
```python
def maximo(a, b):
    if a > b:
        return a
    else:
        return b
```

**C:**
```c
int maximo(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}
```

## 4.3 Explicação linha por linha do código em C

**Linha 1:** `int maximo(int a, int b) {`

Vamos dissecar cada pedaço, da esquerda para a direita:

| Pedaço | Nome | Significado |
|---|---|---|
| `int` (o primeiro) | **tipo de retorno** | "esta função devolve um inteiro" |
| `maximo` | **nome** da função | como você a chamará |
| `(` … `)` | lista de parâmetros | o que a função recebe |
| `int a` | 1º parâmetro | uma variável local chamada `a`, do tipo `int` |
| `int b` | 2º parâmetro | uma variável local chamada `b`, do tipo `int` |
| `{` | abertura de bloco | começo do corpo da função |

O formato geral, como diz o slide:

```
tipo nome(tipo parametro1, tipo parametro2, ...)
```

⚠️ Erro clássico de iniciante: escrever `int maximo(int a, b)`. **Cada parâmetro precisa do seu próprio tipo**, mesmo que sejam iguais. O correto é `int maximo(int a, int b)`.

**Linha 2:** `if (a > b) {`
- Os parênteses ao redor da condição são **obrigatórios** em C (em Python são opcionais).
- Não há `:` no fim. O bloco é aberto com `{`.

**Linha 3:** `return a;`
- Devolve o valor de `a` e **encerra a função imediatamente**.
- Termina com `;`.
- O tipo do que você devolve precisa ser compatível com o tipo declarado no cabeçalho (`int`).

**Linhas 4–6:** `} else { return b; }`
- Repare que o `}` que fecha o `if` e o `else` ficam na mesma linha: `} else {`. É só convenção de estilo; poderia estar em linhas separadas.

**Linha 7:** `}` — fecha o bloco da função.

## 4.4 O tipo `void`

Aparece no slide 24. Quando a função **não devolve nada**, o tipo de retorno é `void`:

```c
void imprime_positivos(int lista[], int n) {
  ...
}
```

É o equivalente a uma função Python que só faz `print` e não tem `return`. Dentro de uma função `void` você pode usar `return;` sozinho (sem valor) para sair mais cedo, mas nunca `return algumacoisa;`.

## 4.5 Protótipos de funções (slide 7)

### A ideia simples

O compilador C lê o arquivo **de cima para baixo, uma vez só**. Se na linha 10 você chama `potencia(...)` mas a função `potencia` só é definida na linha 50, o compilador na linha 10 ainda não sabe que ela existe — e reclama.

O **protótipo** resolve isso: é uma "promessa" antecipada de que a função vai existir.

### Analogia: o índice do livro

Imagine que você escreve um manual técnico. No capítulo 2 você quer escrever "veja o procedimento de calibração", mas esse procedimento só aparece no capítulo 9. Se o leitor lê estritamente de cima para baixo e nunca ouviu falar de "calibração", ele trava.

A solução é colocar um **índice no começo**: "Capítulo 9 — Procedimento de calibração: recebe uma temperatura e uma pressão, devolve um fator de correção." Agora, quando o leitor chega no capítulo 2, ele já sabe que aquilo existe e qual é seu formato — mesmo sem saber ainda *como* funciona.

**Correspondência:**

| Analogia | Conceito |
|---|---|
| Índice no começo do livro | Protótipo, no topo do arquivo |
| A entrada do índice ("recebe X, devolve Y") | Assinatura: tipo de retorno, nome, tipos dos parâmetros |
| O capítulo 9 completo | A definição (implementação) da função |
| Leitor que lê estritamente de cima para baixo | O compilador |

### A sintaxe

Como diz o slide: é a função **sem o bloco**, com a linha terminando em `;`

```c
int maximo(int a, int b);        /* protótipo — note o ; e a ausência de { } */
```

Exemplo completo mostrando por que é útil:

```c
#include <stdio.h>

int maximo(int a, int b);        /* PROTÓTIPO: a promessa */

int main() {
  printf("%d\n", maximo(3, 7));  /* funciona! o compilador já conhece maximo */
  return 0;
}

int maximo(int a, int b) {       /* DEFINIÇÃO: a promessa cumprida */
  if (a > b) return a;
  else return b;
}
```

Sem o protótipo da linha 3, este programa não compilaria com `-Wall -Werror`.

### Detalhe (não essencial): nomes nos parâmetros

No protótipo, os *nomes* dos parâmetros são opcionais — só os tipos importam. Estas duas linhas são equivalentes para o compilador:

```c
int maximo(int a, int b);
int maximo(int, int);
```

Use a primeira forma; ela documenta melhor.

### Por que isso importa de verdade

Protótipos são a base dos **arquivos de cabeçalho** (`.h`). Quando você escreve `#include <stdio.h>`, está literalmente incluindo um arquivo cheio de protótipos — inclusive o de `printf` e `scanf`. É assim que o compilador sabe que essas funções existem sem ver o código delas.

## ✅ O que eu preciso saber deste tópico

- Escrever o cabeçalho de uma função em C dado "recebe isto, devolve aquilo".
- Saber que **cada parâmetro precisa do seu tipo**.
- Explicar o que é `void` e quando usar.
- Explicar o que é um protótipo, por que ele existe, e escrever um.
- Saber que `#include <stdio.h>` traz protótipos.

---

# 5. Blocos e o ponto e vírgula (slide 6)

## 5.1 A ideia simples

Em Python, o que define "estas linhas pertencem ao `if`" é a **indentação**. Em C, é o par de **chaves `{ }`**.

## 5.2 O ponto crucial

> Em C, a indentação **não é obrigatória**. Mas é boa prática de programação. — (slide 6)

Isto é literalmente verdade, e é fonte de bugs. O compilador C ignora completamente espaços e quebras de linha. Este código monstruoso compila e funciona:

```c
int maximo(int a,int b){if(a>b){return a;}else{return b;}}
```

Como o compilador não liga para a indentação, **a indentação pode mentir para você**. Este é o bug clássico:

```c
if (x > 0)
  printf("positivo\n");
  printf("com certeza\n");     /* ← ESTA LINHA SEMPRE EXECUTA */
```

A indentação sugere que as duas linhas estão dentro do `if`. Elas não estão. Sem `{ }`, o `if` controla **apenas o próximo comando**. Em Python esse código faria o que parece; em C, não.

**Regra de sobrevivência para iniciante: sempre use `{ }`, mesmo com uma linha só.** Você pode relaxar essa regra quando tiver experiência (e os próprios slides relaxam, no slide 16).

## 5.3 O ponto e vírgula

> A maioria das linhas em C são terminadas em `;` — blocos são exceção.

Detalhando quando **usa** e quando **não usa**:

| Usa `;` | Não usa `;` |
|---|---|
| `int x = 5;` | após `}` que fecha um bloco |
| `return 0;` | após `if (x > 0)` |
| `printf("oi\n");` | após `for (...)` ou `while (...)` que abre bloco |
| `x = x + 1;` | após `#include <stdio.h>` (é diretiva de pré-processador) |
| protótipo: `int f(int);` | |
| `do { ... } while (cond);` ← **este leva `;`!** | |

### ⚠️ O bug mais cruel de C para iniciantes: o `;` sobrando

```c
for (int i = 0; i < 10; i++);      /* ← olhe o ; no final */
  printf("%d\n", i);
```

Aquele `;` é um **comando vazio**. Ele vira o corpo do `for`. Resultado: o laço roda 10 vezes fazendo absolutamente nada, e depois o `printf` executa **uma única vez**. O programa compila sem erro. Você vai olhar para essa linha por vinte minutos sem ver o problema. O mesmo vale para `if (x > 0);` e `while (cond);`.

## ✅ O que eu preciso saber deste tópico

- Saber que blocos em C são `{ }` e que indentação é apenas visual.
- Saber que um `if`/`for`/`while` sem `{ }` controla **apenas o próximo comando**.
- Saber onde vai e onde não vai `;`, incluindo o caso especial do `do...while`.
- Reconhecer o bug do `;` sobrando depois de `for`/`if`/`while`.

---

# 6. Condicionais (slide 8)

## 6.1 As três formas

```c
/* Forma 1 */              /* Forma 2 */              /* Forma 3 */
if (condicao) {            if (condicao) {            if (condicao) {
  ...                        ...                        ...
}                          } else {                   } else if (condicao) {
                             ...                        ...
                           }                          } else {
                                                        ...
                                                      }
```

Como diz o slide: pode haver **quantos `else if` forem necessários**, e o `else` final é **opcional**.

## 6.2 Diferenças em relação a Python

| Python | C |
|---|---|
| `elif` | `else if` (duas palavras) |
| `if x > 0:` | `if (x > 0) {` — parênteses obrigatórios |
| `and`, `or`, `not` | `&&`, `\|\|`, `!` |
| `if 0 < x < 10:` funciona | **não funciona como você espera** |

## 6.3 ⚠️ A pegadinha número 1 de todo C: `=` versus `==`

```c
if (x = 5) { ... }     /* ATRIBUI 5 a x, e a condição é sempre verdadeira */
if (x == 5) { ... }    /* COMPARA x com 5 — é isto que você quer */
```

Em C, **atribuição é uma expressão** cujo valor é o valor atribuído. Então `x = 5` vale 5, e como em C qualquer valor diferente de zero é "verdadeiro", o `if` sempre entra — e ainda destrói o valor de `x` no processo.

Boa notícia: `-Wall` avisa disso (`suggest parentheses around assignment used as truth value`), e com `-Werror` vira erro. É mais uma razão para usar as flags da disciplina.

## 6.4 ⚠️ Não existe booleano de verdade (no C básico)

Em C99 puro, não há `True`/`False` como em Python. A regra é:

- **Zero é falso.**
- **Qualquer outra coisa é verdadeira** (`1`, `-3`, `42`, tudo).

Por isso a função `eh_primo` do slide 18 devolve `int`: `0` para "não" e `1` para "sim". Essa é a convenção idiomática em C.

> Detalhe: existe `#include <stdbool.h>` com `bool`, `true` e `false`, mas os slides não usam e provavelmente sua disciplina não vai usar.

Consequência prática: estas duas linhas fazem a mesma coisa.

```c
if (eh_primo(n) == 1)    /* como está no slide */
if (eh_primo(n))         /* idiomático em C */
```

## 6.5 ⚠️ Comparação encadeada não funciona

```c
if (0 < x < 10)     /* NÃO faz o que você pensa */
```

C avalia da esquerda para a direita: `0 < x` produz `0` ou `1`; depois compara `0 < 10` ou `1 < 10` — ambos verdadeiros. **A condição é sempre verdadeira.** O correto:

```c
if (0 < x && x < 10)
```

## ✅ O que eu preciso saber deste tópico

- Escrever `if`, `if/else` e cadeias de `else if` em C.
- Saber que os parênteses da condição são obrigatórios.
- Explicar a diferença entre `=` e `==` e por que `if (x = 5)` é sempre verdadeiro.
- Saber que zero é falso e não-zero é verdadeiro.
- Saber que `0 < x < 10` não funciona em C.

---

# 7. Variáveis: declaração e o perigo do lixo (slide 9)

## 7.1 A ideia simples

Em Python, uma variável nasce no momento em que você atribui algo a ela. Em C, você precisa **avisar antes** que ela vai existir, e dizer de que tipo ela é.

```c
int i;                  /* declara i, do tipo int, SEM valor definido */
int i, produto = 1;     /* declara i e produto; inicializa produto com 1 */
```

## 7.2 O que acontece na memória — o ponto mais importante do slide

O slide encerra com um aviso em negrito:

> **Importante: variáveis não inicializadas começam com lixo!**

Isto é absolutamente central e merece explicação de verdade, porque é a origem de uma classe inteira de bugs.

### Analogia: o quarto de hotel

Pense na memória RAM como um **hotel gigantesco**. Quando seu programa declara `int i;`, ele faz check-in e recebe um quarto de 4 bytes.

Agora: quando você entra num quarto de hotel, a arrumadeira já passou por lá? Em Python, sim — o quarto é sempre entregue limpo e arrumado (valores inicializados). Em C, **não existe arrumadeira**. Você recebe o quarto exatamente como o hóspede anterior deixou.

Se o hóspede anterior era outra função que guardou o número `31415` ali, seu `i` vai valer `31415`. Se ninguém usou aquele quarto ainda, pode valer `0` — por acaso. E amanhã, com outro programa rodando no computador, pode valer outra coisa completamente diferente.

**Correspondência:**

| Analogia | Conceito |
|---|---|
| Hotel | Memória RAM |
| Quarto de 4 bytes | O espaço reservado para um `int` |
| Check-in | Declaração da variável |
| Bagunça do hóspede anterior | **Lixo** — bits deixados por dados antigos |
| "Não existe arrumadeira" | C não zera a memória por questão de desempenho |
| Arrumar o quarto ao entrar | **Inicializar** a variável |

### Por que isso é tão perigoso

Porque o programa **não quebra**. Ele roda. Só que dá respostas erradas — e, pior, dá respostas *diferentes* a cada execução, ou funciona na sua máquina e falha na do professor. É o tipo de bug que consome uma tarde inteira.

Veja o que aconteceria se o slide 9 tivesse escrito `potencia` sem inicializar:

```c
int potencia(int a, int b) {
  int i, produto;          /* ← produto contém LIXO */
  for (i = 0; i < b; i++) {
    produto = a * produto; /* lixo × a = lixo */
  }
  return produto;          /* devolve lixo */
}
```

É por isso que o código correto do slide escreve `int i, produto = 1;`. O `= 1` não é decoração: é o que torna a função correta.

**Regra prática: inicialize toda variável na declaração, a menos que tenha um motivo claro para não fazê-lo.** `-Wall` ajuda (`-Wmaybe-uninitialized`), mas o compilador nem sempre consegue detectar.

## 7.3 Onde declarar

O slide diz "fazemos isso no início da função". Isso é herança do C89, onde era **obrigatório**. Com `-std=c99` (que a disciplina usa), você pode declarar em qualquer lugar — inclusive dentro do `for`, como os próprios slides fazem a partir do slide 16:

```c
for (int i = 0; i < b; i++)     /* legal em C99, ilegal em C89 */
```

Declarar a variável no menor escopo possível é considerado boa prática moderna.

## ✅ O que eu preciso saber deste tópico

- Declarar variáveis com e sem inicialização, e várias na mesma linha.
- **Explicar o que é "lixo" e por que ele existe** (a analogia do hotel).
- Explicar por que um programa com variável não inicializada pode "funcionar" e mesmo assim estar errado.
- Saber que `for (int i = 0; ...)` exige C99.

---

# 8. Laços: `while`, `do...while` e `for` (slide 10)

## 8.1 A ideia simples

O slide começa com uma frase que resume tudo:

> Em C, não há `for ... in`.

Em Python você diz "para cada elemento **desta coleção**". Em C você diz "**enquanto** esta condição for verdadeira". C é mais primitivo e mais explícito: você mesmo controla o contador.

## 8.2 As três formas

### `while` — testa antes

```c
while (condicao) {
  ...
}
```

Testa a condição. Se verdadeira, executa o corpo, e volta a testar. Se a condição já é falsa na primeira vez, **o corpo nunca executa**.

### `do...while` — testa depois

```c
do {
  ...
} while (condicao);
```

Executa o corpo, **depois** testa. Ou seja: **o corpo executa no mínimo uma vez**, sempre.

⚠️ Note o `;` obrigatório no final. É o único bloco em C que termina com ponto e vírgula.

**Quando usar `do...while`?** Quando a ação precisa acontecer pelo menos uma vez para você ter o que testar. O caso clássico é validação de entrada:

```c
int idade;
do {
  printf("Digite sua idade (0 a 120): ");
  scanf("%d", &idade);
} while (idade < 0 || idade > 120);
```

Você precisa ler antes de poder verificar se o valor é válido.

### `for` — o laço de contagem

```c
for (inicializacao; condicao; atualizacao) {
  ...
}
```

## 8.3 A ordem exata de execução do `for` — isto cai em prova

O slide anota que a inicialização acontece **antes de testar a condição**. Vamos ao passo a passo completo, porque a ordem é o que confunde:

```c
for (i = 0; i < b; i++) {
  produto = a * produto;
}
```

| Passo | O que acontece | Quantas vezes |
|---|---|---|
| 1 | `i = 0` (**inicialização**) | uma única vez, no começo |
| 2 | testa `i < b` (**condição**) | antes de cada iteração |
| 3 | se falsa → sai do laço | — |
| 4 | se verdadeira → executa o **corpo** | |
| 5 | executa `i++` (**atualização**) | ao fim de cada iteração |
| 6 | volta ao passo 2 | |

**A atualização acontece DEPOIS do corpo, não antes.** Isso significa que na primeira iteração `i` vale `0`, não `1`. Errar isso é a causa nº 1 de erros de contagem.

Trace completo com `b = 3`:

| Iteração | `i` no início do corpo | `i < 3`? | corpo roda? | `i` após `i++` |
|---|---|---|---|---|
| 1ª | 0 | sim | sim | 1 |
| 2ª | 1 | sim | sim | 2 |
| 3ª | 2 | sim | sim | 3 |
| 4ª | 3 | **não** | não | — |

Total: **3 execuções do corpo**, com `i` valendo 0, 1 e 2. Exatamente o que `range(3)` faz em Python. E note: quando o laço termina, `i` vale `3`, não `2`.

## 8.4 A equivalência com Python

```python
for i in range(b):        # Python
```
```c
for (int i = 0; i < b; i++)    /* C */
```

Guarde esta tradução — ela é a que você mais vai usar. E note que `for` é apenas um `while` disfarçado:

```c
int i = 0;                    /* inicialização */
while (i < b) {               /* condição */
  produto = a * produto;      /* corpo */
  i++;                        /* atualização */
}
```

Os dois códigos são equivalentes. O `for` só agrupa as três partes numa linha, o que é mais legível e mais difícil de esquecer o `i++`.

### ⚠️ O laço infinito por atualização esquecida

```c
int i = 0;
while (i < 10) {
  printf("%d\n", i);
  /* esqueceu o i++ */
}
```

`i` nunca muda, a condição nunca fica falsa, o programa imprime `0` para sempre. Esse erro é muito mais comum com `while` do que com `for` — outro motivo para preferir `for` quando você está contando.

## ✅ O que eu preciso saber deste tópico

- Escrever os três laços com a sintaxe correta (incluindo o `;` do `do...while`).
- Explicar a diferença entre `while` e `do...while` em termos de "quantas vezes no mínimo".
- **Descrever a ordem exata de execução das três partes do `for`.**
- Traduzir `for i in range(n)` para C.
- Reescrever um `for` como `while` e vice-versa.

---

# 9. A função `main` (slide 11)

## 9.1 A ideia simples

Em Python, o interpretador executa o arquivo de cima para baixo. Em C, **a execução sempre começa pela função `main`**, esteja ela onde estiver no arquivo.

## 9.2 Analogia: a porta de entrada do prédio

Um prédio pode ter dezenas de salas (funções), em qualquer andar, em qualquer ordem. Mas ele tem **uma única portaria**, e todo visitante entra por ali. O sistema operacional é o visitante; a `main` é a portaria.

**Correspondência:** as salas são as funções; a portaria é a `main`; o visitante é o sistema operacional que executa seu programa; e o "obrigado, tudo certo" que você diz ao sair é o `return 0`.

## 9.3 O código

```c
int main() {
  int a, b, maior, pot;
  printf("Entre com a e b\n");
  scanf("%d %d", &a, &b);
  maior = maximo(a, b);
  pot = potencia(a, b);
  printf("Maior: %d\n", maior);
  printf("a^b: %d\n", pot);
  return 0;
}
```

**Linha a linha:**

1. `int main() {` — a `main` **sempre devolve `int`**. Não invente `void main()`; é tecnicamente incorreto e alguns compiladores reclamam.
2. `int a, b, maior, pot;` — declara as quatro variáveis que serão usadas. Nenhuma inicializada, mas todas receberão valor antes de serem lidas — `a` e `b` pelo `scanf`, `maior` e `pot` por atribuição.
3. `printf(...)` — imprime a instrução para o usuário.
4. `scanf("%d %d", &a, &b);` — lê dois inteiros (detalhado na seção 11).
5–6. Chama as funções e guarda os retornos.
7–8. Imprime os resultados.
9. `return 0;` — devolve 0 ao sistema operacional.

## 9.4 O valor de retorno da `main`

> Sempre devolve um `int`. Se devolver 0 significa que não houve erros. Valores diferentes indicam o erro que ocorreu. — (slide 11)

Esse `int` não é decorativo: é o **código de saída** do processo, e o sistema operacional o usa de verdade. No terminal:

```
$ ./programa
$ echo $?
0
```

É assim que scripts shell encadeiam comandos (`comando1 && comando2` só roda o segundo se o primeiro devolveu 0). Provavelmente o corretor automático da sua disciplina também verifica isso — um programa que devolve valor diferente de 0 pode ser marcado como falha mesmo tendo impresso a saída certa.

> Detalhe: `int main()` e `int main(void)` são ambos aceitos. `int main(int argc, char *argv[])` é a forma que recebe argumentos de linha de comando — você vai ver isso mais adiante no curso.

## ✅ O que eu preciso saber deste tópico

- Saber que a execução começa pela `main`, independente da posição no arquivo.
- Saber que `main` devolve `int` e que `0` significa sucesso.
- Escrever um esqueleto de programa C de cabeça.

---

# 10. Saída: a função `printf` (slide 12)

## 10.1 A ideia simples

`printf` = "print formatted". Você dá a ela um **molde de texto** com buracos, e os valores para preencher os buracos.

```c
printf("Maior: %d\n", maior);
```

O molde é `"Maior: %d\n"`. O buraco é `%d`. O valor que preenche é `maior`.

## 10.2 Analogia: o formulário com lacunas

Pense num documento padrão de cartório:

> "Eu, ______, portador do RG ______, declaro ______."

O texto fixo é sempre o mesmo; as lacunas são preenchidas na hora, **na ordem em que aparecem**. A string de formato é o documento; os `%d`/`%f`/`%s` são as lacunas; os argumentos depois da vírgula são os valores, entregues na ordem.

## 10.3 As regras (todas do slide 12)

- **`%d` significa substituir por um inteiro.** Existem outras substituições: `%f`, `%s`, etc.
- Recebe um parâmetro com a string a ser impressa, **e um parâmetro adicional para cada `%`**.
- **A substituição é feita da esquerda para a direita** na string.
- **Não adiciona `\n` automaticamente** — ao contrário do `print` de Python.

### Os especificadores mais usados

| Especificador | Tipo | Exemplo |
|---|---|---|
| `%d` | `int` | `printf("%d", 42)` → `42` |
| `%f` | `float` / `double` | `printf("%f", 3.14)` → `3.140000` |
| `%.2f` | com 2 casas decimais | `printf("%.2f", 3.14159)` → `3.14` |
| `%c` | `char` | `printf("%c", 'A')` → `A` |
| `%s` | string | `printf("%s", "oi")` → `oi` |
| `%%` | um `%` literal | `printf("100%%")` → `100%` |

### Múltiplas substituições

```c
printf("Maximo: %d\na^b: %d\n", maximo(a, b), potencia(a, b));
```

Da esquerda para a direita: o primeiro `%d` recebe `maximo(a, b)`, o segundo recebe `potencia(a, b)`. O `\n` no meio quebra a linha entre os dois.

## 10.4 ⚠️ Erros comuns

**1. Esquecer o `\n`.** Python: `print("oi")` já quebra linha. C: `printf("oi")` não. Sua saída sai toda grudada e o corretor automático rejeita.

**2. Descasar o tipo do especificador com o argumento.**

```c
double x = 3.5;
printf("%d\n", x);    /* ERRADO — %d espera int, recebeu double */
```

Isso é **comportamento indefinido**. O programa pode imprimir qualquer coisa. `-Wall` avisa (`format '%d' expects argument of type 'int'`), e com `-Werror` vira erro de compilação — mais um ponto para as flags da disciplina.

**3. Esquecer um argumento.**

```c
printf("%d %d\n", a);    /* dois buracos, um valor só */
```

O segundo `%d` vai imprimir lixo da pilha. Também pego pelo `-Wall`.

## ✅ O que eu preciso saber deste tópico

- Usar `printf` com zero, um e vários especificadores.
- Saber a correspondência básica de `%d`, `%f`, `%c`, `%s`.
- Saber que `printf` **não** quebra linha sozinho.
- Saber que o número e o tipo dos argumentos devem casar com os `%`.

---

# 11. Entrada: `scanf` e o operador `&` — sua primeira aula de ponteiros

Este é o ponto onde os slides dizem "veremos mais sobre isso em breve; por enquanto, não se esqueça do `&`". **Vou explicar agora**, porque você pediu que eu não deixasse pré-requisitos para trás — e porque este conceito é a base de toda a disciplina.

## 11.1 Pré-requisito: o que é um endereço de memória

### A ideia simples

A memória do computador é uma **fila gigantesca de caixinhas numeradas**, cada uma com 1 byte. A numeração começa em 0 e vai até bilhões. O número de uma caixinha é o seu **endereço**.

Quando você declara `int a;`, o compilador reserva 4 caixinhas consecutivas e anota: "a variável `a` mora a partir do endereço 1000".

```
Endereço:  ...  1000  1001  1002  1003  1004  1005  1006  1007  ...
           ┌──────────────────────────┬──────────────────────────┐
Conteúdo:  │      variável  a         │      variável  b         │
           └──────────────────────────┴──────────────────────────┘
```

Então toda variável tem **duas coisas** associadas a ela, e distinguir as duas é o coração de C:

| | Nome | Como se escreve | Exemplo de valor |
|---|---|---|---|
| **O que ela guarda** | valor | `a` | `7` |
| **Onde ela mora** | endereço | `&a` | `1000` |

O operador `&` significa, literalmente: **"me dê o endereço de"**.

### Analogia: a casa e o bilhete com o endereço

Pense em `a` como uma **casa** e no valor dela como o **móvel dentro da casa**.

- Falar `a` é falar sobre o *móvel* — "o que tem dentro da casa?" → `7`.
- Falar `&a` é entregar um **bilhete com o endereço** da casa — "Rua da Memória, nº 1000".

Agora, a pergunta decisiva: **você quer que um pedreiro troque o móvel da sua casa. Você entrega a ele uma foto do móvel, ou o endereço da casa?**

Óbvio: o endereço. Se você entregar só a foto (o valor), ele pode olhar, admirar, até fazer uma cópia — mas nunca vai conseguir mexer na *sua* casa.

**Correspondência:**

| Analogia | Conceito |
|---|---|
| A casa | A variável (o espaço na memória) |
| O móvel dentro | O valor guardado |
| Falar "o móvel" | Usar `a` |
| O bilhete com o endereço | `&a` — o endereço da variável |
| O pedreiro | A função `scanf` |
| Trocar o móvel | Escrever um novo valor na variável |

## 11.2 Agora sim: por que `scanf` precisa do `&`

```c
scanf("%d %d", &a, &b);
```

`scanf` é uma função que precisa **modificar** as variáveis `a` e `b` — ela lê números do teclado e tem que colocá-los lá dentro.

Se você escrevesse `scanf("%d", a)`, estaria entregando à função apenas **uma cópia do valor atual** de `a` (que é lixo). A função receberia esse lixo, não teria como saber onde `a` mora, e não conseguiria mudar nada. Você entregou a foto do móvel.

Escrevendo `scanf("%d", &a)`, você entrega o **endereço** de `a`. Agora `scanf` sabe exatamente em qual caixinha da memória depositar o número lido. Você entregou o endereço da casa.

**E é exatamente por isso que `printf` NÃO usa `&`:**

```c
printf("%d\n", a);      /* sem & — printf só quer LER o valor */
scanf("%d", &a);        /* com & — scanf precisa ESCREVER na variável */
```

Guarde essa dupla lado a lado. Ela responde de uma vez a pergunta "quando usa `&`?": **quem só lê não precisa de endereço; quem escreve precisa.**

> **Este é o embrião de todo o resto da disciplina.** "Passar o endereço para que a função possa modificar" é exatamente o mecanismo de ponteiros, e é o que vai permitir construir listas encadeadas, árvores e tudo mais. Se você entendeu esta seção, você já entendeu metade de ponteiros.

## 11.3 As regras do `scanf` (slide 13)

- **A string diz quantos valores serão lidos e os seus tipos.** `"%d %d"` = dois inteiros.
- **Precisa passar o endereço da variável usando o operador `&`.**
- **Ignora espaços em branco, tabs e quebras de linha.** Isso significa que `scanf("%d %d", &a, &b)` lê os dois números tanto se você digitar `3 7` quanto se digitar `3`, Enter, `7`, Enter.
- Os slides avisam: "veremos alguns casos onde isso não acontece". O caso é `%c` (leitura de caractere), que **não** pula espaços em branco — mas isso é assunto de outra aula.

### Especificadores no `scanf`

| Tipo da variável | `scanf` | ⚠️ cuidado |
|---|---|---|
| `int` | `%d` | |
| `float` | `%f` | |
| `double` | **`%lf`** | ⚠️ diferente do `printf`, que usa `%f` |
| `char` | `%c` | não pula espaços |

O par `double` é a pegadinha: no `printf` você escreve `%f`, no `scanf` você escreve `%lf`. Usar `%f` para ler um `double` corrompe a memória.

## 11.4 ⚠️ Erros comuns

**1. Esquecer o `&`.** O erro mais comum de todos.

```c
scanf("%d", a);     /* ERRADO */
```
Resultado típico: **segmentation fault**. O `scanf` interpreta o lixo de `a` como se fosse um endereço, e tenta escrever num lugar aleatório da memória. `-Wall` avisa (`format '%d' expects argument of type 'int *'`).

**2. Colocar `&` onde não deve.** Em vetores, `scanf("%d", &lista[i])` está certo (é o endereço do elemento `i`), mas `scanf("%s", &nome)` para uma string está errado — strings já são endereços. Você vai ver isso na aula de vetores/strings.

**3. Não verificar o retorno.** Os slides não mencionam, mas `scanf` devolve **quantos itens conseguiu ler**. Se o usuário digitar `abc` quando você espera `%d`, o `scanf` devolve `0`, a variável fica com lixo, e o programa segue alegremente com dados inválidos. Em código de produção você escreveria:

```c
if (scanf("%d", &n) != 1) {
  printf("Entrada invalida\n");
  return 1;
}
```

Para os exercícios da disciplina, isso normalmente não é cobrado. Mas saiba que existe.

## ✅ O que eu preciso saber deste tópico

- **Explicar o que é um endereço de memória.**
- Explicar a diferença entre `a` e `&a`.
- **Explicar por que `scanf` precisa de `&` e `printf` não.** (Esta pergunta é quase garantida em prova.)
- Saber que `double` usa `%lf` no `scanf` mas `%f` no `printf`.
- Saber o que provavelmente acontece se você esquecer o `&`.

---

# 12. O programa completo e o `#include` (slide 14)

```c
#include <stdio.h>

int maximo(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int potencia(int a, int b) {
  int i, produto = 1;
  for (i = 0; i < b; i++) {
    produto = a * produto;
  }
  return produto;
}

int main() {
  int a, b, maior, pot;
  printf("Entre com a e b\n");
  scanf("%d %d", &a, &b);
  maior = maximo(a, b);
  pot = potencia(a, b);
  printf("Maior: %d\n", maior);
  printf("a^b: %d\n", pot);
  return 0;
}
```

## 12.1 O `#include`

> No começo, colocamos as bibliotecas a serem usadas. Usamos `stdio.h` por causa de `printf` e `scanf`. — (slide 14)

`#include <stdio.h>` é uma **diretiva de pré-processador** (por isso o `#`, e por isso **não leva `;`**). Ela significa, literalmente: "copie e cole o conteúdo do arquivo `stdio.h` aqui".

E o que tem dentro do `stdio.h`? **Protótipos** — inclusive os de `printf` e `scanf`. Ou seja: exatamente o conceito da seção 4.5, aplicado em escala. É o "índice do livro" da biblioteca padrão.

`stdio` = **st**andar**d i**nput/**o**utput. Outras bibliotecas que você usará:

| Biblioteca | Para quê |
|---|---|
| `stdio.h` | `printf`, `scanf`, arquivos |
| `stdlib.h` | `malloc`, `free`, `rand`, `exit` — **você vai viver aqui** |
| `string.h` | `strlen`, `strcpy`, `strcmp` |
| `math.h` | `sqrt`, `pow`, `sin` (precisa do `-lm`) |

## 12.2 Por que a ordem das funções importa aqui

Repare que `maximo` e `potencia` estão definidas **antes** da `main`, que é quem as chama. Não é coincidência: é isso que evita a necessidade de protótipos neste arquivo. Se `main` viesse primeiro, você precisaria dos protótipos no topo.

Existem duas convenções de organização, ambas válidas:

- **Sem protótipos:** funções auxiliares primeiro, `main` por último. (É o que os slides fazem.)
- **Com protótipos:** protótipos no topo, `main` primeiro, implementações depois. (Mais comum em projetos grandes, porque coloca o que interessa no topo.)

## 12.3 Trace completo da execução

Com entrada `a = 3`, `b = 4`:

| Passo | O que acontece | Estado |
|---|---|---|
| 1 | SO chama `main` | `a`,`b`,`maior`,`pot` = lixo |
| 2 | `printf` imprime a instrução | — |
| 3 | `scanf` lê e **escreve nos endereços** de `a` e `b` | `a=3`, `b=4` |
| 4 | chama `maximo(3, 4)` — recebe **cópias** de `a` e `b` | dentro: `a=3`, `b=4` |
| 5 | `3 > 4` é falso → `return 4` | `maior = 4` |
| 6 | chama `potencia(3, 4)` | dentro: `produto=1`, `i=0` |
| 7 | i=0: `produto = 3*1 = 3` | `produto=3` |
| 8 | i=1: `produto = 3*3 = 9` | `produto=9` |
| 9 | i=2: `produto = 3*9 = 27` | `produto=27` |
| 10 | i=3: `produto = 3*27 = 81` | `produto=81` |
| 11 | i=4: `4 < 4` falso → sai, `return 81` | `pot = 81` |
| 12 | imprime `Maior: 4` e `a^b: 81` | — |
| 13 | `return 0` | processo termina com código 0 |

**Preste atenção no passo 4.** Quando você chama `maximo(a, b)`, a função recebe **cópias** dos valores. Ela não tem acesso às variáveis `a` e `b` da `main` — ela tem suas próprias variáveis `a` e `b`, com os mesmos valores. Isso se chama **passagem por valor**, e é o assunto principal do slide 31, que veremos na Parte 2.

## ✅ O que eu preciso saber deste tópico

- Escrever um programa C completo do zero, com `#include`, funções e `main`.
- Explicar o que `#include` faz e por que ele não leva `;`.
- Saber que funções chamadas precisam ser definidas antes, ou ter protótipo.
- Fazer o trace de um programa simples, acompanhando os valores.

---

# 13. Refatoração e "açúcar sintático" (slide 16)

O slide 16 reescreve o mesmo programa de forma mais enxuta:

```c
int maximo(int a, int b) {
  if (a > b)
    return a;
  else
    return b;
}

int potencia(int a, int b) {
  int produto = 1;
  for (int i = 0; i < b; i++)
    produto *= a;
  return produto;
}

int main() {
  int a, b;
  printf("Entre com a e b\n");
  scanf("%d %d", &a, &b);
  printf("Maximo: %d\na^b: %d\n", maximo(a, b), potencia(a, b));
  return 0;
}
```

## 13.1 O que mudou, e o que aprender de cada mudança

**1. Chaves omitidas em blocos de uma linha.**
> Quando o bloco de um `if`, `else`, `for` ou `while` tiver apenas uma linha, podemos omitir o `{` e `}` — (slide 16)

Correto. Mas lembre da seção 5: isso é exatamente o que causa o bug da indentação mentirosa. Como aluno, **use as chaves**; entenda que a omissão é legal para conseguir ler código dos outros.

**2. `produto *= a` em vez de `produto = a * produto`.**
Mesma coisa, mais curto. Os operadores compostos (`+=`, `-=`, `*=`, `/=`, `%=`) são preferidos por serem menos propensos a erro de digitação.

**3. `int i` declarado dentro do `for`.**
Recurso do C99. A vantagem real: `i` **deixa de existir** quando o laço termina, então você não pode usá-lo por engano depois, e pode reaproveitar o nome em outro `for`.

**4. `printf` imprimindo resultados de expressões diretamente.**
> O `printf` pode imprimir os resultados de expressões — (slide 16)

As variáveis `maior` e `pot` sumiram; as chamadas de função foram para dentro do `printf`. Menos linhas, menos variáveis.

## 13.2 ⚠️ Um detalhe avançado que vale conhecer

Nesta linha:

```c
printf("Maximo: %d\na^b: %d\n", maximo(a, b), potencia(a, b));
```

A **ordem de avaliação dos argumentos de uma função é não especificada em C**. O compilador pode chamar `potencia` antes de `maximo`, se quiser.

Aqui não faz diferença nenhuma, porque nenhuma das duas funções tem efeito colateral (não modificam nada fora delas, não imprimem). Mas se você escrever algo como `printf("%d %d", f(), g())` onde `f` e `g` alteram uma mesma variável global, **o resultado pode variar entre compiladores**. É um detalhe, não um ponto essencial — mas é o tipo de coisa que aparece em questão de múltipla escolha "capciosa".

## ✅ O que eu preciso saber deste tópico

- Reconhecer e escrever as formas compactas (`*=`, chaves omitidas, `int i` no `for`).
- Saber que omitir chaves é legal mas arriscado, e por quê.
- Saber que `printf` aceita qualquer expressão como argumento.

---

# 14. Exercício resolvido: número primo (slides 17–18)

**Enunciado:** escreva um programa em C que verifica se um número é primo.

**Solução dos slides:**

```c
#include <stdio.h>

int eh_primo(int n) {
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int main() {
    int n, i, primo = 1;
    printf("Digite um número: ");
    scanf("%d", &n);
    if (eh_primo(n) == 1)
        printf("O número %d é primo.\n", n);
    else
        printf("O número %d não é primo.\n", n);
    return 0;
}
```

## 14.1 Como a função funciona

A ideia: um número é primo se **nenhum** número entre 2 e n−1 divide ele.

| Linha | O que faz |
|---|---|
| `int eh_primo(int n)` | devolve `int` usado como booleano: `1` = primo, `0` = não primo |
| `for (int i = 2; i < n; i++)` | testa todos os candidatos a divisor, de 2 até n−1 |
| `if (n % i == 0)` | `n % i` é o resto. Resto zero ⇒ `i` divide `n` |
| `return 0;` | achou divisor ⇒ **não é primo**, e sai IMEDIATAMENTE |
| `return 1;` | o laço terminou sem achar nenhum divisor ⇒ **é primo** |

O detalhe elegante aqui é o `return 0` **dentro** do laço. Assim que um divisor é encontrado, a função encerra — não faz sentido continuar procurando. Esse padrão ("saída antecipada") é muito comum e vale internalizar.

O `return 1` só é alcançado se o `for` rodou até o fim sem nunca entrar no `if`. Ou seja: "se eu cheguei até aqui, é porque não achei nada".

## 14.2 🔴 Problemas neste código — três coisas que eu preciso apontar

Você me pediu para avisar quando algo nos slides estiver incompleto ou incorreto. Aqui há três problemas reais.

### Problema 1: o código NÃO COMPILA com as flags da própria disciplina

Eu compilei este código com exatamente a linha de compilação do slide 15. Resultado:

```
error: unused variable 'primo' [-Werror=unused-variable]
   11 |     int n, i, primo = 1;
error: unused variable 'i' [-Werror=unused-variable]
cc1: all warnings being treated as errors
```

As variáveis `i` e `primo` são declaradas na `main` e **nunca usadas**. Provavelmente sobraram de uma versão anterior do código, em que o teste de primalidade era feito dentro da `main`. Com `-Wall -Werror`, isso é erro fatal de compilação.

**Correção:** `int n;` — só isso.

**Lição real:** variável não usada é um *cheiro* de código morto ou de bug (você quis usar uma coisa e usou outra). É por isso que `-Wall` reclama.

### Problema 2: a função responde errado para n ≤ 1

Eu rodei a função. Os resultados:

| `n` | `eh_primo(n)` devolve | Correto? |
|---|---|---|
| `1` | `1` (primo) | ❌ **1 não é primo, por definição** |
| `0` | `1` (primo) | ❌ |
| `-7` | `1` (primo) | ❌ |

Por quê? Para `n = 1`, o `for` começa com `i = 2` e testa `2 < 1`, que é falso. O laço **nunca executa**. A função cai direto no `return 1`. O mesmo vale para 0 e negativos.

**Correção:**

```c
int eh_primo(int n) {
    if (n < 2) return 0;              /* trata o caso base */
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}
```

**Lição real:** sempre teste seu código com os **casos de borda** — o menor valor possível, zero, negativo, e o valor onde o laço não executa. É onde os bugs se escondem, e é o que corretores automáticos testam.

### Problema 3: é ineficiente (e isto é sua primeira aula de complexidade)

O laço vai de 2 até n−1. Para `n = 1 000 003` (que é primo), ele faz **um milhão** de iterações.

Mas há uma observação matemática que muda tudo: **se `n` tem um divisor maior que √n, então ele necessariamente tem também um divisor menor que √n.** (Porque se `n = p × q` e `p > √n`, então `q = n/p < √n`.)

Logo, basta testar até √n:

```c
int eh_primo(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)    /* i*i <= n  equivale a  i <= sqrt(n) */
        if (n % i == 0)
            return 0;
    return 1;
}
```

Para `n = 1 000 003`, isso cai de 1 000 001 iterações para **1 000**. Mil vezes mais rápido.

> Uso `i * i <= n` em vez de `i <= sqrt(n)` porque `sqrt` trabalha com números reais (imprecisão de ponto flutuante) e exige `#include <math.h>` mais a flag `-lm`. A multiplicação de inteiros é exata e mais rápida.

**Isto é Big-O na prática, sem o nome ainda.** A versão dos slides é **O(n)**; a versão melhorada é **O(√n)**. Quando você chegar na aula de complexidade, guarde este exemplo — ele mostra que os dois programas fazem *a mesma coisa*, mas um é dramaticamente melhor porque o **número de operações cresce mais devagar** conforme a entrada cresce.

## 14.3 Versão final recomendada

```c
#include <stdio.h>

int eh_primo(int n) {
    if (n < 2)
        return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int main() {
    int n;
    printf("Digite um numero: ");
    scanf("%d", &n);
    if (eh_primo(n))
        printf("O numero %d eh primo.\n", n);
    else
        printf("O numero %d nao eh primo.\n", n);
    return 0;
}
```

Mudanças em relação ao slide: trata `n < 2`, para em √n, remove variáveis não usadas, e usa `if (eh_primo(n))` de forma idiomática.

## ✅ O que eu preciso saber deste tópico

- Escrever uma função que devolve `0`/`1` como booleano.
- Usar `%` para testar divisibilidade.
- Usar `return` dentro de um laço para saída antecipada.
- **Saber que 1 não é primo e testar casos de borda.**
- Explicar por que basta testar divisores até √n.

---

# 📌 Consolidação da Parte 1

## Tabela Python → C (memorize esta)

| Conceito | Python | C |
|---|---|---|
| Definir função | `def f(a, b):` | `int f(int a, int b) {` |
| Bloco | indentação após `:` | `{ }` |
| Fim de comando | quebra de linha | `;` |
| Declarar variável | automático ao atribuir | `int x;` — obrigatório antes de usar |
| Valor inicial | sempre definido | **lixo**, se você não inicializar |
| Condicional | `elif` | `else if` |
| Operadores lógicos | `and`, `or`, `not` | `&&`, `\|\|`, `!` |
| Laço de contagem | `for i in range(n):` | `for (int i = 0; i < n; i++)` |
| Laço condicional | `while cond:` | `while (cond) { }` |
| Laço "pelo menos uma vez" | não existe | `do { } while (cond);` |
| Imprimir | `print(x)` — quebra linha | `printf("%d\n", x)` — não quebra |
| Ler | `x = int(input())` | `scanf("%d", &x)` |
| Início da execução | topo do arquivo | função `main` |
| Booleano | `True` / `False` | `0` é falso, resto é verdadeiro |
| Divisão | `/` real, `//` inteira | `/` é inteira se ambos forem `int` |
| Tamanho de inteiro | ilimitado | ~32 bits, com **overflow** |
| Executar | `python3 prog.py` | `gcc prog.c -o prog` e `./prog` |

## Os 8 erros que mais derrubam iniciantes

1. **`=` em vez de `==`** no `if`.
2. **Esquecer o `&`** no `scanf` → segmentation fault.
3. **Usar variável não inicializada** → lixo, resultado errado sem aviso.
4. **`;` sobrando** depois de `for`/`if`/`while` → laço vazio.
5. **Achar que a indentação define o bloco** → só a primeira linha entra no `if`.
6. **Esperar `8 / 5 == 1.6`** → divisão inteira dá `1`.
7. **Esquecer o `\n`** no `printf`.
8. **Confundir `a++` com `++a`** dentro de uma expressão.

## O que é essencial × o que é detalhe

**Essencial (vai cair):** tipagem estática; declaração e inicialização; lixo de memória; ordem de execução do `for`; `printf` × `scanf` e o **porquê** do `&`; `main` e `return 0`; blocos e `;`; divisão inteira e `%`.

**Detalhe (bom saber, difícil de cair):** ordem de avaliação de argumentos; posição do `-lm`; `int main(void)` × `int main()`; nomes opcionais em protótipos.

**Provável em prova prática:** escrever um programa completo do zero com função auxiliar, `scanf`, laço e `printf` formatado.

---

# ➡️ Próxima parte

**Parte 2 — Vetores, Escopo e Passagem de Parâmetros** (slides 19 a 34):

- Vetores em C: declaração, tamanho fixo, representação **contígua** na memória
- Por que `lista[i]` funciona, e a relação entre vetor e endereço
- Passar vetores para funções: por que **não se passa o tamanho junto** e por que `n` é sempre necessário
- Funções `void` que modificam vetores (`le_vetor`)
- **Acesso fora dos limites**: segmentation fault, off-by-one, e por que C não te protege
- Variáveis globais × locais, e sobreposição de escopo
- **O grande mistério do slide 31:** por que `soma_um(x)` não muda `x`, mas `soma_um(v, 5)` muda o vetor inteiro — a resposta é a peça que falta de ponteiros
- Exercício resolvido: Produto de Hadamard e produto escalar

E, ao final da Parte 2, o pacote completo que você pediu: resumo geral, mapa mental textual, tabela comparativa, lista de prioridades para prova, pegadinhas e **20 questões de revisão com gabarito comentado**.


<div style="page-break-after: always"></div>

# MC-202 — Curso de C, Parte 1 (Unidade 2)
## Aula completa e comentada — **PARTE 2: Vetores, Escopo e Passagem de Parâmetros**

> Cobre os slides 19 a 34 de "MC-202 — Curso de C — Parte 1".
> Continuação direta da Parte 1 (fundamentos da linguagem).
> **Esta é a parte mais importante do material até aqui** — é onde nasce o conceito que sustenta toda a disciplina.

---

# 15. Vetores: a primeira estrutura de dados

## 15.1 O problema motivador (slides 19–20)

**Enunciado:** ler 10 números inteiros, armazená-los e imprimir os positivos.

Em Python:

```python
print("Digite 10 números")
lista = []
for i in range(10):
    lista.append(int(input()))
print("Positivos")
for x in lista:
    if x > 0:
        print(x)
```

Simples. Agora vem o choque cultural.

## 15.2 A ideia simples: vetor é uma fileira de compartimentos idênticos

Na Parte 1 você viu que uma variável em C é um **compartimento moldado** na memória. Um vetor é o passo seguinte: uma **fileira de compartimentos idênticos, grudados um no outro**, com um nome só e numerados a partir do zero.

```c
int lista[10];
```

Isso reserva **10 compartimentos de `int`, lado a lado**, chamados `lista[0]`, `lista[1]`, …, `lista[9]`.

## 15.3 As quatro diferenças em relação à lista de Python (slide 21)

Os slides são diretos:

> Em C, as listas são bem diferentes em relação ao Python:
> - São chamadas de **vetores** ou **arrays**
> - **Todos os elementos são sempre do mesmo tipo**
> - **Têm tamanho fixo definido na declaração da variável**
> - Exemplo de declaração: `int lista[10];`

Vale destrinchar cada uma, porque cada diferença tem uma consequência prática:

| Diferença | Python | C | Consequência prática |
|---|---|---|---|
| Tipo dos elementos | heterogêneo: `[1, "a", 3.5]` | **homogêneo**: só `int`, ou só `double`… | O compilador sabe o tamanho exato de cada elemento |
| Tamanho | cresce e encolhe (`append`, `pop`) | **fixo**, decidido na declaração | **Não existe `append` em C** |
| Saber o tamanho | `len(lista)` | **não existe** | Você tem que carregar o tamanho na mão |
| Limites | `lista[99]` → `IndexError` | **nenhuma checagem** | Acesso inválido corrompe memória silenciosamente |

Essas quatro limitações parecem um retrocesso brutal. E são — **e é exatamente por isso que esta disciplina existe.** Listas encadeadas, pilhas, filas e árvores são, todas, respostas ao problema "como consigo uma coleção que cresce, num idioma onde o tamanho é fixo?". Guarde essa frase: ela é o fio condutor do curso inteiro.

## 15.4 Como o vetor é representado na memória — o ponto central

Aqui está o conceito que faz tudo funcionar. Os slides dizem, no slide 27:

> No C, um vetor é um **bloco contíguo de memória**.

"Contíguo" significa: os elementos ficam **fisicamente colados** na memória, sem buracos, na ordem dos índices.

Retomando a memória como fila de caixinhas numeradas (Parte 1, seção 11.1), com `int lista[5]` começando no endereço 2000:

```
Índice:        [0]        [1]        [2]        [3]        [4]
             ┌──────────┬──────────┬──────────┬──────────┬──────────┐
Conteúdo:    │    10    │    20    │    30    │    40    │    50    │
             └──────────┴──────────┴──────────┴──────────┴──────────┘
Endereço:      2000       2004       2008       2012       2016
                 └── 4 bytes ──┘
```

Eu comprovei isso rodando um programa de verdade. Note os endereços consecutivos, exatamente 4 bytes (o tamanho de um `int`) de distância:

```
v      = 0x7ffc93058a00
&v[0]  = 0x7ffc93058a00     ← igual ao anterior! guarde isto
&v[1]  = 0x7ffc93058a04     ← 4 bytes depois
```

### Por que a contiguidade é o segredo do desempenho

Como os elementos estão colados e todos têm o mesmo tamanho, o computador calcula o endereço de qualquer elemento com **uma continha de nada**:

```
endereço de lista[i]  =  endereço inicial  +  i × (tamanho do tipo)
```

Para `lista[3]`: 2000 + 3 × 4 = 2012. Uma multiplicação e uma soma.

**Isso significa que acessar `lista[0]` e acessar `lista[999999]` custam exatamente a mesma coisa.** Não há busca, não há percorrer. É o que se chama **acesso aleatório em tempo constante**, ou **O(1)**.

### Analogia: a rua de casas idênticas

Imagine uma rua onde todas as casas foram construídas do mesmo tamanho, encostadas, numeradas a partir do zero, começando no quilômetro 2.

Se cada casa ocupa 4 metros de frente e você quer chegar na casa nº 3, você **não precisa passar pelas casas 0, 1 e 2**. Você calcula: quilômetro 2 + 3 × 4 metros, e vai direto.

Agora compare com um bairro onde as casas foram construídas em terrenos espalhados por toda a cidade, e cada casa só tem um bilhete com o endereço da próxima. Para chegar na quarta casa, você **tem que visitar as três anteriores** para descobrir onde ela fica.

**Correspondência:**

| Analogia | Conceito |
|---|---|
| Rua de casas idênticas e encostadas | **Vetor** (memória contígua) |
| Casas espalhadas, cada uma com o endereço da próxima | **Lista encadeada** (você verá em breve) |
| Ir direto pela conta km + i×4 | Acesso `lista[i]` em **O(1)** |
| Ter que visitar todas as anteriores | Acesso em lista encadeada, **O(n)** |
| Casas de tamanho fixo | Todos os elementos do mesmo tipo |
| Não dá para enfiar uma casa nova no meio da rua | Vetor tem **tamanho fixo** |

**Guarde essa segunda rua.** Quando chegar a aula de listas encadeadas, esta analogia vai explicar de uma vez toda a tabela de vantagens e desvantagens.

## 15.5 Sintaxe de uso (slide 22)

```c
int lista[10];                    /* declara */
lista[0] = 42;                    /* escreve */
int x = lista[3];                 /* lê */
printf("%d", lista[i]);           /* imprime — cada lista[i] é um int comum */
scanf("%d", &lista[i]);           /* lê do teclado — repare no & */
```

O slide 22 destaca justamente a última dupla:

> Cada `lista[i]` é um `int`. Imprimir: `printf("%d", lista[i]);` — Ler: `scanf("%d", &lista[i]);`

**Por que `&lista[i]`?** Pelo mesmo motivo da Parte 1, seção 11: `scanf` precisa **escrever** naquela posição, então precisa do **endereço** dela. E `&lista[i]` significa "o endereço do elemento `i`". A expressão `lista[i]` é uma variável `int` como qualquer outra — inclusive no fato de ter um endereço.

### Inicialização na declaração

```c
int v[5] = {1, 2, 3, 4, 5};    /* todos os valores */
int w[3] = {7};                /* w[0]=7, e o RESTO É ZERADO */
int z[] = {1, 2, 3};           /* tamanho deduzido: 3 */
```

A segunda linha é uma pegadinha útil de saber. Eu testei: `int w[3] = {7};` produz `w = 7 0 0`. Quando você fornece **pelo menos um** inicializador, o C zera todo o resto. Daí o truque idiomático:

```c
int contadores[100] = {0};     /* zera o vetor inteiro */
```

⚠️ Mas **`int v[5];` sozinho, sem `= {…}`, contém lixo** — as mesmas regras da Parte 1, seção 7.

## 15.6 A tradução do programa (slide 21)

```c
#include <stdio.h>

int main() {
  int lista[10];
  printf("Digite 10 números\n");
  for (int i = 0; i < 10; i++)
    scanf("%d", &lista[i]);
  printf("Positivos\n");
  for (int i = 0; i < 10; i++) {
    if (lista[i] > 0)
      printf("%d\n", lista[i]);
  }
  return 0;
}
```

O contraste com Python é instrutivo:

| Python | C | Por quê |
|---|---|---|
| `lista = []` | `int lista[10];` | O tamanho tem que ser decidido **antes** |
| `lista.append(...)` | `scanf("%d", &lista[i])` | Não há `append`; você **preenche uma posição que já existe** |
| `for x in lista:` | `for (int i = 0; i < 10; i++)` | Não há iteração por elemento; você controla o índice |

O ponto conceitual: em Python a lista **cresce** conforme você adiciona. Em C, as 10 posições **já existem desde a declaração** (com lixo dentro) e você apenas as sobrescreve.

## ✅ O que eu preciso saber deste tópico

- Declarar um vetor e explicar as 4 diferenças em relação à lista de Python.
- **Desenhar um vetor na memória**, com índices e endereços.
- Explicar por que `lista[i]` é O(1), usando a fórmula do endereço.
- Saber que `int v[10];` contém lixo e que `int v[10] = {0};` zera tudo.
- Escrever os laços de leitura e impressão de um vetor, com o `&` no lugar certo.

---

# 16. Vetores como parâmetros de funções (slides 23–26)

## 16.1 A motivação (slide 23)

> Podemos melhorar esse código: ter uma função que lê vetores, ter uma função que imprime apenas os positivos.

Boa prática de programação: separar tarefas em funções. Mas isso levanta duas perguntas em C que não existem em Python.

## 16.2 Função que recebe vetor (slide 24)

```c
void imprime_positivos(int lista[], int n) {
  printf("Positivos\n");
  for (int i = 0; i < n; i++)
    if (lista[i] > 0)
      printf("%d\n", lista[i]);
}
```

**Análise do cabeçalho, pedaço por pedaço:**

| Pedaço | Significado |
|---|---|
| `void` | a função **não devolve valor** (slide 24: "significa que a função não devolve valor") |
| `int lista[]` | recebe um vetor de `int`. **Colchetes vazios** |
| `int n` | recebe o tamanho — obrigatório, e a razão vem abaixo |

## 16.3 As duas regras que o slide 24 estabelece

### Regra 1: colchetes vazios no parâmetro

> Não precisamos especificar o tamanho entre o `[]` — apenas quando é um parâmetro.

Ou seja:
- Na **declaração de uma variável**: `int lista[10];` — tamanho **obrigatório**.
- Num **parâmetro de função**: `int lista[]` — tamanho **omitido**.

Por enquanto aceite; na seção 19 você vai entender *por quê*, e a razão é profunda.

### Regra 2: você tem que carregar o tamanho na mão

> É nossa responsabilidade saber o tamanho do vetor. Por isso precisamos do parâmetro `n`. **No C, não há o equivalente ao `len()` do Python.**

Este é um dos pontos mais importantes de todo o material, e vou provar que é verdade com um teste que rodei:

```c
int v[5] = {1,2,3,4,5};
/* dentro da main: */   sizeof(v)  →  20 bytes  →  20/4 = 5 elementos ✔
/* dentro de uma função que recebe int v[]: */
                        sizeof(v)  →  8 bytes   →  ✘ ISSO NÃO É O VETOR
```

O compilador ainda me avisou:

```
warning: 'sizeof' on array function parameter 'v' will return size of 'int *'
```

Traduzindo: **na hora em que o vetor entra na função, a informação de tamanho é perdida.** Aqueles 8 bytes são o tamanho de um endereço de memória, não do vetor.

É por isso que **toda função que recebe vetor em C recebe também o tamanho**. Não é frescura do professor; é uma limitação real da linguagem. Você verá esse par `(vetor, n)` mil vezes no curso.

> ⚠️ Erro comum em prova: escrever `void f(int v[])` sem o `n` e depois tentar percorrer o vetor. Não há como saber onde parar.

## 16.4 Função que MODIFICA o vetor (slide 25)

Aqui os slides fazem uma afirmação que merece cuidado:

> **Em C, não é possível devolver um vetor…** Passamos um vetor como parâmetro e modificamos o seu conteúdo.

```c
void le_vetor(int lista[], int n) {
  printf("Digite %d números\n", n);
  for (int i = 0; i < n; i++)
    scanf("%d", &lista[i]);
}
```

**Linha a linha:**

1. `void le_vetor(int lista[], int n)` — não devolve nada; recebe o vetor a preencher e quantos números ler.
2. `printf("Digite %d números\n", n);` — instrução ao usuário, usando `n` no texto.
3. `for (int i = 0; i < n; i++)` — percorre de 0 a n−1.
4. `scanf("%d", &lista[i]);` — lê e **escreve diretamente na posição `i` do vetor do chamador**.

E os slides admitem o mistério:

> A função modifica o conteúdo do vetor `lista`. **Entenderemos isso melhor em breve…**

Segure essa curiosidade — é o assunto da seção 19, e a resposta é a peça central de toda a disciplina.

### 🔴 Correção: a frase "não é possível devolver um vetor" é imprecisa

Você me pediu para avisar quando algo estiver incompleto. Este é um caso.

**O que é verdade:** você não pode escrever uma função com tipo de retorno "vetor de int". Não existe essa sintaxe. Isto não compila:

```c
int[] cria_vetor();      /* sintaxe inexistente em C */
```

**O que é falso:** que não exista jeito de uma função "produzir" um vetor. Existe, sim — devolvendo um **ponteiro** para memória alocada dinamicamente:

```c
int *cria_vetor(int n) {
    int *v = malloc(n * sizeof(int));    /* isto você aprenderá em breve */
    return v;
}
```

Esta é, aliás, a técnica sobre a qual **todas** as estruturas de dados do curso são construídas. A frase do slide está correta *no contexto do que foi ensinado até aqui*, mas não é uma limitação permanente da linguagem. Não saia da aula achando que C nunca devolve coleções.

E há um motivo real por trás da restrição, que vale entender: se uma função criasse um vetor local e devolvesse "o vetor", esse vetor seria destruído no instante em que a função terminasse (slide 29: "quando a função acaba, o valor é perdido"). Devolver o endereço de algo que acabou de ser destruído é um dos bugs mais clássicos de C. A regra do slide, na prática, te protege disso.

## 16.5 O código completo refatorado (slide 26)

```c
#include <stdio.h>

void le_vetor(int lista[], int n) {
  printf("Digite %d números\n", n);
  for (int i = 0; i < n; i++)
    scanf("%d", &lista[i]);
}

void imprime_positivos(int lista[], int n) {
  printf("Positivos\n");
  for (int i = 0; i < n; i++)
    if (lista[i] > 0)
      printf("%d\n", lista[i]);
}

int main() {
  int lista[10];
  le_vetor(lista, 10);
  imprime_positivos(lista, 10);
  return 0;
}
```

Repare em três coisas:

1. **Ao passar o vetor, você escreve só o nome: `le_vetor(lista, 10)`.** Sem colchetes, sem `&`. O nome do vetor, sozinho, já é o que a função precisa.
2. `main` ficou com 4 linhas e é lida como português: "leia o vetor, imprima os positivos".
3. O número `10` aparece **três vezes** (declaração e duas chamadas). Isso é um cheiro de código: se você mudar para 20, tem que lembrar de mudar nos três lugares. A solução idiomática é `#define TAM 10` — e, olha só, é exatamente o que a Unidade 3 vai te ensinar.

## ✅ O que eu preciso saber deste tópico

- Escrever uma função que recebe um vetor, com `int v[]` e o tamanho `n`.
- **Explicar por que o `n` é obrigatório** (não existe `len()`; `sizeof` não funciona dentro da função).
- Saber que na chamada se passa só o nome: `f(lista, 10)`.
- Escrever uma função `void` que preenche um vetor recebido.
- Saber que "não dá para devolver vetor" vira "devolve-se um ponteiro" quando você aprender `malloc`.

---

# 17. Acesso fora dos limites — o perigo nº 1 de C (slide 27)

## 17.1 O aviso dos slides

> **A responsabilidade de acessar apenas posições válidas é sua!**
> Se você declarou um vetor com 10 posições e acessar a posição 10, 11, 12, etc…
> - Ou você terá um erro de execução: **segmentation fault**
> - **Ou não…**
>   - Se for impressão, pode imprimir o valor de outra variável
>   - Se for escrita, **pode mudar o valor de outra variável**
>
> No C, um vetor é um bloco contíguo de memória. E o C assume que você usará o bloco corretamente. **Não há checagem dos limites do vetor.**

Este slide está tecnicamente perfeito, e aquele **"Ou não…"** é a parte mais assustadora e mais importante.

## 17.2 Por que "ou não" é pior do que o segfault

**Um segfault é um presente.** O programa morre imediatamente, você sabe que tem um bug, e o `gdb` te mostra a linha. Sofrimento: 10 minutos.

O caso "ou não" é o pesadelo: o programa **roda normalmente**, produz resultados, e em algum lugar do meio silenciosamente corrompeu uma variável que não tem nada a ver com aquilo. Você vai depurar a função errada por horas.

### Eu comprovei isso — veja o resultado real

Escrevi um programa com três variáveis vizinhas e escrevi propositalmente fora dos limites:

```c
int antes = 111, v[5] = {1,2,3,4,5}, depois = 999;
v[5]  = 42;      /* fora dos limites: v só vai até v[4] */
v[-1] = 77;      /* índice negativo */
```

Saída real do programa:

```
antes=111 depois=999
depois de escrever em v[5] e v[-1]: antes=111 depois=77
```

Leia com atenção o que aconteceu: **a variável `depois` mudou de 999 para 77 sem que ninguém jamais tenha escrito na variável `depois`.** O programa não deu erro. Não deu warning. Não deu segfault. Ele simplesmente continuou rodando com um dado corrompido.

Isso acontece porque `v[-1]` é traduzido literalmente para "endereço de `v`, menos 4 bytes" — e naquele endereço, por acaso, morava a variável `depois`.

### Analogia: o vizinho e a parede que não existe

Volte à rua de casas idênticas. Seu vetor de 5 posições são as casas 0 a 4. **Mas a rua não acaba na casa 4** — ela continua, com as casas dos vizinhos (outras variáveis do seu programa).

Em Python, há um **muro com guarda** no fim da sua propriedade: tentar entrar na casa 5 dispara um alarme (`IndexError`).

Em C, **não há muro nenhum**. Você anda até onde quiser. Se entrar na casa 5, três coisas podem acontecer:
1. É a casa de um vizinho → você reforma a casa dele achando que é a sua. **Ninguém te avisa.** (foi o que aconteceu no meu teste)
2. É terreno baldio → não acontece nada visível, hoje. Amanhã pode acontecer.
3. É propriedade militar cercada → o sistema operacional te derruba: **segmentation fault**.

**Correspondência:** as casas vizinhas são outras variáveis; o terreno baldio é memória alocada mas não usada; a propriedade militar é uma página de memória fora do seu processo; o alarme do Python é a checagem de limites, que C não faz por questão de desempenho.

## 17.3 O erro *off-by-one* (erro de um)

> O que ocorre muitas vezes é **off-by-one**. Se o vetor tem n posições, você **não deve acessar a posição n**. — (slide 27)

Vetor com `n` posições ⇒ índices válidos vão de **`0` a `n−1`**. A posição `n` **não existe**.

Os quatro jeitos de errar isso:

| Errado | Por quê | Certo |
|---|---|---|
| `for (i = 0; i <= n; i++)` | acessa `v[n]` na última volta | `i < n` |
| `for (i = 1; i <= n; i++)` | pula `v[0]` **e** acessa `v[n]` | `i = 0; i < n` |
| `v[n] = x;` | `n` está fora | `v[n-1] = x;` |
| `for (i = n; i >= 0; i--)` | começa em `v[n]` | `i = n-1; i >= 0; i--` |

**A regra de ouro para nunca mais errar:** o laço padrão de percorrer vetor em C é

```c
for (int i = 0; i < n; i++)
```

Comece em `0`, use `<` (nunca `<=`), pare em `n`. Se você escrever isso automaticamente, elimina a maior parte dos off-by-one da sua vida.

## 17.4 Como se defender na prática

1. **Use o laço padrão acima**, sempre.
2. **Compile com `-g` e rode o `valgrind`**: `valgrind ./programa`. Ele detecta acessos inválidos que não causam crash. Lembra da flag `-g` do slide 15? É para isto.
3. **Nunca confie no `n` que o usuário digitou.** Se você declarou `int v[100]` e o usuário digita `n = 500`, seu programa vai escrever 400 posições além do vetor. Valide: `if (n > 100) n = 100;`

Esse ponto 3 é relevante porque os próprios exercícios do slide 32 declaram `int vetor1[100]` e leem `n` do usuário sem validar.

## ✅ O que eu preciso saber deste tópico

- Saber que C **não checa** limites de vetor, e por quê (desempenho).
- **Explicar os dois desfechos possíveis: segfault OU corrupção silenciosa** — e por que o segundo é pior.
- Saber que os índices válidos são `0` a `n−1`.
- Definir *off-by-one* e apontar o erro em `for (i = 0; i <= n; i++)`.
- Escrever o laço padrão de percurso de cor.

---

# 18. Escopo: variáveis globais e locais (slides 28–30)

## 18.1 O código de referência (slides 28–29)

```c
#include <stdio.h>

int global;

void funcao1(int parametro) {
  int local1, local2;
  ...
}

void funcao2(int parametro) {
  int local1, local2;
  ...
}

int main() {
  int local;
}
```

## 18.2 Variáveis globais (slide 28)

> `global` é uma variável global:
> - pode ser acessada em **qualquer função**
> - variáveis globais só são usadas em **casos específicos**
> - podem levar a **erros difíceis de encontrar** no programa

**Definição técnica:** uma variável declarada **fora de qualquer função** é global. Ela existe durante toda a execução do programa e é visível em todas as funções do arquivo.

> Detalhe (não essencial): variáveis globais são automaticamente inicializadas com **zero**, ao contrário das locais, que contêm lixo. É a única exceção à regra do lixo.

## 18.3 Variáveis locais (slide 29)

> `local`, `local1`, `local2` e `parametro` são variáveis locais:
> - existem **apenas dentro da função** onde foram definidas
> - `local1` de `funcao1` é **diferente** de `local1` de `funcao2`
> - **quando a função acaba, o valor é perdido**

Três afirmações, todas cruciais.

Note especialmente que **parâmetros são variáveis locais**. `parametro` se comporta como qualquer variável declarada dentro da função — ela apenas já nasce com um valor (o que foi passado na chamada). Essa observação é a chave da seção 19.

### Analogia: o hotel e os quartos (retomando a Parte 1)

Voltemos ao hotel da Parte 1, seção 7.2.

- Uma **variável local** é um quarto que você aluga ao entrar na função. Quando a função termina, você faz check-out. O quarto volta para o hotel — **com a sua bagunça dentro**, disponível para o próximo hóspede. É por isso que "o valor é perdido": não é que ele seja apagado, é que o espaço passa a pertencer a outra pessoa.
- Uma **variável global** é o saguão do hotel: não pertence a nenhum hóspede, existe o tempo todo, e **qualquer um pode mexer nele**.

**Correspondência:**

| Analogia | Conceito |
|---|---|
| Alugar o quarto ao entrar | Alocação da variável local na pilha |
| Check-out ao sair | A variável deixa de existir quando a função retorna |
| Bagunça deixada no quarto | O **lixo** que o próximo hóspede encontra |
| O saguão | Variável global |
| Qualquer um mexe no saguão | Qualquer função altera a global |
| Ninguém sabe quem bagunçou o saguão | "erros difíceis de encontrar" |

Essa última linha explica exatamente a advertência do slide. Se um valor global está errado, o culpado pode ser **qualquer** função do programa. Se um valor local está errado, o culpado está naquelas 15 linhas.

## 18.4 Sobreposição de escopo (slide 30)

```c
int x;                      /* global */

void funcao1(int parametro) {
  x = 10;                   /* altera a GLOBAL x */
}

void funcao2(int parametro) {
  int x;                    /* local, com o mesmo nome */
  x = 10;                   /* altera a LOCAL x */
}
```

> **Variáveis locais têm precedência sobre variáveis globais.**
> - Em `funcao1`, a variável global `x` tem seu valor alterado
> - Em `funcao2`, a variável **local** `x` tem seu valor alterado
>
> Um dos motivos que evitamos o uso de variáveis globais!

O nome técnico disso é ***shadowing*** (sombreamento): a variável local "faz sombra" sobre a global de mesmo nome, tornando a global inacessível ali dentro.

**Por que isso é perigoso:** imagine que você escreveu `funcao1` esperando alterar a global. Meses depois, alguém adiciona `int x;` no começo de `funcao1` por outro motivo. O código continua compilando, sem nenhum aviso, mas **para de funcionar** — agora está alterando uma variável local que é descartada ao sair da função. Nada aponta para o problema.

> ⚠️ Isso aparece em prova como pergunta de rastreamento: "qual o valor impresso de `x` ao final?". O truque é sempre: **procure a declaração mais próxima (mais interna) do nome.**

## 18.5 Um caso de shadowing que está nos próprios slides

O slide 34 traz esta função:

```c
int soma(int vetor[], int n) {
  int soma = 0;               /* ← a variável tem o MESMO NOME da função */
  for (int i = 0; i < n; i++)
    soma += vetor[i];
  return soma;
}
```

Isso **compila e funciona** (eu testei: devolve o resultado correto). Dentro da função, a variável local `soma` faz sombra sobre o nome da função `soma`.

Mas é uma prática ruim, por dois motivos:
1. Confunde quem lê: `soma += vetor[i]` está mexendo na variável ou chamando a função?
2. **Torna a função impossível de chamar recursivamente**, porque o nome `soma` ali dentro não se refere mais à função.

Não é um erro nos slides — é código válido. Mas se você fizer isso num trabalho, provavelmente ouvirá do monitor. Chame de `total` ou `acumulador`.

## 18.6 A recomendação prática

**Evite variáveis globais.** As exceções legítimas são poucas: constantes (mas para isso use `#define`, que a Unidade 3 ensina) e algumas situações muito específicas.

A alternativa correta é sempre a mesma: **passe os dados como parâmetro e devolva os resultados**. Uma função que só depende dos parâmetros e só devolve o retorno é fácil de testar, fácil de entender e impossível de quebrar à distância.

## ✅ O que eu preciso saber deste tópico

- Definir variável global e local, e dizer onde cada uma é declarada.
- Saber que **parâmetros são variáveis locais**.
- Explicar "quando a função acaba, o valor é perdido" em termos de memória.
- Explicar shadowing e resolver uma questão de rastreamento de valor.
- Dar dois motivos concretos para evitar variáveis globais.

---

# 19. 🔑 A grande revelação: por que vetores se comportam diferente (slide 31)

Chegamos ao slide mais importante de todo o material — e ao mistério que os slides deixaram em aberto duas vezes.

## 19.1 O experimento dos slides

Dois códigos aparentemente análogos, com resultados completamente diferentes:

**Esquerda — com um `int`:**
```c
void soma_um(int x) {
  x = x + 1;
}

int main() {
  int x = 1;
  soma_um(x);
  printf("%d ", x);      /* imprime 1 */
  return 0;
}
```

**Direita — com um vetor:**
```c
void soma_um(int v[], int n) {
  for (int i = 0; i < n; i++)
    v[i]++;
}

int main() {
  int v[5] = {1, 2, 3, 4, 5};
  soma_um(v, 5);
  for (int i = 0; i < 5; i++)
    printf("%d ", v[i]);   /* imprime 2 3 4 5 6 */
  return 0;
}
```

Os slides constatam o fato e dão a explicação parcial:

> No código da esquerda é impresso **1** — a variável `x` de `main` é diferente da variável `x` de `soma_um`.
> No código da direita é impresso **2 3 4 5 6** — a função altera o conteúdo do vetor. **Entenderemos o motivo disso posteriormente…**

Eu compilei e rodei os dois. Confirmado: `x = 1` e `2 3 4 5 6`. Agora vamos ao *porquê*, porque adiar isso é o que faz aluno decorar em vez de entender.

## 19.2 Metade da resposta: passagem por valor

Isto os slides já explicaram, mas vale formalizar.

**Em C, todo parâmetro é passado por valor**: a função recebe uma **cópia** do que você passou.

Quando você chama `soma_um(x)`, acontece isto:

```
       main                          soma_um
   ┌──────────────┐            ┌──────────────┐
   │  x  =  1     │  ─cópia→   │  x  =  1     │
   │  end. 3000   │            │  end. 5000   │  ← outro endereço!
   └──────────────┘            └──────────────┘
                                      │
                               x = x + 1
                                      ↓
                               ┌──────────────┐
                               │  x  =  2     │  ← só a cópia mudou
                               └──────────────┘
                                      │
                               função termina → cópia destruída
   ┌──────────────┐
   │  x  =  1     │  ← intacta
   └──────────────┘
```

Isso conecta direto com a seção 18: **parâmetros são variáveis locais**. O `x` de `soma_um` é uma variável local que por acaso tem o mesmo nome. São duas casas diferentes, em endereços diferentes.

### Analogia: a fotocópia do documento

Você tem um documento e pede a um colega que "some 1 no número da página". Você não entrega o original — você tira uma **fotocópia** e entrega a cópia. Ele rabisca a cópia, devolve, e você joga a cópia fora. **Seu original está intacto.**

**Correspondência:** o original é a variável na `main`; a fotocópia é o parâmetro; rabiscar a cópia é modificar o parâmetro; jogar fora é a destruição da variável local no retorno.

## 19.3 A outra metade: o que é o "valor" de um vetor?

Se todo parâmetro é passado por valor, e vetores também são passados por valor… **por que o vetor mudou?**

A resposta é a peça que faltava, e é uma das ideias mais elegantes de C:

> **O que é copiado não é o vetor. É o ENDEREÇO do vetor.**

Quando o nome de um vetor é usado numa expressão, ele "se transforma" no **endereço do seu primeiro elemento**. O nome técnico é *array decay* (decaimento de vetor para ponteiro).

Eu provei isso experimentalmente. Lembra da saída que mostrei na seção 15.4?

```
v      = 0x7ffc93058a00
&v[0]  = 0x7ffc93058a00     ← EXATAMENTE o mesmo valor
```

**`v` e `&v[0]` são a mesma coisa.** O nome do vetor *é* o endereço do primeiro elemento.

Então, quando você escreve `soma_um(v, 5)`, o que a função recebe é uma cópia de **um endereço** — o número `0x7ffc93058a00`. E, como você aprendeu na Parte 1 seção 11: **quem tem o endereço, consegue modificar o original.**

```
       main                              soma_um
   ┌──────────────┐                  ┌────────────────────┐
   │ v[0] v[1]... │                  │ v = 0x...a00       │  ← cópia do ENDEREÇO
   │  1    2   ...│                  └────────────────────┘
   │ em 0x...a00  │  ←───────────────────────┘
   └──────────────┘         v[i]++ escreve através do endereço,
          ↑                 direto na memória da main
          └── o vetor original É modificado
```

### Analogia: a fotocópia do documento × a cópia da CHAVE

Retome a fotocópia. Agora o segundo caso:

Você quer que um colega pinte sua casa. Você não pode "fotocopiar a casa" — casas não cabem em fotocopiadora. Então você faz uma **cópia da chave** e entrega a ele.

Repare: **a chave foi copiada** — ele tem a cópia, você tem a original, são duas chaves. Passagem por valor, exatamente como no primeiro caso. Mas as duas chaves **abrem a mesma casa**. Ele entra e pinta *a sua casa de verdade*.

**Correspondência — esta é a tabela mais importante do material:**

| Analogia | Conceito |
|---|---|
| O documento | Uma variável `int` |
| Fotocópia do documento | Cópia do valor — passagem por valor |
| A casa (grande demais para copiar) | O vetor |
| **A chave da casa** | **O endereço do primeiro elemento** |
| Copiar a chave (não a casa) | O que é copiado é o endereço, não os dados |
| As duas chaves abrem a mesma casa | Função e `main` acessam a mesma memória |
| Pintar a casa | `v[i]++` modifica o vetor original |
| Você não pode trocar a casa dele por outra | Atribuir ao parâmetro não afeta o chamador |

**A frase para gravar:** *em C tudo é passado por valor — mas no caso de vetores, o valor passado é um endereço.*

## 19.4 Isto explica, de uma vez, três coisas que pareciam desconexas

Repare como uma única ideia resolve tudo que ficou pendente:

| Pergunta em aberto | Resposta |
|---|---|
| Por que `le_vetor` consegue preencher o vetor da `main`? (slide 25) | Ela recebeu o endereço; escreve direto na memória original |
| Por que "não é possível devolver um vetor"? (slide 25) | Devolver o endereço de um vetor local seria devolver o endereço de um quarto do qual você já fez check-out |
| Por que o `[]` do parâmetro fica vazio? (slide 24) | Porque não é um vetor de verdade — é só um **endereço**. E todo endereço tem o mesmo tamanho, independente de quantos elementos existem |
| Por que `sizeof(v)` dá 8 dentro da função? | Porque 8 bytes é o tamanho de um endereço nessa máquina |
| Por que preciso passar `n`? | Porque o endereço diz *onde começa*, mas não diz *onde termina* |

Cinco mistérios, uma explicação. É por isso que este é o slide mais importante.

## 19.5 Consequências práticas

**1. Como fazer uma função modificar um `int` do chamador?** Passando o endereço — exatamente como o `scanf` faz. A sintaxe completa (`int *x`) você verá na aula de ponteiros, mas o conceito já é este.

**2. Cuidado: quem recebe um vetor pode estragá-lo.** Como a função tem acesso real à memória original, um bug nela corrompe os dados da `main`. Existe uma proteção: `const`.

```c
void imprime(const int v[], int n)    /* promete não modificar v */
```

Se a função tentar escrever em `v`, o compilador dá erro. Não está nos slides, mas é boa prática e você verá em código profissional.

**3. Passar vetor é barato.** Passar um vetor de 1 milhão de elementos copia **8 bytes** (o endereço), não 4 milhões. Não existe custo de cópia. É por isso que C não precisa de "passagem por referência" explícita para coleções.

## ✅ O que eu preciso saber deste tópico

- **Explicar por que `soma_um(x)` não altera `x` mas `soma_um(v, 5)` altera o vetor.** (Se você souber só uma coisa deste material, que seja esta.)
- Definir passagem por valor.
- Explicar que o nome de um vetor equivale ao endereço do primeiro elemento (`v == &v[0]`).
- Usar isso para explicar por que o `[]` do parâmetro é vazio e por que `n` é necessário.
- Relacionar isso com o `&` do `scanf`.

---

# 20. Exercício resolvido: Produto de Hadamard (slides 32–34)

## 20.1 Enunciado

> O Produto de Hadamard de dois vetores u e v é o produto **ponto a ponto**: o vetor (u₁v₁, u₂v₂, …, uₙvₙ).
>
> a) Programa em C que lê dois vetores de n inteiros, n ≤ 100, armazena o produto de Hadamard em um terceiro vetor e o imprime.
> b) Modifique para calcular o **produto escalar** de dois vetores.

Diferença entre os dois, para ficar claro:
- **Hadamard:** vetor × vetor → **vetor**. `(1,2,3) ⊙ (4,5,6) = (4,10,18)`
- **Escalar:** vetor × vetor → **número**. `(1,2,3) · (4,5,6) = 4+10+18 = 32`

O item (b) é o item (a) seguido de uma soma — daí a estratégia da solução.

## 20.2 Solução do item (a) — slide 33

```c
#include <stdio.h>

void le_vetor(int lista[], int n) {
    printf("Digite %d números\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &lista[i]);
}

void imprime_vetor(int vetor[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}

void hadamard(int vetor1[], int vetor2[], int n, int resultado[]) {
    for (int i = 0; i < n; i++)
        resultado[i] = vetor1[i] * vetor2[i];
}

int main() {
    int n, vetor1[100], vetor2[100], resultado[100];
    printf("Digite o tamanho dos vetores\n");
    scanf("%d", &n);
    le_vetor(vetor1, n);
    le_vetor(vetor2, n);
    hadamard(vetor1, vetor2, n, resultado);
    printf("Resultado do produto de Hadamard:\n");
    imprime_vetor(resultado, n);
    return 0;
}
```

### A função `hadamard` — o padrão mais importante do exercício

```c
void hadamard(int vetor1[], int vetor2[], int n, int resultado[])
```

Este cabeçalho é uma aplicação direta da seção 19, e vale ler com atenção:

- É `void` — **não devolve nada**.
- Recebe **quatro** parâmetros: dois vetores de entrada, o tamanho, **e o vetor onde escrever a resposta**.
- `resultado` é o "vetor de saída": a função escreve nele, e a `main` lê o que foi escrito.

**Por que não `int[] hadamard(...)`?** Porque isso não existe em C (seção 16.4). A saída tem que ser passada como parâmetro. Este padrão — *"passe o buffer de saída como parâmetro"* — é onipresente em C. Você vai reencontrá-lo a vida inteira, inclusive em `le_matriz_quadrada` na próxima unidade.

O corpo é trivial: para cada `i`, multiplica os dois e guarda. Como `resultado` é o endereço do vetor da `main`, a escrita acontece direto lá.

### Por que `[100]`

O enunciado diz n ≤ 100. Como o tamanho é fixo em tempo de compilação (seção 15.3), você reserva o **pior caso** e usa só as `n` primeiras posições. Isso desperdiça memória — se n = 3, sobram 97 posições ociosas em cada vetor — mas é a única saída sem alocação dinâmica.

> Essa limitação é, mais uma vez, a motivação do curso inteiro. `malloc` vai te permitir pedir exatamente `n` posições.

## 20.3 Solução do item (b) — slide 34

```c
int soma(int vetor[], int n) {
    int soma = 0;
    for (int i = 0; i < n; i++)
        soma += vetor[i];
    return soma;
}

int main() {
    int n, produto, vetor1[100], vetor2[100], resultado[100];
    printf("Digite o tamanho dos vetores\n");
    scanf("%d", &n);
    le_vetor(vetor1, n);
    le_vetor(vetor2, n);
    hadamard(vetor1, vetor2, n, resultado);
    produto = soma(resultado, n);
    printf("Produto escalar: %d\n", produto);
    return 0;
}
```

A estratégia: **Hadamard primeiro, soma depois.** Faz sentido, porque produto escalar = soma dos produtos ponto a ponto.

Note que `soma` **devolve** um valor (`int`), enquanto `hadamard` escrevia num parâmetro. Por quê? Porque um `int` **pode** ser devolvido; um vetor não. A restrição só existe para coleções.

> ⚠️ A variável local `soma` faz sombra sobre o nome da função — veja a seção 18.5.

## 20.4 A pergunta reflexiva do slide 34

> Outra opção seria não calcular o produto de Hadamard e já calcular diretamente o produto escalar. **Quais as vantagens e desvantagens de cada abordagem?**

Os slides deixam em aberto. Vamos responder, porque é uma excelente pergunta de prova.

**Abordagem alternativa (direta):**

```c
int produto_escalar(int v1[], int v2[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++)
        total += v1[i] * v2[i];
    return total;
}
```

| Critério | Hadamard + soma | Direta |
|---|---|---|
| **Memória extra** | vetor `resultado` de n posições → **O(n)** | uma variável → **O(1)** ✔ |
| **Passagens pelos dados** | 2 (escreve, depois lê) | **1** ✔ |
| **Reaproveitamento** | `hadamard` e `soma` servem para outras coisas ✔ | função de uso único |
| **Resultados intermediários** | disponíveis para inspeção/depuração ✔ | perdidos |
| **Legibilidade** | espelha a definição matemática ✔ | também é bem legível |
| **Complexidade de tempo** | O(n) | O(n) — **mesma ordem** |

**A resposta madura:** as duas são **O(n)** em tempo — a abordagem direta não é assintoticamente melhor. Ela ganha em memória (O(1) vs O(n)) e em constante (uma passada em vez de duas, e melhor uso de cache).

A composicional ganha em **modularidade**: você construiu duas peças reutilizáveis. Se depois precisar do vetor de Hadamard para outra coisa, já tem.

**Regra prática:** para n ≤ 100, prefira a composicional (mais clara, custo irrelevante). Para vetores gigantes ou memória escassa, prefira a direta.

Esse raciocínio — *"mesma complexidade assintótica, mas diferentes em memória e em constante"* — é exatamente o tipo de análise que a disciplina vai cobrar de você o semestre inteiro.

## 20.5 🔴 Problema: nenhuma das soluções valida `n`

Você me pediu para apontar práticas ruins. Esta é séria:

```c
int n, vetor1[100], ...;
scanf("%d", &n);
le_vetor(vetor1, n);      /* e se o usuário digitou 5000? */
```

Se o usuário digitar `n = 5000`, `le_vetor` vai escrever em 5000 posições de um vetor que só tem 100. Resultado: corrupção de memória ou segfault (seção 17). Se digitar `n` negativo, o laço simplesmente não roda e os vetores ficam com lixo.

**Correção mínima:**

```c
#define MAX 100

int main() {
    int n;
    scanf("%d", &n);
    if (n < 1 || n > MAX) {
        printf("Tamanho invalido (deve estar entre 1 e %d)\n", MAX);
        return 1;
    }
    ...
}
```

Note que isso já usa `#define` — assunto da próxima unidade. Além de validar, resolve o problema do número mágico `100` repetido em quatro lugares.

## ✅ O que eu preciso saber deste tópico

- Diferenciar produto de Hadamard (vetor) de produto escalar (número).
- **Escrever uma função que produz um vetor de saída via parâmetro.**
- Explicar por que `hadamard` é `void` mas `soma` devolve `int`.
- Comparar composição vs cálculo direto em termos de tempo e memória.
- Saber que declarar `[100]` e ler `n` do usuário exige validação.

---

# 📌 Consolidação da Parte 2

## O encadeamento das ideias (leia de cima para baixo)

```
Variável em C = espaço de memória com endereço
        ↓
Vetor = vários espaços IGUAIS e CONTÍGUOS
        ↓
Contiguidade ⇒ endereço de v[i] = base + i × tamanho
        ↓
        ├──→ Acesso O(1) (vantagem)
        ├──→ Tamanho fixo (desvantagem) ──→ motiva listas encadeadas
        └──→ Sem checagem de limites ──→ segfault OU corrupção silenciosa
        ↓
Nome do vetor "decai" para o endereço do 1º elemento (v == &v[0])
        ↓
        ├──→ [] vazio no parâmetro
        ├──→ sizeof não funciona dentro da função ──→ precisa passar n
        ├──→ função modifica o vetor original
        └──→ não se "devolve" vetor; passa-se buffer de saída
        ↓
Isto é a base de PONTEIROS, malloc e TODAS as estruturas do curso
```

## Complexidade das operações em vetor

| Operação | Custo | Por quê |
|---|---|---|
| Acessar `v[i]` | **O(1)** | conta aritmética direta |
| Alterar `v[i]` | **O(1)** | idem |
| Percorrer todo o vetor | **O(n)** | visita cada elemento |
| Buscar um valor (não ordenado) | **O(n)** | pode ter que olhar todos |
| Somar/multiplicar ponto a ponto | **O(n)** | uma passada |
| Inserir no meio | **O(n)** | tem que deslocar os seguintes |
| Crescer o vetor | **impossível** | tamanho fixo |

## Vantagens e desvantagens do vetor

**Vantagens:** acesso O(1) a qualquer posição; memória contígua (rápido, ótimo para cache); sem custo extra de armazenamento; sintaxe simples; passar para função é barato (só o endereço).

**Desvantagens:** tamanho fixo; não cresce; desperdiça memória quando se reserva o pior caso; inserção/remoção no meio é O(n); sem checagem de limites; tipo homogêneo.

**Quando usar:** quando você sabe o tamanho máximo antecipadamente, precisa de acesso rápido por índice, e não precisa inserir/remover no meio.

## Os erros mais comuns desta parte

1. **Esquecer que os índices vão de `0` a `n−1`** → off-by-one.
2. **`for (i = 0; i <= n; i++)`** → acessa `v[n]`, que não existe.
3. **Esquecer o `&` em `scanf("%d", &v[i])`**.
4. **Achar que `sizeof(v)` funciona dentro de uma função** → não funciona.
5. **Esquecer de passar `n`** para uma função que recebe vetor.
6. **Achar que a função não altera o vetor** porque "C é passagem por valor" → altera, sim.
7. **Achar que a função altera um `int`** passado como parâmetro → não altera.
8. **Ler `n` do usuário sem validar** contra o tamanho declarado.
9. **Usar variável global** por preguiça de passar parâmetro.
10. **`int v[5];` e sair usando** sem inicializar → lixo.

## O que é essencial × detalhe × prova

**Essencial:** vetor é bloco contíguo; índices 0 a n−1; sem checagem de limites; nome do vetor = endereço do primeiro elemento; passagem por valor; por que vetores "parecem" ser modificados; local vs global.

**Detalhe:** `const` em parâmetros; globais serem inicializadas com zero; `int z[] = {1,2,3}` deduzir o tamanho.

**Quase certo em prova:**
- "Por que este código imprime 1 e aquele imprime 2 3 4 5 6?" ← **decore a resposta**
- "O que acontece se acessar `v[10]` num vetor de 10 posições?"
- Rastreamento de valor com shadowing de global/local
- Escrever uma função que preenche um vetor recebido por parâmetro

---

# ➡️ Próxima parte

**Parte 3 — Unidade 3: Curso de C, Parte 2** (o PDF que você acabou de enviar). Os assuntos:

- **Números reais:** `float` × `double`, precisão, `%f` / `%e` / `%g` / `%lf`
- **Casting e conversão de tipos** — e por que `abs(-7.9)` dá `7`
- **A tabela de divisão inteira × real** (o slide 8, que é ouro puro para prova)
- **`#define`** — macros do pré-processador
- **`do…while`** aplicado ao Método Babilônico de raiz quadrada
- **`math.h`** e como ler um manual com `man`
- **Matrizes**: `double M[MAX][MAX]`, representação na memória, e **por que é obrigatório informar o número de colunas mas não o de linhas** ← isso é aplicação direta da seção 19 desta parte
- Multiplicação de matrizes e o custo O(n³)
- Exercícios: aplicação financeira e matriz de permutação

E, ao final da Parte 3, o fechamento completo que você pediu desde o início: resumo geral, mapa mental textual, tabela comparativa de estruturas, prioridades para prova, pegadinhas, e **20 questões de revisão com gabarito comentado**.


<div style="page-break-after: always"></div>

# MC-202 — Curso de C, Parte 2 (Unidade 3)
## Aula completa e comentada — **PARTE 3: Números Reais, Casting, `#define` e Matrizes**

> Cobre os 22 slides de "MC-202 — Curso de C — Parte 2".
> Continuação direta das Partes 1 e 2. Assume que você já entendeu **vetores** e a **seção 19 da Parte 2** (o nome do vetor é o endereço do primeiro elemento) — sem isso, matrizes viram magia.

---

# 21. O problema motivador: raiz quadrada pelo Método Babilônico (slide 2)

## 21.1 A ideia simples

Você quer calcular √x, mas só pode usar `+`, `−`, `×` e `÷`. Como?

A estratégia é **chutar e melhorar o chute repetidamente**, até que o chute pare de mudar.

## 21.2 O algoritmo dos slides

> **Método Babilônico (ou de Heron):**
> 1. Seja y₁ uma estimativa para y = √x. Por exemplo, y₁ = x. Quanto melhor a estimativa, mais rápido o algoritmo.
> 2. Faça yₙ = ½ (yₙ₋₁ + x / yₙ₋₁)
> 3. Se |yₙ − yₙ₋₁| for "grande", volte para 2
> 4. Devolva yₙ

## 21.3 Por que essa fórmula funciona — a intuição do retângulo

A fórmula parece tirada da cartola. Não é. Aqui está a intuição:

Suponha que você quer √16 = 4. Pense num **retângulo de área 16**. Se um lado mede `y`, o outro necessariamente mede `16/y`. A raiz quadrada é o caso em que o retângulo vira um **quadrado**, ou seja, os dois lados são iguais.

Chute `y = 16`. Então o outro lado é 16/16 = 1. Retângulo 16 × 1 — muito alongado, longe de um quadrado.

O que fazer? **Tire a média dos dois lados**: (16 + 1)/2 = 8,5. Isso é exatamente a fórmula do slide.

Agora o retângulo é 8,5 × 1,88. Ainda alongado, mas *bem menos*. Repita:

| Iteração | y (um lado) | x/y (outro lado) | média = novo y |
|---|---|---|---|
| 1 | 16 | 1 | 8,5 |
| 2 | 8,5 | 1,88 | 5,19 |
| 3 | 5,19 | 3,08 | 4,14 |
| 4 | 4,14 | 3,86 | 4,00 |
| 5 | 4,00 | 4,00 | **4,00** ✔ |

Quando os dois lados ficam iguais, o retângulo virou quadrado — e o lado é a raiz quadrada.

### Analogia: o retângulo que quer virar quadrado

**Correspondência:**

| Analogia | Conceito |
|---|---|
| Área fixa do retângulo | O número `x` |
| Um lado do retângulo | O chute `y` |
| O outro lado | `x / y` (obrigatoriamente) |
| Tirar a média dos dois lados | `y = (y + x/y) / 2` |
| Retângulo virou quadrado | Convergiu: `y ≈ x/y` |
| Lado do quadrado | √x |
| "Os lados quase não mudam mais" | `\|yₙ − yₙ₋₁\| ≤ ERRO` |

**Por que converge tão rápido:** o método sempre "cerca" a resposta — se um lado está acima de √x, o outro está abaixo, e a média cai entre os dois. Cada iteração **dobra o número de dígitos corretos**. Eu medi rodando o programa:

| x | iterações até convergir |
|---|---|
| 2 | 6 |
| 9 | 7 |
| 1 000 000 000 000 | 26 |

Vinte e seis iterações para um número de 13 dígitos. Isso é convergência **quadrática** — e é por isso que o método sobreviveu 2 000 anos.

## 21.4 A versão em Python (slide 3)

```python
ERRO = 1e-12

def raiz_quadrada(x):
    y = x
    erro_pequeno = False
    while not erro_pequeno:
        anterior = y
        y = (y + x / y) / 2
        if abs(anterior - y) <= ERRO:
            erro_pequeno = True
    return y
```

Repare na gambiarra: a variável `erro_pequeno` existe só porque Python **não tem `do...while`**. Você precisa entrar no laço pelo menos uma vez (para ter um `anterior` com que comparar), então usa uma flag.

Os slides então perguntam: *como representar números reais em C? Como ler e escrever tais números?* É a deixa para os próximos assuntos.

## ✅ O que eu preciso saber deste tópico

- Explicar a ideia do método (chutar, calcular o outro lado, tirar a média).
- Escrever a fórmula `y = (y + x/y) / 2`.
- Explicar o critério de parada: quando o chute para de mudar.
- Saber que a convergência é muito rápida (dobra os dígitos corretos por iteração).

---

# 22. Números reais: `float` e `double` (slide 4)

## 22.1 A ideia simples

`int` guarda números inteiros. Para guardar `3,14` você precisa de outro tipo. Em C há dois principais, e a diferença entre eles é **quanta precisão** você quer pagar.

## 22.2 O que dizem os slides

> **`float`** — número de ponto flutuante de **precisão simples**, em geral **32 bits**. Leitura e escrita com `%f`, ou `%e` (notação científica), ou `%g` (o mais curto dos dois).
>
> **`double`** — precisão **dupla**, em geral **64 bits**. Maior precisão, mas mais lento e gasta mais memória. **É o mais usado em geral.** Leitura/impressão com `%lf`, `%le` ou `%lg`.

## 22.3 O que "ponto flutuante" significa, e por que ele mente

Este é o conceito mais mal-entendido de toda a programação, então vale parar.

Um número de ponto flutuante guarda um número em **notação científica binária**: um sinal, uns dígitos significativos (a *mantissa*) e um expoente. O "ponto flutua" porque o expoente decide onde ele fica.

A consequência: **há um número finito de dígitos significativos.** `float` tem cerca de **7 dígitos decimais**; `double`, cerca de **15–16**.

E aqui está o problema: assim como você não consegue escrever 1/3 exatamente em decimal (0,3333…), **o computador não consegue escrever 0,1 exatamente em binário**. Eu rodei isto:

```
float  0.1 = 0.10000000149011611938
double 0.1 = 0.10000000000000000555
```

Nenhum dos dois é 0,1. O `double` erra bem mais tarde, mas erra.

### ⚠️ A consequência prática: NUNCA compare reais com `==`

Testei duas situações:

```
0.1 * 10 == 1.0 ?  → 1 (verdadeiro, por sorte)

double y = 0;
for (i = 0; i < 10; i++) y += 0.1;
y == 1.0 ?  → 0 (FALSO!)   y vale 0.99999999999999989
```

Somar 0,1 dez vezes **não dá 1,0**. Dá 0,99999999999999989. Se seu programa depender de `if (y == 1.0)`, ele vai falhar — e você não vai entender por quê.

**A regra:** compare reais por **proximidade**, não por igualdade.

```c
if (fabs(a - b) < 1e-9)     /* certo: "a e b são praticamente iguais" */
if (a == b)                 /* ERRADO para double/float */
```

E olha só: é **exatamente isso** que o Método Babilônico faz. O critério de parada é `fabs(anterior - y) > ERRO`, não `anterior != y`. Se fosse `!=`, o laço poderia nunca parar, porque os dois valores podem ficar oscilando na última casa binária para sempre. O algoritmo dos slides está certo justamente por causa disso.

### Analogia: a régua com marcações finitas

Uma régua de 30 cm com marcações de milímetro. Você consegue medir 15,3 cm. Mas 15,347 cm? Você anota "15,3" — o mais próximo que a régua permite.

Agora meça dez pedaços de 0,1 cm cada e some. Se cada medição tem um errinho de arredondamento, a soma acumula dez errinhos.

**Correspondência:** as marcações da régua são os bits da mantissa; o arredondamento para a marca mais próxima é o erro de representação; o acúmulo de erros na soma é o `0.99999999999999989`; usar uma régua com marcações mais finas é trocar `float` por `double`.

## 22.4 A tabela de especificadores — cuidado com a pegadinha

| Tipo | `printf` | `scanf` |
|---|---|---|
| `float` | `%f` | `%f` |
| `double` | **`%f`** ou `%lf` | **`%lf`** (obrigatório) |

O slide 4 lista `%lf` para `double` nos dois casos. Isso está correto e é a recomendação certa. Mas você precisa saber por quê a assimetria existe, porque isso confunde muita gente:

- No **`scanf`**, `%f` e `%lf` são **diferentes e não intercambiáveis**. `%f` diz "escreva 4 bytes aqui"; `%lf` diz "escreva 8 bytes". Usar `%f` para ler um `double` **corrompe a memória**.
- No **`printf`**, por uma regra antiga do C (promoção de argumentos), todo `float` vira `double` na passagem. Por isso `%f` funciona para ambos. Desde o C99, `%lf` no `printf` também é válido e significa a mesma coisa.

**Regra prática, à prova de erro: use `%lf` para `double` sempre, em `printf` e `scanf`.** É o que os slides fazem.

## 22.5 `%f`, `%e`, `%g` — quando usar cada um

| Especificador | Formato | `printf` de 1234.5 | `printf` de 0.00002 |
|---|---|---|---|
| `%f` | decimal fixo, 6 casas | `1234.500000` | `0.000020` |
| `%e` | científico | `1.234500e+03` | `2.000000e-05` |
| `%g` | o mais curto dos dois | `1234.5` | `2e-05` |

Controle de casas decimais:

```c
printf("%.2lf", 3.14159);    /* 3.14 — duas casas */
printf("%8.2lf", 3.14159);   /* "    3.14" — largura 8, alinhado à direita */
```

O `%.2lf` aparece no exercício financeiro do slide 19, e é o que você usa para imprimir dinheiro.

## 22.6 `float` ou `double`? A resposta prática

Os slides dizem que `double` "é o mais usado em geral". Concordo, e vale explicitar o porquê:

- A diferença de velocidade é irrelevante em processadores modernos.
- A diferença de memória (4 vs 8 bytes) só importa em vetores gigantescos.
- Os 7 dígitos de um `float` acabam rápido demais.
- As funções de `math.h` trabalham com `double` nativamente.

**Use `double`.** Só use `float` se tiver um motivo concreto (memória apertada, GPU, sistema embarcado).

## ✅ O que eu preciso saber deste tópico

- Diferenciar `float` e `double` em bits, precisão e uso recomendado.
- **Explicar por que `0.1` não é exato e por que não se compara reais com `==`.**
- Escrever a comparação correta com `fabs(a-b) < epsilon`.
- Saber que `scanf` de `double` exige `%lf`, obrigatoriamente.
- Saber usar `%.2lf`.

---

# 23. O código em C do Método Babilônico (slides 5, 9, 10)

```c
#include <stdio.h>
#include <math.h>
#define ERRO 1e-12

double raiz_quadrada(double x) {
  double y = x, anterior;
  do {
    anterior = y;
    y = (y + x / y) / 2;
  } while (fabs(anterior - y) > ERRO);
  return y;
}

int main() {
  double x;
  printf("Entre com o numero:\n");
  scanf("%lf", &x);
  printf("Raiz quadrada: %lf\n", raiz_quadrada(x));
  return 0;
}
```

## 23.1 Linha a linha

| Linha | O que faz |
|---|---|
| `#include <math.h>` | traz `fabs` (e exige a flag `-lm` na compilação) |
| `#define ERRO 1e-12` | cria a macro `ERRO` — seção 24 |
| `double raiz_quadrada(double x)` | recebe um `double`, devolve um `double` |
| `double y = x, anterior;` | `y` começa valendo `x` (o chute inicial do slide 2); `anterior` fica sem valor por enquanto |
| `do {` | entra no laço **sem testar nada** |
| `anterior = y;` | guarda o chute atual antes de melhorá-lo |
| `y = (y + x / y) / 2;` | a fórmula babilônica |
| `} while (fabs(anterior - y) > ERRO);` | repete **enquanto** a mudança ainda for grande |
| `return y;` | devolve o chute final |
| `scanf("%lf", &x);` | lê um `double` — `%lf` e `&`, como sempre |
| `printf("... %lf\n", raiz_quadrada(x));` | chama a função dentro do `printf` (Parte 1, seção 13) |

## 23.2 Por que `do...while` e não `while` (slide 10)

> Estamos usando `do ... while` que não existe em Python. **Calculamos `y` e `anterior` antes de testar a condição.**

Esta é a justificativa perfeita, e vale ver o contraste:

Em **Python** (slide 3), sem `do...while`, foi preciso inventar a variável `erro_pequeno` e um `while not erro_pequeno`. Três linhas extras só para contornar a falta do construto.

Em **C**, o `do...while` expressa a intenção diretamente: *"faça pelo menos uma vez, depois decida se repete"*. E aqui isso não é conveniência, é **necessidade lógica**: a condição compara `anterior` com `y`, mas `anterior` só recebe valor **dentro** do laço. Testar antes seria comparar com lixo.

Isto é exatamente o caso de uso canônico de `do...while` que descrevi na Parte 1, seção 8.2. Guarde o par:

| Situação | Laço |
|---|---|
| Pode ser que eu não precise executar nenhuma vez | `while` |
| Preciso executar pelo menos uma vez para ter o que testar | `do...while` |

⚠️ E lembre: `do { } while (cond);` **leva ponto e vírgula** no final.

## 23.3 `math.h` e a leitura de manual (slides 5 e 6)

> A biblioteca `math.h` contém várias funções matemáticas. `fabs` devolve o valor absoluto de um número `double`.

O slide 6 mostra o resultado de `man fabs` no terminal, e isso é um ensinamento em si: **aprender a ler o manual é parte da disciplina.** No terminal:

```
man fabs      man printf      man scanf      man strlen
```

Do manual do `fabs`, os pedaços que importam:

```
#include <math.h>
double fabs(double x);
Link with -lm.
```

Três informações essenciais em três linhas: qual header incluir, qual a assinatura, e que precisa da flag `-lm`. É sempre esse o padrão. Quando você não souber uma função, `man` primeiro.

Funções úteis de `math.h`: `sqrt`, `pow`, `fabs`, `floor`, `ceil`, `round`, `sin`, `cos`, `log`, `exp`.

> ⚠️ Ironia útil: `sqrt(x)` já calcula raiz quadrada. O exercício inteiro é didático — o objetivo é entender o método iterativo, não obter a raiz.

## 23.4 🔴 Dois bugs reais neste código

Você me pediu para apontar problemas. Eu rodei o programa dos slides com casos de borda. Resultados:

| Entrada | Saída | Iterações |
|---|---|---|
| `2` | 1.414214 ✔ | 6 |
| `9` | 3.000000 ✔ | 7 |
| `1e12` | 1000000.000000 ✔ | 26 |
| **`0`** | **`-nan`** ❌ | 1 |
| **`-4`** | **laço infinito** ❌ | travou (interrompi em 201) |

### Bug 1: x = 0 produz NaN

Com `x = 0`, o chute inicial é `y = 0`, e a fórmula calcula `x / y` = `0 / 0` — **divisão por zero**. Em ponto flutuante isso não causa crash; produz `NaN` ("Not a Number"). O laço então testa `fabs(NaN - NaN) > ERRO`, que é falso (qualquer comparação com NaN é falsa), sai na primeira iteração e devolve `NaN`.

### Bug 2: x negativo trava o programa

Com `x = -4`, a sequência **nunca converge** — os valores oscilam caoticamente para sempre. **O programa entra em laço infinito.** Ele não dá erro, não devolve nada: fica pendurado. Se isso acontecer num corretor automático, é *time limit exceeded* sem explicação.

Faz sentido matematicamente: não existe raiz quadrada real de um número negativo, então o método não tem para onde convergir.

### A correção

```c
double raiz_quadrada(double x) {
  if (x < 0)  return -1;      /* ou trate o erro como preferir */
  if (x == 0) return 0;       /* caso especial: evita 0/0 */
  double y = x, anterior;
  do {
    anterior = y;
    y = (y + x / y) / 2;
  } while (fabs(anterior - y) > ERRO);
  return y;
}
```

**A lição, que já apareceu no exercício de primos da Parte 1:** todo algoritmo iterativo precisa de duas perguntas antes de estar pronto:
1. **Casos de borda:** zero, negativo, o menor valor possível.
2. **Garantia de término:** o laço sempre para? Para *toda* entrada?

Em código de produção sério, laços iterativos costumam ter um limite de segurança:

```c
for (int it = 0; it < 1000 && fabs(anterior - y) > ERRO; it++) { ... }
```

## ✅ O que eu preciso saber deste tópico

- Escrever o método babilônico em C, com `do...while`.
- **Justificar por que `do...while` é obrigatório aqui** (`anterior` só existe dentro do laço).
- Saber que `math.h` exige `-lm`.
- Saber usar `man`.
- Identificar os casos de borda de um algoritmo iterativo (x = 0 e x < 0).

---

# 24. A diretiva `#define` (slide 9)

## 24.1 A ideia simples

> A diretiva `#define` cria uma **macro**: onde aparecer a palavra `ERRO`, substitua por `1e-12`.

É **busca e substitui** de texto, feito antes da compilação.

## 24.2 O detalhe técnico que muda tudo

`#define` **não cria uma variável**. Ela instrui o **pré-processador** — um programa que roda *antes* do compilador e faz edições textuais no seu código.

Quando você escreve:

```c
#define ERRO 1e-12
...
} while (fabs(anterior - y) > ERRO);
```

O compilador nunca vê a palavra `ERRO`. Ele recebe:

```c
} while (fabs(anterior - y) > 1e-12);
```

O mesmo mecanismo do `#include`, que "copia e cola" o arquivo (Parte 1, seção 12.1). Ambas começam com `#` e **nenhuma leva `;`** — não são comandos de C.

### Analogia: o localizar-e-substituir do editor de texto

Antes de imprimir seu trabalho, você aperta Ctrl+H e troca toda ocorrência de "XYZ" por "1e-12". O documento impresso não contém mais "XYZ" em lugar nenhum.

**Correspondência:** o Ctrl+H é o pré-processador; a substituição acontece antes da impressão (compilação); a impressora (compilador) nunca vê o texto original.

## 24.3 A sintaxe, e os dois erros clássicos

```c
#define ERRO 1e-12          /* CERTO */
#define MAX 100             /* CERTO */

#define ERRO = 1e-12;       /* ERRADO — vira "> = 1e-12;" no código */
#define MAX 100;            /* ERRADO — o ; entra na substituição */
```

O segundo erro é traiçoeiro. `int v[MAX];` viraria `int v[100;];` — erro de sintaxe numa linha que parece perfeita, com a mensagem apontando para o lugar errado.

**Regra: `#define NOME valor`. Sem `=`, sem `;`.** Por convenção, macros são escritas em MAIÚSCULAS — é assim que você reconhece uma no meio do código.

## 24.4 Para que serve na prática

**1. Números mágicos.** Compare:

```c
double A[100][100];
...
if (n > 100) ...          /* e se você precisar mudar para 200? */
```
```c
#define MAX 100
double A[MAX][MAX];
...
if (n > MAX) ...          /* muda em UM lugar só */
```

Isto resolve exatamente o problema que apontei na Parte 2, seção 16.5, onde o número `10` aparecia três vezes.

**2. Tamanhos de vetores e matrizes.** É por isso que os slides 14 e 17 usam `#define MAX 100`: em C, o tamanho de um vetor tem que ser uma **constante conhecida em tempo de compilação**. `#define` fornece isso.

**3. Constantes.** `#define PI 3.14159265358979`

## 24.5 Detalhe: `#define` vs `const`

Existe outra forma de criar constantes:

```c
const double ERRO = 1e-12;    /* variável de verdade, só que imutável */
```

| | `#define` | `const` |
|---|---|---|
| O que é | substituição de texto | variável real na memória |
| Tem tipo | não | sim (o compilador checa) |
| Serve para tamanho de vetor | **sim** | não, em C99 (`int v[TAM]` viraria VLA — barrado pela flag `-Wvla`) |
| Aparece no depurador | não | sim |

**Na prática desta disciplina:** use `#define` para tamanhos de vetores/matrizes (é obrigatório), e é aceitável usá-lo para as demais constantes também. É o que os slides fazem.

> ⚠️ Cuidado avançado (detalhe, não essencial): macros com expressões precisam de parênteses. `#define DOBRO(x) x*2` faz `DOBRO(1+1)` virar `1+1*2` = 3, não 4. O certo é `#define DOBRO(x) ((x)*2)`. Você provavelmente não vai escrever macros com parâmetros nesta disciplina, mas saiba que a armadilha existe.

## ✅ O que eu preciso saber deste tópico

- Explicar que `#define` é substituição textual feita **antes** da compilação.
- Escrever a sintaxe correta (**sem `=` e sem `;`**).
- Explicar por que `#define MAX 100;` quebra `int v[MAX];`.
- Saber que tamanhos de vetores exigem constante de compilação.
- Saber que macros vão em MAIÚSCULAS por convenção.

---

# 25. Conversão de tipos e casting (slide 7)

## 25.1 A ideia simples

Uma função que espera `double` recebeu um `int`. O que acontece? C **converte automaticamente**. E você também pode forçar a conversão manualmente.

## 25.2 O que dizem os slides

> Em C, as funções recebem parâmetros de um tipo específico e devolvem resultados de um tipo específico. E **tipos podem ser convertidos**:
> - valor `int` pode ser convertido para `double` — escreva `(double) x` — é o que chamamos de **casting**. `1` é convertido para `1.0`
> - valor `double` pode ser convertido para `int` — `1.0` vira `1`, **`1.937` vira `1`**

## 25.3 O ponto crucial: converter para `int` TRUNCA

```c
(int) 1.937   →  1        /* não é 2! */
(int) 1.999   →  1
(int) -1.937  →  -1
```

Eu confirmei rodando. A conversão **descarta a parte fracionária** — não arredonda. Ela corta em direção ao zero, exatamente como a divisão inteira que vimos na Parte 1.

**Se você quer arredondar de verdade:**

```c
#include <math.h>
round(1.937)      /* 2.0 — arredonda ao mais próximo */
(int) round(1.937)  /* 2 */
```

Ou o truque clássico sem `math.h`: `(int)(x + 0.5)` para positivos.

> ⚠️ Erro comum em prova: perguntar quanto vale `(int) 3.99`. A resposta é **3**.

## 25.4 A pergunta do slide 7: `abs(-7.9)` é 7 e `fabs(-3)` é 3.0. Por quê?

> Temos duas funções diferentes que calculam valor absoluto: `int abs(int x)` e `double fabs(double x)`. Mas `abs(-7.9)` é `7` e `fabs(-3)` é `3.0`. Por quê? **Os valores são convertidos automaticamente.**

A resposta dos slides está correta. Detalhando:

**`abs(-7.9)`:** `abs` espera `int`. O valor `-7.9` é convertido para `int` → **truncado** para `-7`. Então `abs(-7)` = `7`. Eu rodei e confirmei: dá `7`.

Note o que se perdeu no caminho: o `,9`. A conversão aconteceu **silenciosamente**, sem aviso.

**`fabs(-3)`:** `fabs` espera `double`. O `int -3` é convertido para `-3.0`, sem perda. `fabs(-3.0)` = `3.0`.

### 🔴 Um detalhe que falta nos slides e que vai te morder

`fabs` está em `math.h`. Mas **`abs` está em `stdlib.h`**, não em `math.h`. Os slides mencionam as duas funções lado a lado sem dizer isso.

Eu testei o que acontece se você esquecer o `#include <stdlib.h>`:

```
Com    stdlib.h:  abs(-7.9) = 7      ← correto
Sem    stdlib.h:  abs(-7.9) = 1      ← LIXO
```

**O resultado muda de 7 para 1 por causa de um `#include` faltando.** O programa compila (com warning) e roda, dando resposta errada.

Guarde: **`abs` → `stdlib.h`. `fabs` → `math.h`.**

## 25.5 Conversão implícita × explícita

**Implícita (automática):** acontece sozinha quando os tipos se misturam.

```c
double y = 5;        /* 5 vira 5.0 */
int n = 3.9;         /* vira 3 — perda silenciosa! */
```

**Explícita (casting):** você força, escrevendo `(tipo)` antes.

```c
(double) x
(int) y
```

**Quando o casting é obrigatório?** Quando você quer evitar uma conversão implícita indesejada — que é o assunto da próxima seção.

## 25.6 ⚠️ A armadilha do casting no lugar errado

Eu testei os dois:

```c
int x = 6, y = 4;
(double) x / y      →  1.5     ✔ converte x, depois divide (real)
(double)(x / y)     →  1.0     ✘ divide inteiro (=1), depois converte
```

**A ordem importa.** `(double)` tem precedência alta e aplica-se ao que vem logo depois. No segundo caso, o parêntese força a divisão a acontecer primeiro — **inteira** — e o `1` resultante vira `1.0`. O dano já estava feito.

**Regra: converta ANTES da operação, não depois.**

## ✅ O que eu preciso saber deste tópico

- Escrever um casting: `(double) x`, `(int) y`.
- **Saber que converter para `int` trunca**, e responder `(int) 3.99 = 3`.
- Explicar por que `abs(-7.9)` é 7 e `fabs(-3)` é 3.0.
- Saber que `abs` está em `stdlib.h` e `fabs` em `math.h`.
- **Explicar a diferença entre `(double)x / y` e `(double)(x / y)`.**

---

# 26. A tabela de divisão inteira × real (slide 8) — ouro para prova

## 26.1 A tabela dos slides

|  | Python | C |
|---|---|---|
| `6 / 4` | 1.5 | **1** |
| `6.0 / 4.0` | 1.5 | 1.5 |
| `6.0 / 4` | 1.5 | 1.5 |
| `6 / 4.0` | 1.5 | 1.5 |
| `6 // 4` | 1 | *operador não existe* |
| `6.0 // 4.0` | 1.0 | *operador não existe* |
| `6.0 // 4` | 1.0 | *operador não existe* |
| `6 // 4.0` | 1.0 | *operador não existe* |
| `6 % 4` | 2 | 2 |
| `6.0 % 4.0` | 2.0 | **erro de compilação** |
| `6.0 % 4` | 2.0 | **erro de compilação** |
| `6 % 4.0` | 2.0 | **erro de compilação** |

> Se necessário, fazemos casting: se `x` vale 6 e `y` vale 4, então `(double)x / y` é `1.5`.

Eu rodei todos os casos de C e confirmei: a tabela está **perfeita**.

## 26.2 A regra única que gera a tabela inteira

Não decore 12 linhas. Decore **uma regra**:

> **Em C, `/` olha para os tipos dos operandos.**
> - **Os dois inteiros** → divisão **inteira** (trunca)
> - **Pelo menos um real** → divisão **real**

E mais duas regras curtas:

> - **`//` não existe em C.** É sintaxe de Python. Em C, `//` inicia um **comentário**!
> - **`%` só funciona com inteiros.** Com real, é **erro de compilação**.

### Por que `//` não existe

Porque em C `//` já significa outra coisa:

```c
int x = 6 // 4;      /* o compilador lê: int x = 6   e o resto é comentário */
```

Isso não é "operador ausente" — é uma armadilha ativa. O código pode até compilar, com significado totalmente diferente. Se você vem de Python, este é um erro que você **vai** cometer uma vez.

### Por que `%` não aceita reais

`a % b` é definido como o resto da divisão **inteira**. Com reais, "resto" não é bem definido. C é rígido e recusa em tempo de compilação — o que, aliás, é bom: erro pego cedo.

> Se você realmente precisar: `fmod(a, b)` de `math.h` faz isso para reais.

## 26.3 O caso prático que sempre aparece

Calcular a média de dois inteiros:

```c
int a = 7, b = 8;

double m1 = (a + b) / 2;            /* 7.0  — ERRADO */
double m2 = (a + b) / 2.0;          /* 7.5  — certo */
double m3 = (double)(a + b) / 2;    /* 7.5  — certo */
```

Em `m1`, `(7+8)/2` = `15/2` = **7** (inteira), e só então o 7 vira 7.0. **A atribuição a um `double` não conserta nada** — o estrago já aconteceu.

**Isto é praticamente garantido em prova.** A pergunta é sempre da forma "por que este código imprime 7.000000 em vez de 7.5?".

## ✅ O que eu preciso saber deste tópico

- **Enunciar a regra: `/` é inteira se ambos os operandos forem inteiros.**
- Saber que `//` não existe em C (e que é comentário).
- Saber que `%` com reais é erro de compilação.
- Corrigir `(a+b)/2` para obter média real.
- Reproduzir a tabela do slide 8 de cabeça.

---

# 27. Matrizes: vetores de vetores (slides 11–17)

Chegamos ao assunto principal desta unidade. E aqui a Parte 2 vai pagar dividendos: quase tudo que você viu sobre vetores se aplica, com uma dimensão a mais.

## 27.1 O problema (slide 11)

> Dadas duas matrizes A e B em ℝⁿˣⁿ, calcular C = A × B.
> `C[i][j]` é o produto escalar da linha `i` de A com a coluna `j` de B:
>
> C[i][j] = Σₖ₌₁ⁿ A[i][k] · B[k][j]

Note que **produto escalar** é exatamente o exercício da Parte 2, seção 20. A multiplicação de matrizes é n² produtos escalares.

## 27.2 A ideia simples

Uma matriz é uma **tabela**: linhas e colunas. Em C, você declara com dois pares de colchetes:

```c
double M[3][4];      /* 3 linhas, 4 colunas */
M[1][2] = 7.5;       /* linha 1, coluna 2 */
```

**Sempre `[linha][coluna]`, nessa ordem, ambos começando em 0.**

## 27.3 Como a matriz está na memória — a chave de tudo

Você aprendeu na Parte 2 que a memória é **linear** — uma fila de bytes. Mas uma matriz é bidimensional. Como conciliar?

**Resposta: C "achata" a matriz, guardando uma linha inteira, depois a próxima.** Isso se chama ordem **row-major** (por linhas).

Eu provei isso rodando um programa com `#define MAX 5`:

```
&M[0][0] = 0x7fff98c9ef60
&M[0][1] = +8 bytes      ← o vizinho na mesma linha
&M[1][0] = +40 bytes     ← 5 doubles depois = uma linha inteira!
sizeof(M) = 200 bytes = 25 doubles
```

E lendo a memória de forma linear, ignorando a estrutura 2D:

```
0 1 2 3 4 | 10 11 12 13 14 | 20 21 ...
└─linha 0─┘ └──linha 1───┘ └─linha 2…
```

A matriz 5×5 está guardada como **25 doubles seguidos**, linha após linha.

### A fórmula do endereço

Assim como no vetor (Parte 2, seção 15.4):

```
endereço de M[i][j] = base + (i × NUM_COLUNAS + j) × tamanho_do_tipo
```

**Fixe essa fórmula.** Ela responde sozinha a pergunta mais importante desta seção, que vem a seguir.

### Analogia: o prédio de apartamentos e a numeração corrida

Um prédio com 5 andares e 5 apartamentos por andar. Duas maneiras de identificar um apartamento:

- **Bidimensional:** "andar 2, apartamento 3" → é como você pensa.
- **Numeração corrida:** os apartamentos são numerados 0 a 24, começando no térreo. → é como a memória guarda.

Para converter: apartamento nº = **andar × 5 + porta**. Andar 2, porta 3 → 2×5+3 = 13.

Agora, a pergunta decisiva: **para fazer essa conta, o que você precisa saber?**

Você precisa saber **quantos apartamentos há por andar** (5). Você **não precisa** saber quantos andares o prédio tem. Se eu te disser "andar 2, porta 3" e você não souber quantas portas há por andar, é impossível calcular.

**Correspondência:**

| Analogia | Conceito |
|---|---|
| O prédio | A matriz |
| Andar | Índice `i` (linha) |
| Porta | Índice `j` (coluna) |
| Numeração corrida 0–24 | Posição linear na memória |
| Apartamentos por andar | **Número de colunas** |
| `andar × 5 + porta` | `i × NUM_COLUNAS + j` |
| Precisa saber portas por andar | **Precisa saber o número de colunas** |
| Não precisa saber quantos andares | **Não precisa saber o número de linhas** |

Guarde essa analogia — ela é a resposta pronta para a seção 27.6.

## 27.4 Declaração (slide 17)

> `double A[MAX][MAX];` declara uma matriz MAX × MAX de doubles.
> Números de linhas e colunas podem ser diferentes: 10 linhas e 3 colunas → `int matriz[10][3];`
> Podemos também declarar matrizes multidimensionais: `double M[10][5][7];`

Tudo correto. Pontos a observar:

**1. O tamanho tem que ser constante de compilação** — daí o `#define MAX 100`. Você não pode escrever `double A[n][n]` com `n` lido do teclado (seria um VLA, barrado pela flag `-Wvla`).

**2. Isso significa reservar o pior caso.** `double A[100][100]` são 10 000 doubles = **80 KB**, mesmo que você use só uma matriz 3×3. E o slide 17 declara **três** dessas na `main`: 240 KB.

> ⚠️ **Cuidado real que os slides não mencionam:** variáveis locais vivem na *pilha*, que tem tamanho limitado (tipicamente 8 MB no Linux). `double A[1000][1000]` são 8 MB de uma vez só — **estouro de pilha e segfault imediato**, antes mesmo de o programa fazer qualquer coisa. Com `MAX 100` você está seguro; saiba que o limite existe.

**3. Inicialização:**

```c
int m[2][3] = {{1,2,3}, {4,5,6}};
double M[MAX][MAX] = {0};          /* zera tudo */
```

## 27.5 Percorrendo: o padrão dos dois `for` aninhados

```c
for (int i = 0; i < n; i++)           /* para cada linha */
  for (int j = 0; j < n; j++)         /* para cada coluna */
    ... M[i][j] ...
```

O `for` externo escolhe a linha; o interno varre as colunas daquela linha. Ordem de visita: `M[0][0]`, `M[0][1]`, …, `M[0][n-1]`, `M[1][0]`, …

Repare que essa ordem coincide com a ordem na memória — o que, por acaso, é a maneira mais rápida de percorrer uma matriz (aproveita o cache do processador). Percorrer por colunas funciona igual, mas é mais lento.

**Custo de percorrer uma matriz n×n: O(n²).**

## 27.6 🔑 Matrizes como parâmetros — a regra que confunde todo mundo

O slide 14 traz a regra:

> Matrizes têm sempre um tamanho definido. Estamos usando um `#define` para esse tamanho. **E temos que passar o número de colunas para a função — passar o número de linhas é opcional.**

Ou seja:

```c
void f(double M[][MAX], int n)      /* colunas OBRIGATÓRIO, linhas omitido */
void f(double M[MAX][MAX], int n)   /* também vale */
void f(double M[][], int n)         /* NÃO COMPILA */
```

### Por que essa assimetria bizarra? A resposta

Aqui a Parte 2 e a analogia do prédio se encontram. Vamos juntar tudo:

1. Pela Parte 2, seção 19: quando você passa um vetor para uma função, o que é copiado é **o endereço do primeiro elemento**. O mesmo vale para matrizes — a função recebe apenas o endereço de `M[0][0]`.
2. Dentro da função, quando você escreve `M[i][j]`, o compilador precisa **calcular** o endereço: `base + (i × NUM_COLUNAS + j) × 8`.
3. Ele tem a `base` (foi passada) e tem `i` e `j` (você escreveu). Falta **`NUM_COLUNAS`**.
4. Esse número **não vem junto** com o endereço. Então você tem que declará-lo no parâmetro.
5. E o número de **linhas** não aparece na fórmula em lugar nenhum. Por isso é dispensável.

É exatamente o prédio: para converter "andar 2, porta 3" em "apartamento 13", você precisa saber quantas portas por andar. Quantos andares o prédio tem é irrelevante para a conta.

**Esta é a explicação, e ela cai em prova.** Se você souber recitar a fórmula `i × colunas + j`, a resposta sai sozinha.

### ⚠️ E note uma sutileza que engana muita gente

No cabeçalho é `double M[][MAX]` — **`MAX`, não `n`!**

O `n` é quantas linhas/colunas você está *usando*. O `MAX` é como a matriz está *fisicamente organizada* na memória. A fórmula do endereço usa o layout físico, não o lógico.

Se você escrevesse `double M[][n]`, o cálculo do endereço estaria errado e a função leria posições completamente equivocadas. É um bug difícil de achar porque o código "parece" certo.

## ✅ O que eu preciso saber deste tópico

- Declarar matrizes, inclusive não-quadradas, e acessar `M[i][j]`.
- **Explicar a ordem row-major e escrever a fórmula do endereço.**
- Escrever o duplo `for` de percurso e saber que custa O(n²).
- **Explicar por que o número de colunas é obrigatório no parâmetro e o de linhas não.**
- Saber que no parâmetro vai `MAX`, não `n`.
- Saber que o tamanho precisa ser constante de compilação (`#define`).

---

# 28. As três funções de matriz (slides 13–16)

O slide 12 estabelece a estratégia, que vale destacar como método de trabalho:

> **Uma boa forma de programar é pensar nas pequenas tarefas.**

```python
n = int(input())
A = le_matriz_quadrada(n)
B = le_matriz_quadrada(n)
C = multiplica_quadradas(A, B, n)
imprime_matriz_quadrada(C, n)
```

Escreva primeiro o programa principal como se as funções já existissem. Depois implemente cada uma. Isso é *decomposição top-down*, e é o mesmo que foi feito no exercício de vetores (Parte 2, seção 20).

O slide 13 mostra as versões em Python e alerta: **"Em C, não há list comprehension!"** — aquele `[[0 for i in range(n)] for j in range(n)]` não tem equivalente. Em C você zera com dois `for` (ou com `= {0}` na declaração).

## 28.1 Impressão (slide 14)

```c
#define MAX 100

void imprime_matriz_quadrada(double M[][MAX], int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%lf ", M[i][j]);
    printf("\n");
  }
}
```

**Linha a linha:**

| Linha | O que faz |
|---|---|
| `void ...(double M[][MAX], int n)` | não devolve nada; recebe a matriz e o tamanho em uso |
| `for (i = 0; i < n; i++) {` | para cada linha — **com chaves**, porque o corpo tem 2 comandos |
| `for (j = 0; j < n; j++)` | para cada coluna — **sem chaves**, corpo de 1 comando |
| `printf("%lf ", M[i][j]);` | imprime o elemento e um espaço |
| `printf("\n");` | **fora do `for` interno** — quebra a linha ao terminá-la |

**O detalhe que faz o programa funcionar** é a posição daquele `printf("\n")`. Ele pertence ao `for` externo, não ao interno. Se estivesse dentro do interno, cada número sairia numa linha. Se estivesse fora dos dois, tudo sairia numa linha só.

### A pergunta do slide 14

> Note que um `for` usa `{` e `}`, mas o outro não… **E se não usarmos `{` e `}` no primeiro `for`?**

Excelente pergunta armadilha. Se você tirasse as chaves do `for` externo:

```c
for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      printf("%lf ", M[i][j]);
    printf("\n");                  /* ← agora está FORA de tudo */
```

O `for` externo passaria a controlar **apenas o `for` interno** (que é um único comando). O `printf("\n")` viraria um comando solto depois do laço, executado **uma única vez**.

Resultado: todos os n² números numa linha só, e uma quebra de linha no final.

**E a indentação continuaria dizendo que está tudo certo** — o exato bug da Parte 1, seção 5.2. Este é um dos melhores exemplos do material.

## 28.2 Leitura (slide 15)

```c
void le_matriz_quadrada(double M[][MAX], int n) {
  int i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      scanf("%lf", &M[i][j]);
}
```

O slide abre com a frase que conecta tudo:

> **Não podemos devolver matrizes… mas podemos passá-las como parâmetro e modificá-las. O mesmo que fizemos para vetores.**

Isto é literalmente a seção 19 da Parte 2 aplicada. A função recebe o **endereço** da matriz, então escreve direto na memória da `main`. Não há retorno porque não precisa haver.

**Note o `&M[i][j]`:** `scanf` precisa escrever, logo precisa do endereço daquela célula. Mesma regra de sempre.

E o slide observa:

> Note que **ambos os `for` não usam `{` e `}`** — as linhas 4 e 5 correspondem a **um único comando**!

Perfeito. O `for` interno inteiro (cabeçalho + `scanf`) conta como um comando para o `for` externo. Por isso funciona sem chaves aqui — ao contrário do caso da impressão, onde havia dois comandos.

## 28.3 Multiplicação (slide 16)

```c
void multiplica_quadradas(double A[][MAX], double B[][MAX],
                          double C[][MAX], int n) {
  int i, j, k;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      C[i][j] = 0;
      for (k = 0; k < n; k++)
        C[i][j] += A[i][k] * B[k][j];
    }
}
```

**Análise:**

| Elemento | Significado |
|---|---|
| `A`, `B` | matrizes de entrada |
| **`C`** | **matriz de saída** — "C é passada como parâmetro para ser alterada" (slide 16) |
| `i` | linha de A e de C |
| `j` | coluna de B e de C |
| `k` | o índice que percorre a linha de A **e** a coluna de B |
| `C[i][j] = 0;` | zera o acumulador — **essencial**, porque `C` contém lixo |
| `C[i][j] += A[i][k] * B[k][j];` | acumula a soma da fórmula matemática |

Repare em `A[i][k]` e `B[k][j]`: o mesmo `k` é a **coluna** em A e a **linha** em B. É isso que implementa "produto escalar da linha i de A com a coluna j de B".

Mais uma vez o padrão *"buffer de saída como parâmetro"* da Parte 2, seção 20.2. `C` é a saída porque não se devolve matriz.

### ⚠️ A linha `C[i][j] = 0;` não é opcional

Se você esquecê-la, `+=` acumula em cima de **lixo** (Parte 1, seção 7.2) e a matriz resultante é aleatória. E, pior: com sorte o lixo é zero e o programa "funciona" na sua máquina.

### A observação sobre chaves (slide 16)

> O `for` da linha 4 não precisa de `{` e `}` — tem uma única expressão dentro dele, o `for` de 5–9. O `{` e `}` pode ser omitido para encurtar o código, ou pode ser colocado para deixar explícito. **Faça como te deixar mais confortável! E cuidado para a indentação incorreta não te confundir!**

Concordo integralmente com esse conselho, e reforço a recomendação que dei na Parte 1: **como aluno, use as chaves.** O custo é dois caracteres; o benefício é nunca cair na armadilha da indentação mentirosa.

### Complexidade: O(n³)

Três laços aninhados, cada um de 0 a n−1 ⇒ **n³ multiplicações**.

| n | operações |
|---|---|
| 10 | 1 000 |
| 100 | 1 000 000 |
| 1 000 | 1 000 000 000 |

Dobrar `n` multiplica o tempo por **8**. Esse é seu primeiro encontro com um algoritmo cúbico, e é um bom marco: O(n) foi o vetor, O(n²) foi percorrer a matriz, O(n³) é multiplicá-las.

> Detalhe cultural: existem algoritmos melhores (Strassen, O(n^2.807)) — mas isso é assunto de outra disciplina.

## 28.4 A `main` (slide 17)

```c
int main() {
  int n;
  double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
  scanf("%d", &n);
  le_matriz_quadrada(A, n);
  le_matriz_quadrada(B, n);
  multiplica_quadradas(A, B, C, n);
  imprime_matriz_quadrada(C, n);
  return 0;
}
```

Note: ao passar a matriz, escreve-se **só o nome** — `le_matriz_quadrada(A, n)`. Sem colchetes, sem `&`. Igual a vetores.

> 🔴 Mesmo problema da Parte 2, seção 20.5: **`n` não é validado**. Se o usuário digitar 500, as funções escrevem muito além dos limites das matrizes. Falta um `if (n < 1 || n > MAX) return 1;`

## ✅ O que eu preciso saber deste tópico

- Escrever as três funções de matriz com o cabeçalho correto.
- **Explicar por que o `printf("\n")` fica no `for` externo.**
- Explicar o que aconteceria se as chaves do `for` externo fossem removidas na impressão.
- Explicar por que `C[i][j] = 0;` é obrigatório.
- Saber que multiplicação de matrizes é **O(n³)**.
- Explicar por que `C` é parâmetro em vez de retorno.

---

# 29. Exercício resolvido: aplicação financeira (slides 18–19)

## 29.1 Enunciado

> Dada uma aplicação com depósito inicial `inicial`, depósitos mensais de `mensal`, juros mensais de `juros` porcento ao mês e um número de meses `meses`, calcule o valor final.

## 29.2 A solução dos slides

```c
#include <stdio.h>
#include <math.h>

int main() {
    double inicial, mensal, juros, meses, valorFinal;

    printf("Digite o depósito inicial: ");
    scanf("%lf", &inicial);
    /* ... lê mensal, juros, meses da mesma forma ... */

    valorFinal = inicial;
    for (int i = 0; i < meses; i++) {
        valorFinal *= (1 + juros/100);
        valorFinal += mensal;
    }

    printf("O valor final da aplicação é: %.2lf\n", valorFinal);
    return 0;
}
```

## 29.3 A lógica

O núcleo são duas linhas dentro do laço, e a **ordem delas define o modelo financeiro**:

1. `valorFinal *= (1 + juros/100);` — rende juros sobre o saldo atual.
2. `valorFinal += mensal;` — deposita a parcela do mês.

Ou seja: **primeiro rende, depois deposita.** O depósito do mês *m* só começa a render no mês *m+1*.

O `/100` converte porcentagem em fração: 2% → `1 + 2/100` = `1.02`, ou seja, multiplicar por 1,02.

⚠️ **Observe que `juros` é `double`.** Se fosse `int`, `juros/100` seria divisão inteira (seção 26!) e daria **zero** para qualquer taxa menor que 100%. O programa renderia 0% de juros. É a armadilha da seção 26 aparecendo num contexto real.

Trace com inicial = 1000, mensal = 100, juros = 1%, meses = 3:

| Mês | rende ×1,01 | deposita +100 |
|---|---|---|
| 1 | 1010,00 | 1110,00 |
| 2 | 1121,10 | 1221,10 |
| 3 | 1233,31 | **1333,31** |

O `%.2lf` imprime `1333.31` — duas casas, como convém a dinheiro.

## 29.4 🔴 Três problemas neste código

### Problema 1: `meses` deveria ser `int`

```c
double inicial, mensal, juros, meses, valorFinal;
                                ↑ isto está errado conceitualmente
```

Número de meses é uma **contagem** — inerentemente inteiro. Declarar como `double` gera três consequências ruins:

1. `scanf("%lf", &meses)` aceita `meses = 3.7`. O que significam 3,7 meses?
2. `for (int i = 0; i < meses; i++)` compara um `int` com um `double`. Funciona (converte), mas é comparação de tipos mistos.
3. Se o usuário digitar `3.9`, o laço roda **3 vezes** (i vai 0,1,2 e para quando 3 < 3.9 é falso… na verdade roda 4 vezes: i=0,1,2,3). Comportamento imprevisível para quem lê o código.

**Correção:** `int meses;` e `scanf("%d", &meses);`

### Problema 2: `#include <math.h>` é inútil aqui

Nenhuma função de `math.h` é usada. O include é inofensivo, mas é ruído — e, se você compilar com `-lm` por causa dele, está carregando uma dependência sem motivo. Provavelmente sobrou de copiar o programa anterior.

### Problema 3: recalcula a mesma coisa n vezes

`(1 + juros/100)` é **constante** e é recalculado a cada iteração. Melhor:

```c
double fator = 1 + juros/100;
for (int i = 0; i < meses; i++) {
    valorFinal = valorFinal * fator + mensal;
}
```

Não muda a complexidade (continua O(meses)), mas é mais limpo e expressa melhor a intenção. Tirar cálculos invariantes de dentro de laços é um hábito que vale cultivar.

> 💡 Curiosidade: existe fórmula fechada para isso (série geométrica), que resolveria em **O(1)** em vez de O(meses). Mas a versão iterativa é mais legível e mais robusta a arredondamentos.

## ✅ O que eu preciso saber deste tópico

- Modelar juros compostos com um laço.
- Explicar por que a ordem "rende, depois deposita" importa.
- **Saber que `juros` como `int` quebraria tudo por divisão inteira.**
- Usar `%.2lf` para dinheiro.
- Identificar que uma contagem deve ser `int`, não `double`.

---

# 30. Exercício resolvido: matriz de permutação (slides 20–21)

## 30.1 Enunciado

> Uma matriz quadrada é uma **matriz de permutação** se em cada linha e em cada coluna há **exatamente um 1** e todos os outros elementos são **0**.

Exemplos:

```
    É permutação:          NÃO é (duas 1s na linha 0):
    0 1 0                  1 1 0
    1 0 0                  0 0 1
    0 0 1                  0 0 0
```

## 30.2 A solução dos slides

```c
int eh_permutacao(double M[][MAX], int n) {
  int soma_linha, soma_coluna;
  for (int i = 0; i < n; i++) {
    soma_linha = 0;
    soma_coluna = 0;
    for (int j = 0; j < n; j++) {
      if (M[i][j] != 0 && M[i][j] != 1)
        return 0;
      soma_linha  += M[i][j];
      soma_coluna += M[j][i];
    }
    if (soma_linha != 1)
      return 0;
    if (soma_coluna != 1)   // aprenderemos "ou" em breve
      return 0;
  }
  return 1;
}
```

## 30.3 A ideia — e por que ela é elegante

O algoritmo verifica três condições **numa passada só**:

1. Todo elemento é 0 ou 1.
2. Cada linha soma exatamente 1.
3. Cada coluna soma exatamente 1.

Se as três valem, é matriz de permutação. (E são necessárias e suficientes: se só há 0s e 1s e a linha soma 1, então há exatamente um 1 nela.)

**O truque bonito** está nestas duas linhas:

```c
soma_linha  += M[i][j];     /* percorre a LINHA i    → varia a coluna */
soma_coluna += M[j][i];     /* percorre a COLUNA i   → varia a linha  */
```

Índices **trocados**. Com o mesmo `j`, uma linha varre a linha `i` e a outra varre a coluna `i`. Duas verificações pelo preço de um laço.

Eu testei a função com três matrizes:

| Matriz | Resultado | Esperado |
|---|---|---|
| `{{0,1,0},{1,0,0},{0,0,1}}` | 1 | 1 ✔ |
| `{{1,1,0},{0,0,1},{0,0,0}}` | 0 | 0 ✔ |
| Identidade 3×3 | 1 | 1 ✔ |

**A função está funcionalmente correta.** Compila sem warnings, inclusive com `-Wall -Werror`.

## 30.4 A observação do próprio slide

```c
if (soma_coluna != 1)   // aprenderemos "ou" em breve
```

O professor está sinalizando que os dois `if` separados poderiam virar um só:

```c
if (soma_linha != 1 || soma_coluna != 1)
    return 0;
```

O operador `||` (ou) é assunto da próxima unidade. Note também que `//` aqui é **comentário** — e não o operador de divisão inteira do Python (seção 26.2). Boa coincidência para reforçar o ponto.

## 30.5 🔴 Duas práticas questionáveis

### Prática 1: comparar `double` com `==` / `!=`

```c
if (M[i][j] != 0 && M[i][j] != 1)
```

Isto compara reais por igualdade exata — precisamente o que a seção 22.3 diz para não fazer.

**Aqui funciona**, porque os valores vêm de `scanf("%lf")` lendo "0" e "1", que são representáveis exatamente em binário. Não há aritmética antes, logo não há acúmulo de erro.

**Mas é frágil.** Se a matriz fosse resultado de um cálculo — digamos, o produto de duas matrizes de permutação — um elemento poderia sair como `0.9999999999999998` e a função diria "não é permutação". Um bug invisível.

**E a pergunta de fundo:** por que essa matriz é de `double` se ela só contém 0 e 1? Uma matriz de permutação é naturalmente `int`. A escolha do tipo é o problema real; o `!=` é só o sintoma. Provavelmente `double` foi mantido para reaproveitar `le_matriz_quadrada`.

### Prática 2: acumular `double` em variável `int`

```c
int soma_linha;
soma_linha += M[i][j];      /* M[i][j] é double! */
```

Isso faz uma conversão implícita `double → int` **a cada iteração**, com truncamento (seção 25.3). Como os valores são exatamente 0 e 1, não há perda. Mas se houvesse um `0.5` na matriz, `0 + 0.5` truncaria para `0` — e a soma ficaria silenciosamente errada.

Neste código específico isso não causa resposta errada (o `return 0` do teste anterior pega qualquer valor fora de {0,1} antes que importe), mas é o tipo de mistura de tipos que costuma virar bug em código maior.

**A versão que eu recomendaria:**

```c
int eh_permutacao(int M[][MAX], int n) {      /* int, não double */
  for (int i = 0; i < n; i++) {
    int soma_linha = 0, soma_coluna = 0;      /* declara no menor escopo */
    for (int j = 0; j < n; j++) {
      if (M[i][j] != 0 && M[i][j] != 1)
        return 0;
      soma_linha  += M[i][j];
      soma_coluna += M[j][i];
    }
    if (soma_linha != 1 || soma_coluna != 1)
      return 0;
  }
  return 1;
}
```

## 30.6 Complexidade

Dois laços aninhados de `n` ⇒ **O(n²)**, e cada iteração faz trabalho constante. Como a matriz tem n² elementos e você precisa olhar todos, **O(n²) é o ótimo** — não existe algoritmo melhor.

Compare com a multiplicação de matrizes, que é O(n³). Verificar é mais barato que multiplicar.

## ✅ O que eu preciso saber deste tópico

- Definir matriz de permutação e as três condições verificadas.
- **Explicar o truque `M[i][j]` vs `M[j][i]`** para varrer linha e coluna juntas.
- Saber que a função é O(n²) e que isso é ótimo.
- Identificar a fragilidade de comparar `double` com `!=`.
- Reescrever os dois `if` usando `||`.

---

# 📌 Consolidação da Parte 3

## Mapa dos conceitos desta unidade

```
Precisa representar números reais
        ↓
float (32 bits, ~7 dígitos) × double (64 bits, ~15 dígitos) → USE double
        ↓
Ponto flutuante é APROXIMADO
        ├──→ 0.1 não é exato
        ├──→ NUNCA compare com ==, use fabs(a-b) < eps
        └──→ é por isso que o Método Babilônico para com fabs(...) > ERRO
        ↓
Misturar int e double gera CONVERSÃO
        ├──→ implícita: acontece sozinha (int→double sem perda, double→int TRUNCA)
        ├──→ explícita: casting (double)x
        ├──→ (double)x/y  ≠  (double)(x/y)
        └──→ / é inteira se AMBOS forem int ──→ tabela do slide 8
        ↓
#define: substituição de texto ANTES de compilar
        └──→ obrigatório para tamanho de vetor/matriz
        ↓
MATRIZ = vetor de vetores, guardada linha após linha (row-major)
        ↓
endereço de M[i][j] = base + (i × COLUNAS + j) × tam
        ├──→ colunas OBRIGATÓRIO no parâmetro
        ├──→ linhas dispensável
        ├──→ percorrer = O(n²)
        └──→ multiplicar = O(n³)
        ↓
Matriz passada por parâmetro É modificada (Parte 2, seção 19)
        └──→ padrão "buffer de saída": void f(A, B, C, n)
```

## Tabela-resumo de complexidades vistas até agora

| Operação | Custo |
|---|---|
| Acessar `v[i]` ou `M[i][j]` | **O(1)** |
| Percorrer vetor de n | **O(n)** |
| Produto escalar / Hadamard | **O(n)** |
| Percorrer matriz n×n | **O(n²)** |
| Verificar matriz de permutação | **O(n²)** |
| Multiplicar matrizes n×n | **O(n³)** |
| Método Babilônico | ~O(log log) iterações — praticamente constante |

## Os 10 erros mais comuns desta unidade

1. **Comparar `double` com `==`** em vez de `fabs(a-b) < eps`.
2. **`(a+b)/2` esperando média real** → divisão inteira.
3. **`(double)(x/y)`** em vez de `(double)x/y`.
4. **Achar que `(int)3.99` é 4** → é 3, trunca.
5. **`#define MAX 100;`** com ponto e vírgula → quebra `int v[MAX]`.
6. **`%f` no `scanf` para `double`** → tem que ser `%lf`.
7. **`double M[][n]`** no parâmetro → tem que ser `MAX`.
8. **Omitir o número de colunas** no parâmetro de matriz → não compila.
9. **Esquecer `C[i][j] = 0`** antes do `+=` → acumula lixo.
10. **Usar `//` achando que é divisão inteira** → é comentário.

## Essencial × detalhe × prova

**Essencial:** `float` vs `double`; imprecisão de ponto flutuante; regra da divisão; casting e truncamento; `#define`; row-major; a fórmula do endereço; por que colunas são obrigatórias; `do...while`.

**Detalhe:** `%e` vs `%g`; `short`/`long`; `const` vs `#define`; Strassen; limite da pilha.

**Quase certo em prova:**
- Reproduzir a tabela do slide 8 ou responder "quanto vale `6/4` em C?"
- "Por que este código imprime 7.000000 em vez de 7.5?"
- **"Por que passamos o número de colunas mas não o de linhas?"**
- Qual a complexidade da multiplicação de matrizes?
- O que acontece se as chaves do `for` externo forem removidas?

---

# ➡️ Próxima parte

**Parte 4 — Unidade 4: Curso de C, Parte 3** (o PDF que você acabou de enviar). Os assuntos:

- **O tipo `char`** e a tabela **ASCII** — por que uma letra é um número
- **Cifra de César**: aritmética com caracteres, e o famoso truque `letra - 'A'`
- **`scanf("%d ", ...)`** — o espaço no formato e por que "o C é chato na leitura de caracteres"
- **Operadores lógicos** `&&`, `||`, `!` e precedência
- **Strings**: vetores de `char` terminados em `'\0'` — como o `'\0'` resolve o problema de "não existe `len()`" que vimos na Parte 2
- Busca de padrão com coringa `*`
- **`fgets` vs `%s`**, e por que strings não levam `&`
- **`string.h`**: `strlen`, `strcmp`, `strcpy`, `strcat` — e por que **não se compara string com `==`**
- Tipos inteiros: `short`, `long`, `long long`, `unsigned`
- Exercícios: copiar, reverter e comparar strings

E, ao final da Parte 4, o fechamento completo: resumo geral, mapa mental de tudo, tabela comparativa, prioridades de prova, pegadinhas e **20 questões com gabarito comentado**.


<div style="page-break-after: always"></div>

# MC-202 — Curso de C, Parte 3 (Unidade 4)
## Aula completa e comentada — **PARTE 4: `char`, ASCII e Strings**

> Cobre os 26 slides de "MC-202 — Curso de C — Parte 3".
> Continuação das Partes 1–3. Assume vetores (Parte 2) e a ideia de que o nome do vetor é o endereço do primeiro elemento.
> **Ao final há o fechamento do bloco "linguagem C" com 20 questões e gabarito comentado.**

---

# 31. O tipo `char`: letras são números (slides 4–5)

## 31.1 A ideia simples

O computador só guarda números. Então **como ele guarda a letra 'A'?**

Resposta: ele não guarda. Ele guarda **o número 65**, e existe uma tabela combinada dizendo que 65 significa 'A'. Essa tabela é a **ASCII**.

## 31.2 O que dizem os slides

> Uma letra ou caractere em C é representado pelo tipo `char`:
> - **é um número inteiro** — normalmente tem 8 bits (está entre −128 e 127)
> - podemos **somar, subtrair, multiplicar, dividir**, etc
> - como se fosse um `int` mas com menos valores válidos
> - representa caracteres usando a **tabela ASCII**
> - representamos constantes usando **aspas simples**: `'a'`, `'b'`, `'\n'`
> - `'a'` significa o número do caractere a na tabela ASCII — **não precisamos saber qual é esse número exatamente**
> - para ler e imprimir usamos `%c`
> - ex: `printf("letra: %c, código: %d", 'a', 'a');` imprime `letra: a, código: 97`

Aquele último exemplo é a chave de tudo. **O mesmo valor**, `'a'`, impresso de duas formas: com `%c` sai a letra `a`; com `%d` sai o número `97`.

**`char` não é um "tipo texto". É um `int` pequeno.** A diferença é só como você escolhe *enxergar* o número.

### Analogia: o número da camisa do jogador

Num time, cada jogador tem um número de camisa. O número 10 *é* o Pelé, no contexto daquele time.

Se alguém pergunta "quem jogou?", você responde "o Pelé" (`%c`). Se pergunta "qual o número?", você responde "10" (`%d`). **É o mesmo jogador** — só muda a pergunta.

E aqui vem a parte esquisita e útil: como camisas são números, você pode fazer conta com elas. "Quem é o jogador três camisas depois do 10?" → 10 + 3 = 13. Sem sentido no futebol, mas em ASCII isso é ouro: `'A' + 3` é `'D'`.

**Correspondência:**

| Analogia | Conceito |
|---|---|
| Jogador | O caractere |
| Número da camisa | O código ASCII |
| A escalação oficial | A tabela ASCII |
| Perguntar "quem?" | `printf("%c", c)` |
| Perguntar "qual número?" | `printf("%d", c)` |
| Somar números de camisa | Aritmética com `char` |

## 31.3 A tabela ASCII — os três blocos que importam

O slide 5 traz a tabela completa. Você **não precisa decorá-la**. Precisa saber três fatos:

| Bloco | Faixa | Fato útil |
|---|---|---|
| Dígitos `'0'`–`'9'` | 48–57 | **consecutivos** |
| Maiúsculas `'A'`–`'Z'` | 65–90 | **consecutivas** |
| Minúsculas `'a'`–`'z'` | 97–122 | **consecutivas** |

**Que os blocos sejam consecutivos é o que torna tudo possível.** Rodei para confirmar:

```
'A' = 65    'a' = 97    diferença = 32
'0' = 48    '5' - '0' = 5
```

Disso saem os truques que você vai usar a vida inteira:

```c
c - 'A'          /* posição da letra maiúscula no alfabeto: 'C'-'A' = 2 */
'A' + 2          /* a letra na posição 2: 'C' */
c - '0'          /* converte o CARACTERE '5' no NÚMERO 5 */
c + ('a' - 'A')  /* maiúscula → minúscula (soma 32) */
c - ('a' - 'A')  /* minúscula → maiúscula */
```

> ⚠️ Não confunda `'5'` (o caractere, código 48+5=53) com `5` (o número). `'5' - '0'` = 5 é a conversão.

## 31.4 🔴 Erro factual no slide 5

O slide afirma:

> Existem também `\t` (9 - tab) e `\n` (**12** - quebra de linha)

**O código de `\n` é 10, não 12.** Eu verifiquei:

```
'\t' = 9      ✔ correto no slide
'\n' = 10     ✘ o slide diz 12
'\v' = 11     (tabulação vertical)
'\f' = 12     ← este é o form feed, provavelmente a confusão
'\r' = 13     (carriage return)
'\0' = 0
```

O 12 é o `\f` (*form feed*, avanço de página). O slide trocou os dois. Não muda nada na prática (você escreve `'\n'`, não `10`), mas se cair numa questão de múltipla escolha sobre códigos ASCII, a resposta certa é **10**.

## 31.5 Caracteres de escape

Alguns caracteres não podem ser digitados diretamente, então usam barra invertida:

| Escape | Significado | Código |
|---|---|---|
| `'\n'` | quebra de linha | 10 |
| `'\t'` | tabulação | 9 |
| `'\0'` | **caractere nulo** | 0 |
| `'\\'` | barra invertida | 92 |
| `'\''` | aspa simples | 39 |
| `'\"'` | aspa dupla | 34 |

O `'\0'` é o mais importante de todos — ele é a estrela da seção 34.

## 31.6 ⚠️ `char` tem sinal e é pequeno

> normalmente tem 8 bits (está entre −128 e 127)

Duas consequências:

1. **Overflow rápido.** `char c = 200;` não cabe. Se precisar de 0–255, use `unsigned char`.
2. **Códigos negativos.** O slide diz "códigos negativos são usados em outras tabelas". Isso se refere a caracteres acentuados (á, ç, ã), que em UTF-8 ocupam **mais de um byte** e aparecem como valores negativos num `char`. É por isso que o slide 9 avisa: *"vamos trabalhar com strings sem acentos"*.

## ✅ O que eu preciso saber deste tópico

- Explicar que `char` **é um inteiro** e que ASCII é a tabela de correspondência.
- Saber que `printf("%c", 'a')` e `printf("%d", 'a')` mostram coisas diferentes do mesmo valor.
- **Saber que dígitos, maiúsculas e minúsculas são blocos consecutivos.**
- Escrever `c - 'A'`, `'A' + k`, `c - '0'`.
- Saber que `'\n'` é 10 (e que o slide erra dizendo 12).

---

# 32. Cifra de César (slides 2, 3, 6)

## 32.1 O algoritmo

> Dado um parâmetro inteiro k, cada letra é trocada pela k-ésima letra após ela. Ao chegar no final do alfabeto, **voltamos para o início**. Para desencriptar, basta fazer o mesmo processo para **26 − k**.

Com k = 6: A→G, B→H, …, T→Z, **U→A**, V→B…

O "voltar para o início" é o `%` (resto), e é a razão de a cifra funcionar.

## 32.2 O programa (slide 6)

```c
#include <stdio.h>

int main() {
  int k;
  char original, encriptado, pos_original, pos_encriptado;
  scanf("%d ", &k);
  scanf("%c", &original);
  while (original != '#') {
    pos_original = original - 'A';
    pos_encriptado = (pos_original + k) % 26;
    encriptado = 'A' + pos_encriptado;
    printf("%c", encriptado);
    scanf("%c", &original);
  }
  printf("\n");
  return 0;
}
```

## 32.3 As três linhas do coração — o padrão "converter, operar, converter de volta"

Este trio é o que você precisa entender, e ele reaparece em qualquer problema com letras:

```c
pos_original   = original - 'A';         /* letra  →  posição (0 a 25) */
pos_encriptado = (pos_original + k) % 26;  /* opera na posição */
encriptado     = 'A' + pos_encriptado;   /* posição  →  letra */
```

Trace com `original = 'C'` e `k = 6`:

| Passo | Cálculo | Valor |
|---|---|---|
| `'C' - 'A'` | 67 − 65 | `pos_original = 2` |
| `(2 + 6) % 26` | 8 % 26 | `pos_encriptado = 8` |
| `'A' + 8` | 65 + 8 = 73 | `encriptado = 'I'` |

E com uma letra perto do fim, `'Z'`, para ver o `%` agir:

| Passo | Cálculo | Valor |
|---|---|---|
| `'Z' - 'A'` | 90 − 65 | 25 |
| `(25 + 6) % 26` | 31 % 26 | **5** ← deu a volta |
| `'A' + 5` | 70 | `'F'` |

### Por que não somar direto `original + k`?

Porque `'Z' + 6` = 96, que é `` ` `` (crase), não `'F'`. **Somar direto sai do alfabeto.** A conversão para posição (0–25) é o que permite ao `% 26` dar a volta corretamente.

### Analogia: o relógio

Um relógio tem 12 horas. Que horas são 5 horas depois das 10? Não são "15 horas" no mostrador — são **3**. Você deu a volta: 15 % 12 = 3.

A cifra de César é um relógio de 26 posições. As letras são as horas; `k` é quanto você avança; o `% 26` é a volta ao passar do fim.

**Correspondência:** o mostrador de 12 é o alfabeto de 26; a hora atual é `original - 'A'`; avançar 5h é `+ k`; `% 12` é `% 26`; ler a hora no mostrador é `'A' + pos`.

Isso também explica a decriptação: para voltar `k` posições, você avança `26 − k`. Voltar 6h no relógio de 12 é o mesmo que avançar 6h. É **aritmética modular**.

## 32.4 O detalhe do `scanf("%d ", &k)` (slide 6)

> Há um **espaço após o `%d`** — consome os próximos caracteres brancos: espaço, `\n` e `\t`. Sem isso, o `scanf` leria um `\n`. **Cuidado, o C é chato na leitura de caracteres…**

Isto é uma das maiores fontes de sofrimento em C, e vale explicar bem.

**A regra:** `%d`, `%lf`, `%s` **pulam** espaços em branco automaticamente. **`%c` NÃO pula.** Ele lê o próximo byte, seja ele qual for.

Então imagine o usuário digitando `6` e apertando Enter. O buffer de entrada fica:

```
'6'  '\n'
```

O `scanf("%d", &k)` consome o `'6'` e para. **O `'\n'` continua lá.** Quando vem `scanf("%c", &original)`, ele lê… o `'\n'`. A primeira "letra" do texto vira uma quebra de linha.

O **espaço no formato** (`"%d "`) instrui o `scanf` a consumir todos os brancos que vierem depois. Problema resolvido.

> 💡 A forma mais comum de escrever isso na prática é `scanf(" %c", &c)` — espaço **antes** do `%c`. Faz a mesma coisa e é mais fácil de lembrar: *"antes de ler um caractere, jogue fora os brancos"*.

## 32.5 🔴 Dois bugs no programa — testei e comprovei

Compilei o programa exatamente como está no slide (passa em `-Wall -Werror`) e rodei:

### Bug 1: qualquer caractere que não seja maiúsculo vira lixo

```
Entrada:  6 OLA MUNDO#
Esperado: URG SATJU
Obtido:   URG@SATJU        ← o espaço virou '@'
```

**Por quê?** Quando `original` é um espaço `' '` (código 32):

```
pos_original = 32 - 65 = -33
(-33 + 6) % 26 = -27 % 26 = -1        ← em C, o resto é NEGATIVO
encriptado = 'A' + (-1) = 64 = '@'
```

Aqui aparece exatamente a pegadinha da **Parte 1, seção 3.3**: em C, `%` com número negativo dá resto negativo (ao contrário de Python). O programa assume implicitamente que toda entrada é `A`–`Z`.

### Bug 2: minúsculas produzem letras erradas

```
Entrada:  6 abc#
Esperado: ghi
Obtido:   MNO
```

`'a' - 'A'` = 32, e `(32 + 6) % 26` = 12, que dá `'M'`. O programa trata minúsculas como se fossem maiúsculas deslocadas 32 posições.

### A correção

```c
while (original != '#') {
  if (original >= 'A' && original <= 'Z')
    printf("%c", 'A' + (original - 'A' + k) % 26);
  else if (original >= 'a' && original <= 'z')
    printf("%c", 'a' + (original - 'a' + k) % 26);
  else
    printf("%c", original);        /* espaços e pontuação passam intactos */
  scanf("%c", &original);
}
```

E, se `k` puder ser negativo (para decriptar), a forma robusta do resto é:

```c
((original - 'A' + k) % 26 + 26) % 26
```

**A lição:** o programa dos slides é didático e correto *para o caso que ele assume* (só maiúsculas). Mas ele não valida a entrada — o mesmo padrão que já apontei nos exercícios de vetores e matrizes. Sempre pergunte: **"e se a entrada não for o que eu esperava?"**

## 32.6 Um detalhe de tipo

```c
char original, encriptado, pos_original, pos_encriptado;
```

`pos_original` e `pos_encriptado` são **posições no alfabeto** (0–25), não caracteres. Declará-las como `char` funciona (cabe em 8 bits), mas `int` expressaria melhor a intenção e evitaria surpresas com valores negativos. É estilo, não erro.

## ✅ O que eu preciso saber deste tópico

- **Escrever o trio "letra → posição → operar → letra".**
- Explicar por que `% 26` é necessário e por que somar direto não funciona.
- Explicar a analogia do relógio / aritmética modular.
- **Explicar por que `%c` precisa do espaço no formato e `%d` não.**
- Saber que o programa quebra com espaços e minúsculas, e por quê.

---

# 33. Operadores lógicos (slide 7)

## 33.1 A tabela

> Como no Python, os operadores de comparação: `<`, `<=`, `>`, `>=`, `==` e `!=` — **mas não temos o operador `is`**.
>
> Em C, **não temos o tipo `bool`**: o C considera o valor **0 como falso** e valores **diferentes de 0 como verdadeiro**.

| | Python | C |
|---|---|---|
| E | `and` | **`&&`** |
| Ou | `or` | **`\|\|`** |
| Não | `not` | **`!`** |

Isto reforça o que já vimos na Parte 1, seção 6.4. Dois pontos a acrescentar:

## 33.2 Precedência: `&&` vem antes de `||`

O slide 12 observa:

> Note o uso de `||` e `&&`: **`&&` precede `||`** — mas os parênteses deixam clara a ordem de precedência.

Ou seja, `a || b && c` é lido como `a || (b && c)`. Pense em `&&` como multiplicação e `||` como soma: a multiplicação vem primeiro.

**Conselho:** mesmo sabendo a regra, **use parênteses**. É o que o próprio código do slide 12 faz, e por isso ele é legível.

## 33.3 Avaliação em curto-circuito — essencial, e ausente dos slides

`&&` e `||` **param de avaliar assim que a resposta é conhecida**:

- Em `A && B`: se `A` é falso, o resultado já é falso. **`B` nem é avaliado.**
- Em `A || B`: se `A` é verdadeiro, o resultado já é verdadeiro. **`B` nem é avaliado.**

Isso não é curiosidade — é uma **técnica de proteção** que você vai usar sempre:

```c
if (i < n && v[i] > 0)        /* seguro */
if (v[i] > 0 && i < n)        /* PERIGOSO — acessa v[i] antes de checar */
```

Na primeira, se `i >= n`, o `v[i]` nunca é executado. Na segunda, você acessa fora dos limites (Parte 2, seção 17) e só depois verifica se podia.

**Regra: coloque a condição de segurança primeiro.**

## 33.4 Por que não existe `is`

Em Python, `is` compara **identidade de objetos** (se são o mesmo objeto na memória). C não tem objetos nesse sentido — mas tem algo análogo: comparar endereços. E é justamente o que acontece por acidente quando você compara strings com `==` (seção 39.2).

## ✅ O que eu preciso saber deste tópico

- Traduzir `and`/`or`/`not` para `&&`/`||`/`!`.
- Saber que 0 é falso e não-zero é verdadeiro.
- Saber que `&&` tem precedência sobre `||`.
- **Explicar curto-circuito e usá-lo para proteger acessos a vetor.**

---

# 34. 🔑 Strings: vetores de `char` terminados em `'\0'` (slide 10)

Este é o conceito central da unidade, e ele resolve elegantemente um problema que ficou pendente desde a Parte 2.

## 34.1 O problema que a string precisa resolver

Lembre da **Parte 2, seção 16.3**: em C, uma função que recebe um vetor **não sabe o tamanho dele**. Por isso toda função de vetor recebe `n` junto.

Mas texto é diferente: você declara `char nome[50]` e o nome pode ter 4 ou 40 letras. Passar o tamanho toda vez seria insuportável.

**A solução de C:** guardar o fim **dentro dos próprios dados**.

## 34.2 O que dizem os slides

> Strings em C são **vetores de `char` terminados com `'\0'`**. Por exemplo, podemos ter um vetor de char com 12 posições mas a string ter apenas 7 caracteres.

```
 e   x   e   m   p   l   o  \0   l   i   x   o
 0   1   2   3   4   5   6   7   8   9  10  11
```

> O tamanho da string é o número de caracteres **antes** do `'\0'`.

Eu rodei um programa que mostra os bytes um a um:

```
sizeof(s) = 12         ← o VETOR tem 12 posições
strlen(s) = 7          ← a STRING tem 7 caracteres
[0]='e' [1]='x' [2]='e' [3]='m' [4]='p' [5]='l' [6]='o' [7]=0 [8]=0 ...
```

Repare na distinção, que cai em prova: **`sizeof` é o tamanho do vetor; `strlen` é o tamanho da string.** São coisas diferentes. O vetor é o recipiente; a string é o conteúdo.

## 34.3 O que é o `'\0'`

É o caractere de código **zero**. Não é o dígito `'0'` (que é 48). Não é o espaço (32). É o valor 0.

**Ele é um marcador de fim.** Tudo depois dele é lixo irrelevante — a string acabou ali.

### Analogia: o ponto final e a folha de papel

Você tem uma **folha pautada com 12 linhas** (o vetor `char[12]`). Você escreve um bilhete de 7 palavras e coloca um **ponto final** (o `'\0'`).

Quem lê o bilhete não precisa saber quantas linhas a folha tem. Ele lê até o ponto final e para. As linhas restantes podem ter rabiscos de um bilhete anterior — irrelevante.

Agora, os dois desastres possíveis:

- **Esqueceu o ponto final:** o leitor continua lendo os rabiscos antigos, e depois **vira a página e continua lendo a folha seguinte**. Nunca sabe onde parar.
- **Escreveu mais palavras do que cabem na folha:** você continua escrevendo **na mesa, na parede** — destruindo o que estava lá.

**Correspondência:**

| Analogia | Conceito |
|---|---|
| Folha com 12 linhas | `char s[12]` — o vetor |
| O que está escrito | A string |
| Ponto final | O `'\0'` |
| Rabiscos após o ponto | Lixo — não faz parte da string |
| Ler até o ponto final | `for (i=0; s[i] != '\0'; i++)` |
| Esquecer o ponto final | String sem terminador → lê memória alheia |
| Escrever além da folha | **Buffer overflow** |

## 34.4 Eu provei os dois desastres

### Desastre 1: esquecer o `'\0'`

Preenchi `char s[12]` com "exemplo" mas **não** coloquei o `'\0'`:

```
sem o \0  ->  strlen = 10   conteudo = "exemploqM-}^?"
com o \0  ->  strlen = 7    conteudo = "exemplo"
```

Sem o terminador, `strlen` devolveu **10** e o `printf` imprimiu lixo binário. Ele continuou lendo a memória até encontrar um zero por acaso.

### Desastre 2: escrever além do vetor

Copiei uma string de 18 caracteres para um `char pequeno[5]`:

```
*** stack smashing detected ***: terminated
Aborted
```

O programa **morreu**. Neste caso o sistema detectou (há proteções modernas), mas nem sempre detecta — pode simplesmente corromper a variável vizinha, exatamente como demonstrei na Parte 2, seção 17.2.

**A regra de ouro:** um vetor de `char[N]` comporta uma string de **no máximo N−1 caracteres**, porque uma posição é do `'\0'`.

## 34.5 Declaração e inicialização

```c
char s[20] = "exemplo";     /* forma prática — o '\0' é colocado automaticamente */
char s[] = "exemplo";       /* tamanho deduzido: 8 (7 letras + '\0') */
char s[20];                 /* LIXO — nem sequer é uma string ainda */
```

⚠️ Note o `char s[] = "exemplo"` ter tamanho **8**, não 7. O `'\0'` ocupa lugar.

⚠️ E note a diferença entre aspas:

| | Significa | Tamanho |
|---|---|---|
| `'a'` | um `char` | 1 byte |
| `"a"` | uma **string** | 2 bytes: `'a'` e `'\0'` |

`'a'` e `"a"` são coisas diferentes. Confundir aspas simples com duplas é erro de compilação clássico.

## 34.6 A função `tamanho` (slide 10)

```c
int tamanho(char string[]) {
  int i;
  for (i = 0; string[i] != '\0'; i++) ;
  return i;
}
```

**Como funciona:** anda pelas posições até achar o `'\0'`. Quando o laço para, `i` é a quantidade de caracteres antes do terminador. Confirmei: para `"exemplo"` devolve **7**, igual ao `strlen`.

**Note que ela não recebe `n`.** Esta é a grande vantagem do `'\0'`: a string **carrega o próprio fim**. É a resposta de C para o problema levantado na Parte 2.

### O `for` de corpo vazio — o alerta do slide

> Note que esse `for` tem um **bloco vazio**! É raro usarmos isso (e algumas pessoas não gostam). Poderia ser trocado por um `while` (exercício). **Um `for` desses pode ser um bug no seu programa.**

Excelente alerta, e conecta com a **Parte 1, seção 5.3**: aquele `;` solto no fim do `for` é exatamente o bug do ponto e vírgula sobrando. Aqui é **intencional** — todo o trabalho está no `i++` do cabeçalho.

Mas como é indistinguível de um erro de digitação, prefira a versão explícita:

```c
int tamanho(char str[]) {
  int i = 0;
  while (str[i] != '\0')
    i++;
  return i;
}
```

Mesma coisa, sem ambiguidade. (E é o exercício que o slide sugere.)

**Complexidade: O(n)**, onde n é o comprimento da string. Você tem que percorrer para descobrir o tamanho — não há atalho. Isso é uma desvantagem em relação a Python, onde `len()` é O(1) porque o tamanho fica guardado.

> ⚠️ Cuidado clássico de desempenho: `for (int i = 0; i < strlen(s); i++)` recalcula `strlen` **a cada iteração**, transformando um laço O(n) em **O(n²)**. Guarde o tamanho antes.

## ✅ O que eu preciso saber deste tópico

- **Definir string em C: vetor de `char` terminado em `'\0'`.**
- Desenhar uma string na memória, mostrando o `'\0'` e o lixo depois.
- Explicar a diferença entre `sizeof(s)` e `strlen(s)`.
- Saber que `char[N]` comporta N−1 caracteres.
- Diferenciar `'a'` de `"a"`.
- Escrever a função `tamanho` e saber que ela é O(n).

---

# 35. Busca de padrão com coringa (slides 8, 9, 11, 12)

## 35.1 O problema (slide 8)

> Queremos buscar por um padrão em um texto. Um símbolo `*` representa um **caractere coringa**.
> Procurando por `*os` no texto, encontraremos `nos` e `dos`.

O `*` casa com **qualquer** caractere. Então `*os` significa "qualquer letra, seguida de `o`, seguida de `s`".

## 35.2 A estratégia (slide 9)

> **Para cada posição do texto, verifique se o padrão começa ali.** Existem algoritmos melhores do que esse.

Essa é a **busca por força bruta**. Simples de entender, e o slide honestamente admite que não é o melhor.

**Complexidade:** para cada uma das `n` posições do texto, comparamos até `m` caracteres do padrão ⇒ **O(n × m)** no pior caso.

> Os "algoritmos melhores" citados são KMP, Boyer-Moore, Rabin-Karp, que chegam a O(n + m). Assunto de outra disciplina — mas saiba que existem.

E o slide aplica de novo a **decomposição em tarefas** (o método do slide 12 da Unidade 3):

```c
int  ocorre(char texto[], int pos, char padrao[]);
void imprime_trecho(char texto[], int ini, int tam);
int  tamanho(char string[]);
```

## 35.3 `imprime_trecho` (slide 11)

```c
void imprime_trecho(char texto[], int ini, int tam) {
  printf("%d: ", ini);
  for (int j = 0; j < tam; j++)
    printf("%c", texto[ini + j]);
  printf("\n");
}
```

Imprime a posição, depois `tam` caracteres a partir de `ini`. Note o índice `texto[ini + j]`: `ini` é onde começa, `j` anda de 0 a tam−1.

### O bug que o próprio slide admite

> **Um bug:** pode ser que `j` ultrapasse a última letra da string. Poderíamos parar antes se encontrarmos o `'\0'`.

Se o padrão casa perto do fim do texto, o laço pode imprimir **além do `'\0'`** — lendo lixo. A correção é adicionar a condição de parada:

```c
for (int j = 0; j < tam && texto[ini + j] != '\0'; j++)
```

E note: isto é **exatamente** o curto-circuito da seção 33.3 — a condição de segurança precisa vir de forma que `texto[ini+j]` só seja lido se ainda estiver dentro. Aqui as duas condições são independentes, então a ordem não importa tanto, mas o padrão é o mesmo.

## 35.4 `ocorre` (slide 12)

```c
int ocorre(char texto[], int pos, char padrao[]) {
  for (int j = 0; padrao[j] != '\0'; j++)
    if (texto[pos + j] == '\0' ||
        (texto[pos + j] != padrao[j] && padrao[j] != '*'))
      return 0;
  return 1;
}
```

> Função devolve **0 se não ocorre**, diferente de 0 caso contrário.

**Lendo a condição por partes:**

| Parte | Significa | Ação |
|---|---|---|
| `texto[pos+j] == '\0'` | o texto acabou antes do padrão | não casa → `return 0` |
| `texto[pos+j] != padrao[j]` | os caracteres diferem | candidato a falha… |
| `&& padrao[j] != '*'` | …**mas só falha se não for coringa** | |

Ou seja: *"falhe se o texto acabou, OU se os caracteres diferem E o padrão não é coringa."*

O `padrao[j] != '*'` é o que implementa o coringa: quando o padrão tem `*`, a diferença é perdoada.

Se o laço chega ao fim (`padrao[j] == '\0'`), todos os caracteres casaram ⇒ `return 1`.

**Este é o mesmo padrão de "saída antecipada" do exercício de primos** (Parte 1, seção 14.1): retorna `0` assim que descobre a falha; retorna `1` só se sobreviveu ao laço inteiro.

Note também o uso do `'\0'` para saber onde o padrão e o texto acabam — **nenhum tamanho é passado**. É a string se auto-delimitando.

## 35.5 A `main` (slides 13–15)

```c
int main() {
  char texto[MAX], padrao[MAX];
  scanf("%s ", padrao);
  fgets(texto, MAX, stdin);
  printf("Procurando por %s no texto: %s\n", padrao, texto);
  for (int i = 0; texto[i] != '\0'; i++)
    if (ocorre(texto, i, padrao))
      imprime_trecho(texto, i, tamanho(padrao));
  return 0;
}
```

O laço principal é a "força bruta": tenta **cada posição** `i` do texto.

## 35.6 Lendo strings: `%s` e `fgets`

### `%s` (slide 13)

> Imprimimos strings usando `%s`. Lemos strings **sem espaço** usando `%s`: isto é, lê até o primeiro espaço, `'\n'` ou `'\t'`. **Não colocamos o `&` antes do nome da variável.**

**Por que não leva `&`?** Aqui a Parte 2, seção 19 responde de imediato: o nome do vetor **já é** o endereço do primeiro elemento. `padrao` já é um endereço. Escrever `&padrao` seria "o endereço do endereço" — coisa diferente.

Compare a família toda:

```c
scanf("%d", &n);        /* int:    precisa do & */
scanf("%lf", &x);       /* double: precisa do & */
scanf("%c", &c);        /* char:   precisa do & */
scanf("%s", nome);      /* string: NÃO leva &, já é endereço */
```

### `fgets` (slide 14)

> Lemos strings **com espaços** usando `fgets`:
> - 1º parâmetro: nome da variável
> - 2º parâmetro: **tamanho máximo da string**, contando o `'\0'`
> - 3º parâmetro: de qual arquivo ler — `stdin` é a entrada padrão
>
> O `fgets` lê apenas até o primeiro `'\n'` — **e pode incluir o `'\n'` na string**.

Aquele último ponto é uma armadilha frequente. Se o usuário digita `oi` e Enter, a string fica `"oi\n"` — com **três** caracteres. Se você comparar com `"oi"`, não vai casar.

A remoção idiomática:

```c
fgets(texto, MAX, stdin);
int len = strlen(texto);
if (len > 0 && texto[len-1] == '\n')
    texto[len-1] = '\0';           /* substitui o \n pelo terminador */
```

### `%s` vs `fgets` — quando usar cada um

| | `scanf("%s", s)` | `fgets(s, MAX, stdin)` |
|---|---|---|
| Lê espaços? | **não** — para no primeiro branco | **sim** — até o `\n` |
| Limita tamanho? | **não** ⚠️ | **sim** (o `MAX`) |
| Inclui o `\n`? | não | **sim** |
| Uso típico | uma palavra | uma linha inteira |

**`fgets` é mais seguro**, porque `%s` sem limite de largura é a receita clássica de buffer overflow — se o usuário digitar 500 caracteres num `char[100]`, o `scanf` escreve todos.

> 💡 Existe forma segura de `%s`: `scanf("%99s", s)` para um `char s[100]`.

## 35.7 O espaço no `"%s "` (slide 15)

> **Por que colocamos o espaço após o `%s`?** Para consumir os espaços em branco depois da string… Caso contrário, o `fgets` poderia ler apenas o `\n` após o padrão.

Mesmo problema da seção 32.4, agora atingindo o `fgets`. **Eu testei os dois casos:**

Entrada: `*os` + Enter + `Muito alem, nos confins` + Enter

```
COM o espaço  ("%s "):   texto = [Muito alem, nos confins\n]   ✔
SEM o espaço  ("%s"):    texto = [\n]                          ✘
```

Sem o espaço, o `fgets` encontra o `'\n'` que o `scanf` deixou para trás, e considera que a linha acabou imediatamente. **Lê uma string vazia.** O programa não acha nada e você não faz ideia do porquê.

**Este é, na minha experiência, o bug nº 1 de quem está aprendendo C.** A regra para memorizar: **misturar `scanf` com `fgets` exige limpar o buffer**.

## 35.8 🔴 Um problema não mencionado: `MAX` e a validação

O código usa `char texto[MAX]` mas **`MAX` não é definido em nenhum slide desta unidade**. Presume-se um `#define MAX 100` (Unidade 3, seção 24). Se você for reproduzir o programa, não esqueça dele.

E `scanf("%s ", padrao)` **não limita o tamanho** — se o padrão for maior que `MAX`, há overflow. O correto seria `scanf("%99s ", padrao)`.

## ✅ O que eu preciso saber deste tópico

- Explicar a busca por força bruta e sua complexidade O(n×m).
- Ler e explicar a condição composta de `ocorre`, incluindo o coringa.
- **Explicar por que `%s` não leva `&`.**
- Diferenciar `%s` de `fgets` e saber quando usar cada um.
- **Explicar o problema do `\n` no buffer e as duas soluções** (espaço no formato, ou `" %c"`).
- Saber que `fgets` pode incluir o `'\n'` e como removê-lo.

---

# 36. A biblioteca `string.h` (slide 16)

## 36.1 O que dizem os slides

> A biblioteca `string.h` tem várias funções úteis:
> - **`strlen`** devolve o tamanho da string
> - **`strcmp`** compara duas strings, já que **não podemos usar `<`, `<=`, `>`, `>=`, `==` e `!=`**
> - **`strcpy`** copia uma string
> - **`strcat`** concatena duas strings
>
> Veja o manual para a documentação (`man strlen`). **Não confunda com a biblioteca `strings.h`**.

## 36.2 A tabela prática

| Função | Assinatura | O que faz |
|---|---|---|
| `strlen(s)` | `size_t strlen(const char *s)` | comprimento (sem contar o `'\0'`) |
| `strcmp(a, b)` | `int strcmp(...)` | 0 se iguais; <0 se a<b; >0 se a>b |
| `strcpy(dest, orig)` | `char *strcpy(...)` | copia `orig` para `dest` |
| `strcat(dest, orig)` | `char *strcat(...)` | anexa `orig` ao fim de `dest` |

⚠️ **Em `strcpy` e `strcat`, o DESTINO vem primeiro.** Pense em `dest = orig`, como uma atribuição.

## 36.3 🔑 Por que não se compara string com `==`

Esta é a frase mais importante do slide, e merece a explicação que ele não dá.

Eu rodei:

```c
char a[10] = "oi", b[10] = "oi";
a == b        →  0    (falso!)
strcmp(a, b)  →  0    (iguais)
```

**Duas strings com o mesmo conteúdo, e `==` diz que são diferentes.**

**Por quê?** Porque `a` e `b` são **endereços** (Parte 2, seção 19). `a == b` pergunta *"estas duas strings estão no mesmo lugar da memória?"* — e não estão, são dois vetores distintos. A pergunta que você queria fazer era *"elas têm o mesmo conteúdo?"*, que é `strcmp`.

O compilador ainda avisou:

```
warning: comparison between two arrays [-Warray-compare]
```

### Analogia: duas cartas idênticas

Você e eu escrevemos cartas com exatamente o mesmo texto. Elas estão em **envelopes diferentes, em endereços diferentes**.

- `a == b` pergunta: *"é o mesmo envelope?"* → **não**.
- `strcmp(a,b) == 0` pergunta: *"o texto é o mesmo?"* → **sim**.

**Correspondência:** o envelope é o endereço na memória; o texto é o conteúdo da string; `==` compara envelopes; `strcmp` compara textos, caractere por caractere.

E isto é exatamente o que o `is` do Python faria (seção 33.4) — comparar identidade em vez de conteúdo. C não tem `is`, mas tem o mesmo problema disfarçado de `==`.

**Regra absoluta: para comparar strings, use `strcmp`. Sempre.**

```c
if (strcmp(a, b) == 0)      /* iguais */
if (strcmp(a, b) < 0)       /* a vem antes de b (alfabeticamente) */
```

## 36.4 `string.h` vs `strings.h`

O aviso do slide é real. São bibliotecas **diferentes**:

- **`string.h`** — a padrão, com `strlen`, `strcmp`, `strcpy`, `strcat`. **É esta que você quer.**
- **`strings.h`** — extensão POSIX (não padrão), com `strcasecmp`, `bzero`. Pode nem existir em Windows.

Uma letra de diferença. Se algo não compilar, confira o `s`.

## 36.5 ⚠️ O perigo de `strcpy` e `strcat`

Nenhuma das duas verifica se cabe no destino:

```c
char pequeno[5];
strcpy(pequeno, "texto muito grande");   /* buffer overflow */
```

É o desastre 2 da seção 34.4, que fez meu teste morrer com *stack smashing detected*. Versões seguras (`strncpy`, `snprintf`) existem, mas provavelmente não serão cobradas nesta disciplina. Saiba que o risco existe.

## ✅ O que eu preciso saber deste tópico

- Citar as quatro funções e o que cada uma faz.
- **Explicar por que `a == b` não compara conteúdo de strings.**
- Usar `strcmp` corretamente, incluindo o sinal do retorno.
- Saber que em `strcpy`/`strcat` o destino vem primeiro.
- Saber que `#include <string.h>` (sem `s` no final).

---

# 37. Os tipos do C — tabela de referência (slides 17–19)

## 37.1 Os tipos mais comuns (slide 17)

| Dado | Tipo | Formato | Constante |
|---|---|---|---|
| inteiros | `int` | `%d` | `10` |
| ponto flutuante | `float` | `%f`, `%g`, `%e` | `10.0f`, `2e-3f` |
| ponto flutuante duplo | `double` | `%lf`, `%lg`, `%le` | `10.0`, `2e-3` |
| caractere | `char` | `%c` | `'c'` |
| **string** | **`char []`** | `%s` | `"string"` |

Note o `f` no fim de `10.0f` e `2e-3f`: é assim que se escreve uma constante `float`. Sem o `f`, a constante é `double`.

E note que **string não é um tipo** — é `char[]`, um vetor. C não tem tipo texto nativo.

## 37.2 Variações de inteiro (slide 18)

> - `short` ou `short int` — `%hi` — pelo menos 16 bits
> - `int` — `%d` ou `%i` — pelo menos 16 bits
> - `long` ou `long int` — `%li` — pelo menos 32 bits
> - `long long` ou `long long int` — `%lli` — pelo menos 64 bits
>
> A quantidade de bits **pode variar de acordo com a plataforma**: `int` em geral tem 32 bits, mas a especificação diz pelo menos 16.
>
> A vantagem é poder escolher entre **economizar memória** ou **representar mais números**.

Isto confirma o que eu disse na Parte 1, seção 3.2: o padrão só garante mínimos.

**Na prática, num PC de 64 bits:**

| Tipo | Bits típicos | Faixa aproximada |
|---|---|---|
| `short` | 16 | −32 768 a 32 767 |
| `int` | 32 | ±2,1 bilhões |
| `long` | 64 (Linux) / 32 (Windows) | — |
| `long long` | 64 | ±9,2 × 10¹⁸ |

⚠️ `long` é o mais traiçoeiro: **64 bits no Linux, 32 no Windows**. Se precisa garantir 64 bits, use `long long`.

## 37.3 `unsigned` (slide 19)

> Versões sem sinal: `unsigned char` (`%c`), `unsigned short` (`%hu`), `unsigned` (`%u`), `unsigned long` (`%lu`), `unsigned long long` (`%llu`).
>
> **A vantagem:** se você for trabalhar apenas com números não-negativos, consegue representar **mais números**.
>
> Em geral, trabalhamos apenas com os tipos básicos: **`int`, `double` e `char`**.

`unsigned` sacrifica os negativos para dobrar o alcance positivo. Um `int` vai até ~2,1 bilhões; um `unsigned int` vai até ~4,2 bilhões.

### ⚠️ A armadilha do `unsigned`: não existe negativo

```c
unsigned int u = 0;
u = u - 1;               /* NÃO dá −1 — dá 4294967295! */
```

Sem sinal, subtrair de zero "dá a volta" para o maior valor possível. Isso destrói laços decrescentes:

```c
for (unsigned int i = n-1; i >= 0; i--)    /* LAÇO INFINITO */
```

`i >= 0` é **sempre verdadeiro** para um `unsigned`. Quando `i` chega a 0 e decrementa, vira 4 bilhões.

O conselho final do slide é o certo: **fique com `int`, `double` e `char`.** As variações existem para casos específicos.

## ✅ O que eu preciso saber deste tópico

- Citar os tipos básicos e seus especificadores.
- Saber que o padrão garante **mínimos**, não tamanhos exatos.
- Saber o que `unsigned` faz e qual a vantagem.
- **Saber que `for (unsigned i = n-1; i >= 0; i--)` é laço infinito.**
- Saber que string é `char[]`, não um tipo.

---

# 38. Exercícios resolvidos (slides 20–25)

## 38.1 Exercício 1: copiar (slides 20–21)

> Faça uma função `void copia(char str1[], char str2[])` que copia o conteúdo de `str1` para `str2`.

```c
void copia(char str1[], char str2[]) {
    int i;
    for(i = 0; str1[i] != '\0'; i++)
        str2[i] = str1[i];
    str2[i] = '\0';
}
```

**Linha a linha:**

| Linha | O que faz |
|---|---|
| `for(i = 0; str1[i] != '\0'; i++)` | percorre a origem até o terminador |
| `str2[i] = str1[i];` | copia caractere por caractere |
| `str2[i] = '\0';` | **coloca o terminador no destino** |

### A linha 5 é a mais importante do exercício

Quando o laço termina, `i` aponta para onde estava o `'\0'` da origem. Mas **o `'\0'` não foi copiado** — o laço parou antes dele.

Sem essa linha, o destino ficaria **sem terminador**, e você teria o desastre 1 da seção 34.4: `strlen` errado, `printf` imprimindo lixo.

Testei a função: `copia("exemplo", d)` produz `"exemplo"` corretamente. Com a linha 5 removida, produziria lixo.

**Lição geral: toda função que constrói uma string é responsável por terminá-la.**

### 🔴 Duas críticas

**1. A ordem dos parâmetros contraria a convenção.**

`copia(str1, str2)` copia **str1 → str2**, ou seja, origem primeiro, destino depois. Mas a `strcpy` da biblioteca padrão é `strcpy(destino, origem)` — **destino primeiro**.

Isso é um convite ao erro: quem se acostumar com esta função vai usar `strcpy` invertida, e vice-versa. Nomes melhores deixariam isso óbvio:

```c
void copia(char origem[], char destino[])
```

**2. Não há proteção contra overflow.** Se `str2` for menor que `str1`, a função escreve além do vetor — foi exatamente assim que provoquei o *stack smashing* na seção 34.4. A versão segura receberia o tamanho do destino:

```c
void copia(char origem[], char destino[], int tam_destino)
```

## 38.2 Exercício 2: reverter (slides 22–23)

> Faça `void reverte(char str[])` que reverte o conteúdo. `"MC202"` → `"202CM"`.

```c
void reverte(char str[]) {
    int tam = tamanho(str);
    for (int i = 0; i < tam / 2; i++) {
        char temp = str[i];
        str[i] = str[tam - i - 1];
        str[tam - i - 1] = temp;
    }
}
```

### A ideia: trocar as pontas, andando para o meio

```
M  C  2  0  2          i=0: troca str[0] com str[4]
↑___________↑
   C  2  0             i=1: troca str[1] com str[3]
   ↑_____↑
      2                i=2: PARA — 2 não é < 5/2 = 2
```

**Três detalhes que valem ouro:**

**1. `tam / 2` — divisão inteira, e ela está certa.** Para tam=5, `5/2` = 2 (Parte 1, seção 3.3). Duas trocas, e o elemento do meio fica no lugar — que é o correto, o do meio não precisa se mover. Para tam=4, `4/2` = 2, duas trocas, todos se movem. **A divisão inteira acerta os dois casos automaticamente.**

**2. `str[tam - i - 1]` é o espelho de `str[i]`.** Por que o `-1`? Porque o último índice válido é `tam-1`, não `tam` (Parte 2, seção 17.3 — off-by-one!). Para i=0, `tam-0-1` = último. ✔

**3. A troca precisa da variável `temp`.** Este é o erro clássico:

```c
str[i] = str[j];      /* ERRADO: str[i] foi DESTRUÍDO */
str[j] = str[i];      /* e agora copia o valor errado de volta */
```

Você não pode trocar dois valores sem guardar um deles. É como trocar o conteúdo de dois copos cheios: precisa de um terceiro copo.

### A segunda versão (slide 23)

```c
// Outra versão, só para mostrar um for mais complicado
void reverte_v2(char str[]) {
    int tam = tamanho(str);
    for (int i = 0, j = tam - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}
```

Novidade sintática: **o `for` aceita várias variáveis e várias atualizações**, separadas por vírgula.

- `int i = 0, j = tam - 1` — dois contadores
- `i < j` — condição: enquanto não se cruzarem
- `i++, j--` — um avança, o outro recua

É mais expressivo: em vez de calcular `tam-i-1` toda vez, você tem `j` andando sozinho. E a condição `i < j` diz literalmente *"enquanto os ponteiros não se encontrarem"*.

Esta técnica dos **dois índices caminhando um em direção ao outro** é um padrão clássico. Você vai reencontrá-la em algoritmos de ordenação (particionamento do Quicksort) e em verificação de palíndromos.

**Complexidade:** O(n) — faz n/2 trocas.

## 38.3 Exercício 3: comparar (slides 24–25)

> Faça `int compara(char str1[], char str2[])` que devolve 0 se iguais, um número **menor que zero** se `str1` é lexicograficamente menor, e **maior que zero** caso contrário.

```c
int compara(char str1[], char str2[]) {
    int i;
    for(i = 0; str1[i] == str2[i]; i++)
        if (str1[i] == '\0')
            return 0;              // strings são iguais
    return str1[i] - str2[i];      // comparação lexicográfica
}
```

Esta é uma reimplementação da `strcmp`, e é a mais engenhosa das três.

### Como funciona

**O laço avança enquanto os caracteres forem IGUAIS.** Ele só para quando encontra uma diferença.

Duas maneiras de sair:

1. **Achou o `'\0'` com tudo igual** ⇒ as strings terminaram juntas, são idênticas ⇒ `return 0`.
2. **O `for` parou** ⇒ `str1[i] != str2[i]` ⇒ a diferença está na posição `i`.

E aí vem o truque: **`return str1[i] - str2[i]`**. A subtração dos códigos ASCII dá automaticamente o sinal certo:

- Se `str1[i]` vem antes no alfabeto, o código é menor ⇒ diferença **negativa** ✔
- Se vem depois, diferença **positiva** ✔

Eu testei:

| Chamada | Retorno |
|---|---|
| `compara("abc","abc")` | `0` |
| `compara("abc","abd")` | `-1` (`'c'-'d'`) |
| `compara("abd","abc")` | `1` |
| `compara("ab","abc")` | `-99` (`'\0'` − `'c'` = 0−99) |

Note o último caso: quando uma string é **prefixo** da outra, a mais curta tem `'\0'` (=0) onde a outra tem uma letra. Como qualquer letra tem código > 0, a subtração dá negativo — **a mais curta vem antes**. Que é exatamente a ordem de dicionário: "ab" vem antes de "abc". **O `'\0'` resolve o caso do prefixo de graça.**

### Por que o laço não precisa checar o fim de `str2`

Sutileza elegante: se `str1` acabou (`'\0'`) e `str2` não, então os caracteres são diferentes e o laço para sozinho. Não é preciso testar as duas strings. O `if` interno só existe para o caso em que **ambas** acabaram ao mesmo tempo.

### Ordem "lexicográfica" é ordem ASCII, não alfabética

⚠️ Cuidado: `compara("Zebra", "abelha")` dá **negativo**, porque `'Z'`=90 < `'a'`=97. **Todas as maiúsculas vêm antes de todas as minúsculas.** Não é a ordem de dicionário de português. Para isso seria necessário normalizar antes.

## ✅ O que eu preciso saber deste tópico

- **Escrever `copia` e saber por que a linha do `'\0'` é indispensável.**
- Escrever `reverte` e justificar `tam/2`, `tam-i-1` e a variável `temp`.
- Entender o `for` com duas variáveis e a técnica dos dois índices.
- **Explicar o `return str1[i] - str2[i]` e por que ele dá o sinal certo.**
- Explicar como o `'\0'` resolve o caso de prefixo.
- Saber que a ordem é ASCII, não alfabética.

---

# 🎓 FECHAMENTO DO BLOCO "LINGUAGEM C" (Unidades 2, 3 e 4)

Com esta unidade, você completou o arco da **linguagem C**. A Unidade 5, que você já enviou, começa um arco novo (`struct`, `typedef` e Tipos Abstratos de Dados) — o começo de estrutura de dados propriamente dita.

> **Nota honesta sobre a tabela comparativa de estruturas que você pediu:** ela ainda não pode ser escrita. Listas encadeadas, pilhas, filas e árvores **não apareceram em nenhum slide até aqui**. A única estrutura vista foi o vetor (e a matriz). Vou montar essa tabela quando o material chegar lá — escrevê-la agora seria inventar conteúdo que sua disciplina ainda não deu.

## Mapa mental do bloco inteiro

```
                         LINGUAGEM C
                              │
        ┌─────────────────────┼──────────────────────┐
        │                     │                      │
   TIPAGEM ESTÁTICA     MEMÓRIA EXPLÍCITA      COMPILAÇÃO
        │                     │                      │
 tipo definido no código   variável = espaço      gcc + flags
        │                   com endereço          -Wall -Werror
        │                     │                    erro antes de rodar
   ┌────┴────┐                │
   │         │        ┌───────┴────────┐
 int/char  float/double │              │
   │         │      não inicializada = LIXO
   │         │              │
   │    ponto flutuante     │
   │    é APROXIMADO   endereço (&) ──────────────┐
   │    nunca ==            │                     │
   │                        │                     │
   │                  scanf precisa de &      VETOR = bloco contíguo
   │                  printf não precisa          │
   │                                     ┌────────┼─────────┐
 char É INT                              │        │         │
   │                              v[i] = O(1)  tamanho    nome do vetor
 tabela ASCII                     base+i×tam    FIXO      É o endereço
   │                                         (sem len)         │
 blocos consecutivos                            │      ┌───────┴────────┐
 'A'+k, c-'0'                                   │  função MODIFICA  precisa
   │                                            │   o original      passar n
 STRING = char[] + '\0'  ←──────────────────────┘         │
   │                    (o '\0' resolve o "sem len")       │
   ├─ strlen O(n)                                    MATRIZ M[i][j]
   ├─ == compara ENDEREÇO → use strcmp              row-major
   ├─ char[N] cabe N−1                            base+(i×COLS+j)
   └─ sem '\0' → lê lixo                                  │
                                                  colunas OBRIGATÓRIO
                                                  linhas dispensável

  SEM CHECAGEM DE LIMITES  →  segfault OU corrupção silenciosa
  (vale para vetor, matriz e string — é o perigo nº1 de C)
```

## Complexidades vistas até agora

| Operação | Custo |
|---|---|
| `v[i]`, `M[i][j]` | **O(1)** |
| Percorrer vetor / `strlen` / `strcmp` | **O(n)** |
| Reverter string | **O(n)** |
| Percorrer matriz n×n | **O(n²)** |
| Busca de padrão (força bruta) | **O(n×m)** |
| Multiplicar matrizes | **O(n³)** |

## As 15 pegadinhas mais prováveis em prova

1. `=` em vez de `==` no `if`.
2. Esquecer o `&` no `scanf` — **e colocá-lo em string, onde não vai**.
3. Variável não inicializada → lixo.
4. `;` sobrando depois de `for`/`if`/`while`.
5. Indentação mentirosa: sem `{ }`, o `if` controla só o próximo comando.
6. `6 / 4` dá `1`; `(a+b)/2` não dá média real.
7. `(double)(x/y)` em vez de `(double)x/y`.
8. `(int) 3.99` é **3**, trunca.
9. Comparar `double` com `==`.
10. `a++` × `++a` em expressões.
11. Off-by-one: `i <= n` acessa `v[n]`.
12. `sizeof(v)` dentro de função não dá o tamanho do vetor.
13. `#define MAX 100;` com ponto e vírgula.
14. Comparar strings com `==` em vez de `strcmp`.
15. `%c` não pula brancos → o `\n` residual estraga a leitura seguinte.

---

# 📝 20 QUESTÕES DE REVISÃO

*(dificuldade crescente — gabarito comentado logo após)*

**1.** Qual a diferença entre uma linguagem compilada e uma interpretada? Cite uma consequência prática.

**2.** O que acontece se você declarar `int x;` e imprimir `x` sem atribuir valor?

**3.** Quantas vezes o corpo executa? `for (int i = 0; i < 5; i++)`. E quanto vale `i` ao terminar?

**4.** Por que `scanf("%d", &n)` leva `&` mas `printf("%d", n)` não?

**5.** Em C, quanto vale `7 / 2`? E `7 % 2`? E `7.0 / 2`?

**6.** Qual a diferença entre `'a'` e `"a"`?

**7.** O que é impresso?
```c
int a = 5, x;
x = a++;
printf("%d %d", x, a);
```

**8.** Um vetor `int v[10]`. Quais índices são válidos? O que acontece ao acessar `v[10]`?

**9.** Por que toda função em C que recebe um vetor recebe também o tamanho `n`?

**10.** Qual o valor de `(int) -3.87`?

**11.** Escreva uma função `int conta_pares(int v[], int n)` que conta os números pares de um vetor.

**12.** Explique por que este código imprime `7.000000` e corrija-o:
```c
int a = 7, b = 8;
double m = (a + b) / 2;
printf("%lf", m);
```

**13.** Considere:
```c
void f(int x) { x = 99; }
void g(int v[]) { v[0] = 99; }
int main() {
  int a = 1, w[3] = {1,2,3};
  f(a); g(w);
  printf("%d %d", a, w[0]);
}
```
O que é impresso e por quê?

**14.** Numa função que recebe matriz, por que `void f(double M[][MAX], int n)` compila mas `void f(double M[][], int n)` não?

**15.** O que este código imprime, e por quê?
```c
char a[10] = "oi", b[10] = "oi";
if (a == b) printf("iguais");
else printf("diferentes");
```

**16.** Uma string está em `char s[20]`. Qual o maior número de caracteres que ela pode ter? Por quê?

**17.** Explique o que faz `'A' + (c - 'A' + 3) % 26` e por que o `% 26` é necessário.

**18.** Este trecho tem um bug. Encontre-o e explique o que acontece na execução.
```c
int i;
char s[6] = "abcde";
for (i = 0; i < 6; i++)
  if (s[i] == 'c') break;
printf("%d\n", i);
```
*(Considere: e se a letra procurada não existir?)*

**19.** Analise:
```c
scanf("%d", &n);
scanf("%c", &c);
```
O usuário digita `5`, Enter, `A`, Enter. Qual o valor de `c`? Como corrigir?

**20.** A função `compara` do slide 25 devolve `str1[i] - str2[i]`. Explique por que isso funciona para `compara("ab", "abc")` e qual valor é devolvido.

---

# ✅ GABARITO COMENTADO

**1.** O interpretador traduz e executa linha a linha, a cada execução; o compilador traduz o programa inteiro uma vez, gerando um executável independente. **Consequência prática:** em C, um erro de sintaxe na linha 300 impede o programa inteiro de rodar, mesmo que aquela linha nunca fosse executada — o compilador vê tudo antes de gerar o executável. Em Python, o erro só apareceria se a execução chegasse lá.
*(Parte 1, seção 1)*

**2.** Imprime **lixo** — o valor que estava naquele espaço de memória. Não é aleatório nem necessariamente zero: é o resto de dados anteriores. O programa **não dá erro**, o que torna o bug difícil de achar. Analogia do quarto de hotel sem arrumadeira.
*(Parte 1, seção 7.2)*

**3.** Executa **5 vezes**, com `i` valendo 0, 1, 2, 3, 4. Ao terminar, **`i` vale 5** — foi incrementado uma última vez antes do teste que falhou. Errar isso é a causa nº 1 de off-by-one.
*(Parte 1, seção 8.3)*

**4.** Porque `scanf` precisa **escrever** na variável, e para isso precisa saber **onde ela mora** — o `&` fornece o endereço. `printf` só precisa **ler** o valor, e o valor lhe é entregue por cópia. **Regra: quem escreve precisa de endereço; quem lê, não.**
*(Parte 1, seção 11.2)*

**5.** `7 / 2` = **3** (divisão inteira, ambos são `int`). `7 % 2` = **1**. `7.0 / 2` = **3.5** (um operando é real ⇒ divisão real).
*(Parte 3, seção 26)*

**6.** `'a'` é um **`char`**, 1 byte, valor 97. `"a"` é uma **string**, ou seja, um vetor de 2 `char`: `'a'` e `'\0'`. São tipos diferentes; confundir as aspas é erro de compilação.
*(Parte 4, seção 34.5)*

**7.** Imprime **`5 6`**. `a++` é pós-incremento: devolve o valor **antigo** (5) para `x` e depois incrementa `a` para 6. Se fosse `++a`, imprimiria `6 6`.
*(Parte 1, seção 3.3)*

**8.** Válidos: **0 a 9**. Acessar `v[10]` pode causar **segmentation fault**, ou — pior — **não causar erro nenhum** e ler/escrever silenciosamente em outra variável. C não faz checagem de limites. O caso silencioso é mais perigoso porque o programa continua rodando com dados corrompidos.
*(Parte 2, seção 17)*

**9.** Porque, ao ser passado para a função, o vetor **decai para o endereço do primeiro elemento** — a informação de tamanho é perdida. `sizeof` dentro da função devolve o tamanho de um endereço (8 bytes), não do vetor. E C não tem equivalente ao `len()` de Python. O endereço diz onde começa, mas não onde termina.
*(Parte 2, seções 16.3 e 19)*

**10.** **−3**. A conversão para `int` **trunca** em direção ao zero, não arredonda. Para arredondar, use `(int) round(-3.87)`, que daria −4.
*(Parte 3, seção 25.3)*

**11.**
```c
int conta_pares(int v[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++)
        if (v[i] % 2 == 0)
            total++;
    return total;
}
```
⚠️ Note que usei `% 2 == 0` (par), não `% 2 == 1` (ímpar) — este último falharia para negativos, pois em C `-7 % 2` é `-1`.
*(Parte 1, seção 3.3)*

**12.** `(a + b)` é `15`, e `15 / 2` é **divisão inteira** porque ambos são `int` ⇒ resultado `7`. Só então o 7 é convertido para `7.0`. **A atribuição a um `double` não conserta nada** — o estrago aconteceu antes. Correções: `(a + b) / 2.0` ou `(double)(a + b) / 2`.
*(Parte 3, seção 26.3)*

**13.** Imprime **`1 99`**.
- `f(a)`: passagem por valor — a função recebe uma **cópia** de `a`. Modificar a cópia não afeta o original.
- `g(w)`: também é passagem por valor, **mas o valor copiado é o endereço** do vetor. Com o endereço, a função escreve direto na memória original.

*Tudo em C é passado por valor — no caso de vetores, o valor é um endereço.* Analogia: fotocópia do documento × cópia da chave da casa.
*(Parte 2, seção 19)*

**14.** Porque, para calcular o endereço de `M[i][j]`, o compilador usa a fórmula **`base + (i × NUM_COLUNAS + j) × tamanho`**. Ele recebe a base (o endereço), e você fornece `i` e `j` — mas o **número de colunas** não vem junto com o endereço, então precisa estar declarado. O número de **linhas** não aparece na fórmula, por isso é dispensável. Analogia: para converter "andar 2, porta 3" em numeração corrida, você precisa saber quantas portas há por andar; quantos andares o prédio tem é irrelevante.
*(Parte 3, seção 27.6)*

**15.** Imprime **`diferentes`**. `a` e `b` são **endereços** de dois vetores distintos, então `a == b` compara endereços, não conteúdo — e os endereços são diferentes. Para comparar conteúdo: `if (strcmp(a, b) == 0)`. Analogia: duas cartas com o mesmo texto em envelopes diferentes.
*(Parte 4, seção 36.3)*

**16.** **19 caracteres.** Uma das 20 posições é obrigatoriamente ocupada pelo `'\0'`, que marca o fim da string. Regra geral: `char[N]` comporta N−1 caracteres.
*(Parte 4, seção 34.4)*

**17.** É a **Cifra de César com k = 3**, o padrão "letra → posição → operar → letra":
- `c - 'A'` converte a letra maiúscula em posição no alfabeto (0–25)
- `+ 3` avança três posições
- `% 26` faz **dar a volta** ao passar do 'Z' — sem ele, `'Z' + 3` sairia do alfabeto e produziria um caractere qualquer
- `'A' +` converte a posição de volta em letra

Analogia do relógio: aritmética modular.
*(Parte 4, seção 32.3)*

**18.** O bug: se a letra **não existir**, o `for` termina normalmente com `i == 6` — e o código imprime `6`, um índice **fora dos limites válidos** (0–5). Pior: se depois desse trecho alguém usasse `s[i]`, estaria lendo fora do vetor.

Além disso, `char s[6] = "abcde"` usa as 6 posições exatas (5 letras + `'\0'`), então o laço `i < 6` chega a examinar o próprio `'\0'` na última iteração. O correto seria percorrer com `s[i] != '\0'` e sinalizar "não encontrado" explicitamente:

```c
int pos = -1;
for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == 'c') { pos = i; break; }
if (pos == -1) printf("nao encontrado\n");
else printf("%d\n", pos);
```
*(Parte 2, seção 17.3 + Parte 4, seção 34)*

**19.** `c` recebe **`'\n'`** (código 10), não `'A'`. O `scanf("%d")` consome o `5` mas **deixa o `\n` no buffer**; `%c` **não pula brancos** e lê esse `\n`.

Duas correções equivalentes:
```c
scanf("%d ", &n);      /* espaço DEPOIS: consome os brancos seguintes */
scanf(" %c", &c);      /* espaço ANTES: descarta brancos antes de ler */
```
A segunda é a mais usada na prática. **Esta é a causa nº 1 de "meu programa pula uma leitura".**
*(Parte 4, seções 32.4 e 35.7)*

**20.** Devolve **−99**.

Quando uma string é **prefixo** da outra, o laço avança enquanto os caracteres são iguais: compara `'a'=='a'`, `'b'=='b'`, e para em `i=2`, onde `str1[2]` é `'\0'` (código **0**) e `str2[2]` é `'c'` (código **99**).

O `if` interno não dispara porque o laço já havia parado (os caracteres são diferentes). Então retorna `0 - 99 = -99`, ou seja, **negativo** ⇒ `"ab"` vem antes de `"abc"`.

Isso está correto pela ordem de dicionário, e o mais elegante é que **o `'\0'` resolve o caso do prefixo de graça**: como ele vale 0 e qualquer caractere imprimível vale mais que 0, a string mais curta sempre sai como "menor".
*(Parte 4, seção 38.3)*

---

# ➡️ Próxima parte

**Parte 5 — Unidade 5: Curso de C, Parte 4** (o PDF que você acabou de enviar). É onde a disciplina finalmente vira *estrutura de dados*:

- **`struct`** — agrupar dados heterogêneos num tipo só (o que vetores não permitem!)
- **`typedef`** — dar nome a tipos
- Registros como parâmetro e como retorno
- **Números complexos** como estudo de caso
- **Tipo Abstrato de Dados (TAD)** — separar *o que a estrutura faz* de *como ela faz*
- **Arquivos `.h` e `.c`** — interface × implementação, e por que protótipos (Parte 1, seção 4.5) eram a preparação para isso
- **Makefile** e compilação de múltiplos arquivos
- Vantagens do TAD e como criar um
- Exercício completo: TAD de matrizes (`matriz.h`, `matriz.c`, `cliente_matriz.c`)

Este é o assunto que abre caminho para listas encadeadas, pilhas, filas e árvores — porque todas elas são TADs construídos com `struct` e ponteiros.


<div style="page-break-after: always"></div>

# MC-202 — Curso de C, Parte 4 (Unidade 5)
## Aula completa e comentada — **PARTE 5: `struct`, `typedef` e Tipos Abstratos de Dados**

> Cobre os 28 slides de "MC-202 — Curso de C — Parte 4", terminando no **Exercício de Matrizes**.
> **Esta é a unidade em que a disciplina deixa de ensinar "a linguagem C" e começa a ensinar "estrutura de dados".** Tudo que vem depois (listas encadeadas, pilhas, filas, árvores) é construído com as ideias desta aula.

---

# 39. O problema motivador: o centroide (slide 2)

## 39.1 O enunciado

> Dado um conjunto de pontos do plano, como calcular o **centroide**?

O centroide é o "centro de massa": a média dos x e a média dos y.

```c
#include <stdio.h>
#define MAX 100

int main () {
  double x[MAX], y[MAX];       /* UM vetor para cada coordenada */
  double cx, cy;
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%lf %lf", &x[i], &y[i]);
  cx = cy = 0;
  for (int i = 0; i < n; i++) {
    cx += x[i] / n;
    cy += y[i] / n;
  }
  printf("%lf %lf\n", cx, cy);
  return 0;
}
```

Duas observações rápidas sobre o código:

- `cx = cy = 0;` — atribuição encadeada. Funciona porque, como vimos na Parte 1, seção 6.3, **atribuição é uma expressão** cujo valor é o valor atribuído. Então `cy = 0` vale 0, e esse 0 é atribuído a `cx`.
- `cx += x[i] / n` divide **antes** de somar, em vez de somar tudo e dividir no fim. Matematicamente equivalente; numericamente um pouco pior (acumula n arredondamentos em vez de um). Detalhe, não erro.

## 39.2 A pergunta que motiva tudo

> **E se tivéssemos mais dimensões?** Precisaríamos de um vetor para cada dimensão…

Aí está o problema. Para 3 dimensões: `x[MAX]`, `y[MAX]`, `z[MAX]`. Para 10 dimensões, dez vetores. E toda função precisaria receber os dez.

E há um problema pior, mais sutil: **nada no código diz que `x[3]` e `y[3]` são o mesmo ponto.** Essa relação existe só na sua cabeça. Se você ordenar `x` e esquecer de ordenar `y` junto, os pontos se despedaçam silenciosamente.

**A informação que pertence junta está armazenada separada.** É esse o problema que `struct` resolve.

---

# 40. `struct`: agrupando dados relacionados (slides 3–7)

## 40.1 A ideia simples

Vetor guarda **muitos valores do mesmo tipo** (`int v[10]` — dez inteiros).

`struct` guarda **poucos valores de tipos diferentes**, dando um nome a cada um.

```c
struct ponto {
  double x, y;
};
```

Isso cria um **tipo novo** que junta um x e um y numa coisa só.

## 40.2 O que dizem os slides

> **Registro é:** uma coleção de dados relacionados **de vários tipos**, organizados em uma **única estrutura**, e referenciados por um **nome comum**.
>
> **Características:**
> - Cada dado é chamado de **membro** do registro
> - Cada membro é acessado por um nome na estrutura
> - Cada estrutura **define um novo tipo**, com as mesmas características de um tipo padrão da linguagem
>
> **Não é uma classe!** Não tem funções associadas. C não é Orientada a Objetos como Python.

Vale fixar a diferença fundamental com vetores:

| | Vetor | `struct` |
|---|---|---|
| Elementos | **muitos, do mesmo tipo** | **poucos, de tipos variados** |
| Identificados por | índice (`v[3]`) | nome (`p.x`) |
| Quantidade | definida na declaração | fixa na definição do tipo |
| Serve para | coleção de coisas iguais | **as partes de uma coisa só** |

**Vetor é "dez alunos". `struct` é "um aluno".** E você pode combinar os dois: um vetor de structs é "dez alunos, cada um com nome, RA e telefone".

## 40.3 Analogia: o formulário de papel

Um vetor é uma **lista de chamada**: uma coluna, cem linhas iguais, tudo do mesmo tipo.

Uma `struct` é um **formulário**: campos com rótulos diferentes — Nome (texto), RA (número), Data de nascimento (data). Cada campo tem seu nome e seu tipo. O formulário **em branco** é o *tipo*; cada formulário **preenchido** é um *registro*.

**Correspondência:**

| Analogia | Conceito |
|---|---|
| O modelo de formulário em branco | `struct ficha_aluno { ... };` — a **definição do tipo** |
| Um formulário preenchido | `struct ficha_aluno aluno;` — uma **variável** |
| Um campo do formulário | Um **membro** |
| O rótulo do campo ("Nome:") | O nome do membro |
| Ler o campo "Nome" | `aluno.nome` |
| Uma pasta com 100 formulários | `struct ficha_aluno turma[100];` |
| Fotocopiar um formulário preenchido | `aluno1 = aluno2;` |

Note que definir o modelo **não gasta papel**. Só quando você imprime um formulário é que ocupa espaço. Igualzinho: a definição da `struct` não ocupa memória; a declaração da variável ocupa.

## 40.4 Sintaxe (slide 4)

**Definindo o tipo:**

```c
struct identificador {
   tipo1 membro1;
   tipo2 membro2;
   ...
};                      /* ← ATENÇÃO: leva ponto e vírgula! */
```

**Declarando uma variável:**

```c
struct identificador nome_registro;
```

> Em C: declaramos um tipo de estrutura **apenas uma vez**; podemos declarar **vários registros** da mesma estrutura.

### ⚠️ Erro nº 1 dos iniciantes: o `;` depois da chave

```c
struct ponto {
  double x, y;
}          /* ← FALTA O ; */
```

Este é o único bloco em C que **leva `;` depois do `}`** — junto com o `do...while` (Parte 1, seção 8.2). Esquecê-lo gera mensagens de erro confusas, geralmente apontando para a linha *seguinte*.

### ⚠️ Erro nº 2: esquecer a palavra `struct` na declaração

```c
struct ponto p;       /* certo (sem typedef) */
ponto p;              /* ERRO — o tipo se chama "struct ponto", não "ponto" */
```

Isso é exatamente o que o `typedef` da seção 41 vem resolver.

## 40.5 Exemplo: ficha de aluno (slide 5)

```c
struct data {
   int dia;
   int mes;
   int ano;
};

struct ficha_aluno {
   int ra;
   int telefone;
   char nome[30];
   char endereco[100];
   struct data nascimento;     /* ← uma struct DENTRO de outra */
};
```

> Ou seja, podemos ter **estruturas aninhadas**.

Repare no que está acontecendo aqui, porque é importante:

- `char nome[30]` — **um vetor dentro de uma struct**. Perfeitamente legal.
- `struct data nascimento` — **uma struct dentro de uma struct**. Também legal.

Isso significa que `struct` é **composicional**: você monta tipos complexos a partir de simples. Uma turma é um vetor de fichas; uma ficha contém uma data; uma data contém três inteiros.

> ⚠️ Ordem importa: `struct data` precisa estar definida **antes** de ser usada dentro de `struct ficha_aluno`. Mesma lógica do compilador ler de cima para baixo (Parte 1, seção 4.5).

## 40.6 Usando um registro (slide 6)

> Acessando um membro do registro: **`registro.membro`**

```c
struct ficha_aluno aluno;
printf("Aluno: %s\n", aluno.nome);
```

**Aninhamento** — encadeie os pontos:

```c
printf("Aniversario: %d/%d\n", aluno.nascimento.dia,
                               aluno.nascimento.mes);
```

Leia da esquerda para a direita: *"do aluno, pegue o nascimento; do nascimento, pegue o dia"*.

### 🔑 O ponto mais surpreendente: structs se copiam com `=`

```c
aluno1 = aluno2;   // copia todos os dados de um para o outro
```

**Isto é enorme, e é a diferença mais importante entre `struct` e vetor.**

Lembre da Parte 2, seção 19: com vetores, `v1 = v2` **não compila**, e passar um vetor para função passa só o endereço. Com `struct`, `=` copia **todos os membros, um por um**, de verdade.

Consequências que decorrem disso:

| | Vetor | `struct` |
|---|---|---|
| `a = b` copia o conteúdo? | ❌ nem compila | ✅ **sim** |
| Função recebe cópia ou original? | endereço (**modifica o original**) | **cópia** (não modifica o original) |
| Pode ser devolvida por `return`? | ❌ não | ✅ **sim** |

**A `struct` se comporta como um `int`**: é copiada na atribuição, é copiada na passagem para função, e pode ser retornada. É por isso que o slide 3 diz que uma estrutura *"define um novo tipo, com as mesmas características de um tipo padrão da linguagem"*.

⚠️ **Pegadinha que decorre disso:** se a struct **contém um vetor**, a cópia copia o vetor inteiro também. `aluno1 = aluno2` copia os 30 bytes do nome e os 100 do endereço. Isso é conveniente — mas caro, e essa conta vai voltar a nos assombrar na seção 47.

## 40.7 O centroide revisitado (slide 7)

```c
struct ponto {
   double x, y;
};

int main () {
  struct ponto v[MAX], centroide;      /* vetor de structs! */
  int i, n;
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%lf %lf", &v[i].x, &v[i].y);
  centroide.x = 0;
  centroide.y = 0;
  for (i = 0; i < n; i++) {
    centroide.x += v[i].x / n;
    centroide.y += v[i].y / n;
  }
  printf("%lf %lf\n", centroide.x, centroide.y);
  return 0;
}
```

**O que melhorou em relação ao slide 2:**

1. **Um vetor só**, em vez de um por dimensão.
2. `v[i].x` e `v[i].y` são visivelmente **o mesmo ponto**. A relação está no código, não na sua cabeça.
3. Acrescentar uma dimensão é adicionar `double z;` à struct — **as declarações e as assinaturas não mudam**.
4. `centroide` é um ponto, não duas variáveis soltas. Pode ser devolvido por uma função.

**Note a sintaxe `&v[i].x`.** Como se lê? O `.` tem precedência maior que o `&`, então é `&(v[i].x)`: *"o endereço do membro x do elemento i"*. E precisa do `&` porque `scanf` escreve (Parte 1, seção 11).

## ✅ O que eu preciso saber deste tópico

- Definir `struct` e a diferença conceitual em relação a vetor.
- Escrever a definição de uma struct — **com o `;` depois da chave**.
- Acessar membros com `.`, inclusive aninhados.
- Declarar um **vetor de structs** e acessar `v[i].membro`.
- **Explicar por que `a = b` funciona com struct e não com vetor.**
- Saber que struct é passada por cópia e pode ser retornada.

---

# 41. `typedef`: dando nome aos tipos (slide 8)

## 41.1 A ideia simples

> O `typedef` permite dar um **novo nome** para um tipo.

```c
typedef unsigned int u32;
```

> Com isso, é possível declarar `u32 x;`. Escrever `unsigned int` ou `u32` é a mesma coisa.

É um **apelido**. Não cria tipo novo, não ocupa memória, não muda nada em tempo de execução. É conveniência de escrita — parecido em espírito com o `#define` (Parte 3, seção 24), mas processado pelo compilador, não pelo pré-processador.

## 41.2 A forma que interessa: `typedef` + `struct`

```c
typedef struct identificador {
  tipo1 membro1;
  ...
} novonome;
```

> Com isso, ao invés de `struct identificador var;`, podemos declarar `novonome var;`

Comparando lado a lado:

```c
/* SEM typedef */                    /* COM typedef */
struct ponto {                       typedef struct {
  double x, y;                         double x, y;
};                                   } Ponto;

struct ponto p;                      Ponto p;
struct ponto v[100];                 Ponto v[100];
struct ponto soma(struct ponto a,    Ponto soma(Ponto a, Ponto b);
                  struct ponto b);
```

A diferença de legibilidade fica gritante nas assinaturas de função.

## 41.3 A forma anônima

No slide 9 aparece:

```c
typedef struct {
  double real;
  double imag;
} complexo;
```

Repare: **não há nome depois de `struct`**. É uma struct *anônima* com um apelido. Funciona perfeitamente e é a forma mais comum.

**Quando você precisa do nome?** Quando a struct precisar se referir a si mesma:

```c
typedef struct No {           /* ← o nome "No" é obrigatório aqui */
    int valor;
    struct No *proximo;       /* aponta para outro nó do mesmo tipo */
} No;
```

Guarde isso: **é exatamente assim que uma lista encadeada é declarada.** Você vai escrever essa struct muitas vezes neste curso. A `struct Matriz` do exercício final também usa o nome, embora não precise.

## 41.4 Convenções

Não há regra da linguagem, mas o costume é:

| Estilo | Exemplo |
|---|---|
| Nome do tipo em maiúscula inicial | `Matriz`, `Ponto`, `No` |
| Tudo minúsculo | `complexo`, `matriz` |
| Sufixo `_t` | `matriz_t` |

Os slides usam `complexo` (minúsculo) e `Matriz` (maiúsculo) — inconsistente, mas irrelevante. **Escolha um estilo e seja consistente.**

## ✅ O que eu preciso saber deste tópico

- Explicar o que `typedef` faz (dá apelido a um tipo).
- Escrever `typedef struct { ... } Nome;`.
- Saber que sem `typedef` o tipo se chama `struct nome`.
- Saber quando o nome depois de `struct` é obrigatório (auto-referência).

---

# 42. Estudo de caso: números complexos (slides 9–12)

## 42.1 A versão ingênua (slide 9)

> Um número complexo é da forma `a + b·i`, onde a e b são reais e `i = √−1`. Queremos somar dois complexos lidos e calcular o valor absoluto (`√(a² + b²)`).

```c
typedef struct {
  double real;
  double imag;
} complexo;

int main () {
  complexo a, b, c;
  scanf("%lf %lf", &a.real, &a.imag);
  scanf("%lf %lf", &b.real, &b.imag);
  c.real = a.real + b.real;
  c.imag = a.imag + b.imag;
  printf("%lf\n", sqrt(c.real * c.real + c.imag * c.imag));
  return 0;
}
```

Funciona. Mas **toda a lógica de "como somar complexos" está espalhada na `main`**.

> 🔴 Nota: falta `#include <math.h>` (por causa do `sqrt`) e `#include <stdio.h>`. O slide mostra só o trecho relevante — mas se você for reproduzir, não esqueça.

## 42.2 A reflexão do slide 10 — o coração da aula

> Quando somamos 2 variáveis `float`, **não nos preocupamos como a operação é feita**. Internamente o float é representado por um número binário (ex: 0.3 é `00111110100110011001100110011010`). **O compilador esconde os detalhes!**
>
> E se quisermos lidar com números complexos? **Nos preocupamos com os detalhes.**
>
> **Será que também podemos abstrair um número complexo?** Sim — usando registros e funções. Faremos algo que se parece com uma classe.

Este slide é o argumento central de toda a disciplina, então vale destrinchar.

Quando você escreve `x + y` com `double`, você **não sabe nem precisa saber** que existe mantissa, expoente e bit de sinal; que a soma exige alinhar expoentes; que há arredondamento. Você pensa "somar dois números". O compilador cuida do resto.

**Isso é abstração: usar uma coisa pelo que ela faz, sem saber como ela faz.**

Com complexos, essa abstração some. Você é obrigado a escrever `c.real = a.real + b.real; c.imag = a.imag + b.imag;` toda vez. Você está de novo pensando em mantissa e expoente — só que no nível dos complexos.

**A pergunta do slide é: dá para recuperar a abstração?** E a resposta é sim: `struct` guarda os dados, funções escondem as operações.

### Analogia: dirigir sem saber mecânica

Você dirige um carro girando o volante e pisando no acelerador. Você **não precisa saber** como funciona a injeção eletrônica, a caixa de câmbio ou o diferencial. A interface (volante, pedais, câmbio) esconde uma máquina de milhares de peças.

E a prova de que a abstração é boa: você aprende a dirigir num carro e sabe dirigir **qualquer** carro. Se a montadora trocar o motor de combustão por elétrico, o volante continua girando igual — **seu conhecimento não é invalidado.**

**Correspondência:**

| Analogia | Conceito |
|---|---|
| Volante, pedais, câmbio | A **interface** (as funções públicas) |
| Motor, injeção, transmissão | A **implementação** |
| Motorista | O **cliente** (código que usa) |
| "Não preciso saber como funciona" | **Abstração** |
| Trocar o motor sem mudar o volante | Trocar a implementação sem quebrar clientes |
| Saber dirigir qualquer carro | Reutilização |

Guarde essa analogia: ela é literalmente a lista de vantagens do slide 20.

## 42.3 Usando funções (slide 11)

```c
complexo complexo_novo(double real, double imag) {
  complexo c;
  c.real = real;
  c.imag = imag;
  return c;
}

complexo complexo_soma(complexo a, complexo b) {
  return complexo_novo(a.real + b.real, a.imag + b.imag);
}

complexo complexo_le() {
  complexo a;
  scanf("%lf %lf", &a.real, &a.imag);
  return a;
}
```

**Repare no que essas funções fazem que seria impossível com vetores:**

- `complexo_novo` **devolve uma struct** por `return`. Com vetor isso não existe (Parte 2, seção 16.4).
- `complexo_soma` **recebe duas structs por cópia** e devolve uma terceira. Nenhum parâmetro de saída, nenhum ponteiro.

O código fica com cara de matemática: `c = soma(a, b)`. É exatamente o que a seção 40.6 previu — struct se comporta como tipo básico.

**`complexo_soma` chamando `complexo_novo`** é bom estilo: ela não sabe (nem precisa saber) como um complexo é construído. Se amanhã a struct ganhar um terceiro membro, só `complexo_novo` muda.

> O slide comenta: **DRY (Don't Repeat Yourself) vs. WET (Write Everything Twice)** — funções permitem reutilizar código. E: *"onde a função é usada, só é importante o seu resultado, não como o resultado é calculado"*.

> ⚠️ Detalhe técnico: `complexo complexo_le()` com parênteses vazios significa, em C, *"parâmetros não especificados"* — o compilador não checa nada nas chamadas. O correto é `complexo complexo_le(void)`. Não é erro (compila até com `-Wall -Werror`), mas `(void)` é a forma certa de dizer "não recebe nada".

## 42.4 O problema que sobra (slide 12)

O slide lista as funções possíveis (`complexo_absoluto`, `complexo_imprime`, `complexos_iguais`, `complexo_multiplicacao`, `complexo_conjugado`…) e então pergunta:

> **E se quisermos usar números complexos em vários programas?**
> - basta copiar a struct e as funções…
> - **e se acharmos um bug ou quisermos mudar algo?**
> - Essa solução não é DRY…

Aí está o problema final. Copiar e colar o código em cinco programas significa que um bug precisa ser corrigido em cinco lugares — e você vai esquecer de um.

**A solução é separar o código em arquivos.** É o assunto da próxima seção.

## ✅ O que eu preciso saber deste tópico

- **Explicar a analogia do `float`: por que você não pensa em mantissa ao somar reais.**
- Definir abstração com suas palavras.
- Escrever funções que recebem e devolvem structs.
- Explicar por que copiar e colar código não é DRY.

---

# 43. 🔑 Tipo Abstrato de Dados (slides 13–14)

## 43.1 A divisão em três partes (slide 13)

> Vamos quebrar o programa em três partes: **Cliente — Interface — Implementação**
>
> 1. **Implementação:** as funções para os números complexos. Definem *como* calcular soma, absoluto, etc.
> 2. **Cliente:** código que utiliza as funções. Soma dois complexos **sem se importar como**. Mas precisa conhecer o **protótipo** das funções.
> 3. **Interface:** struct e protótipos das funções. Define **o que o Cliente pode fazer** e **o que precisa ser implementado**.

## 43.2 A definição (slide 14)

> Um **TAD** é um conjunto de valores associado a um conjunto de operações permitidas nesses dados.
> - **Interface:** conjunto de operações de um TAD
> - **Implementação:** conjunto de algoritmos que realizam as operações
> - **Cliente:** código que utiliza/chama uma operação
>
> **Em C:**
> - um TAD é declarado como uma **struct**
> - a interface é um conjunto de **protótipos de funções** que manipula a struct

Note a estrutura da definição: **valores + operações**. Não basta ter os dados (a struct); é o par "dados + o que se pode fazer com eles" que forma o TAD.

## 43.3 A interface é um contrato

A melhor forma de entender: a interface é um **contrato de duas vias**.

```
        ┌──────────────────────────────────┐
        │          INTERFACE (.h)          │
        │   "toda Matriz sabe se somar"    │
        └──────────────────────────────────┘
              ▲                      ▲
              │ promete USAR         │ promete FORNECER
              │ só o que está aqui   │ tudo o que está aqui
        ┌─────┴──────┐        ┌──────┴──────────┐
        │  CLIENTE   │        │ IMPLEMENTAÇÃO   │
        │ (main)     │        │ (os algoritmos) │
        └────────────┘        └─────────────────┘
              ✗ não se conhecem diretamente ✗
```

Cliente e implementação **nunca se falam diretamente**. Toda comunicação passa pela interface. É isso que permite trocar a implementação sem tocar no cliente.

## 43.4 Analogia: o cardápio do restaurante

O **cardápio** lista os pratos e os preços. É a interface.

- O **cliente** lê o cardápio e pede "uma lasanha". Ele não entra na cozinha, não sabe a receita, não precisa saber.
- A **cozinha** é a implementação. Ela promete: para todo prato do cardápio, existe alguém que sabe fazer.

Se o chef mudar a receita da lasanha, trocar o forno ou contratar outro cozinheiro, **o cliente não precisa saber de nada** — desde que continue vindo lasanha. Mas se o cardápio anuncia um prato e a cozinha não sabe fazer, o restaurante quebra.

**Correspondência:**

| Analogia | Conceito |
|---|---|
| Cardápio | Arquivo `.h` (interface) |
| Item do cardápio | Protótipo de função |
| Cozinha | Arquivo `.c` (implementação) |
| Receita | Corpo da função |
| Freguês | Cliente (`main`) |
| Trocar a receita sem mudar o cardápio | Otimizar sem quebrar clientes |
| Prato no cardápio que a cozinha não faz | **Erro de linkagem** (*undefined reference*) |
| Pedir prato que não está no cardápio | **Erro de compilação** |

Essa última linha é útil na prática: se você errar o nome de uma função, o erro vem do **compilador**; se a função está declarada mas não implementada, o erro vem do **linker**, e a mensagem é diferente (`undefined reference to ...`).

## 43.5 "Faremos algo que se parece com uma classe"

O slide 10 diz isso, e o slide 3 avisou: *"Não é uma classe! Não tem funções associadas. C não é Orientada a Objetos."*

Vale esclarecer a semelhança e a diferença:

| | Classe (Python/Java) | TAD em C |
|---|---|---|
| Dados | atributos | membros da `struct` |
| Operações | métodos | funções que recebem a struct |
| Chamada | `c.soma(d)` | `complexo_soma(c, d)` |
| Vínculo dado↔função | a linguagem garante | **convenção de nomes** |
| Encapsulamento | `private` | nenhum — o cliente vê os membros |

**A diferença crucial:** em C, nada impede o cliente de escrever `c.real = 5`. A "privacidade" é **combinado social**, não regra da linguagem. Por isso a convenção de prefixar as funções (`complexo_`, `matriz_`) é levada a sério: ela é o que amarra as funções ao tipo.

## ✅ O que eu preciso saber deste tópico

- **Definir TAD: valores + operações.**
- Definir e distinguir interface, implementação e cliente.
- Explicar por que cliente e implementação não se conhecem.
- Explicar em que um TAD se parece e em que difere de uma classe.

---

# 44. Arquivos `.h` e `.c` (slides 15–17)

## 44.1 A interface: `complexos.h` (slide 15)

> Criamos um arquivo `complexos.h` com **a struct e os protótipos de função**.

```c
typedef struct {
  double real;
  double imag;
} complexo;

complexo complexo_novo(double real, double imag);
complexo complexo_soma(complexo a, complexo b);
double   complexo_absoluto(complexo a);
complexo complexo_le();
void     complexo_imprime(complexo a);
int      complexos_iguais(complexo a, complexo b);
complexo complexo_multiplicacao(complexo a, complexo b);
complexo complexo_conjugado(complexo a);
```

**O `.h` contém apenas:** definições de tipo (`typedef`, `struct`), protótipos e `#define`. **Nunca corpos de função.**

E olha só: **protótipos**. Aquele conceito da Parte 1, seção 4.5, que parecia burocracia inútil, é exatamente o mecanismo que torna TADs possíveis. O `.h` é um "índice do livro" que se pode entregar a qualquer programa.

## 44.2 A implementação: `complexos.c` (slide 16)

```c
#include <stdio.h>
#include <math.h>          /* bibliotecas usadas */
#include "complexos.h"     /* tem a definição da struct */

complexo complexo_novo(double real, double imag) {
  complexo c;
  c.real = real;
  c.imag = imag;
  return c;
}
/* ... demais funções ... */
```

### ⚠️ `#include "arquivo.h"` com **aspas**, não `<>`

| Forma | Onde procura |
|---|---|
| `#include <stdio.h>` | nos diretórios **do sistema** |
| `#include "complexos.h"` | **primeiro na pasta atual**, depois no sistema |

**Regra: aspas para os seus arquivos, `<>` para bibliotecas.**

### Por que o `.c` inclui o próprio `.h`?

Porque ele precisa da definição da `struct complexo` para poder declarar variáveis daquele tipo. E há um segundo benefício: se você escrever a implementação com assinatura diferente do protótipo, **o compilador acusa a divergência**. O `.h` funciona como conferência.

## 44.3 O cliente (slide 17)

```c
#include <stdio.h>
#include "complexos.h"     /* tem a struct e as funções */

int main () {
  complexo a, b, c;
  a = complexo_le();
  b = complexo_le();
  c = complexo_soma(a, b);
  complexo_imprime(c);
  printf("%lf\n", complexo_absoluto(c));
  return 0;
}
```

Compare com a versão da seção 42.1. O cliente virou **matemática legível**. Nenhuma menção a `.real` ou `.imag`. Nenhuma fórmula de raiz quadrada.

E o mais importante: **o cliente não inclui `complexos.c`.** Ele inclui só o `.h` — só o cardápio. Ele nem precisa que a implementação exista para ser *compilado* (só para ser *linkado*).

## ✅ O que eu preciso saber deste tópico

- Saber o que vai no `.h` e o que vai no `.c`.
- **Saber que `.h` nunca tem corpo de função.**
- Diferenciar `#include <>` de `#include ""`.
- Explicar por que o `.c` inclui o próprio `.h`.
- Escrever um cliente que usa só o `.h`.

---

# 45. Compilação separada e Makefile (slides 18–19)

## 45.1 Compilando por partes (slide 18)

> Temos três arquivos: `cliente.c` (a `main`), `complexos.c` (implementação), `complexos.h` (interface).

```
gcc -std=c99 -Wall -Werror -Wvla -g -c cliente.c      → gera cliente.o
gcc -std=c99 -Wall -Werror -Wvla -g -c complexos.c    → gera complexos.o
gcc cliente.o complexos.o -lm -o cliente              → linkagem
```

**A flag nova é `-c`: "compile, mas não linke".** Ela produz um arquivo-objeto `.o` — código de máquina com "buracos" nos lugares onde há chamadas a funções de outros arquivos.

**O processo em duas fases:**

```
cliente.c  ──compilação──▶ cliente.o    ┐
                                        ├──linkagem──▶ cliente (executável)
complexos.c ──compilação──▶ complexos.o ┘
```

- **Compilação (`-c`):** cada `.c` vira `.o`, independentemente. Aqui se pegam erros de sintaxe e de tipo.
- **Linkagem:** o linker junta os `.o`, preenche os buracos, adiciona bibliotecas (`-lm`). Aqui se pegam funções declaradas mas não implementadas.

> Note que `-lm` aparece só na linkagem. Faz sentido: bibliotecas são um assunto de junção, não de tradução.

## 45.2 Makefile (slide 19)

> É mais fácil usar um Makefile para compilar. **Apenas recompila o que for necessário!**

```make
all: cliente

cliente: cliente.o complexos.o
	gcc cliente.o complexos.o -g -lm -o cliente

cliente.o: cliente.c complexos.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c cliente.c

complexos.o: complexos.c complexos.h
	gcc -std=c99 -Wall -Werror -Wvla -c complexos.c
```

> Basta executar `make` na pasta com `cliente.c`, `complexos.c`, `complexos.h` e `Makefile`.

### Como ler um Makefile

Cada bloco é uma **regra** com três partes:

```make
alvo: dependências
	comando
```

Leia como: *"para construir **alvo**, preciso de **dependências**; se alguma delas for mais nova que o alvo, execute **comando**"*.

⚠️ **A linha do comando precisa começar com TAB, não espaços.** Este é o erro nº 1 de quem escreve Makefile pela primeira vez, e a mensagem de erro (`missing separator`) não ajuda em nada.

### Eu testei o "recompila só o necessário"

Montei o projeto e rodei `make` em três situações:

```
$ make                          # do zero
gcc ... -c cliente_matriz.c
gcc ... -c matriz.c
gcc cliente_matriz.o matriz.o -g -lm -o cliente

$ touch matriz.h ; make         # mudei a INTERFACE
gcc ... -c cliente_matriz.c     ← recompilou OS DOIS
gcc ... -c matriz.c
gcc ... -o cliente

$ touch matriz.c ; make         # mudei só a IMPLEMENTAÇÃO
gcc ... -c matriz.c             ← recompilou SÓ ELE
gcc ... -o cliente

$ make                          # nada mudou
make: Nothing to be done for 'all'.
```

**Observe a segunda situação, que é a mais instrutiva.** Mudar o `.h` obrigou a recompilar o cliente também — porque o cliente depende da interface. Mudar o `.c` não afetou o cliente, porque ele nunca viu a implementação.

Isso é a separação interface/implementação aparecendo até no *tempo de compilação*. Num projeto de mil arquivos, mudar uma implementação recompila um arquivo; mudar um `.h` recompila todos que o incluem.

### Um Makefile um pouco melhor

```make
CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDLIBS = -lm

all: cliente

cliente: cliente_matriz.o matriz.o
	gcc cliente_matriz.o matriz.o -g $(LDLIBS) -o cliente

cliente_matriz.o: cliente_matriz.c matriz.h
	gcc $(CFLAGS) -c cliente_matriz.c

matriz.o: matriz.c matriz.h
	gcc $(CFLAGS) -c matriz.c

clean:
	rm -f *.o cliente
```

As variáveis evitam repetição (se mudar uma flag, muda num lugar), e o alvo `clean` (rodado com `make clean`) apaga os arquivos gerados.

> 🔴 Detalhe: no Makefile do slide 19, a última linha **não tem o `-g`** que as outras têm. Provavelmente descuido. Sem `-g` naquele arquivo, o `gdb` não mostra as linhas de `complexos.c`.

## ✅ O que eu preciso saber deste tópico

- Explicar o que a flag `-c` faz e o que é um `.o`.
- **Distinguir erro de compilação de erro de linkagem.**
- Ler uma regra de Makefile (alvo, dependências, comando).
- Saber que o comando começa com **TAB**.
- Explicar por que mudar o `.h` recompila mais coisas que mudar o `.c`.

---

# 46. Vantagens do TAD e `#ifndef` (slides 20–22)

## 46.1 As vantagens (slide 20)

> - **Reutilizar o código em vários programas** — `complexos.{c,h}` podem ser usados em outros lugares; permite criar bibliotecas de tipos úteis (ex: álgebra linear)
> - **Código mais simples, claro e elegante** — o cliente só se preocupa em usar funções; o TAD só em disponibilizá-las
> - **Separa a implementação da interface** — podemos mudar a implementação sem quebrar clientes; os resultados precisam ser os mesmos, mas permite otimizações ou novas funções
> - **O código fica modular** — mais fácil colaborar; arquivos menores com responsabilidade bem definida
> - **Permite disponibilizar apenas o `.h` e `.o`** — não precisa disponibilizar o código-fonte da biblioteca

Cada uma dessas é a analogia do carro (seção 42.2) em outra roupagem: trocar o motor sem mudar o volante; saber dirigir qualquer carro; não precisar abrir o capô.

**Sobre a última:** você pode distribuir `matriz.h` + `matriz.o` e o cliente compila normalmente, **sem jamais ver seu código-fonte**. É assim que bibliotecas comerciais são vendidas.

**E a vantagem que a lista não menciona explicitamente, mas é a maior de todas:** o TAD te permite **pensar em um nível mais alto**. Depois de escrever `matriz.c`, você para de pensar em índices `i`, `j`, `k` e passa a pensar em "multiplicar matrizes". Esse ganho de nível é o que torna possível construir listas, árvores e grafos sem enlouquecer.

## 46.2 O `#ifndef` — include guard (slide 22)

> Pode ser que você tenha dois TADs e um precise incluir o outro… o que leva a um **loop de inclusão**. Podemos usar o `#ifndef` para evitar isso.

```c
#ifndef ARQUIVO_H       // trocamos ARQUIVO pelo nome do arquivo
#define ARQUIVO_H

// Conteúdo do arquivo.h

#endif
```

### Como funciona

Lembre (Parte 3, seção 24): `#include` **copia e cola** o arquivo. Se `a.h` inclui `b.h`, e seu programa inclui os dois, o conteúdo de `b.h` é colado **duas vezes**. E definir a mesma struct duas vezes é erro.

O mecanismo, linha por linha:

| Linha | Significa |
|---|---|
| `#ifndef ARQUIVO_H` | "**se não** estiver definida a macro `ARQUIVO_H`…" |
| `#define ARQUIVO_H` | "…defina-a agora" (primeira passagem) |
| *conteúdo* | processado só na primeira vez |
| `#endif` | fim do bloco condicional |

Na **segunda** inclusão, `ARQUIVO_H` já está definida, o `#ifndef` é falso, e **todo o conteúdo é ignorado**. O arquivo é incluído uma vez só, não importa quantas vezes você peça.

### Eu provei que o problema é real

Montei `a.h` incluindo `b.h`, e um programa incluindo os dois. **Sem** o guard:

```
b.h:1:27: error: conflicting types for 'B'; have 'struct <anonymous>'
```

Erro de compilação. **Com** o `#ifndef` em `b.h`: compilou limpo.

### Analogia: a lista de presença da reunião

Você organiza uma reunião e cada convidado pode trazer outros. Sem controle, a mesma pessoa pode ser convidada por três amigos e aparecer três vezes na lista.

Com uma **lista de presença na porta**: ao entrar, verifica-se se o nome já está lá. Se estiver, a pessoa não entra de novo.

**Correspondência:** a lista é o conjunto de macros definidas; o nome é `ARQUIVO_H`; conferir a lista é o `#ifndef`; assinar é o `#define`; entrar é processar o conteúdo.

**Regra prática: todo `.h` que você escrever deve ter include guard.** Não custa nada e evita um bug chato. O nome da macro deve ser único — a convenção é o nome do arquivo em maiúsculas com `_H`.

## ✅ O que eu preciso saber deste tópico

- Citar três vantagens do TAD e justificá-las.
- **Explicar o problema da inclusão dupla e como o `#ifndef` resolve.**
- Escrever um include guard corretamente.
- Explicar por que se pode distribuir `.h` + `.o` sem o `.c`.

---

# 47. 🎯 EXERCÍCIO: TAD de Matrizes (slides 23–27)

> **Faça um TAD que representa uma matriz de reais e que suporte as operações mais comuns para matrizes como multiplicação, adição, etc.**

Vamos primeiro seguir a receita do slide 21, depois analisar a solução dos slides, e por fim construir uma versão melhor.

## 47.1 A receita (slide 21)

> Construímos o TAD definindo:
> - **Um nome para o tipo** (ex: `complexo`) — uma struct com typedef
> - **Quais funções ele deve responder** — considerando entradas, saídas e resultado esperado. **Idealmente, cada função tem apenas uma responsabilidade.**
>
> Ou seja, **primeiro definimos a interface**. Basta então fazer uma possível implementação.

**"Primeiro a interface" é a lição de método mais importante da unidade.** Antes de escrever uma linha de algoritmo, decida *o que* o tipo faz. É o mesmo top-down do slide 12 da Unidade 3, agora aplicado a tipos.

## 47.2 A solução dos slides — `matriz.h` (slide 24)

```c
#ifndef MATRIZ_H
#define MATRIZ_H
#define MATRIZ_MAX 100

typedef struct Matriz {
    double elementos[MATRIZ_MAX][MATRIZ_MAX];
    int linhas;
    int colunas;
} Matriz;

Matriz matriz_nova(int linhas, int colunas, double elementos[][MATRIZ_MAX]);
void   matriz_imprime(Matriz m);
Matriz matriz_adiciona(Matriz m1, Matriz m2);
Matriz matriz_multiplica(Matriz m1, Matriz m2);
Matriz matriz_multiplica_escalar(Matriz m, double escalar);

#endif
```

**A decisão de projeto mais importante está nos três membros da struct:**

```c
double elementos[MATRIZ_MAX][MATRIZ_MAX];   /* os dados */
int linhas;                                 /* dimensões REAIS em uso */
int colunas;
```

Lembre da Parte 3, seção 27.6: quando você passa uma matriz crua para uma função, precisa passar `n` separado, e o número de colunas tem que estar no cabeçalho. **A struct resolve isso**: as dimensões viajam *junto* com os dados. `matriz_adiciona(m1, m2)` não precisa de mais nenhum parâmetro.

Isso é a mesma ideia do `'\0'` nas strings (Parte 4, seção 34): **fazer o dado carregar a própria informação de tamanho.**

Note também o `MATRIZ_MAX` com prefixo, e não `MAX`. Boa prática: como o `.h` pode ser incluído em qualquer programa, um `#define MAX 100` colidiria com o `MAX` do cliente.

## 47.3 A implementação (slides 25–26)

```c
Matriz matriz_adiciona(Matriz m1, Matriz m2) {
    Matriz m;
    m.linhas = m1.linhas;
    m.colunas = m1.colunas;
    for (int i = 0; i < m1.linhas; i++)
        for (int j = 0; j < m1.colunas; j++)
            m.elementos[i][j] = m1.elementos[i][j] + m2.elementos[i][j];
    return m;
}

Matriz matriz_multiplica(Matriz m1, Matriz m2) {
    Matriz m;
    m.linhas = m1.linhas;
    m.colunas = m2.colunas;
    for (int i = 0; i < m1.linhas; i++)
        for (int j = 0; j < m2.colunas; j++) {
            m.elementos[i][j] = 0;
            for (int k = 0; k < m1.colunas; k++)
                m.elementos[i][j] += m1.elementos[i][k] * m2.elementos[k][j];
        }
    return m;
}
```

**Pontos a observar:**

- `m.linhas = m1.linhas; m.colunas = m2.colunas;` na multiplicação — está **correto**: o produto de uma (a×b) por uma (b×c) é (a×c).
- `m.elementos[i][j] = 0;` antes do `+=` — **obrigatório**, como já vimos na Parte 3, seção 28.3. Sem isso, acumula lixo.
- É o mesmo triplo laço O(n³) da Unidade 3, agora encapsulado.

**Compilei os três arquivos exatamente como estão nos slides**, com as flags da disciplina, e rodei o cliente do slide 27:

```
Soma:            Multiplicacao:      Escalar x2:
6.000000  8.000000    19.000000 22.000000    2.000000 4.000000
10.000000 12.000000   43.000000 50.000000    6.000000 8.000000
```

**Os resultados estão matematicamente corretos.** A solução funciona.

## 47.4 🔴 Análise crítica — quatro problemas reais

### Problema 1: nenhuma verificação de dimensões

Somar uma matriz 2×3 com uma 2×2 é indefinido em matemática. E multiplicar (2×3) por (2×2) é impossível — o número de colunas da primeira tem que igualar o de linhas da segunda.

**Testei os dois casos:**

```
--- somando 2x3 com 2x2 (INCOMPATIVEL) ---
2.000000 4.000000 6.000000
7.000000 9.000000 12.000000

--- multiplicando 2x3 por 2x2 (INCOMPATIVEL: 3 != 2) ---
7.000000 10.000000
19.000000 28.000000
```

**Nenhum erro. Nenhum aviso. Números plausíveis, todos errados.**

De onde vieram? `matriz_nova` só copia `linhas × colunas` elementos — o resto de `m.elementos` fica com **lixo** (Parte 1, seção 7.2). A soma leu `m2.elementos[0][2]`, que nunca foi inicializado.

Esse é o pior tipo de bug: **saída plausível**. Se essas matrizes fossem parte de um cálculo maior, você jamais desconfiaria.

**Um TAD tem a obrigação de proteger seu invariante.** Se a operação é impossível, ele precisa dizer isso.

### Problema 2: passar `Matriz` por valor custa caro

Aqui está a conta que eu medi:

```
sizeof(Matriz)  = 80008 bytes (78,1 KB)
  elementos     = 80000 bytes
  linhas+colunas=     8 bytes
```

Cada `Matriz` ocupa **78 KB**, esteja ela sendo usada como 100×100 ou como 2×2.

E como structs são passadas **por cópia** (seção 40.6), uma única chamada custa:

```
matriz_adiciona(m1, m2):
   cópia de m1     78 KB
   cópia de m2     78 KB
   cópia do retorno 78 KB
   ─────────────────────
   TOTAL          234 KB copiados
```

Para somar duas matrizes 2×2, que precisam de **64 bytes** de dados úteis. Mais de 99,9% do trabalho é copiar lixo não inicializado.

E o cliente do slide 27 declara **duas matrizes cruas de 80 KB mais cinco `Matriz`** — cerca de 550 KB de variáveis locais na pilha. Funciona (o limite típico é 8 MB), mas basta aumentar `MATRIZ_MAX` para 1000 e o programa morre com estouro de pilha antes de executar a primeira linha.

**Este é exatamente o preço da conveniência que a seção 40.6 elogiou.** Struct copiar-se sozinha é ótimo para um `complexo` de 16 bytes e péssimo para uma `Matriz` de 78 KB.

> **A solução definitiva é passar ponteiros** (`const Matriz *m`), que copia 8 bytes em vez de 78 KB — e é o que você vai aprender na próxima unidade. É também por isso que a disciplina vai insistir tanto em `malloc`: uma matriz alocada dinamicamente usaria exatamente `linhas × colunas × 8` bytes, não 80 000.

### Problema 3: `matriz_nova` obriga o cliente a criar um array gigante

```c
double elementos1[MATRIZ_MAX][MATRIZ_MAX] = {{1, 2}, {3, 4}};
Matriz m1 = matriz_nova(2, 2, elementos1);
```

Para criar uma matriz 2×2, o cliente precisa declarar um array de **80 KB**. Isso vaza um detalhe da implementação (o `MATRIZ_MAX`) para dentro do cliente — o oposto do que um TAD deveria fazer. O freguês teve que entrar na cozinha.

### Problema 4: detalhes menores

- `#include <stdlib.h>` em `matriz.c` **não é usado**. Ruído.
- Faltam operações que o enunciado pede com "etc.": **transposta, subtração, identidade, comparação**.
- Não há função de **leitura** (`matriz_le`), então o cliente não consegue ler do teclado.

## 47.5 ✅ Versão melhorada — a que eu recomendo entregar

Reconstruí o TAD corrigindo os problemas 1, 3 e 4. **Compilei com `-Wall -Werror -Wvla` e testei todos os casos**, inclusive os inválidos.

O problema 2 (o custo da cópia) **não dá para resolver ainda** sem ponteiros — deixo assinalado onde ele se resolverá.

### `matriz.h` — a interface

```c
#ifndef MATRIZ_H
#define MATRIZ_H
#define MATRIZ_MAX 100

typedef struct {
    double elementos[MATRIZ_MAX][MATRIZ_MAX];
    int linhas;
    int colunas;
} Matriz;

/* Construtores */
Matriz matriz_zeros(int linhas, int colunas);
Matriz matriz_identidade(int n);
Matriz matriz_le(int linhas, int colunas);

/* Consulta */
int    matriz_valida(Matriz m);
void   matriz_imprime(Matriz m);
int    matriz_iguais(Matriz a, Matriz b);

/* Operações */
Matriz matriz_adiciona(Matriz a, Matriz b);
Matriz matriz_subtrai(Matriz a, Matriz b);
Matriz matriz_multiplica(Matriz a, Matriz b);
Matriz matriz_multiplica_escalar(Matriz m, double escalar);
Matriz matriz_transposta(Matriz m);

#endif
```

**As decisões de projeto, e o porquê de cada uma:**

**1. Uma matriz inválida tem `linhas = 0`.** Como uma matriz real sempre tem pelo menos 1 linha, `linhas == 0` é um valor impossível — perfeito para sinalizar erro. Isso permite devolver "deu errado" **sem ponteiros e sem parâmetro de saída**.

Este é o mesmo truque do `return 0` em `eh_primo` (Parte 1) e do `'\0'` nas strings: **reservar um valor impossível para significar algo especial.**

**2. `matriz_zeros` substitui `matriz_nova`.** O cliente não precisa mais de um array de 80 KB. Ele cria a matriz e preenche.

**3. `matriz_valida` é pública.** O cliente precisa poder checar o resultado.

### `matriz.c` — trechos essenciais

```c
#include "matriz.h"
#include <stdio.h>
#include <math.h>
#define EPS 1e-9

static Matriz matriz_invalida(void) {
    Matriz m;
    m.linhas = 0;
    m.colunas = 0;
    return m;
}

int matriz_valida(Matriz m) {
    return m.linhas > 0 && m.colunas > 0;
}

Matriz matriz_zeros(int linhas, int colunas) {
    if (linhas < 1 || colunas < 1 ||
        linhas > MATRIZ_MAX || colunas > MATRIZ_MAX)
        return matriz_invalida();
    Matriz m;
    m.linhas = linhas;
    m.colunas = colunas;
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            m.elementos[i][j] = 0.0;
    return m;
}

Matriz matriz_adiciona(Matriz a, Matriz b) {
    if (a.linhas != b.linhas || a.colunas != b.colunas)
        return matriz_invalida();                    /* ← a verificação */
    Matriz m = matriz_zeros(a.linhas, a.colunas);
    for (int i = 0; i < a.linhas; i++)
        for (int j = 0; j < a.colunas; j++)
            m.elementos[i][j] = a.elementos[i][j] + b.elementos[i][j];
    return m;
}

Matriz matriz_multiplica(Matriz a, Matriz b) {
    if (a.colunas != b.linhas)                       /* ← a regra matemática */
        return matriz_invalida();
    Matriz m = matriz_zeros(a.linhas, b.colunas);
    for (int i = 0; i < a.linhas; i++)
        for (int j = 0; j < b.colunas; j++) {
            double soma = 0.0;                       /* acumula em local */
            for (int k = 0; k < a.colunas; k++)
                soma += a.elementos[i][k] * b.elementos[k][j];
            m.elementos[i][j] = soma;
        }
    return m;
}

Matriz matriz_transposta(Matriz m) {
    if (!matriz_valida(m)) return matriz_invalida();
    Matriz t = matriz_zeros(m.colunas, m.linhas);    /* dimensões TROCADAS */
    for (int i = 0; i < m.linhas; i++)
        for (int j = 0; j < m.colunas; j++)
            t.elementos[j][i] = m.elementos[i][j];   /* índices TROCADOS */
    return t;
}

int matriz_iguais(Matriz a, Matriz b) {
    if (a.linhas != b.linhas || a.colunas != b.colunas) return 0;
    for (int i = 0; i < a.linhas; i++)
        for (int j = 0; j < a.colunas; j++)
            if (fabs(a.elementos[i][j] - b.elementos[i][j]) > EPS)
                return 0;                            /* ← fabs, não == */
    return 1;
}

Matriz matriz_subtrai(Matriz a, Matriz b) {
    return matriz_adiciona(a, matriz_multiplica_escalar(b, -1.0));
}
```

**Cinco detalhes que valem comentário:**

1. **`static` em `matriz_invalida`** — a palavra `static` numa função a torna **visível só dentro deste arquivo**. É uma função auxiliar interna: não está no `.h`, o cliente não pode chamá-la. É o mais próximo de `private` que C oferece, e vale conhecer.

2. **`matriz_zeros` valida os limites.** Se alguém pedir 200 linhas com `MATRIZ_MAX 100`, devolve inválida em vez de estourar o vetor. É o problema de validação que apontei nas Partes 2 e 3, finalmente resolvido.

3. **A multiplicação acumula em `double soma` local** em vez de `m.elementos[i][j] += ...`. Duas vantagens: evita reescrever na memória a cada iteração do `k`, e elimina a possibilidade de esquecer o `= 0` inicial.

4. **`matriz_iguais` usa `fabs(...) > EPS`**, nunca `==`. É a regra da Parte 3, seção 22.3 — comparar reais por proximidade.

5. **`matriz_subtrai` reaproveita duas funções existentes.** A − B é A + (−1)·B. Três linhas em vez de dez, e se houver um bug na soma, ele é corrigido num lugar só. É DRY na prática. (O custo: mais uma cópia de 78 KB. Se o desempenho importasse, valeria escrever o laço.)

### `cliente_matriz.c` e o resultado real

```c
#include <stdio.h>
#include "matriz.h"

int main(void) {
    Matriz a = matriz_zeros(2, 3);
    a.elementos[0][0]=1; a.elementos[0][1]=2; a.elementos[0][2]=3;
    a.elementos[1][0]=4; a.elementos[1][1]=5; a.elementos[1][2]=6;
    Matriz b = matriz_transposta(a);
    matriz_imprime(matriz_multiplica(a, b));
    ...
}
```

Saída real do programa que compilei e rodei:

```
A (2x3):                A^T (3x2):            A * A^T (2x2):
    1.00 2.00 3.00          1.00 4.00            14.00 32.00
    4.00 5.00 6.00          2.00 5.00            32.00 77.00
                            3.00 6.00

A * I(3) == A ?  1                      ← a identidade funciona

--- casos INVALIDOS ---
A(2x3) + I(3)    -> <matriz invalida>   ← agora avisa!
A(2x3) * A(2x3)  -> <matriz invalida>
matriz_zeros(0,5)-> <matriz invalida>
```

Compare com a versão dos slides, que produzia números errados em silêncio nos mesmos três casos.

> 💡 Note o teste `A × I == A`. Multiplicar pela identidade deve devolver a matriz original — é uma **propriedade matemática** que serve de teste automático. Testar TADs por propriedades (A+B = B+A, (Aᵀ)ᵀ = A, A−A = 0) é muito mais eficaz que conferir números na mão.

## 47.6 Complexidade das operações

| Operação | Custo (matriz n×m) |
|---|---|
| `matriz_zeros`, `matriz_identidade` | O(n·m) |
| `matriz_imprime`, `matriz_le` | O(n·m) |
| `matriz_adiciona`, `matriz_subtrai` | O(n·m) |
| `matriz_multiplica_escalar` | O(n·m) |
| `matriz_transposta` | O(n·m) |
| `matriz_iguais` | O(n·m) — pior caso |
| **`matriz_multiplica`** | **O(n·m·p)** — cúbico se quadradas |
| Cópia implícita a cada chamada | **O(MATRIZ_MAX²)** ⚠️ |

Aquela última linha é o problema 2 aparecendo na tabela: **a cópia custa O(100²) = 10 000 operações independentemente do tamanho real da matriz.** Somar duas matrizes 2×2 — que deveria custar 4 operações — custa 30 000 por causa das três cópias. A operação mais barata do TAD é dominada pelo overhead da passagem por valor.

Guarde essa observação. Ela é o argumento mais convincente que existe para aprender ponteiros.

## ✅ O que eu preciso saber deste tópico

- **Projetar um TAD começando pela interface.**
- Explicar por que guardar `linhas`/`colunas` dentro da struct resolve o problema da Parte 3.
- **Verificar compatibilidade de dimensões antes de operar.**
- Usar um valor impossível (`linhas = 0`) para sinalizar erro.
- Saber que `static` numa função a esconde do resto do programa.
- **Explicar por que passar `Matriz` por valor custa 78 KB e por que isso motiva ponteiros.**
- Escrever transposta, identidade e comparação com `fabs`.

---

# 📌 Consolidação da Parte 5

## Mapa mental da unidade

```
PROBLEMA: dados relacionados espalhados em vetores separados
        ↓
   struct — agrupa dados de tipos diferentes sob um nome
        ├── acesso com  .  (e aninhado: a.b.c)
        ├── vetor de structs:  v[i].membro
        ├── COPIA com =  (ao contrário de vetor!)
        ├── passada por CÓPIA para funções
        └── pode ser RETORNADA
        ↓
   typedef — apelido para o tipo (some o "struct")
        ↓
   REFLEXÃO: você soma double sem pensar em mantissa
        → isso é ABSTRAÇÃO
        → dá para fazer o mesmo com tipos seus?
        ↓
   TAD = valores (struct) + operações (funções)
        ↓
   ┌──────────────┬───────────────────┬──────────────────┐
   │   CLIENTE    │   INTERFACE (.h)  │ IMPLEMENTAÇÃO(.c)│
   │  usa         │  struct+protótipos│  os algoritmos   │
   │  não sabe    │  o CONTRATO       │  pode mudar      │
   │  como        │                   │  livremente      │
   └──────────────┴───────────────────┴──────────────────┘
        ↓                    ↓                   ↓
   #include "x.h"      #ifndef guard        static = privado
        ↓
   COMPILAÇÃO SEPARADA:  gcc -c  →  .o  →  linkagem
        └── Makefile: recompila só o necessário
        ↓
   LIMITAÇÃO QUE SOBRA: struct grande copiada a cada chamada (78 KB!)
        └──────────► resolvida por PONTEIROS + malloc (próxima unidade)
```

## `struct` × vetor — a tabela que cai em prova

| | Vetor | `struct` |
|---|---|---|
| Tipos dos elementos | todos iguais | **variados** |
| Acesso | índice `v[3]` | nome `p.x` |
| `a = b` | ❌ não compila | ✅ **copia tudo** |
| Passagem para função | **endereço** (modifica original) | **cópia** (não modifica) |
| Pode ser retornado? | ❌ | ✅ |
| Sabe o próprio tamanho? | ❌ | ✅ (se você guardar num membro) |

**As duas linhas do meio são a fonte nº 1 de confusão.** Vetor e struct se comportam de maneiras opostas, e a razão é a mesma da Parte 2, seção 19: o nome de um vetor decai para endereço; o nome de uma struct, não.

⚠️ **Consequência sutil que combina as duas:** se uma struct **contém** um vetor, o vetor é copiado junto na atribuição. `Matriz a = b;` copia os 80 000 doubles. Isso surpreende quem espera o comportamento de vetor.

## Os 10 erros mais comuns desta unidade

1. **Esquecer o `;` depois de `}` na definição da struct.**
2. Escrever `ponto p;` em vez de `struct ponto p;` (quando não há typedef).
3. Colocar **corpo de função no `.h`**.
4. Usar `#include <matriz.h>` em vez de `#include "matriz.h"`.
5. Esquecer o **include guard** → erro de redefinição.
6. Usar **espaços em vez de TAB** no Makefile.
7. Confundir erro de **compilação** com erro de **linkagem**.
8. Esquecer de linkar o `.o` da implementação → `undefined reference`.
9. **Não verificar dimensões/pré-condições** dentro do TAD.
10. Achar que passar uma struct grande é barato (não é: 78 KB por cópia).

## Essencial × detalhe × prova

**Essencial:** o que é `struct` e como acessar membros; `struct` copia com `=`; `typedef`; a tríade cliente/interface/implementação; o que vai em `.h` e em `.c`; include guard; compilação separada.

**Detalhe:** `static` em funções; nomes de convenção; variáveis no Makefile; `(void)` em protótipos sem parâmetros.

**Quase certo em prova:**
- **"Qual a diferença entre passar um vetor e passar uma struct para uma função?"**
- "O que vai no `.h` e o que vai no `.c`?"
- "Para que serve o `#ifndef`?"
- Escrever um TAD pequeno (Ponto, Fração, Data) com interface e implementação
- "Cite três vantagens de usar TAD"

---

# ➡️ O que vem por aí

Esta unidade fechou a fundação. O que falta para as estruturas de dados de verdade é **uma única peça**: ponteiros e alocação dinâmica.

Repare que os problemas que ficaram **em aberto** nas cinco partes apontam todos para o mesmo lugar:

| Problema em aberto | Onde apareceu | Resolvido por |
|---|---|---|
| Vetor tem tamanho fixo | Parte 2, seção 15.3 | `malloc` |
| "Não dá para devolver vetor" | Parte 2, seção 16.4 | ponteiro + `malloc` |
| Declarar `[100]` e desperdiçar | Partes 2, 3 e 5 | `malloc` do tamanho exato |
| Função não modifica um `int` recebido | Parte 2, seção 19 | ponteiro |
| Copiar 78 KB por chamada | Parte 5, seção 47.4 | `const Matriz *` |
| `struct No { struct No *proximo; }` | Parte 5, seção 41.3 | ponteiro |

**Uma peça, seis problemas.** E o mais importante: a última linha dessa tabela é a definição de uma **lista encadeada**.

Quando a próxima unidade chegar, é ali que eu vou finalmente poder montar a tabela comparativa de estruturas de dados que você pediu desde o começo — vetor × lista encadeada × pilha × fila × árvore, com memória, inserção, remoção, busca e complexidade de cada uma. Até agora seria invenção; a partir de ponteiros, vira conteúdo.


<div style="page-break-after: always"></div>

# Explicação detalhada — TAD Matriz (`matriz.h`, `matriz.c`, `cliente_matriz.c`)

> Leitura linha a linha do código dos slides 24 a 27 da Unidade 5.
> Tudo aqui foi compilado com `gcc -std=c99 -Wall -Werror -Wvla -g` e executado; as saídas mostradas são reais.

---

# A1. Panorama: por que TRÊS arquivos?

Antes de olhar qualquer linha, entenda o desenho geral. O programa foi partido em três pedaços com papéis diferentes:

```
   cliente_matriz.c              matriz.h                 matriz.c
   ┌──────────────┐         ┌──────────────┐         ┌──────────────┐
   │  a main      │         │  o CONTRATO  │         │ os ALGORITMOS│
   │              │         │              │         │              │
   │ "some essas  │────────▶│ typedef      │◀────────│ como somar   │
   │  matrizes"   │  usa    │ + protótipos │ cumpre  │ como multipl.│
   └──────────────┘         └──────────────┘         └──────────────┘
        CLIENTE                 INTERFACE              IMPLEMENTAÇÃO
        └──────────── não se conhecem diretamente ──────────┘
```

**A regra que organiza tudo:** o cliente e a implementação **nunca se enxergam**. Os dois só conhecem o `.h`.

Prova disso no código: `cliente_matriz.c` escreve `#include "matriz.h"` e **em nenhum lugar** menciona `matriz.c`. Ele nem precisa que `matriz.c` exista para ser compilado — só para ser *linkado*.

**Analogia do cardápio:** o `.h` é o cardápio, o `.c` é a cozinha, a `main` é o freguês. O freguês pede pelo cardápio; a cozinha promete fazer tudo que o cardápio anuncia. Trocar a receita não muda o cardápio, e o freguês nem percebe.

---

# A2. `matriz.h` — a interface, linha por linha

```c
1  #ifndef MATRIZ_H
2  #define MATRIZ_H
3  #define MATRIZ_MAX 100
```

**Linhas 1, 2 e 19 (`#endif`) formam o *include guard*.** Leia assim:

> *"**Se ainda não** existe a macro `MATRIZ_MAX_H`… então crie-a agora e processe tudo até o `#endif`."*

Na primeira vez que este arquivo é incluído, a macro não existe → o conteúdo é processado. Se algum outro arquivo incluir `matriz.h` de novo, a macro **já existe** → o `#ifndef` é falso → todo o conteúdo é pulado.

**Por que isso importa?** Porque `#include` é literalmente **copiar e colar**. Se o arquivo fosse colado duas vezes, o `typedef struct Matriz` apareceria duas vezes, e redefinir um tipo é erro de compilação. Eu testei essa situação e o gcc reclama assim:

```
error: conflicting types for 'B'; have 'struct <anonymous>'
```

Com o guard, compila limpo. **Regra: todo `.h` que você escrever leva include guard.**

**Linha 3:** `#define MATRIZ_MAX 100` cria a constante do tamanho máximo. Lembre (Unidade 3) que `#define` é substituição de texto feita **antes** de compilar — não leva `=` nem `;`. Onde aparecer `MATRIZ_MAX`, o compilador verá `100`.

Note o nome com prefixo: `MATRIZ_MAX`, não `MAX`. Isso é cuidado deliberado — como este `.h` pode ser incluído em qualquer programa, um `MAX` genérico colidiria com o `MAX` do cliente.

```c
6  typedef struct Matriz {
7      double elementos[MATRIZ_MAX][MATRIZ_MAX];
8      int linhas;
9      int colunas;
10 } Matriz;
```

**Esta é a decisão de projeto mais importante do TAD inteiro.** Vamos por partes.

| Elemento | O que significa |
|---|---|
| `struct Matriz {` | define uma estrutura chamada `Matriz` |
| `double elementos[100][100]` | os dados: uma matriz 100×100 de reais |
| `int linhas` | quantas linhas estão **realmente em uso** |
| `int colunas` | quantas colunas estão **realmente em uso** |
| `} Matriz;` | o `typedef` dá o apelido `Matriz` ao tipo |

**Por que guardar `linhas` e `colunas` dentro da struct?**

Lembre do problema da Unidade 3: quando você passava uma matriz crua para uma função, tinha que escrever

```c
void imprime_matriz_quadrada(double M[][MAX], int n)   /* o n vem separado */
```

Os dados iam por um caminho e o tamanho por outro. Se você errasse o `n`, ninguém percebia.

Com a struct, **as dimensões viajam junto com os dados**. Por isso a assinatura ficou:

```c
void matriz_imprime(Matriz m);      /* e só. o tamanho está dentro do m */
```

Essa ideia — *fazer o dado carregar a informação do próprio tamanho* — é exatamente a mesma do `'\0'` nas strings. É um padrão recorrente em C.

**O detalhe do `typedef`:** sem ele, você teria que escrever `struct Matriz m;` em todo lugar. Com ele, escreve só `Matriz m;`. Repare que o nome aparece duas vezes (depois de `struct` e depois de `}`) — são coisas diferentes: o primeiro é o nome da struct, o segundo é o apelido. Aqui os dois são iguais, o que é comum e legal.

```c
13 Matriz matriz_nova(int linhas, int colunas, double elementos[][MATRIZ_MAX]);
14 void   matriz_imprime(Matriz m);
15 Matriz matriz_adiciona(Matriz m1, Matriz m2);
16 Matriz matriz_multiplica(Matriz m1, Matriz m2);
17 Matriz matriz_multiplica_escalar(Matriz m, double escalar);
```

**São cinco protótipos** — funções sem corpo, terminadas em `;`. Este é o "cardápio": diz o que existe e como chamar, sem dizer como funciona.

Repare no padrão de nomes: **todas começam com `matriz_`**. Isso não é exigência da linguagem — é **convenção**, e é o que amarra as funções ao tipo. Em C não existe `m.imprime()` como em Python; o prefixo é o substituto disso.

Repare também nos tipos de retorno:

- `matriz_imprime` devolve `void` — só imprime, não produz valor.
- **As outras quatro devolvem `Matriz`** — uma struct inteira, por `return`.

**Isso seria impossível com vetores.** Lembre: `int[] funcao()` não existe em C. Mas struct pode ser retornada como se fosse um `int`. É essa propriedade que permite escrever `m3 = matriz_adiciona(m1, m2)` de forma natural.

E a linha 13, `double elementos[][MATRIZ_MAX]`, é a única que ainda usa matriz crua. Por isso ela precisa do `MATRIZ_MAX` nos colchetes: como vimos na Unidade 3, o compilador precisa do número de colunas para calcular `base + (i × colunas + j)`.

---

# A3. `matriz.c` — a implementação

```c
1  #include "matriz.h"
2  #include <stdio.h>
3  #include <stdlib.h>
```

**Aspas vs. sinais de menor/maior:**

| Forma | Onde o compilador procura |
|---|---|
| `#include "matriz.h"` | **primeiro na pasta atual** |
| `#include <stdio.h>` | nos diretórios do sistema |

**Regra: aspas para os seus arquivos, `<>` para bibliotecas.**

**Por que o `.c` inclui o próprio `.h`?** Por dois motivos:
1. Ele precisa da definição de `struct Matriz` para declarar variáveis do tipo.
2. Se você implementar uma função com assinatura diferente do protótipo, **o compilador acusa** — o `.h` funciona como conferência.

> 🔴 `<stdlib.h>` na linha 3 **não é usado** por nenhuma função deste arquivo. É ruído, provavelmente sobra de outro código. Inofensivo, mas removível.

## 3.1 `matriz_nova` — construindo uma matriz

```c
5  Matriz matriz_nova(int linhas, int colunas, double elementos[][MATRIZ_MAX]) {
6      Matriz m;
7      m.linhas = linhas;
8      m.colunas = colunas;
9      for (int i = 0; i < linhas; i++)
10         for (int j = 0; j < colunas; j++)
11             m.elementos[i][j] = elementos[i][j];
12     return m;
13 }
```

**Linha 6:** `Matriz m;` cria uma variável local do tipo `Matriz`. Neste instante ela contém **lixo** — 80 mil doubles indefinidos. É a mesma regra de sempre: variável não inicializada em C contém o que estava naquele espaço de memória.

**Linhas 7–8:** define as dimensões em uso. Note a sintaxe `m.linhas` — o ponto acessa um **membro** da struct.

⚠️ Cuidado com os nomes: `m.linhas` (o membro) e `linhas` (o parâmetro) são coisas diferentes. `m.linhas = linhas;` lê como *"o membro linhas da struct m recebe o valor do parâmetro linhas"*.

**Linhas 9–11:** os dois `for` aninhados copiam os elementos. `i` percorre as linhas, `j` percorre as colunas.

**O detalhe crucial:** o laço copia **apenas `linhas × colunas` elementos**, não os 10 000. Para uma matriz 2×2, só 4 posições são preenchidas — as outras 9 996 continuam com lixo.

Eu testei o que fica fora da região usada:

```
m foi criada como 2x2. O que há FORA dessa região?
           1           2           0   <- linha usada
           3           4           0   <- linha usada
           0           0           0   <- linha NÃO inicializada
```

Aqui o lixo por acaso era zero. **Noutra execução foi diferente** — num teste que fiz com outra matriz, uma posição não inicializada continha `3`. É imprevisível, e é o que causa o problema que comento na seção A6.

**Linha 12:** `return m;` devolve a struct **por cópia**. Todos os 80 008 bytes são copiados para quem chamou.

**Por que isso funciona e com vetor não funcionaria?** Porque a struct é um valor, como um `int`. Já um vetor decai para endereço, e devolver o endereço de `m` seria devolver o endereço de uma variável local que acabou de ser destruída.

## 3.2 `matriz_imprime`

```c
15 void matriz_imprime(Matriz m) {
16     for (int i = 0; i < m.linhas; i++) {
17         for (int j = 0; j < m.colunas; j++)
18             printf("%f ", m.elementos[i][j]);
19         printf("\n");
20     }
21 }
```

Repare em duas coisas de estilo que já apareceram na Unidade 3:

**1. As chaves.** O `for` externo **tem** chaves (linhas 16 e 20) porque seu corpo tem **dois comandos**: o `for` interno e o `printf("\n")`. O `for` interno **não tem** chaves porque seu corpo é um comando só.

**Se você tirasse as chaves do `for` externo**, o `printf("\n")` sairia de dentro dele e executaria **uma única vez, no fim** — todos os números apareceriam numa linha só. E a indentação continuaria parecendo certa. É o clássico bug da chave faltante.

**2. A posição do `printf("\n")`.** Ele está no `for` externo, depois do interno. Traduzindo: *"imprimi a linha inteira → agora quebro a linha"*. É essa posição que dá o formato de tabela.

**3. `m.linhas` e `m.colunas` no lugar de um parâmetro `n`.** Esta função não recebe tamanho nenhum — ele está dentro da struct. É o benefício prometido na seção A2.

> Nota: `%f` serve tanto para `float` quanto para `double` no `printf`. Por isso `%f` funciona aqui, embora `elementos` seja `double`. (No `scanf` seria diferente: lá `double` exige `%lf`.)

## 3.3 `matriz_adiciona`

```c
23 Matriz matriz_adiciona(Matriz m1, Matriz m2) {
24     Matriz m;
25     m.linhas = m1.linhas;
26     m.colunas = m1.colunas;
27     for (int i = 0; i < m1.linhas; i++)
28         for (int j = 0; j < m1.colunas; j++)
29             m.elementos[i][j] = m1.elementos[i][j] + m2.elementos[i][j];
30     return m;
31 }
```

**A matemática:** somar matrizes é somar **elemento a elemento**, na mesma posição.

```
┌ 1  2 ┐   ┌ 5  6 ┐   ┌ 1+5  2+6 ┐   ┌  6   8 ┐
│      │ + │      │ = │          │ = │        │
└ 3  4 ┘   └ 7  8 ┘   └ 3+7  4+8 ┘   └ 10  12 ┘
```

**Linhas 25–26:** o resultado tem as **mesmas dimensões** das parcelas. A função usa as de `m1`.

**Linha 29:** o coração. Para cada posição `(i,j)`, soma os dois valores correspondentes. Um único `for` duplo, uma única expressão. Custo: **O(linhas × colunas)** — cada elemento é tocado uma vez.

## 3.4 `matriz_multiplica` — a mais complexa

```c
32 Matriz matriz_multiplica(Matriz m1, Matriz m2) {
33     Matriz m;
34     m.linhas = m1.linhas;
35     m.colunas = m2.colunas;
36     for (int i = 0; i < m1.linhas; i++)
37         for (int j = 0; j < m2.colunas; j++) {
38             m.elementos[i][j] = 0;
39             for (int k = 0; k < m1.colunas; k++)
40                 m.elementos[i][j] += m1.elementos[i][k] * m2.elementos[k][j];
41         }
42     return m;
43 }
```

**A matemática:** o elemento `(i,j)` do produto é o **produto escalar da linha `i` de m1 com a coluna `j` de m2**.

```
                  coluna j de m2
                        ↓
  linha i de m1 →  [ ─────── ]   ⇒  m[i][j] = soma dos produtos
```

**Linhas 34–35 — leia com atenção, é onde as pessoas erram:**

```c
m.linhas  = m1.linhas;     /* do PRIMEIRO */
m.colunas = m2.colunas;    /* do SEGUNDO */
```

Regra: **(a×b) × (b×c) = (a×c)**. O resultado herda as linhas da primeira e as colunas da segunda. As dimensões "do meio" (b) precisam coincidir e desaparecem no resultado.

**Os três laços:**

| Laço | Variável | Percorre |
|---|---|---|
| externo (36) | `i` | as linhas do resultado |
| meio (37) | `j` | as colunas do resultado |
| interno (39) | `k` | os termos da soma |

**Linha 38 — `m.elementos[i][j] = 0;` NÃO É OPCIONAL.**

O `+=` da linha 40 significa "some ao que já está aí". Se você não zerar antes, o que "já está aí" é **lixo**, e o resultado inteiro fica corrompido. Pior: às vezes o lixo é zero e o programa "funciona" na sua máquina, falhando na do professor.

Note também que essa linha está **dentro** do `for` do `j` — ela zera uma posição por vez, imediatamente antes de acumular nela. Por isso o `for` do meio (linha 37) tem chaves: seu corpo tem dois comandos.

**Linha 40 — o índice `k` aparece nos dois operandos, em posições trocadas:**

```c
m1.elementos[i][k]  ×  m2.elementos[k][j]
             ↑ ↑                   ↑ ↑
        linha fixa,           coluna fixa,
        coluna varia          linha varia
```

É isso que implementa "linha de m1 vezes coluna de m2".

**Trace real da multiplicação.** Instrumentei o código e rodei com as matrizes do cliente:

```
m[0][0]: 1*5 + 2*7 = 19
m[0][1]: 1*6 + 2*8 = 22
m[1][0]: 3*5 + 4*7 = 43
m[1][1]: 3*6 + 4*8 = 50
```

Confira o primeiro: linha 0 de m1 é `[1, 2]`; coluna 0 de m2 é `[5, 7]`. Produto escalar: 1·5 + 2·7 = 5 + 14 = **19**. ✔

**Complexidade: O(n³)** para matrizes n×n. Três laços aninhados. Dobrar `n` multiplica o tempo por 8.

> Detalhe: a linha 43 está em branco antes do `}`. Cosmético, sem efeito.

## 3.5 `matriz_multiplica_escalar`

```c
46 Matriz matriz_multiplica_escalar(Matriz m, double escalar) {
47     Matriz r;
48     r.linhas = m.linhas;
49     r.colunas = m.colunas;
50     for (int i = 0; i < m.linhas; i++)
51         for (int j = 0; j < m.colunas; j++)
52             r.elementos[i][j] = m.elementos[i][j] * escalar;
53     return r;
54 }
```

A mais simples: multiplica **todo** elemento pelo mesmo número. Dimensões preservadas. Custo **O(linhas × colunas)**.

Note que a variável de resultado se chama `r`, não `m` — porque `m` já é o nome do parâmetro. Se ambas se chamassem `m`, a local faria sombra sobre o parâmetro e a função leria os próprios valores não inicializados. Um detalhe pequeno que evita um bug grande.

---

# A4. `cliente_matriz.c` — quem usa

```c
1  #include <stdio.h>
2  #include "matriz.h"
3
4  int main() {
5      double elementos1[MATRIZ_MAX][MATRIZ_MAX] = {{1, 2}, {3, 4}};
6      double elementos2[MATRIZ_MAX][MATRIZ_MAX] = {{5, 6}, {7, 8}};
7      Matriz m1 = matriz_nova(2, 2, elementos1);
8      Matriz m2 = matriz_nova(2, 2, elementos2);
9      Matriz m3 = matriz_adiciona(m1, m2);
10     Matriz m4 = matriz_multiplica(m1, m2);
11     Matriz m5 = matriz_multiplica_escalar(m1, 2);
```

**Linha 2:** o cliente inclui **só o `.h`**. Ele nunca vê `matriz.c`. Este é o ponto central do TAD.

**Linhas 5–6:** cria as matrizes cruas com os valores iniciais.

A sintaxe `= {{1, 2}, {3, 4}}` inicializa por linhas: a primeira chave interna é a linha 0, a segunda é a linha 1. **Todo o resto é automaticamente zerado** — quando você fornece pelo menos um inicializador, C zera o que sobra.

**Linhas 7–8:** converte as matrizes cruas em `Matriz`, informando que só 2×2 é usado.

**Linhas 9–11:** as operações. Leia essas três linhas e note como elas parecem **matemática**, não programação:

```
m3 = m1 + m2
m4 = m1 × m2
m5 = m1 × 2
```

Nenhum índice `i`, `j`, `k`. Nenhum laço. Nenhuma menção a `elementos`. **Isso é a abstração funcionando** — o cliente pensa em matrizes, não em laços aninhados.

Compare com o que a `main` teria que conter se não houvesse TAD: os três laços da multiplicação, os dois da soma, a inicialização em zero… tudo misturado com a lógica do programa.

```c
12     printf("Matriz 1:\n");
13     matriz_imprime(m1);
       ... (idem para m2, m3, m4, m5)
22     return 0;
23 }
```

Impressão dos resultados. Nada de especial.

## Saída real do programa

Compilei os três arquivos e executei:

```
Soma:                     Multiplicação:            Multiplicação por 2:
6.000000  8.000000        19.000000 22.000000       2.000000 4.000000
10.000000 12.000000       43.000000 50.000000       6.000000 8.000000
```

Confira à mão: 1+5=6 ✔, 2+6=8 ✔, 3+7=10 ✔, 4+8=12 ✔. E a multiplicação bate com o trace da seção A3.4. **O código está matematicamente correto.**

---

# A5. O que acontece na memória

## 5.1 Como uma `Matriz` está guardada

```
       ┌──────────────────────────────────────────────┐
       │ elementos[0][0..99]   800 bytes              │
       │ elementos[1][0..99]   800 bytes              │  80 000 bytes
       │ ...                                          │
       │ elementos[99][0..99]  800 bytes              │
       ├──────────────────────────────────────────────┤
       │ linhas      (int)       4 bytes              │
       │ colunas     (int)       4 bytes              │
       └──────────────────────────────────────────────┘
                    TOTAL: 80 008 bytes
```

Medi com `sizeof(Matriz)`: **80 008 bytes, ou 78,1 KB**. Uma matriz 2×2 e uma 100×100 ocupam **exatamente o mesmo espaço** — o tamanho da struct é fixo, decidido em tempo de compilação.

Os membros ficam em sequência na memória, na ordem em que foram declarados. E `elementos` internamente é guardado linha após linha (*row-major*), como toda matriz em C.

## 5.2 A propriedade que faz tudo funcionar: struct se copia

Este é o comportamento que diferencia struct de vetor, e é o que permite `m3 = matriz_adiciona(m1, m2)`. Eu comprovei:

```c
Matriz copia = m1;              /* atribuição de struct */
copia.elementos[0][0] = 999;    /* mexo na cópia */
```

Resultado:

```
copia.elementos[0][0] = 999
m1.elementos[0][0]    = 1     <- INTACTO
```

**São duas structs independentes.** Mexer numa não afeta a outra.

Compare com o que aconteceria com uma matriz crua:

| | `double M[100][100]` | `Matriz m` |
|---|---|---|
| `a = b` | ❌ não compila | ✅ **copia os 80 008 bytes** |
| passar para função | manda o **endereço** → função **modifica o original** | manda uma **cópia** → original intacto |
| devolver por `return` | ❌ impossível | ✅ possível |

**Por que essa diferença existe?** Porque o nome de um vetor "decai" para o endereço do primeiro elemento, enquanto o nome de uma struct é um valor completo — como um `int`. É essa única diferença que explica as três linhas da tabela.

## 5.3 Onde isso custa caro

A conveniência tem preço. Numa chamada `matriz_adiciona(m1, m2)`:

```
cópia de m1        78,1 KB
cópia de m2        78,1 KB
cópia do retorno   78,1 KB
──────────────────────────
TOTAL             234,4 KB copiados
```

…para somar duas matrizes 2×2, que precisam de **64 bytes** de dados úteis. Mais de 99,9% do trabalho é copiar posições que nunca serão lidas.

Isso não é defeito do professor — é a consequência inevitável de combinar "struct copia por valor" com "vetor de tamanho fixo grande dentro dela". A solução definitiva são **ponteiros** (`const Matriz *m` copia 8 bytes em vez de 78 KB) e **alocação dinâmica** (`malloc` reservaria exatamente `linhas × colunas × 8` bytes). É o assunto da próxima unidade, e essa conta é o melhor argumento que existe para aprendê-la.

---

# A6. ⚠️ A falha que você precisa conhecer

O código funciona **desde que você o use corretamente**. Ele não se defende de uso incorreto.

**Testei somar uma matriz 2×3 com uma 2×2** (matematicamente impossível) e **multiplicar uma 2×3 por uma 2×2** (também impossível — 3 colunas não casam com 2 linhas):

```
somando 2x3 com 2x2:         multiplicando 2x3 por 2x2:
2.000000  4.000000  6.000000     7.000000 10.000000
7.000000  9.000000 12.000000    19.000000 28.000000
```

**Nenhum erro. Nenhum aviso. Números plausíveis, todos sem significado.**

De onde vieram? De `matriz_nova` copiar só a região `linhas × colunas` (seção A3.1) — as posições fora dela contêm lixo, e as funções leram esse lixo.

**Por que isso acontece:** nenhuma das funções verifica se a operação faz sentido. `matriz_adiciona` assume que as dimensões batem; `matriz_multiplica` assume que `m1.colunas == m2.linhas`.

**A correção é curta.** Basta uma linha no começo de cada função:

```c
Matriz matriz_adiciona(Matriz m1, Matriz m2) {
    if (m1.linhas != m2.linhas || m1.colunas != m2.colunas)
        return matriz_invalida();       /* uma Matriz com linhas = 0 */
    ...
}

Matriz matriz_multiplica(Matriz m1, Matriz m2) {
    if (m1.colunas != m2.linhas)        /* a regra matemática */
        return matriz_invalida();
    ...
}
```

**O truque de sinalizar erro sem ponteiros:** como uma matriz de verdade sempre tem pelo menos 1 linha, `linhas == 0` é um valor **impossível** — perfeito para significar "deu errado". É a mesma ideia do `'\0'` marcando o fim de uma string e do `return 0` em `eh_primo`: reservar um valor impossível para dizer algo especial.

Com isso, os três casos inválidos passam a responder `<matriz invalida>` em vez de números falsos.

---

# A7. Como compilar

Três arquivos exigem compilação em duas fases:

```
gcc -std=c99 -Wall -Werror -Wvla -g -c matriz.c           → matriz.o
gcc -std=c99 -Wall -Werror -Wvla -g -c cliente_matriz.c   → cliente_matriz.o
gcc matriz.o cliente_matriz.o -lm -o cliente              → executável
```

**A flag nova é `-c`: "compile, mas não linke".** Ela gera um `.o` — código de máquina com "buracos" onde há chamadas a funções de outros arquivos. A terceira linha é a **linkagem**: junta os `.o` e preenche os buracos.

Isso explica dois tipos diferentes de erro que você vai encontrar:

| Erro | Quando aparece | Causa típica |
|---|---|---|
| **de compilação** | fase `-c` | sintaxe errada, tipo errado, função não declarada no `.h` |
| **de linkagem** (`undefined reference`) | fase final | função **declarada** no `.h` mas **não implementada** no `.c`, ou você esqueceu de incluir o `.o` |

Aquele "prato no cardápio que a cozinha não sabe fazer" é literalmente o erro de linkagem.

---

# A8. ✅ O que eu preciso saber deste código

- Explicar o papel de cada um dos três arquivos e por que cliente e implementação não se enxergam.
- Explicar o `#ifndef`/`#define`/`#endif` e o problema que ele resolve.
- **Justificar por que `linhas` e `colunas` ficam dentro da struct** (as dimensões viajam com os dados).
- Acessar membros com `.` e saber que `Matriz` é o apelido dado pelo `typedef`.
- **Explicar por que as funções podem devolver `Matriz` mas não poderiam devolver uma matriz crua.**
- Explicar por que `m.linhas = m1.linhas; m.colunas = m2.colunas;` na multiplicação.
- **Explicar por que `m.elementos[i][j] = 0;` antes do `+=` é obrigatório.**
- Fazer o trace de `m1 × m2` à mão e chegar em 19, 22, 43, 50.
- Saber que struct **copia** com `=`, ao contrário de vetor.
- **Apontar que faltam verificações de dimensão** e escrever a correção.
- Distinguir erro de compilação de erro de linkagem.
