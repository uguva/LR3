#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    int pavel_score = 0, vika_score = 0;
    int idx = 0;
    int prev_k = 0;
    bool pavel_turn = true;

    while (idx < n) {
        long long max_sum = -1e18; // очень маленькое число
        int best_k = 0;
        int limit = min(m, n - idx);

        for (int k = 1; k <= limit; k++) {
            if (k == prev_k) continue; // Правило 2 варианта

            long long current_sum = 0;
            for (int i = 0; i < k; i++) {
                current_sum += arr[idx + i];
            }

            if (current_sum > max_sum) {
                max_sum = current_sum;
                best_k = k;
            }
        }

        // Если ходов нет из-за ограничений, вынуждены прервать или пропустить
        if (best_k == 0) break;

        if (pavel_turn) pavel_score += max_sum;
        else vika_score += max_sum;

        idx += best_k;
        prev_k = best_k;
        pavel_turn = !pavel_turn;
    }

    if (pavel_score > vika_score) cout << 1 << endl;
    else cout << 0 << endl;

    return 0;
}
