#include "GenericList.h"
#include "SortFunctions.c"

void setValueInt(int value, Data* d){
    int* allocate_value = (int*) malloc(sizeof(int));
    *allocate_value = value;
    d->value = allocate_value;
}

void setValueFloat(float value, Data* d){
    float* allocate_value = (float*) malloc(sizeof(float));
    *allocate_value = value;
    d->value = allocate_value;
}

void setValueDouble(double value, Data* d){
    double* allocate_value = (double*) malloc(sizeof(double));
    *allocate_value = value;
    d->value = allocate_value;
}

void printValue(Data* d){
    if(d!=NULL){
        switch(d->type){
        case INT:
            printf("%d], ", *(int*)d->value);
            break;
        case CHAR:
            printf("%c], ", *(int*)d->value);
            break;
        case FLOAT:
            printf("%f], ", *(float*)d->value);
            break;
        case DOUBLE:
            printf("%lf], ", *(double*)d->value);
        }
    }
}

Data* createData(enum data_type type){
    Data* d = (Data*) malloc(sizeof(Data));
    if(d==NULL) return NULL;
    d->type = type;
    d->printValue = printValue;

    return d;
}

void printItem(List* item, bool index){
    if(item==NULL){
        printf("\nInvalid item error\n");
    }else{
        if(item->prev!=NULL){
            if(index) printf("[%d : ", item->index);
            else printf("[");
            item->value->printValue(item->value);
            //printf("\nNext : %d", item->next);
            //printf("\nSelf : %d", item);
            //printf("\nPrev : %d", item->prev);
        }
    }
}

void printList(List* head, bool index){
    if(head==NULL){
        printf("\nInvalid list error\n");
    }else{
        List* current = head->next;
        printf("{ ");
        while(current!=NULL){
            printItem(current, index);
            current = current->next;
        }
        printf("}");
    }
}

List* init_List(enum data_type type){
    List* head = (List*) malloc(sizeof(List));
    if(head==NULL) return NULL;
    head->value = createData(type);

    head->index = -1;

    head->next = NULL;
    head->prev = NULL;
    head->last = head;

    return head;
}

bool isEmpty(List* head){
    if(head==NULL){
        printf("\nInvalid list error\n");
        return true;
    }
    if(head->next==NULL) return true;
    else return false;
}

List* create(Data* value, List* next, List* prev, int index){
    List* newItem = (List*) malloc(sizeof(List));
    if(newItem==NULL) return NULL;

    newItem->index = index;
    newItem->value = value;
    newItem->next = next;
    newItem->prev = prev;
    newItem->last = NULL;

    return newItem;
}

int sizeList(List* head){
    if(head==NULL) return 0;
    int len = 0;
    List* current = head->next;
    while(current!=NULL){
        len++;
        current = current->next;
    }
    return len;
}

void fixIndex(List* head){
    int index = 0;
    List* current = head->next;
    while(current!=NULL){
        current->index = index;
        current = current->next;
        index++;
    }
}

bool RemoveForIndex(List* head, unsigned int index){
    if(head==NULL) return false;
    List* current = head->next;
    while(current!=NULL){
        if(current->index==index){
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            return true;
        }
        current = current->next;
    }
    fixIndex(head);
    return false;
}

bool RemoveInt(List* head, int value, bool allOccurrences){
    if(head->value->type!=INT && head->value->type!=CHAR) return false;
    if(head==NULL) return false;
    List* current = head->next;
    bool isPresent = false;
    while(current!=NULL){
        if(*(int*)current->value->value==value){
            isPresent = true;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            if(!allOccurrences) return true;
        }
        current = current->next;
    }
    fixIndex(head);
    return isPresent;
}

bool RemoveFloat(List* head, float value, bool allOccurrences){
    if(head==NULL) return false;
    if(head->value->type!=FLOAT && head->value->type!=DOUBLE) return false;
    List* current = head->next;
    bool isPresent = false;
    while(current!=NULL){
        if(*(float*)current->value->value==value){
            isPresent = true;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            if(!allOccurrences) return true;;
        }
        current = current->next;
    }
    fixIndex(head);
    return isPresent;
}

bool RemoveDouble(List* head, double value, bool allOccurrences){
    if(head==NULL) return false;
    if(head->value->type!=DOUBLE) return false;
    List* current = head->next;
    bool isPresent = false;
    while(current!=NULL){
        if(*(double*)current->value->value==value){
            isPresent = true;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            if(!allOccurrences) return true;
        }
        current = current->next;
    }
    fixIndex(head);
    return isPresent;
}

bool AddInt(List* head, int value){
    if(head->value->type!=INT && head->value->type!=CHAR) return false;
    if(head==NULL) return false;
    Data* data_value = createData(head->value->type);
    if(data_value==NULL) return false;
    setValue(value,data_value);

    List* newItem = create(data_value, NULL, head->last, head->last->index+1);
    if(newItem==NULL) return false;
    head->last->next = newItem;
    head->last = newItem;

    return true;
}

