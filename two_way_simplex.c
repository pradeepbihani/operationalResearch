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
	float pt=eq[ir][ic],tr;
	int i,j,k,R,C;
	//Changing Variable
	    C=ic-1;
	    R=NOV+ir-1;
		i=x[0][C];j=x[1][C];
		x[0][C]=x[0][R];x[1][C]=x[1][R];
		x[0][R]=i;x[1][R]=j;
	//printf("^^^^[[[[[[[%d//////,%d=%f****\n",ir,ic,eq[ir][ic]);	
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
		
		//printMatrix(eq,NOE+2,NOV+2);
		//Dividing row by pt
		for(j=1;j<=NOV+1;j++)
			eq[ir][j]=eq[ir][j]/pt;
			
		//	printf("After ROW\n");
	//	printMatrix(eq,NOE+2,NOV+2);
		
		//dividing coloumn by -pt
		for(i=1;i<=NOV+1;i++)
			eq[i][ic]=-(eq[i][ic]/pt);
			
		//	printf("After COL\n");
		printMatrix(eq,NOE+2,NOV+2);	
			eq[ir][ic]=(-1)*(eq[ir][ic]);	
	}
	
	tr=eq[0][ic];
	eq[0][ic]=eq[ir][0];
	eq[ir][0]=tr;
}

