#include <stdio.h>

/* Ideia final: decidi trabalhar com somente 2 variáveis (start, end) pois notei que:

                    [start][start]  →  [start][end]
                    
                          ↑                  ↓
                                             
                     [end][start]   ←   [end][end]

   Então seria possível trabalhar com esses valores, apenas mudando a posição deles na hora de
   atribuir o valor à matriz. */

void spiralize(unsigned n, int spiral[n][n]) {
  int start = 0, end = n - 1;
  unsigned int aux = n;

  /* A primeira linha deve ser inicializada dessa forma pois após o primeiro loop, é necessário usar
     start - 1, ao fazer isso quando start = 0, é acessado o valor '-1' na memória, o qual não existe */
  for (int L = start; L <= end; L++) {
    spiral[start][L] = 1;
  }
  n--;

  while (n > 0) {

    // Loop responsável pela Coluna da Direita : Cima -> Baixo - (↓)
    if (n > 0) {
      for (int C = start + 1; C <= end; C++) {
        spiral[C][end] = 1;
      }
      n--;
    } else {
    }

    // Loop responsável pela Linha Inferior : Direita -> Esquerda - (←)
    if (n > 0) {
      for (int L = end - 1; L >= start; L--) {
        spiral[end][L] = 1;
      }
      n--;
    } else {
    }

    // Loop responsável pela Coluna da Esquerda : Baixo -> Cima - (↑)
    if (n > 0) {
      start += 2;
      for (int C = end; C >= start; C--) {
        spiral[C][start - 2] = 1;
      }
      n--; 
      end -= 2;
    } else {
    }
   
    // Loop responsável pela Linha Superior : Esquerda -> Direita - (→)
    if (n > 0) {

      for (int L = start - 1; L <= end; L++) {
        spiral[start][L] = 1;
      }

      n--;

    } else {
    }
    
  }

  // Coloca '0' em todas as casas que não possuem '1'
  for (unsigned int i = 0; i < aux; i++) {
    for (unsigned int j = 0; j < aux; j++) {
      if (spiral[i][j] != 1) {
        spiral[i][j] = 0;
      } else {
      } 
    }
  }
  
}