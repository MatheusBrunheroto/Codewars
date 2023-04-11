#include <stdlib.h>
#include <stdbool.h>

struct interval {
    int first;
    int second;
} vetor;

// Função que encurta o código, essa sequência seria escrita 4x se não fosse criado a função
void reset(struct interval ** ptr, struct interval ** x, size_t * j){
  (*ptr)->first = 0;
  (*ptr)->second = 0;
  *j = 0;
  *ptr = *x;
}

int sum_intervals(const struct interval *v, size_t n){

  int soma = 0;
  
  struct interval * x = malloc(10*n*sizeof(vetor)); 
  struct interval * ptr = x;
  
  struct interval * maior = malloc(sizeof(vetor));
  int maior_intervalo = 0;
 
  bool saida = false;
  
  size_t aux = 0;

  /* Copia o "const struct interval * v" para "struct interval * x" , justamente para tirar o "const", 
    que só concede permissão de leitura. E ao mesmo tempo encontra o maior intervalo, para separar os intervalos que
    devem ser comparados mais facilmente, ex -> [0,100] contém [1,4] [2,3] [1,20] [30,50], porém não contem [200,300], caso isso aconteca
    o novo loop terá que usar esse intervalo para encontrar os outros, e os que restarem farão parte da soma final. */
  for(size_t i = 0; i < n; i++, ptr++, v++){
    *ptr = *v;
    if(ptr->second - ptr->first > maior_intervalo){
      maior_intervalo = ptr->second - ptr->first - 1;
      *maior = *ptr; // Marca o "first" e "second" do maior intervalo.
    }
  }

  for(size_t i = 0; i < n && saida == false; i++){

    ptr = x;

    for(size_t j = 0; j < n && saida == false; j++){

      // A sequência abaixo verifica se todos os valores são = 0, se for, o código acaba.
      aux = j;
      while(ptr->first == 0 && ptr->second == 0 && aux < n){
        ptr++;
        aux++;
      } 
      if(aux == n){
        saida = true;
      }
     
      // 1.1 menor e valor 1.2 entre 2.1 e 2.2                                                             ↓           ↓
      if(maior->first <= ptr->first && (maior->second <= ptr->second && maior->second >= ptr->first)){ // [-1,10] e [1,14] -> [-1,14] (Parcialmente Inserido)
        maior->first = maior->first; // (-1)
        maior->second = ptr->second; // (14)
        reset(&ptr, &x, &j);
      }

      // 1.2 maior e valor 1.1 entre 2.1 e 2.2                                                                    ↓      ↓
      else if(maior->second >= ptr->second && (maior->first >= ptr->first && maior->first <= ptr->second)){ // [7,20] e [5,14] -> [5,20] (Parcialmente Inserido)
        maior->first = ptr->first; // (5)
        maior->second = maior->second; // (20)
        reset(&ptr, &x, &j);
      }

      // 1.1 menor que 2.1 e 2.2 maior que 1.2                                          ↓  ↓
      else if(maior->first >= ptr->first && ptr->second >= maior->second){ // [5,10] e [0,100] -> [0,100] (Intervalo Contido)
        maior->first = ptr->first; // (0)
        maior->second = ptr->second; // (100)
        reset(&ptr, &x, &j);
      }

      // 1.1 maior que 2.1 e 2.2 menor que 1.2                                 ↓  ↓    
      else if(maior->first <= ptr->first && maior->second >= ptr->second){ // [0,100] e [5,10] -> [0,100] (Intervalo Contido), nesse caso não faz nada, pois "maior" ja possui o valor certo
        reset(&ptr, &x, &j);
      } 
      
      // 1.1 e 1.2 > 2.1 e 2.2 ou 1.1 e 1.2 < 2.2, Isso será tratado no loop seguinte, todos os valores que não entraram nos excedentes
      else{
        ptr++;    
      }
        
      // O novo intervalo "maior" deve ser verificado novamente, ou seja, j = 0, ptr = x. Para isso a função "reset" é chamada.

    }

    soma += maior->second - maior->first;
    maior->first = 0;
    maior->second = 0;
   
    /* O primeiro valor da soma já é determinável pois se tem um intervalo [0,100] e [200,300], eles podem não estar inicialmente conectados, mas pode existir
       intervalos entre eles que os conectem, sim, e eles já terão sido eliminados no loop anterior. O loop a seguir determina o novo maior valor, para
       novamente compararmos os intervalos, isso se repetirá até que não existam mais intervalos maiores. */

    ptr = x;  
    maior_intervalo = 0;
    for(size_t k = 0; k < n; k++){
      if(ptr->first == 0 && ptr->second == 0){        
      }
      else{
        saida = false;
        if(ptr->second - ptr->first  > maior_intervalo){ 
          maior_intervalo = ptr->second - ptr->first ;
          *maior = *ptr; 
        }
      }
      ptr++;
    }
    
  }
  
  return soma;
}
