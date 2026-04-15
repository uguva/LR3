#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <set>

using namespace std;

// Шаг 1: Построить таблицу простых чисел, меньших 500
vector<uint64_t> getPrimes(int max_val) {
    vector<bool> is_prime(max_val + 1, true);
    vector<uint64_t> primes;
    for (int p = 2; p * p <= max_val; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= max_val; i += p)
                is_prime[i] = false;
        }
    }
    for (int p = 2; p <= max_val; p++) {
        if (is_prime[p]) primes.push_back(p);
    }
    return primes;
}

int bitLength(uint64_t n) {
    int bits = 0;
    while (n > 0) { bits++; n >>= 1; }
    return bits;
}

// Безопасное умножение по модулю (исправление ошибки C2065/C2146)
uint64_t mulMod(uint64_t a, uint64_t b, uint64_t mod) {
    uint64_t res = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) res = (res + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}

uint64_t powerMod(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = mulMod(res, base, mod);
        base = mulMod(base, base, mod);
        exp /= 2;
    }
    return res;
}

// Процедура тестирования Миллера
bool millerTestProcedure(uint64_t n, const vector<uint64_t>& q_factors, int t) {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dist(2, n - 1);

    for (int j = 0; j < t; j++) {
        uint64_t a = dist(gen);
        if (powerMod(a, n - 1, n) != 1) return false;
    }

    for (uint64_t q : q_factors) {
        bool found_a = false;
        for (int j = 0; j < t; j++) {
            uint64_t a = dist(gen);
            if (powerMod(a, (n - 1) / q, n) != 1) {
                found_a = true;
                break;
            }
        }
        if (!found_a) return false;
    }
    return true;
}

// Шаг 2: Реализовать процедуру генерации чисел-кандидатов заданной разрядности
void generateCandidate(int bits, const vector<uint64_t>& primes, uint64_t& n, vector<uint64_t>& q_factors) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> prime_dist(0, primes.size() - 1);

    while (true) {
        uint64_t m = 1;
        set<uint64_t> qs;
        
        while (bitLength(m) < bits - 1) {
            uint64_t q = primes[prime_dist(gen)];
            if (m > UINT64_MAX / q) break;
            uint64_t next_m = m * q;
            if (bitLength(next_m) > bits - 1) break;
            m = next_m;
            qs.insert(q);
        }

        if (bitLength(m) != bits - 1) continue;

        n = 2 * m + 1;
        
        // Убедимся, что итоговое число n имеет ровно нужную разрядность bits
        if (bitLength(n) != bits) continue;

        q_factors.assign(qs.begin(), qs.end());
        q_factors.push_back(2);
        break;
    }
}

int main() {
    int bits;
    cout << "Входные данные (bits): ";
    if (!(cin >> bits) || bits < 4 || bits > 60) return 0;

    // Шаг 1: Построить таблицу простых чисел
    vector<uint64_t> primes = getPrimes(500);

    cout << "-----------------------------------------------------------------\n";
    cout << "| №  | Простое число | Результат проверки | Отвергнутых (rejected)|\n";
    cout << "-----------------------------------------------------------------\n";

    // Шаг 3: Построить 10 различных чисел-кандидатов
    for (int i = 1; i <= 10; i++) {
        
        // Шаг 4: Переменная rejected
        int rejected = 0;
        uint64_t candidate_n;
        vector<uint64_t> q_factors;

        // Шаг 5: Каждое построенное число проверить тестом
        while (true) {
            // Генерируем кандидата
            generateCandidate(bits, primes, candidate_n, q_factors);
            
            // Проверяем базовым тестом (t=1)
            bool is_prime_t1 = millerTestProcedure(candidate_n, q_factors, 1);
            
            if (!is_prime_t1) {
                // Шаг 5.a: не простое -> генерируем новое, увеличиваем rejected
                rejected++;
            } else {
                // Шаг 5.b: простое -> переходим к шагу 6
                break;
            }
        }

        // Шаг 6: Дополнительная проверка при t=2
        bool final_result = millerTestProcedure(candidate_n, q_factors, 2);

        // Шаг 7: Вывод и переход к следующему кандидату
        cout << "| " << setw(2) << i << " | " 
             << setw(13) << candidate_n << " | " 
             << setw(18) << (final_result ? "true" : "false") << " | " 
             << setw(21) << rejected << " |\n";
    }
    cout << "-----------------------------------------------------------------\n";

    return 0;
}
