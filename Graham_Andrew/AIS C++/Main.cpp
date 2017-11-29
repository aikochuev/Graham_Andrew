#include <stack>
#include <iterator>
#include "iostream"
#include <ctime>
#include <stdlib.h>
#include <math.h>
using namespace std;

struct Point
{
	int X, Y, pX, pY;
};
int isLeft (Point p0,Point p1,Point p2)
	{
		 return (p1.X - p0.X)*(p2.Y - p0.Y) - (p2.X - p0.X)*(p1.Y - p0.Y);
	}
int compare(const void* a, const void* b)
{
        const Point* k = (const Point*)a;
        const Point* m = (const Point*)b;
		int C1=(k->pX)*(m->pY) - (k->pY)*(m->pX);
		int C2=(k->pX)*(k->pX)+(k->pY)*(k->pY);
		int C3=(m->pX)*(m->pX)+(m->pY)*(m->pY);
		if ((C1<0)||((C1==0)&&(C2>C3))) 
			return 1;
		else
			return -1;
		if ((C1== 0)&&(C2 == C3)) 
			return 0;
}
int compareA(const void* a, const void* b)
{
        const Point* k = (const Point*)a;
        const Point* m = (const Point*)b;
		if (((k->X)>(m->X))||((k->X)==(m->X))&&((k->Y)>(m->Y))) 
			return 1;
		else
			return -1;
		if (((k->X)==(m->X))&&((k->Y)==(m->Y))) 
			return 0;
}
void heapify (Point *arr,int pos, int n,int var) {
    while (2 * pos + 1 < n)
	{
        int t = 2 * pos +1;
		if(var==1)
		{
			if ((2 * pos + 2 < n) && ((arr[2*pos+2].pX*arr[t].pY - arr[2*pos+2].pY*arr[t].pX <0)||
				((arr[2*pos+2].pX*arr[t].pY - arr[2*pos+2].pY*arr[t].pX == 0)&&
					 ((arr[2*pos+2].pX*arr[2*pos+2].pX+arr[2*pos+2].pY*arr[2*pos+2].pY) > (arr[t].pX*arr[t].pX+arr[t].pY*arr[t].pY)))))
			{
				t = 2 * pos + 2;
			}
			if (((arr[pos].pX*arr[t].pY - arr[pos].pY*arr[t].pX >0)||
				((arr[pos].pX*arr[t].pY - arr[pos].pY*arr[t].pX == 0)&&
				((arr[pos].pX*arr[pos].pX+arr[pos].pY*arr[pos].pY) <= (arr[t].pX*arr[t].pX+arr[t].pY*arr[t].pY))))) 
			{
				swap(arr[pos], arr[t]);
				pos = t;
			} 
			else break;
		}
		else
		{
			if ((2 * pos + 2 < n) && ((arr[2*pos+2].X>arr[t].X)||
				((arr[2*pos+2].X==arr[t].X)&&(arr[2*pos+2].Y > arr[t].Y))))
			{
				t = 2 * pos + 2;
			}
			if ((arr[pos].X<arr[t].X)||((arr[pos].X==arr[t].X)&&(arr[pos].Y == arr[t].Y)))
			{
				swap(arr[pos], arr[t]);
				pos = t;
			} 
			else break;
		}
    }
}
void heap_make(Point *arr,int n,int var)
{
    for (int i = n - 1; i >= 0; i--)
    {
        heapify(arr,i, n,var);
    }
}
void heap_sort(Point *arr,int n,int var)
{
    heap_make(arr,n,var);
    while(n>0)
    {
        swap(arr[0],arr[n-1]);
        n--;
        heapify(arr,0,n,var);
    }
}
stack <Point> GRAHAMup(stack <Point> upG, Point*upM,int size_upM)
{
	upG.push(upM[0]);
	Point prevtopUP=upM[0];
	upG.push(upM[1]);
	int i=2;
	while (i<size_upM)
	{
		if(isLeft(prevtopUP,upG.top(),upM[i])>0)
		{
			if(upG.size()>2)
			{
				upG.pop();
				Point tmp=upG.top();
				upG.pop();
				prevtopUP=upG.top();
				upG.push(tmp);
				continue;
			}
			else
			{
				upG.pop();
				prevtopUP=upG.top();
				upG.push(upM[i]);
				i++;
				continue;
			}
		}
		if(isLeft(prevtopUP,upG.top(),upM[i])==0)
		{
			if((upG.top().X<upM[i].X)||(upG.top().Y<upM[i].Y))
			{
				upG.pop();
				prevtopUP=upG.top();
				upG.push(upM[i]);
				i++;
				continue;
			}
			else
			{
				i++;
				continue;
			}
		}
		if(isLeft(prevtopUP,upG.top(),upM[i])<0)
		{
			prevtopUP=upG.top();
			upG.push(upM[i]);
			i++;
			continue;
		}
	}
	return upG;
}
stack <Point> GRAHAMdown(stack <Point> downG, Point*downM,int size_downM)
{
	downG.push(downM[0]);
	Point prevtopDOWN=downM[0];
	downG.push(downM[1]);
	int i=2;
	while  (i<size_downM)
		{
			if(isLeft(prevtopDOWN,downG.top(),downM[i])>0)
			{
				prevtopDOWN=downG.top();
				downG.push(downM[i]);
				i++;
				continue;
			}
			if(isLeft(prevtopDOWN,downG.top(),downM[i])==0)
			{
				if((downG.top().X<downM[i].X)||(downG.top().Y<downM[i].Y))
				{
					downG.pop();
					prevtopDOWN=downG.top();
					downG.push(downM[i]);
					i++;
					continue;
				}
				else
				{
					i++;
					continue;
				}
			}
			if(isLeft(prevtopDOWN,downG.top(),downM[i])<0)
			{
				if(downG.size()>2)
				{
					downG.pop();
					Point tmp=downG.top();
					downG.pop();
					prevtopDOWN=downG.top();
					downG.push(tmp);
					continue;
				}
				else
				{
					downG.pop();
					prevtopDOWN=downG.top();
					downG.push(downM[i]);
					i++;
					continue;
				}
			}
		}
	return downG;
}
stack <Point> GRAHAM (stack <Point> G, Point*P,int k)
{
	G.push(P[0]);
	Point prevtop=P[0];
	G.push(P[1]);
	int i=2;
	while (i<k)
	{
		if(isLeft(prevtop,G.top(),P[i])>0)
		{
			prevtop=G.top();
			G.push(P[i]);
			i++;
			continue;
		}
		if(isLeft(prevtop,G.top(),P[i])==0)
		{
			G.pop();
			prevtop=G.top();
			G.push(P[i]);
			i++;
			continue;
		}
		if(isLeft(prevtop,G.top(),P[i])<0)
		{
			G.pop();
			Point tmp=G.top();
			G.pop();
			prevtop=G.top();
			G.push(tmp);
			continue;
		}
	}
	return G;
}
void ERROR(Point *GR,int G_Size,Point *ConvexHullR,  int ConvexHull_Size)
{
	if(ConvexHull_Size==G_Size)
	{
		int error=0;
		for (int i = 0; i < G_Size; i++)
			if ((ConvexHullR[i].X==GR[G_Size-1-i].X)&&(ConvexHullR[i].Y==GR[G_Size-1-i].Y))
				error=0;
			else
				error++;
		if(error==0)
			cout<<endl<<"GOOD"<<endl;
		else
			cout<<"error"<<endl;
	}
	else
	{
		cout<<"error"<<endl;
	}
}
void FULL_GRAHAM(Point *P,int k,double &timeprog1,Point *GR,int &G_Size,int var)
{
	double t_start,t_end;
t_start=clock();
	//ищем нижнюю левую точку
	int number_leftP=0;
	Point leftP = P[0];
/*#pragma omp parallel
	cout << "OpenMP Test" << endl;*/
#pragma omp for
	for (int i = 0; i < k; i++)
		if ((leftP.X > P[i].X)||((leftP.X==P[i].X)&&(leftP.Y > P[i].Y)))
		{
			leftP = P[i];
			number_leftP=i;
		}
		
	if(k<=10)
		cout<<endl<<"Left_Point = "<<'('<<leftP.X<<','<<leftP.Y<<')'<<endl<<endl;

	P[number_leftP].pX=0;P[number_leftP].pY=-1;
	swap(P[0],P[number_leftP]);
	if(k<=10)
				cout<<'{'<<P[0].X<<','<<P[0].Y<<'}'<<'<'<<P[0].pX<<','<<P[0].pY<<'>'<<endl;
	for (int i=1;i<k;i++)
	{
			P[i].pX=P[i].X-leftP.X;
			P[i].pY=P[i].Y-leftP.Y;
			if(k<=10)
				cout<<'{'<<P[i].X<<','<<P[i].Y<<'}'<<'<'<<P[i].pX<<','<<P[i].pY<<'>'<<endl;
	}

	if(var==1)
		qsort(P,k,sizeof(Point),compare);
	else
		heap_sort(P,k,1);
	if(k<10)
	{
		cout<<endl<<"PSort"<<endl;
		for(int i=0;i<k;i++)
			cout<<'{'<<P[i].X<<','<<P[i].Y<<'}'<<'<'<<P[i].pX<<','<<P[i].pY<<'>'<<endl;
	}
	stack <Point> G;
	G=GRAHAM(G,P,k);

t_end=clock();
timeprog1=t_end-t_start;
	G_Size=G.size();
	GR=new Point[G_Size]; 
	for (int i=0;i<G_Size;i++)
	{
		GR[i]=G.top();
		G.pop();
	}
	if(k<10)
	{
		cout<<endl<<"ConvexHull"<<endl;
		for (int i=G_Size-1;i>=0;i--)
			cout<<'('<<GR[i].X<<','<<GR[i].Y<<')'<<endl;
	}
}
void FULL_ANDREW(Point *PR,int k,double &timeprog2,Point *ConvexHullR,int &ConvexHull_Size,int var)
{
	double t_start,t_end;
	Point downP,upP;
t_start=clock();
	//ищем нижнюю левую точку
	downP = PR[0];
	for (int i = 0; i < k; i++)
		if ((downP.X > PR[i].X)||((downP.X==PR[i].X)&&(downP.Y > PR[i].Y)))
			downP = PR[i];

	if(k<=10)
		cout<<endl<<"DownP = "<<'('<<downP.X<<','<<downP.Y<<')'<<endl;
	//ищем верхнюю правую точку
	upP = PR[0];
	for (int i = 0; i < k; i++)
    	if ((upP.X < PR[i].X)||((upP.X==PR[i].X)&&(upP.Y < PR[i].Y)))
			upP = PR[i];
	if(k<=10)
		cout<<"UpP = "<<'('<<upP.X<<','<<upP.Y<<')'<<endl;

	Point *downM;
	downM=new Point[k];
	Point *upM;
	upM=new Point[k];
	int i=0;
	int size_downM=0;
	int size_upM=0;
	while(i<k)
	{
		if((upP.Y-downP.Y)*PR[i].X+(downP.X-upP.X)*PR[i].Y+(upP.X*downP.Y-downP.X*upP.Y)>0)
		{
			downM[size_downM]=PR[i];
			i++;
			size_downM++;
			continue;
		}
		if((upP.Y-downP.Y)*PR[i].X+(downP.X-upP.X)*PR[i].Y+(upP.X*downP.Y-downP.X*upP.Y)<0)
		{
			upM[size_upM]=PR[i];
			i++;
			size_upM++;
			continue;
		}
		if((upP.Y-downP.Y)*PR[i].X+(downP.X-upP.X)*PR[i].Y+(upP.X*downP.Y-downP.X*upP.Y)==0)
		{
			downM[size_downM]=PR[i];
			upM[size_upM]=PR[i];
			size_upM++;
			i++;
			size_downM++;
			continue;
		}
	}
	
	//Обход Грэхэма
	if (var==1)
		qsort(downM,size_downM,sizeof(Point),compareA);
	else
		heap_sort(downM,size_downM,0);
	stack <Point> downG;
	downG = GRAHAMdown(downG, downM,size_downM);
	int size_downG=downG.size();

	//Обход Грэхэма
	if(var==1)
		qsort(upM,size_upM,sizeof(Point),compareA);
	else
		heap_sort(upM,size_upM,0);
	stack <Point> upG;
	upG=GRAHAMup(upG,upM,size_upM);
	int size_upG=upG.size();
t_end=clock();
timeprog2=t_end-t_start;
stack <Point> ConvexHull;
	stack <Point> tmp;
	upG.pop();
	for(int h=0;h<size_upG-2;h++)
	{
		tmp.push(upG.top());
		upG.pop();
	}
	for(int h=0;h<size_upG-2;h++)
	{
		ConvexHull.push(tmp.top());
		tmp.pop();
	}
	for(int h=0;h<size_downG;h++)
	{
		ConvexHull.push(downG.top());
		downG.pop();
	}
	ConvexHull_Size=ConvexHull.size();
	ConvexHullR=new Point[ConvexHull_Size]; 
	for (int i=0;i<ConvexHull_Size;i++)
	{
		ConvexHullR[i]=ConvexHull.top();
		ConvexHull.pop();
	}
	if(k<10)
	{
		cout<<endl<<"ConvexHull2"<<endl;
		for (int i=0;i<=ConvexHull_Size-1;i++)
		{
			cout<<'('<<ConvexHullR[i].X<<','<<ConvexHullR[i].Y<<')'<<endl;
		}
	}
}
void RANDOM_POINT(Point *P,Point *PR,Point *PH,Point *HR,int k)
{
	srand(time(NULL));
	for (int i=0;i<k;i++)
	{
		P[i].X=rand()%(k)+1;
		P[i].Y=rand()%(k)+1;
		PR[i]=P[i];
		PH[i]=P[i];
		HR[i]=P[i];
	}
	if(k<=10)
	{
		cout<<endl<<"P"<<endl;
		for (int i=0;i<k;i++)
			cout<<'('<<P[i].X<<','<<P[i].Y<<')'<<endl;
	}
}

