 typedef struct table{
    char gender;
    char name[7];
    int id;
    int score;
}Table;
int n;
int cmp0(const void *a,const void *b);
int cmp1(const void *a,const void *b);
int cmp2(const void *a,const void *b);
int cmp3(const void *a,const void *b);
int cmp4(const void *a,const void *b);
void print(Table people[n]);