#include<stdio.h>
#include<stdlib.h>
#include"header.h"


void CreatNameStack(NameStack* ps)
{
    ps->top=0;
}
void Push(ListEntry *pe,NameStack* ps)
{
    uint8_t i;
    for(i=0; pe->Name[i]!='\0'; i++)
    {
        ps->entry[ps->top].Namecopy[i]= pe->Name[i];
    }

    ps->entry[ps->top].Namecopy[i]='\0';

    for(i=0; pe->BirthDay[i]!='\0'; i++)
    {
        ps->entry[ps->top].BDcopy[i]=pe->BirthDay[i];
    }

    ps->entry[ps->top].BDcopy[i]='\0';

    for(i=0; pe->Address[i]!='\0'; i++)
    {
        ps->entry[ps->top].Addrcopy[i]=pe->Address[i];

    }
    ps->entry[ps->top].Addrcopy[i]='\0';

    for(i=0; pe->Phone[i]!='\0'; i++)
    {
        ps->entry[ps->top].Phcopy[i]=pe->Phone[i];

    }
    ps->entry[ps->top].Phcopy[i]='\0';


    ps->entry[ps->top].IDcopy=pe->ID;

    ps->top++;
}
void CDataSort(NameStack* ps)
{
    DataEntry tmp;
    DataEntry *tmpPtr=&tmp;
    int i,j;
    int x;
    for(i=ps->top-1; i>=0; i--)
    {
        for(j=i-1; j>=0; j--)
        {
            x=compare_info(ps->entry[i].Namecopy, ps->entry[j].Namecopy);
            if(x>0)
            {
                *tmpPtr=ps->entry[i];
                ps->entry[i]=ps->entry[j];
                ps->entry[j]=*tmpPtr;

            }
        }
    }

}
void List_Print(NameStack *ps)
{
    int32_t i;
    printf("Name|\t\t  ID|\t   Date of Birth|\t Address| \tPhoneNumber| \n");
    for (i=ps->top-1; i>=0; i--)
    {
        fflush(stdout);
        printf("%s\t",ps->entry[i].Namecopy);
        fflush(stdout);
        printf("%d\t",ps->entry[i].IDcopy);
        fflush(stdout);
        printf("%s\t",ps->entry[i].BDcopy);
        fflush(stdout);
        printf("%s\t",ps->entry[i].Addrcopy);
        fflush(stdout);
        printf("%s\n",ps->entry[i].Phcopy);
        fflush(stdout);

    }

}
int32_t compare_info( uint8_t* array1, uint8_t* array2)
{
    int32_t i;
    for (i=0; array1[i]!=0 && array2[i]!=0; i++)
    {
        if (array1[i] > array2[i])
            return +1;
        if (array1[i] < array2[i])
            return -1;
    }
    if (array1[i] != 0)
        return +1;
    if (array2[i] != 0)
        return -1;
    return 0;
}
void INSERT_TICKET(Tree*pt)
{
    TicEntry EN;

    fflush(stdin);
    printf("ClientID: ");
    scanf("%u",&(EN.ID));
    fflush(stdin);

    printf("Enter Ticket Code:\n");
    scanf("%u",&EN.tic);
    Insert(&EN,pt);

}
void T_SEARCH_PRINT(Tree*pt)
{
    TreeNode* tr;                         //tmp pointer
    TicEntry EN;
    printf("Enter Ticket Code:\n");
    scanf("%u",&EN.tic);

    tr= BinarySearch(&EN,pt);
    printf("ID=%d",tr->entry.ID);
}
void CreatTree(Tree* pt)
{
    pt->root=NULL;
    pt->parent=NULL;
    pt->Search =pt->root;
}
TreeNode* Insert( TicEntry*pe, Tree* pt )
{
    if(pt->root==NULL)
    {
        TreeNode* pn = (TreeNode*) malloc (sizeof(TreeNode));
        pt->root=pn;
        pn->entry.ID= pe->ID;
        pn->entry.tic= pe->tic;
        pn->left=NULL;
        pn->right=NULL;

        pt->parent=pt->root;
    }
    else
    {

        if(pe->tic< (pt->parent->entry.tic))
        {
            if(pt->parent->left==NULL)
            {
                //insert(left)
                TreeNode* pn = (TreeNode*) malloc (sizeof(TreeNode));
                pt->parent->left=pn;
                pn->entry.ID= pe->ID;
                pn->entry.tic= pe->tic;
                pn->left=NULL;
                pn->right=NULL;

            }
            else
            {
                if((pe->tic < (pt->parent->entry.tic))&&(pe->tic< (pt->root->entry.tic))&&(pe->tic>(pt->root->left->entry.tic)))
                {
                    pt->parent=pt->root;
                }
                //recursion
                pt->parent= pt->parent->left;
                Insert(pe,pt);
                pt->parent=pt->root;

            }
        }

        else
        {
            if(pt->parent->right==NULL)
            {

                //insert(right)
                TreeNode* pn = (TreeNode*) malloc (sizeof(TreeNode));
                pt->parent->right=pn;
                pn->entry.ID= pe->ID;
                pn->entry.tic= pe->tic;
                pn->left=NULL;
                pn->right=NULL;
            }
            else
            {
                if((pe->tic > (pt->parent->entry.tic))&&(pe->tic > (pt->root->entry.tic))&&(pe->tic<(pt->root->right->entry.tic)))
                {
                    pt->parent=pt->root;
                }

                //recursion
                pt->parent= pt->parent->right;
                Insert(pe,pt);
                pt->parent=pt->root;
            }
        }
    }
    pt->Search=pt->root;
    return pt->root;
}
TreeNode* BinarySearch(TicEntry* pe, Tree* pt)
{
    int Flag=0;
    while(pt->Search!=NULL && Flag==0)
    {
        if(pe->tic==pt->Search->entry.tic)
        {
            Flag=1;
        }
        else if(pe->tic<pt->Search->entry.tic)
        {
            //left recursion
            pt->Search=pt->Search->left;
            BinarySearch(pe,pt);

        }
        else
        {
            //right recursion
            pt->Search=pt->Search->right;
            BinarySearch(pe,pt);
        }
    }
    return (pt->Search);
}
uint8_t TreeEmpty(Tree* pt)
{
    return !(pt->root);
}
