#include "flight_analysis.h"
#include "menus_options.h"
#include "calculo.h"

char *MENU_PRINCIPAL[] = {"MENU_PRINCIPAL","Terminar o programa","Simular o movimento da aeronave","Vizualizar resultados graficos","Outras Opcoes"};
int tamanho_menu_principal = 5;
char *OUTRAS_OPCOES[] = {"OUTRAS OPCOES","Mostrar Parametros/Estado Inicial","Voltar ao Menu Principal"};
int tamanho_outras_opcoes = 3;
char* nome_parametros[14] = {"tempo final da simulacao","passo de integracao dt","area da asa","comprimento da asa","massa da aeronave","aceleracao da gravidade","densidade do ar ao nivel do mar","valor do coeficiente de drag para C1 = 0","fator de eficiencia de Oswald","angulo de ataque","velocidade inicial","gamma","posicao horizontal inicial","altitude inicial"};


int run_menu(int opcao, int menu_number){
	if(menu_number == 1)
	{
		if(opcao == 0)
		{
			return 0;
		}
		if (opcao == 1)
		{ 
			/* Ficheiros e dados a adicionar, constantes dadas, funçoes para as variavei do voo */
			double parametros[14];
			ler_ficheiro(parametros,nome_parametros);
			create_file(parametros);
		}

		if (opcao == 2)
		{
			/* escolher o tipo de grafico, fazer o grafico, biblioteca grafica lsd2 */
		}

		if(opcao == 3)
		{
			system("clear");
			menu(menu_number+1);
			return 0;
		}

		printf("Press Enter to go back to menu\n");
		getchar();
		system("clear");

		menu(menu_number);
		return 0;
	}
	
	if(menu_number == 2)
	{
		if (opcao == 0)
		{ 
			double parametros[14];
			if(!(ler_ficheiro(parametros,nome_parametros))){
				printParametros(parametros, nome_parametros);
			}

			printf("Press Enter to go back to menu\n");
			getchar();
			system("clear");

			menu(menu_number);
		}
		if (opcao == 1)
		{
			menu(menu_number-1);
		}
	}

	return 0;
}


void writeMenu(char* MENU[], int tamanho)
{
	system("clear");
	int i = 0;
	printf("---------------------------------------------------------\n");
	while(i < tamanho)
	{
		if(i) printf("%-3d- %s\n", (i-1), MENU[i]);
		else
		{
			printf("%s\n", MENU[i]);
			printf("---------------------------------------------------------\n");
		}
		i++;
	}
	printf("---------------------------------------------------------\n");
}


void menu (int menu_number){
	char **MENU;
	int tamanho;
	if(menu_number == 1){
		MENU = MENU_PRINCIPAL;
		tamanho = tamanho_menu_principal;
	} 
	if(menu_number == 2){
		MENU = OUTRAS_OPCOES;
		tamanho = tamanho_outras_opcoes;
	} 

	int op;
	writeMenu(MENU, tamanho);
	printf ("\nSeleciona opcao:\n");

	scanf("%d", &op);
	getchar();
	fflush (stdin); /* Limpar o buffer do teclado */

	if(op < 0 || op >= tamanho){
		system("clear");
		printf ("---\nOpcao invalida! Por favor escolha de novo\n---\n");
		menu(menu_number);
		return;
	}
	system("clear");
	run_menu(op,menu_number);
}