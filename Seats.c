#include<stdio.h>
#include<stdlib.h>
#include"header.h"

void CreatSeats(Seats *ps)
{
    uint32_t i,j;
    for (i=0; i<3; i++)
    {
        for(j=0; j<6; j++)
        {
            ps->Frclssptr[i][j]=NULL;
        }
    }
    for (i=0; i<4; i++)
    {
        for(j=0; j<6; j++)
        {
            ps->Bzclssptr[i][j]=NULL;
        }
    }
    for (i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            ps->Prclssptr[i][j]=NULL;
        }
    }
    for (i=0; i<6; i++)
    {
        for(j=0; j<8; j++)
        {
            ps->Eoclssptr[i][j]=NULL;
        }
    }

}
/*Pre: The stack of Seats is initialized and not full
  Post: The assigned seat will be initialized as a pointer to the Client Data in the LinkedList*/
void Class_Seats(ListNode*pn,Seats* ps)
{
    uint32_t row;
    uint32_t colmdecimal;
    uint32_t PreClass;
    uint8_t colm;
    uint8_t AssignComplete=0;

    while(! AssignComplete)
    {
        printf("Please Enter the number the preferred Class.\n 1.Fist Class.\n 2.Business Class.\n 3. Premium Economic.\n 4.Economic.\n ");
        scanf("%d",&PreClass);
        if((PreClass>0)&&(PreClass<=4))
        {
            printf("Seat ROW: ");
            scanf("%d",&row);
            fflush(stdin);
            printf("Seat Column: ");
            scanf(" %c",&colm);
            colmdecimal=(uint32_t)(colm-'A');

            if(!SeatReserved(PreClass,row,colmdecimal,ps))
            {

                AssignComplete= AssignSeat(PreClass,row,colmdecimal,pn,ps);

            }
            else
            {
                printf("the Seat is reserved, Please select another Seat.\n ");
            }

        }
        else
        {
            printf("Wrong Entry,Please try again.\n");
        }
    }

}

void PrintFreeSeats(Seats* ps)
{
    uint32_t i,j;
    printf("First Class*\n");
    for (i=0; i<3; i++)
    {
        for(j=0; j<6; j++)
        {
            if(ps->Frclssptr[i][j]==NULL)
            {
                printf("(%d %c) ",(i+1),(j+'A'));
            }
            else
            {
                printf("---- ");
            }
        }
        printf("\n");
    }
    printf("__________________________________________\n\n");
    printf("Business Class\n");
    for (i=0; i<4; i++)
    {
        for(j=0; j<6; j++)
        {
            if(ps->Bzclssptr[i][j]==NULL)
            {
                printf("(%d %c) ",(i+7),(j+'A'));
            }
            else
            {
                printf("---- ");
            }
        }
        printf("\n");
    }
    printf("__________________________________________\n\n");
    printf("Premium Economic Class\n");
    for (i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(ps->Prclssptr[i][j]==NULL)
            {
                printf("(%d %c) ",(i+22),(j+'A'));
            }
            else
            {
                printf("---- ");
            }
        }
        printf("\n");
    }
    printf("__________________________________________\n\n");
    printf("Economic Class\n");
    for (i=0; i<6; i++)
    {
        for(j=0; j<8; j++)
        {
            if(ps->Eoclssptr[i][j]==NULL)
            {
                printf("(%d %c) ",(i+45),(j+'A'));
            }
            else
            {
                printf("---- ");
            }
        }
        printf("\n");
    }
    printf("__________________________________________\n");
}

