#include <stdlib.h>

// LEIA A DESCRIÇÃO DA SEGUNDA FUNÇÃO "last_digit" PRIMEIRO, DEPOIS LEIA A DO "calc_expoente"

unsigned long int calc_expoente(unsigned long int expoente_antigo,unsigned long int expoente_atual){
  unsigned long int expoente_aux = expoente_atual;
  
  /* O loop abaixo adapta qualquer número > 9 para a divisão por 4 
     Vamos pegar como exemplo -> 12^(30^21)
     30 % 4 != 0    -> Não seria problema se o número 30 anteriormente não estivesse sendo elevado por n > 1
     900 % 4 == 0   

     Então como achar o número suficiente para fazer essa conta? dividindo o expoente 21 por 4, temos o número 1, essa
     é a quantidade de vezes que faremos 30 *= 30.
     Se durante esse loop, o novo expoente já for divisível por 4, o loop deve acabar para diminuir processamento, caso nunca seja
     divisível por 4, o mesmo se adaptará a outro resto de divisão por 4. */
  
  for(unsigned long int i = 0; i <= expoente_antigo % 2; i ++){
    expoente_atual *= expoente_aux; // para no caso de 9³, 9 x 9 = 27 não virar 27 x 27, mantendo o valor 9, ficando 27 x 9
    expoente_atual = expoente_atual % 1000000000; // Pega os últimos 9 algarismos para manter uma certa precisão nas multiplicações sem exceder o limite de memória.

    /* 1) 953.865 x 953.865 = 909.858.438.225,
       2) 909.858.438.225 x 953.865 = 867.882.119.177.489.625 e 
                                                  ↑
       3) 858.438.225 x 953.865 = 818.834.177.489.625
                                          ↑ 
       
       Note que, a multiplicação dos 9 últimos dígitos de 953.865² por 953.865 é igual aos 9 últimos digitos de 953.865³,
       o problema é que 818.834.177.489.625 excede a memória */
 
    if(expoente_atual % 4 == 0){
      return expoente_atual;
    } else {}
  }

  return expoente_atual;
}

int last_digit(const unsigned long int *arr, size_t arr_size) {
  int ultimo_numero = 0, base = 0;
  long int expoente = 0;

  /* "Banco de Dados" dos últimos algarismos de potências de: 2, 3, 4, 7, 8, 9 
      Como foram determinadas as posições? -> cada número possui seu padrão de últimos dígitos, sei que por exemplo:

     2¹ = 2
     2² = 4
     2³ = 8
     2⁴ = 16
     2⁵ = 32, a partir de 6, os últimos algarismos começam a se repetir...

     As posições foram definidas na ordem 2⁴, 2⁵, 2², 2³. Pois 4 % 4 == 0, 5 % 4 == 1, 2 % 4 == 2, 3 % 4 == 3. Dessa forma é
     possível determinar pelo resultado do resto da divisão por 4 o valor do último algarismo, pois todas as possibilidades foram pré-posicionadas no "Banco de Dados"
     para causar esse resultado */

  int numero_2[] = {6, 2, 4, 8}; 
  int numero_3[] = {1, 3, 9, 7}; 
  int numero_4[] = {6, 4};
  int numero_7[] = {1, 7, 9, 3}; 
  int numero_8[] = {6, 8, 4, 2};
  int numero_9[] = {1, 9};

  // Reduzir o processamento caso o primeiro número seja 1, pois 1^0 == 1 e 1^n∈N == 1
  if(arr[0] % 10 == 1 || arr_size == 0){
    return 1;
  }
  else if(arr_size == 1){
    return arr[0] % 10;
  } 
  else{
    
    arr += arr_size - 1; // ptr apontar para o último número do array
    
    unsigned long int expoente_aux = 1, expoente_anterior = 1;
    expoente = *arr;
    arr--;
    for(size_t i = arr_size; i > 1 ; i--, arr--){

      // Calcula o expoente atual caso o anterior seja > 1, para que a divisão por 4 não de problema
      if(expoente_aux > 1){
        expoente = calc_expoente(expoente_aux,expoente);
      } else {}

      base = *arr % 10;

      // Eliminar casos específicos
      if(expoente == 0){
        ultimo_numero = 1;                       // Qualquer número elevado a 0 = 1
      }
      else if(expoente == 1 && base != 0){
          ultimo_numero = base;                  // n^1 = n para qualquer n∈R
      }
      else{
        if(base == 0){
          ultimo_numero = 0;                     // 0 elevado a qualquer exceto ele mesmo numero = 0
        }
        
      /* O resto da divisão do expoente pela quantidade de elementos, gerará um resultado de 
         0 a seu tamanho - 1, que servíra para determinar qual valor do seu "banco de dados" será o último algarismo.
         Dessa forma é possível reduzir x^81 -> x^1, note que essa regra só se aplica ao último digito do vetor, 
         obviamente qualquer número diferente de "1" elevado a 81 é diferente dele mesmo */
        
        else if(base == 2){
          ultimo_numero = numero_2[expoente % 4];
        }
        else if(base == 3){
          ultimo_numero = numero_3[expoente % 4];
        }
        else if(base == 4){
          ultimo_numero = numero_4[expoente % 2]; 
        }
        else if(base == 7){
          ultimo_numero = numero_7[expoente % 4];
        }
        else if(base == 8){
          ultimo_numero = numero_8[expoente % 4];
        }
        else if(base == 9){
          ultimo_numero = numero_9[expoente % 2];
        }
        
        else{ 
          if(base == 1){
            ultimo_numero = 1;
          }
          else if(base == 5){
            ultimo_numero = 5;
          }   
          else{
            ultimo_numero = 6;
          }
        }
      }

      expoente_aux = expoente;
      /* O laço condicional abaixo verifica se por exemplo, a base de fato == 0, ou se só o último algarismo == 0. Então para o expoente não ser "0" 
        caso apenas o último algarismo seja "0", o expoente recebe o valor completo "30", afinal, 2 ^ 0 = 1. 
        E isso serve para qualquer valor que possui mais que um algarismo. */
      if(*arr != *arr % 10){
        expoente = *arr;
      }
      else{
        expoente = ultimo_numero;
      }
    }   
  }

  return ultimo_numero;
}
