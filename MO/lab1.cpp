#include <iostream>
#include <iomanip>

int main() {
	//DOUBLE
	int counterDouble = 0;
	double xStepDouble = 1.0, xHolderDouble = 1.1;

	while (xHolderDouble > 1.0) {
		xStepDouble *= 0.5; // uzywamy mnozenia zamiast dzielenia, ze wzgledu na ryzyko dzielenia przez zero
					  // w przypadku zaokraglenia do 0, mnozenie eliminuje ten problem
					  // operacje powtarzamy do czasu, az dotrzemy do limitu precyzji 
		xHolderDouble = 1.0 + xStepDouble;
		counterDouble++;
	}
	counterDouble -= 1;
	// po wykonaniu petli xStep to wartosc NI, epsylon to 2*NI, zatem wartosc epsylona:
	std::cout << std::scientific << "Epsylon maszynowy: " << std::setprecision(10) << (2.0 * xStepDouble) << std::endl;
	std::cout << "Liczba bitow mantysy: " << counterDouble;

	// FLOAT
	int counterFloat = 0;
	float xStepFloat = 1.0f, xHolderFloat = 1.1f;

	while (xHolderFloat > 1.0) {
		xStepFloat *= 0.5;
		xHolderFloat = 1.0f + xStepFloat;
		counterFloat++;
	}
	counterFloat -= 1;
	std::cout << std::endl << std::endl;
	std::cout << std::scientific << "Epsylon maszynowy: " << std::setprecision(10) << (2.0 * xStepFloat) << std::endl;
	std::cout << "Liczba bitow mantysy: " << counterFloat;

	return 0;
}