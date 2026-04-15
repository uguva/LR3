#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double T_sr;  // Температура окружающей среды
    double T_k;   // Начальная температура кофе
    double r;     // Коэффициент остывания
    double t_max; // Максимальное время
    double dt;    // Шаг времени

    cout << "=== Моделирование процесса остывания кофе ===" << endl;
    cout << "Введите температуру окружающей среды (T_sr): ";
    cin >> T_sr;
    cout << "Введите начальную температуру кофе (T_k): ";
    cin >> T_k;
    cout << "Введите коэффициент остывания (r): ";
    cin >> r;
    cout << "Введите максимальное время наблюдения: ";
    cin >> t_max;
    cout << "Введите шаг по времени (dt): ";
    cin >> dt;

    cout << "\n----------------------------" << endl;
    cout << "| Время (t) | Темп. кофе |" << endl;
    cout << "----------------------------" << endl;

    for (double t = 0; t <= t_max; t += dt) {
        cout << "| " << setw(9) << fixed << setprecision(2) << t 
             << " | " << setw(10) << fixed << setprecision(4) << T_k << " |" << endl;
        
        // Пересчет температуры на следующий шаг (Метод Эйлера)
        T_k = T_k - r * (T_k - T_sr) * dt;
    }
    cout << "----------------------------" << endl;

    return 0;
}
