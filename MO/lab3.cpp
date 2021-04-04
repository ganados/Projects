#include <iostream>
#include <cmath>

#define LICZBA_ITERACJI 30
#define TOLF pow(10.0, -10)
#define TOLX pow(10.0, -10)

double sinKwadrat(double x) {
	return (pow(sin(x / 4.0), 2.0) - x);

}
double sinPochodna(double x) {
	return ((1.0 / 4.0) * sin(x / 2) - 1.0);
}
double tangens(double x) {
	return (tan(x * 2.0) - x - 1.0);
}
double tangensPochodna(double x) {
	return (2.0 / (pow(cos(2.0 * x), 2.0)) - 1.0);
}
double sinPicard(double x) {
	return (pow(sin(x / 4.0), 2.0));
}
double tanPicard(double x) {
	return (tan(2.0 * x) - 1);
}
double sinPochodnaPicard(double x) {
	return ((1.0 / 4.0) * sin(x / 2));
}
double tanPochodnaPicard(double x) {
	return (2.0 / (pow(cos(2.0 * x), 2.0)));
}

typedef double(*pointer)(double); //wskaznik na funkcje, aby uniknac dublowania sie funkcji obslugujacych metody iteracyjne
								  //bez tego, musialbym napisac po 2 funkcje Picard, Newton, Sieczne, Bisekcji osobno dla
								  //funkcji sin jak i tangens

void Picard(pointer fMain, pointer fPicard, pointer fPicardDeriv, double x){
	if (fabs(fPicardDeriv(x) >= 1.0)) {
		std::cout << "Rozbieznosc funkcji\n";
		return;
	}
	double estymatorBledu = 0.0;
	double reziduum = 0.0;
	double result = x;

	std::cout << "--------------------------------------------------------------------------------------------------\n";
	std::cout << "| \tNumer Iteracji\t | \tPrzyblizenie\t | \tEstymator bledu\t | \tReziduum\t |";
	std::cout << "\n--------------------------------------------------------------------------------------------------\n";

	int i = 0;
	for (i = 0; i < LICZBA_ITERACJI; i++) { // pierwszy warunek zakonczenia iteracji (dotarcie do maksymalnej liczby iteracji)
		result = fPicard(result);
		estymatorBledu = fabs(result - x);
		reziduum = fabs(fMain(result));
		x = result;
		std::cout << "\t" << i << "\t\t\t" << result << "\t\t" << estymatorBledu << "\t\t" << reziduum << "\t\n";

		if (estymatorBledu <= TOLX) {
			std::cout << "\nEstymator bledu mniejszy niz tolerancja";
			break;
		}
		else if (reziduum <= TOLF) {
			std::cout << "\nReziduum mniejszy niz tolerancja";
			break;
		}
	}
	if (i == LICZBA_ITERACJI)
		std::cout << "\nUzyskana maksymalna liczba iteracji";
}

void Bisekcja(pointer funkcja, double a, double b) {
	double averageAB = 0.0, estymatorBledu = 0.0;
	if ((funkcja(a) < 0 && funkcja(b) < 0) || (funkcja(a) > 0 && funkcja(b) > 0)) {
		std::cout << "\nW przedziale nie ma zmiany znaku, blad";
		return;
	}

	std::cout << "----------------------------------------------------------------------------------------------------------\n";
	std::cout << "| \tNumer Iteracji\t | \ta\t | \tb\t | \tEstymator Bledu\t | \tReziduum\t |";
	std::cout << "\n----------------------------------------------------------------------------------------------------------\n";
	int i = 0;
	double reziduum = 0.0;
	for (i = 0; i < LICZBA_ITERACJI; i++) {
		averageAB = (a + b) / 2.0;
		estymatorBledu = fabs((b - a) / 2.0);
		reziduum = fabs(funkcja(averageAB));
		std::cout << "\t" << i << "\t\t\t" << a << "\t\t" << b << "\t\t\t" << estymatorBledu << "\t\t" << reziduum << "\t\n";

		// ograniczenie przedzialu, sprawdzenie warunkow, dla ktorych nastepuje zmiana znaku
		if ((funkcja(a) < 0 && funkcja(averageAB) > 0) || (funkcja(a) > 0 && funkcja(averageAB) < 0))
			b = averageAB;
		else if ((funkcja(b) < 0 && funkcja(averageAB) > 0) || (funkcja(b) > 0 && funkcja(averageAB) < 0))
			a = averageAB;
		else {
			std::cout << "\nBrak pierwiastka w przedziale" << std::endl;
			break;
		}

		if (estymatorBledu <= TOLX) {
			std::cout << "\nPowod zatrzymania iteracji: Estymator bledu mniejszy niz tolerancja";
			break;
		}
		else if (reziduum <= TOLF) {
			std::cout << "\nPowod zatrzymania iteracji: Reziduum mniejszy niz tolerancja";
			break;
		}
	}
	if (i == LICZBA_ITERACJI)
		std::cout << "\nPowod zatrzymania iteracji: Uzyskana maksymalna liczba iteracji";
}

