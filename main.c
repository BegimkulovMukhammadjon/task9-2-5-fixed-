#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <limits.h>
#include <float.h>

void Task2()
{
    printf("Zamechanie 2\n");
    int m,n,k,i,j,count=1;
    int **mas;

    printf("Vvedite kolichestvo strok i stolbsov\n");
    scanf("%d %d",&m,&n);
    mas=(int**)malloc(m*sizeof(int*));
    for(i=0;i<m;i++)mas[i]=(int*)malloc(n*sizeof(int));

    printf("Kitayskaya 1 stranisa(%dx%d)\n",m,n);
    for(i=0;i<m;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            mas[i][j]=abs(i-j)+1;
            printf("%d ",mas[i][j]);
            mas[i][j]=0;
        }
    }

    printf("\nKitayskaya 2 strochka(%dx%d)\n",m,n);
    if(n>=m)
    {
        for(j=0;j<m/2;j++)
        {
            for(i=j;i<n-j;i++)mas[j][i]=count++;
            for(i=j+1;i<m-j;i++)mas[i][n-j-1]=count++;
            for(i=n-j-2;i>j-1;i--)mas[m-j-1][i]=count++;
            for(i=m-j-2;i>j;i--)mas[i][j]=count++;
        }
        if(m%2==1)for(i=m/2;i<n-m/2;i++)mas[m/2][i]=count++;
    }
    else
    {
        for(j=0;j<n/2;j++)
        {
            for(i=j;i<n-j;i++)mas[j][i]=count++;
            for(i=j+1;i<m-j;i++)mas[i][n-j-1]=count++;
            for(i=n-j-2;i>j-1;i--)mas[m-j-1][i]=count++;
            for(i=m-j-2;i>j;i--)mas[i][j]=count++;
        }
        if(n%2==1)for(i=n/2;i<m-n/2;i++)mas[i][n/2]=count++;
    }
    for(i=0;i<m;i++,printf("\n"))for(j=0;j<n;j++)printf("%d ",mas[i][j]);

    for(i=0;i<m;i++)free(mas[i]);
    free(mas);
}

void swap(double*a,double*b)
{
    double t=*a;
    *a=*b;
    *b=t;
}

double*Gauss5(double**mas,double*y,int n)
{
  double *x,max;
  int k,index,i,j;
  const double e=0.00001;
  x=(int*)malloc(n*sizeof(double));
  k=0;
  while(k<n)
  {
    max=fabs(mas[k][k]);
    index=k;
    for(i=k+1;i<n;i++)
    {
      if(fabs(mas[i][k])>max)
      {
        max=fabs(mas[i][k]);
        index=i;
      }
    }
    for(j=0;j<n;j++)swap(&mas[k][j],&mas[index][j]);
    swap(&y[k],&y[index]);

    for(i=k;i<n;i++)
    {
      double t=mas[i][k];
      if(fabs(t)<e)continue;
      for(j=0;j<n;j++)mas[i][j]=mas[i][j]/t;
      y[i]=y[i]/t;
      if(i==k)continue;
      for(j=0;j<n;j++)mas[i][j]=mas[i][j]-mas[k][j];
      y[i]=y[i]-y[k];
    }
    k++;
  }

  for(k=n-1;k>=0;k--)
  {
    x[k]=y[k];
    for(i=0;i<k;i++)y[i]=y[i]-mas[i][k]*x[k];
  }
  return x;
}

void Task5()
{
    printf("Zamechanie 5\n");
    int n,i,j;
    double **mas,*y,*x;
    printf("Vzveshennie uzli i vstavki(n)\n");
    scanf("%d",&n);
    mas=(int**)malloc(n*sizeof(int*));
    for(i=0;i<n;i++)mas[i]=(int*)malloc(n*sizeof(double));
    y=(int*)malloc(n*sizeof(double));
    x=(int*)malloc(n*sizeof(double));

    printf("Pusk\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("Dobavlen noviy kanal %d v uzle %d: ",j+1,i+1);
            scanf("%lf",&mas[i][j]);
        }
        printf("Zabitiy probeg %d: ",i+1);
        scanf("%lf",&y[i]);
    }

    printf("Pusk\n");
    for(i=0;i<n;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            printf("%4.3lf ",mas[i][j]);
        }
        printf("%4.3lf ",y[i]);
    }

    x=Gauss5(mas,y,n);

    printf("Vredonosniy element\n");
    for(i=0;i<n;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            printf("%4.3lf ",mas[i][j]);
        }
        printf("%4.3lf ",y[i]);
    }
    printf("Chertyoj:\n");
    for(i=0;i<n;i++)printf("x[%d] = %lf\n",i,x[i]);

    for(i=0;i<n;i++)free(mas[i]);
    free(mas);
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printf("Task 9\n");
    int task;
    do
    {
        printf("Vyavlenniy shtamm(0-tiket,2,5)\n");
        scanf("%d",&task);
        switch(task)
        {
        case 0:
            break;
        case 2:
            Task2();
            break;
        case 5:
            Task5();
            printf("Detalnie obyavleniya o novih");
            break;
        }
        printf("\n");
    }while(task!=0);


    return 0;
}
