/* Лабораторная работа 10.
  Реализовать звездный каталог, в котором для каждой звезды представлена следующая
  информация: название, видимая величина, расстояние до Земли, координаты на небосклоне,
  Обеспечивать сортировку записей по расстоянию до Земли и поиск по видимой величине. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   char name[16];
   double m, earthRange;
   double h, azimuth;
} Star;


/* Ввод параметров звезды */
int inputStar(Star *star) {
   if(star == NULL)
      return 0;

   char buf[100];

   while(printf("Имя звезды (Если имя составное, вводите через _): "),
   fflush(stdin), strlen(fgets(buf, 100, stdin)) > 15)
      printf("ОШИБКА: длина имени не должна превышать 15 символов. Попробуйте еще раз.\n");
   strncpy(star->name, buf, strlen(buf)-1);

   while(printf("Блеск звезды: "),
   fflush(stdin), scanf("%lg", &star->m) != 1)
      printf("ОШИБКА: данные введены неправильно. Попробуйте еще раз.\n");

   while(printf("Расстояние до Земли: "),
   fflush(stdin), scanf("%lg", &star->earthRange) !=1)
      printf("ОШИБКА: данные введены неправильно. Попробуйте еще раз.\n");

   while(printf("Азимут: "),
   fflush(stdin), scanf("%lg", &star->azimuth) !=1)
      printf("ОШИБКА: данные введены неправильно. Попробуйте еще раз.\n");

   while(printf("Высота на небосклоне: "),
   fflush(stdin), scanf("%lg", &star->h) !=1)
      printf("ОШИБКА: данные введены неправильно. Попробуйте еще раз.\n");

   return 1;
}


/* Вывод параметров звезды */
int printStar(Star *star) {
   if(star == NULL)
      return 0;

   printf("\n-------------------------\n");
   printf("Имя звезды: ");
   puts(star->name);
   printf("Расстояние до Земли: %lg\n", star->earthRange);
   printf("Блеск звезды: %lg\n", star->m);
   printf("Азимут: %lg\n", star->azimuth);
   printf("Высота: %lg\n", star->h);

   return 1;
}


/* Поиск по звездной величине */
void searchByM(Star stars[], double a, double b, int n) {
   int i;
   for (i = 0; i < n; i++) {
      if (stars[i].m >= a && stars[i].m <= b)
         printStar(&stars[i]);
   }  
}


/* Компаратор возвращает одно из нескольких значений:
   -1 - если произошла ошибка;
    1 - если из двух величин большая - первая;
    0 - если из двух величин большая - вторая, либо обе равны */
   int compare(Star *star1, Star *star2) {
   if (star1 == NULL || star2 == NULL)
      return -1;

   if (star1->earthRange > star2->earthRange)
      return 1;
   else 
      return 0;
}


