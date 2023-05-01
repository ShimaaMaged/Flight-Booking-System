#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"header.h"


uint32_t MAIN_MENU (void)
{
    uint32_t Operation;
    printf("\n\t  Welcome!\n");
    printf("Please Enter The Operation Number: \n");
    printf(" 1.New Client\n 2.Delete Client\n 3.Client List\n 4.Client Edit\n 5.Free Seats\n 6.Class List\n 7.InsertTicket\n 8.SearchTicket\n  ");
    scanf("%u",&Operation);
    return Operation;
}
/*PreCo:the order of functions call is crucial */
void NEW_CLIENT(uint32_t i,List *pl,Seats* ps)
{
    ListEntry e;
    ScanfClientData(&e);
    InsertFunction(&e,i,pl,ps);
    printf("Client has been entered!\n");
}
/*PreCo:the order of functions call is crucial */
void DELETE_CLIENT(List* pl, Seats *ps  )
{
    uint32_t FoundIn;
    ListEntry e;
    fflush(stdin);
    printf("ClientID: ");
    scanf("%u",&(e.ID));
    fflush(stdin);

    FoundIn= ClientSearch(&e,pl);
    DeleteFunction(&e,FoundIn,pl,ps);
    printf("Client :\n");
    PrintClientData(&e);
    printf("Has been Deleted!\n");

}
/*PreCo:the order of functions call is crucial */
void CLIENT_EDIT(List* pl, Seats *ps)
{
    uint32_t FoundIn;
    ListEntry e;
    fflush(stdin);
    printf("ClientID: ");
    scanf("%u",&(e.ID));
    fflush(stdin);
    FoundIn= ClientSearch(&e,pl);
    EditFunction(&e,FoundIn,pl,ps);
    printf("Edit Done!\nThe New Data Are:\n");
    PrintClientData(&e);
}
/*Pre: The list is initialized and not empty*/
void CLASS_LIST(List* pl, Seats *ps)
{
    void(*ClassLi_ptr[])(Seats*)= {FirstClass,BusClass,PremClass,EcoClass};
    uint32_t CL;
    printf("Please Enter the number the preferred Class.\n 1.First Class.\n 2.Business Class.\n 3. Premium Economic.\n 4.Economic.\n ");
    scanf("%u",&CL);
    if((CL>0)&&(CL<=4))
    {
        ClassLi_ptr[CL-1](ps);
    }
    else
    {
        printf("wrong Entry");
    }
}
/*Pre: The list is initialized and not empty*/
void CLIENT_LIST( List *pl)
{
    uint32_t i;
    NameStack NS;
	CreatNameStack(&NS);
    ListNode *pn=pl->top;

	for(i=0;i<(pl->Size);i++)
    {
        Push(&(pn->entry),&NS);
        pn=pn->next;
    }
    CDataSort(&NS);
    List_Print(&NS);

}
void CreatList (List* pl)
{
    pl->top=NULL;
    pl->Size=0;

}
/*Pre: ListEntry structure is initialized
  Post: Data is stored temporary in the stack*/
void ScanfClientData(ListEntry* data)
{
    fflush(stdin);
    printf("Name: ");
    scanf("%[^\n]s",(data->Name));
    fflush(stdin);

    printf("ID: ");
    scanf("%u",&(data->ID));
    fflush(stdin);

    printf("Date of Birth: ");
    scanf("%[^\n]s",(data->BirthDay));
    fflush(stdin);

    printf("Address: ");
    scanf("%[^\n]s",(data->Address));
    fflush(stdin);

    printf("Phone Number: ");
    scanf("%[^\n]s",(data->Phone));
    fflush(stdin);

}
void PrintClientData(ListEntry* data)
{
    printf("Name: %s\n",(data->Name));
    printf("ID: %d\n",(data->ID));
    printf("Date of Birhth: %s\n",data->BirthDay);
    printf("Address:%s\n",data->Address);
    printf("Phone Number: %s\n",data->Phone);
}
/*Pre: The list is initialized and not full
  Post: The entry has been stored at the top of the stack and did not change*/
void InsertFunction(ListEntry* pe,uint32_t pos, List* pl, Seats* ps)
{
    uint32_t i;
    ListNode *pn=(ListNode*)malloc(sizeof(ListNode));
    ListNode *tmp=pl->top;

    if(pos >= pl->Size)
    {
        pn->next=tmp;
    }

    for(i=0; i<((pl->Size)-pos); i++)
    {
        tmp=tmp->next;
    }
    if(pos>=pl->Size)
    {
        pl->top=pn;
    }
    else
    {
        pn->next=tmp->next;
        tmp->next=pn;
    }
    pn->entry= *pe;
    Class_Seats(pn,ps);
    pl->Size++;

}
/*Pre: The list is initialized and not empty
  Post: The last element entered is returned, and Seat pointer is released */
void DeleteFunction(ListEntry* pe,uint32_t pos, List* pl,Seats* ps)
{

    uint32_t i;
    ListNode*pn=pl->top;
    ListNode*tmp=pl->top;

    if(pos>=pl->Size)
    {

        pl->top=pn->next;;
    }
    else{

        for(i=0; i<(pl->Size-pos); i++)
        {

            pn=pn->next;
        }

        for(i=0; i<(pl->Size-pos-1); i++)
        {

            tmp=tmp->next;
        }
    }

    *pe=pn->entry;
    tmp->next=pn->next;
    Free_Seat(pn,ps);
    free(pn);
    pl->Size--;

}
/*Pre: The list is not empty
  Post: All client data entered can be Edited, seat is reassigned.*/
void EditFunction(ListEntry* pe,uint32_t pos, List* pl,Seats* ps)
{
    uint32_t i;
    ListNode*pn=pl->top;
    for(i=0; i<(pl->Size-pos); i++)
    {
        pn=pn->next;
    }

    fflush(stdin);
    printf("New Name: ");
    scanf("%[^\n]s",pn->entry.Name);
    fflush(stdin);
    printf("New ID: ");
    scanf("%d",&(pn->entry.ID));

    fflush(stdin);
    printf("New BirthDay: ");
    scanf("%[^\n]s",pn->entry.BirthDay);

    fflush(stdin);
    printf("New Address: ");
    scanf("%[^\n]s",pn->entry.Address);

    fflush(stdin);
    printf("New Phone Number: ");
    scanf("%[^\n]s",pn->entry.Phone);

    *pe=pn->entry;
    Free_Seat(pn,ps);
    Class_Seats(pn,ps);

}
/*Pre: The function takes the Id to search for
  Post: The desired element position is Found, and returns the potion without any changes in the element */
uint32_t ClientSearch(ListEntry* pe, List*pl)
{
    uint32_t i;
    ListNode *pn=pl->top;
    uint32_t pos=pl->Size;

    for(i=0; i<(pl->Size); i++)
    {
        if((pe->ID)!=(pn->entry.ID))
        {
            pn=pn->next;
            pos--;
        }
        else
        {
            break;
        }
    }
    return pos;
}

uint8_t ClientListEmpty(List*pl)
{
    return (pl->top==NULL);
}
