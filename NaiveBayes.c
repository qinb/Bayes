#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SAMPLE_CNT 150
#define ATTR_CNT 4

struct Iris{
 double attr[ATTR_CNT];
  int label;
};

char pr[20]; //用于存放类别
struct Iris Iris[SAMPLE_CNT];
int labnum[3]={0};

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


void process()
{
  int i,j,k;
  int plabel; //预测的类别
  int predT=0;   //预测正确
  int label; //存放测试样本类别
  
  double attr[ATTR_CNT]; //存放测试样本属性
  double attrNum[3]; //每一类和测试样本属性相同的个数
  double prob[3];
  double maxscore;

   ReadFile();

 
  for(i=0;i<SAMPLE_CNT;i++)
  {
	//测试样本  (使用留一法)
	label = Iris[i].label;
	labnum[label-1]--;

	//类别概率
	prob[0]=(double)labnum[0]/(SAMPLE_CNT-1);
 	prob[1]=(double)labnum[1]/(SAMPLE_CNT-1);
    prob[2]=(double)labnum[2]/(SAMPLE_CNT-1);

		//测试样本第j个属性
    for(j=0;j<ATTR_CNT;j++)
	{
	   attrNum[0]=0;
	   attrNum[1]=0;
	   attrNum[2]=0;

     //训练样本中和测试样本第j个属性相同的个数放入attrNum
	 for(k=0;(k<SAMPLE_CNT);k++)
	  {
		if((k!=i)&&(Iris[i].attr[j]==Iris[k].attr[j]))
           attrNum[Iris[k].label-1]++;
	  }
        prob[0]*=(double)attrNum[0]/labnum[0];
        prob[1]*=(double)attrNum[1]/labnum[1];
        prob[2]*=(double)attrNum[2]/labnum[2];
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

  printf("%d %d\n",i,label);
  printf("%.8lf  %.8lf   %.8lf\n\n",prob[0],prob[1],prob[2]);

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

