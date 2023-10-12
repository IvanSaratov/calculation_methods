#include <iostream>
#include <Windows.h>
#include <cstdio>

using namespace std;


double func(double x);

double integralLeftTriangleFull(const long double a, const long double b, const long double eps);

double integralLeftTriangle(const long double a, const long double b, const long long n);

double integralRightTriangleFull(const long double a, const long double b, const long double eps);

double integralRightTriangle(const long double a, const long double b, const long long n);

double integralSimpson(const long double a, const long double b, const long long n);

double integralTrapezoidal(const long double a, const long double b, const long long n);

int main()
{
	SetConsoleOutputCP(1251);   // Устанавливаем кодировку для windows

	long double result = 0; // Переменная для ответа
	long double a = 1; // Левая граница интегрирования
	long double b = 2; // Правая граница интегрирования
	long double h = 1e9; // Разбиение для Симпсона и трапеций
	long double eps = 0.0001; // Точность вычисления

	cout << "Функция x / (1 * x^2)" << endl << endl;
	cout << "Ответ по методу левых прямоугольников: " << integralRightTriangleFull(a, b, eps) << endl;
	cout << "Ответ по методу правых треугольников: " << integralLeftTriangleFull(a, b, eps) << endl;
	cout << "Ответ по методу Сипсона: " << integralSimpson(a, b, h) << endl;
	cout << "Ответ по методу трапеции (средних треугольников): " << integralTrapezoidal(a, b, h) << endl;

	return 0;
}

// Наша заданная функция по варианту
double func(double x)
{
	return x / (1.0 + x * x);
}

// Функция для вызовы формулы прямоугольников с заданой точностью
double integralLeftTriangleFull(const long double a, const long double b, const long double eps) {
	long double s, s1;
	long long n = 1; // Начальное число шагов

	s1 = integralLeftTriangle(a, b, n); // Первое приближение интеграла
	do {
		s = s1; // Сохраняем предыдущее значение
		n *= 2; // Увеличиваем число шагов в два раза

		s1 = integralLeftTriangle(a, b, n);
	} while (fabs(s1 - s) > eps); // Сравниваем приближение с указанной точностью

	return s1;
}

// Функция для вызовы формулы прямоугольников с заданой точностью
double integralRightTriangleFull(const long double a, const long double b, const long double eps) {
	long double s, s1;
	long long n = 1; // Начальное число шагов

	s1 = integralRightTriangle(a, b, n); // Первое приближение интеграла
	do {
		s = s1; // Сохраняем предыдущее значение
		n *= 2; // Увеличиваем число шагов в два раза

		s1 = integralRightTriangle(a, b, n);
	} while (fabs(s1 - s) > eps); // Сравниваем приближение с указанной точностью

	return s1;
}

// Метод интегрирования левых треугольников
// a и b границы отрезка
// n - точность
double integralLeftTriangle(const long double a, const long double b, const long long n) {
	long double x;
	long double result = 0.0;
	long double fx;

	const double h = (b - a) / n; // Сетка h

	for (int i = 0; i < n; i++) {
		x = a + i * h;
		fx = func(x);
		result += fx;
	}
	return (result * h); //приближенное значение интеграла равно сумме площадей прямоугольников
}

// Ментод правых треугольников
double integralRightTriangle(const long double a, const long double b, const long long n) {
	long double x;
	long double result = 0.0;
	long double fx;

	const double h = (b - a) / n; // Сетка h

	for (int i = 1; i <= n; i++) {
		x = a + i * h;
		fx = func(x);
		result += fx;
	}

	return (result * h);
}

// Интеграл по методу симпсона
// a и b границы отрезка
// n - количество отрезков разбиения
double integralSimpson(const long double a, const long double b, const long long n) {
	const double width = (b - a) / n;

	double result = 0;
	for (int step = 0; step < n; step++) {
		const double x1 = a + step * width;
		const double x2 = a + (step + 1) * width;

		result += (x2 - x1) / 6.0 * (func(x1) + 4.0 * func(0.5 * (x1 + x2)) + func(x2));
	}

	return result;
}


// Интеграл по методу трапеции
// Принимает 3 параметра
// Границы отрезка a и b
// Число промежутков n разбиения
double integralTrapezoidal(const long double a, const long double b, const long long n) {
	const double width = (b - a) / n;

	long double result = 0;

	for (int step = 0; step < n; step++) {
		const double x1 = a + step * width;
		const double x2 = a + (step + 1) * width;

		result += 0.5 * (x2 - x1) * (func(x1) + func(x2));
	}

	return result;
}