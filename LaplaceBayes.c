#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SAMPLE_CNT 150
#define ATTR_CNT 4
#define CLASS_CNT 3


struct Iris{
 double attr[ATTR_CNT];
  int label;
};

char pr[20]; //用于存放类别
struct Iris Iris[SAMPLE_CNT];
int labnum[CLASS_CNT]={0};
double classId[SAMPLE_CNT-1];  //���ѵ����������� 
double AllEachattr[SAMPLE_CNT-1]; //����ѵ������ĳһ���� 
//Iris-setosa=1
//Iris-versicolor=2
//Iris-virginica=3

void ReadFile()
{
  FILE *fi;
  int i=0;
  fi=fopen("Iris.txt","rb");

  while(!feof(fi))
  {
    fscanf(fi,"%lf,%lf,%lf,%lf,%s",&Iris[i].attr[0],&Iris[i].attr[1],&Iris[i].attr[2],&Iris[i].attr[3],pr);
    if(!strcmp(pr,"Iris-setosa"))
		Iris[i].label=1;

    if(!strcmp(pr,"Iris-versicolor"))
   		Iris[i].label=2;

    if(!strcmp(pr,"Iris-virginica"))
		Iris[i].label=3;

   labnum[Iris[i].label-1]++;
    i++;
  }
}


void swap(double *a,double *b)
{
  double tmp;
  tmp=*a;
   *a=*b;
  *b=tmp;
}


void Bubblesort(double a[],int p,int n) 
{//p��ʾ��ʼ�±꣬nΪ���� 
    int i, j, temp;
  
    for (j = p; j <p + n - 1; j++)
    for (i = p; i <p + n - 1 - j; i++)
      if(a[i] > a[i + 1])
         {
         swap(&a[i],&a[i+1]);
         swap(&AllEachattr[i],&AllEachattr[i+1]);
         }
}


void Bubblesort1(double a[],int p,int n) 
{//p��ʾ��ʼ�±꣬nΪ���� 
    int i, j, temp;
  
    for (j = p; j <p + n - 1; j++)
    for (i = p; i <p + n - 1 - j; i++)
      if(a[i] > a[i + 1])
         {
         swap(&a[i],&a[i+1]);
         }
}


int DifferNum(double *w,int p,int n)
{
   int j,count=1;  
  for(j=p;j<p+n-1;j++)     
    if(w[j]!=w[j+1])
        count++;
  return count;
} 



void process()
{
  int i,j,k,t;
  int plabel; //预测的类别
  int predT=0;   //预测正确
  int label; //存放测试样本类别
  int count[CLASS_CNT];
  int h=0; 
     
  double attr[ATTR_CNT]; //存放测试样本属性
  double attrNum[CLASS_CNT]; //每一类和测试样本属性相同的个数
  double prob[CLASS_CNT];
  double maxscore;

   
   ReadFile();
    
  for(i=0;i<SAMPLE_CNT;i++)
  {
	//测试样本  (使用留一法)
	label = Iris[i].label;
	labnum[label-1]--;
     
	//类别概率
	prob[0]=(double)labnum[0]/(SAMPLE_CNT+CLASS_CNT-1); //Laplace smooth 
 	prob[1]=(double)labnum[1]/(SAMPLE_CNT+CLASS_CNT-1);
    prob[2]=(double)labnum[2]/(SAMPLE_CNT+CLASS_CNT-1);
    
      for(k=0;k<SAMPLE_CNT-1;k++) 
          classId[k]=0;  
	 
   //测试样本第j个属性
     for(j=0;j<ATTR_CNT;j++)
	{
       t=0;
       attrNum[0]=0;
	   attrNum[1]=0;
	   attrNum[2]=0;
       
     
     //训练样本中和测试样本第j个属性相同的个数放入attrNum
	 for(k=0;k<SAMPLE_CNT;k++)
	  {
		if((k!=i))
        {  
          if(Iris[i].attr[j]==Iris[k].attr[j])
            attrNum[Iris[k].label-1]++;                       
                
             if(j==0) 
             classId[t]=Iris[k].label;  
           //  printf("sdfsdfadf\n"); 
           AllEachattr[t++]=Iris[k].attr[j];                
        }  
      
	  }
	 	 
	  //���������,����ֵҲ���Ŷ� 
       Bubblesort(classId,0,SAMPLE_CNT-1); 
     
       for(k=0;k<CLASS_CNT;k++)
       {  
          if(k==0)
          {                     
           Bubblesort1(AllEachattr,0,labnum[k]);         
		  count[k]=DifferNum(AllEachattr,0,labnum[k]);
          }
          else
          {
           Bubblesort1(AllEachattr,labnum[k-1],labnum[k]);
           count[k]=DifferNum(AllEachattr,labnum[k-1],labnum[k]);
          }
          
         prob[k]*=(double)(attrNum[k]+1)/(labnum[k]+count[k]);                    
      }      	  
	}

    maxscore=(prob[0]>prob[1]?prob[0]:prob[1])>prob[2]?(prob[0]>prob[1]?prob[0]:prob[1]):prob[2]; //最大值

    if(prob[0]==maxscore)
        plabel=1;
    if(prob[1]==maxscore)
        plabel=2;
    if(prob[2]==maxscore)
        plabel=3;

      if(label==plabel)
		  predT++;

  printf("��%d������,ʵ������Ϊ%d\n",i,label);
  printf("%.8lf   %.8lf��%.8lf\n",prob[0],prob[1],prob[2]);
    labnum[label-1]+=1; //恢复各类样本数
  }

   printf("true rate is%lf\n",(double)predT/SAMPLE_CNT);

}


int main()
{
  	process();
  	getch(); 
    return 1;
}

