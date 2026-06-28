#ifndef _VARIAVEIS_H
#define _VARIAVEIS_H

#define T_STR   100
#define T_LSTR  10000
#define T_SNS   30
#define T_STRS  10
#define FIM     0

typedef char string[T_STR];
typedef char string_l[T_LSTR];

typedef struct sensor {
    string nome_s;
    string tipo_s;
    int faixa_m;
    int faixa_M;
    struct sensor *proximo;
} sensor_t;

typedef struct relatorio {
    sensor_t sensor;
    int horario_1;
    int leitura_1;
    int horario_2;
    int leitura_2;
    struct relatorio *proximo;
} relatorio_t;

typedef struct setores {
    string lugar;
    string_l descricao;
    int qtd_sensores_por_setor;
    relatorio_t *relatorios;
    struct setores *proximo;
} setores_t;

#endif