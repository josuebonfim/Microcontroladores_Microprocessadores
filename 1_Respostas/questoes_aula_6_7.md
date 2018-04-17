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
 
;s = R1
 
raiz_quadrada:      cmp #2, R15
                    jge raiz_nao_trivial
                    ret
raiz_nao_trivial:   push R5       ; empurra r5 para a pilha
                    push R6       ; emurra r6 para a pilha
                    mov.w R15, R5 ; joga s que estah em r5 para r15
                    inc R5        ; s += 1
                    rra R5        ; s = s/2
                    clr R6        ; i = 0
raiz_loop:          cmp #1000, R6 ; i == 1000?
                    jge raiz_fim  ; se sim, vai para o final
                    push R15      ; empurra r15 para a pilha
                    mov.w R5, R14 ; joga s para r14
                    call divisao  ; implementa s/x
                    add.w R15, R5 ; soma o resultado da divisao com x
                    rra R5        ; divide x/2
                    pop R15       ; recupera o valor de R15 da pilha
                    inc R6        ; incrementa o contador
                    jmp raiz_loop ; volta para o loop da raiz
raiz_fim:           mov R5, R15
                    pop R6
                    pop R5
                    ret



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

pot_loop:         push R5       ; joga R5 na pilha
                  push R6       ; joga R6 na pilha
                  mov.w R15, R5 ; joga o valor de x de R15 para R5
                  mov.w R14, R6 ; joga o valor de n de R14 para R6
if_loop:          tst R6        ; verifica se n = 0
                  jne else_loop ;pula para o Else
                  mov.w #1, R15
                  ret
else_loop:        cmp R6, #1
                  jge pot_fim
while_loop:       call multi_loop
                  dec R6
                  jmp while_loop
pot_fim:          pop R6
                  pop R5
                  ret
                  
multi_loop:       mov.w R15, R13
                  add.w R13, R15
                  dec R14
                  tst R14
                  jl multi_loop
                  ret
                  
3. Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula a divisão de a por b, onde a, b e o valor de saída 
são inteiros de 16 bits. a e b são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá ser 
fornecida através do registrador R15.

divisao           clr R13         ; auxiliar k  = 0
                  clr R12         ; contador q = 0
div_loop:         add.w R14, R13  ; k = k + b
                  inc R12         ; q += 1
                  cmp R13, R15    ; compara o auxiliar k com a
                  jge div_loop    ; se k >= a 
                  dec R12
                  mov.w R12, R15
                  ret
                  
                  
4. Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula o resto da divisão de a por b, onde a, b e o valor de 
saída são inteiros de 16 bits. a e b são fornecidos através dos registradores R15 e R14, respectivamente, e a saída deverá 
ser fornecida através do registrador R15.

resto_div         clr R13         ; auxiliar k  = 0
                  clr R12         ; contador q = 0
div_loop:         add.w R14, R13  ; k = k + b
                  inc R12         ; q += 1
                  cmp R13, R15    ; compara o auxiliar k com a
                  jge div_loop    ; se k >= a 
                  sub.w R13, R15  ; a = a - b
                  add.w R14, R15  ; a = a + b
                  ret
                  

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

primo:          push R5 ;x
                push R6 ; limite
                mov.w R15, R5
                clr R13    ;i = 0
                call raiz_quadrada
                mov.w R15, R6
                
for:            mov.w R5, R15
                mov.w R13, R14
                call resto_div
if_loop:        tst R15
                jne else_loop
                clr R15
                jmp for_inc
else_loop:      mov.w #1, R15
                jmp for_inc              
for_inc:        inc R13           ; i++
                cmp R13, R6
                jeq for_final
                jmp for
for_final:      pop R6
                pop R5
                ret
                

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
até o termo n = 20. O protótipo da função é double ExpTaylor(double x); 

double fatorial(int n);

double ExpTaylor(double x){
	double sum = 0;
	int n = 0;

	for (n = 0; n < 20; n++){

		sum+= (x**n/fatorial(n));

	}

	return sum;
}

double fatorial(int n){
	if (n < 1){

		return 1;

	}else{

		return n * fatorial(n-1);

	}
}


(b) Escreva a sub-rotina equivalente na linguagem 
Assembly do MSP430, mas considere que os valores de entrada e de saída são inteiros de 16 bits. A variável de entrada é 
fornecida pelo registrador R15, e o valor de saída também.

