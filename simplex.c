#include <stdio.h>
int NOE;
int NOV;
int NBV;
int NNV;
int NUM=0;

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

int maxNegative(float *eq,int *ic)
{
	int i,j,k;
	float min=0;
	
	for(k=0;k<=NOV;k++)
	{
		if(eq[k] < min)
		{	min=eq[k];
			*ic=k;
		}
	}
	
	if (min==0)
		return 0;
	else
		return 1;
		
}

void minratio(float eq[][NOV+1],int *ir,int ic)
{
	int i,j,k;
	float ratio[NOE],min=eq[0][NOV]/eq[0][ic];
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

void transformMatrix(float eq[][NOV+1],int ir,int ic,int x[][NOV])
{
	float pt=eq[ir][ic];
	int i,j,k;
	//Changing Variable
		i=x[0][ic];j=x[1][ic];
		x[0][ic]=x[0][NNV+ir-1];x[1][ic]=x[1][NNV+ir-1];
		x[0][NNV+ir-1]=i;x[1][NNV+ir-1]=j;
		
	if (pt!=0)
	{	
		
		
		for(i=0;i<=NOE;i++)
		{
			if (i!=ir)
				for(j=0;j<=NOV;j++)
				{
					if (j!=ic)
						eq[i][j]=((eq[i][j]*pt)-(eq[i][ic]*eq[ir][j]))/pt;
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
   
    float eq[noe+1][nov+1],feq[noe+1][noe+1],ec[noe+1][noe+1];
    int *pt,ir,ic,check,x[3][nov];
    int i=0,j=0,k=0,p=0;
    
    //Taking input of equTION FOLLOWED BY CONSTAINT EQUATION
    for(i=0;i<=noe;i++)
    {
        if(i!=noe)
        	printf("enter the %d equation:\n",i+1);
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
            	scanf("%f",&eq[i][j]);
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
            	else
            		printf(" -");
                printf("%0.1fX[%d]",eq[i][k],k);
            }
            else if(k==nov){
                printf(" =");
                printf("%0.1f\n",eq[i][k]);
             }   
        }
        printf("\n");
         
   }
   NBV=p;
   NNV=NOV-NBV;
   //Making Last Row Negative
   	for(j=0;j<=nov;j++)
   		eq[noe][j]=-eq[noe][j];
   	check=1;
   while (check) 	
   {//printf("/////%f***",eq[noe][ic]);	
   //printMatrix(eq,noe+1,nov+1);
	   if(maxNegative(eq[noe],&ic))
	   {
	   		minratio(eq,&ir,ic);
	   		transformMatrix(eq,ir,ic,x);
	   		printMatrix(eq,noe+1,nov+1);
	   }
	 check=maxNegative(eq[noe],&ic);
   }
   for(j=0;j<nov;j++)
   {	if(j < NBV)
   			printf("X[%d]=0\n",x[0][j]+1);
   		else
   			printf("X[%d]=%f\n",x[0][j]+1,eq[j-NBV][NOV]);
   }
}
