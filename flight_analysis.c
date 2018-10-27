#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define PI 

void menu (int* op, char* MENU[], int tamanho, int start);
void writeMenu(char* MENU[], int tamanho, int start);
int ler_ficheiro(float parametros[], char* name[]);
void printParametros (float parametros[], char* nome_parametros[]);


char *MENU_PRINCIPAL[] = {"MENU_PRINCIPAL","Terminar o programa","Simular o movimento da aeronave","Vizualizar resultados graficos","Outras Opcoes"};
int tamanho_menu_principal = 5;
char *OUTRAS_OPCOES[] = {"OUTRAS OPCOES","Mostrar Parametros/Estado Inicial","Voltar ao Menu Principal"};
int tamanho_outras_opcoes = 3;

char* nome_parametros[14] = {"tempo final da simulacao","passo de integracao dt","area da asa","comprimento da asa","massa da aeronave","aceleracao da gravidade","densidade do ar ao nivel do mar","valor do coeficiente de drag para C1 = 0","fator de eficiencia de Oswald","angulo de ataque","velocidade inicial","gamma","posicao horizontal inicial","altitude inicial"};

int main ()
{
	printf("\n");
	int opcao;
	menu(&opcao, MENU_PRINCIPAL, tamanho_menu_principal, 0);

	if (opcao == 1)
	{ 
		/* Ficheiros e dados a adicionar, constantes dadas, funçoes para as variavei do voo */
		float parametros[14];

		ler_ficheiro(parametros,nome_parametros);
		
	}
		

	if (opcao == 2)
	{
		/* escolher o tipo de grafico, fazer o grafico, biblioteca grafica lsd2 */
	}

	if (opcao == 4)
	{
		float parametros[14];
		ler_ficheiro(parametros,nome_parametros);
		printParametros(parametros, nome_parametros);
	}

	printf("---------------\nFim do programa\n---------------\n");
	return 0;
}

void writeMenu(char* MENU[], int tamanho, int start)
{
	int i = 0;
	printf("---------------------------------------------------------\n");
	while(i < tamanho)
	{
		if(i) printf("%-3d- %s\n", (i+start-1), MENU[i]);
		else
		{
			printf("%s\n", MENU[i]);
			printf("---------------------------------------------------------\n");
		}
		i++;
	}
	printf("---------------------------------------------------------\n");
}


void menu (int* op, char* MENU[], int tamanho, int start){
	system("@cls||clear");
	writeMenu(MENU, tamanho,start);
	printf ("\nSeleciona opcao:\n");

	scanf("%d", op);
	printf("\n");
	int opcao = *op;
	fflush (stdin); /* Limpar o buffer do teclado */

	if(opcao < start || opcao >= tamanho+start){
		printf ("---\nOpcao invalida! Por favor escolha de novo\n---\n");
		menu(op, MENU, tamanho, start);
	}

	if(opcao == 3)
	{
		menu(op,OUTRAS_OPCOES, tamanho_outras_opcoes, tamanho-1);
		if(*op == 5) menu(op, MENU, tamanho, start);
	}
	system("@cls||clear");
}

int ler_ficheiro(float parametros[], char* name[]){
	FILE *fp1;
	fp1 = fopen("config_model.txt", "r");

	if (!fp1)
	{
		printf("---\nnão foi possivel abrir o ficheiro\n---\n");
		return 1;
	}

	char *pointer; //local onde se está a ler o ficheiro
	char line[130];
	int i = 0;

	do{
		pointer = fgets(line,130,fp1);
		int check = line[0];
		if(check != '%')
		{
			if(isdigit(check)) //ctype.h
			{
				parametros[i++] = atof(line); //stdlib.h
			}
			else
			{
				printf("---\nvalor de \"%s\" em falta\n---\n", name[i]);
				return 1;
			}
		}
	}while(pointer != NULL && i < 14);

	return 0;
}

void printParametros (float parametros[], char* nome_parametros[]){
	int i = 0;

	printf("---------------------------------------------------------\n");
	printf("%-45s%-13s\n", "nome", "| valor");
	printf("---------------------------------------------|-----------\n");
	while(i < 14)
	{
		printf("%-45s| %-13.6f\n", nome_parametros[i], parametros[i]);
		i++;
	}
	printf("---------------------------------------------------------\n");

}
