#include<stdio.h>
#include<string.h>
int main()
{
    int every[10] = {0};
    char str[4] = {0};
    int no, times, num, time, i, n;
    scanf("%d", &times);
    for (no = 0; no < times; no++)
    {
        for (time = 0; time < 10; time++)
            every[time] = 0;
        scanf("%d", &num);
        for (time = 1; time <= num; time++)
        {
            sprintf(str, "%d", time);
            n = strlen(str);
            for (i = 0; i < n; i++)
                switch (str[i])
                {
                case 48: every[0]++; break;
                case 49: every[1]++; break;
                case 50: every[2]++; break;
                case 51: every[3]++; break;
                case 52: every[4]++; break;
                case 53: every[5]++; break;
                case 54: every[6]++; break;
                case 55: every[7]++; break;
                case 56: every[8]++; break;
                case 57: every[9]++; break;
                }
        }
        for (time = 0; time < 9; time++)
            printf("%d ", every[time]);
        printf("%d\n", every[time]);
    }
    return 0;
}
