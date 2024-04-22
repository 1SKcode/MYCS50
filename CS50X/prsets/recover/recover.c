#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check if file has one argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Открываем файл на чтение
    FILE *readf = fopen(argv[1], "r");
    if (readf == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Буфер для считывания блоков данных
    unsigned char buffer[BLOCK_SIZE];

    FILE *jpegFile = NULL;
    int jpegCount = 0;

    while (fread(buffer, BLOCK_SIZE, 1, readf) == 1)
    {
        // Проверяем, является ли блок началом нового файла JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Если уже открыт файл JPEG, закрываем его
            if (jpegFile != NULL)
            {
                fclose(jpegFile);
            }

            // Создаем имя нового файла JPEG
            char filename[8];
            sprintf(filename, "%03d.jpg", jpegCount);

            // Открываем новый файл JPEG для записи
            jpegFile = fopen(filename, "w");
            if (jpegFile == NULL)
            {
                fprintf(stderr, "Could not create %s for writing.\n", filename);
                fclose(readf);
                return 1;
            }

            // Увеличиваем счетчик файлов JPEG
            jpegCount++;
        }

        // Если файл JPEG открыт, записываем данные в него
        if (jpegFile != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, jpegFile);
        }
    }

    // Закрываем последний файл JPEG
    if (jpegFile != NULL)
    {
        fclose(jpegFile);
    }

    //ОЧИЩАЕМ ТУТ

    // ЗАКРЫВАЕМ ТУТ
    fclose(readf);

    // ЖОСКИЙ УСПЕХ
    return 0;
}
