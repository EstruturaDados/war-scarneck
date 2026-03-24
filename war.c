#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//variáveis globais
#define NUM_TERR 5
#define TAM_STR 50

//estruturas usadas
struct Territorio {
    char nome[TAM_STR];
    char cor[TAM_STR];
    int tropas;
};
struct Players{
    struct Territorio *atacante;
    struct Territorio *defensor;
};

//assinatura/protótipo das funções criadas e usadas
void bufferCln();
void interface();
void actionMenu();
void territoriosInput(struct Territorio territorio[]);
void territoriosOutput(struct Territorio territorio[]);
struct Players attackPhase(struct Territorio territorio[]);
void battle(struct Players players);
char* defMission(struct Territorio *territorios, int index);
void missionZero(struct Territorio *territorio, int index, int *final);
void missionOne(struct Territorio *territorio, int *final);
void missionTwo(struct Territorio *territorio, int index, int *final);
int checkMission(struct Territorio *territorio, char *mission, int index, int *final);
void checkVictory(struct Territorio territorio[], int *final);
void actualMission(char *mission);

//função principal
int main(){
    //criação das estruturas
    struct Territorio *territorio;
    territorio = calloc(NUM_TERR, sizeof(struct Territorio));
    
    //Interface inicial
    interface();
    
    //Coleta das informações dos territorios
    territoriosInput(territorio);
    
    
    
    srand(time(NULL));
    int index = rand()%NUM_TERR;
    char *mission = defMission(territorio, index);
    actualMission(mission);
    
    
    int final = 0;
    //looping principal
    do{
        // imprimindo territorios
        territoriosOutput(territorio);
        
        actionMenu();
        
        int opt;
        scanf("%d", &opt);
        bufferCln();


        switch (opt){
            case 1:
                // escolhendo o atacante e o defensor
                struct Players players = attackPhase(territorio);
                
                if (players.atacante == NULL || players.defensor == NULL){ //garantindo encerramento
                    break;
                }else{ // rodando dados
                    battle(players);
                    break;
                }
            case 2:
                actualMission(mission);
                break;
            case 0:
                final++;
                break;
            default:
                printf("escolha uma opção válida!");
                continue;
            
        }
        
        
        //checando vencedor
        if (final == 0) {
        checkMission(territorio,mission,index,&final);   
        checkVictory(territorio, &final);
        }     
        
    }while(final==0);
    
    //limpando memória
    free(territorio);
    free(mission);
    return 0;
}


void missionZero(struct Territorio *territorio, int index, int *final){
    for (int i = 0; i < NUM_TERR; i++){
        if (strcmp(territorio[i].cor, territorio[index].cor) == 0){
            return; // ainda existe → não venceu
        }
    }

    (*final)++;
    printf("Parabéns! o exército %s foi derrotado!\n", territorio[index].cor);
}
void missionOne(struct Territorio *territorio, int *final){
    int d = 0;

    for (int i = 0; i < NUM_TERR; i++){
        for (int j = i+1; j < NUM_TERR; j++){
            if (strcmp(territorio[i].cor, territorio[j].cor) == 0){
                d++;
            }
        }
    }

    if (d >= 2){ 
        (*final)++;
        printf("Parabéns! Você dominou o mapa!\n");
    }
}
void missionTwo(struct Territorio *territorio, int index, int *final){
    int d = 0;

    for (int i = 0; i < NUM_TERR; i++){
        if (strcmp(territorio[i].cor, territorio[index].cor) == 0){
            d++;
        }
    }

    if (d >= 3){
        (*final)++;
        printf("Parabéns! Você conquistou 3 territórios!\n");
    }
}
char* defMission(struct Territorio *territorios, int index){
    int dMission = rand() % 3;


    char *mission = malloc(TAM_STR);
    
    
    if (dMission == 0){
        snprintf(mission, TAM_STR, "Eliminar o Exercito %s.\n",
                 territorios[index].cor);
    } 
    else if (dMission == 1){
        snprintf(mission, TAM_STR, "Derrote 3 territórios do mapa.\n");
    } 
    else {
        snprintf(mission, TAM_STR, "Consiga 3 territórios do exercito %s.\n",territorios[index].cor);
    }
    return mission;

}

int checkMission(struct Territorio *territorio, char *mission, int index, int *final){

    char buffer[TAM_STR];

    // missão 0
    snprintf(buffer, TAM_STR, "Eliminar o Exercito %s.\n",
             territorio[index].cor);

    if (strcmp(mission, buffer) == 0){
        missionZero(territorio, index, final);
        return 1;
    }

    // missão 1
    snprintf(buffer, TAM_STR, "Derrote 3 territórios do mapa.\n");

    if (strcmp(mission, buffer) == 0){
        missionOne(territorio, final);
        return 1;
    }

    // missão 2
    snprintf(buffer, TAM_STR, "Consiga 3 territórios do exercito %s.\n",
             territorio[index].cor);

    if (strcmp(mission, buffer) == 0){
        missionTwo(territorio, index, final);
        return 1;
    }

    return 0;
}


