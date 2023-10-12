#include <iostream>
#include <time.h>
#include <Windows.h>
#include <cstdio>

using namespace std;


void initData(double** matrix, double* v, int size);

void printMatrix(double** matrix, double* v, int size);

void deleteMatrix(double** matrix, double* v, int size);

double* gauss(double** matrix, double* v, int size);

int main()
{
	SetConsoleOutputCP(1251);   // Устанавливаем кодировку для windows

	const int size = 3; // Размерность матрицы
	double** matrix = new double*[size]; // Наша матрица
	for (int i = 0; i < size; i++)
		matrix[i] = new double[size];
	double* v = new double[size]; // Правая сторона матрицы после =
	double* result; // Массив где будут ответы

	// Инициализируем и выводим матрицу на экран
	initData(matrix, v, size);
	cout << "Наша матрица:" << endl;
	printMatrix(matrix, v, size);

	// Запуска Гаусса
	result = gauss(matrix, v, size);
	cout << endl << "Результат:" << endl;
	for (int i = 0; i < size; i++)
		cout << "x[" << i << "]=" << result[i] << endl;

	// Очищаем память
	deleteMatrix(matrix, v, size);

	return 0;
}

// Инициализируем и заполняем нашу матрицу данными
void initData(double** matrix, double *v, int size) {
	matrix[0][0] = 6.0;
	matrix[0][1] = 0.6;
	matrix[0][2] = 0.5;
	v[0] = 41.0;

	matrix[1][0] = 0.6;
	matrix[1][1] = 5.0;
	matrix[1][2] = 0.4;
	v[1] = 30.2;

	matrix[2][0] = 0.5;
	matrix[2][1] = 0.4;
	matrix[2][2] = 4.0;
	v[2] = 21.0;
}

// Функция вывода матрицы на экран
void printMatrix(double** matrix, double* v, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j] << "*x" << j + 1;
			if (j < size - 1)
				cout << " + ";
		}
		cout << " = " << v[i] << endl;
	}
}

// Очищаем память
void deleteMatrix(double** matrix, double* v, int size) {
	for (int i = 0; i < size; i++)
		delete matrix[i];
	delete matrix;
	delete v;
}

double* gauss(double** matrix, double* v, int size) {
	double max;
	int k = 0, index;

	const double eps = 0.00001; // Зададим точность
	
	while (k < size) {
		//Поиск строки с максимальным a[i][k]
		max = abs(matrix[k][k]); // Считаем что максимальный элемент самый первый
		index = k;
		// Начинаем поиск со следующей строки
		for (int i = k + 1; i < size; i++) {
			if (abs(matrix[i][k]) > max) {
				max = abs(matrix[i][k]);
				index = i; 
				// Находим новый максимальный элемент и запоминаем его индекс
			}
		}

		if (max < eps) { // Проверка на пустоту
			cout << "Решения не существует из-за нулевого столбца ";
			cout << index << " матрицы" << endl;
			return 0;
		}

		// Меняем строки местами
		for (int j = 0; j < size; j++)
			swap(matrix[index][j], matrix[k][j]);
		swap(v[index], v[k]);

		// Начинаем нормальзацию уравнения
		for (int i = k; i < size; i++) {
			double tmp = matrix[i][k];

			if (abs(tmp) < eps) 
				continue; // Если коэфициент нулевой, пропускаем
			for (int j = 0; j < size; j++)
				matrix[i][j] /= tmp;  // Делим поэлментно
			v[i] /= tmp; // Делим правую часть матрицы

			if (i == k)
				continue; // Невычитаем сами из себя
			for (int j = 0; j < size; j++)
				matrix[i][j] -= matrix[k][j];
			v[i] -= v[k];
		}
		k++;
		
		cout << endl << k << " итерация цикла" << endl;
		printMatrix(matrix, v, size);
	}

	double* result = new double[size]; // Массив с ответами

	// Запускаем обратную подстановку
	for (k = size - 1; k >= 0; k--) {
		result[k] = v[k];
		for (int i = 0; i < k; i++)
			v[i] -= (matrix[i][k] * result[k]);
	}

	return result;
}