/* Лабораторная работа 7. Вариант 11.
  Реализовать звёздный каталог, в котором для каждой звезды представлена следующая
  информация: название, видимая величина, расстояние до Земли, координаты на небосклоне,
  Обеспечивать сортировку записей по расстоянию до Земли и поиск по видимой величине. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[11];
  double m, h, azimuth, earthRange;
} Star;

int inputStar(Star *star) {
  if(star == NULL)
    return 0;

    char buf[100];

  while(printf("Имя звезды: "),
  fflush(stdin), strlen(fgets(buf, 100, stdin)) > 10)
    printf("ОШИБКА: длина имени не должна превышать 10 символов. Попробуйте ещё раз.\n");

  strcpy(star->name, buf);

  while(printf("Блеск звезды: "),
  fflush(stdin), scanf("%lg", &star->m) != 1)
    printf("ОШИБКА: данные введены неправильно. Попробуйте ещё раз.\n");

  while(printf("Расстояние до Земли, в а.е.: "),
  fflush(stdin), scanf("%lg", &star->earthRange) !=1)
    printf("ОШИБКА: данные введены неправильно. Попробуйте ещё раз.\n");

  while(printf("Азимут: "), fflush(stdin),
  scanf("%lg", &star->azimuth) !=1)
    printf("ОШИБКА: данные введены неправильно. Попробуйте ещё раз.\n");

  while(printf("Высота на небосклоне: "),
  fflush(stdin), scanf("%lg", &star->h) !=1)
    printf("ОШИБКА: данные введены неправильно. Попробуйте ещё раз.\n");

  return 1;
}

int printStar(Star* star) {
  if(star == NULL)
    return 0;

  printf("\n");
  printf("Имя звезды: ");
  puts(star->name);
  printf("Расстояние до Земли: %lg а.е.\n", star->earthRange);
  printf("Блеск звезды: %lg\n", star->m);
  printf("Азимут: %lg\n", star->azimuth);
  printf("Высота: %lg\n", star->h);

  return 1;
}

int compare(Star *star1, Star *star2) {
  if (star1 == NULL || star2 == NULL)
    return -1;

  if (star1->earthRange > star2->earthRange)
    return 1;
  else
    return 0;
}

int main() {
  system ("chcp 1251 > nul");

  Star star1, star2;

  printf("Введите данные первой звезды: \n");
  inputStar(&star1);

  printf("\n");

  printf("Введите данные второй звезды: \n");
  inputStar(&star2);

  printf("\nВЫВОД\n");

  printStar(&star1);
  printStar(&star2);

  printf("Наибольшее расстояние до Земли: ");
  if (compare(&star1, &star2) == 1)
    printf("%lg", star1.earthRange);
  else if(compare(&star1, &star2) == 0)
    printf("%lg", star2.earthRange);
  else printf("ОШИБКА");

  return 0;
}
