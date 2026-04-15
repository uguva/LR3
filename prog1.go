package main

import (
    "fmt"
    "math"
)

func calculateY(x float64) float64 {
    if x <= -2.0 {
        return (x + 2.0) / 3.0
    } else if x > -2.0 && x < 2.0 {
        return math.Tan(x / 2.0)
    } else {
        return 0.5*x - 1.5
    }
}

func main() {
    var xStart, xEnd, dx float64
    fmt.Print("Введите X_нач, X_кон и шаг dx: ")
    fmt.Scan(&xStart, &xEnd, &dx)

    fmt.Println("-----------------------")
    fmt.Println("|      X      |      Y      |")
    fmt.Println("-----------------------")

    for x := xStart; x <= xEnd; x += dx {
        fmt.Printf("| %11.4f | %11.4f |\n", x, calculateY(x))
    }
    fmt.Println("-----------------------")
}
