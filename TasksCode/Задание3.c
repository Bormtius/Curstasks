#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define size 4

void showField(int[][size]);
void RandomField(int[][size],int*,int*);
void Game(int[][size],int[][size],int*,int*,int,int);
void RobotRandomField(int[][size],int*,int*);
void Switchlines(int[][size],int*,int*);
bool checkWin(int[][size],int[][size]);
int checkNum(int,int,int[][size],int);

//Основная часть где производится выбор режима игры
int main()
{
	int x1=3,y1=3,key,n;
	int Field[size][size]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};
	int WinField[size][size]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};
	int *x=&x1,*y=&y1;
	srand(time(NULL));
	do{
	printf("Выберите режим игры\n0-Выключить игру\n1-Стандартный режим 4x4\n2-Робот замешивает фишки\n3-Через введённое количество шагов искомая нумерация меняется\n4-Текущая нумерация меняется через введённое количество шагов\n");
	scanf("%d",&key);
	switch(key)
	{
		case 0:
			printf("Выключение");
		break;
		case 1:
			RandomField(Field,y,x);
			Game(Field,WinField,y,x,key,n);	
		break;
		case 2:
			RobotRandomField(Field,y,x);
			Game(Field,WinField,y,x,key,n);	
		break;
		case 3:
			printf("Введите через сколько ходов будет меняться искомая нумерация ");
			scanf("%d",&n);
			RandomField(Field,y,x);
			Game(Field,WinField,y,x,key,n);	
		break;
		case 4:
			printf("Введите через сколько ходов будет меняться текущая нумерация ");
			scanf("%d",&n);
			RandomField(Field,y,x);
			Game(Field,WinField,y,x,key,n);	
		break;
	}
	}while(key!=0);
	return 0;
}

//Функция, которая выводит на экран поля клеток и позволяет передвигать фишки
void Game(int F[][size],int WinF[][size],int *y,int *x,int key,int n)
{
	system("clear");
	printf("Искомая нумерация\n");
	showField(WinF);
	printf("Текущая нумерация\n");
	printf("Количество ходов = 0\n");
	showField(F);
	int x2,y2,turn = 0,turns =0;
	do//Зацикленная смена фишек
	{
		int selchip=0,ok=0; //Одноразовая смена фишки
		do{
			printf("Введите номер фишки,которую хотите передвинуть в пустую клетку\n");
			scanf("%d",&selchip);
			for(int i=0;i<size;i++)
			for(int j=0;j<size;j++)
			{
				if((((i==*y+1||i==*y-1)&&j==*x)||((j==*x+1||j==*x-1)&&i==*y))&&F[i][j]==selchip)
				{
					x2=j;
					y2=i;
					ok=1;
					break;
				}
			}
			if(ok==1)
			{
			F[y2][x2]=F[*y][*x];
			F[*y][*x]=selchip;
			*y=y2;
			*x=x2;
			turn++;
			turns++;
			}
			else 
			{
				printf("Неправильный ввод, попробуйте заново\n");
				system("sleep 1");
			}
			if(turn==n && key == 3)
			{
			RandomField(WinF,0,0);
			turn=0;
			}
			else if(turn==n && key == 4)
			{
			Switchlines(F,y,x);
			turn=0;
			}
			system("clear");
			printf("Искомая нумерация\n");
			showField(WinF);
			printf("Текущая нумерация\n");
			printf("Количество ходов = %d\n",turns);
			showField(F);
		}while(ok!=1);
	}while(checkWin(F,WinF)==false);
	printf("Победа\n");
}
//Функция для вывода на экран поля 
void showField(int F[][size])
{
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
		if(F[i][j]>9) printf("\t|%d|", F[i][j]);
		else if(F[i][j]<10) printf("\t|%d |", F[i][j]);
		else if(F[i][j]==0) printf("\t|  |");
		}
	printf("\n");
	}
	printf("\n\n");
}

//Функция для заполнения поля фишками в случайном порядке
void RandomField(int F[][size],int *y,int *x)
{
    for(int i=0;i<size;i++)
    for(int j=0;j<size;j++)
	{
        do F[i][j]=rand()%16;
		while(checkNum(i,j,F,F[i][j]) != 0);
		if(F[i][j]==0 && y!=0 && x!=0)
		{
			*x=j;
			*y=i;
		}
    }
}
//Функция для замешивания фишек роботом
void RobotRandomField(int F[][size],int *y,int *x)
{
	int Fnums[4]={0},nums,selchip,pastchip=0,it=0,allit;
	printf("Введите количество шагов робота ");
	scanf("%d",&allit);
	do{
	nums=0;
	for(int i=0;i<4;i++)
		Fnums[i]=0;
	
	for(int i=0;i<size;i++)
	for(int j=0;j<size;j++)
	{
		if((((i==*y+1||i==*y-1)&&j==*x)||((j==*x+1||j==*x-1)&&i==*y)))
		{
			Fnums[nums]=F[i][j];
			nums++;
		}
	}
	do
	selchip = rand()%4;
	while(Fnums[selchip]==0 || Fnums[selchip] == pastchip );
	
	for(int i=0;i<size;i++)
	for(int j=0;j<size;j++)
		if(Fnums[selchip] == F[i][j])
		{
			selchip = F[i][j];
			F[i][j]=F[*y][*x];
			F[*y][*x]= selchip;
			pastchip = selchip;
			*x=j;
			*y=i;
			break;
		}
	it++;
	showField(F);
	system("sleep 1");
	system("clear");
	}while(it!=allit);
}
//Функция, меняющая местами строки либо столбцы
void Switchlines(int F[][size],int *y,int *x)
{
	int numline1=rand()%4,numline2,c=rand()%2,save;
	do numline2=rand()%4;
	while(numline1==numline2);
	switch(c)
	{
	case 0:
	for(int i=0;i<size;i++)
	{
		save = F[i][numline1];
		F[i][numline1]= F[i][numline2];
		F[i][numline2]=save;
	}
	break;
	case 1:
	for(int i=0;i<size;i++)
	{
		save = F[numline1][i];
		F[numline1][i]= F[numline2][i];
		F[numline2][i]=save;
	}
	break;
	}
	for(int i=0;i<size;i++)
    for(int j=0;j<size;j++)
	{
		if(F[i][j]==0 && y!=0 && x!=0)
		{
			*x=j;
			*y=i;
		}
    }
	
}
//Функция проверки, существует ли уже в массиве данное число
int checkNum(int i1,int j1,int F[][size],int num)
{
	int numpos=i1*4+j1,pos=0;
	for(int i=0;i<size;i++)
	{
	for(int j=0;j<size;j++)
	{
		if(pos==numpos)
		break;
		pos++;
		if(F[i][j]==num)
		{
		return 1;
		}
	}
	}
	return 0;
}
//Функция проверки, собрана ли искомая нумерация фишек
bool checkWin(int F[][size],int WinF[][size])
{
	for(int i=0;i<size;i++)
	for(int j=0;j<size;j++)
	if(F[i][j]!=WinF[i][j])
	return false;
	return true;
}

