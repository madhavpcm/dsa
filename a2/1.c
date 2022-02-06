#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DELETED -2
#define NONE -1
#define h1(x) ((x) % M)
#define h2(x) (LARGEST_PRIME - (x) % LARGEST_PRIME )

static int M = 2;
static int LARGEST_PRIME;
static int C1 = 0, C2 = 1;
static char MODE;

//int h1(const int x)
//{
//    return x % M;
//}
//int h2(const int x)
//{
//    return LARGEST_PRIME - (x) % LARGEST_PRIME;
//}

int qdProbing(const int k, const int i)
{
    return (int)(h1(k) + i * C1 + i * i * C2) % M;
}
int dblHash(const int k, const int i)
{
    return (h1(k) + i * (h2(k))) % M;
}
int hashIt(char ch, const int k, const int i)
{
    if (ch == 'a')
        return qdProbing(k, i);
    else
        return dblHash(k, i);
}
int isPrime(const int n)
{
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}
void setLargestPrime()
{
    int n = M - 1;
    while (!isPrime(n))
        n--;
    LARGEST_PRIME = n;
}
void insertToHashTable(int *HT, const int k)
{
    for (int i = 0; i < M; i++)
    {
        int hi = hashIt(MODE, k, i);
        if (HT[hi] == DELETED || HT[hi] == NONE)
        {
            HT[hi] = k;
            return;
        }
    }
    //printf("-1\n");
}
void deleteFromHashTable(int *HT, const int k)
{
    for (int i = 0; i < M; i++)
    {
        int hi = hashIt(MODE, k, i);
        if (HT[hi] == k)
        {
            HT[hi] = DELETED;
        }
    }
    //printf("-1\n");
}
void searchHashTable(int *HT, const int k)
{
    for (int i = 0; i < M; i++)
    {
        int hi = hashIt(MODE, k, i);
        //printf("[debug] i:%d hi:%d HT[hi]:%d\n", i,hi,HT[hi]);
        if (HT[hi] == k)
        {
            printf("1\n");
            return;
        }
    }
    printf("-1\n");
}
void printHashTable(int *HT)
{
    for (int i = 0; i < M; i++)
    {
        if (HT[i] == NONE || HT[i] == DELETED)
        {
            printf("%d ()\n", i);
        }
        else
        {
            printf("%d (%d)\n", i, HT[i]);
        }
    }
}
int main()
{
    //freopen("input.txt", "r", stdin);
    int *HT;

    scanf("%c", &MODE);
    scanf("%d", &M);

    HT = malloc(M * sizeof(int));
    memset(HT, -1, M * sizeof(int));
    setLargestPrime();
    char ch;

    while (EOF != (ch = fgetc(stdin)))
    {
        if (ch == 'i')
        {
            //insert
            int k;
            scanf("%d", &k);
            insertToHashTable(HT, k);
        }
        if (ch == 's')
        {
            //search
            int k;
            scanf("%d", &k);
            searchHashTable(HT, k);
        }
        if (ch == 'd')
        {
            //delete
            int k;
            scanf("%d", &k);
            deleteFromHashTable(HT, k);
        }
        if (ch == 'p')
        {
            //print
            printHashTable(HT);
        }
        if (ch == 't')
        {
            //exit
            break;
        }
    }

    free(HT);
    return 0;
}