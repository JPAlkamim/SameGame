#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Posições da linha e coluna do jogo SAME
typedef struct Posicoes{
    int linha;
    int coluna;
}Posicoes;

//Fila para realocar a coluna do jogo SAME
typedef struct filaReloc{
    int elem[25];
    int inicio;
    int fim;
    int tamMAX;
}filaReloc;

//Inicializa fila de realocar
void inicializaFilaReloc (filaReloc *q){
    q->inicio=-1;
    q->fim=-1;
}

//Verifica se a fila realocar está vazia
int filaRelocVazia (filaReloc *q){
  return q->inicio==q->fim;
}

//Verifica se a fila realocar está cheia
int filaRelocCheia (filaReloc *q){
    return q->fim==q->tamMAX;
}

//Desloca a fila realocar caso ela esteja cheia
void descolaFilaReloc (filaReloc *q){
    int desloc=q->inicio+1;
    for(int i=desloc;i<q->fim;i++){
        q->elem[i-desloc]=q->elem[i];
    }
    q->inicio=-1;
    q->fim=q->fim-desloc;
}

//Insere na fila realocar
void insereFilaReloc (filaReloc *q, int x){
    if(filaRelocCheia(q)){
        descolaFilaReloc(q);
    } else {
        q->fim=q->fim+1;
        q->elem[q->fim]=x;
    }
}

//Remove da fila realocar
void removeFilaReloc (filaReloc *q){
    int x;
    if(!filaRelocVazia(q)){
        q->inicio=q->inicio+1;
        x=q->elem[q->inicio];
        if (filaRelocVazia(q)){
            inicializaFilaReloc(q);
        }
    }
};

//Devolve a o primeiro da fila realocar
int primeirodaFilaReloc (filaReloc *q){
    if (!filaRelocVazia(q)){
        return q->elem[q->inicio+1];
    }
};

//Fila para a função busca do jogo SAME
typedef struct fila1{
    struct Posicoes elem[25];
    int inicio;
    int fim;
    int tamMAX;
}fila1;

//Inicializa a fila para a função busca
void inicializaFila1 (fila1 *q){
  q->inicio=-1;
  q->fim=-1;
}

//Verifica se a fila para a função busca está vazia
int filaVazia1 (fila1 *q){
  return q->inicio==q->fim;
}

//Verifica se a fila para a função busca está cheia
int filaCheia1 (fila1 *q){
    return q->fim==q->tamMAX;
}

//Desloca a fila para a função busca caso esteja cheia
void descolaFila1 (fila1 *q){
    int desloc=q->inicio+1;
    for(int i=desloc;i<q->fim;i++){
        q->elem[i-desloc]=q->elem[i];
    }
    q->inicio=-1;
    q->fim=q->fim-desloc;
}

//Insere na fila para a função busca
void insereFila1 (fila1 *q, Posicoes *x){
    if(filaCheia1(q)){
        descolaFila1(q);
    } else {
        q->fim=q->fim+1;
        q->elem[q->fim]=*x;
    }
}

//Remove da fila para a função busca
struct Posicoes removeFila1 (fila1 *q){
    struct Posicoes x;
    if(!filaVazia1(q)){
        q->inicio=q->inicio+1;
        x=q->elem[q->inicio];
        if (filaVazia1(q)){
            inicializaFila1(q);
        }
    }
    return x;
};

//Retorna o primeiro da fila para a função busca
struct Posicoes primeirodaFila1 (fila1 *q){
    if (!filaVazia1(q)){
        return q->elem[q->inicio+1];
    }
};

//Busca os números(cores) ao redor de sua posição
int busca(int mSAME[12][16], int par, int linha, int coluna){
    fila1 *q=(fila1*)malloc(sizeof(fila1));;
    q->tamMAX=12*16;
    inicializaFila1(q);
    Posicoes *pri=(Posicoes*)malloc(sizeof(Posicoes));
    Posicoes *cima=(Posicoes*)malloc(sizeof(Posicoes));
    Posicoes *baixo=(Posicoes*)malloc(sizeof(Posicoes));
    Posicoes *esq=(Posicoes*)malloc(sizeof(Posicoes));
    Posicoes *dir=(Posicoes*)malloc(sizeof(Posicoes));
    pri->linha=linha;
    pri->coluna=coluna;
    insereFila1(q,pri);
    int contador=0,potencia2=1;
    while (!filaVazia1(q)){
        *pri=primeirodaFila1(q);
        if (mSAME[pri->linha][pri->coluna]==par||mSAME[pri->linha][pri->coluna]==0){
            mSAME[pri->linha][pri->coluna]=0;
            if (pri->linha+1<12){
                baixo->linha=pri->linha+1;
                baixo->coluna=pri->coluna;
                if (mSAME[baixo->linha][baixo->coluna]==par){
                    mSAME[baixo->linha][baixo->coluna]=0;
                    insereFila1(q,baixo);
                    contador++;
                }
            }
            if (pri->linha-1>-1){
                cima->linha=pri->linha-1;
                cima->coluna=pri->coluna;
                if (mSAME[cima->linha][cima->coluna]==par){
                    mSAME[cima->linha][cima->coluna]=0;
                    insereFila1(q,cima);
                    contador++;
                }
            }
            if (pri->coluna-1>-1){
                esq->linha=pri->linha;
                esq->coluna=pri->coluna-1;
                if (mSAME[esq->linha][esq->coluna]==par){
                    mSAME[esq->linha][esq->coluna]=0;
                    insereFila1(q,esq);
                    contador++;
                }
            }
            if (pri->coluna+1<16){
                dir->linha=pri->linha;
                dir->coluna=pri->coluna+1;
                if (mSAME[dir->linha][dir->coluna]==par){
                    mSAME[dir->linha][dir->coluna]=0;
                    insereFila1(q,dir);
                    contador++;
                }
            }
        }
        removeFila1(q);
    }
    if(contador!=0){
        for(int i=1;i<contador+1;i++){
            potencia2=potencia2*2;
        }
    }
    return potencia2;
}