bool AddFloat(List* head, float value){
    if(head->value->type!=FLOAT && head->value->type!=DOUBLE) return false;
    if(head==NULL) return false;
    Data* data_value = createData(head->value->type);
    if(data_value==NULL) return false;
    setValue((float)value,data_value);

    List* newItem = create(data_value, NULL, head->last, head->last->index+1);
    if(newItem==NULL) return false;
    head->last->next = newItem;
    head->last = newItem;

    return true;
}

bool AddDouble(List* head, double value){
    if(head->value->type!=DOUBLE) return false;
    if(head==NULL) return false;
    Data* data_value = createData(head->value->type);
    if(data_value==NULL) return false;
    setValue(value,data_value);

    List* newItem = create(data_value, NULL, head->last, head->last->index+1);
    if(data_value==NULL) return false;
    head->last->next = newItem;
    head->last = newItem;

    return true;
}

bool InsertInt(List* head, int value, unsigned int index){
    if(head->value->type!=INT && head->value->type!=CHAR) return false;
    if(head==NULL) return false;
    if(index<=sizeList(head)/2){
        List* current = head->next;
        while(current!=NULL){
            if(current->index==index-1){
                Data* data_value = createData(head->value->type);
                setValue(value, data_value);

                List* newItem = create(data_value,current->next,current,index);
                current->next = newItem;
                newItem->next->prev = newItem;
                fixIndex(head);
                return true;
            }
            current = current->next;
        }
    }else{
        List* current = head->last;
        while(current!=NULL){
            if(current->index==index+1){
                Data* data_value = createData(head->value->type);
                setValue(value, data_value);

                List* newItem = create(data_value,current,current->prev,index);
                current->prev = newItem;
                newItem->prev->next = newItem;
                fixIndex(head);
                return true;
            }
            current = current->prev;
        }
    }
    return false;
}

bool InsertFloat(List* head, float value, unsigned int index){
    if(head->value->type!=FLOAT && head->value->type!=DOUBLE) return false;
    if(head==NULL) return false;
    if(index<=sizeList(head)/2){
        List* current = head->next;
        while(current!=NULL){
            if(current->index==index-1){
                Data* data_value = createData(head->value->type);
                setValue((float)value, data_value);

                List* newItem = create(data_value,current->next,current,index);
                current->next = newItem;
                newItem->next->prev = newItem;
                fixIndex(head);
                return true;
            }
            current = current->next;
        }
    }else{
        List* current = head->last;
        while(current!=NULL){
            if(current->index==index+1){
                Data* data_value = createData(head->value->type);
                setValue((float)value, data_value);

                List* newItem = create(data_value,current,current->prev,index);
                current->prev = newItem;
                newItem->prev->next = newItem;
                fixIndex(head);
                return true;
            }
            current = current->prev;
        }
    }
    return false;
}

bool InsertDouble(List* head, double value, unsigned int index){
    if(head->value->type!=DOUBLE) return false;
    if(head==NULL) return false;
    if(index<=sizeList(head)/2){
        List* current = head->next;
        while(current!=NULL){
            if(current->index==index-1){
                Data* data_value = createData(head->value->type);
                setValue(value, data_value);

                List* newItem = create(data_value,current->next,current,index);
                current->next = newItem;
                newItem->next->prev = newItem;
                fixIndex(head);
                return true;
            }
            current = current->next;
        }
    }else{
        List* current = head->last;
        while(current!=NULL){
            if(current->index==index+1){
                Data* data_value = createData(head->value->type);
                setValue(value, data_value);

                List* newItem = create(data_value,current,current->prev,index);
                current->prev = newItem;
                newItem->prev->next = newItem;
                fixIndex(head);
                return true;
            }
            current = current->prev;
        }
    }
    return false;
}

bool UpdateInt(List* head, int value, unsigned int index){
    if(head->value->type!=INT && head->value->type!=CHAR) return false;
    if(head==NULL) return false;
    List* current = head;
    while(current!=NULL){
        if(current->index==index){
            *(int*)current->value->value = value;
            return true;
        }
        current = current->next;
    }
    return false;
}

bool UpdateFloat(List* head, float value, unsigned int index){
    if(head->value->type!=FLOAT && head->value->type!=DOUBLE) return false;
    if(head==NULL) return false;
    List* current = head;
    while(current!=NULL){
        if(current->index==index){
            *(float*)current->value->value = value;
            return true;
        }
        current = current->next;
    }
    return false;
}

bool UpdateDouble(List* head, double value, unsigned int index){
    if(head->value->type!=DOUBLE) return false;
    if(head==NULL) return false;
    List* current = head;
    while(current!=NULL){
        if(current->index==index){
            *(double*)current->value->value = value;
            return true;
        }
        current = current->next;
    }
    return false;
}

void fill_List(List* head, void* arr, int len){
    for(int i=0;i<len;i++){
        switch(head->value->type){
        case INT:
            Add(head, *(int*)(arr+(i*sizeof(int))));
            break;
        case FLOAT:
            Add(head, *(float*)(arr+(i*sizeof(float))));
            break;
        case DOUBLE:
            Add(head, *(double*)(arr+(i*sizeof(double))));
            break;
        default:
            break;
        }
    }
}

