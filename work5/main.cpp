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

	double a = 1; // Начало интервала
	double b = 2; // Конец интервала
	const int n = 50; // Число точек численного решения
	double h = (b - a) / (n - 1); // Шаг интегрирования
	double y[n]; // Искомое значение
	y[0] = 2; // Начальное условия по заданию
	double x; // Независимая переменная

	// Метод Эллера
	for (int i = 1; i < n; i++) {
		x = a + i * h;
		y[i] = y[i - 1] + h * func(x, y[i - 1]);
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