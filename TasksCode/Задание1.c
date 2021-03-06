#include <stdio.h>//Подключение стандартной библиотеки для ввода и вывод информации
#include <math.h>//Подключение стандартной библиотеки для работы с математическими операциями

//Вход в программу, главная функция
int main()
{
	//Объявление переменных вещественного типа:x-значение x в представлении, e-точность,a1-хранение значения суммы ряда,a2-хранение значения уравнения вычисляемого с помощью математической библиотеки
	float x,e,a1=0,a2=0;
	//Объявление целочисленной переменной для подсчёта количества рядов
	int n = 0; 
	//Вывод на экран запроса о введении точности
	printf("Задайте точность e ");
	//Вход в цикл постусловием
	do{	
		//Ввод точности
		scanf("%f",&e); 
		//Условие,если точность меньше или равна нулю
		if(e<=0)
		//Вывод на экран предупреждения
		printf("Точность должна быть больше нуля\n");
	//Условие цикла,введение точности пока e не станет больше нуля
	}while(e<=0);
	//Вывод на экран запроса о введении значения x
	printf("Задайте значение x "); 
	//Вход в цикл с постусловием
	do{
		//Ввод значения x
		scanf("%f",&x);
		//Условие,если значение не входит в границы x>-1 и x<1
		if(x>=1 || x<=-1)
		//Вывод на экран предупреждения
		printf("Значение не входит в границы\n");
	 //Условие цикла,ввод значения x, пока значение не будет меньше 1 и больше -1
	}while(x>=1 || x<=-1);
	//Вычисление уравнения с помощью математической библиотеки
	a2=(float)1/4*log((1+x)/(1-x))+(float)1/2*atan(x); 
	//Вывод на экран значения x
	printf("Значение x = %f\n",x);
	//Вывод на экран значения уравнения
	printf ("Вычисление с помощью математической библиотеки %f\n",a2);
	//цикл с предусловием,выполняется пока полученный результат не будет соответствовать введённой ранее точности
	while((a1<=a2-e)||(a1>=a2+e))
	{
		//Подсчёт значения с помощью суммы ряда
		a1+=pow(x,4*n+1)/(4*n+1); 
		//Инкрементация количества рядов
		n++;
	}
	//Вывод на экран значение суммы ряда,количества рядов и заданную точность
	printf("Сумма ряда = %f, количество рядов = %d, точность = %f\n",a1,n,e);
	//Возврат нуля в качестве успешного выполнения программы
	return 0;
}