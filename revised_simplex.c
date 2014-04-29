#include <stdio.h>
int NOE;
int NOV;
int NBV;
int TNV;
int NNV;
int NUM=0;

void printMatrix(float eq[][NOV+2],int n,int m)
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

int maxNegative(float eq[][NOV+2],int *ic)
{
	int i,j,k=1;
	float min=0;
	int n=NOV;
	    
	for(k=1;k<=n;k++)
	{
		if(eq[NOE+1][k] < min)
		{	min=eq[NOE+1][k];
			*ic=k;
		}
	}
	//printf("MAX NEGATIVE ELEMENT:%d",*ic);
	if (min==0)
		return 0;
	else
		return 1;
		
}

void minratio(float eq[][NOV+2],int *ir,int ic)
{
	int i,j,k;
	float ratio=0,min=1000;
	for(i=1;i<=NOE;i++)
	{
		if(eq[i][ic]!=0)
		{	
			ratio=eq[i][NOV+1]/eq[i][ic];
			if(ratio < min && (eq[i][NOV+1]*eq[i][ic])>0)
			{
				min = ratio;
				*ir=i;
			}
		}
		
	}
	
}

void transformMatrix(float eq[][NOV+2],int ir,int ic,int x[][TNV])
{
	float pt=eq[ir][ic];
	int i,j,k;
	//Changing Variable
		i=x[0][ic-1];j=x[1][ic-1];
		x[0][ic-1]=x[0][NBV+ir-1];x[1][ic-1]=x[1][NBV+ir-1];
		x[0][NBV+ir-1]=i;x[1][NBV+ir-1]=j;
		
	if (pt!=0)
	{	
		
		
		for(i=1;i<=NOE+1;i++)
		{
			if (i!=ir)
				for(j=1;j<=NOV+1;j++)
				{
					if (j!=ic)
						eq[i][j]=((eq[i][j]*pt)-(eq[i][ic]*eq[ir][j]))/pt;
				}
		}
		
		//Dividing row by pt
		for(j=1;j<=NOV+1;j++)
			eq[ir][j]=eq[ir][j]/pt;
		
		//dividing coloumn by -pt
		for(i=1;i<=NOV+1;i++)
			eq[i][ic]=-(eq[i][ic]/pt);
			
			eq[ir][ic]=(-1)*(eq[ir][ic]);	
	}
	
	
}

int main()
{
	int noe,novp,nov,fc,diff,type3;
	printf("\t\tWelcome to The Two way Simplex Method Solving Scheme\n");
    printf("Enter The Number of equation:");
    scanf("%d",&noe);
    printf("enter the number of unknown variable\n");
    scanf("%d",&novp);
    printf("\n");
    
    //getting and checking euation
   
   
   printf( "NOTE:Please describe the equation type before entering equation on the system:\n");
   printf("\t\t\tType of Equation:\n");
   printf("1.Equation ax+by<=c\n");
   printf("2.Equation ax+by=c\n");
   printf("3.Equation ax+by>=c\n");
   
   
   TNV=novp+noe;
   NOE=noe;
   NBV=novp;
   NOV=TNV;
   nov=TNV;
   
    float eq[noe+2][nov+2],feq[noe+2][noe+2],ec[noe+2],bigm[nov+2];
    int *pt,ir,ic,check,x[2][TNV],v=0;
    int i=0,j=0,k=0,t=0,p=0,basicV=0,surplusV=0,artificalV=0,slackV=0,type=0;
    
    //initilazing to zeros
    for(i=0;i<=noe+1;i++)
        for(j=0;j<=nov+1;j++)
            eq[i][j]=(float)t;
            
     
       
    //Taking input of equTION FOLLOWED BY CONSTAINT EQUATION
    //Phase 1
    for(i=1;i<=noe;i++)
    {
        	
        	printf("enter the %d equation:\n",i);
        	printf("Enter which type of equation is:");
    		scanf("%d",&type);
    		
    			
        for(j=1;j<=novp;j++)
        {
            printf("enter the %d unknown coefficient:",j);
            	scanf("%f",&eq[i][j]);
            	
        }
       
        eq[i][j+v]=1;
         v++;
            
		printf("Enter the constant value:");
		scanf("%f",&eq[i][nov+1]);
        printf("\n");
        
        //Output
        for(k=1;k<=nov;k++)
        {
			if(k==1||k==nov)
				printf("%0.1fX[%d]",eq[i][k],k);	        	
            else
            { 	
            	if(eq[i][k] >= 0)
            		printf(" +");
            	else
            		printf(" -");
                printf("%0.1fX[%d]",eq[i][k],k);
            }   
        }
        
    		if(type==1)
    		    printf(" <=");
    		else if(type == 2)
    		    printf(" =");
    		else if(type == 3)
                printf(" >=");
                
    printf("%0.1f",eq[i][nov+1]);	
    printf("\n");
         
   }

    //taking constaint euqation
    printf("Enter the constaint equation:\n");
    for(j=1;j<=novp;j++)
    {   
         printf("enter the %d unknown coefficient:",j+1);
         scanf("%f",&eq[NOE+1][j]);
         eq[0][j]=eq[NOE+1][j];
         eq[NOE+1][j]=-eq[NOE+1][j];
    }
   	
   	for(j=0;j<TNV;j++)
   	{
   	    if(j<novp-1)
   	        x[0][j]=1;   
   	    else
   	       x[0][j]=0;
   	        
   	    x[1][j]=j+1;
   	}	    
   printMatrix(eq,noe+2,nov+2);
   check=1;
   	t=0;
   while (check) 	
   {
	   if(maxNegative(eq,&ic))
	   {
	   		minratio(eq,&ir,ic);
	   		transformMatrix(eq,ir,ic,x);
	   		
	   		
	   }
	   t++;
	   if(t==2)
	   break;
	 check=maxNegative(eq,&ic);
    }
	 for(j=0;j<TNV;j++)
   	{
   	    if(j<=NBV-1)
   	        printf("X[%d]=0\n",x[1][j]);
   	    else
   	        printf("X[%d]=%f\n",x[1][j],eq[j-NBV+1][NOV+1]);
   	}	 
   	printf("Maximum Value is:%f\n\n",eq[NOE+1][NOV+1]) ;	
}

