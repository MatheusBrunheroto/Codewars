#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Minha ideia final foi, usar strlen(observed), e com um ponteiro percorrendo observed "comparar os caracteres com
   o banco de dados" (na prática não foi isso efetivamente), descobrir o número máximo de combinações possíveis, e atribuir
   a int max, pois count é size_t, muito ruim de trabalhar com o resto do algorítimo. Após isso, novamente com um ponteiro
   comparar os valores com o banco de dados real, e através disso enviar os valores do banco de dados para retornar
   todas as possibilidades através da função results, e transformar char ** em const char **, para retornar à main corretamente */


char ** results(int total, int max, int size, int sel, int pos_x, char ** pos, char ** data, int decimal_place ){
  
   /* Repetições enquanto i < max, max é o valor total de combinações de cada pos_x (matrizes do banco de dados), para que serve o segundo loop?
    ele faz com que dependendo da casa decimal que o número para ser combinado esteja, demore mais até que avance no banco de dados pos_x.
    então se por exemplo, o valor recebido na outra função é 11, sua sel (valor que limita a linha da matriz pos_x) = 0, na função o loop
    ira percorrer somente pos[0][j], j aumenta a cada iteração do primeiro loop em função da velocidade determinada pelo segundo. O que acaba acontecendo é que,
    primeiro a função results vai receber "1", e esse "1" está marcado com a casa decimal "1", ou seja dezenas. Como podem ver na função, escrevi que 
    k <  total/pos_x, assim como descobri max através de sucessivas multiplicações,desmontei novamente com sucessivas divisões para conseguir
    acertar o número de repetições que cada casa decimal deve seguir, , se pos_x representa pos_3, essa função fará com que o segundo loop 
    se repita enquanto total/pos_x > 0, retornando no caso de "11", "1" (3x), "2" (3x), "4"(3x) na primeira chamada onde 
    results[0 e 1][0]-> (J DETERMINADO ATRAVÉS DE UMA EQUAÇÃO) decimal_place = 1 (dezenas), e "1", "2", "4" (3x), na segunda chamada onde 
    results[0 e 1][1]-> (J DETERMINADO ATRAVÉS DE UMA EQUAÇÃO) decimal_place = 0 (unidades). */
  
  for(int i = 0, j = 0; i < max; j++){
    if(j == pos_x){
      j = 0;
    }
    else{}
    for(int k = 0; k < total/pos_x; k++, i++){
      data[i][size - 1 - decimal_place] = pos[sel][j];  
    }
  }
  return data;
}