void main(int argc, char *argv[])
{
	int GRQ_Size=0,ARQ_Size=0,GRH_Size=0,ARH_Size=0;
	unsigned int k = 100;
	double G_QS_TIME=0,A_QS_TIME=0,G_HS_TIME=0,A_HS_TIME=0;
	cin >> k;
	Point *ConvexHull_GR_QSORT=new Point[GRQ_Size]; 
	Point *ConvexHull_AR_QSORT=new Point[ARQ_Size];
	Point *ConvexHull_GR_HSORT=new Point[GRH_Size]; 
	Point *ConvexHull_AR_HSORT=new Point[ARH_Size];
	//int k=atoi(argv[1]);
	Point *GP_QS=new Point[k];
	Point *AP_QS=new Point[k];
	Point *GP_HS=new Point[k];
	Point *AP_HS=new Point[k];
	RANDOM_POINT(GP_QS,AP_QS,GP_HS,AP_HS,k);
	FULL_GRAHAM(GP_QS,k,G_QS_TIME,ConvexHull_GR_QSORT,GRQ_Size,1);
	cout<<endl<<"Graham_QS = "<<G_QS_TIME<<endl;
	cout << endl << "Size_QS = " << GRQ_Size << endl;
	delete[] GP_QS;
	delete[] ConvexHull_GR_QSORT;
	FULL_GRAHAM(GP_HS,k,G_HS_TIME,ConvexHull_GR_HSORT,GRH_Size,0);
	cout<<endl<<"Graham_HS = "<<G_HS_TIME<<endl;
	delete[] GP_HS;
	delete[] ConvexHull_GR_HSORT;
	FULL_ANDREW(AP_QS,k,A_QS_TIME,ConvexHull_AR_QSORT,ARQ_Size,1);
	cout<<endl<<"Andrew_QS = "<<A_QS_TIME<<endl;
	delete[] AP_QS;
	delete[] ConvexHull_AR_QSORT;
	FULL_ANDREW(AP_HS,k,A_HS_TIME,ConvexHull_AR_HSORT,ARH_Size,0);
	cout<<endl<<"Andrew_HS = "<<A_HS_TIME<<endl;
	delete[] AP_HS;
	delete[] ConvexHull_AR_HSORT;
	//ERROR(ConvexHull_GR_QSORT,GRQ_Size,ConvexHull_AR_QSORT,ARQ_Size);
	system("pause");
}