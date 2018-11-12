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
		printf("%f %f %f %f %f\n",t,V,gamma,X,H);
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
