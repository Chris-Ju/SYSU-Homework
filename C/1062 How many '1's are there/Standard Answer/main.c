#include <stdio.h>
int bitcount(int x) {
        int count = 0;
        while (x != 0) {
                x &= (x-1);
                count++;
        }
        return count;
}
 
int main() {
        int num;
        int x;
        scanf("%d", &num);
 
        while (num--) {
                scanf("%d", &x);
                printf("%d\n", bitcount(x));
        }
        return 0;
}
