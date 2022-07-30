#include<stdio.h>
#include<malloc.h>
struct node
{
    int data;
    struct node *left;
    struct node *right;
};
struct node *createNode(int data)
{
    struct node *n=(struct node *)malloc(sizeof(struct node));
    n->data=data;
    n->left=NULL;
    n->right=NULL;
    return n;
}
struct node *searchItre(struct node *root, int key)
{
    if(root == NULL)
    {
        return NULL;
    }
    if(root->data==key)
    {
        return root;
    }
    else if(key<root->data)
    {
        searchItre(root->left, key);
    }
    else
    {
        searchItre(root->right, key);
    }
}
int main()
{
    struct node *p=createNode(5);
    struct node *p1=createNode(3);
    struct node *p2=createNode(6);
    struct node *p3=createNode(1);
    struct node *p4=createNode(4);

    p->left=p1;
    p->right=p2;
    p1->left=p3;
    p1->right=p4;

    struct node *n=searchItre(p, 5);
    if(n !=NULL)
    {
        printf("Found: %d", n->data);
    }
    else
    {
        printf("Element Not Found");
    }
    return 0;
}