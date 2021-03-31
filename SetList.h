typedef struct node* nodeptr;
typedef struct node{
    int data;
    nodeptr next;
}Node;
typedef Node* Set;

Set initialize();

void display(Set s);

int contains(Set s, int elem);

Set add(Set s, int elem);

Set getUnion(Set result, Set s1, Set s2);

Set intersection(Set result, Set s1, Set s2);

Set difference(Set result, Set s1, Set s2);

Set symmetricdifference(Set result, Set s1, Set s2);

int subset(Set s1, Set s2);

int disjoint(Set s1, Set s2);

int equal(Set s1, Set s2);

