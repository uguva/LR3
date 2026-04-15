package main

import (
	"fmt"
	"math"
)

func gcd(a, b uint64) uint64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func main() {
	var a, b uint64
	fmt.Scan(&a, &b)

	if b == 1 {
		fmt.Println("infinity")
		return
	}

	// Создаем матрицу для чисел Эйлера
	A := make([][]uint64, a+1)
	for i := range A {
		A[i] = make([]uint64, a+1)
	}

	if a >= 1 {
		A[1][1] = 1
	}

	for i := uint64(2); i <= a; i++ {
		for j := uint64(1); j <= i; j++ {
			A[i][j] = (i-j+1)*A[i-1][j-1] + j*A[i-1][j]
		}
	}

	var num uint64 = 0
	for k := uint64(1); k <= a; k++ {
		bPow := uint64(math.Pow(float64(b), float64(a+1-k)))
		num += A[a][k] * bPow
	}

	den := uint64(math.Pow(float64(b-1), float64(a+1)))

	div := gcd(num, den)
	fmt.Printf("%d/%d\n", num/div, den/div)
}
