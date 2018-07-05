//Protótipo do produto final
/*

Mostrar no LCD: 
"Para iniciar, pressione o botão"

Assim que pressionado:
Motrar no LCD:
"Abrindo bureta"
depois, chamar a função:
bureta (flag, n);
	função para abrir ou fechar a bureta, onde:
	n => número de passos necessários para abrir ou fechar
		 a bureta
	if(flag);
		abre;
	else
		fecha;
esperar por mais 2 segundos

Mostrar no LCD
	"ligando o mixer"
chamar a função:
mixer(flag);
	função para ligar ou desligar o mixer
	if (flag == 1)
		liga;
	else
		desliga;
e esperar por 2 segundos

Mostrar no LCD: 
"Aguarde detecção"

agora, espera a detecção da cor
while(!detection)
	detection = color_detection();


quando detectar, chamar as funções:
bureta (!flag, n);
mixer(!flag);
e mostrar no LCD 
"    Processo 
    Finalizado"
*/