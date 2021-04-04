#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>

static int inputNames = 1;

double calcExponent(double xValue) {
    double result = ((1.0 - exp(-xValue)) / xValue);

    return result;
}

double calcTaylor(double xValue) {
    double result = 1.0;
    double stepT = 1.0;
    for (int i = 2; i < 30; i++) {
        stepT *= (xValue / (double)i);
        result += pow(-1.0, (i - 1)) * stepT;
    }
    return result;
}

bool saveIO30(double x, double wartDokladna, double wartWyliczona, double bladBezw1, double bladWzgled1, double TaylorMaclaurin, double bladBezw2, double bladWzgled2, int width = 30) {
    std::string fileName = "daneOut.txt";
    std::ofstream wFile;

    wFile.open(fileName.c_str(), std::ios_base::app);
    if (!wFile.good())
        return false;
    if (inputNames == 1) {
        wFile << std::setw(width) << "x" << std::setw(width) << "Wartosc dokladna" << std::setw(width) << "Wartosc wyliczona" << std::setw(width)
            << "Blad bezwzgledny" << std::setw(width) << "Blad wzgledny" << std::setw(width) << "Wartosc Taylor/Maclaurin"
            << std::setw(width) << "Blad bezwzgledny" << std::setw(width) << "Blad wzgledny" << std::endl;
        inputNames += 1;
    }

    wFile.precision(20);
    wFile.scientific;
    wFile << std::setw(width) << x;
    wFile << std::setw(width) << wartDokladna;
    wFile << std::setw(width) << wartWyliczona;
    wFile << std::setw(width) << bladBezw1;
    wFile << std::setw(width) << bladWzgled1;
    wFile << std::setw(width) << TaylorMaclaurin;
    wFile << std::setw(width) << bladBezw2;
    wFile << std::setw(width) << bladWzgled2;
    wFile << std::endl;

    wFile.close();

    return true;
}

bool save(std::string filePath, long double value, long double value2) {
    std::ofstream wFile;

    wFile.open(filePath.c_str(), std::ios_base::app);
    if (!wFile.good())
        return false;
    wFile.precision(20);
    wFile.scientific;
    wFile << value << "\t" << value2 << std::endl;

    wFile.close();

    return true;
}


int main() {

    std::ifstream rFile;
    std::string fileName = "dane.txt";

    rFile.open(fileName.c_str());

    if (!rFile.good())
        return false;

    double log10x, x, wzorExp;
    double granicaBledu = pow(10.0L, -16);

    double wartWylicz, bezwzgledny1, bezwzgledny2, wzgledny1, wzgledny2, taylorMaclaurin;
    double log10Bezwzgledny;

    while (true) {
        rFile >> log10x >> x >> wzorExp;
        if (!rFile.fail()) {
            wartWylicz = calcExponent(x);
            bezwzgledny1 = fabs(wzorExp - wartWylicz);
            wzgledny1 = fabs(bezwzgledny1 / wzorExp);

            log10Bezwzgledny = log10(fabs(wzgledny1));

            save("log10x.txt", log10x, log10Bezwzgledny);

            if (bezwzgledny1 > granicaBledu) {
                taylorMaclaurin = calcTaylor(x);
                bezwzgledny2 = fabs(wzorExp - taylorMaclaurin);
                wzgledny2 = fabs(bezwzgledny2 / wzorExp);
//                std::cout << bezwzgledny2 << "\t" << wzgledny2 << std::endl;
                if (wzgledny2 != 0) {
                    save("log10x2.txt", log10x, log10(fabs(wzgledny2)));
                    save("log10x3.txt", log10x, log10(fabs(wzgledny2)));
                }
            }
            else {
                taylorMaclaurin = 0;
                bezwzgledny2 = 0;
                wzgledny2 = 0;
                save("log10x3.txt", log10x, log10(fabs(wzgledny1)));
            }
            if (!saveIO30(x, wzorExp, wartWylicz, bezwzgledny1, wzgledny1, taylorMaclaurin, bezwzgledny2, wzgledny2)) {
                std::cout << "Blad zapisu\n" << std::endl;
            }
        }
        else break;
    }

    rFile.close();

    return 0;
}