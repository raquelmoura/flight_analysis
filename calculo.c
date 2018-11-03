#include "calculo.h"


void create_file (double parametros[])
{
	double t;
	double AR = ar(parametros);
	double CL = cl(parametros);
	double epslon1 = epslon(parametros, AR);
	double CD = cd(parametros, epslon1, CL);

	double buff, lift, drag;

	double gamma = parametros[GAMMAi];
	double gamma1 = gamma;
	double V = parametros[Vi];
	double V1 = V;
	double H = parametros[Hi];
	double X = parametros[Xi];

	double m = parametros[M];
	double g = parametros[G];
	double dt = parametros[DT];

	// printf("---------------------------------------------------------\n");
	// printf("Escreva o nome do ficheiro onde quer guardar os movimentos\n");
	// printf("---------------------------------------------------------\n");

	for(t=0; t <= parametros[TF] && H >= 0;t=t+dt)
	{
		printf("%f %f %f %f %f\n",t,V,gamma,X,H);
		buff = parametros[RHO] * pow(V, 2) * parametros[S] * (1/2);
		lift = CL * buff;
		drag = CD * buff;

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
	return ( ( parametros[ALPHA] * PI * n_ar) / ( 1 + sqrt( 1 + pow((n_ar/2), 2) ) ) );
}

double epslon (double parametros[], double ar1)
{
	return ( 1 / ( PI * parametros[E] * ar1 ) );
}

double ar (double parametros[])
{
	return ( ( pow(parametros[B],(double) 2) ) / parametros[S] );
}