int main()
{
    int noe,novp,nov,fc,diff,type3;
    printf("\t\tWelcome to The Two way Simplex Method Solving Scheme\n");
    printf("Enter The Number of equation\n");
    scanf("%d",&noe);
    printf("Enter the number of unknown variable\n");
    scanf("%d",&novp);
    printf("\n");
    
    //getting and checking euation
   printf( "NOTE:Please describe the equation type before entering equation on the system:\n");
   printf("\t\t\tType of Equation:\n");
   printf("1.Equation ax+by<=c\n");
   printf("2.Equation ax+by=c\n");
   printf("3.Equation ax+by>=c\n");
   
   printf("Please enter the number of equation of type 3:");
   scanf("%d",&type3);
   
   nov=novp+type3;
   NOE=noe;
   NOV=nov;
   TNV=nov+noe;
   
    float eq[noe+2][nov+2],feq[noe+2][noe+2],ec[novp],bigm[nov+2];
    int *pt,ir=1,ic=1,check,x[2][TNV],v;
    int i=0,j=0,k=0,t=0,p=0,type=0,surplusV=0;
    
    //initilazing to zeros
    for(i=0;i<=NOE+1;i++)
        for(j=0;j<=NOV+1;j++)
            eq[i][j]=(float)t;
            
     
    //printMatrix(eq,noe+2,nov+2);        
    //Taking input of equTION FOLLOWED BY CONSTAINT EQUATION
    //Phase 1
    for(i=1;i<=noe;i++)
    {
        	
        	printf("enter the %d equation:\n",i);
        	printf("Enter which type of equation is:");
    		scanf("%d",&type);
    		
    		if(type==1)
    		    eq[i][0]=0;
    		else if(type == 2)
    		    eq[i][0]=-1;
    		else if (type == 3)
    		{    
    		    eq[i][0]=-1;
    		    surplusV++;
    		}
    		else
    		    printf("Wrong Input");
    			
        
        
        	
        for(j=1;j<=novp;j++)
        {
            printf("enter the %d unknown coefficient:",j);
            	scanf("%f",&eq[i][j]);
        }
        
        if(type==3)
            eq[i][novp+surplusV]=-1;
            
        
		printf("Enter the constant value:");
		scanf("%f",&eq[i][nov+1]);	
        printf("\n");
        
        //Output
        for(k=1;k<=novp;k++)
        {
			if(k==1||k==novp)
				printf("%0.1fX[%d]",eq[i][k],k);	        	
            else if(k!=novp && k!=1)
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

    printf("Enter The constaint Equtaion\n:");
    for(j=0;j<novp;j++)
    {
        printf("enter the %d unknown coefficient:",j);
            	scanf("%f",&ec[j]);
    }
   //Making Last Row Negative
   	for(j=1;j<=NOV+1;j++)
   	{    
   	    eq[noe+1][j]=-eq[0][j];
   	    for(i=1;i<=NOE;i++)
   		{    eq[noe+1][j]=eq[noe+1][j]+(eq[i][0]*eq[i][j]);}
   	}
   		    
   	printf("\n\n\n\t\t\tFIRST TABLEAU \n");	    
   printMatrix(eq,noe+2,nov+2);
   
   
   // Variable tracking
   for(j=0;j<TNV;j++)
   {
        if(j<novp)
            x[0][j]=1;
        else
            x[0][j]=0;
            
        x[1][j]=j+1;
   }		    
   
   	check=1;t=0;
  
   while (check) 	
   {
        //printf("/////%f***",eq[noe][ic]);	
        //printMatrix(eq,noe+1,nov+1);
	   if(maxNegative(eq,&ic))
	   {
	   		minratio(eq,&ir,ic);
	   		transformMatrix(eq,ir,ic,x);
	   		//printMatrix(eq,noe+2,nov+2);
	   }
	 check=maxNegative(eq,&ic);
   }
   
    
   printf("\n\n\n\t\t\tTABLEAU AFTER FIRST TRANSFORMATION\n");
    printMatrix(eq,noe+2,nov+2);
  for(i=1;i<=novp;i++)	
  { 
      for(j=0;j<TNV;j++)
       {	
            if(x[1][j]==i)	
       		{
       		    if(j<=NOV-1)
       		    {
       		        eq[0][j+1]=ec[i-1];
       		    }
       		    else
       		    {
       		        eq[j-NOV+1][0]=ec[i-1];
       		    }
       		    
       		}
       }
   
  } 
  
  //Reducing Matrix
  for(j=1;j<=nov;j++)
  {	
            if(x[1][j-1]>nov)	
       		{
       		    for(i=1;i<=noe+1;i++) 
   		            eq[i][j]=0;
       		    
       		}
  }
 // printMatrix(eq,noe+2,nov+2);
  
  for(j=1;j<=nov+1;j++)
  { 	    
        eq[NOE+1][j]=-eq[0][j];
        for(i=1;i<=noe;i++)
   		    eq[noe+1][j]=eq[noe+1][j]+(eq[i][0]*eq[i][j]);
  }
  
  printf("\n\n\n\t\t\tINITIAL TABLEAU SECOND\n");
   printMatrix(eq,noe+2,nov+2);
   printf("\n\n\n\t\t\tTABLEAU AFTER SECOND TRANSFORMATION\n");
   t=0;
   
   check=maxNegative(eq,&ic);
   while (check) 	
   {//printf("/////%f***",eq[noe][ic]);	
   //printMatrix(eq,noe+1,nov+1);
	   if(maxNegative(eq,&ic))
	   {
	   		minratio(eq,&ir,ic);
	   		//printf("^^^^%d//////,%d=%f****\n",ir,ic,eq[ir][ic]);
	   		transformMatrix(eq,ir,ic,x);
	   		 //printf("%d//////,%d=%f****\n",ir,ic,eq[ir][ic]);
	   		//printMatrix(eq,noe+2,nov+2);
	   }
	  
	 check=maxNegative(eq,&ic);
	 //printf("\nCHECK=====%d\n",check);
   }
   
   printMatrix(eq,noe+2,nov+2);
   
   for(j=0;j<TNV;j++)
   {	if(j <= nov-1)
   			printf("X[%d]=0\n",x[1][j]);
   		else
   			printf("X[%d]=%f\n",x[1][j],eq[j-NOV][NOV+1]);
   }
   printf("The Maximum Value of the Function is:%f\n\n\n",eq[noe+1][nov+1]);
   
}
