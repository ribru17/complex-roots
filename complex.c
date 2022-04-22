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

void squareQuaternion(int results[5], int a, int b, int c, int d) {
    double newA = a*a - b*b - c*c - d*d;
    double newB = 2 * a * b;
    double newC = 2 * a * c;
    double newD = 2 * a * d;
    int res = sqrt(newA*newA + newB*newB + newC*newC + newD*newD);
    results[0] = round(newA);
    results[1] = round(newB);
    results[2] = round(newC);
    results[3] = round(newD);
    results[4] = round(res);
}

int main() {
    double n;
    double a;
    double b;
    double results[2];
    printf("Enter n, a, b, for n raised to the complex number a + bi\n");
    scanf("%lf%lf%lf", &n, &a, &b);
    computeRoot(results, n, a, b);
    printf("Answer: %lf + %lfi\n", results[0], results[1]);
    int t;
    printf("Enter terms to add\n");
    scanf("%d", &t);
    double sumResults[2];
    computeSeries(sumResults, t, a, b);
    printf("Results: %lf + %lfi\n", sumResults[0], sumResults[1]);
    int qa;
    int qb;
    int qc;
    int qd;
    int quintupleResults[5];
    printf("Enter integers a, b, c, d, for q = a + bi + cj + dk\n");
    scanf("%d%d%d%d", &qa, &qb, &qc, &qd);
    squareQuaternion(quintupleResults, qa, qb, qc, qd);
    printf("Pythagorean quintuple: %d%c + %d%c + %d%c + %d%c = %d%c", quintupleResults[0], 253, quintupleResults[1], 253, quintupleResults[2], 253, quintupleResults[3], 253, quintupleResults[4], 253);
    return 0;
}