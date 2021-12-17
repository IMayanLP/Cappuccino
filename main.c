#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
// Definindo cores
#define AZUL        1
#define VERDE       2
#define VERMELHO    4
#define AMARELO     6
#define CORPADRAO   15
// Definindo tamanho do tabuleiro como constante
#define Tam         5

struct tab{
  int altura;
  int jogador;
};

void iniciarJogo(struct tab matriz[Tam][Tam], int player[4][5], int jogadorAtual){
  jogadorAtual = 0;
  gerarPlayers(player);
  gerarTabuleiro(matriz, player);
  exibeTabuleiro(matriz, jogadorAtual);
}

void textoColorido(int texto, int jogador) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(jogador) {
        case 0: SetConsoleTextAttribute(hConsole, AZUL); break;
        case 1: SetConsoleTextAttribute(hConsole, VERDE); break;
        case 2: SetConsoleTextAttribute(hConsole, VERMELHO); break;
        case 3: SetConsoleTextAttribute(hConsole, AMARELO); break;
    }
    printf("%d",texto);
    SetConsoleTextAttribute(hConsole, CORPADRAO);
}

void limparTela(){
    system("cls");
}

int gerarNum(int x,int y){
    int num;
    do{
        num = rand() % 10;  
    }while(num < x || num > y);
    return num;
}

void gerarPlayers(int a[4][5]){
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 5; j++){
      switch (i){
        case 0:
          a[i][j] = 0;
          break;
        case 1:
          a[i][j] = 1;
          break;
        case 2:
          a[i][j] = 2;
          break;
        case 3:
          a[i][j] = 3;
          break;
      }
    }
  }
}

void gerarTabuleiro(struct tab matriz[Tam][Tam], int player[4][5]){
  int pecas[20], count=0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 5; j++){
            pecas[count] = player[i][j];
            count++;
        }
    }

  count=0;
  for (int i = 0; i < Tam; i++){
    for (int j = 0; j < Tam; j++){
      if ((i == 0 && j == 0) || (i == 2 && j == 2) || (i == 4 && j == 4) || (i == 0 && j == 4) || (i == 4 && j == 0)){
        matriz[i][j].altura=0;
        matriz[i][j].jogador=4;
      } else {
        matriz[i][j].altura=1;
        matriz[i][j].jogador=pecas[count];
        count++;
      }
    }
  }

  for (int i = 0; i < Tam; i++){
    for (int j = 0; j < Tam; j++){
      if (matriz[i][j].jogador < 4){
        int x, y;
        do{
          x = gerarNum(0, 4);
          y = gerarNum(0, 4);
          if (matriz[x][y].jogador < 4){
            int aux = matriz[i][j].jogador;
            matriz[i][j].jogador = matriz[x][y].jogador;
            matriz[x][y].jogador = aux;
          }
        } while (matriz[x][y].jogador == 4);
      }
    }
  }
}

void exibeTabuleiro(struct tab matriz[Tam][Tam], int jogadorAtual){
  limparTela();
  printf("    1   2   3   4   5 ");
  printf("\n  ---------------------\n");
  for (int i = 0; i < Tam; i++){
    switch (i){
      case 0: printf("A |"); break;
      case 1: printf("B |"); break;
      case 2: printf("C |"); break;
      case 3: printf("D |"); break;
      case 4: printf("E |"); break;
    } 
    for (int j = 0; j < Tam; j++){
      switch (matriz[i][j].altura){
      case 0: printf("   |"); break;
      default: printf(" "); textoColorido(matriz[i][j].altura, matriz[i][j].jogador); printf(" |"); break;
      }
    }
    printf("\n  ---------------------\n");
  }
  logica(matriz, jogadorAtual);
}

void mostrarTabuleiro(struct tab matriz[Tam][Tam]){
  limparTela();
  printf("    1   2   3   4   5 ");
  printf("\n  ---------------------\n");
  for (int i = 0; i < Tam; i++){
    switch (i){
      case 0: printf("A |"); break;
      case 1: printf("B |"); break;
      case 2: printf("C |"); break;
      case 3: printf("D |"); break;
      case 4: printf("E |"); break;
    } 
    for (int j = 0; j < Tam; j++){
      switch (matriz[i][j].altura){
      case 0: printf("   |"); break;
      default: printf(" "); textoColorido(matriz[i][j].altura, matriz[i][j].jogador); printf(" |"); break;
      }
    }
    printf("\n  ---------------------\n");
  }
}

