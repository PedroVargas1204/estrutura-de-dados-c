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