void Newton(pointer mainFun, pointer derivFun, double x) {
	
	double estymatorBledu = 0.0, reziduum = 0.0, xNext = 0.0, xPrev = x;


	std::cout << "--------------------------------------------------------------------------------------------------\n";
	std::cout << "| \tNumer Iteracji\t | \txNext\t\t | \tEstymator Bledu\t | \tReziduum\t |";
	std::cout << "\n--------------------------------------------------------------------------------------------------\n";
	int i = 0;

	for(i = 0; i < LICZBA_ITERACJI; i++){
		if (derivFun(xPrev) != 0) {
			xNext = xPrev - (mainFun(xPrev) / derivFun(xPrev));
			estymatorBledu = fabs(xNext - xPrev);
			xPrev = xNext;
			reziduum = fabs(mainFun(xPrev));

			std::cout << "\t" << i << "\t\t\t" << xNext << "\t\t" << estymatorBledu << "\t\t" << reziduum << "\t\n";
		}

		if (estymatorBledu <= TOLX) {
			std::cout << "\nPowod zatrzymania iteracji: Estymator bledu mniejszy niz tolerancja";
			break;
		}
		else if (reziduum <= TOLF) {
			std::cout << "\nPowod zatrzymania iteracji: Reziduum mniejszy niz tolerancja";
			break;
		}
	}
	if (i == LICZBA_ITERACJI)
		std::cout << "\nPowod zatrzymania iteracji: Uzyskana maksymalna liczba iteracji";
}

void Sieczne(pointer mainFun, double x, double x1) {
	double xNext = 0.0, estymatorBledu = 0.0, reziduum = 0.0;

	std::cout << "--------------------------------------------------------------------------------------------------\n";
	std::cout << "| Numer Iteracji | \tx\t\t | \t\tEstymator Bledu\t | \tReziduum\t |";
	std::cout << "\n--------------------------------------------------------------------------------------------------\n";

	int i = 0;
	for (i = 0; i < LICZBA_ITERACJI; i++) {
		xNext = x1 - (mainFun(x1) / ((mainFun(x1) - mainFun(x)) / (x1 - x)));
		estymatorBledu = fabs(xNext - x1);
		reziduum = fabs(mainFun(xNext));

		std::cout << "\t" << i << "\t\t" << xNext << "\t\t\t" << estymatorBledu << "\t\t" << reziduum << "\t\n";
		if (estymatorBledu <= TOLX) {
			std::cout << "\nPowod zatrzymania iteracji: Estymator bledu mniejszy niz tolerancja";
			break;
		}
		else if (reziduum <= TOLF) {
			std::cout << "\nPowod zatrzymania iteracji: Reziduum mniejszy niz tolerancja";
			break;
		}
		x = x1;
		x1 = xNext;
	}
	if (i == LICZBA_ITERACJI)
		std::cout << "\nPowod zatrzymania iteracji: Uzyskana maksymalna liczba iteracji";
}



int main() {
	std::cout << "Funkcja sinus: " << std::endl;
	std::cout << "Picard" << std::endl;
	Picard(sinKwadrat, sinPicard, sinPochodnaPicard, 0.5);
	std::cout << std::endl << std::endl << "Bisekcja" << std::endl;
	Bisekcja(sinKwadrat, -0.1, 0.7);
	std::cout << std::endl << std::endl << "Newton" << std::endl;
	Newton(sinKwadrat, sinPochodna, 0.5);
	std::cout << std::endl << std::endl << "Sieczne" << std::endl;
	Sieczne(sinKwadrat, 0.1, 0.7);

	std::cout << std::endl << std::endl <<"Funkcja tangens: " << std::endl;
	std::cout << "Picard" << std::endl;
	Picard(tangens, tanPicard, tanPochodnaPicard, 0.5);
	std::cout << std::endl << std::endl << "Bisekcja" << std::endl;
	Bisekcja(tangens, 0.4, 0.5);
	std::cout << std::endl << std::endl << "Newton" << std::endl;
	Newton(tangens, tangensPochodna, 0.5);
	std::cout << std::endl << std::endl << "Sieczne" << std::endl;
	Sieczne(tangens, 0.1, 0.7);

	return 0;
}