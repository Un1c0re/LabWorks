/* Лабораторная работа 8.
  Реализовать звёздный каталог, в котором для каждой звезды представлена следующая
  информация: название, видимая величина, расстояние до Земли, координаты на небосклоне,
  Обеспечивать сортировку записей по расстоянию до Земли и поиск по видимой величине. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ШАГ 1: Структуры и функции, реализованные в лабораторной работе №7 */

typedef double coords;

typedef struct {
   char name[200];
   double m, earth_range;
   coords h, azimuth;
} Star;

/* Ввод параметров звезды */
int input_star(Star *star) {
   if(star == NULL)
      return 0;

   while(printf("Имя звезды: "),
   fflush(stdin), gets(star->name), strlen(star->name) > 200)
      printf("ОШИБКА: длина имени не должна превышать 200 символов. Попробуйте ещё раз.\n");

   while(printf("Блеск звезды: "),
   fflush(stdin), scanf("%lg", &star->m) != 1)
      printf("ОШИБКА: данные введены неправильно. Попробуйте ещё раз.\n");

   while(printf("Расстояние до Земли, в а.е.: "),
   fflush(stdin), scanf("%lg", &star->earth_range) !=1)
      printf("ОШИБКА: данные введены неправильно. Попробуйте ещё раз.\n");

   while(printf("Азимут: "),
   fflush(stdin), scanf("%lg", &star->azimuth) !=1)
      printf("ОШИБКА: данные введены неправильно. Попробуйте ещё раз.\n");

   while(printf("Высота на небосклоне: "),
   fflush(stdin), scanf("%lg", &star->h) !=1)
      printf("ОШИБКА: данные введены неправильно. Попробуйте ещё раз.\n");

   return 1;
}

/* Вывод параметров звезды */
int print_star(Star *star) {
   if(star == NULL)
      return 0;

   printf("\n");
   printf("Имя звезды: ");
   puts(star->name);
   printf("Расстояние до Земли: %lg а.е.\n", star->earth_range);
   printf("Блеск звезды: %lg\n", star->m);
   printf("Азимут: %lg\n",star->azimuth);
   printf("Высота: %lg\n", star->h);

   return 1;
}

/* ШАГ 2: Реализация функций для обработки массива струтктур */

/* Поиск по звёздной величине */
void search_by_m(Star stars[], double m, int n) {
   int i;
   for (i = 0; i < n; i++) {
      if (stars[i].m == m)
         print_star(&stars[i]);
   }      
}

/* Компаратор возвращает одно из нескольких значений:
   -1 - если произошла ошибка;
    1 - если из двух величин большая - первая;
    0 - если из двух величин большая - вторая, либо обе равны */
   int compare(Star *star1, Star *star2) {
   if (star1 == NULL || star2 == NULL)
      return -1;

   if (star1->earth_range > star2->earth_range)
      return 1;

   else return 0;
}

/*Сортировка по расстоянию до Земли (Метод сортировки "пузырьком") */
void sort_by_range(Star *star, int n) {
   int i, j;
   for (i = 0; i < n-1; i++) 
      for (j = 1; j < n - i; j++)
         if (compare(&star[i], &star[i+1])) {
            Star temp;
            temp = star[i];
            star[i] = star[i+1];
            star[i+1] = temp;
         }
}

/*ШАГ 3 - Работа с файлами*/

#define LEN 100

/* Сохранение файла */
int save() {
   FILE *file;
   file = fopen("Звёздный каталог.txt", "w");
   if (file != NULL) {
      printf("Файл успешно сохранён!\n");
      return 0;
   }
   else {
      fprintf(stderr, "не удалось сохранить файл.\n");   
      return 1;
   }
}

/* Загрузка файла */
int download(Star *arr) {
   char catalog[LEN];
   FILE *file;
   file = fopen("Звёздный каталог.txt", "r+a");
   if (file !=NULL) {
      while(fgets(catalog, LEN, file)) /* Получаем данные из файла */
         fprintf(stdout, "%s\n", catalog);
      fputs(arr, file);
   }
}

/* Удаление файла */

/* ШАГ 4 - ГЛАВНАЯ ФУНКЦИЯ: Реализация интерактивного интерфейса */

#define N 25 /* Задаем максимальное количество переменных списка */

int main() {
   system("chcp 1251 > nul");

   Star arr[N];
   int n = 0, key, k, i;
   double m = 0;
   
   do {
      system ("cls"); /* Очищаем экран */
      printf("Выберите, что необходимо сделать:\n");
      printf("1. Вывести каталог звёзд;\n");
      printf("2. Добавить звезду в каталог;\n");
      printf("3. Найти звёзду по её звёздной величине;\n");
      printf("4. Сохранить файл;\n");
      printf("5. Загрузить файл;\n");
      printf("6. Удалить файл;\n");
      printf("7. Выход\n");
      fflush(stdin); /*Очищаем память */

      if (scanf("%d", &key) != 1)
         key = -1;
      switch (key) {

         case 1: /*Вывести каталог звёзд */
         sort_by_range(&arr[n], n);
         for (i = 0; i < n; i++)
            print_star(&arr[i]);
         system("pause");
            break;

         case 2: /*Добавить звезду в каталог */
            if (n < N) {
               printf("Введите параметры %d звезды\n", n+1);
               input_star(&arr[n]);
               n++;
            }
            else
               printf("\aОШИБКА: вы ввели максимальное количество звёзд!\n");
            break;

         case 3: /*Найти звёзду по её звёздной величине */
            printf("Введите видимую звёздную величину искомой звезды: ");
            scanf("%lg", &m);
            search_by_m(arr, m, n);
            system("pause");
            break;

         case 4: /*Выход */
            return 0;
            break;

         default:
            printf("ОШИБКА: попробуйте ещё раз");
            break;
      }
   } while (key);

   system("pause");
   return 0;
}