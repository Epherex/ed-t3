#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "static_list.h"
#include "../sig/circle.h"

typedef struct Item {
    int meupintao;
    char teste[32];
} Item;

bool compFunc(void *itemVoid, void *deveSerVoid) {
    int deveser = *((int*) deveSerVoid);
    Item *item = (Item *) itemVoid;
    return item->meupintao == deveser;
}

bool circComp(void *circ, void *deveSer) {
    return (Circle_GetRadius(circ) == Circle_GetRadius(deveSer) &&
        Circle_GetX(circ) == Circle_GetX(deveSer) &&
        Circle_GetY(circ) == Circle_GetY(deveSer));
}

void destroyItem(void *itemVoid) {
    Item *item = (Item *) itemVoid;
    printf("destruindo item %d\n", item->meupintao);
    free(item);
}

void printInfos(void *itemVoid, void *nada) {
    Item *item = (Item *) itemVoid;
    printf("------\nInfos:\nmeupintao=%d\nteste=%s\n", item->meupintao, item->teste);
}

void printCirc(void *circ, void *nada) {
    printf("Circ: %.15lf %lf %lf\n", Circle_GetRadius(circ), Circle_GetX(circ), Circle_GetY(circ));
}

int main() {
    StList list = StList_Create(10);
    Item *item = malloc(sizeof(Item));
    item->meupintao = 10;
    strcpy(item->teste, "oi heheh");
    StList_Add(list, item);
    Item *item2 = malloc(sizeof(Item));
    item2->meupintao = 20;
    strcpy(item2->teste, "dasdasd ");
    StList_Add(list, item2);

    int deveSer = 20;
    Item *element = StList_Find(list, compFunc, &deveSer);

    if(element != NULL)
        printf("aelemento: %d, %s\n", element->meupintao, element->teste);
    element = StList_GetFirst(list);
    if(element != NULL)
        printf("elemento: %d, %s\n", element->meupintao, element->teste);

    Item *item3 = malloc(sizeof(Item));
    item3->meupintao = 30;
    strcpy(item3->teste, ",,,,asd");
    StList_Add(list, item3);
    
    deveSer = 30;
    element = StList_Find(list, compFunc, &deveSer);
    if(element != NULL)
        printf("aelemento: %d, %s\n", element->meupintao, element->teste);

    StList_Execute(list, printInfos, NULL);
    printf("-----\n");

    StList_Destroy(list, destroyItem);



    StList list2 = StList_Create(10);
    StList_Add(list2, Circle_Create(1.9192312335345, 5, 10));
    Circle c = StList_GetFirst(list2);
    /*if(c != NULL) {
        printf("%.15lf %lf %lf\n", Circle_GetRadius(c), Circle_GetX(c), Circle_GetY(c));
    }*/
    Circle c2 = Circle_Create(1, 1, 1);
    bool adicionou = StList_Add(list2, c2);
    if(adicionou)
        printf("wtf\n");
    else {
        printf("tudo normal\n");
        Circle_Destroy(c2);
    }

    c = StList_Remove(list2, circComp, c);
    if(c != NULL)
        printf("nao nulo meu mano\n");

    c2 = StList_GetFirst(list2);
    if(c2 != NULL) {
        printCirc(c2, NULL);
    }

    //oi(list2);

    StList_Add(list2, c);

    c = StList_GetFirst(list2);
    if(c != NULL) {
        printCirc(c, NULL);
    }

    printf("---\n");
    StList_Execute(list2, printCirc, NULL);


    //oi(list2);

    printf("---\n");

    StList_Add(list2, Circle_Create(10, 10, 10));

    //oi(list2);

    StList_Add(list2, Circle_Create(11, 10, 10));
    StList_Add(list2, Circle_Create(12, 10, 10));
    StList_Add(list2, Circle_Create(13, 10, 10));
    StList_Add(list2, Circle_Create(14, 10, 10));
    StList_Add(list2, Circle_Create(15, 10, 10));
    StList_Add(list2, Circle_Create(16, 10, 10));
    StList_Add(list2, Circle_Create(17, 10, 10));
    StList_Resize(list2, 15);
    StList_Add(list2, Circle_Create(18, 10, 10));
    StList_Add(list2, Circle_Create(19, 10, 10));
    StList_Add(list2, Circle_Create(20, 10, 10));


    //oi(list2);

    StList_Execute(list2, printCirc, NULL);

    //Circle_Destroy(StList_RemoveLast(list2));

    assert(adicionou);
    
    StList_Destroy(list2, Circle_Destroy);
}