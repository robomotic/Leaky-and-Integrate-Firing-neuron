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
	int steps;//last spike time expressed in seconds
	int time;

}Lif;


bool lif_init(Lif *ptr,float R,float C,float deltaT,float refract=0.0)
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
		if(refract>0.0)
		{
			//compute the number of steps
			ptr->steps=(int)refract/deltaT;
			ptr->time=0;

		}
		else ptr->steps=0;

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
			//verify if we are out of the refractory period
			if((ptr->steps>0) && (ptr->time)>=(ptr->steps))
			{
				ptr->spike=1;
				ptr->time=0;
				ptr->u[1]=0;
				ptr->u[0]=0;
			}//refractory period is null
			else if(ptr->steps<1)
			{
				ptr->spike=1;
				ptr->u[1]=0;
				ptr->u[0]=0;
			}
		}
		else
			ptr->spike=0;
		ptr->time++;
	}
}
#endif