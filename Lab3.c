/*	Лаблраторная работа 3
  	Вариант 27
  	Задано число диапазона unsigned long. Определить, является ли четным количество единиц в его двоичном представлении. */

#include <stdio.h>
#include <stdlib.h>

int main() {

	system ("chcp 1251 > nul");

	int count = 0;
	unsigned long n;

	while (printf("Введите число: "),
		fflush (stdin),
		scanf ("%u", &n)!=1)
  		printf("\aОШИБКА: вы ввели некорректные данные. Попробуйте ещё раз.\n");

	while (n > 0) {
		count = count + n %2;
		n = n/2;
	}

	if (count %2 == 0)
		printf ("Количество единиц в двоичной записи числа является чётным\n");
	else
		printf ("Количество единиц в двоичной записи числа является НЕчётным.\n");

	system ("pause");
	return 0;
}
