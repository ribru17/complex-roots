#include <stdio.h>
#include <math.h>

// n^(a+bi)
void computeRoot(double* results, double n, double a, double b) {
    double re = pow(n, a) * cos(b * log(n));
    double im = sin(b * log(n));
    results[0] = re;
    results[1] = im;
}

// NOTE: for 0 < Re(s) < 1 the series would have to be multiplied
// by 1 / (1 - 2^(1 - s)) but this calculation is omitted as it 
// does not affect the nontrivial zeros
void computeSeries(double* results, int n, double a, double b) {
    results[0] = 0;
    results[1] = 0;
    for (int i = 0; i < n; i++) {
        double toAdd[2];
        computeRoot(toAdd, i + 1, -a, -b);
        if (i % 2 == 0) {
            results[0] += toAdd[0];
            results[1] += toAdd[1];
        } else {
            results[0] -= toAdd[0];
            results[1] -= toAdd[1];
        }
    }
}

int main() {
    double n;
    double a;
    double b;
    double results[2];
    printf("Enter n, a, b for n raised to the complex number a + bi\n");
    scanf("%lf%lf%lf", &n, &a, &b);
    computeRoot(results, n, a, b);
    printf("Answer: %lf + %lfi\n", results[0], results[1]);
    int t;
    printf("Enter terms to add\n");
    scanf("%d", &t);
    double sumResults[2];
    computeSeries(sumResults, t, a, b);
    printf("Results: %lf + %lfi\n", sumResults[0], sumResults[1]);
    return 0;
}