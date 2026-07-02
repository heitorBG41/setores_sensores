#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "variaveis.h"
#include "utilidade.h"
#include "menu.h"


sensor_t* criar_sensor(void);
setores_t* criar_setores(sensor_t *lista_sensores);

void inserir_na_lista_sensores(sensor_t **lista, sensor_t *novo);
void inserir_na_lista_setores(setores_t **lista_setores, setores_t *novo);
void inserir_relatorio(setores_t *setor, sensor_t *sensor, int h1, int l1, int h2, int l2);

void listar_sensor(sensor_t *lista);
void listar_setores(setores_t *lista);

void pesquisar_sensores(sensor_t *lista);
void pesquisar_setores(setores_t *lista);

void selecao_numero_sensores_nomes(setores_t **novo, sensor_t *lista_sensores);

setores_t* procurar_setor(setores_t *lista, string str);
sensor_t* procurar_sensor(setores_t *lista, string str);

void excluir_lista(setores_t **lista, sensor_t *sensor_excluido, setores_t *setor_achado);
void execucao_lista(setores_t *lista);

void relatorio_de_sensores_geral(sensor_t *lista_sensores, setores_t *lista_setores);
void relatorio_de_sensores_por_tipo(sensor_t *lista_sensores, setores_t *lista_setores);
void relatorio_de_setores(setores_t *lista_setores);
void relatorio_leituras_por_local(setores_t *lista_setores);
void relatorio_leituras_todos_locais(setores_t *lista_setores);
void relatorio_variacao_por_setor_sensor(setores_t *lista_setores);
void relatorio_media_por_sensor(sensor_t *lista_sensores, setores_t *lista_setores);

sensor_t* descobrir_ultimo_sensor(sensor_t *lista);
setores_t* descobrir_ultimo_setor(setores_t *lista);

void exportar_arquivo_binario(sensor_t *lista_sensores, setores_t *lista_setores, char *nome_arq_sensores, char *nome_arq_setores);
void exportar_arquivo_para_csv(sensor_t *lista_sensores, setores_t *lista_setores, char *nome_arq_sensores, char *nome_arq_setores);
void exportar_arquivo_html(sensor_t *lista_sensores, setores_t *lista_setores, char *nome_arq_sensores, char *nome_arq_setores);
void importar_arq(sensor_t **lista_sensores, setores_t **lista_setores, char *nome_arq_sensores, char *nome_arq_setores);

int main() {
    int opcao, opcao_a, opcao_b, opcao_c;
    sensor_t *sensores_todos = NULL, *novo_sensor = NULL;
    setores_t *setores_todos = NULL, *novo_setor = NULL;

    srand(time(NULL));
    limpar_tela();

    do {
        opcao = menu_principal();

        switch (opcao) {
            case 1:
                novo_sensor = criar_sensor();
                inserir_na_lista_sensores(&sensores_todos, novo_sensor);
                limpar_tela();
                break;
            case 2:
                novo_setor = criar_setores(sensores_todos);
                inserir_na_lista_setores(&setores_todos, novo_setor);
                limpar_tela();
                break;
            case 3:
                limpar_tela();
                listar_sensor(sensores_todos);
                botao_pause();
                limpar_tela();
                break;
            case 4:
                limpar_tela();
                listar_setores(setores_todos);
                botao_pause();
                limpar_tela();
                break;
            case 5:
                do {
                    opcao_a = menu_pesquisar();
                    switch (opcao_a) {
                        case 1:
                            pesquisar_sensores(sensores_todos);
                            break;
                        case 2:
                            pesquisar_setores(setores_todos);
                            break;
                    }
                } while (opcao_a != FIM);
                break;
            case 6:
                do {
                    opcao_b = menu_relatorios();
                    switch (opcao_b) {
                        case 1:
                            relatorio_de_sensores_geral(sensores_todos, setores_todos);
                            botao_pause();
                            limpar_tela();
                            break;
                        case 2:
                            relatorio_de_sensores_por_tipo(sensores_todos, setores_todos);
                            botao_pause();
                            limpar_tela();
                            break;
                        case 3:
                            relatorio_de_setores(setores_todos);
                            botao_pause();
                            limpar_tela();
                            break;
                        case 4:
                            limpar_tela();
                            relatorio_leituras_por_local(setores_todos);
                            botao_pause();
                            limpar_tela();
                            break;
                        case 5:
                            limpar_tela();
                            relatorio_leituras_todos_locais(setores_todos);
                            botao_pause();
                            limpar_tela();
                            break;
                        case 6:
                            limpar_tela();
                            relatorio_variacao_por_setor_sensor(setores_todos);
                            botao_pause();
                            limpar_tela();
                            break;
                        case 7:
                            limpar_tela();
                            relatorio_media_por_sensor(sensores_todos, setores_todos);
                            botao_pause();
                            limpar_tela();
                            break;
                        case 0:
                            break;
                        default:
                            printf("programa nao existente");
                    }
                } while (opcao_b != FIM);
                break;
            case 7: execucao_lista(setores_todos);
                    break;
            case 8:
                limpar_tela();
                do {
                    opcao_c = menu_arquivos();
                    switch (opcao_c) {
                        case 1:
                            exportar_arquivo_binario(sensores_todos, setores_todos, "arq_sensores.bin", "arq_setores.bin");
                            break;
                        case 2:
                            exportar_arquivo_para_csv(sensores_todos, setores_todos, "arq_sensores.csv", "arq_setores.csv");
                            break;
                        case 3:
                            exportar_arquivo_html(sensores_todos, setores_todos, "arq_sensores.html", "arq_setores.html");
                            break;
                        case 4:
                            importar_arq(&sensores_todos, &setores_todos, "arq_sensores.bin", "arq_setores.bin");
                            break;
                    }
                } while (opcao_c != FIM);
                break;
        }
    } while (opcao != FIM);

    return 0;
}