/* Сортировка по расстоянию до Земли (Метод сортировки "пузырьком") */
void sortByRange(Star *star, int n) {
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
void saveFile(Star list[], int n, char *name) {
   FILE *file;
   file = fopen(name, "w");
   if(!file) {
      fprintf(stderr, "Не удалось сохранить файл.\n");
      return;
   }

   int i;
   fprintf(file, "%d\n", n);
   for (i = 0; i < n; i++)
      fprintf(file, "%s %.3lf %.3lf %.3lf %.3lf\n",
         list[i].name, list[i].earthRange, list[i].m, list[i].azimuth, list[i].h);
   printf("Файл успешно сохранен!\n");

   fclose(file);
}


/* Загрузка файла */
void loadFile(Star **list, int *n, char *name) {
   FILE *file;
   file = fopen(name, "r");
   if(!file){
      fprintf(stderr, "Не удалось загрузить файл.\n");
      return;
   }


   int i;
   if(fscanf(file, "%d", n) != 1) {
      printf("ОШИБКА: Данные файла повреждены (количество переменных)\n");
      fclose(file);
      return;
   }
   *list = malloc(*n*sizeof(Star));
   if(!(*list)) {
      printf("ОШИБКА: неудалось выделить память при загрузке\n");
      fclose(file);
      return;
   }
   for (i = 0; i < *n; i++) {
      if (fscanf(file, "%s%lf%lf%lf%lf",
      (*list)[i].name, &(*list)[i].earthRange, &(*list)[i].m, 
      &(*list)[i].azimuth, &(*list)[i].h) != 5) {
         
         printf("ОШИБКА: данные файла повреждены (параметры переменных)\n");
         free(*list);
         *list = NULL;
         *n = 0;
         fclose(file);
         return;
      } 
   }

   printf("Файл успешно загружен!\n");
   fclose(file);
}

void addData(Star list[]) {
   Star sun = {"Солнце", -26.7, 0.5, 36.6, 45.5};
   Star polar = {"Полярная_звезда", 2, 137.4, 12.12, 11.04};
   Star sirius = {"Сириус", 1.46, 2.64, 5.01, 44.44};

   list[0] = sun;
   list[1] = polar;
   list[2] = sirius;
}

int main() {
   system("chcp 1251 > nul");

   Star *arr = NULL, *t, temp;
   int n = 3, key, i, j;
   int var, del;
   double a, b;
   char filename[32];

   arr = (Star*) malloc(n*sizeof(Star));  /* выделить блок - динамический массив */
      if(!arr) {
         printf("ОШИБКА: неудалось выделить память\n");
         return -1;
      }

   addData(arr);

   do {
      system ("cls"); /* Очищаем экран */
      printf("Количество звёзд в каталоге: %d\n", n);
      printf("Выберите, что необходимо сделать:\n");
      printf("1. Вывести каталог звезд;\n");
      printf("2. Добавить звезду в каталог;\n");
      printf("3. Удалить звезду из каталога;\n");
      printf("4. Найти звезду по ее звездной величине;\n");
      printf("5. Сохранить файл;\n");
      printf("6. Загрузить файл;\n");
      printf("7. Удалить каталог;\n");
      printf("8. Выход\n");
      fflush(stdin); /* Очищаем память */


      if (scanf("%d", &key) != 1)
         key = -1;
      switch (key) {

         case 1: /* Вывести каталог звезд */
            sortByRange(arr, n);
            for (i = 0; i < n; i++)
               printStar(&arr[i]);

            system("pause");
            break;

         case 2: /* Добавить звезду в каталог */
            t = (Star*) realloc(arr, (n+1)*sizeof(Star));
            if(t) {
               arr = t;
               printf("Введите параметры %d звезды\n", n+1);
               inputStar(&arr[n]);
               n++;
               printf("\nЗвезда успешно добавлена в каталог!\n");
            }
            else
               printf("ОШИБКА: проблемы с памятью при добавлении\n");  

            system("pause");
            break;

         case 3: /* Удалить звезду из каталога */
            printf("Выберите звезду, которую хотите удалить: \n");
            for(i = 0; i < n; i++) {
               del = i + 1;
               printf("%d - %s", del, arr[i].name);
               printf("\n");
            }
            while(fflush(stdin), scanf("%d", &var) != 1 || var > n)
               printf("ОШИБКА: нет звезды с введенным номером. Попробуйте еще раз\n");

            for(i = var-1; i < n-1; i++) {
               for(j = var; j < n; j++) {
                  temp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = temp;
               }
            }

            t = (Star*) realloc(arr, (n-1)*sizeof(Star));
            if(t) {
               arr = t;
               printf("Звезда успешно удалена из каталога.\n");
               n--;
            }
            else
               printf("ОШИБКА: проблемы с памятью при удалении\n");

            var = 0;

            system("pause");
            break;

         case 4: /* Найти звезду по ее звездной величине */
            while(printf("Введите диапазон значений (через пробел): "), 
            fflush(stdin), scanf("%lg%lg", &a, &b) != 2 || a >=b)
               printf("ОШИБКА: данные введены неправильно. попробуйте еще раз.\n");
            searchByM(arr, a, b, n);

            system("pause");
            break;

         case 5: /* Сохранить файл */
            if(n > 0) {
               printf("Введите имя сохраняемого файла: ");
               scanf("%s", filename);
               saveFile(arr, n, filename);
            }
            else
               printf("ОШИБКА: каталог пуст. Добавьте звезду, чтобы сохранить файл\n");

            system("pause");
            break;

         case 6: /* Загрузить файл */
            free(arr);
            arr = NULL;
            n = 0;
            printf("Введите имя файла, который вы хотите загрузить: ");
            scanf("%s", filename);
            loadFile(&arr, &n, filename);

            if(!arr) {
               n = 3;
               arr = (Star*) malloc(n*sizeof(Star));
               addData(arr);
            }

            system("pause");
            break;

         case 7: /* Удалить данные */
            if(arr) {
               printf("Вы действительно хотите удалить каталог? (Введите 0 для отмены): ");
               scanf("%d", &var);

               if (var == 0)
                  printf("Удаление отменено\n");
               else {
                  free(arr);
                  arr = NULL;
                  n = 0;

                  printf("Каталог успешно удален!\n");
               }
            }
            else 
               printf("ОШИБКА: каталог уже удален\n");

            system("pause");
            break;

         case 8: /* Выход */
            if(arr) {
               free(arr);
               arr = NULL;
               n = 0;
            }
            return 0;

         default:
            printf("ОШИБКА: что-то пошло не так. Попробуйте еще раз.\n");

            system("pause");
            break;
      }
   } while (key);

   system("pause");
   return 0;
}
