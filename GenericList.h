#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#ifndef GENERICLIST_H_INCLUDED
#define GENERICLIST_H_INCLUDED

#define setValue(X,D) _Generic( (X), int: setValueInt(X,D), float: setValueFloat(X,D), double: setValueDouble(X,D), default: -1)
#define Add(HEAD,VALUE) _Generic( (VALUE), int: AddInt(HEAD,VALUE), float: AddFloat(HEAD,VALUE), double: AddDouble(HEAD,VALUE), default: -1)
#define Insert(HEAD,VALUE,INDEX) _Generic( (VALUE), int: InsertInt(HEAD,VALUE,INDEX), float: InsertFloat(HEAD,VALUE,INDEX), double: InsertDouble(HEAD,VALUE,INDEX), default: -1)
#define Remove(HEAD,VALUE,ALL_OCCURRENCES) _Generic( (VALUE), int: RemoveInt(HEAD,VALUE,ALL_OCCURRENCES), float: RemoveFloat(HEAD,VALUE,ALL_OCCURRENCES), double: RemoveDouble(HEAD,VALUE,ALL_OCCURRENCES), default: -1)
#define Search(HEAD,VALUE) _Generic( (VALUE), int: SearchInt(HEAD,VALUE), float: SearchFloat(HEAD,VALUE), double: SearchDouble(HEAD,VALUE), default: -1)
#define Count(HEAD,VALUE) _Generic( (VALUE), int: CountInt(HEAD,VALUE), float: CountFloat(HEAD,VALUE), double: CountDouble(HEAD,VALUE), default: -1)
#define Update(HEAD,VALUE,INDEX) _Generic( (VALUE), int: UpdateInt(HEAD,VALUE,INDEX), float: UpdateFloat(HEAD,VALUE,INDEX), double: UpdateDouble(HEAD,VALUE,INDEX), default: -1)

enum data_type{
    INT, CHAR, FLOAT, DOUBLE
};

typedef struct Data Data;

typedef struct Data{
    enum data_type type;
    void* value;
    void (*printValue) (Data* d);
}Data;

typedef struct Double_Linked_List{
    Data* value;
    int index;
    struct Double_Linked_List* next;
    struct Double_Linked_List* prev;
    struct Double_Linked_List* last;
}List;

extern void setValueInt(int value, Data* d);
extern void setValueFloat(float value, Data* d);
extern void setValueDouble(double value, Data* d);
extern void printItem(List* head, bool index);
extern void printList(List* head, bool index);
extern void fill_List(List* head, void* arr, int len);
extern void Clear(List* head);
extern void* toArray(List* head);
extern void* get(List* head, unsigned int index);
extern int* SearchInt(List* head, int value);
extern int* SearchFloat(List* head, float value);
extern int* SearchDouble(List* head, double value);
extern int sizeList(List* head);
extern int CountInt(List* head, int value);
extern int CountFloat(List* head, float value);
extern int CountDouble(List* head, double value);
extern bool AddInt(List* head, int value);
extern bool AddFloat(List* head, float value);
extern bool AddDouble(List* head, double value);
extern bool RemoveInt(List* head, int value, bool allOccurrences);
extern bool RemoveFloat(List* head, float value, bool allOccurrences);
extern bool RemoveDouble(List* head, double value, bool allOccurrences);
extern bool RemoveForIndex(List* head, unsigned int index);
extern bool InsertInt(List* head, int value, unsigned int index);
extern bool InsertFloat(List* head, float value, unsigned int index);
extern bool InsertDouble(List* head, double value, unsigned int index);
extern bool UpdateInt(List* head, int value, unsigned int index);
extern bool UpdateFloat(List* head, float value, unsigned int index);
extern bool UpdateDouble(List* head, double value, unsigned int index);
extern bool isEmpty(List* head);
extern List* init_List();
extern List* Sort(List* head, bool reverse);

#endif
