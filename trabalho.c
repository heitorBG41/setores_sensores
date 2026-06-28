/*
    o que fazer de novidade
    -remover variaveis globais (não retirar pra não dar erro de compliaçao, remova aos poucos)
    -arrumar o calculo ali em baixo(parte concluida);
    -funcao de excluir algum objeto(parte concluida);
    -a possibilidade de novas leituras em um setor(o anderson falou e acho que ele vai cobrar)
    -colocar para o html, csv, e mais arquivo binario.(sensores deram certo menos os setores, me de mais tempo e eu termino isso dai);
    -colocar os tipos

    
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define T_STR   100
#define T_LSTR  10000   // esse daqui e para a descricao do setor
#define T_SNS   30      // quantidade de sensores;     
#define T_STRS  10
#define FIM     0

typedef char string[T_STR];
typedef char string_l[T_LSTR];

typedef struct sensor{
    string nome_s;
    string tipo_s;
    int id_tipo;
    int faixa_m;
    int faixa_M;
    struct sensor *proximo;

}sensor_t;

typedef struct setores{
    string lugar;
    string_l descricao;
    int qtd_sensores_por_setor;
    sensor_t *sensor_S;
    int *horario_1;
    int *leitura_1;
    int *horario_2;
    int *leitura_2;
    struct setores *proximo;
}setores_t;

//variaveis globais
sensor_t sensores[T_SNS];
setores_t setores[T_STRS];

int qtd_sensores = 0, qtd_setores = 0, id = 1;

//detalhes
void retirar_enter(string str);
void limpar_tela(void);
void botao_pause(void);
//cabeçalho
int menu_principal(void);
int menu_pesquisar(void);
int menu_relatorios(void);
int menu_arquivos(void);

sensor_t* criar_sensor(void);
setores_t* criar_setores(sensor_t *lista_sensores);

void inserir_na_lista_sensores(sensor_t **lista, sensor_t *novo);
void inserir_na_lista_setores(setores_t **lista_setores, setores_t *novo);

void listar_sensor(sensor_t *lista);
void listar_setores(setores_t *lista);

void pesquisar_sensores(sensor_t *lista);
void pesquisar_setores(setores_t *lista);

void selecao_numero_sensores_nomes(setores_t **novo, sensor_t *lista_sensores);
void selecao_numero_sensores_horarios(setores_t **novo, sensor_t *lista_sensores);
void selecao_numero_sensores_leitura(setores_t **novo, sensor_t *lista_sensores);

setores_t* procurar_setor(setores_t *lista, string str);
sensor_t* procurar_sensor(setores_t *lista, string str);

void excluir_lista(setores_t **lista, sensor_t *sensor_excluido, setores_t *setor_achado);

void relatorio_de_sensores_geral(void);
void relatorio_de_sensores_por_tipo(void);
void relatorio_de_setores(void);
void relatorio_leituras_por_local(void);
void relatorio_leituras_todos_locais(void);
void relatorio_variacao_por_setor_sensor(void);
void relatorio_media_por_sensor(void);

sensor_t* descobrir_ultimo_sensor(sensor_t *lista);
setores_t* descobrir_ultimo_setor(setores_t *lista);

void exportar_arquivo_binario(sensor_t *lista_sensores, setores_t *lista_setores,  char *nome_arq_sensores, char *nome_arq_setores);
void exportar_arquivo_para_csv(sensor_t *lista_sensores, setores_t *lista_setores,  char *nome_arq_sensores, char *nome_arq_setores);
void exportar_arquivo_html(sensor_t *lista_sensores, setores_t *lista_setores,  char *nome_arq_sensores, char *nome_arq_setores);
void importar_arq(sensor_t **lista_sensores, setores_t **lista_setores,  char *nome_arq_sensores, char *nome_arq_setores);



int main()
{
    int opcao, opcao_a, opcao_b, opcao_c;
    sensor_t *sensores_todos = NULL, *novo_sensor = NULL, *achar_sensor = NULL;
    setores_t *setores_todos = NULL, *novo_setor = NULL, *achar_setor = NULL;
    string nome_setor, nome_sensor;
    char checagem_exclusao;

    srand(time(NULL));
    limpar_tela();

    do{
        opcao = menu_principal();
        

        switch (opcao){
            case 1: novo_sensor = criar_sensor();
                    inserir_na_lista_sensores(&sensores_todos, novo_sensor);
                    limpar_tela();
                    break;
            case 2: novo_setor = criar_setores(sensores_todos);
                    inserir_na_lista_setores(&setores_todos, novo_setor);
                    limpar_tela();
                    break;
            case 3: limpar_tela();
                    listar_sensor(sensores_todos);
                    botao_pause();
                    limpar_tela();
                    break;
            case 4: limpar_tela();
                    listar_setores(setores_todos);
                    botao_pause();
                    limpar_tela();
                    break;
            case 5: do{
                        opcao_a = menu_pesquisar();
                        switch (opcao_a) {
                            case 1: pesquisar_sensores(sensores_todos);
                                    break;
                            case 2: pesquisar_setores(setores_todos);
                                    break;
                        }
                    } while (opcao_a != FIM);
                    break;
            case 6: do {
                        opcao_b = menu_relatorios();
                        switch (opcao_b){
                            case 1:relatorio_de_sensores_geral();
                                   botao_pause();
                                   limpar_tela();
                                   break;
                            case 2:relatorio_de_sensores_por_tipo();
                                   botao_pause();
                                   limpar_tela(); 
                                   break;
                            case 3: listar_setores(setores_todos);
                                    botao_pause();
                                    limpar_tela();
                                    break;
                            case 4: limpar_tela();
                                    relatorio_leituras_por_local();
                                    botao_pause();
                                    break;
                            case 5: limpar_tela();
                                    relatorio_leituras_todos_locais();
                                    botao_pause();
                                    break;
                            case 6: limpar_tela();
                                    relatorio_variacao_por_setor_sensor();
                                    botao_pause();
                                    break;
                            case 7: limpar_tela();
                                    relatorio_media_por_sensor();
                                    botao_pause();
                                    break;
                            case 0: break;
                            default: printf("programa nao existente");
                        }


                    }while(opcao_b != FIM);
            
            case 7: printf("digite o nome so setor que quer remover o sensor:");
                    fgets(nome_setor, T_STR, stdin);
                    retirar_enter(nome_setor);

                    achar_setor = procurar_setor(setores_todos, nome_setor);

                    if(achar_setor == NULL) printf("setor nao encontrado\n");
                    else{
                        printf("digite o nome do sensor que se quer excluir: ");
                        fgets(nome_sensor, T_STR, stdin);
                        retirar_enter(nome_sensor);

                        achar_sensor = procurar_sensor(achar_setor, nome_sensor);
                        
                        if(achar_sensor == NULL) printf("sensor não achado\n");
                        else{
                            printf("voce deseja excluir o sensor %s do setor %s?(S/N): ", achar_sensor->nome_s, achar_setor->lugar);
                            scanf("%c", &checagem_exclusao);
                            if(checagem_exclusao == 's' || checagem_exclusao == 'S'){
                                excluir_lista(&setores_todos, achar_sensor, achar_setor);
                                printf("sensor excluido do setor com sucesso");
                                botao_pause();
                                limpar_tela();
                            }

                        } 
                        
                    }
                    //modular isso pelo amor de deus

                    break;
            case 8: limpar_tela();
                    do{
                        opcao_c = menu_arquivos();
                        switch (opcao_c) {
                            case 1: exportar_arquivo_binario(sensores_todos, setores_todos, "arq_sensores.bin", "arq_setores.bin");
                                    break;
                            case 2: break;
                            case 3: exportar_arquivo_html(sensores_todos, setores_todos, "arq_sensores.html", "arq_setores.html");
                                    break;
                            case 4: importar_arq(&sensores_todos, &setores_todos, "arq_sensores.bin", "arq_setores.bin");
                                    break;
                        }

                    } while(opcao_c != FIM);
                    
                    break;
            }
    }while (opcao != FIM);

    return 0;
}

void retirar_enter(string str)
{
    str[strlen(str) - 1] = '\0';
}

//menu pricipal
int menu_principal(void)
{   
    int opcao;
    printf("|-------------MENU SENSORES ------------|\n");
    printf("1. criar novo sensor\n");
    printf("2. registrar setor novo\n");
    printf("3. listar sensores\n");
    printf("4. listar setores\n");
    printf("5. menu de pesquisa\n");
    printf("6. menu de relatorios\n");
    printf("7. retirar o sensor de um setor\n");
    printf("8. menu de arquivos\n");
    printf("0. sair do programa\n");
    printf(":::: ");
    scanf("%i", &opcao);
    getchar();
    return opcao;
}

//cria um novo sensor
sensor_t *criar_sensor(void)
{
    sensor_t *novo = NULL;
    novo  = (sensor_t*)malloc(sizeof(sensor_t));

    printf("digite o nome do sensor\n");
    fgets(novo->nome_s, T_STR, stdin);
    retirar_enter(novo->nome_s);

    printf("digite o nome do tipo de identificao\n");
    fgets(novo->tipo_s, T_STR, stdin);
    retirar_enter(novo->tipo_s);
    
    novo->id_tipo = 1;
    //poderia arrumar isso io_2;
    
    /*if(){
        novo->id_tipo = id;
    }->proximo
    for(int i = 0; i < qtd_sensores; i++){
        if (strcmp(novo->tipo_s, sensores[i].tipo_s ) == 0){
            novo->id_tipo = sensores[i].id_tipo;
            break;
        }
        else{
           novo->id_tipo = -1;
        }
        
    }

    if(novo->id_tipo == -1){
        id ++;
        novo->id_tipo = id;
    }*/

    printf("digite o parametro minimo\n");
    scanf("%i", &novo->faixa_m);
    getchar();

    printf("digite o parametro maximo\n");
    scanf("%i", &novo->faixa_M);
    getchar();
    
    novo->proximo = NULL;

    return novo;
}

