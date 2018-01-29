#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isPrime(int x) {
    if(x == 1) return false;
    for (int i = 2; i <= sqrt(x); ++i) {
        if (x % i == 0)
            return false;
    } 
    return true;
}

int main() {
    int n = 0, m = 0;
    bool found = false;

    scanf("%d%d", &n, &m);
    
    for (int i = n; i <= m; ++i) {
        if (isPrime(i)) {
            printf("%d\n", i);
            found = true;
            break;
        }
    }
    if (!found) printf("none\n");
}
