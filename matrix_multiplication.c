#include<stdio.h>
#include<malloc.h>

print_matrix(float **M,int n)
{
    int i=0,j=0;
    printf("Matrix IS :\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%f\t",M[i][j]);   
        }
        printf("\n");
    }
    printf("\n");
}



void mul_matrix(float **M,float **M1,float **V,int n)
{
    int i=0,j=0,t=0;
    float sum=0,tr[n][n];
    
    
    for(i=0;i<n;i++)
    {    
        
        for(j=0;j<n;j++)
        {
            sum=0;
            for(t=0;t<n;t++)
            {
                sum=sum+M1[i][t]*V[t][j];
            }
            tr[i][j]=sum;
        }
    }
    
    for(i=0;i<n;i++)
    {    
        for(j=0;j<n;j++)
        {
           M[i][j]=tr[i][j]; 
        }
    }
}



void make_matrix(float **M,float **V,int k,int n)
{
    int i=0,j=0;
    for(j=0;j<n;j++)
    {    
       if(j!=k)
       {
            for(i=0;i<n;i++)
            {
                if(i==j)
                    V[i][j]=1;
                else
                    V[i][j]=0;
            }
       }
       else
       {
            for(i=0;i<n;i++)
            {
                V[i][j]=-(M[i][k]/M[k][k]);
            }
            V[k][k]=(1/M[k][k]);
       }
    }
}

void make_matrix_2(float **M,float **M_pre,float **M_new,float **V_pre,float **V_new,int k,int n)
{
    int i=0,j=0,t=0;
    float P[n],sum=0;
    
    for(i=0;i<n;i++)
    {  
        sum=0;
         for(j=0;j<n;j++)
            sum=sum+M_pre[i][j]*M[j][k];
         P[i]=sum;    
    }
    
   for(i=0;i<n;i++)
    {
        printf("///%f\t===",P[i]);
        if(i!=k)
            P[i]=-(P[i]/P[k]);
        printf("///%f\t",P[i]);  
    }
    P[k]=1/P[k];
    
   
    for(j=0;j<n;j++)
    {    
       if(j!=k)
       {
            for(i=0;i<n;i++)
            {
                if(i==j)
                    V_new[i][j]=1;
                else
                    V_new[i][j]=0;
            }
       }
       else
       {
            for(i=0;i<n;i++)
            {
                V_new[i][j]=P[i];
            }
            
       }
    }
    
    mul_matrix(M_new,V_new,M_pre,n);
    printf("M MAtrix:\n");
    print_matrix(M_pre,n);
    print_matrix(V_new,n);
}


int main()
{
    float **mat,**mat_mul,***E,***M;
    int n=0,i=0,j=0,t=0;
    
    printf("Enter the no of row of the square matrix:");
    scanf("%d",&n);
    E=malloc(n*sizeof(float**));
    M=malloc(n*sizeof(float**));
    mat=malloc(n*sizeof(float*));
    mat_mul=malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
    {    
        mat[i]=malloc(n*sizeof(float));
        mat_mul[i]=malloc(n*sizeof(float));
        E[i]=malloc(n*sizeof(float*));
        M[i]=malloc(n*sizeof(float*));
        for(j=0;j<n;j++)
        {    E[i][j]=malloc(n*sizeof(float));
             M[i][j]=malloc(n*sizeof(float));
        }
    }
    
    printf("Enter the matrix:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%f",&mat[i][j]);   
        }
        printf("\n");
    }
    
    
    print_matrix(mat,n);
    make_matrix(mat,E[0],0,n);
    M[0]=E[0];
    for(i=1;i<n;i++)
    {
        make_matrix_2(mat,M[i-1],M[i],E[i-1],E[i],i,n);
    }
    
    for(i=0;i<n;i++)
    {    
        
        for(j=0;j<n;j++)
        {
            mat_mul[i][j]=E[0][i][j];
            for(t=0;t<n;t++)
            {
                printf("%f\t",E[i][j][t]);
                
            }
            printf("\n");
        }
        printf("\n\n");
    }
    
    print_matrix(mat_mul,n);
    for(i=1;i<n;i++)
    {
        mul_matrix(mat_mul,E[i],mat_mul,n);
    }
    
    for(i=0;i<n;i++)
    {    
        
        for(j=0;j<n;j++)
        {
            
           printf("%f\t",mat_mul[i][j]);
           
        }
        printf("\n");
    }
    
   
}