//cria um setor novo
setores_t *criar_setores(sensor_t *lista_sensores)
{
    setores_t *novo = NULL;
    novo = (setores_t*)malloc(sizeof(setores_t));

    printf("digite o nome do setor que deseja adicionar: ");
    fgets(novo->lugar, T_STR, stdin);
    retirar_enter(novo->lugar);

    printf("digite um breve descricao do setor:");
    fgets(novo->descricao, T_LSTR, stdin);
    retirar_enter(novo->descricao);

    do{    
        printf("digite o numero sensores voce quer adicionar (1 a 3): ");
        scanf("%i", &novo->qtd_sensores_por_setor);
        getchar();
        
        if(novo->qtd_sensores_por_setor > 3 || novo->qtd_sensores_por_setor < 1) printf("numero invalido\n");
    
    }while(novo->qtd_sensores_por_setor > 3 || novo->qtd_sensores_por_setor < 1);

    selecao_numero_sensores_nomes(&novo, lista_sensores);

    selecao_numero_sensores_horarios(&novo, lista_sensores);

    selecao_numero_sensores_leitura(&novo, lista_sensores);

    novo->proximo = NULL;

    return novo;
}

void selecao_numero_sensores_nomes(setores_t **novo,sensor_t *lista_sensores)
{
    int qtd_sensores_adicionados = 0, j = 0;
    string str;
    
    (*novo)->sensor_S = (sensor_t*)malloc(sizeof(sensor_t) * (*novo)->qtd_sensores_por_setor);

    do{
        sensor_t *aux = lista_sensores; 

        printf("digite quais sensores voce quer adicionar(nome): ");
        fgets(str, T_STR, stdin);
        retirar_enter(str);

        for(aux; aux != NULL; aux = aux->proximo){
            if(strcmp(str,aux->nome_s) == 0)
            {
                *((*novo)->sensor_S+qtd_sensores_adicionados) = *aux;
                qtd_sensores_adicionados++;
            }
        }
        if(qtd_sensores_adicionados == j) printf("sensor invalido\n");
        if(qtd_sensores_adicionados > j) j++; 

    }while(qtd_sensores_adicionados != (*novo)->qtd_sensores_por_setor);

}

