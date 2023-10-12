#include <iostream>
#include <time.h>
#include <Windows.h>
#include <cstdio>

using namespace std;

double lagrange(double x_array[], double y_array[], int n, double x);

int main()
{
	SetConsoleOutputCP(1251);   // Устанавливаем кодировку для windows

	const int n = 4;

	double x_array[n] = { 0, 1, 2, 3 };
	double y_array[n] = { 10, 11, 13, 18 };

	for (double x = 0; x < n; x += 0.5) {
		cout << "f(" << x << ") = " << lagrange(x_array, y_array, n, x) << endl;
	}

	return 0;
}

// x_array - массив точек x
// y_array - массив точек y
// n - размерность массива
// x - Значение Х
double lagrange(double x_array[], double y_array[], int n, double x) {
	double result = 0.0;

	//Для избежания эфекта Рунге-Мерей
	if (n > 5)
		return (x <= x_array[n / 2]) ? lagrange(x_array, y_array, (n + 1) / 2, x) : lagrange(&x_array[n / 2], &y_array[n / 2], (n + 1) / 2, x);

	for (int i = 0; i < n; i++) {
		double l = 1.0;
		
		for (int j = 0; j < n; j++) 
			if (j != i)
				l *= (x - x_array[j]) / (x_array[i] - x_array[j]);
	
		result += l * y_array[i];
	}

	return result;
}