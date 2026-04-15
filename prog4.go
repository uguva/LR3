package main

import (
	"fmt"
)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func main() {
	var n, m int
	fmt.Scan(&n, &m)

	arr := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&arr[i])
	}

	pavelScore, vikaScore := 0, 0
	idx := 0
	prevK := 0
	pavelTurn := true

	for idx < n {
		maxSum := -1000000000 // Аналог минус бесконечности
		bestK := 0
		limit := min(m, n-idx)

		for k := 1; k <= limit; k++ {
			if k == prevK {
				continue
			}

			currentSum := 0
			for i := 0; i < k; i++ {
				currentSum += arr[idx+i]
			}

			if currentSum > maxSum {
				maxSum = currentSum
				bestK = k
			}
		}

		if bestK == 0 {
			break
		}

		if pavelTurn {
			pavelScore += maxSum
		} else {
			vikaScore += maxSum
		}

		idx += bestK
		prevK = bestK
		pavelTurn = !pavelTurn
	}

	if pavelScore > vikaScore {
		fmt.Println(1)
	} else {
		fmt.Println(0)
	}
}