//Realoca a linha do jogo SAME para baixo
void relocLinha (int mSAME[12][16]){ 
    filaReloc *q=(filaReloc*)malloc(sizeof(filaReloc));
    q->tamMAX=12;
    int aux=11;
    inicializaFilaReloc(q);
    for (int j=15;j>=0;j--){
        aux=11;
        for (int i=11;i>=0;i--){
            if(mSAME[i][j]!=0){
                insereFilaReloc(q,mSAME[i][j]);
                mSAME[i][j]=0;
            }
        }
        while (!filaRelocVazia(q)){
            mSAME[aux][j]=primeirodaFilaReloc(q);
            removeFilaReloc(q);
            aux--;
        }
        inicializaFilaReloc(q);
    }
}

//Realoca a coluna do jogo SAME para a esquerda
void relocColuna (int mSAME[12][16]){
    int aux=0;
    while (aux<15){
        if(mSAME[11][aux]==0){
            for(int j=aux;j<15;j++){
                for(int i=0;i<12;i++){
                    mSAME[i][j]=mSAME[i][j+1];
                    mSAME[i][j+1]=0;
                }
            }
            aux++;
        } else {
            aux++;
        }
    }
}

//Desenha o jogo SAME no terminal
void printarJogo(int mSAME[12][16]){
    int aux=0;
    printf("\033[0m    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n");
    for(int i=0;i<12;i++){
        for(int j=0;j<16;j++){
            if(j==0){
                if(aux<10){
                    printf("\033[0m%d ",aux);
                } else {
                    printf("\033[0m%d",aux);
                }
                aux++;
            }
            if(mSAME[i][j]==1){
                printf("\033[0;31m\1  1");
            } else if (mSAME[i][j]==2){
                printf("\033[0;34m\2  2");
            } else if (mSAME[i][j]==3){
                printf("\033[0;32m\3  3");
            } else {
                printf("\033[0;30m  0");
            }
        }
        printf("\n");
    }
}

//Retorna se a posição que o usuário escolheu é válida, ou seja, tem um grupo e não somente 1 (um)
int posicaoValida(int mSAME[12][16], int linha, int coluna){
    int aux=0;
    if(mSAME[linha][coluna]==mSAME[linha+1][coluna]||mSAME[linha][coluna]==mSAME[linha-1][coluna]||mSAME[linha][coluna]==mSAME[linha][coluna+1]||mSAME[linha][coluna]==mSAME[linha][coluna-1]){
        aux=1;
        return aux;
    } else {
        return aux;
    }
}

//Função a qual acontece os processos para o jogo SAME funcionar
void jogarSAME(int mSAME[12][16], int *contador){
    int coluna;
    int linha;
    printarJogo(mSAME);
    printf("\033[0mDigite a linha: \n");
    scanf("%d", &linha);
    printf("\033[0mDigite a coluna: \n");
    scanf("%d", &coluna);
    if (linha>11||coluna>15){
        printf("Posicao invalida, digite novamente.\n");
    } else if (posicaoValida(mSAME,linha,coluna)==0){
        printf("Jogada inválida, digite novamente.\n");
    } else {
        *contador=*contador + busca(mSAME,mSAME[linha][coluna],linha,coluna);
        relocLinha(mSAME);
        for(int i=0;i<14;i++){
            relocColuna(mSAME);
        }
  }
}

//Preenche de forma aleatória o jogo SAME
void preencherSAME(int mSAME[12][16]){
    for (int i=0;i<12;i++){
        for(int j=0;j<16;j++){
            int r = rand() % 18000;
            if (r<6000){
                mSAME[i][j]=1;
            } else if (r<12000){
                mSAME[i][j]=2;
            } else {
                mSAME[i][j]=3;
            }
        }
    }
}

//Retorna se ainda tem movimentos no jogo SAME
int movimento (int mSAME[12][16]){
    int auxiliar=0;
    for(int i=0;i<12;i++){
        for(int j=0;j<16;j++){
            if(mSAME[i][j]!=0){
                if(mSAME[i][j+1]==mSAME[i][j]||mSAME[i+1][j]==mSAME[i][j]||mSAME[i-1][j]==mSAME[i][j]||mSAME[i][j-1]==mSAME[i][j]){
                    auxiliar=1;
                }
            }
        }
    }
    return auxiliar;
}

//Retorna se o jogador ganhou ou perdeu o jogo SAME
int vencer (int mSAME[12][16]){
    int aux=0;
    for(int j=0;j<16;j++){
        if (mSAME[11][j]!=0){
            aux=1;
        }
    }
    return aux;
}


int main(){
    int mSAME[12][16], pontuacao=0;
    srand(time(NULL));
    preencherSAME(mSAME);
    while (movimento(mSAME)==1){
        jogarSAME(mSAME,&pontuacao);
    }
    if(vencer(mSAME)==0){
        printarJogo(mSAME);
        printf("\033[0mVoce ganhou o jogo.\n");
        printf("Sua pontuação: %d\n", pontuacao);
    } else {
        printarJogo(mSAME);
        printf("\033[0mVoce perdeu o jogo.\n");
        printf("Sua pontuação: %d\n", pontuacao);
    }
}
