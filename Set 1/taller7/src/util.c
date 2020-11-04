#include <stdio.h>
#include "util.h"

int comp1(int a, int b){
        if (a>b){
                return 1;
        }else if(a<b){
                return -1;
        }return 0;
}

int comp2(int a, int b){
        if (a<b){
                return 1;
        }else if(a>b){
                return -1;
        }return 0;
}

int comp_extrano(int a, int b){
        if (a<b){
                return -1;
        }else if(a>b){
                return 0;
        }return 1;
}

void insertionSort(int arr[], int n, comparador comp){
        int i, key, j;
        for (i=1;i<n;i++){
                key=arr[i];
                j=i-1;

                while (j>=0 && comp(arr[j], key)>0){
                        arr[j+1]=arr[j];
                        j=j-1;
                }
                arr[j+1]=key;
        }
}