const char** get_pins(const char* observed, size_t* count) {
  int max = 1;
  
  /* 1º - Achar o valor de Count, ou seja, N total de combinações */
  
  const char * observed_ptr = observed; // Ponteiro para percorrer observed sem correr o risco de perder o endereço inicial
  for(size_t i = 0; i < strlen(observed);i++, observed_ptr++){
    if(*observed_ptr == '0'){
        max *= 2;
    }
    else if(*observed_ptr == '1' || *observed_ptr == '3' || *observed_ptr == '7' || *observed_ptr == '9' ){
        max *= 3;
    }
    else if(*observed_ptr == '2' || *observed_ptr == '4' || *observed_ptr == '6'){
        max *= 4;
    }
    else{
        max *= 5;
    }
  }

  int x = strlen(observed);  // Defini "x" e "y" para não trabalhar
  int y = max;               // com size_t, e facilitar a vizualização
  
   /* 2º Banco de dados pos_x = {x e N| 2 <= x <= 5} seguido de sua alocação dinâmica,
      para conseguir trabalhar com ponteiros dentro das funções, pois não da pra fazer uma passagem
      por referência mais de uma vez dentro da função usando a alocação estática */

  char pos_2[1][2] = {
    {'0', '8'}};                                                     // 0
  char **pos_2_dyn = (char **)malloc(sizeof(char *) * 1); 
  for (int i = 0; i < 1; i++) {
    pos_2_dyn[i] = (char *)malloc(sizeof(char) * 2); 
    for (int j = 0; j < 2; j++) {
      pos_2_dyn[i][j] = pos_2[i][j]; 
    }
  }

  char pos_3[4][3] = {
    { '1', '2', '4' },                                               // 1 
    { '2', '3', '6' },                                               // 3
    { '4', '7', '8' },                                               // 7
    { '6', '8', '9' }};                                              // 9
  char **pos_3_dyn = (char **)malloc(sizeof(char *) * 4); 
  for (int i = 0; i < 4; i++) {
    pos_3_dyn[i] = (char *)malloc(sizeof(char) * 3); 
    for (int j = 0; j < 3; j++) {
      pos_3_dyn[i][j] = pos_3[i][j]; 
    }
  }
  
  char pos_4[3][4] = {
    {'1', '2', '3', '5'},                                            // 2
    {'1', '4', '5', '7'},                                            // 4
    {'3', '5', '6', '9'}};                                           // 6
  char **pos_4_dyn = (char **)malloc(sizeof(char *) * 3); 
  for (int i = 0; i < 3; i++) {
    pos_4_dyn[i] = (char *)malloc(sizeof(char) * 4); 
    for (int j = 0; j < 4; j++) {
      pos_4_dyn[i][j] = pos_4[i][j]; 
    }
  }
  
  char pos_5[2][5] = {
    {'2', '4', '5', '6', '8'},                                       // 5
    {'0', '5', '7', '8', '9'}};                                      // 8
   char **pos_5_dyn = (char **)malloc(sizeof(char *) * 2); 
  for (int i = 0; i < 2; i++) {
    pos_5_dyn[i] = (char *)malloc(sizeof(char) * 5); 
    for (int j = 0; j < 5; j++) {
      pos_5_dyn[i][j] = pos_5[i][j]; 
    }
  }

  observed_ptr = observed; // Retomada do endereço de observed em observed_ptr, que havia sido alterado
  
    /* 3º - Alocação dinâmica de uma matriz char para trabalhar dentro da função results */
  
  char **data = (char **)malloc(sizeof(char *) * y); 
  for (int i = 0; i < y; i++) {
    data[i] = (char *)malloc(sizeof(char) * x);
  }
  
   /* 4º - Trabalhar letra por letra de observed dentro da função results
      enviando os dados necessários para os cálculos */
  
  for(int sel = 0, n = 0, decimal_place = x - 1, total = max; n < x; n++, decimal_place--, observed_ptr++){  

    if(*observed_ptr == '0'){

      sel = 0;    
      
      results(total, y, x, sel, 2, pos_2_dyn, data, decimal_place);
      total = total / 2;
    }
    else if(*observed_ptr == '1' || *observed_ptr == '3' || *observed_ptr == '7' || *observed_ptr == '9'){ 
      if(*observed_ptr == '1'){
       sel = 0;
       }
      else if(*observed_ptr == '3'){
       sel = 1;
       }
      else if(*observed_ptr == '7'){
       sel = 2;
       }
      else{
       sel = 3;
      }
      results(total, y, x, sel, 3, pos_3_dyn, data, decimal_place);
      total = total / 3;

     }
     else if(*observed_ptr == '2' || *observed_ptr == '4' || *observed_ptr == '6'){
      if(*observed_ptr == '2'){
        sel = 0;
       }
      else if(*observed_ptr == '4'){
       sel = 1;
       }
      else{
       sel = 2;
       }
      results(total, y, x, sel, 4, pos_4_dyn, data, decimal_place);
      total = total / 4;

     }
     else{
        if(*observed_ptr == '5'){
          sel = 0;
        }
        else{
          sel = 1;
        }
      results(total, y, x, sel, 5, pos_5_dyn, data, decimal_place);
       total = total / 5;
    }  
  }   
 
   /* 5º - Adiciona '\0' ao fim de todos os valores retornados de results */
  
  for (int i = 0; i < y; i++) {
    for(int j = 0; j <= x; j++){
      if(j == x){
      data[i][j] = '\0';
      }
      else{}
    }
  }
  
   /* 6º - Alocação dinâmica de um const char, que não pode ser alterado, portanto durante a segunda etapa
      de sua alocação, devemos fazer o endereço apontado anteriormente desreferenciado ter os mesmos endereços
      de data, pois const char é uma variável read only */
  
  const char **results = (const char **)malloc(sizeof(char *) * y); 
  for (int i = 0; i < y; i++) {
    results[i] = data[i];
  }

  *count = max; // "Burlando" o sistema pois trabalhar com size_t é lamentável
  return results;
}


void free_pins(const char ** pins){
    free(pins);
}