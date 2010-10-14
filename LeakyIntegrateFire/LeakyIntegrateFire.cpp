// LeakyIntegrateFire.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lifsimple.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Lif neuronL;
	Lif neuronLref;
	lif_init(&neuronL,20,10,0.01);
	
	FILE * pRaw;
	pRaw = fopen ( "lif.csv" , "wb" );
	printf("alfa %f beta %f\n",neuronL.alfa,neuronL.beta);
	fprintf(pRaw,"R=%f,C=%f,dt=%f\n",1.1,0.05,0.01);
	for(int i=0;i<1000;i++)
	{
		if(i<100)
			lif_update(&neuronL,0);
		else if(i>100 && i<500)
			lif_update(&neuronL,100);
		else 
			lif_update(&neuronL,0);
		if(neuronL.spike==1)
			printf("t %d membrane %f fire %d \n",i,neuronL.u[1],neuronL.spike);

		if(neuronL.u[1]>0.0)
			printf("t %d membrane %e fire %d \n",i,neuronL.u[1],neuronL.spike);
		fprintf (pRaw,"%d,%e,%e,%d\n",i,neuronL.u[1],neuronL.u[0],neuronL.spike);
	}

		fclose (pRaw);
	return 0;
}