void selecao_numero_sensores_horarios(setores_t **novo, sensor_t *lista_sensores)
{
    (*novo)->horario_1 = (int*)malloc(sizeof(int) * (*novo)->qtd_sensores_por_setor);
    (*novo)->horario_2 = (int*)malloc(sizeof(int) * (*novo)->qtd_sensores_por_setor);

    for(int i = 0; i < (*novo)->qtd_sensores_por_setor; i++)
    {
        
        printf("horario da primeira leitura.: (%s)", ((*novo)->sensor_S+i)->nome_s);
        scanf("%i", &*((*novo)->horario_1+i)) ;
        getchar();

        printf("horario da segunda leitura..: (%s)", ((*novo)->sensor_S+i)->nome_s);
        scanf("%i", &*((*novo)->horario_2+i));
        getchar();

    }

    
    
}

void selecao_numero_sensores_leitura(setores_t **novo, sensor_t *lista_sensores)
{
    (*novo)->leitura_1 = (int*)malloc(sizeof(int) * (*novo)->qtd_sensores_por_setor);
    (*novo)->leitura_2 = (int*)malloc(sizeof(int) * (*novo)->qtd_sensores_por_setor);


    for(int i = 0; i < (*novo)->qtd_sensores_por_setor; i++){
            do{
                *((*novo)->leitura_1+i) = (rand() %  ((*novo)->sensor_S+i)->faixa_M)+ ((*novo)->sensor_S+i)->faixa_m;
                *((*novo)->leitura_2+i) = (rand() %  ((*novo)->sensor_S+i)->faixa_M) + ((*novo)->sensor_S+i)->faixa_m;
            
            }while (*((*novo)->leitura_1+i) > ((*novo)->sensor_S+i)->faixa_M || *((*novo)->leitura_1+i) < ((*novo)->sensor_S+i)->faixa_m ||
                    *((*novo)->leitura_2+i) > ((*novo)->sensor_S+i)->faixa_M || *((*novo)->leitura_2+i) < ((*novo)->sensor_S+i)->faixa_m);
        
        
    }
}
/*acredito que tenha ficado um pouco confuso, mas o que ele faz é: ele aleatoriza os valores e checa se esta nos dois parametros. se não, ele retorna 
e tenta novamente */

