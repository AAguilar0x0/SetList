#include <stdio.h>
#include <stdlib.h>
#include "SetList.h"
#define NULL ((void *)0)

Set initialize(){
    Set temp = malloc(sizeof(Node));
    temp->data = 0;
    temp->next = temp;
    return temp;
}

// Display on the screen all valid elements of the list
void display(Set s) {
    if(s == NULL || s == s->next) {
        printf("Empty Set");
        return;
    }
    nodeptr ptr = s;
    while(ptr != NULL) {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
}

// Search the array elements for the value elem
int contains(Set s, int elem) {
    if(s == NULL || s == s->next) return 0;
    nodeptr ptr = s;
    int found = 0;
    while(ptr != NULL) {
        found = (ptr->data == elem);
        ptr = (Set) (!found * (intptr_t) ptr->next);
    }
    return found;
}

// Simply store elem in the list
Set add(Set s, int elem) {
    if(s == NULL) return NULL;
    if(contains(s,elem)) return s;
    nodeptr ptr = s;
    while(ptr != ptr->next && ptr->next != NULL) ptr = ptr->next;
    nodeptr temp = ptr;
    if(ptr->next == NULL)
        temp = malloc(sizeof(Node));
    temp->data = elem;
    temp->next = NULL;
    ptr->next = (Set) ((temp != ptr) * (intptr_t) temp);
    return s;
}

/* 
 * Store in the set result the set resulting from
 * the union of s1 and s2.
 * x is an element of s1 union s2 if x is an
 * element of s1 or x is an element of s2.
 */
Set getUnion(Set result, Set s1, Set s2) {
    if(result == NULL) return result;
    if(s1 == s1->next && s2 == s2->next) return result;

    nodeptr ptr = s1 != s1->next ? s1 : s2;
    result->data = ptr->data;
    result->next = NULL;
    ptr = ptr->next;
    while(ptr != NULL) {
        add(result,ptr->data);
        ptr = ptr->next;
    }

    if(s1 == s1->next || s2 == s2->next) return result;
    ptr = s2 != s2->next ? s2 : s1;
    nodeptr ptr2srch = s1 != s1->next ? s1 : s2;
    while(ptr != NULL) {
        if(!contains(ptr2srch,ptr->data))
            add(result,ptr->data);
        ptr = ptr->next;
    }

    return result;
}

/* 
 * Store in the set result the set resulting from
 * the intersection of s1 and s2.
 * x is an element of s1 intersection s2 if x is
 * an element of s1 and x is an element of s2.
 */
Set intersection(Set result, Set s1, Set s2) {
    if(result == NULL) return result;
    if(s1 == s1->next && s2 == s2->next) return result;
    nodeptr ptr = s1 != s1->next ? s1 : s2;
    nodeptr ptr2search = s1 == s1->next ? s1 : s2;
    while(ptr != NULL) {
        if(contains(ptr2search,ptr->data))
            add(result,ptr->data);
        ptr = ptr->next;
    }
    return result;
}

/* 
 * Store in the set result the set resulting from
 * the difference of s1 and s2.
 * x is an element of s1 - s2 if x is an element
 * of s1 and x is not an element of s2.
 */
Set difference(Set result, Set s1, Set s2) {
    if(result == NULL) return result;
    if(s1 == s1->next) return result;
    nodeptr ptr = s1;
    while(ptr != NULL) {
        if(!contains(s2,ptr->data))
            add(result,ptr->data);
        ptr = ptr->next;
    }
    return result;
}

/* 
 * Store in the set result the set resulting from the
 * symmetric difference of s1 and s2.
 * x is an element of s1 - s2 if x is an element of
 * s1 and x is not an element of s2 and vice versa.
 */
Set symmetricdifference(Set result, Set s1, Set s2) {
    if(result == NULL) return result;
    if(s1 == s1->next && s2 == s2->next) return result;
    nodeptr ptr = s1 == s1->next ? NULL : s1;
    while(ptr != NULL) {
        if(!contains(s2,ptr->data))
            add(result,ptr->data);
        ptr = ptr != NULL ? ptr->next : NULL;
    }
    ptr = s2 == s2->next ? NULL : s2;
    while(ptr != NULL) {
        if(!contains(s1,ptr->data))
            add(result,ptr->data);
        ptr = ptr != NULL ? ptr->next : NULL;
    }
    return result;
}

// s1 is a subset of s2 if all elements of s1 are in s2
int subset(Set s1, Set s2) {
    if(s1 == NULL) return 1;
    if(s1 == s1->next) return 1;
    nodeptr ptr = s1;
    while(ptr != NULL) {
        if(!contains(s2,ptr->data))
            return 0;
        ptr = ptr->next;
    }
    return 1;
}

// Two sets are disjoint if the intersection is empty
int disjoint(Set s1, Set s2) {
    if(s1 == NULL) return 1;
    if(s1 == s1->next || s2 == s2->next) return 1;
    nodeptr ptr = s1;
    while(ptr != NULL) {
        if(contains(s2,ptr->data))
            return 0;
        ptr = ptr->next;
    }
    return 1;
}

// Two sets are equal if they have exactly the same elements
int equal(Set s1, Set s2) {
    if(s1 == s1->next && s2 == s2->next) return 1;
    else if((s1 == s1->next && s2 != s2->next) || 
    (s1 != s1->next && s2 == s2->next)) return 0;
    if(subset(s1,s2) && subset(s2,s1))
        return 1;
    return 0;
}