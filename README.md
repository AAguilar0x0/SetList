# Set List

A set of integers may be implemented using a linked list.

Implement the following functions given the definition:
```c
typedef struct node* nodeptr;

typedef struct node{
    int data;
    nodeptr next;
}Node;

typedef Node* Set;

// simply initialize to NULL
Set initialize();

// display on the screen all valid elements of the list
void display(Set s);

// simply store elem in the list
Set add(Set s, elem);

// search the array elements for the value elem
int contains(Set s, int elem);

/*
 * store in the set result the set resulting from the union of s1 and s2
 * x is an element of s1 union s2 if x is an element of s1 or x is an element of s2
 */
Set getUnion(Set result, Set s1, Set s2);

/*
 * store in the set result the set resulting from the intersection of s1 and s2
 * x is an element of s1 intersection s2 if x is an element of s1 and x is an element of s2
 */
Set intersection(Set result, Set s1, Set s2);

/*
 * store in the set result the set resulting from the difference of s1 and s2
 * x is an element of s1 - s2 if x is an element of s1 and x is not an element of s2
 */
Set difference(Set result, Set s1, Set s2);

/*
 * store in the set result the set resulting from the symmetric difference of s1 and s2
 * x is an element of s1 - s2 if x is an element of s1 and x is not an element of s2 and vice versa
 */
Set symmetricdifference(Set result, Set s1, Set s2);

// s1 is a subset of s2 if all elements of s1 are in s2
int subset(Set s1, Set s2);

// two sets are disjoint if the intersection is empty
int disjoint(Set s1, Set s2);

// two sets are equal if they have exactly the same elements
int equal(Set s1, Set s2);
```