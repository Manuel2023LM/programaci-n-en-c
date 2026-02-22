#include<stdio.h>

int multiplicacionb(int a, int b){
    return a * b;
}

int main(){

    int m = 3;
    int n = 2;

    int suma = m + n;
    int producto = multiplicacionb(m, n);

    printf("%i\n", suma);
    printf("%i\n", producto);

    return 0;

}