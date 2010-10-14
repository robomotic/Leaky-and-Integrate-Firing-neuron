#ifndef lif_h
#define lif_h
typedef struct{

	float alfa; //inertia factor
	float beta; //input factor
	float u[2]; //membrane potential
	float R; //resistance of the model
	float C; //capacitance of the model
	float Th;//threshold of the I&F neuron
	unsigned int spike;//a spike is generated or not

}Lif;


bool lif_init(Lif *ptr,float R,float C,float deltaT)
{
	if(ptr!=NULL)
	{
		float tau=R*C;
		ptr->alfa=(tau/(tau+deltaT));
		ptr->beta=(R*deltaT)/(tau+deltaT);
		ptr->spike=0;
		ptr->u[0]=0.0;
		ptr->u[1]=0.0;
		ptr->Th=1.0;

		return true;
	}
	else return false;
}


void lif_update(Lif *ptr,int input)
{
	if(ptr!=NULL)
	{
		//compute the membrane potential
		ptr->u[1]=ptr->alfa*ptr->u[0]+ptr->beta*input;
		//update the sample
		ptr->u[0]=ptr->u[1];

		if((ptr->u[1])>=(ptr->Th))
		{
				ptr->spike=1;
				ptr->u[1]=0;
				ptr->u[0]=0;
		}
		else
			ptr->spike=0;
	}
}
#endif