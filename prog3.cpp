#include <iostream>
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

// Функция вычисления НОД
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}

uint64_t intPow(uint64_t base, uint64_t exp) {
    uint64_t res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) res *= base;
        base *= base;
        exp /= 2;
    }
    return res;
}

// Вся логика вынесена в отдельную функцию, возвращающую строку через return
string calculateSeriesSum(uint64_t a, uint64_t b) {
    if (b == 1) {
        return "infinity";
    }

    // Вычисление чисел Эйлера A(a, k)
    vector<vector<uint64_t>> A(a + 1, vector<uint64_t>(a + 1, 0));
    if (a >= 1) A[1][1] = 1;
    
    for (uint64_t i = 2; i <= a; i++) {
        for (uint64_t j = 1; j <= i; j++) {
            A[i][j] = (i - j + 1) * A[i - 1][j - 1] + j * A[i - 1][j];
        }
    }

    uint64_t num = 0;
    for (uint64_t k = 1; k <= a; k++) {
        uint64_t b_pow = intPow(b, a + 1 - k);
        num += A[a][k] * b_pow;
    }

    uint64_t den = intPow(b - 1, a + 1);

    // Сокращаем дробь
    uint64_t div = gcd(num, den);
    
    return to_string(num / div) + "/" + to_string(den / div);
}

int main() {
    uint64_t a, b;
    
    if (cin >> a >> b) {
        // Вывод результата работы функции
        cout << calculateSeriesSum(a, b) << endl;
    }

    return 0;
}
