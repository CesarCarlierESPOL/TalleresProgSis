#ifndef VIDA_H
#define VIDA_H

typedef int (*comparador)(int, int);
int comp1(int a, int b);
int comp2(int a, int b);
int comp_extrano(int a, int b);
void insertionSort(int arr[], int n, comparador comp);

#endif