uint8_t AssignSeat(uint8_t PreClass,uint32_t row, uint32_t colm,ListNode* pn,Seats *ps)
{
    uint8_t asigned=0;
    switch (PreClass)
    {
    case First:
        row=row-1;
        /*array boundary*/
        if((row>=0)&&(row<3)&&(colm>=0)&&(colm<6))
        {
            ps->Frclssptr[row][colm]=pn;
            asigned=1;
        }
        else
        {
            printf("This Seat is not in First Class, Please Try Again\n");
        }
        break;
    case Bus:
        row=row-7;
        /*array boundary*/
        if((row>=0)&&(row<4)&&(colm>=0)&&(colm<6))
        {
            ps->Bzclssptr[row][colm]=pn;
            asigned=1;
        }
        else
        {
            printf("This Seat is not in Business Class, Please Try Again\n");
        }
        break;

    case PreEco:
        row=row-22;
        /*array boundary*/
        if((row>=0)&&(row<8)&&(colm>=0)&&(colm<8))
        {
            ps->Prclssptr[row][colm]=pn;
            asigned=1;
        }
        else
        {
            printf("This Seat is not in Premium Economic Class, Please Try Again\n");
        }
        break;

    case Eco:
        row=row-45;
        /*array boundary*/
        if((row>=0)&&(row<6)&&(colm>=0)&&(colm<8))
        {
            ps->Eoclssptr[row][colm]=pn;
            asigned=1;

        }
        else
        {
            printf("This Seat is not in Economic Class, Please Try Again\n");
        }

        break;
    default:
        printf("Wrong Entry\n");
        break;
    }
    return asigned;
}
void Free_Seat(ListNode* pn,Seats *ps)
{
    uint8_t Free=0;
    uint32_t Class;
    uint32_t row;
    uint8_t col;
    uint32_t colmdecimal;
    while(!Free)
    {
        printf("Enter the reserved class (1) for First Class (2) for Business (3) for premium Economic Class (4) for Economic Class\n:  ");
        scanf("%d",&Class);
        printf("Row:  ");
        scanf("%d",&row);
        printf("Column: ");
        scanf(" %c",&col);
        colmdecimal=col-'A';

        switch (Class)
        {
        case First:
            row=row-1;
            if((row>=0)&&(row<3)&&(colmdecimal>=0)&&(colmdecimal<6))
            {

                if(ps->Frclssptr[row][colmdecimal]== pn)
                {

                    ps->Frclssptr[row][colmdecimal]=NULL;
                    Free=1;
                    printf("Seat is Free\n");

                }
                else
                {
                    printf("This seat is No registered to this Client\n");
                }

            }
            else
            {
                printf("This Seat is not in First Class, Please Try Again\n");
            }
            break;
        case Bus:
            row=row-7;
            if((row>=0)&&(row<4)&&(colmdecimal>=0)&&(colmdecimal<6))
            {
                if(ps->Bzclssptr[row][colmdecimal]==pn)
                {
                    ps->Bzclssptr[row][colmdecimal]=NULL;
                    Free=1;
                    printf("Seat is Free\n");
                }
                else
                {
                    printf("This seat is No registered to this Client\n ");
                }

            }
            else
            {
                printf("This Seat is not in Business Class, Please Try Again\n");
            }
            break;
        case PreEco:
            row=row-22;
            if((row>=0)&&(row<8)&&(colmdecimal>=0)&&(colmdecimal<8))
            {
                if(ps->Prclssptr[row][colmdecimal]==pn)
                {
                    ps->Prclssptr[row][colmdecimal]=NULL;
                    Free=1;
                    printf("Seat is Free\n");
                }
                else
                {
                    printf("This seat is No registered to this Client\n ");
                }
            }
            else
            {
                printf("This Seat is not in Premium Economic Class, Please Try Again\n");
            }
            break;
        case Eco:
            row=row-22;
            if((row>=0)&&(row<6)&&(colmdecimal>=0)&&(colmdecimal<8))
            {
                if (ps->Eoclssptr[row][colmdecimal]==pn)
                {
                    ps->Eoclssptr[row][colmdecimal]=NULL;
                    Free=1;
                    printf("Seat is Free\n");
                }
                else
                {
                    printf("This seat is No registered to this Client\n ");
                }
            }
            else
            {
                printf("This Seat is not in Economic Class, Please Try Again\n");
            }
            break;
        default:
            printf("wrong Entry Please try again\n");
            break;
        }
    }

}
void FirstClass(Seats*ps)
{
    uint32_t i,j;
    uint8_t flag=0;
    for (i=0; i<3; i++)
    {
        for(j=0; j<6; j++)
        {
            if(ps->Frclssptr[i][j]!=NULL)
            {
                printf("(%d %c)- ",i+1,j+'A');
                printf("%s\t",ps->Frclssptr[i][j]->entry.Name);
                printf("%d\n",ps->Frclssptr[i][j]->entry.ID );
                flag=1;
            }
        }
    }
    if(!flag)
    {
        printf("Class is Empty");
    }

}
void BusClass(Seats*ps)
{
    uint32_t i,j;
    uint8_t flag=0;
    for (i=0; i<4; i++)
    {
        for(j=0; j<6; j++)
        {
            if(ps->Bzclssptr[i][j]!=NULL)
            {
                printf("(%d %c)- ",i+7,j+'A');
                printf("%s\t",ps->Bzclssptr[i][j]->entry.Name);
                printf("%d\n",ps->Bzclssptr[i][j]->entry.ID );
                flag=1;
            }
        }
    }
    if(!flag)
    {
        printf("Class is Empty");
    }


}
void PremClass(Seats*ps)
{
    uint32_t i,j;
    uint8_t flag=0;

    for (i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(ps->Prclssptr[i][j]!=NULL)
            {
                printf("(%d %c)- ",i+22,j+'A');
                printf("%s\t",ps->Prclssptr[i][j]->entry.Name);
                printf("%d\n",ps->Prclssptr[i][j]->entry.ID );
                flag=1;
            }
        }
    }
    if(!flag)
    {
        printf("Class is Empty");
    }

}
void EcoClass(Seats*ps)
{
    int i,j;
    uint8_t flag=0;

    for (i=0; i<6; i++)
    {
        for(j=0; j<8; j++)
        {
            if(ps->Eoclssptr[i][j]!=NULL)
            {
                printf("Seat\t Name\t ID\n");
                printf("(%d %c)- ",i+45,j+'A');
                printf("%s\t",ps->Eoclssptr[i][j]->entry.Name);
                printf("%d\n",ps->Eoclssptr[i][j]->entry.ID );
                flag=1;
            }
        }
    }
    if(!flag)
    {
        printf("Class is Empty");
    }

}