//inserir na lista pelo ultimo, tanto sensores e setores
void inserir_na_lista_sensores(sensor_t **lista, sensor_t *novo)
{

    if(*lista == NULL){
        *lista = novo;
    }

    else{
        sensor_t *aux = descobrir_ultimo_sensor(*lista);
        aux->proximo = novo;
    }

}

sensor_t* descobrir_ultimo_sensor(sensor_t *lista)
{
    while(lista->proximo != NULL)
    {
        lista = lista->proximo;
    }

    return lista;
}

void inserir_na_lista_setores(setores_t **lista, setores_t *novo)
{

    if(*lista == NULL){
        *lista = novo;
    }

    else{
        setores_t *aux = descobrir_ultimo_setor(*lista);
        aux->proximo = novo;
    }
}

setores_t* descobrir_ultimo_setor(setores_t *lista)
{

    while(lista->proximo != NULL)
    {
        lista = lista->proximo;
    }

    return lista;

}
//fim da inserção de lista setores e sensores


//mostra os sensores ativos
void listar_sensor(sensor_t *lista)
{
    if(lista == NULL) printf("nenhum sensor ativo\n");

    else{
        for(lista; lista != NULL ; lista = lista->proximo){
            printf("--------------------------------\n");
            printf("nome so sensor: %s\n", lista->nome_s);
            printf("nome do tipo  : %s\n", lista->tipo_s);
            printf("faixa minima  : %i\n", lista->faixa_m);
            printf("faixa maxima  : %i\n", lista->faixa_M);
            printf("--------------------------------\n");
        }   

    }    
}

void listar_setores(setores_t *lista)
{
    if(lista == NULL) printf("nenhum setor criado\n");

    else{

        for(lista; lista != NULL; lista = lista->proximo){
            printf("--------------------------------\n");
            printf("nome so setor.......: %s\n", lista->lugar);
            printf("descrição do setor..: %s\n", lista->descricao);
            for(int k = 0; k < lista->qtd_sensores_por_setor; k++)
            {
                printf("horario 1(sensor:%s).: %i\n",   (lista->sensor_S+k)->nome_s, *(lista->horario_1+k));
                printf("leitura 1(sensor:%s).: %i\n",   (lista->sensor_S+k)->nome_s, *(lista->leitura_1+k));
                printf("horario 2(sensor:%s).: %i\n",   (lista->sensor_S+k)->nome_s, *(lista->horario_2+k));
                printf("leitura 2(sensor:%s).: %i\n",   (lista->sensor_S+k)->nome_s, *(lista->leitura_2+k));
            }
            printf("--------------------------------\n");
        }   

    }    
    
}



//parte pesquisa.(inicio)
int menu_pesquisar()
{
    int opcao;

    printf("------------MENU PESQUISA------------\n");
    printf("1.Pesquisar por tipo de sensor\n");
    printf("2.Pesquisar por descrição de setor\n");
    printf("0.Voltar para o menu principal\n");
    printf(":::: ");
    scanf("%i", &opcao);
    getchar();
    return opcao;
}

void pesquisar_sensores(sensor_t *lista)
{
    string str;

    printf("digite o tipo de sensor: ");
    fgets(str, T_STR, stdin);
    retirar_enter(str);

    for(lista; lista != NULL; lista = lista->proximo)
    {
        if(strcmp(str,lista->tipo_s) == 0)
        {
            printf("--------------------------------\n");
            printf("nome so sensor: %s\n",  lista->nome_s);
            printf("nome do tipo  : %s\n",  lista->tipo_s);
            printf("faixa minima  : %i\n",  lista->faixa_m);
            printf("faixa maxima  : %i\n",  lista->faixa_M);
            printf("--------------------------------\n"); 
            break;
        }
    }
}

