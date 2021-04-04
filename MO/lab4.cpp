#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

#define LICZBA_ITERACJI 30
#define TOLF pow(10, -10)
#define TOLX pow(10, -10)

double f1(double x, double y, double z) {
	return x * x + y * y + z * z - 2.0;
}
double f2(double x, double y) {
	return x * x + y * y - 1.0;
}
double f3(double x, double y) {
	return x * x - y;
}

double getRule(double table[3]) {
	return *std::max_element(table, table + 3);
}

void macierzJakob(double (&table)[3][3], double x, double y, double z) {
	table[0][0] = 0.0;
	table[0][1] = -2.0 * z;
	table[0][2] = -4.0 * y * z;
	table[1][0] = 0.0;
	table[1][1] = -4.0 * x * z;
	table[1][2] = 4.0 * x * z;
	table[2][0] = -2.0 * x * (1.0 + 2.0 * y);
	table[2][1] = 2.0 * x + 4.0 * y;
	table[2][2] = 0.0;
}

double wyznacznikCalc(double x, double y, double z) {
	return (-1.0 / ((4.0 * x * z) * (1.0 + 2.0 * y)));
}

void matrixWyznacznik(double(&table)[3][3], double x, double y, double z, double wyznacznik) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			table[i][j] *= wyznacznik;
		}
	}
}

void deltaCalc(double(&table)[3], double (&jakob)[3][3], double (&wartosc)[3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			table[i] += jakob[i][j] * wartosc[j];
		}
	}
}

void absoluteValue(double(&table)[3], double(&wartosc)[3]) {
	for (int i = 0; i < 3; i++) {
		table[i] = fabs(wartosc[i]);	
	}
}

void Newton(double x, double y, double z) {
	double estymatorBledu = 0.0, reziduum = 0.0;
	double wektorWartosci[3] = { 0, };
	double delta[3] = { 0, };
	double wyznacznik = 0.0;
	double jakobDT[3][3] = { 0, };
	double absWartosc[3] = { 0, };
	double absEstymator[3] = { 0, };

	wektorWartosci[0] = f1(x, y, z);
	wektorWartosci[1] = f2(x, y);
	wektorWartosci[2] = f3(x, y);

	std::cout << "-----------------------------------------------------------------------------------------------------------------\n";
	std::cout << "| Numer Iteracji | \t x \t | \t y \t | \t z \t | \t Estymator bledu | \t Reziduum \t|" << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------------------------------\n";
	
	int i = 0;
	for (i = 0; i < LICZBA_ITERACJI; i++) {
		wyznacznik = wyznacznikCalc(x, y, z);
		macierzJakob(jakobDT, x, y, z);

		delta[0] = 0;
		delta[1] = 0;
		delta[2] = 0;

		matrixWyznacznik(jakobDT, x, y, z, wyznacznik);
		deltaCalc(delta, jakobDT, wektorWartosci);

		absoluteValue(absWartosc, wektorWartosci); // wartosci bezwzgledne konieczne do obliczenia normy
		absoluteValue(absEstymator, delta);

		reziduum = getRule(absWartosc);
		estymatorBledu = getRule(absEstymator);

		std::cout << "|" << std::setw(10) << i << "\t" << std::setw(15) << x << "\t" << std::setw(15) << y << "\t" << std::setw(15) << z << "\t\t"
			<< std::setw(15) << estymatorBledu << "\t\t" << std::setw(15) << reziduum << "\t|" << std::endl;

		if (fabs(reziduum) < TOLF) {
			std::cout << "-----------------------------------------------------------------------------------------------------------------\n\n";
			std::cout << "Tolerancja dla reziduum przekroczona" << std::endl;
			break;
		}
		if (fabs(estymatorBledu) < TOLX) {
			std::cout << "-----------------------------------------------------------------------------------------------------------------\n\n";
			std::cout << "Tolerancja dla estymatora bledu przekroczona" << std::endl;
			break;
		}	

		x -= delta[0];
		y -= delta[1];
		z -= delta[2];

		wektorWartosci[0] = f1(x, y, z);
		wektorWartosci[1] = f2(x, y);
		wektorWartosci[2] = f3(x, y);
	}
	if (i == LICZBA_ITERACJI)
		std::cout << "-----------------------------------------------------------------------------------------------------------------\n\n" <<
		std::endl << "Zostala osiagnieta maksymalna liczba iteracji, przerwanie programu" << std::endl;
}

int main() {
	
	std::cout.precision(10);
	Newton(0.5, 0.5, 1.0);

	return 0;
}