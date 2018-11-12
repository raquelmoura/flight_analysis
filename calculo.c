#include "calculo.h"

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

void create_file (double parametros[])
{
	double t;
	double AR = ar(parametros);
	double CL = cl(parametros);
	double epslon1 = epslon(parametros, AR);
	double CD = cd(parametros, epslon1, CL);
	

	double lift, drag;

	double gamma = parametros[GAMMAi];
	double gamma1 = gamma;
	
	double V = parametros[Vi];
	double V1 = V;
	double H = parametros[Hi];
	double X = parametros[Xi];

	double m = parametros[M];
	double g = parametros[G];
	double dt = parametros[DT];

	printf("---------------------------------------------------------\n");
	printf("Escreva o nome do ficheiro onde quer guardar os movimentos\n");
	printf("---------------------------------------------------------\n");
	char nome[200];
	scanf("%s", nome);
	int i = 0;
	while(nome[i] != '\n' && nome[i] != '\0') i++;
	nome[i] = '\0';

	FILE *fp = fopen(nome, "w");

	for(t=0; t <= parametros[TF] && H >= 0;t=t+dt)
	{
		fprintf(fp,"%f %f %f %f %f\n",t,V,gamma,X,H);
		lift = ((parametros[RHO] * V * V * parametros[S]) / 2) * CL;
		drag = ((parametros[RHO] * V * V * parametros[S]) / 2) * CD;

		gamma = gamma + (lift - m * g * cos(gamma))*dt/(m*V);
		V = V +((-drag-m*g*sin(gamma1)) * dt / m);
		X = X + (V1 * cos(gamma1) * dt);
		H = H + (V1 * sin(gamma1) * dt);

		gamma1 = gamma;
		V1 = V;
	}
}

/*pedir as variáveis do gráfico e guardar maximo e minimo*/

int max_min(double varia[], double maxmin[][3], char nome[]){
	FILE *fp;
	char linha[200];
	char *stopr;
	int x,y;
	
	fp=fopen(nome, "r");
	if(fp==NULL){
		printf("Erro na abertura do ficheiro\n");
		getchar();
	return -1;}
	
	x=pedex()-1;
	y=pedey()-1;
	
	do{
		stopr = fgets(linha, 200, fp);
		/*?????*/
		if(scanf(linha, "%le %le %le %le %le\n", &varia[TEMPO] ,&varia[VEL], &varia[GAMMA], &varia[DIST], &varia[ALT]) == 5){
		// if(scanf(linha, "%le %le %le %le %le\n", &varia[TF] ,&varia[Vi], &varia[GAMMAi], &varia[Xi], &varia[Hi]) == 5){
		if(varia[x]>=maxmin[GRAFX][MAXI])
			maxmin[GRAFX][MAXI]=varia[x];
		if(varia[x]<= maxmin[GRAFX][MINI])
			maxmin[GRAFX][MINI]=varia[x];
		if(varia[y]>=maxmin[GRAFY][MAXI])
			maxmin[GRAFY][MAXI]=varia[y];
		if(varia[y]<=maxmin[GRAFY][MINI])
			maxmin[GRAFY][MINI]=varia[y];}
	}
	while(stopr!=NULL);
	
		maxmin[GRAFX][EX]=x;
		maxmin[GRAFY][EX]=y;
		fclose(fp);
	/*??????*/
		return 0;
}

	/*fazer gráfico*/
int grafico(double maxmin[][3], double varia[], char nome[]){
	printf("inicio\n");
	FILE *fp;
	char *stopr;
	char linha[200];
	int x=maxmin[GRAFX][EX];
	int y=maxmin[GRAFY][EX];
	int i=0;
	int j=0;
	fp=fopen(nome, "r");
	if(fp==NULL){
		printf("Erro na abertura do ficheiro\n");
	return -1;}
	printf("nao deu 2");
	if((SDL_INIT_EVERYTHING) >=0){
		g_pWindow = SDL_CreateWindow("graf",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		printf("nao deu1");
		 getchar();
	if(g_pWindow !=0){
        printf("nao deu");
        getchar();
		g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);}
	}
	else return 0;
	
	SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 0);
	SDL_RenderClear(g_pRenderer);
	SDL_Rect r1, r2, r3;
	r1.x = 150; /*eixo y */
	r1.y = -10+480;
	r1.w=1;
	r1.h=-450;
	r2.x=10; /*eixo y*/
	r2.y=-150+480;
	r2.w=620;
	r2.h=-1;
	SDL_SetRenderDrawColor( g_pRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect( g_pRenderer, &r1);
	SDL_RenderFillRect( g_pRenderer, &r2);
	
	do{
		stopr=fgets(linha, 200, fp);
		if((sscanf(linha," %le %le %le %le %le\n", &varia[TEMPO], &varia[VEL], &varia[GAMMA], &varia[DIST], &varia[ALT]))==5){
		// if(scanf(linha, "%le %le %le %le %le\n", &varia[TF] ,&varia[Vi], &varia[GAMMAi], &varia[Xi], &varia[Hi]) == 5){
			if(i==j){
				if(maxmin[GRAFX][MAXI]< -maxmin[GRAFX][MINI]) r3.x=(150-10)/fabs(maxmin[GRAFX][MINI]*varia[x]+150);
				else r3.x=(((610-150)/maxmin[GRAFX][MAXI])*varia[x]+150);

				if(maxmin[GRAFY][MAXI]< -maxmin[GRAFY][MINI]) r3.y=-(150/fabs(maxmin[GRAFY][MINI]+varia[y]+150)+480);
				else r3.y=(-((470-150)/maxmin[GRAFY][MAXI]*varia[y]+150)+480);
				
				r3.w=1;
				r3.h=-1;
				SDL_RenderFillRect(g_pRenderer, &r3);
				i=i+5;
				}
			j++;
		}
	}while(stopr!=NULL);
	
	SDL_RenderPresent(g_pRenderer);
	SDL_Delay(8000);
	SDL_Quit();
	fclose(fp);
	return 1;
}

/*pedir o parametro dos eixos x e y*/
int pedex(){
	int x;
	int i = 0;
	do{
		if (i != 0)
		{
			system("clear");
			printf("Opção inválida\n\n");
		}
		i++;
		printf("Escolha variável para o eixo xx:\n1-tempo\n2-velocidade\n3-gama\n4-distancia\n5-altura\n");
		scanf("%d", &x);
		getchar();
		fflush(stdin);}
	while((x!=1 && x!=2 && x!=3 && x!=4 && x!=5));
		system("clear");
	return x;
}

int pedey(){
	int y;
	int i = 0;
	do{
		if (i != 0)
			{
				system("clear");
				printf("Opção inválida\n\n");
			}
			i++;
		printf("Escolha variável para o eixo yy:\n1-tempo\n2-velocidade\n3-gama\n4-distancia\n5-altura\n");
		scanf("%d", &y);
		fflush(stdin);}
	while((y!=1 && y!=2 && y!=3 && y!=4 && y!=5));
	system("clear");
	return y;
}

//Constants
double cd (double parametros[], double epslon1, double cl1)
{
	return ( parametros[CD0] + ( epslon1 * pow(cl1,2) ) );
}

double cl (double parametros[])
{
	double n_ar = ar(parametros);
	return ( ( parametros[ALPHA] * PI * n_ar) / ( 1 + sqrt( 1 + ((n_ar * n_ar) / 4) ) ) );
}

double epslon (double parametros[], double ar1)
{
	return ( 1 / ( PI * parametros[E] * ar1 ) );
}

double ar (double parametros[])
{
	return ( ( parametros[B] * parametros[B] ) / parametros[S] );
}