void pesquisar_setores(setores_t *lista)
{
    string_l str;

    printf("digite a descrição do setor: ");
    fgets(str, T_LSTR, stdin);
    retirar_enter(str);

    for(lista; lista != NULL; lista = lista->proximo)
    {
        if(strcmp(str,lista->descricao) == 0)
        {
            printf("--------------------------------\n");
            printf("nome so setor.......: %s\n", lista->lugar);
            printf("descrição do setor..: %s\n", lista->descricao);
            for(int k = 0; k < lista->qtd_sensores_por_setor; k ++)
            {
                printf("setor[ %s ], horario[ %i ], leitura 1: %i\n", lista->lugar, *(lista->horario_1+k), *(lista->leitura_1+k));
                printf("setor[ %s ], horario[ %i ], leitura 2: %i\n", lista->lugar, *(lista->horario_2+k), *(lista->leitura_1+k));
            }
            printf("--------------------------------\n"); 
            break;
        }   
    }
}

int menu_relatorios()
{
    int opcao;

    printf("1.relatório de sensores geral\n");
    printf("2.relatório de sensores por tipo\n");
    printf("3.Relatório de setores\n");
    printf("4.Relatório de leituras por local\n");
    printf("5.Relatório de leituras por todos os locais\n");
    printf("6.Relatório de variação de leitura por setor e por sensor\n");
    printf("7.Relatório de médias de leitura por sensor considerando todos os setores\n");
    printf("0.voltar para o menu principal\n");
    printf("::::");
    scanf("%i", &opcao);
    getchar();
    return opcao;

}
//parte pesquisa final

// parte de relatorios
void relatorio_de_sensores_geral(void)
{    
    int taboao = 1;
    if(taboao == 3) printf("nenhum sensor ativo\n");

    else{
        for(int i = 0; i < qtd_sensores; i++){
            printf("--------------------------------\n");
            printf("nome so sensor: %s\n", sensores[i].nome_s);
            printf("nome do tipo  : %s\n", sensores[i].tipo_s);
            printf("faixa minima  : %i\n", sensores[i].faixa_m);
            printf("faixa maxima  : %i\n", sensores[i].faixa_M);
            /*if(qtd_setores == 0) printf("nenhum setor disponivel\n");
            
            else{
                for(int j = 0; j < qtd_setores; j++){
                    for(int k = 0; k < 3; k++){
                        if(!strcmp(sensores[i].nome_s,setores[j].sensor_S[k].nome_s)){
                            printf("setor[ %s ], horario[ %i ], leitura 1: %i\n",setores[j].lugar, setores[j].leitura_1[0][k], setores[j].horario_1[0][k]);
                            printf("setor[ %s ], horario[ %i ], leitura 2: %i\n",setores[j].lugar, setores[j].leitura_2[0][k], setores[j].horario_2[0][k]);
                        }
                    }
                }
            }*/
            printf("----------------------------------\n");
            /* 
                primeiro ele checa se possui algum setor 
               em segundo ele checa os setores que estão ativos 
               em terceiro ele checa o setor_S pra ver se aparece o nome dos sensores são iguais 
               em quarto ele terminda mostrando a leitura do setor em que aparece o sensor e mostra a leitura
            */
        }   

    }
}

void relatorio_de_sensores_por_tipo(void)
{
    int valor_comparador = 1;

    if(qtd_sensores == 0) printf("sem sensores para relatar\n");
    /*
    else{
        for(int i = 0; i < qtd_sensores; i++)
        {   
            //essa parte esta com erro, pois ele pega outra coisa
            if(i == 0){
            printf("--------------------------------\n");
            printf("tipo do sensor..........: %s\n", sensores[valor_comparador].tipo_s);
            }

            if(sensores[i].id_tipo == valor_comparador){
                printf("--------------------------------\n");
                printf("nome do sensor......: %s\n", sensores[i].nome_s);
                printf("tipo do sensor......: %s\n", sensores[i].tipo_s);
                if(qtd_setores == 0) printf("sem setores ativos\n");
                for(int p = 0; p < qtd_setores; p++){
                    for(int k = 0; k < 3; k++){
                        if(!strcmp(sensores[i].nome_s,setores[p].sensor_S[k].nome_s)){
                            printf("setor[ %s ], horario[ %i ], leitura 1: %i\n",setores[p].lugar, setores[p].leitura_1[0][k], setores[p].horario_1[0][k]);
                            printf("setor[ %s ], horario[ %i ], leitura 2: %i\n",setores[p].lugar, setores[p].leitura_2[0][k], setores[p].horario_2[0][k]);
                        }
                    }
                }
                    printf("--------------------------------\n");
                }   
            
            if(i == qtd_sensores - 1){
                valor_comparador++;
                i = 0;
            }
            
            if(valor_comparador > id) break;  
        }
    }*/    

}
void relatorio_de_setores(void)
{
    //listar_setores();
}

