#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *formacao(int *x, char *y, int *min, int count) {

  /* Nessa função, é definido inicialmente se a primeira parte da string será
     "", " and " ou ", ". 
     Caso "" : somente se y for o primeiro valor ou o ultimo (min). 
     Caso ", ": somente se o próximo valor de y não for 0. 
     Caso " and ": ocorre uma vez, antes do último valor, no caso "min".

     Estrutura : years, days, hours, minutes and seconds.
                 years, days, and minutes. */

  char *aux = (char *)malloc(100 * sizeof(aux));
  char *aux2 = (char *)malloc(100 * sizeof(aux));

  if (x != x - count) { // "x - rep" representa o valor x[0]
    if (x == min) {
      aux = " and ";
    } else {
      aux = ", ";
    }
  } else {
    aux = "";
  }

  if (*x == 0) {
    return "";
  } else if (*x == 1) {
    sprintf(aux2, "%i %s", *x, y);
  } else {
    sprintf(aux2, "%i %ss", *x, y);
  }

  char *result = (char *)malloc(strlen(aux) + strlen(aux2) + 1);
  strcpy(result, aux);
  strcat(result, aux2);

  return result;
}

char *formatDuration(int n) {

  char *Human_Readable = (char *)malloc(1000 * sizeof(char));
  memset(Human_Readable, '\0', 1000);
  char *aux = (char *)malloc(100 * sizeof(char));

  /* O grande loop de "fors" abaixo serve para cada 60 segundos, virar 1 minuto;
   * 60 minutos virar 1 hora; e assim por diante.*/

  int YY = 0, DD = 0, HH = 0, MM = 0, SS = 0;
  int conf = 0;
  SS = n;

  for (int i = 1; i <= SS; i++) {
    if (conf < 1) {                                       // conf == 1 -> Possui segundos
      conf++;
    } else {
    }

    if (i > 59) {
      i = 0;
      SS -= 60;
      MM++;

      for (int j = 0; j <= MM; j++) {
        if (conf < 2) {                                   // conf == 2 -> Possui minutos
          conf++;
        } else {
        }

        if (j > 59) {
          j = 0;
          MM -= 60;
          HH++;

          for (int k = 0; k <= HH; k++) {
            if (conf < 3) {                               // conf == 3 -> Possui horas
              conf++;
            } else {
            }

            if (k > 23) {
              k = 0;
              HH -= 24;
              DD++;

              for (int l = 0; l <= DD; l++) {
                if (conf < 4) {                           // conf == 4 -> Possui dias
                  conf++;

                } else {
                }

                if (l > 364) {
                  l = 0;
                  DD -= 365;
                  YY++;

                  if (conf < 5) {                         // conf == 5 -> Possui anos
                    conf++;

                  } else {
                  }

                } else {
                }
              }
            } else {
            }
          }
        } else {
        }
      }
    } else {
    }
  }

  /* Abaixo separamos os valores descobertos no loop acima em diferentes espaços
     no vetor "x", no uso da função, "formacao", o vetor "x" irá trabalhar
     de cima para baixo, ou seja, de YY à SS, porém há variações que podem
     atrapalhar a simples definição: min = &x[0] e max = &x[4] "max" por
     exemplo, deve ser igual x[count - 1], não sei exatamente qual seria a
     função de "max" tendo em vista que o uso de "x" partirá do mesmo ponto.
     já no caso de "min", armazenará inicialmente &x[0] e passará por um loop
     que vai definir que min = &x[1] caso x[0] == 0, e assim por diante.
     Isso é importante para determinar a posição de " and ", os outros valores
     x[i] != 0 -> ", " e x[i] == 0 será simplesmente ignorado na função
     "formação" */

  if (conf != 0) {
    int x[] = {SS, MM, HH, DD, YY};
    char *y[] = {"second", "minute", "hour", "day", "year"};

    int *min = x;
    int rep = 0;

    for (int i = 0; i < conf; i++) {
      if (x[i] == 0) {
        min++;
      } else {
        break;
      }
    }

    int count = 0;
    for (int i = 4; i >= 0; i--) {
      if (conf > i) {
        strcat(Human_Readable, formacao(&x[i], y[i], min, count));
        count++;
      }
    }

  } else {
    strcpy(Human_Readable, "now");
  }
  
  return Human_Readable;
}