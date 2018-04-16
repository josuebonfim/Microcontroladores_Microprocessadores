Para cada questão, escreva funções em C e/ou sub-rotinas na linguagem Assembly do MSP430. Reaproveite funções 
e sub-rotinas de uma questão em outra, se assim desejar. Leve em consideração que as sub-rotinas são utilizadas 
em um código maior, portanto utilize adequadamente os registradores R4 a R11. As instruções da linguagem Assembly 
do MSP430 se encontram ao final deste texto.

1. (a) Escreva uma função em C que calcule a raiz quadrada x de uma variável S do tipo float, utilizando o seguinte 
algoritmo: após n+1 iterações, a raiz quadrada de S é dada por

#include "stdlib.h"
#include "stdio.h"

unsigned int raiz_quadrada(unsigned int s);

int main(int argc, char const *argv[]) {
  unsigned int s, x;
  scanf("%d",&s );
  x = raiz_quadrada(s);
  printf("raiz de %d = %d\n", s, x );
  return 0;
}

unsigned int raiz_quadrada(unsigned int s)
{
  unsigned int x = (s+1)/2, i;
  if (s < 2) {
    return s;
  }else
  {
    for (i = 0; i < 1000; i++)
    x = (x + s/x)/2;
  }
  return x;
}


(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. A variável S é fornecida pelo registrador R15, 
 e a raiz quadrada de S (ou seja, a variável x) é fornecida pelo registrador R15 também.
 
 ;s = R15
 ;i = R14
 
 rai_quadrada:  cmp #2, R15
                
                

2. (a) Escreva uma função em C que calcule x elevado à N-ésima potência, seguindo o seguinte protótipo:

int Potencia(int x, int N);

#include "stdlib.h"
#include "stdio.h"

int Potencia(int x, int n);

int main(int argc, char const *argv[]) {
  int x, n, pot;
  scanf("%d", &x);
  scanf("%d", &n);
  pot = Potencia(x, n);
  printf("%d ^ %d = %d\n", x, n, pot );
}

int Potencia (int x, int n)
{
  int pot = x;
  if (n == 0)
  {
    return 1;
  }else
  {
    while (n > 1) {
      x = x*pot;
      n-- ;
    }
  }
  return x;
}

(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. x e n são fornecidos através dos registradores R15 
e R14, respectivamente, e a saída deverá ser fornecida no registrador R15.

3. Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula a divisão de a por b, onde a, b e o valor de saída 
são inteiros de 16 bits. a e b são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser 
fornecida através do registrador R15.

4. Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula o resto da divisão de a por b, onde a, b e o valor de 
saída são inteiros de 16 bits. a e b são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá 
ser fornecida através do registrador R15.

5. (a) Escreva uma função em C que indica a primalidade de uma variável inteira sem sinal, retornando o valor 1 se o número 
for primo, e 0, caso contrário. Siga o seguinte protótipo:

int Primalidade(unsigned int x);
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

int Primo (int x);

int main(int argc, char const *argv[]) {
  int x, primo;
  scanf("%d", &x);
  primo = Primo(x);
  if (primo) {
    printf("%d eh primo\n", x);
  }else
  {
    printf("%d nao eh primo\n", x);
  }
}

int Primo (int x)
{
  int limite, i;
  limite = (int)sqrt(x);

  for ( i = 0; i < limite; i++) {
    if (x % i == 0) {
      return 0;
    }
    else
    {
      return 1;
    }
  }
}


(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. A variável de entrada é fornecida pelo registrador
R15,e o valor de saída também.

6. Escreva uma função em C que calcula o duplo fatorial de n, representado por n!!. Se n for ímpar, n!! = 135*...n, e se 
n for par, n!! = 246...n. Por exemplo, 9!! = 13579 = 945 e 10!! = 2468*10 = 3840. Além disso, 0!! = 1!! = 1. O protótipo 
da função é:

unsigned long long DuploFatorial(unsigned long long n);
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

unsigned long long duploFatorial (unsigned long long n);

int main(int argc, char const *argv[]) {
  unsigned long long n, duploFac;
  scanf("%llu", &n);
  duploFac = duploFatorial(n);
  printf("%llu\n", duploFac);
}

unsigned long long duploFatorial (unsigned long long n)
{
  int controle;
  int x, i = 1;
  if (n == 0)
  {
    return 1;
  }else
  {
    if (n%2 == 0)
    {
      controle = n/2;
      x = 2;
      while(controle > 0)
      {
        i *= x;
        x += 2;
        controle-- ;
      }
    }else
    {
      controle = (n + 1)/2;
      x = 1;
      while(controle > 0)
      {
        i *= x;
        x += 2;
        controle-- ;
      }
    }
  }
  return i;
}


7. (a) Escreva uma função em C que calcula a função exponencial utilizando a série de Taylor da mesma. Considere o cálculo 
até o termo n = 20. O protótipo da função é double ExpTaylor(double x); (b) Escreva a sub-rotina equivalente na linguagem 
Assembly do MSP430, mas considere que os valores de entrada e de saída são inteiros de 16 bits. A variável de entrada é 
fornecida pelo registrador R15, e o valor de saída também.



8. Escreva uma sub-rotina na linguagem Assembly do MSP430 que indica se um vetor esta ordenado de forma decrescente. Por 
exemplo: [5 4 3 2 1] e [90 23 20 10] estão ordenados de forma decrescente. [1 2 3 4 5] e [1 2 3 2] não estão. O primeiro 
endereço do vetor é fornecido pelo registrador R15, e o tamanho do vetor é fornecido pelo registrador R14. A saída deverá 
ser fornecida no registrador R15, valendo 1 quando o vetor estiver ordenado de forma decrescente, e valendo 0 em caso 
contrário.

9. Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula o produto escalar de dois vetores, a e b. O primeiro 
endereço do vetor a deverá ser passado através do registrador R15, o primeiro endereço do vetor b deverá ser passado 
através do registrador R14, e o tamanho do vetor deverá ser passado pelo registrador R13. A saída deverá ser fornecida no 
registrador R15.

10. (a) Escreva uma função em C que indica se um vetor é palíndromo. Por exemplo: [1 2 3 2 1] e [0 10 20 20 10 0] são 
palíndromos. [5 4 3 2 1] e [1 2 3 2] não são. Se o vetor for palíndromo, retorne o valor 1. Caso contrário, retorne o 
valor 0. O protótipo da função é:

int Palindromo(int vetor[ ], int tamanho);

(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. O endereço do vetor de entrada é dado pelo regis-
trador R15, o tamanho do vetor é dado pelo registrador R14, e o resultado é dado pelo registrador R15.