/*coisas para arrumar 
  -terminar de implantar o codigo dos relatorios
  -arrumar o calculo da faixa maxima e minima pq ele nao faz sentido
  -nao sei como fazer o relatorio_de_sensores_por_tipo, precisa ir na monitoria
*/



void relatorio_leituras_por_local(void)
{
    /*string nome_setor;

    printf("Digite o nome do setor: ");
    fgets(nome_setor, T_STR, stdin);
    retirar_enter(nome_setor);

    for(int i = 0; i < qtd_setores; i++)
    {
        if(strcmp(nome_setor, setores[i].lugar) == 0)
        {
            printf("\nSETOR: %s\n", setores[i].lugar);

            for(int k = 0; k < setores[i].qtd_sensores_por_setor; k++)
            {
                printf("\nSensor: %s\n",
                       setores[i].sensor_S[k].nome_s);

                printf("Horario %i -> Leitura %i\n",
                       setores[i].horario_1[0][k],
                       setores[i].leitura_1[0][k]);

                printf("Horario %i -> Leitura %i\n",
                       setores[i].horario_2[0][k],
                       setores[i].leitura_2[0][k]);
            }
            return;
        }
    }*/

    printf("Setor nao encontrado\n");
}

void relatorio_leituras_todos_locais(void)
{
    /*if(qtd_setores == 0)
    {
        printf("Nenhum setor cadastrado\n");
        return;
    }

    for(int i = 0; i < qtd_setores; i++)
    {
        printf("\n--------------------------------\n");
        printf("SETOR: %s\n", setores[i].lugar);

        for(int k = 0; k < setores[i].qtd_sensores_por_setor; k++)
        {
            printf("\nSensor: %s\n",
                   setores[i].sensor_S[k].nome_s);

            printf("Horario %i -> Leitura %i\n",
                   setores[i].horario_1[0][k],
                   setores[i].leitura_1[0][k]);

            printf("Horario %i -> Leitura %i\n",
                   setores[i].horario_2[0][k],
                   setores[i].leitura_2[0][k]);
        }
    }
    */
}

void relatorio_variacao_por_setor_sensor(void)
{
    /*if(qtd_setores == 0)
    {
        printf("Nenhum setor cadastrado\n");
        return;
    }

    for(int i = 0; i < qtd_setores; i++)
    {
        printf("\n--------------------------------\n");
        printf("SETOR: %s\n", setores[i].lugar);

        for(int k = 0; k < setores[i].qtd_sensores_por_setor; k++)
        {
            int variacao =
                setores[i].leitura_2[0][k] -
                setores[i].leitura_1[0][k];

            printf("Sensor: %s\n",
                   setores[i].sensor_S[k].nome_s);

            printf("Leitura 1: %i\n",
                   setores[i].leitura_1[0][k]);

            printf("Leitura 2: %i\n",
                   setores[i].leitura_2[0][k]);

            printf("Variacao : %i\n\n",
                   variacao);
        }
    }*/

}

void relatorio_media_por_sensor(void)
{
    /*if(qtd_sensores == 0)
    {
        printf("Nenhum sensor cadastrado\n");
        return;
    }

    for(int i = 0; i < qtd_sensores; i++)
    {
        int soma = 0;
        int quantidade = 0;

        for(int j = 0; j < qtd_setores; j++)
        {
            for(int k = 0; k < setores[j].qtd_sensores_por_setor; k++)
            {
                if(strcmp(
                    sensores[i].nome_s,
                    setores[j].sensor_S[k].nome_s) == 0)
                {
                    soma += setores[j].leitura_1[0][k];
                    soma += setores[j].leitura_2[0][k];
                    quantidade += 2;
                }
            }
        }

        if(quantidade > 0)
        {
            float media = (float)soma / quantidade;

            printf("--------------------------------\n");
            printf("Sensor: %s\n", sensores[i].nome_s);
            printf("Media : %.2f\n", media);
            printf("--------------------------------\n");
        }
    }
    */
}

