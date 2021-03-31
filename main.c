#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "myTools.h"
#include "SetList.h"

void freeNodes(Set s) {
    nodeptr temp = NULL;
    if(s == s->next)
        s->next = NULL;
    while(s != NULL) {
        temp = s->next;
        free(s);
        s = temp;
    }
}

void inputSet(Set s) {
    char *buffer = NULL;
    int res;
    int i,limOfI;
    gotoxy(0,3);
    delline(3);
    printf("\tPress 'S' to stop the\n");
    printf("\tinput for this set.\n");
    printf("\tElement> ");
    while(1) {
        getDigit(&buffer,10,'\0');
        if (*buffer == 's') break;
        res = atoi(buffer);
        i = 0;
        limOfI = (int) log10(res) + 1;
        do{
            printf("%c %c",8,8);
            ++i;
        }while(i < limOfI);
        add(s,res);
    }
    free(buffer);
}

int addElem(void) {
    char *buffer = NULL;
    int res = 0;
    printf("\t\tAdd Element to chosen Set\n");
    printf("\t0. Set 1\n");
    printf("\t1. Set 2\n");
    printf("\t> ");
    do {
        getDigit(&buffer,1,'\0');
        if (*buffer == 's') break;
        res = atoi(buffer);
        printf("%c %c",8,8);
    } while(res < 0 || res > 1);
    free(buffer);
    return res;
}

int menu(void) {
    char *buffer = NULL;
    int res = 0;
    gotoxy(0,2);
    delline(12);
    gotoxy(0,2);
    printf("\t\tOptions\n");
    printf("\t0. Display\n");
    printf("\t1. Search\n");
    printf("\t2. Union\n");
    printf("\t3. Intersect\n");
    printf("\t4. Difference\n");
    printf("\t5. Symmetrical Difference\n");
    printf("\t6. Subset\n");
    printf("\t7. Disjoint\n");
    printf("\t8. Equal\n");
    printf("\t9. Add Element\n");
    printf("\tS. To Stop\n");
    printf("\t> ");
    do {
        getDigit(&buffer,1,'\0');
        if (*buffer == 's') {
            res = 10;
            break;
        }
        res = atoi(buffer);
        printf("%c %c",8,8);
    } while(res < 0 || res > 9);
    free(buffer);
    return res;
}

void progEntry(Set s1, Set s2) {
    system("cls");
    printf("\t\tSetList\n\n");
    printf("\t\tSet 1\n");
    inputSet(s1);
    outString(0,2,"\t\tSet 2\n");
    inputSet(s2);
}

int main(void) {
    Set s1 = initialize();
    Set s2 = initialize();
    Set result = NULL;
    int choice = 0;
    int elem = 0;
    char *buffer = NULL;

    progEntry(s1,s2);
    while(!buffer ? 1 : *buffer != 's') {
        free(buffer);
        buffer = NULL;
        choice = menu();
        gotoxy(0,16);
        delline(12);
        gotoxy(0,16);
        switch(choice) {
            case 0:
                printf("\t\tDisplay\n");
                printf("\tSet 1: ");
                display(s1);
                printf("\n\tSet 2: ");
                display(s2);
                break;
            case 1:
                printf("\t\tSearch\n");
                printf("\tElement> ");
                scanf("%d",&elem);
                choice = contains(s1,elem);
                printf("\tThe element is %sin set 1.\n",choice ? "" : "not ");
                choice = contains(s2,elem);
                printf("\tThe element is %sin set 2.",choice ? "" : "not ");
                break;
            case 2:
                result = initialize();
                printf("\t\tUnion\n");
                result = getUnion(result,s1,s2);
                printf("\tResult: ");
                display(result);
                freeNodes(result);
                result = NULL;
                break;
            case 3:
                result = initialize();
                printf("\t\tIntersect\n");
                result = intersection(result,s1,s2);
                printf("\tResult: ");
                display(result);
                freeNodes(result);
                result = NULL;
                break;
            case 4:
                result = initialize();
                printf("\t\tDifference\n");
                result = difference(result,s1,s2);
                printf("\tResult: ");
                display(result);
                freeNodes(result);
                result = NULL;
                break;
            case 5:
                result = initialize();
                printf("\t\tSymmetric Difference\n");
                result = symmetricdifference(result,s1,s2);
                printf("\tResult: ");
                display(result);
                freeNodes(result);
                result = NULL;
                break;
            case 6:
                printf("\t\tSubset\n");
                printf("\tSet 1 is %sa subset of set 2.",subset(s1,s2) ? 
				"" : "not ");
                break;
            case 7:
                printf("\t\tDisjoint\n");
                printf("\tSet 1 and set 2 are %sdisjoint.",disjoint(s1,s2) ?
				 "" : "not ");
                break;
            case 8:
                printf("\t\tEqual\n");
                printf("\tSet 1 and set 2 are %sequal.",equal(s1,s2) ?
				 "" : "not ");
                break;
            case 9:
                gotoxy(0,2);
                delline(13);
                gotoxy(0,2);
                choice = addElem();
                gotoxy(0,2);
                delline(4);
                gotoxy(0,2);
                if(!choice) {
                    printf("\t\tSet 1\n");
                    inputSet(s1);
                } else {
                    outString(0,2,"\t\tSet 2\n");
                    inputSet(s2);
                }
                break;
            case 10:
                system("cls");
                printf("\t\tSet List\n\n");
                printf("\tPress 1 if you want to run again.\n");
                printf("\tPress 'S' if you want to exit.\n");
                printf("\t> ");
                do {
                    getDigit(&buffer,1,'\0');
                    if (*buffer == 's') {
                        choice = 0;
                        break;
                    }
                    choice = atoi(buffer);
                    printf("%c %c",8,8);
                } while(choice != 1);
                if(choice) {
                    freeNodes(s1);
                    freeNodes(s2);
                    s1 = initialize();
                    s2 = initialize();
                    progEntry(s1,s2);
                }
                break;
        }
    }
    free(buffer);
    freeNodes(s1);
    freeNodes(s2);
    printf("\n\n\tProgram Terminated\n");
    sleep(1);

    return 0;
}
