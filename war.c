#include <stdio.h>
#include <string.h>

#define NUM_TERR 5
#define TAM_STR 50

typedef struct {
    char nome[TAM_STR];
    char cor[TAM_STR];
    int tropas;
} Territorio;

void bufferCln(){
    int c;
    while((c = getchar()) !='\n' && c != EOF);
}

void interface(){
    printf("=================================================================\n");
    printf("              Cadastrando os %d territorios iniciais.\n", NUM_TERR);
    printf("=================================================================\n");
}
void territoriosInput(Territorio territorio[]){ //Aprendi com GPT que precisa de [] e não &
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

        printf("------------------------------------------------------\n");

        territorio[i].nome[strcspn(territorio[i].nome, "\n")] = '\0';
        territorio[i].cor[strcspn(territorio[i].cor, "\n")] = '\0';
        i++;
    }
    printf("                cadastro inicial completo!\n\n");
}
void territoriosOutput(Territorio territorio[]){
    printf("=================================================================\n");
    printf("                    ESTADO DO MAPA ATUAL\n");
    printf("=================================================================\n");

    for (int i = 0; i < NUM_TERR; i++){
        printf("TERRITORIO %d\n", i+1);
        printf("    - Nome do territorio: %s\n", territorio[i].nome);
        printf("    - Dominado por: Exercito %s\n", territorio[i].cor);
        printf("    - Tropas: %d\n", territorio[i].tropas);
        printf("------------------------------------------------------\n");
    }

}

// Função principal
int main(){
    Territorio territorio[NUM_TERR];

    //Interface inicial
    interface();

    // coletando informações dos territorios
    territoriosInput(territorio);
    
    // imprimindo territorios
    territoriosOutput(territorio);

    return 0;
}