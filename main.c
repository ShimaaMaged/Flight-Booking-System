#include <stdio.h>
#include <stdlib.h>
#include"header.h"

int main()
{
    uint32_t i=0;
    uint32_t ch;
    List L;
    Seats FL;
    Tree BT;
    CreatList (&L);
    CreatSeats(&FL);
    CreatTree(&BT);


    while (1)
    {
        ch=MAIN_MENU();
        switch (ch-1)
        {
        case NewClient:
            if(!SeatsFull(&FL))
            {
                NEW_CLIENT(i,&L,&FL);
                i++;
            }
            break;
        case DeleteClient:
            if(!ClientListEmpty(&L)){DELETE_CLIENT(&L,&FL);}
            else
            {
                printf("List is Empty\n");
            }
            break;
        case ClientList:
            if(!ClientListEmpty(&L)){CLIENT_LIST (&L);}
            else
            {
                printf("List is Empty\n");
            }
            break;
        case ClientEdit:
            if(!ClientListEmpty(&L)){CLIENT_EDIT (&L,&FL);}
            else
            {
                printf("List is Empty\n");
            }
            break;
        case FreeSeats:
            PrintFreeSeats(&FL);
            break;
        case ClassList:
            CLASS_LIST(&L,&FL);
            break;
        case InsertTicket:
            if(!ClientListEmpty(&L)){INSERT_TICKET(&BT);}
            break;
        case SearchTicket:
            if(!TreeEmpty(&BT)){T_SEARCH_PRINT(&BT);}
            break;

        default:
            /*nothing;*/
            break;
        }

    }
    return 0;
}
