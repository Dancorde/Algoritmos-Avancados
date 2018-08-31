/*
 * Jan-Ken-Puzzle
 *
 * Autores:
 * Danilo Henrique Cordeiro - 6791651
 * Giovanni Attina do Nascimento - 9286614
 * 
 */

#include <stdlib.h>
#include <stdio.h>

#define empty 0
#define rock 1
#define scissor 2
#define paper 3

int main(void){
  int R, C;
  int i, j;

  scanf("%d %d", &R, &C);

  int board[R][C];

  for(i = 0; i < R; i++){
    for(j = 0; j < C; j++){
      scanf("%d", &board[i][j]);
    }
  }

  return 0;
}
