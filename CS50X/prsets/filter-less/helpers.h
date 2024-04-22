#include "bmp.h"

// Конвертация изображения в ЧБ - grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Конвертация изображения в сепию - sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]);

// Отражение изображения - reflection
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Размытие - blur
void blur(int height, int width, RGBTRIPLE image[height][width]);