sensor_t *criar_sensor(void) 
{
    sensor_t *novo = NULL;
    novo = (sensor_t*)malloc(sizeof(sensor_t));

    printf("digite o nome do sensor\n");
    fgets(novo->nome_s, T_STR, stdin);
    retirar_enter(novo->nome_s);

    printf("digite o nome do tipo de identificao\n");
    fgets(novo->tipo_s, T_STR, stdin);
    retirar_enter(novo->tipo_s);


    printf("digite o parametro minimo\n");
    scanf("%i", &novo->faixa_m);
    getchar();

    printf("digite o parametro maximo\n");
    scanf("%i", &novo->faixa_M);
    getchar();

    novo->proximo = NULL;
    return novo;
}

void inserir_relatorio(setores_t *setor, sensor_t *sensor, int h1, int l1, int h2, int l2) 
{
    relatorio_t *novo = (relatorio_t*)malloc(sizeof(relatorio_t));
    novo->sensor = *sensor;
    novo->horario_1 = h1;
    novo->leitura_1 = l1;
    novo->horario_2 = h2;
    novo->leitura_2 = l2;
    novo->proximo = NULL;

    if (setor->relatorios == NULL) {
        setor->relatorios = novo;
    } else {
        relatorio_t *aux = setor->relatorios;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
}

setores_t *criar_setores(sensor_t *lista_sensores) 
{
    setores_t *novo = NULL;
    novo = (setores_t*)malloc(sizeof(setores_t));
    novo->relatorios = NULL;

    printf("digite o nome do setor que deseja adicionar: ");
    fgets(novo->lugar, T_STR, stdin);
    retirar_enter(novo->lugar);

    printf("digite uma breve descricao do setor: ");
    fgets(novo->descricao, T_LSTR, stdin);
    retirar_enter(novo->descricao);

    do {
        printf("digite o numero sensores voce quer adicionar (1 a 3): ");
        scanf("%i", &novo->qtd_sensores_por_setor);
        getchar();

        if (novo->qtd_sensores_por_setor > 3 || novo->qtd_sensores_por_setor < 1)
            printf("numero invalido\n");
    } while (novo->qtd_sensores_por_setor > 3 || novo->qtd_sensores_por_setor < 1);

    selecao_numero_sensores_nomes(&novo, lista_sensores);

    novo->proximo = NULL;
    return novo;
}

void selecao_numero_sensores_nomes(setores_t **novo, sensor_t *lista_sensores) 
{
    int qtd_sensores_adicionados = 0, j = 0;
    string str;

    do {
        sensor_t *aux = lista_sensores;

        printf("digite quais sensores voce quer adicionar(nome): ");
        fgets(str, T_STR, stdin);
        retirar_enter(str);

        for (aux; aux != NULL; aux = aux->proximo) {
            if (strcmp(str, aux->nome_s) == 0) {
                sensor_t *sensor_copia = (sensor_t*)malloc(sizeof(sensor_t));
                *sensor_copia = *aux;
                sensor_copia->proximo = NULL;

                int h1, l1, h2, l2;
                printf("horario da primeira leitura (%s): ", aux->nome_s);
                scanf("%i", &h1);
                getchar();

                printf("horario da segunda leitura (%s): ", aux->nome_s);
                scanf("%i", &h2);
                getchar();

                l1 = (rand() % (aux->faixa_M - aux->faixa_m + 1)) + aux->faixa_m;
                l2 = (rand() % (aux->faixa_M - aux->faixa_m + 1)) + aux->faixa_m;

                inserir_relatorio(*novo, sensor_copia, h1, l1, h2, l2);
                qtd_sensores_adicionados++;
            }
        }
        if (qtd_sensores_adicionados == j)
            printf("sensor invalido\n");
        if (qtd_sensores_adicionados > j)
            j++;

    } while (qtd_sensores_adicionados != (*novo)->qtd_sensores_por_setor);
}

void inserir_na_lista_sensores(sensor_t **lista, sensor_t *novo) 
{
    if (*lista == NULL) {
        *lista = novo;
    } else {
        sensor_t *aux = descobrir_ultimo_sensor(*lista);
        aux->proximo = novo;
    }
}

sensor_t* descobrir_ultimo_sensor(sensor_t *lista) 
{
    if(lista->proximo == NULL){
        return lista;
    }
  
    //função recursiva
    return descobrir_ultimo_sensor(lista->proximo);

}

void inserir_na_lista_setores(setores_t **lista, setores_t *novo) 
{
    if (*lista == NULL) {
        *lista = novo;
    } else {
        setores_t *aux = descobrir_ultimo_setor(*lista);
        aux->proximo = novo;
    }
}

setores_t* descobrir_ultimo_setor(setores_t *lista) 
{
    if(lista->proximo == NULL){
        return lista;
    }
    
    descobrir_ultimo_setor(lista->proximo);
}

void listar_sensor(sensor_t *lista) 
{
    if (lista == NULL)
        printf("nenhum sensor ativo\n");
    else {
        for (lista; lista != NULL; lista = lista->proximo) {
            printf("--------------------------------\n");
            printf("nome do sensor: %s\n", lista->nome_s);
            printf("nome do tipo  : %s\n", lista->tipo_s);
            printf("faixa minima  : %i\n", lista->faixa_m);
            printf("faixa maxima  : %i\n", lista->faixa_M);
            printf("--------------------------------\n");
        }
    }
}

void listar_setores(setores_t *lista) 
{
    if (lista == NULL)
        printf("nenhum setor criado\n");
    else {
        for (lista; lista != NULL; lista = lista->proximo) {
            printf("--------------------------------\n");
            printf("nome do setor.......: %s\n", lista->lugar);
            printf("descricao do setor..: %s\n", lista->descricao);

            relatorio_t *aux = lista->relatorios;
            while (aux != NULL) {
                printf("Sensor: %s\n", aux->sensor.nome_s);
                printf("horario 1: %i, leitura 1: %i\n", aux->horario_1, aux->leitura_1);
                printf("horario 2: %i, leitura 2: %i\n", aux->horario_2, aux->leitura_2);
                aux = aux->proximo;
            }
            printf("--------------------------------\n");
        }
    }
}



void pesquisar_sensores(sensor_t *lista) 
{
    string str;
    printf("digite o tipo de sensor: ");
    fgets(str, T_STR, stdin);
    retirar_enter(str);

    for (lista; lista != NULL; lista = lista->proximo) {
        if (strcmp(str, lista->tipo_s) == 0) {
            printf("--------------------------------\n");
            printf("nome do sensor: %s\n", lista->nome_s);
            printf("nome do tipo  : %s\n", lista->tipo_s);
            printf("faixa minima  : %i\n", lista->faixa_m);
            printf("faixa maxima  : %i\n", lista->faixa_M);
            printf("--------------------------------\n");
        }
    }
}

void pesquisar_setores(setores_t *lista) 
{
    string_l str;
    printf("digite a descricao do setor: ");
    fgets(str, T_LSTR, stdin);
    retirar_enter(str);

    for (lista; lista != NULL; lista = lista->proximo) {
        if (strcmp(str, lista->descricao) == 0) {
            printf("--------------------------------\n");
            printf("nome do setor.......: %s\n", lista->lugar);
            printf("descricao do setor..: %s\n", lista->descricao);

            relatorio_t *aux = lista->relatorios;
            while (aux != NULL) {
                printf("Sensor: %s\n", aux->sensor.nome_s);
                printf("horario 1: %i, leitura 1: %i\n", aux->horario_1, aux->leitura_1);
                printf("horario 2: %i, leitura 2: %i\n", aux->horario_2, aux->leitura_2);
                aux = aux->proximo;
            }
            printf("--------------------------------\n");
        }
    }
}

void relatorio_de_sensores_geral(sensor_t *lista_sensores, setores_t *lista_setores) 
{
    if (lista_sensores == NULL) {
        printf("Nenhum sensor ativo\n");
        return;
    }

    for (sensor_t *s = lista_sensores; s != NULL; s = s->proximo) {
        printf("--------------------------------\n");
        printf("nome do sensor: %s\n", s->nome_s);
        printf("nome do tipo  : %s\n", s->tipo_s);
        printf("faixa minima  : %i\n", s->faixa_m);
        printf("faixa maxima  : %i\n", s->faixa_M);

        printf("Setores onde este sensor aparece:\n");
        for (setores_t *set = lista_setores; set != NULL; set = set->proximo) {
            relatorio_t *aux = set->relatorios;
            while (aux != NULL) {
                if (strcmp(aux->sensor.nome_s, s->nome_s) == 0) {
                    printf("  Setor: %s\n", set->lugar);
                    printf("    Leitura 1: %i (horario %i)\n", aux->leitura_1, aux->horario_1);
                    printf("    Leitura 2: %i (horario %i)\n", aux->leitura_2, aux->horario_2);
                }
                aux = aux->proximo;
            }
        }
        printf("--------------------------------\n");
    }
}

void relatorio_de_sensores_por_tipo(sensor_t *lista_sensores, setores_t *lista_setores) 
{
    if (lista_sensores == NULL) {
        printf("Nenhum sensor ativo\n");
        return;
    }

    char tipos[T_SNS][T_STR];
    int qtd_tipos = 0;

    for (sensor_t *s = lista_sensores; s != NULL; s = s->proximo) {
        int encontrado = 0;
        for (int i = 0; i < qtd_tipos; i++) {
            if (strcmp(tipos[i], s->tipo_s) == 0) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(tipos[qtd_tipos], s->tipo_s);
            qtd_tipos++;
        }
    }

    for (int i = 0; i < qtd_tipos; i++) {
        printf("\n========== TIPO: %s ==========\n", tipos[i]);
        for (sensor_t *s = lista_sensores; s != NULL; s = s->proximo) {
            if (strcmp(s->tipo_s, tipos[i]) == 0) {
                printf("--------------------------------\n");
                printf("nome do sensor: %s\n", s->nome_s);
                printf("faixa minima  : %i\n", s->faixa_m);
                printf("faixa maxima  : %i\n", s->faixa_M);

                for (setores_t *set = lista_setores; set != NULL; set = set->proximo) {
                    relatorio_t *aux = set->relatorios;
                    while (aux != NULL) {
                        if (strcmp(aux->sensor.nome_s, s->nome_s) == 0) {
                            printf("  Setor: %s\n", set->lugar);
                            printf("    Leitura 1: %i (horario %i)\n", aux->leitura_1, aux->horario_1);
                            printf("    Leitura 2: %i (horario %i)\n", aux->leitura_2, aux->horario_2);
                        }
                        aux = aux->proximo;
                    }
                }
            }
        }
    }
}

void relatorio_de_setores(setores_t *lista_setores) 
{
    listar_setores(lista_setores);
}

void relatorio_leituras_por_local(setores_t *lista_setores) 
{
    string nome_setor;
    printf("Digite o nome do setor: ");
    fgets(nome_setor, T_STR, stdin);
    retirar_enter(nome_setor);

    setores_t *setor = procurar_setor(lista_setores, nome_setor);
    if (setor == NULL) {
        printf("Setor nao encontrado\n");
        return;
    }

    printf("\nSETOR: %s\n", setor->lugar);
    relatorio_t *aux = setor->relatorios;
    while (aux != NULL) {
        printf("\nSensor: %s\n", aux->sensor.nome_s);
        printf("Horario %i -> Leitura %i\n", aux->horario_1, aux->leitura_1);
        printf("Horario %i -> Leitura %i\n", aux->horario_2, aux->leitura_2);
        aux = aux->proximo;
    }
}

void relatorio_leituras_todos_locais(setores_t *lista_setores) 
{
    if (lista_setores == NULL) {
        printf("Nenhum setor cadastrado\n");
        return;
    }

    for (setores_t *set = lista_setores; set != NULL; set = set->proximo) {
        printf("\n--------------------------------\n");
        printf("SETOR: %s\n", set->lugar);

        relatorio_t *aux = set->relatorios;
        while (aux != NULL) {
            printf("\nSensor: %s\n", aux->sensor.nome_s);
            printf("Horario %i -> Leitura %i\n", aux->horario_1, aux->leitura_1);
            printf("Horario %i -> Leitura %i\n", aux->horario_2, aux->leitura_2);
            aux = aux->proximo;
        }
    }
}

void relatorio_variacao_por_setor_sensor(setores_t *lista_setores) 
{
    if (lista_setores == NULL) {
        printf("Nenhum setor cadastrado\n");
        return;
    }

    for (setores_t *set = lista_setores; set != NULL; set = set->proximo) {
        printf("\n--------------------------------\n");
        printf("SETOR: %s\n", set->lugar);

        relatorio_t *aux = set->relatorios;
        while (aux != NULL) {
            int variacao = aux->leitura_2 - aux->leitura_1;
            printf("\nSensor: %s\n", aux->sensor.nome_s);
            printf("Leitura 1: %i\n", aux->leitura_1);
            printf("Leitura 2: %i\n", aux->leitura_2);
            printf("Variacao : %i\n", variacao);
            aux = aux->proximo;
        }
    }
}

void relatorio_media_por_sensor(sensor_t *lista_sensores, setores_t *lista_setores) 
{
    if (lista_sensores == NULL) {
        printf("Nenhum sensor cadastrado\n");
        return;
    }

    for (sensor_t *s = lista_sensores; s != NULL; s = s->proximo) {
        int soma = 0;
        int quantidade = 0;

        for (setores_t *set = lista_setores; set != NULL; set = set->proximo) {
            relatorio_t *aux = set->relatorios;
            while (aux != NULL) {
                if (strcmp(aux->sensor.nome_s, s->nome_s) == 0) {
                    soma += aux->leitura_1;
                    soma += aux->leitura_2;
                    quantidade += 2;
                }
                aux = aux->proximo;
            }
        }

        if (quantidade > 0) {
            float media = (float)soma / quantidade;
            printf("--------------------------------\n");
            printf("Sensor: %s\n", s->nome_s);
            printf("Media : %.2f\n", media);
            printf("--------------------------------\n");
        }
    }
}

setores_t* procurar_setor(setores_t *lista, string str) 
{
    for (lista; lista != NULL; lista = lista->proximo) {
        if (strcmp(str, lista->lugar) == 0)
            return lista;
    }
    return NULL;
}

sensor_t* procurar_sensor(setores_t *lista, string str) 
{
    relatorio_t *aux = lista->relatorios;
    while (aux != NULL) {
        if (strcmp(str, aux->sensor.nome_s) == 0) {
            return &(aux->sensor);
        }
        aux = aux->proximo;
    }
    return NULL;
}

void execucao_lista(setores_t *lista)
{
    setores_t *achar_setor = NULL;
    sensor_t *achar_sensor = NULL;
    string nome_setor, nome_sensor;
    char checagem_exclusao;

    printf("digite o nome do setor que quer remover o sensor: ");
    fgets(nome_setor, T_STR, stdin);
    retirar_enter(nome_setor);

    achar_setor = procurar_setor(lista, nome_setor);

    if (achar_setor == NULL)
        printf("setor nao encontrado\n");
    else {
        printf("digite o nome do sensor que se quer excluir: ");
        fgets(nome_sensor, T_STR, stdin);
        retirar_enter(nome_sensor);

        achar_sensor = procurar_sensor(achar_setor, nome_sensor);

        if (achar_sensor == NULL) printf("sensor nao achado\n");
        else {
            printf("voce deseja excluir o sensor %s do setor %s?(S/N): ", achar_sensor->nome_s, achar_setor->lugar);
            scanf("%c", &checagem_exclusao);
            getchar();
            if (checagem_exclusao == 's' || checagem_exclusao == 'S') {
                excluir_lista(&lista, achar_sensor, achar_setor);
                printf("sensor excluido do setor com sucesso\n");
                botao_pause();
                limpar_tela();
            }
        }
    }
}

void excluir_lista(setores_t **lista, sensor_t *sensor_excluido, setores_t *setor_achado) 
{
    for (setores_t *set = *lista; set != NULL; set = set->proximo) {
        if (!strcmp(setor_achado->lugar, set->lugar)) {
            relatorio_t *atual = set->relatorios;
            relatorio_t *anterior = NULL;

            while (atual != NULL) {
                if (!strcmp(atual->sensor.nome_s, sensor_excluido->nome_s)) {
                    if (anterior == NULL) {
                        set->relatorios = atual->proximo;
                    } else {
                        anterior->proximo = atual->proximo;
                    }
                    free(atual);
                    set->qtd_sensores_por_setor--;
                    return;
                }
                anterior = atual;
                atual = atual->proximo;
            }
        }
    }
}



void exportar_arquivo_binario(sensor_t *lista_sensores, setores_t *lista_setores, char *nome_arq_sensores, char *nome_arq_setores) 
{
    
    FILE *fp = fopen(nome_arq_sensores, "wb");
    
    while (lista_sensores) {
        fwrite(lista_sensores, sizeof(sensor_t), 1, fp);
        lista_sensores = lista_sensores->proximo;
    }
    fclose(fp);

    fp = fopen(nome_arq_setores, "wb");
    while (lista_setores) {
        fwrite(lista_setores, sizeof(setores_t), 1, fp);

        relatorio_t *aux = lista_setores->relatorios;
        
        while (aux != NULL) {
            fwrite(&(aux->sensor), sizeof(sensor_t), 1, fp);
            fwrite(&(aux->horario_1), sizeof(int), 1, fp);
            fwrite(&(aux->leitura_1), sizeof(int), 1, fp);
            fwrite(&(aux->horario_2), sizeof(int), 1, fp);
            fwrite(&(aux->leitura_2), sizeof(int), 1, fp);
            aux = aux->proximo;
        }

        lista_setores = lista_setores->proximo;
    }
    fclose(fp);
}

void exportar_arquivo_para_csv(sensor_t *lista_sensores, setores_t *lista_setores, char *nome_arq_sensores, char *nome_arq_setores) 
{
    FILE *fp = fopen(nome_arq_sensores, "w");
    fprintf(fp, "nome_sensor;tipo_sensor;faixa_minima;faixa_maxima\n");
    while (lista_sensores) {
        fprintf(fp, "%s;%s;%i;%i\n", lista_sensores->nome_s, lista_sensores->tipo_s,
                lista_sensores->faixa_m, lista_sensores->faixa_M);
        lista_sensores = lista_sensores->proximo;
    }
    fclose(fp);

    fp = fopen(nome_arq_setores, "w");
    fprintf(fp, "setor;descricao;sensor;horario1;leitura1;horario2;leitura2\n");
    while (lista_setores) {
        relatorio_t *aux = lista_setores->relatorios;
        while (aux != NULL) {
            fprintf(fp, "%s;%s;%s;%i;%i;%i;%i\n", lista_setores->lugar, lista_setores->descricao,
                    aux->sensor.nome_s, aux->horario_1, aux->leitura_1, aux->horario_2, aux->leitura_2);
            aux = aux->proximo;
        }
        lista_setores = lista_setores->proximo;
    }
    fclose(fp);
}

void exportar_arquivo_html(sensor_t *lista_sensores, setores_t *lista_setores, char *nome_arq_sensores, char *nome_arq_setores) 
{
    FILE *fp = fopen(nome_arq_sensores, "w");
    fprintf(fp, "<html><body>\n");
    fprintf(fp, "<h1>Sensores</h1>\n");
    fprintf(fp, "<table border='1'>\n");
    fprintf(fp, "<tr><th>Nome</th><th>Tipo</th><th>Faixa Minima</th><th>Faixa Maxima</th></tr>\n");

    while (lista_sensores) {
        fprintf(fp, "<tr>");
        fprintf(fp, "<td>%s</td>", lista_sensores->nome_s);
        fprintf(fp, "<td>%s</td>", lista_sensores->tipo_s);
        fprintf(fp, "<td>%i</td>", lista_sensores->faixa_m);
        fprintf(fp, "<td>%i</td>", lista_sensores->faixa_M);
        fprintf(fp, "</tr>\n");
        lista_sensores = lista_sensores->proximo;
    }
    fprintf(fp, "</table>\n");

    fprintf(fp, "<h1>Setores</h1>\n");
    fprintf(fp, "<table border='1'>\n");
    fprintf(fp, "<tr><th>Setor</th><th>Descricao</th><th>Sensor</th><th>Horario1</th><th>Leitura1</th><th>Horario2</th><th>Leitura2</th>\n");
   
    while (lista_setores) {
        relatorio_t *aux = lista_setores->relatorios;
        while (aux != NULL) {
            fprintf(fp, "<tr>");
            fprintf(fp, "<td>%s</td>", lista_setores->lugar);
            fprintf(fp, "<td>%s</td>", lista_setores->descricao);
            fprintf(fp, "<td>%s</td>", aux->sensor.nome_s);
            fprintf(fp, "<td>%i</td>", aux->horario_1);
            fprintf(fp, "<td>%i</td>", aux->leitura_1);
            fprintf(fp, "<td>%i</td>", aux->horario_2);
            fprintf(fp, "<td>%i</td>", aux->leitura_2);
            fprintf(fp, "</tr>\n");
            aux = aux->proximo;
        }
        lista_setores = lista_setores->proximo;
    }
    fprintf(fp, "</table>\n");
    fprintf(fp, "</body></html>\n");
    fclose(fp);
}

void importar_arq(sensor_t **lista_sensores, setores_t **lista_setores, char *nome_arq_sensores, char *nome_arq_setores) 
{
    FILE *fp = fopen(nome_arq_sensores, "rb");
    if (fp == NULL) {
        printf("Arquivo de sensores nao encontrado\n");
        return;
    }

    sensor_t *novo = NULL;
    
    while (!feof(fp)) {
        novo = (sensor_t*)malloc(sizeof(sensor_t));
        
        fread(novo, sizeof(sensor_t), 1, fp);
        novo->proximo = NULL;
        
        if(!feof(fp)){
            inserir_na_lista_sensores(lista_sensores, novo);
        }
        else{
            free(novo);
        }

    }
    fclose(fp);
    //primeira parte

    FILE *fp1 = fopen(nome_arq_setores, "rb");
    if (fp1 == NULL) {
        printf("Arquivo de setores nao encontrado\n");
        return;
    }

    setores_t *novo_setor = NULL;
    while (!feof(fp1)) {
        
        novo_setor = (setores_t*)malloc(sizeof(setores_t));
        
        fread(novo_setor, sizeof(setores_t), 1, fp1);

        if(!feof(fp1)){
            novo_setor->relatorios = NULL;
        }
        else{
            free(novo_setor);
            fclose(fp1);
            return;
        }

        for (int i = 0; i < novo_setor->qtd_sensores_por_setor; i++) {
            relatorio_t *novo_rel = (relatorio_t*)malloc(sizeof(relatorio_t));
            fread(&(novo_rel->sensor), sizeof(sensor_t), 1, fp1);
            fread(&(novo_rel->horario_1), sizeof(int), 1, fp1);
            fread(&(novo_rel->leitura_1), sizeof(int), 1, fp1);
            fread(&(novo_rel->horario_2), sizeof(int), 1, fp1);
            fread(&(novo_rel->leitura_2), sizeof(int), 1, fp1);
            novo_rel->proximo = NULL;

            if (novo_setor->relatorios == NULL) {
                novo_setor->relatorios = novo_rel;
            } 
            
            else {
                relatorio_t *aux = novo_setor->relatorios;
                while (aux->proximo != NULL) {
                    aux = aux->proximo;
                }
                aux->proximo = novo_rel;
            }
        }

        novo_setor->proximo = NULL;
        inserir_na_lista_setores(lista_setores, novo_setor);
    }
    fclose(fp1);
}