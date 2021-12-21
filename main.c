#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
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

// Struct que sera usado no tabuleiro
struct tab{
  int altura;
  int jogador;
};

// Essa função inicia o jogo e chama todas as outras funções necessarias em ordem
void iniciarJogo(struct tab matriz[Tam][Tam], int player[4][5], int jogadorAtual){
  jogadorAtual = 0;
  gerarPlayers(player);
  gerarTabuleiro(matriz, player);
  exibeTabuleiro(matriz, jogadorAtual);
}

// Texto coloridinho, obrigado Roberto
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

// Limpa tela
void limparTela(){
    system("cls");
}

// Eu sei que num = rand() % 4 já gera um número entre 0 e 4 mas fiz essa função pq vai que eu preciso
// de outros numeros aleatórios, ai ja posso botar logo o intervalo que eu quiser (PS.: não precisei)
int gerarNum(int x,int y){
    int num;
    do{
        num = rand() % 10;
    }while(num < x || num > y);
    return num;
}

// Essa função faz uma matriz de players onde a linha 0 (player 1) é preenchida com 0 (id do player 1), etc...
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

// Essa função gera o tabuleiro, embaralha e deixa tudo pronto pra jogar
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

// Essa função converte texto em uma posição acessível para a matriz (Ex.: "a3" -> {0, 2})
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

// Essa função retorna 0 ou 1 para se a peça selecionada é válida ou não (tem movimentos possíveis ao redor)
int validaPeca(struct tab matriz[Tam][Tam], int pos[2]){
  int qtdMov = 0;
  if (matriz[pos[0]-1][pos[1]-1].altura >= 1 && (matriz[pos[0]-1][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]-1 < 4 && pos[0]-1 >= 0) && (pos[1]-1 >= 0 && pos[1]-1 < 4)) qtdMov++;
  if (matriz[pos[0]-1][pos[1]].altura >= 1 && (matriz[pos[0]-1][pos[1]].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]-1 < 5 && pos[0]-1 >= 0) && (pos[1] >= 0 && pos[1] < 5)) qtdMov++;
  if (matriz[pos[0]-1][pos[1]+1].altura >= 1 && (matriz[pos[0]-1][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]-1 < 5 && pos[0]-1 >= 0) && (pos[1]+1 >= 0 && pos[1]+1 < 5)) qtdMov++;
  if (matriz[pos[0]][pos[1]-1].altura >= 1 && (matriz[pos[0]][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0] < 5 && pos[0] >= 0) && (pos[1]-1 >= 0 && pos[1]-1 < 4)) qtdMov++;
  if (matriz[pos[0]][pos[1]+1].altura >= 1 && (matriz[pos[0]][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0] < 5 && pos[0] >= 0) && (pos[1]+1 >= 0 && pos[1]+1 < 5)) qtdMov++;
  if (matriz[pos[0]+1][pos[1]-1].altura >= 1 && (matriz[pos[0]+1][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]+1 <= 5 && pos[0]+1 >= 0) && (pos[1]-1 >= 0 && pos[1]-1 < 4)) qtdMov++;
  if (matriz[pos[0]+1][pos[1]].altura >= 1 && (matriz[pos[0]+1][pos[1]].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]+1 < 5 && pos[0]+1 >= 0) && (pos[1] >= 0 && pos[1] < 5)) qtdMov++;
  if (matriz[pos[0]+1][pos[1]+1].altura >= 1 && (matriz[pos[0]+1][pos[1]+1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]+1 < 5 && pos[0]+1 >= 0) && (pos[1]+1 >= 0 && pos[1]+1 < 5)) qtdMov++;
  if (qtdMov>0){
    return 1;
  } else {
    return 0;
  }
}

