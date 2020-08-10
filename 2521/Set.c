// SET ADT //
// Implementation //
// Ethan Hansen - 10/08/2020 //
//////////////////////////////

#include <stdio.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0

typedef struct _elem {
    int value;
    struct _elem *next;
} *Elem;

typedef struct _set {
    int nelems;
    Elem first;
    Elem last;
} *Set;

Set newSet() {
    Set new = malloc(sizeof(struct _set));
    new->nelems = 0;
    new->first = NULL;
    new->last = NULL;
    return new;
}

void freeSet(Set s) {
    Elem iterate = s->first;
    while (iterate != NULL) {
        Elem temp = iterate;
        iterate = iterate->next;
        free(temp);
    }
    free(s);
}

int inSet(int value, Set s) {
    Elem iterate = s->first;
    while (iterate != NULL) {
        if (iterate->value == value) return TRUE;
        iterate = iterate->next;
    }
    return FALSE;
}

int setInsert(int value, Set s) {
    if (inSet(value, s)) return 1;
    Elem e = malloc(sizeof(struct _elem));
    e->next = s->first;
    e->value = value;
    s->first = e;
    s->nelems++;
    return 0;
}

void showSet(Set s) {
    Elem iterate = s->first;
    while (iterate != NULL) {
        printf("%d->", iterate->value);
        iterate = iterate->next;
    }
    printf("\n");
}

int setDelete(int value, Set s) {
    if (!inSet(value, s)) return 1;
    Elem previous = NULL;
    Elem iterate = s->first;
    while (iterate != NULL) {
        if (iterate->value == value && previous == NULL) {
            s->first = iterate->next;
            if (s->last == iterate) s->last = NULL;
            free(iterate);
        } else if (iterate->value == value) {
            previous->next = iterate->next;
            free(iterate);
        }
        previous = iterate;
        iterate = iterate->next;
    }
    s->nelems--;
    return 0;
}

int main(void) {
    Set s = newSet();
    for (int i = 0; i <= 100; i++) {
        setInsert(i, s);
    }
    setDelete(4, s);
    showSet(s);
}