void logica(struct tab matriz[Tam][Tam], int jogadorAtual){
  if (jogadorEmJogo(matriz, jogadorAtual)){
    char texto[2];
    int pos[2];
    do{
      limparTela();
      mostrarTabuleiro(matriz);
      printf("\nVez do jogador "); textoColorido(jogadorAtual+1, jogadorAtual);
      printf("\nEscolha uma peca SUA para mover! (Ex.: a3): ");
      scanf("%s", &texto);
      posicaoMatriz(texto, pos);
    } while (matriz[pos[0]][pos[1]].jogador != jogadorAtual);
    printf("peca selecionada: "); textoColorido(matriz[pos[0]][pos[1]].altura,matriz[pos[0]][pos[1]].jogador);
    if (validaPeca(matriz, pos)){
      printf("\n  7   8   9 \n   \\  ^  / \n 4 <  "); textoColorido(matriz[pos[0]][pos[1]].altura,matriz[pos[0]][pos[1]].jogador); printf("  > 6 \n   /  v  \\ \n  1   2   3 ");
      int mov;
      printf("\nAgora, utilizando o teclado numerico escolha uma direcao VALIDA para ir:\t");
      scanf("%d", &mov);
      while (validaMov(matriz, pos, mov) == 0){
        printf("\nEscolha uma direcao VALIDA para ir:\t");
        scanf("%d", &mov);
      }
      MoverPeca(matriz, pos, mov);
      jogadorAtual = trocaTurno(jogadorAtual);
      exibeTabuleiro(matriz, jogadorAtual);
    } else {
      printf("\nImpossivel mecher essa peca");
      getch();
      logica(matriz, jogadorAtual);
    }
  } else {
    printf("\nJogador %d sem pecas", (jogadorAtual+1));
    getch();
    jogadorAtual = trocaTurno(jogadorAtual);
    exibeTabuleiro(matriz, jogadorAtual);
  }
}

int jogadorEmJogo(struct tab matriz[Tam][Tam], int jogadorAtual){
  int pos[2];
  for (int i = 0; i < Tam; i++){
    for (int j = 0; j < Tam; j++){
      if (matriz[i][j].jogador == jogadorAtual){
        pos[0] = i;
        pos[1] = j;
        if (validaPeca(matriz, pos)){
          return 1;
        }
      }
    }
  }
  return 0;
}

int fimPartida(struct tab matriz[Tam][Tam]){
  int pos[2], pecasEmJogo = 0;
  for (int i = 0; i < Tam; i++){
    for (int j = 0; j < Tam; i++){
      pos[0] = i;
      pos[1] = j;
      if (validaPeca(matriz, pos)){
        pecasEmJogo++;
      }
    }
  }
  if (pecasEmJogo > 0){
    return 1;
  } else {
    return 0;
  }
}

int trocaTurno(int jogadorAtual){
  if (jogadorAtual >= 3){
    jogadorAtual = 0;
  } else {
    jogadorAtual++;
  }
  return jogadorAtual;
}

void posicaoMatriz(char texto[], int pos[]){
    switch (texto[0]){
      case 'A': case 'a': pos[0] = 0; break;
      case 'B': case 'b': pos[0] = 1; break;
      case 'C': case 'c': pos[0] = 2; break;
      case 'D': case 'd': pos[0] = 3; break;
      case 'E': case 'e': pos[0] = 4; break;
      default: pos[0] = 5; break;
    }
    switch (texto[1]){
      case '1': pos[1] = 0; break;
      case '2': pos[1] = 1; break;
      case '3': pos[1] = 2; break;
      case '4': pos[1] = 3; break;
      case '5': pos[1] = 4; break;
      default: pos[1] = 5; break;
    }
}

