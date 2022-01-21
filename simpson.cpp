#include <iostream>
#include <cmath>
using namespace std;

const int NumberOfIterations = 500;

double compute (double a, double b);

int main() {
    cout << compute (0., 1.);
    return 0;
}

//Function to integrate
double f(const double x) {
    return sin(100 * x) / (x + 1);
}

double arg(const int index, const double a, const double b) {
    return a + (b - a) * index / NumberOfIterations;
}

//Simpson's rule with small grid
double compute (const double a, const double b) {
    double result = 0.;
    for (int i = 1; i < NumberOfIterations; i += 2) {
        result += f(arg(i - 1, a, b)) + 4 * f(arg(i, a, b)) + f(arg(i + 1, a, b));
    }
    return result * (b - a) / NumberOfIterations / 3;
}