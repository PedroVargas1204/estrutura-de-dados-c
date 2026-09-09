#include "matriz.h"
#include <stdio.h>
#include <math.h>
#define EPS 1e-9

/* Matriz inválida: linhas = 0 é um valor impossível para uma matriz real,
 * então usamos isso para sinalizar erro sem ponteiros e sem parâmetro de
 * saída. static porque é um detalhe interno: o cliente não deve chamar. */
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

Matriz matriz_identidade(int n) {
    Matriz m = matriz_zeros(n, n);
    if (!matriz_valida(m)) return m;
    for (int i = 0; i < n; i++)
        m.elementos[i][i] = 1.0;
    return m;
}

Matriz matriz_le(int linhas, int colunas) {
    Matriz m = matriz_zeros(linhas, colunas);
    if (!matriz_valida(m)) return m;
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            scanf("%lf", &m.elementos[i][j]);
    return m;
}

void matriz_imprime(Matriz m) {
    if (!matriz_valida(m)) {
        printf("<matriz invalida>\n");
        return;
    }
    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++)
            printf("%6.2f ", m.elementos[i][j]);
        printf("\n");
    }
}

int matriz_iguais(Matriz a, Matriz b) {
    if (a.linhas != b.linhas || a.colunas != b.colunas) return 0;
    for (int i = 0; i < a.linhas; i++)
        for (int j = 0; j < a.colunas; j++)
            if (fabs(a.elementos[i][j] - b.elementos[i][j]) > EPS)
                return 0;                            /* ← fabs, não == */
    return 1;
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

Matriz matriz_subtrai(Matriz a, Matriz b) {
    return matriz_adiciona(a, matriz_multiplica_escalar(b, -1.0));
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

Matriz matriz_multiplica_escalar(Matriz m, double escalar) {
    if (!matriz_valida(m)) return matriz_invalida();
    Matriz r = matriz_zeros(m.linhas, m.colunas);
    for (int i = 0; i < m.linhas; i++)
        for (int j = 0; j < m.colunas; j++)
            r.elementos[i][j] = m.elementos[i][j] * escalar;
    return r;
}

Matriz matriz_transposta(Matriz m) {
    if (!matriz_valida(m)) return matriz_invalida();
    Matriz t = matriz_zeros(m.colunas, m.linhas);    /* dimensões TROCADAS */
    for (int i = 0; i < m.linhas; i++)
        for (int j = 0; j < m.colunas; j++)
            t.elementos[j][i] = m.elementos[i][j];   /* índices TROCADOS */
    return t;
}
