#include"Naming.h"
typedef enum clss {First=1, Bus, PreEco, Eco} Class;
typedef enum oper {NewClient, DeleteClient,ClientList,ClientEdit,FreeSeats,ClassList,InsertTicket,SearchTicket}OPe;


typedef struct listentry {
    uint8_t Name[20];
	uint32_t ID;
	uint8_t BirthDay[10];
	uint8_t Address[20];
	uint8_t Phone[16];

}ListEntry;

typedef struct listnode{
	ListEntry entry;
	struct listnode* next;
	struct listnode* prev;

}ListNode;

typedef struct seats{
    ListNode *Frclssptr[3][6];
    ListNode *Bzclssptr[4][6];
    ListNode *Prclssptr[8][8];
    ListNode *Eoclssptr[6][8];
}Seats;

typedef struct llist{
	ListNode *top;
    uint32_t Size;

}List;

typedef struct dataentry{
    uint8_t Namecopy[20];
    uint32_t IDcopy;
    uint8_t BDcopy[10];
	uint8_t Addrcopy[20];
	uint8_t Phcopy[16];

}DataEntry;

typedef struct namestack{
    DataEntry entry[100];
    uint32_t top;

}NameStack;
/*-------------------Binary Search Tree--------------------------*/
typedef struct ticentry{
    int tic;
    int ID;
}TicEntry;
typedef struct treenode
{
    TicEntry entry;
    struct treenode* left;
    struct treenode* right;
} TreeNode;

typedef struct tree
{
    TreeNode* root;
    TreeNode* parent;
    TreeNode* Search;
} Tree;

/*--------------------------------------------------------*/


/*Client Prototypes*/
uint32_t MAIN_MENU      (void);
void    NEW_CLIENT      (uint32_t i,List *pl,Seats* ps);
void    DELETE_CLIENT   (List* pl, Seats *ps  );
void    CLIENT_EDIT     (List* pl, Seats *ps);
void    CLASS_LIST      (List* pl, Seats *ps);
void    CLIENT_LIST     (List* pl);

void CreatList          (List* );
uint8_t ClientListEmpty (List* );
void InsertFunction     (ListEntry* ,uint32_t , List* , Seats* );
void DeleteFunction     (ListEntry* ,uint32_t , List* ,Seats* );
void EditFunction       (ListEntry* ,uint32_t , List* ,Seats* );
void ScanfClientData    (ListEntry* );
void PrintClientData    (ListEntry* );
uint32_t ClientSearch   (ListEntry* , List* );

/*Seats Prototypes*/

void CreatSeats    (Seats*);
void PrintFreeSeats(Seats*);

uint8_t AssignSeat  (uint8_t ,uint32_t , uint32_t ,ListNode* ,Seats *);
uint8_t SeatReserved(uint8_t,uint32_t , uint32_t ,Seats *);
void    Class_Seats (ListNode* ,Seats* );
void    Free_Seat   (ListNode* ,Seats* );
uint8_t SeatsFull   (Seats* );
void    FirstClass  (Seats* );
void    BusClass    (Seats* );
void    PremClass   (Seats* );
void    EcoClass    (Seats* );

/*Name stack Prototypes*/
void    CreatNameStack (NameStack *);
void    List_Print     (NameStack *);
void    CDataSort      (NameStack *);
void    Push           (ListEntry* ,NameStack* );
int32_t compare_info   (uint8_t* ,uint8_t* );

/* Binary Search Tree*/
void CreatTree(Tree* pt);
TreeNode* Insert( TicEntry*pe, Tree* pt );
uint8_t TreeEmpty(Tree* pt);
TreeNode* BinarySearch(TicEntry* pe, Tree* pt);


void INSERT_TICKET(Tree*pt);
void T_SEARCH_PRINT(Tree*pt);
