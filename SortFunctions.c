#include "GenericList.h"

void sortIntArray(int *array,int length,bool reverse){
    for(int i=0;i<length;i++){
        for(int y=i;y<length;y++){
          if(reverse){
           if(array[y]>array[i]){
              int temp = array[i];
              array[i] = array[y];
              array[y] = temp;
           }
          }else{
            if(array[y]<array[i]){
            int temp = array[i];
            array[i] = array[y];
            array[y] = temp;
           }
          }
        }
    }
}

void sortDoubleArray(double *array,int length,bool reverse){
    for(int i=0;i<length;i++){
        for(int y=i;y<length;y++){
          if(reverse){
           if(array[y]>array[i]){
              double temp = array[i];
              array[i] = array[y];
              array[y] = temp;
           }
          }else{
            if(array[y]<array[i]){
            double temp = array[i];
            array[i] = array[y];
            array[y] = temp;
           }
          }
        }
    }
}

void sortCharArray(char *array,int length,bool reverse){
    for(int i=0;i<length;i++){
        for(int y=i;y<length;y++){
          if(reverse){
           if(array[y]>array[i]){
              char temp = array[i];
              array[i] = array[y];
              array[y] = temp;
           }
          }else{
            if(array[y]<array[i]){
            char temp = array[i];
            array[i] = array[y];
            array[y] = temp;
           }
          }
        }
    }
}
