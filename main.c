#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *data;
    struct Node*left,*right;
} Node;

Node *treeDictionary=NULL;

Node * NewNode(char *data)
{
    Node *n = malloc(sizeof(Node));
    n->data=data;
    n->left=NULL;
    n->right=NULL;
    return n;
}
Node* insert(Node *n,char *c)
{
    if (n==NULL)
        return NewNode(c);
    if (strcasecmp(c,n->data)<0)
        n->left=insert(n->left,c);
    else if (strcasecmp(c,n->data)>0)
        n->right=insert(n->right,c);
    return n;
}

int count (Node *root)
{
    if (root==NULL)
        return 0;
    else
        return 1+count(root->left) + count(root->right);
}

int max(int a, int b)
{
    return a>b?a:b;
}
int height(Node *root) //recursive
{
    if(root==NULL)
        return -1;
    else
        return 1+max(height(root->left),height(root->right));
}
Node* maxNode(Node*root)
{
    if (root==NULL)
        return NULL;
    else if (root->right!=NULL)
    {
        return maxNode(root->right);
    }
    else
        return root;
}
Node* minNode(Node*root)
{
    if (root==NULL)
        return NULL;
    else if (root->left!=NULL)
    {
        return minNode(root->left);
    }
    else
        return root;
}
int search (Node *root, char * c)
{
    if (root==NULL)
        return 0;
    if (strcasecmp(c,root->data)==0)
        return 1;
    if (strcasecmp(c,root->data)<0)
        return search(root->left,c);
    if (strcasecmp(c,root->data)>0)
        return search(root->right,c);
}
void InOrdertraverse(Node *n)
{
    if (n!=NULL)
    {
        InOrdertraverse(n->left);
        printf("%s\n",n->data);
        InOrdertraverse(n->right);
    }
}
void readfile()
{

    FILE *f=fopen("EN-US-Dictionary.txt","r");
    printf("Dictionary Loaded Sucessfully . . . !\n");
    printf(". . . . . . . . . . . . . . . . . . . \n");
    while (!feof(f))
    {
        char *words=malloc(100);
        fscanf(f,"%s",words);
        treeDictionary=insert(treeDictionary,words);
    }
}
char* findLastNode(Node*root,char*c)
{
    if (root==NULL)
        return NULL;
    if ((strcasecmp(c,root->data)<0&&root->left==NULL)||(strcasecmp(c,root->data)>0&&root->right==NULL))
        return root->data;
    if (strcasecmp(c,root->data)<0)
        return findLastNode(root->left,c);
    if (strcasecmp(c,root->data)>0)
        return findLastNode(root->right,c);
}
Node*temp=NULL;
char*findSuccesor(Node*root,char*c)
{

    if ((strcasecmp(c,root->data)==0)&&(root->right==NULL))
    {
        return temp->data;
    }
    if ((strcasecmp(c,root->data)==0)&&(root->right!=NULL))
    {
        temp=minNode(root->right);
        return temp->data;
    }
    if (strcasecmp(c,root->data)<0)
    {
        temp=root;
        return findSuccesor(root->left,c);
    }
    if (strcasecmp(c,root->data)>0)
        return findSuccesor (root->right,c);
}
char*findpredecessor(Node*root,char*c)
{
    if (strcasecmp(c,root->data)==0&&root->left==NULL)
        return temp->data;
    if (strcasecmp(c,root->data)==0&&root->left!=NULL)
    {
        temp=maxNode(root->left);
        return temp->data;
    }
    if (strcasecmp(c,root->data)<0)
        return findpredecessor(root->left,c);
    if (strcasecmp(c,root->data)>0)
    {
        temp=root;
        return findpredecessor(root->right,c);
    }
}
int main()
{
    readfile();
    printf("Size = %d\n",count(treeDictionary));
    printf(". . . . . . . . . . . . . . . . . . . \n");
    printf("Height = %d\n",height(treeDictionary));
    printf(". . . . . . . . . . . . . . . . . . . \n");
    char *m=malloc(250);
    printf("Enter a sentence :\n");
    gets(m);
    char *token=strtok(m," ");
    while (token!=NULL)
    {
        if (search(treeDictionary,token)==1)
        {
            printf("%s - Correct\n",token);
        }
        else
        {
            char*temp=findLastNode(treeDictionary,token);
            printf("%s - Incorrect, Suggestions : %s %s %s\n",token,temp,findSuccesor(treeDictionary,temp),findpredecessor(treeDictionary,temp));
        }
        token= strtok(NULL," ");
    }
    return 0;
}