uint8_t SeatReserved(uint8_t PreClass,uint32_t row, uint32_t colm,Seats *ps)
{
    uint8_t RES=0;
    switch (PreClass)
    {
    case First:
        row=row-1;
        if((row>=0)&&(row<3)&&(colm>=0)&&(colm<6))
        {
            if(ps->Frclssptr[row][colm]!=NULL)
            {
                RES=1;
            }
        }
        break;
    case Bus:
        row=row-7;
        if((row>=0)&&(row<4)&&(colm>=0)&&(colm<6))
        {
            if(ps->Bzclssptr[row][colm]!=NULL)
            {
                RES=1;
            }
        }
        break;

    case PreEco:
        row=row-22;
        if((row>=0)&&(row<8)&&(colm>=0)&&(colm<8))
        {
            if(ps->Prclssptr[row][colm]!=NULL)
            {
                RES=1;
            }
        }
        break;

    case Eco:
        row=row-45;
        if((row>=0)&&(row<6)&&(colm>=0)&&(colm<8))
        {
            if(ps->Eoclssptr[row][colm]!=NULL)
            {

                RES=1;
            }
        }
        break;
    default:
        printf("Wrong Entry");
        break;

    }
    return RES;
}
uint8_t SeatsFull(Seats* ps)
{
   uint8_t Re=0;
   uint32_t i,j;
    for (i=0; i<3; i++)
    {
        for(j=0; j<6; j++)
        {
            if (ps->Frclssptr[i][j]==NULL)
           {
                Re++;
           }
        }
    }
    for (i=0; i<4; i++)
    {
        for(j=0; j<6; j++)
        {
            if(ps->Bzclssptr[i][j]==NULL){Re++;}
        }
    }
    for (i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(ps->Prclssptr[i][j]==NULL){Re++;}
        }
    }
    for (i=0; i<6; i++)
    {
        for(j=0; j<8; j++)
        {
            if(ps->Eoclssptr[i][j]==NULL){Re++;}
        }
    }
    return !Re;

}
