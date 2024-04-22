#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
    // Определяем доступные фильтры: b - Blur, g - Grayscale, r - Reflection, s - Sepia
    char *filters = "bgrs";

    // Получаем флаг фильтра и проверяем корректность
    char filter = getopt(argc, argv, filters);
    if (filter == '?')
    {
        printf("Invalid filter.\n");
        return 1;
    }

    // Убеждаемся, что выбран один фильтр
    if (getopt(argc, argv, filters) != -1)
    {
        printf("Only one filter allowed.\n");
        return 2;
    }

    // Убеждаемся в правильном использовании
    if (argc != optind + 2)
    {
        printf("Usage: ./filter [flag] infile outfile\n");
        return 3;
    }

    // Запоминаем имена файлов
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    // Открываем файл на чтение
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // Открываем файл на запись
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    // Читаем BITMAPFILEHEADER из файла (первые байты файла - заголовочные)
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Читаем BITMAPINFOHEADER из файла
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Убеждаемся, что это 24-бит несжатый BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {

        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 6;
    }

    // Получаем размеры изображения
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // ВЫДЕЛЯЕМ ПАМЯТЬ !АККУРАТНО - НЕ ЗАБЫТЬ ПОЧИСТИТЬ!
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);
        fclose(inptr);
        return 7;
    }

    // Определяем отступы строк
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // итеррируем по строкам
    for (int i = 0; i < height; i++)
    {
        // Читать строку в массив пикселей
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);

        // Пропустить заполнение
        fseek(inptr, padding, SEEK_CUR);
    }

    // ФИЛЬТРЫ
    switch (filter)
    {
        // Blur
        case 'b':
            blur(height, width, image);
            break;

        // Grayscale
        case 'g':
            grayscale(height, width, image);
            break;

        // Reflection
        case 'r':
            reflect(height, width, image);
            break;

        // Sepia
        case 's':
            sepia(height, width, image);
            break;
    }

    // Запись BITMAPFILEHEADER в файл (заголовок)
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Запись BITMAPINFOHEADER в файл (заголовок)
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Запись новых пикселей в файл
    for (int i = 0; i < height; i++)
    {
        // Записывааем строку в файл (куском сразу)
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // Пишем отступ в конце строки
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // ОЧИЩАЕМ ТУТ
    free(image);

    // ЗАКРЫВАЕМ ТУТ
    fclose(inptr);
    fclose(outptr);

    //успех (.) (.) -- 0======3
    return 0;
}