setores_t* procurar_setor(setores_t *lista, string str)
{
    for(lista; lista!=NULL ; lista = lista->proximo)
    {
        if(!strcmp(str,lista->lugar)) return lista;

    }
    return NULL;
    
}

sensor_t* procurar_sensor(setores_t *lista, string str)
{
    for(int i = 0; i < 3; i++)
    {
        if(!strcmp(str, (lista->sensor_S+i)->nome_s))
        {
            return (lista->sensor_S+i);
        }

    }
    return NULL;

}

void excluir_lista(setores_t **lista, sensor_t *sensor_excluido, setores_t *setor_achado)
{
    setores_t *aux = NULL;
    aux = *lista;

   for(aux; aux != NULL; aux = (aux)->proximo){
        if(!strcmp(setor_achado->lugar, (aux)->lugar)){
            for(int i = 0; i < setor_achado->qtd_sensores_por_setor; i++){
                if(!strcmp(((aux)->sensor_S+i)->nome_s,sensor_excluido->nome_s)){
                    if(i == 0){
                        ((aux)->sensor_S++);
                        ((aux)->horario_1++);
                        ((aux)->leitura_1++);
                        ((aux)->horario_2++);
                        ((aux)->leitura_2++);

                        (aux)->qtd_sensores_por_setor -= 1;
                        return;
                    }
                    if(i == 1){
                        *((aux)->sensor_S+1) = *((aux)->sensor_S+2);
                        *((aux)->horario_1+1) = *((aux)->horario_1+2);
                        *((aux)->leitura_1+1) = *((aux)->leitura_1+2);
                        *((aux)->horario_2+1) = *((aux)->horario_2+2);
                        *((aux)->leitura_2+1) = *((aux)->leitura_2+2);

                        (aux)->qtd_sensores_por_setor -= 1;
                        return;
                    }
                    if(i == 2){
                        (aux)->qtd_sensores_por_setor -= 1;
                        return;
                    }
                }
            }
        }
   }


}


int menu_arquivos(void)
{
    int opcao;
    
    printf("1. exportar arquivo para binario\n");
    printf("2. exportar arquivo para .csv\n");
    printf("3. exportar arquivo para html\n");
    printf("4. pegar relatorio existente e inserir\n");
    printf(":::::");
    scanf("%i", &opcao);
    getchar();


    return opcao;
}

void limpar_tela(void)
{
    system("clear");
}

void botao_pause(void){
    char pause;

    printf("pessione enter para continuar\n");
    scanf("%c", &pause);
}

void exportar_arquivo_binario(sensor_t *lista_sensores, setores_t *lista_setores,  char *nome_arq_sensores, char *nome_arq_setores)
{
    FILE *fp = NULL;
    FILE *fp1 = NULL;

    fp = fopen(nome_arq_sensores, "wb");

    while (lista_sensores) {
        fwrite(lista_sensores, sizeof(sensor_t), 1, fp);
        lista_sensores = lista_sensores->proximo;
    }

    fclose(fp);

    fp1 = fopen(nome_arq_setores, "wb");

    while (lista_setores) {
        fwrite(lista_setores, sizeof(setores_t), 1, fp1);

        int n = lista_setores->qtd_sensores_por_setor;

        fwrite(lista_setores->sensor_S,  sizeof(sensor_t), n, fp1);
        fwrite(lista_setores->horario_1, sizeof(int), n, fp1);
        fwrite(lista_setores->leitura_1, sizeof(int), n, fp1);
        fwrite(lista_setores->horario_2, sizeof(int), n, fp1);
        fwrite(lista_setores->leitura_2, sizeof(int), n, fp1);

        lista_setores = lista_setores->proximo;
    }

    fclose(fp1);

}

void exportar_arquivo_para_csv(sensor_t *lista_sensores, setores_t *lista_setores,  char *nome_arq_sensores, char *nome_arq_setores)
{
    FILE *fp = NULL;

    fp = fopen(nome_arq_sensores, "w");

    while (lista_sensores) {
        fprintf(fp, "%s;", lista_sensores->nome_s);
        fprintf(fp, "%s;", lista_sensores->tipo_s);
        fprintf(fp, "%i;\n", lista_sensores->faixa_M);
        fprintf(fp, "%i;\n", lista_sensores->faixa_M);

        lista_sensores = lista_sensores->proximo;
    }

    fclose(fp);

}

