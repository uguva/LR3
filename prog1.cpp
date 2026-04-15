#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>

using namespace std;

double calculateY(double x) {
    if (x <= -2.0) {
        return (x + 2.0) / 3.0;
    } else if (x > -2.0 && x < 2.0) {
        return tan(x / 2.0);
    } else {
        return 0.5 * x - 1.5; 
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    double x_start, x_end, dx;
    
    cout << "Введите X_нач, X_кон и шаг dx: ";
    if (!(cin >> x_start >> x_end >> dx)) return 0;

    cout << "-----------------------" << endl;
    cout << "|      X      |      Y      |" << endl;
    cout << "-----------------------" << endl;

    for (double x = x_start; x <= x_end; x += dx) {
        cout << "| " << setw(10) << fixed << setprecision(4) << x << " | " 
             << setw(10) << fixed << setprecision(4) << calculateY(x) << " |" << endl;
    }
    cout << "-----------------------" << endl;

    return 0;
}
