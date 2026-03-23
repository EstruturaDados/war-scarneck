#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TERR 5
#define TAM_STR 50

struct Territorio {
    char nome[TAM_STR];
    char cor[TAM_STR];
    int tropas;
};

struct Players{
    struct Territorio *atacante;
    struct Territorio *defensor;
};

void bufferCln(){
    int c;
    while((c = getchar()) !='\n' && c != EOF);
}

void interface(){
    printf("=================================================================\n");
    printf("              Cadastrando os %d territorios iniciais.\n", NUM_TERR);
    printf("=================================================================\n");
}

void territoriosInput(struct Territorio territorio[]){ //Aprendi com GPT que precisa de [] e não &
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
    printf("                cadastro inicial completo!\n\n");
}
void territoriosOutput(struct Territorio territorio[]){
    printf("=================================================================\n");
    printf("                    ESTADO DO MAPA ATUAL\n");
    printf("=================================================================\n");

    for (int i = 0; i < NUM_TERR; i++){
        printf("#%d -> %s (Exercito: %s, Tropas: %d)\n",i+1, territorio[i].nome, territorio[i].cor, territorio[i].tropas);
        printf("-----------------------------------------------------------------\n");
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
        
        struct Players *player;
        player = (struct Players*)malloc(sizeof(struct Players));
        
        if ((opt<=NUM_TERR) && (opt >=1) && (opt!=0)){
            player -> atacante = &territorio[opt-1];
            
            do{
                printf("escolha o territorio defensor (de 1 a %d): ", NUM_TERR);
                int opt2;
                scanf("%d",&opt2);
                bufferCln();
                if ((opt2<=NUM_TERR) && (opt2 >=1) && (opt2!=opt)){
                    player -> defensor = &territorio[opt2-1];
                    return *player;
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

    printf("O atacante rolou um dado e tiro: %d\n", dAtk);
    printf("O defensor rolou um dado e tiro: %d\n", dDef);

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


int main(){
    struct Territorio *territorio;
    territorio = (struct Territorio*) calloc(NUM_TERR, sizeof(struct Territorio));

    //Interface inicial
    interface();

    // coletando informações dos territorios
    territoriosInput(territorio);

    srand(time(NULL));


    int final=0;
    do{
        // imprimindo territorios
        territoriosOutput(territorio);
        
        // escolhendo o atacante e o defensor
        struct Players players = attackPhase(territorio);

        if (players.atacante == NULL || players.defensor == NULL){ //garantindo encerramento
            break;
        }else{ // rodando dados
            battle(players);
        }
        
        
        if (final==0){
            int end = 0;
            for (int i = 1; i<NUM_TERR; i++){
                if (strcmp(territorio[0].cor, territorio[i].cor) == 0){
                    end++;
                    if (end == NUM_TERR-1){
                        printf("Parabéns! vitória do exercito '%s'.\n\n", territorio[i].cor);
                        final++;
                        break;
                    }
                    continue;
                }else{
                    printf("Sem vencedor.\n\n");
                    break;
                }
            }
        }else{
            break;
        }

    }while(final==0);
    return 0;
}