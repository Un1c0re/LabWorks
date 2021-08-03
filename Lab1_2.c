/* 	Лабораторная работа 1
    Вариант 34. 
	Задан год. Определить количество дней в году.  */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	system ("chcp 1251 >nul");
	
	int days, year, a;
	
	printf("Введите год: ");
	scanf("%d", &year);
	
	days = 365 + ((year-year%4)/year) - ((year - year%100)/year) + ((year-year%400)/year);
	printf("Количество дней в году: %d\n", days);
	
	system("pause");
	return 0;
}