double fatorial(int n);

double ExpTaylor(double x){
	double sum = 0;
	int n = 0;

	for (n = 0; n < 20; n++){

		sum+= (x**n/fatorial(n));

	}

	return sum;
}

double fatorial(int n){
	if (n < 1){

		return 1;

	}else{

		return n * fatorial(n-1);

	}
}

8. Escreva uma sub-rotina na linguagem Assembly do MSP430 que indica se um vetor esta ordenado de forma decrescente. Por 
exemplo: [5 4 3 2 1] e [90 23 20 10] estão ordenados de forma decrescente. [1 2 3 4 5] e [1 2 3 2] não estão. O primeiro 
endereço do vetor é fornecido pelo registrador R15, e o tamanho do vetor é fornecido pelo registrador R14. A saída deverá 
ser fornecida no registrador R15, valendo 1 quando o vetor estiver ordenado de forma decrescente, e valendo 0 em caso 
contrário.

crescente:
	push.w R5
	push.w R6
	mov.w R15, R6 ; R6 = &a[0]
	mov.w R14, R5; R5 = len(a)
	mov.w R6 ,R14
	incd.w R14

loop_compara:
	cmp R15, R14
	jl Nao_dec ; se a(x+1)<a(x), não é decrescente
	incd.w R15
	incd.w R14
	dec.w R5
	cmp R5, #0
	jne loop_compara ; se R5 = 0, é decrescente

decrescente:
	pop.w R6
	pop.w R5
	mov.w #1, R15
	ret

nao_decrescente:
	pop.w R6
	pop.w R5
	clr R15
	ret

9. Escreva uma sub-rotina na linguagem Assembly do MSP430 que calcula o produto escalar de dois vetores, a e b. O primeiro 
endereço do vetor a deverá ser passado através do registrador R15, o primeiro endereço do vetor b deverá ser passado 
através do registrador R14, e o tamanho do vetor deverá ser passado pelo registrador R13. A saída deverá ser fornecida no 
registrador R15.

Prod_Int:
	push R5 ; guarda R5 na pilha
	mov.w R14, R5 ; R5 = &b(0)
	push R6 ; guarda R6 na pilha
	mov.w R15, R6 ; R6 = &a(0)

	clr R12 ; R12 = 0

PI_Loop:
	mov.w 0(R6), R15
	mov.w 0(R5), R14
	call Multiplica ; r15 = R15 * R14
	add.w R15, R12
	incd.w R6
	incd.w R5
	dec.w R13

Primo_Loop_End:
	mov.w R12, R15
	pop R6
	pop R5
	ret

10. (a) Escreva uma função em C que indica se um vetor é palíndromo. Por exemplo: [1 2 3 2 1] e [0 10 20 20 10 0] são 
palíndromos. [5 4 3 2 1] e [1 2 3 2] não são. Se o vetor for palíndromo, retorne o valor 1. Caso contrário, retorne o 
valor 0. O protótipo da função é:

int Palindromo(int vetor[ ], int tamanho);

int Palindromo(int vetor[], int tamanho)
{
	int i, result;
	for( i = 0 ; i < tamanho/2; i ++)
	{
		if (a[i] == a[tamanho - 1 - i])
		{
			result = 0;
		} else
		{
			return = 1;
		}
	return result;
}

(b) Escreva a sub-rotina equivalente na linguagem Assembly do MSP430. O endereço do vetor de entrada é dado pelo regis-
trador R15, o tamanho do vetor é dado pelo registrador R14, e o resultado é dado pelo registrador R15.

palindromo:     push R6
                mov.w R14, R6
                rra R6          ;r6 = tamanho/2
                clr R13         ;i = 0
                mov.w R6, R12 
                dec R12         ;r12 = tamanho/2 - 1
                add.w R15, R12  ;r12 = &a[tamanho/2 - 1] 
for_loop:       cmp R13, R6
		jge fim
		cmp 0(R15), 0(R12)
		jne for_fim
		add.w #2, R15
		sub.w #2, R12
		inc.w R13
		jmp for_loop
for_fim:	mov.w #1, R15
		ret
fim:		clr R15
		ret
		

		
                
