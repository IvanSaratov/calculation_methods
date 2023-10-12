#include <iostream>
#include <time.h>
#include <Windows.h>
#include <cstdio>

using namespace std;

double rightAnswer(double x);
double func(double x, double y);

int main()
{
	SetConsoleOutputCP(1251);   // Устанавливаем кодировку для windows

	const double a = 1; // Начало интервала
	const double b = 2; // Конец интервала
	const int n = 50;
	const double h = (b - a) / (n - 1); // Шаг интегрирования
	double x, k1, k2, k3, k4;

	double y[n];
	y[0] = 2; // Начальное значение по условию
	
	// Метод Рунге-Кутта
	for (int i = 0; i < n - 1; i++) {
		x = a + i * h;
		k1 = h * func(x, y[i]);
		k2 = h * func(x + h / 2, y[i] + k1 / 2);
		k3 = h * func(x + h / 2, y[i] + k2 / 2);
		k4 = h * func(x + h, y[i] + k3);
		y[i + 1] = y[i] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
	}

	// Сравнение с аналитическим решением
	for (int i = 0; i < n; i++) {
		x = a + i * h;
		cout << "X: " << x << " подсчитанное нами: " << y[i] << " аналитическое: " << rightAnswer(x) << endl;
	}

	return 0;
}

// Точное решение по заданию
double rightAnswer(double x) {
	return ((log(x) + 2) * pow(x, 2));
}

// Диф. уравнение по заданию
double func(double x, double y) {
	return ((pow(x, 2) + 2 * y) / x);
}