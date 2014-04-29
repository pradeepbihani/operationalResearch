#include <stdio.h>
int NOE;
int NOV;
int NUM=0;
float MAXX=-100;

void printMatrix(float (*eq)[NOE+1],int n,int m)
{
	int i=0,j=0;
	for(i=0;i< n;i++)
    {
        for(j=0;j< m;j++)
            printf("%f\t",eq[i][j]);
        printf("\n");
    }
    printf("\n");
}


float* gauss(float eq[][NOE+1],float ecf[][NOV+1],int n,int m,float *x)
{
    int i,j,k,sol=1;
    float ec[n][m],ft,pre,pt;
    //Copying array from original array
    for(i=0;i< n;i++)
        for(j=0;j< m;j++)
            ec[i][j]=eq[i][j];
    
   // printMatrix(ec,n,m);
            
    for(i=0;i<n-1;i++)
    {
        for(k=i+1;k< n;k++)
        {	
        	pre=ec[k][i];
        	pt=ec[i][i];
            for(j=0;j<m;j++)
                {
                	ft=(ec[i][j]*pre)/pt;
                	ec[k][j]=ec[k][j]-ft;
                }  
         }       
   }
    
    
    if(m-1== n)//checking of square matrix
    {
    		
    	//Resubstitute
    	for(i=n-1;i>=0;i--)
    	{	
			x[i]=ec[i][m-1];
			
			for(j=n-1;j > i;j--)
				x[i]=x[i]-ec[i][j]*x[j];
				
			if((int)ec[i][i] == 0)
			{	
				sol=0;
			}
			else
				x[i]=x[i]/ec[i][i];
				
    	}
    	
    	if(sol==1)
		{	
			for(i=0;i<n;i++);
				//printf("Solution of x[%d]:%f\n",i,x[i]);
		}
		else
			printf("Infinite many solution OR No solution\n");
    }
    else
    {
    	printf("No solution");
    }
   // printMatrix(ec,n,m);
}



//make Square Matrix
void makeSqMatrix(float eq[][NOV+1],float ec[][NOE+1],int d,int* x,int n,int m,float *y)
{
	int i=0,j,k=0,p=0,q=-1;
	//for(k=0; k< d || j < m; k++)
	//{
		for(j=0;j<m;j++)
		{	
			//printf("********%d----%d\n",j,q);
			if(k<d)
			{	
				if(x[k]==j)
				{
					//printf("Break at k=%d\n\n",k);
					k++;
					continue;
				}
				else
					q++;	
			}
			else
				q++;
				
			for(i=0;i<n;i++)
			{	
				ec[i][q]=eq[i][j];
				//printf("%d,%d/////%d,%d****eq=%f+++++ec=%f\n",i,q,i,j,eq[i][j],ec[i][q]);
			}
			//printf("\n");	
		}
		gauss(ec,eq,n,n+1,y);		
	//}
}

//Fact
int fact(int n)
{
    if(n==0 || n==1)
        return 1;
    
    return n*fact(n-1); 
}









int comb(int *x,int *y,int n,int m,float eq[][NOV+1],float ec[][NOE+1],int diff,int noe,int nov)
{
	int i,j,p=0,q=0,check=0;
	float val[n],z;
	if(m!=0)
	{	for(i=n-1;i>=0;i--)
		{
			y[m-1]=x[i];
			comb(x,y,i,m-1,eq,ec,diff,noe,nov);
		}
	}
	else
	{	
		makeSqMatrix(eq,ec,diff,y,noe,nov+1,val);
		printf("Value of X in  System Of Equation:\n");
		z=0;
		for(j=0;j<NOV;j++)
		{
			if(p < diff && j==y[p])
			{	
					p++;
					continue;
			}
			else	
			{	
				printf("x[%d]=%0.3f\t",j+1,val[q]);
				if(val[q] < 0)
					check=1;
				z=z+val[q]*eq[NOE][j];
				q++;
			}
		}
		printf("z=%f",z);
   		printf("\n\n");
   			if(z > MAXX && check==0)
   				MAXX=z;
		return x[n];	
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
    int *pt;
    int i=0,j=0,k=0;
    
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
            scanf("%f",&eq[i][j]);
        }
        
        printf("Enter the constant value:");
        scanf("%f",&eq[i][nov]);
        printf("\n");
        for(k=0;k<=nov;k++)
        {
			if(k==0)
				printf("%0.1fX[%d]",eq[i][k],k);	        	
            if(k!=nov && k!=0)
            { 	
            	if(eq[i][k] > 0)
            		printf(" +");
                printf("%0.1fX[%d]",eq[i][k],k);
            }
            else if(k==nov){
                printf(" =");
                printf("%0.1f\n",eq[i][k]);
             }   
        }
        printf("\n");
         
   }
   
 // printMatrix(eq,noe+1,nov+1);
  //checking number of variable 
    if(nov > noe)
     {
            fc=fact(nov)/(fact(noe)*fact(nov-noe));
            NUM=fc;
            diff=nov-noe;
           int x[diff],y[nov];
           //printMatrix(eq,noe+1,nov+1);
            
            for(i=0;i<nov;i++)
            	y[i]=i;
            printf("System of Equation Will Have %d no of system solution:\n",fc);	
            comb(y,x,i,diff,eq,ec,diff,noe,nov);
     } 
        else if(nov < noe)
        {
        	printf("Infinite many solution\n");
        }
        
        	 printf("Maimum Value Of Constaint is:%f\n\n",MAXX);
       	 
   
}
