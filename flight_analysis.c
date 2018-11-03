#include "flight_analysis.h"
#include "menus_options.h"

int main ()
{
	system("clear");
	printf("\n");

	menu(1);

	system("clear");
	printf("---------------\nFim do programa\n---------------\n");
	printf("\nPress Enter to close program\n");
	getchar();
	system("clear");
	return 0;
}

int ler_ficheiro(double parametros[], char* name[]){
	FILE *fp1;
	fp1 = fopen("config_model.txt", "r");

	if (!fp1)
	{
		system("clear");
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
				parametros[i++] = (double) atof(line); //stdlib.h
			}
			else
			{
				system("clear");
				printf("---\nvalor de \"%s\" em falta\n---\n", name[i]);
				return 1;
			}
		}
	}while(pointer != NULL && i < 14);

	return 0;
}

void printParametros (double parametros[], char* nome_parametros[]){
	int i = 0;

	printf("---------------------------------------------------------\n");
	printf("%-45s%-13s\n", "nome", "| valor");
	printf("---------------------------------------------|-----------\n");
	while(i < 14)
	{
		double write = parametros[i];
		if(write < 0.02 && write != 0 && write > -0.02){
			printf("%-45s| %-13.3e\n", nome_parametros[i], parametros[i]);
		}else{
			printf("%-45s| %-13.3f\n", nome_parametros[i], parametros[i]);
		}
		i++;
	}
	printf("---------------------------------------------------------\n\n");

}