//implementação das funções
void bufferCln(){
    int c;
    while((c = getchar()) !='\n' && c != EOF);
}
void interface(){
    printf("=================================================================\n");
    printf("              Cadastrando os %d territorios iniciais.\n", NUM_TERR);
    printf("=================================================================\n");
}
void territoriosInput(struct Territorio territorio[]){
    int i = 0;
    while (i < NUM_TERR){
        printf("\n***     Cadastre o territorio %d     ***\n\n", i+1);
        printf("Digite o nome do territorio: \n");
        fgets(territorio[i].nome, TAM_STR, stdin);
        printf("Digite a cor do territorio: \n");
        fgets(territorio[i].cor, TAM_STR, stdin);
        printf("Digite o numero de tropas: \n");
        
        scanf("%d", &territorio[i].tropas);
        bufferCln();
        
        printf("-----------------------------------------------------------------\n");
        
        territorio[i].nome[strcspn(territorio[i].nome, "\n")] = '\0';
        territorio[i].cor[strcspn(territorio[i].cor, "\n")] = '\0';
        i++;
    }
    printf("                cadastro inicial completo!\n\n\n");
}
void territoriosOutput(struct Territorio territorio[]){
    printf("=================================================================\n");
    printf("                    ESTADO DO MAPA ATUAL\n");
    printf("=================================================================\n");
    
    for (int i = 0; i < NUM_TERR; i++){
        printf("#%d -> %s (Exercito: %s, Tropas: %d)\n",i+1, territorio[i].nome, territorio[i].cor, territorio[i].tropas);
        printf("-----------------------------------------------------------------\n\n");
    }
    
}
struct Players attackPhase(struct Territorio territorio[]){
    printf("\n=================================================================\n");
    printf("                        FASE DE ATAQUE\n");
    printf("=================================================================\n");
    
    do{
        
        printf("Escolha o territorio atacante (de 1 a %d ou 0 para sair): ", NUM_TERR);
        int opt;
        scanf("%d", &opt);
        bufferCln();
        
        struct Players player;
        
        if ((opt<=NUM_TERR) && (opt >=1) && (opt!=0)){
            player.atacante = &territorio[opt-1];
            
            do{
                printf("escolha o territorio defensor (de 1 a %d): ", NUM_TERR);
                int opt2;
                scanf("%d",&opt2);
                bufferCln();
                if ((opt2<=NUM_TERR) && (opt2 >=1) && (opt2!=opt)){
                    player.defensor = &territorio[opt2-1];
                    return player;
                }else if(opt2 == opt){
                    printf("Selecione um defensor diferente do atacante.\n");
                    continue;
                }else{
                    printf("Opcao invalida, tente novamente.\n");
                    continue;
                }
            }while(1);
            
        }else if(opt == 0){
            printf("Saindo...");
            break;
        }else{
            printf("Opcao invalida, tente novamente.\n");
            continue;
        }
    }while(1);
    struct Players vazio = {NULL, NULL};
    return vazio;
}
void battle(struct Players players){
    printf("\n=================================================================\n");
    printf("                    RESULTADO DA BATALHA\n");
    printf("=================================================================\n");
    
    int dAtk = (rand() % 6)+1; 
    int dDef = (rand() % 6)+1; 
    
    printf("O atacante rolou um dado e tirou: %d\n", dAtk);
    printf("O defensor rolou um dado e tirou: %d\n", dDef);
    
    struct Territorio *vencedor;
    struct Territorio *perdedor;
    if(dAtk > dDef){
        vencedor = players.atacante;
        perdedor = players.defensor;
        
        perdedor -> tropas--;
        if(perdedor->tropas <= 0){
            strcpy(perdedor->cor, vencedor->cor); //ChatGPT ...
            perdedor->tropas = 1;
        }
        
    }else if(dDef > dAtk){
        vencedor = players.defensor;
        perdedor = players.atacante;
        perdedor->tropas--;
        if(perdedor->tropas <= 0){
            strcpy(perdedor->cor, vencedor->cor); //ChatGPT ...
            perdedor->tropas = 1;
        }
    }else{
        printf("Houve empate.\n");
        printf("pressione ENTER para continuar.\n");
        bufferCln();
        getchar();
        return; 
    }
    printf("VITORIA DA %s! e %s perdeu 1 tropa\n", vencedor->nome, perdedor->nome);
    
    printf("pressione ENTER para ir para o próximo turno.\n");
    bufferCln();
    getchar();
}
void actualMission(char *mission){
    printf("=================================================================\n");
    printf("                        MISSÂO ATUAL.\n");
    printf("=================================================================\n");
    printf("%s", mission);
    printf("-----------------------------------------------------------------\n\n");
    printf("pressione ENTER para ir para o próximo turno.\n");
    bufferCln();
    getchar();
    
}
void actionMenu(){
    
    printf("=================================================================\n");
    printf("                        MENU DE ACOES.\n");
    printf("=================================================================\n");
    printf("#1. Atacar\n");
    printf("#2. Verificar missao\n");
    printf("#0. Sair\n");
    printf("-----------------------------------------------------------------\n\n");

}
void checkVictory(struct Territorio territorio[], int *final){
    char *corBase = territorio[0].cor;

    for (int i = 1; i < NUM_TERR; i++){
        if (strcmp(corBase, territorio[i].cor) != 0){
            return; // ainda não venceu
        }
    }

    // se chegou aqui, todos são iguais
    printf("Parabéns! vitória do exército '%s'.\n\n", corBase);
    (*final)++;
}