void exportar_arquivo_html(sensor_t *lista_sensores, setores_t *lista_setores,  char *nome_arq_sensores, char *nome_arq_setores)
{
    FILE *fp = NULL;

    fp = fopen(nome_arq_sensores, "w");

    fprintf(fp, "<html><body>\n");
    fprintf(fp, "<table>\n");
    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr><th>nome do sensor</th><th>tipo de sensor</th><th>faixa minima</th><th>faixa maxima</th></tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");

    while (lista_sensores) {
        fprintf(fp, "<tr>\n");
        fprintf(fp, "<td>%s</td>", lista_sensores->nome_s);
        fprintf(fp, "<td>%s</td>", lista_sensores->tipo_s);
        fprintf(fp, "<td>%i</td>", lista_sensores->faixa_m);
        fprintf(fp, "<td>%i</td>\n", lista_sensores->faixa_M);
        fprintf(fp, "</tr>\n");
        lista_sensores = lista_sensores->proximo;
    }
    fprintf(fp, "</tbody>\n");

    fprintf(fp, "</table>\n");
    fprintf(fp, "</body></html>\n");

    fclose(fp);

    //ele reabre com outra coisa
    fp = fopen(nome_arq_setores, "w");

    fprintf(fp, "<html><body>\n");
    fprintf(fp, "<table>\n");
    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr><th>nome do setor</th><th>descrição</th><th>sensores ativosv</th><th>horario 1</th><th>leitura 1</th><th>horario 2</th><<th>leitura 2</th></tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");

    //mudar a exportação
    while (lista_setores) {
        fprintf(fp, "<tr>\n");
        fprintf(fp, "<td>%s</td>", lista_setores->lugar);
        fprintf(fp, "<td>%s</td>", lista_setores->descricao);
        for(int k = 0; k < lista_setores->qtd_sensores_por_setor; k++)
            {
                fprintf(fp,"<td>%i</td>", *(lista_setores->horario_1+k));
                fprintf(fp,"<td>%i</td>", *(lista_setores->leitura_1+k));
                fprintf(fp,"<td>%i</td>", *(lista_setores->horario_2+k));
                fprintf(fp,"<td>%i</td>", *(lista_setores->leitura_2+k));
            }
        fprintf(fp, "</tr>\n");
        lista_setores = lista_setores->proximo;
    }
    fprintf(fp, "</tbody>\n");

    fprintf(fp, "</table>\n");
    fprintf(fp, "</body></html>\n");

    fclose(fp);

}

void importar_arq(sensor_t **lista_sensores, setores_t **lista_setores,  char *nome_arq_sensores, char *nome_arq_setores)
{
    FILE *fp = NULL;
    sensor_t *novo = NULL;

    fp = fopen(nome_arq_sensores, "rb");

    while (!feof(fp)) {
        novo = (sensor_t*)malloc(sizeof(sensor_t));
        fread(novo, sizeof(sensor_t), 1, fp);
        
        novo->proximo = NULL;
        
        if (!feof(fp)) {
            inserir_na_lista_sensores(lista_sensores, novo);
        }
        else {
            free(novo);
        }
    }

    fclose(fp);

    FILE *fp1 = NULL;
    setores_t *novo_setor = NULL;

    fp1 = fopen(nome_arq_setores, "rb");

    while (!feof(fp1)) {
        novo_setor = (setores_t*)malloc(sizeof(setores_t));
        fread(novo_setor, sizeof(setores_t), 1, fp1);
        
        int qtd_sensores = novo_setor->qtd_sensores_por_setor; 

        novo_setor->sensor_S = (sensor_t*)malloc(sizeof(sensor_t) * qtd_sensores);
        novo_setor->horario_1 = (int*)malloc(sizeof(int) * qtd_sensores);
        novo_setor->leitura_1 = (int*)malloc(sizeof(int) * qtd_sensores);
        novo_setor->horario_2 = (int*)malloc(sizeof(int) * qtd_sensores);
        novo_setor->leitura_2 = (int*)malloc(sizeof(int) * qtd_sensores);

        fread(novo_setor->sensor_S, sizeof(sensor_t), qtd_sensores, fp1);
        fread(novo_setor->horario_1, sizeof(int), qtd_sensores, fp1);
        fread(novo_setor->leitura_1, sizeof(int), qtd_sensores, fp1);
        fread(novo_setor->horario_2, sizeof(int), qtd_sensores, fp1);
        fread(novo_setor->leitura_2, sizeof(int), qtd_sensores, fp1);

        novo_setor->proximo = NULL;
        
        if (!feof(fp1)) {
            inserir_na_lista_setores(lista_setores, novo_setor);
        }
        else {
            free(novo_setor);
        }
    }

    fclose(fp1);
}
