/* Лабораторная работа 8.
  Реализовать звёздный каталог, в котором для каждой звезды представлена следующая
  информация: название, видимая величина, расстояние до Земли, координаты на небосклоне,
  Обеспечивать сортировку записей по расстоянию до Земли и поиск по видимой величине. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   char name[16];
   double m, earth_range;
   double h, azimuth;
} Star;


/* Ввод параметров звезды */
int input_star(Star *star) {
   if(star == NULL)
      return 0;
   
   char buf[100];

   while(printf("Имя звезды: "),
   fflush(stdin), strlen(fgets(buf, 100, stdin)) > 15)
      printf("ОШИБКА: длина имени не должна превышать 15 символов. Попробуйте ещё раз.\n");
   strcpy(star->name, buf);

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

   printf("\n-------------------------\n");
   printf("Имя звезды: ");
   puts(star->name);
   printf("Расстояние до Земли: %lg а.е.\n", star->earth_range);
   printf("Блеск звезды: %lg\n", star->m);
   printf("Азимут: %lg\n",star->azimuth);
   printf("Высота: %lg\n", star->h);

   return 1;
}


/* Поиск по звёздной величине */
void search_by_m(Star stars[], double a, double b, int n) {
   int i;
   for (i = 0; i < n; i++) {
      if (stars[i].m >= a && stars[i].m <= b)
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
   else 
      return 0;
}


/* Сортировка по расстоянию до Земли (Метод сортировки "пузырьком") */
void sort_by_range(Star *star, int n) {
   int i, j;
   for (i = 1; i < n; i++)
      for (j = 0; j < n - i; j++)
         if (compare(&star[j], &star[j+1])) {
            Star temp;
            temp = star[j];
            star[j] = star[j+1];
            star[j+1] = temp;
         }
}


/* Сохранение файла */
void saveFile(Star *catalog, int n, char *name) {
   FILE *file;
   int i;
   file = fopen(name, "w");
   if (file != NULL) {
      for (i = 0; i < n; i++)
         fprintf(file, "%lf", catalog[i].m);
      printf("Файл успешно сохранён!\n");
   }
   else fprintf(stderr, "Не удалось сохранить файл.\n");
   fclose(file);
}


/* Загрузка файла */
int loadFile(Star *catalog, int n, char *name) {
   FILE *file;
   int i;
   char line[255];

   file = fopen(name, "r");
   if (file) {
      for (i = 0; i < n; i++) {
         fgets(line, n, file);
      }

      printf("Файл успшно загружен!\n");
      
      for (i = 0; i < n; i++) 
         printf("%.3lf\n", line);

      fclose (file);
      return i;
   }

   printf("Ошибка загрузки файла.\n");
   return 0;
}

#define N 25 /* Задаем максимальное количество переменных списка */

int main() {
   system("chcp 1251 > nul");

   Star arr[N];
   int n = 0, key, i;
   int var, count;
   double a, b;
   char name;
   
   do {
      system ("cls"); /* Очищаем экран */
      printf("Выберите, что необходимо сделать:\n");
      printf("1. Вывести каталог звёзд;\n");
      printf("2. Добавить звезду в каталог;\n");
      printf("3. Удалить звезду из каталога;\n");
      printf("4. Найти звёзду по её звёздной величине;\n");
      printf("5. Сохранить файл;\n");
      printf("6. Загрузить файл;\n");
      printf("7. Удалить файл;\n");
      printf("8. Выход\n");
      fflush(stdin); /*Очищаем память */

      if (scanf("%d", &key) != 1)
         key = -1;
      switch (key) {

         case 1: /* Вывести каталог звёзд */
            sort_by_range(arr, n);
            for (i = 0; i < n; i++)
               print_star(&arr[i]);

            system("pause");
            break;

         case 2: /* Добавить звезду в каталог */
            if (n < N) {
               printf("Введите параметры %d звезды\n", n+1);
               input_star(&arr[n]);
               n++;
               printf("\nЗвезда успешно добавлена в каталог!\n");
            }
            else printf("\aОШИБКА: вы ввели максимальное количество звёзд!\n");

            system("pause");
            break;

         case 3: /* Удалить звезду из каталога */
            printf("Выберите звезду, которую хотите удалить: \n");
            for(i = 0; i < n; i++) {
               count = i + 1;
               printf("%d - ", count);
               puts(arr[i].name);
            }

            while(fflush(stdin), scanf("%d", &var) != 1 || var > n)
               printf("ОШИБКА: нет звезды с введенным номером. Попробуйте ещё раз\n");

            for(i = var-1; i < n; i++)
               arr[i] = arr[i+1];
            n--;
            printf("Звезда успешно удалена из каталога.\n");

            system("pause");
            break;

         case 4: /* Найти звёзду по её звёздной величине */
            while(printf("Введите диапазон значений (через пробел): "), 
            fflush(stdin), scanf("%lg%lg", &a, &b) != 2 || a >=b)
               printf("ОШИБКА: данные введены неправильно. попробуйте ещё раз.\n");

            search_by_m(arr, a, b, n);

            system("pause");
            break;

         case 5: /* Сохранить файл */
            printf("Введите имя сохраняемого файла: ");
            scanf("%s", &name);
            saveFile(arr, n, &name);

            printf("Файл успешно сохранен!");
            system("pause");
            break;

         case 6: /* Загрузить файл */
            printf("Введите имя файла, который вы хотите загрузить: ");
            scanf("%s", &name);

            loadFile(arr, n, &name);

            printf("Файл успешно загружен!\n");
            system("pause");
            break;

         case 7: /* Удалить файл */
            printf("Введите имя файла, который вы хотите удалить: ");
            /*name =  ввод имени файла */

            /* функция удаления */

            printf("Файл успешно удалён!");
            system("pause");
            break;


         case 8: /* Выход */
            return 0;
            break;

         default:
            printf("ОШИБКА: что-то пошло не так. Попробуйте ещё раз.\n");
            
            system("pause");
            break;
      }
   } while (key);

   system("pause");
   return 0;
}
