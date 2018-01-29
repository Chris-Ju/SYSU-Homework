#include <stdio.h>
#include <memory.h>
#include <string.h>
int main()
{
    int r, c, n, m, i, k, times = 0;;
    scanf("%d %d", &r, &c);
    m = r * c;
    char mat[r][c + 1];
    char str[r * c + 1];
    memset(mat, 0, sizeof(mat));
    memset(str, 0, sizeof(str));
    for(i = 0; i < r; i++)
        scanf("%s ",mat[i]);
    scanf("%d", &n);
    char fuck[n][10];
    memset(fuck, 0, sizeof(fuck));
    for(i = 0; i < n; i++)
        scanf("%s", fuck[i]);
    i = 0;
    while(1)
    {
        for(int j = times; j < r - times; j++)
            str[i++] = mat[j][times];
        if(i >= m)
            break;
        for(int j = times + 1; j < c - times; j++)
            str[i++] = mat[r - times - 1][j];
        if(i >= m)
            break;
        for(int j = r - times - 2; j >= times; j--)
            str[i++] = mat[j][c - times - 1];
        if(i >= m)
            break;
        for(int j = c - times - 2; j > times; j--)
            str[i++] = mat[times][j];
        if(i >= m)
            break;
        times++;
    }
    printf("%s\n", str);
    for(i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(k = 0; k < strlen(fuck[j]); k++)
            {
                if(str[i + k] != fuck[j][k])
                    break;
            }
            if(k == strlen(fuck[j]))
            {
                for(k = 1; k < strlen(fuck[j]); k++)
                    str[i + k] = '*';
                i = i + strlen(fuck[j]) - 1;
                break;
            }

        }
    }
    printf("%s\n", str);
    return 0;
}
