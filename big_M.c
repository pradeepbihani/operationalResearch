#include <stdio.h>
int NOE,NOV,NBV,NNV,NUM=0;

void printMatrix(float eq[][NOV+1],int n,int m)
{
	int i=0,j=0;
	for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            printf("%f\t",eq[i][j]);
        printf("\n");
    }
    printf("\n");
}

int maxNegative(float *eq,float *bigm,int *ic)
{
	int i,j,k;
	float min=0;
	
	for(k=0;k<NOV;k++)
	{
		if(eq[k] < min )
		{	
			min=eq[k];
			*ic=k;
		}
		
		/*if(eq[k]==0 )
		{
			if(bigm[k] < min )
			{	
				*ic=k;
				min=-1 ;
				break;
			}
		}*/
	}
	
	if (min==0)
	{
		if (min==0)
			return 0;
	}
	else
		return 1;	
}

void minratio(float eq[][NOV+1],int *ir,int ic)
{
	int i,j,k;
	float ratio[NOE],min=eq[0][NOV]/eq[0][ic];*ir=0;
	for(i=0;i<NOE;i++)
	{
		if(eq[i][ic]!=0)
		{	
			ratio[i]=eq[i][NOV]/eq[i][ic];
			if(ratio[i] < min)
			{
				min = ratio[i];
				*ir=i;
			}
		}
		else
			ratio[i]=0;
	}
}

void transformMatrix(float eq[][NOV+1],int ir,int ic,int x[][NOV],float *bigm)
{
	float pt=eq[ir][ic];
	int i,j,k,t=0;
	//Changing Variable
		/*i=x[0][ic];j=x[1][ic];
		x[0][ic]=x[0][NNV+ir-1];x[1][ic]=x[1][NNV+ir-1];
		x[0][NNV+ir-1]=i;x[1][NNV+ir-1]=j;*/
		
	if (pt!=0)
	{	
		for(i=0;i<=NOE;i++)
		{
			if (i!=ir)
			{	
				for(j=0;j<=NOV;j++)
				{
					if (j!=ic)
					{	
						eq[i][j]=((eq[i][j]*pt)-(eq[i][ic]*eq[ir][j]))/pt;
						if(t==0)
						{	
							bigm[j]=((bigm[j]*pt)-(bigm[ic]*eq[ir][j]))/pt;
							t++;
						}
					}
					
					
				}
			}
		}
		
		//Dividing row by pt
		for(j=0;j<=NOV;j++)
			eq[ir][j]=eq[ir][j]/pt;
		
		//dividing coloumn by -pt
		for(i=0;i<=NOV;i++)
			eq[i][ic]=-(eq[i][ic]/pt);
			
			eq[ir][ic]=(-1)*(eq[ir][ic]);	
	}
	
	
}

int main()
{
	int noe,nov,fc,diff;
    printf("Enter The Number of equation\n");
    scanf("%d",&noe);
    printf("enter the number of unknown variable\n");
    scanf("%d",&nov);
    printf("\n");
    NOE=noe;
    NOV=nov;
    //getting and checking euation
   printf( "NOTE:Please describe the equation type before entering equation on the system:\n");
   printf("\t\t\tType of Equation:\n");
   printf("1.Equation ax+by<=c\n");
   printf("2.Equation ax+by=c\n");
   printf("3.Equation ax+by>=c\n");
    float eq[noe+1][nov+1],feq[noe+1][noe+1],ec[noe+1][noe+1],bigm[nov+1];
    int *pt,ir,ic,check,x[3][nov],v;
    int i=0,j=0,k=0,t=0,p=0,basicV=0,surplusV=0,artificalV=0,slackV=0,type=0;
    //1.Equation ax+by<=c ;2.Equation ax+by=c\n;3.Equation ax+by>=c;
    //Taking input of equTION FOLLOWED BY CONSTAINT EQUATION
    for(i=0;i<=noe;i++)
    {	
        if(i!=noe)
        {	
        	printf("enter the %d equation:\n",i+1);
        	printf("Enter which type of equation is:");
    		scanf("%d",&type);
    		if(type==3)
    			surplusV++;
        }
        else
        	printf("Enter the constaint equation:\n");
        for(j=0;j<nov;j++)
        {
            printf("enter the %d unknown coefficient:",j+1);
            if(i==noe)
            {
            	scanf("%f",&eq[i][j]);
            	x[0][j]=j;
            	if(eq[i][j]!=0)
            	{	
            		x[1][j]=1;
            		p++;
            	}
            	else
            		x[1][j]=0;
            }	
            else
            {
            	scanf("%f",&eq[i][j]);
            	if (type==3&&eq[i][j]!=0)
            		v=j;
            }
        }
        
        if(i!=noe)
		{    printf("Enter the constant value:");
		     scanf("%f",&eq[i][nov]);
		}
		else
			eq[i][nov]=0;
			
        printf("\n");
        for(k=0;k<=nov;k++)
        {
			if(k==0)
				printf("%0.1fX[%d]",eq[i][k],k);	        	
            else if(k!=nov && k!=0)
            { 	
            	if(eq[i][k] >= 0)
            		printf(" +");
                printf("%0.1fX[%d]",eq[i][k],k);
            }
            else if(k==nov){
                printf(" =");
                printf("%0.1f\n",eq[i][k]);
             }
             //Calculating bigm matrix
             if(i==0)
             	bigm[k]=0;
   			if(type!=1&&i!=noe)
   				bigm[k]=bigm[k]-eq[i][k];   
        }
        printf("\n");
   }
   NBV=p+surplusV;
   NNV=NOV-NBV;
   //Making Last Row Negative
   	for(j=0;j<=nov;j++)
   		eq[noe][j]=-eq[noe][j];
   		
   printMatrix(eq,noe+1,nov+1);
   for(j=0;j<=nov;j++)
   		printf("%f\t",bigm[j]);
   	printf("\n\n\n");
   
   
  	check=1;
   while (check) 	
   {	
   //printMatrix(eq,noe+1,nov+1);
	   if(maxNegative(eq[noe],bigm,&ic))
	   {
	   		minratio(eq,&ir,ic);
	   		transformMatrix(eq,ir,ic,x,bigm);
	   		printMatrix(eq,noe+1,nov+1);
	   		for(j=0;j<=nov;j++)
   				printf("%f\t",bigm[j]);
   			printf("\n\n\n");
	   }
	 check=maxNegative(eq[noe],bigm,&ic);
   }
  /* for(j=0;j<nov;j++)
   {	if(j < NBV)
   			printf("X[%d]=0\n",x[0][j]+1);
   		else
   			printf("X[%d]=%f\n",x[0][j]+1,eq[j-NBV][NOV]);
   }*/
}