int validaPeca(struct tab matriz[Tam][Tam], int pos[2]){
  int qtdMov = 0;
  if (matriz[pos[0]-1][pos[1]-1].altura >= 1 && (matriz[pos[0]-1][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura)) qtdMov++;
  if (matriz[pos[0]-1][pos[1]].altura >= 1 && (matriz[pos[0]-1][pos[1]].altura <= matriz[pos[0]][pos[1]].altura)) qtdMov++;
  if (matriz[pos[0]-1][pos[1]+1].altura >= 1 && (matriz[pos[0]-1][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura)) qtdMov++;
  if (matriz[pos[0]][pos[1]-1].altura >= 1 && (matriz[pos[0]][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura)) qtdMov++;
  if (matriz[pos[0]][pos[1]+1].altura >= 1 && (matriz[pos[0]][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura)) qtdMov++;
  if (matriz[pos[0]+1][pos[1]-1].altura >= 1 && (matriz[pos[0]+1][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura)) qtdMov++;
  if (matriz[pos[0]+1][pos[1]].altura >= 1 && (matriz[pos[0]+1][pos[1]].altura <= matriz[pos[0]][pos[1]].altura)) qtdMov++;
  if (matriz[pos[0]+1][pos[1]+1].altura >= 1 && (matriz[pos[0]+1][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura)) qtdMov++;

  if (qtdMov>0){
    return 1;
  } else {
    return 0;
  }
}

int validaMov(struct tab matriz[Tam][Tam], int pos[2], int mov){
  switch (mov){
  case 1:
    if (matriz[pos[0]+1][pos[1]-1].altura > 0 && (matriz[pos[0]+1][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]+1 < 5 && pos[0]+1 >= 0) && (pos[1]-1 >= 0 && pos[1]-1 < 5)){
      return 1;
    }
    break;
  case 2:
    if (matriz[pos[0]+1][pos[1]].altura > 0 && (matriz[pos[0]+1][pos[1]].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]+1 < 5 && pos[0]+1 >= 0) && (pos[1] >= 0 && pos[1] < 5)){
      return 1;
    } break;
  case 3:
    if (matriz[pos[0]+1][pos[1]+1].altura > 0 && (matriz[pos[0]+1][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]+1 < 5 && pos[0]+1 >= 0) && (pos[1]+1 >= 0 && pos[1]+1 < 5)){
      return 1;
    } break;
  case 4:
    if (matriz[pos[0]][pos[1]-1].altura > 0 && (matriz[pos[0]][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0] < 5 && pos[0] >= 0) && (pos[1]-1 >= 0 && pos[1]-1 < 5)){
      return 1;
    } break;
  case 6:
    if (matriz[pos[0]][pos[1]+1].altura > 0 && (matriz[pos[0]][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0] < 5 && pos[0] >= 0) && (pos[1]+1 >= 0 && pos[1]+1 < 5)){
      return 1;
    } break;
  case 7:
    if (matriz[pos[0]-1][pos[1]-1].altura > 0 && (matriz[pos[0]-1][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]-1 < 5 && pos[0]-1 >= 0) && (pos[1]-1 >= 0 && pos[1]-1 < 5)){
      return 1;
    } break;
  case 8:
    if (matriz[pos[0]-1][pos[1]].altura > 0 && matriz[pos[0]-1][pos[1]].altura <= matriz[pos[0]][pos[1]].altura && (pos[0]-1 < 5 && pos[0]-1 >= 0) && (pos[1] >= 0 && pos[1] < 5)){
      return 1;
    } break;
  case 9:
    if (matriz[pos[0]-1][pos[1]+1].altura > 0 && (matriz[pos[0]-1][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]-1 < 5 && pos[0]-1 >= 0) && (pos[1]+1 >= 0 && pos[1]+1 < 5)){
      return 1;
    } break;
  }
  return 0;
}

void MoverPeca(struct tab matriz[Tam][Tam], int pos[2], int mov){
  switch (mov){
  case 1:
    if (matriz[pos[0]+1][pos[1]-1].altura > 0 && (matriz[pos[0]+1][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]+1 < 5 && pos[0]+1 >= 0) && (pos[1]-1 >= 0 && pos[1]-1 < 5)){
      matriz[pos[0]+1][pos[1]-1].jogador = matriz[pos[0]][pos[1]].jogador;
      matriz[pos[0]+1][pos[1]-1].altura += matriz[pos[0]][pos[1]].altura;
      matriz[pos[0]][pos[1]].jogador = 4;
      matriz[pos[0]][pos[1]].altura = 0;
    }
    break;
  case 2:
    if (matriz[pos[0]+1][pos[1]].altura > 0 && (matriz[pos[0]+1][pos[1]].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]+1 < 5 && pos[0]+1 >= 0) && (pos[1] >= 0 && pos[1] < 5)){
      matriz[pos[0]+1][pos[1]].jogador = matriz[pos[0]][pos[1]].jogador;
      matriz[pos[0]+1][pos[1]].altura += matriz[pos[0]][pos[1]].altura;
      matriz[pos[0]][pos[1]].jogador = 4;
      matriz[pos[0]][pos[1]].altura = 0;
    } break;
  case 3:
    if (matriz[pos[0]+1][pos[1]+1].altura > 0 && (matriz[pos[0]+1][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]+1 < 5 && pos[0]+1 >= 0) && (pos[1]+1 >= 0 && pos[1]+1 < 5)){
      matriz[pos[0]+1][pos[1]+1].jogador = matriz[pos[0]][pos[1]].jogador;
      matriz[pos[0]+1][pos[1]+1].altura += matriz[pos[0]][pos[1]].altura;
      matriz[pos[0]][pos[1]].jogador = 4;
      matriz[pos[0]][pos[1]].altura = 0;
    } break;
  case 4:
    if (matriz[pos[0]][pos[1]-1].altura > 0 && (matriz[pos[0]][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0] < 5 && pos[0] >= 0) && (pos[1]-1 >= 0 && pos[1]-1 < 5)){
      matriz[pos[0]][pos[1]-1].jogador = matriz[pos[0]][pos[1]].jogador;
      matriz[pos[0]][pos[1]-1].altura += matriz[pos[0]][pos[1]].altura;
      matriz[pos[0]][pos[1]].jogador = 4;
      matriz[pos[0]][pos[1]].altura = 0;
    } break;
  case 6:
    if (matriz[pos[0]][pos[1]+1].altura > 0 && (matriz[pos[0]][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0] < 5 && pos[0] >= 0) && (pos[1]+1 >= 0 && pos[1]+1 < 5)){
      matriz[pos[0]][pos[1]+1].jogador = matriz[pos[0]][pos[1]].jogador;
      matriz[pos[0]][pos[1]+1].altura += matriz[pos[0]][pos[1]].altura;
      matriz[pos[0]][pos[1]].jogador = 4;
      matriz[pos[0]][pos[1]].altura = 0;
    } break;
  case 7:
    if (matriz[pos[0]-1][pos[1]-1].altura > 0 && (matriz[pos[0]-1][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]-1 < 5 && pos[0]-1 >= 0) && (pos[1]-1 >= 0 && pos[1]-1 < 5)){
      matriz[pos[0]-1][pos[1]-1].jogador = matriz[pos[0]][pos[1]].jogador;
      matriz[pos[0]-1][pos[1]-1].altura += matriz[pos[0]][pos[1]].altura;
      matriz[pos[0]][pos[1]].jogador = 4;
      matriz[pos[0]][pos[1]].altura = 0;
    } break;
  case 8:
    if (matriz[pos[0]-1][pos[1]].altura > 0 && matriz[pos[0]-1][pos[1]].altura <= matriz[pos[0]][pos[1]].altura && (pos[0]-1 < 5 && pos[0]-1 >= 0) && (pos[1] >= 0 && pos[1] < 5)){
      matriz[pos[0]-1][pos[1]].jogador = matriz[pos[0]][pos[1]].jogador;
      matriz[pos[0]-1][pos[1]].altura += matriz[pos[0]][pos[1]].altura;
      matriz[pos[0]][pos[1]].jogador = 4;
      matriz[pos[0]][pos[1]].altura = 0;
    } break;
  case 9:
    if (matriz[pos[0]-1][pos[1]+1].altura > 0 && (matriz[pos[0]-1][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]-1 < 5 && pos[0]-1 >= 0) && (pos[1]+1 >= 0 && pos[1]+1 < 5)){
      matriz[pos[0]-1][pos[1]+1].jogador = matriz[pos[0]][pos[1]].jogador;
      matriz[pos[0]-1][pos[1]+1].altura += matriz[pos[0]][pos[1]].altura;
      matriz[pos[0]][pos[1]].jogador = 4;
      matriz[pos[0]][pos[1]].altura = 0;
    } break;
  }
}

int main(void){
  srand(time(NULL));
  int player[4][5];
  struct tab tabuleiro[Tam][Tam];

  int jogadorAtual;

  int menu = 0;

  do{
    limparTela();
    printf("-=-=-=-=-=-=-=-=-=-=-\n1 - Jogar\n2 - Regras\n3 - Sair\n-=-=-=-=-=-=-=-=-=-=-\nO que deseja fazer?\t");
    scanf("%d", &menu);
    if (menu == 1){
      iniciarJogo(tabuleiro, player, jogadorAtual);
      getch();
    } else if (menu == 2){
      printf("2");
      getch();
    } else if (menu == 3){
      break;
    } else {
      menu = 1;
      printf("Digite uma opcao valida\n");
      getch();
      continue;
    }
  } while (menu > 0 && menu < 4);
}