List* Sort(List* head, bool reverse){
    if(head==NULL) return NULL;
    int len = sizeList(head);
    List* newHead = init_List(head->value->type);
    switch(head->value->type){
    case INT:
        goto nullInt;
        nullInt:;
        int* arrInt = (int*) malloc(sizeof(int)*len);
        arrInt = toArray(head);
        sortIntArray(arrInt,len,reverse);
        fill_List(newHead,arrInt,len);
        free(arrInt);
        break;
    case FLOAT:
        goto nullFloat;
        nullFloat:;
        float* arrFloat = (float*) malloc(sizeof(float)*len);
        arrFloat = toArray(head);
        sortDoubleArray((double*)arrFloat,len,reverse);
        fill_List(newHead,arrFloat,len);
        free(arrFloat);
        break;
    case DOUBLE:
        goto nullDouble;
        nullDouble:;
        double* arrDouble = (double*) malloc(sizeof(double)*len);
        arrDouble = toArray(head);
        sortDoubleArray(arrDouble,len,reverse);
        fill_List(newHead,arrDouble,len);
        free(arrDouble);
    default:
        return NULL;
    }
    Clear(head);
    return newHead;
}

void* get(List* head, unsigned int index){
    if(head==NULL) return NULL;
    if(index<=sizeList(head)/2){
        List* current = head->next;
        while(current!=NULL){
            if(current->index==index) return current->value->value;
            current = current->next;
        }
    }else{
        List* current = head->last;
        while(current!=NULL){
            if(current->index==index) return current->value->value;
            current = current->prev;
        }
    }
    return NULL;
}

int CountInt(List* head, int value){
    if(head->value->type!=INT && head->value->type!=CHAR) return -1;
    if(head==NULL) return -1;
    List* current = head->next;
    int count = 0;
    while(current!=NULL){
        if(*(int*)current->value->value==value) count++;
        current = current->next;
    }
    return count;
}

int CountFloat(List* head, float value){
    if(head->value->type!=FLOAT && head->value->type!=DOUBLE) return -1;
    if(head==NULL) return -1;
    List* current = head->next;
    int count = 0;
    while(current!=NULL){
        if(*(float*)current->value->value==value) count++;
        current = current->next;
    }
    return count;
}

int CountDouble(List* head, double value){
    if(head->value->type!=DOUBLE) return -1;
    if(head==NULL) return -1;
    List* current = head->next;
    int count = 0;
    while(current!=NULL){
        if(*(double*)current->value->value==value) count++;
        current = current->next;
    }
    return count;
}

int* SearchInt(List* head, int value){
    if(head->value->type!=INT && head->value->type!=CHAR) return NULL;
    if(head==NULL) return NULL;
    List* current = head->next;
    int i = 0;
    int* arrIndex = (int*) malloc(sizeof(int)*Count(head,value));
    while(current!=NULL){
        if(*(int*)current->value->value==value) *(arrIndex+i++) = current->index;
        current = current->next;
    }
    return arrIndex;
}

int* SearchFloat(List* head, float value){
    if(head->value->type!=FLOAT && head->value->type!=DOUBLE) return NULL;
    if(head==NULL) return NULL;
    List* current = head->next;
    int i = 0;
    int* arrIndex = (int*) malloc(sizeof(int)*Count(head,value));
    while(current!=NULL){
        if(*(float*)current->value->value==value) *(arrIndex+i++) = current->index;
        current = current->next;
    }
    return arrIndex;
}

int* SearchDouble(List* head, double value){
    if(head->value->type!=DOUBLE) return NULL;
    if(head==NULL) return NULL;
    List* current = head->next;
    int i = 0;
    int* arrIndex = (int*) malloc(sizeof(int)*Count(head,value));
    while(current!=NULL){
        if(*(double*)current->value->value==value) *(arrIndex+i++) = current->index;
        current = current->next;
    }
    return arrIndex;
}

void* toArray(List* head){
    if(head==NULL) return NULL;
    int len = sizeList(head);
    switch(head->value->type){
    case INT:
        goto nullInt;
        nullInt:;
        int* arrInt = (int*) malloc(sizeof(int)*len);
        for(int i=0;i<len;i++){
            *(arrInt+i) = *(int*)get(head, i);
        }
        return arrInt;
    case FLOAT:
        goto nullFloat;
        nullFloat:;
        float* arrFloat = (float*) malloc(sizeof(float)*len);
        for(int i=0;i<len;i++){
            *(arrFloat+i) = *(float*)get(head, i);
        }
        return arrFloat;
    case DOUBLE:
        goto nullDouble;
        nullDouble:;
        float* arrDouble = (float*) malloc(sizeof(float)*len);
        for(int i=0;i<len;i++){
            *(arrDouble+i) = *(float*)get(head, i);
        }
        return arrDouble;
    default:
        return NULL;
    }
    return NULL;
}

void Clear(List* head){
    if(head==NULL) printf("\nInvalid list error\n");
    else{
        while(head->next!=NULL){
            List* temp = head->next->next;
            free(head->next);
            head->next = temp;
        }
    }
}
