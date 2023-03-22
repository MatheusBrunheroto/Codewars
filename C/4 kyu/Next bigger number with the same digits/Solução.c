#include <stdlib.h>
#include <stdbool.h>

/* Ideia final: A partir do ultimo algarismo em sentido ao primeiro, achar o próximo maior através de uma "bolha",
   exemplo: 5(41)23, onde está a bolha, 4 deve ser marcado por ser o primeiro maior a ser encontrado na esquerda dentro da bolha.
   Após isso, deve-se procurar o próximo maior a partir dessa posição em direção ao último algarismo,
   após encontrar deve ser marcado também, e os dois números marcados são trocados. Após troca-los de posição, deve-se colocar
   em ordem os números da primeira marcação + 1 em sentido ao último algarismo. */

long long next_bigger_number(long long n) {
  
  // 1º - Contar o número de dígitos de n
  long long int n_cpy = n;
  int size = 0;
    while (n_cpy > 0) {
      n_cpy = n_cpy / 10;
      size++;
    }
  long long int *div = (long long int *)malloc(size*sizeof(long long int)); 
  long long int *div_aux = (long long int *)malloc(size*sizeof(long long int)); 
  long long int *ptr = div_aux; 

  // 2º - Separar os algarismos em ordem invertida, ex: 1234 -> 4, 3, 2, 1
  int count = 0;
  for (long long int x = 10, y = n; size > 0; y = y / x, ptr++, count++, size--) {
    *ptr = y % x;
  }

  // 3º - Rearranja os algarismos na ordem correta
  for(int i = 0, j = count - 1; i < count; i++, j--){
    div[j] = div_aux[i];
  }
  
  int marc_esquerda = 0, marc_direita = 0;
  long long int bigger = 0, aux;
  bool found = false;

  // 4º - Encontrar a marcação da direita → esquerda
  for(int i = count - 1; i >= 0; i--){
    if(div[i-1] < div[i]){
      marc_esquerda = i - 1;
      found = true;
      break;
    } else {}
  }
  
  // 5º - Encontrar a marcação da esquerda → direita
  for(int i = marc_esquerda, j = i + 1; j < count; j++){
    if(div[j] > div[i]){
      marc_direita = j;
    } else {}
  }
  if(marc_direita == 0){
    found = false;
  }

  // 6º - Trocar os valores marcados nas duas posições
  aux = div[marc_esquerda];
  div[marc_esquerda] = div[marc_direita];
  div[marc_direita] = aux;

  // 7º - Ordenar todos os valores da esquerda → direita a partir da marcação da esquerda + 1
  for(int i = marc_esquerda + 1; i < count; i++){
    for(int j = marc_esquerda + 1; j < count - 1; j++){
      if(div[j+1] < div[j]){
        aux = div[j];
        div[j] = div[j+1];
        div[j+1] = aux;
      }
    }
  }

  // 8º - Transformar o vetor em um único valor inteiro
  long long int dec = 1;
  for(long long int i = 0; i < count - 1; i++){
    dec*=10;
  }
  for(long long int i = 0; i < count; i++){
    bigger += dec*div[i];
    dec = dec / 10;
  }
  
  // 9º - Retornar caso exista, o valor bigger
  if(found != true){
    return -1;
  }
  else{
    return bigger;
  }
  
}