// Essa função retorna 0 ou 1 para se o movimento escolhido pelo jogador é válido
int validaMov(struct tab matriz[Tam][Tam], int pos[2], int mov){
  switch (mov){
  case 1:
    // cada um desses if verifica se a altura do destino é maior que 0, menor que a peça escolhida e se está dentro do tabuleiro
    if (matriz[pos[0]+1][pos[1]-1].altura > 0 && (matriz[pos[0]+1][pos[1]-1].altura <= matriz[pos[0]][pos[1]].altura) && (pos[0]+1 <= 5 && pos[0]+1 >= 0) && (pos[1]-1 >= 0 && pos[1]-1 < 5)){
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

// Essa função percorre o tabuleiro verificando se o jogador atual tem peças suas que ainda são validas para jogo (Eu sei que não precisava da variavel "pecasEmJogo" e dava pra fazer mais facil, mas eu botei pra por um printf e poder ver se ta funcionando 100% ai to com preguiça de mudar, dx assim mesmo)
int jogadorEmJogo(struct tab matriz[Tam][Tam], int jogadorAtual){
  int pos[2], pecasEmJogo = 0;
  for (int i = 0; i < Tam; i++){
    for (int j = 0; j < Tam; j++){
      if (matriz[i][j].jogador == jogadorAtual){
        pos[0] = i;
        pos[1] = j;
        if (validaPeca(matriz, pos)){
          pecasEmJogo++;
        }
      }
    }
  }
  
  if (pecasEmJogo > 0){
    return 1;
  } else {
    return 0;
  }
}

// Essa função move uma peça após ela ter sido validada e o movimento aprovado
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

// Essa função faz a troca de turnos bem autoexplicativo
int trocaTurno(int jogadorAtual){
  if (jogadorAtual >= 3){
    jogadorAtual = 0;
  } else {
    jogadorAtual++;
  }
  return jogadorAtual;
}

// Essa função exibe o tabuleiro
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

// Essa função verifica o fim da partida
int fimPartida(struct tab matriz[Tam][Tam]){
  int pos[2], pecasEmJogo = 0;
  for (int i = 0; i < Tam; i++){
    for (int j = 0; j < Tam; j++){
      pos[0] = i;
      pos[1] = j;
      if (validaPeca(matriz, pos)){
        pecasEmJogo++;
      }
    }
  }
  if (pecasEmJogo > 0){
    return 0;
  } else {
    return 1;
  }
}

// Caso a partida tenha chegado ao fim, essa função me diz o vencedor e o placar
void verificarVencedor(struct tab matriz[Tam][Tam]){
  int placar[4] = {0, 0, 0, 0};
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < Tam; j++){
      for (int k = 0; k < Tam; k++){
        if (matriz[j][k].jogador == i){
          placar[i] = placar[i] + matriz[j][k].altura;
        }
      }
    }
  }

  int maior = placar[0], vencedor = 0;
    for (int i = 0; i < 4; i++){
        if (placar[i] >= maior){
            maior = placar[i];
            vencedor = i;
        }
    }

  printf("Vencedor:\njogador"); textoColorido(vencedor+1, vencedor); printf("\n\nPlacar total:\n");
  for (int i = 0; i < 4; i++){
    printf("jogador "); textoColorido(i+1, i); printf(": %d\n", placar[i]);
  }
  printf("Pressione Enter para ser redirecionado ao menu");
}

// Essa função é igual a mostrarTabuleiro a unica diferença é que no final eu chamo a logica() pra fazer um loop para rodar o jogo, a outra eu uso quando vou dar um CLS pq se eu chamar essa aqui ela reseta a lógica.
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

// Essa função é a lógica no jogo e no final chama a exibeTabuleiro() para fazer um loop para rodar o jogo
void logica(struct tab matriz[Tam][Tam], int jogadorAtual){
  if (fimPartida(matriz)){
    getch();
    limparTela();
    verificarVencedor(matriz);
    getch();
  } else {
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
      getchar();
      while (validaMov(matriz, pos, mov) == 0){
        printf("\nEscolha uma direcao VALIDA para ir:\t");
        scanf("%d", &mov);
        getchar();
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
    printf("\nJogador "); textoColorido(jogadorAtual+1, jogadorAtual); printf(" sem peças");
    getch();
    jogadorAtual = trocaTurno(jogadorAtual);
    exibeTabuleiro(matriz, jogadorAtual);
    }
  }
}

// Função main normal, sem segredo, só a main mesmo
int main(void){
  //setLocale no meu VSCode nao funciona, essa parada ai deu certo, obrigado stackOverflow
  SetConsoleOutputCP(65001);

  srand(time(NULL));
  int player[4][5];
  struct tab tabuleiro[Tam][Tam];

  int jogadorAtual;

  int menu = 0;

  do{
    limparTela();
    printf("-=-=-=-=-=-=-=-=-=-=-\n1 - Jogar\n2 - Regras\n3 - Requisitos mínimos\n4 - Sair\n-=-=-=-=-=-=-=-=-=-=-\nO que deseja fazer?\t");
    scanf("%d", &menu);
    getchar();
    if (menu == 1){
      iniciarJogo(tabuleiro, player, jogadorAtual);
      getch();
    } else if (menu == 2){
      limparTela();
      printf("Cappuccino é um jogo abstrato para quatro jogadores cujo objetivo é ter a maior\nquantidade de pilhas sobre seu domínio ao final da partida.\nEsse objetivo é alcançado empilhando peças durante a partida.\nCada Jogador começa com 5 peças sendo elas posicionadas aleatoriamente no tabuleiro 5x5.\n\n1 - Você só pode mecher peças suas.\n2 - Uma peça só pode se mover para cima de outra peça, sendo impossível se mover para um espaço vazio.\n3 - Você só pode empilhar peças de altura menor ou igual a sua.\n4 - O fim da partida será quando restar apenas um jogador ou não houver mais movimentos possíveis.\n5 - Em caso de empate, a ordem inversa dos turnos será usada para escolher um vencedor.\n(jogador 4 tem vantagem sobre o 3, o 3 sobre o 2, etc)\n\nPressione Enter para voltar ao menu...");
      getch();
    } else if(menu == 3){
      limparTela();
      printf("Requisitos mínimos\n\nProcessador: Intel 4004\nPlaca de vídeo: Intel UHD Graphics 1\nMemória RAM: 2MB\nEspaço em disco: 60KB\n\nRequisitos recomendados: (ta um pouco pesado)\n\nProcessador: Ryzen 9 5950X 3.4GHz\nPlaca de vídeo: AMD Radeon RX 6900 XT\nMemória RAM: 32GB\nEspaço em disco: 1TB\n\nPressione Enter para voltar ao menu...");
      getch();
    } else if (menu == 4){
      break;
    } else {
      menu = 1;
      printf("Digite uma opcao valida\n");
      getch();
      continue;
    }
  } while (menu > 0 && menu < 4);
}