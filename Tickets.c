#include"Tickets.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#define MAX_WALLET_TICKETS 10
#define MAX_DATABASE_TICKETS 100
#define ID_LENGTH 3
#define MAX_OPTION 7


// Returns 1 if a is a valid option between 1 and MAX_OPTION. else, 0
int isValidOption(int a)
{
    while(getchar()!='\n');
    return (a>=1 && a<=MAX_OPTION);
}

// Returns 1 if c is A-Z or 0-9
int isValidAscii(char c)
{
    char values[35] = "ABCDEFGHIJKLMNOPQRSTUVWXY0123456789";
    for(int i=0; i<35; i++)
        if(c==values[i])
            return 1;
    return 0;
}

// Returns 1 if the id is a valid ID (all digits A-Z or 0-9(
int isValidID(char * id)
{
    for(int i=0; i<ID_LENGTH; i++)
        if(!isValidAscii(id[i]))
            return 0;
    return 1;
}

// Generates a random ascii character and returns it
char randomAsciiChar()
{
    char * values = "ABCDEFGHIJKLMNOPQRSTUVWXY0123456789";
    char ascii = values[rand()%35];
    return ascii;
}

// Generates a valid ticket ID and returns its pointer
char * generateTicketID()
{
    char * id = malloc(sizeof(char)*ID_LENGTH);
    for(int i=0; i<ID_LENGTH; i++)
        id[i]=randomAsciiChar();
    return id;
}

// Add ticket to wallet
void addTicketToWallet(char * ticketID, TicketWallet * wallet)
{
    wallet->tickets[wallet->index].isChecked=0;
    for(int i=0; i<ID_LENGTH; i++)
        wallet->tickets[wallet->index].id[i]=ticketID[i];
    wallet->index++;
}

// Add ticket to database
void addTicketToDatabase(char * ticketID, TicketDatabase * database)
{
    database->tickets[database->index].isChecked=0;
    for(int i=0; i<ID_LENGTH; i++)
        database->tickets[database->index].id[i]=ticketID[i];
    database->index++;
}

// Returns 1 if the wallet is empty, 0 in other case
int emptyWallet(TicketWallet wallet)
{
    return wallet.index==0;
}

// Prints all wallet tickets
void showWalletTickets(TicketWallet wallet)
{
    for(int i=0; i<wallet.index; i++)
    {
        printf("Ticket %d: %s\n",i+1,wallet.tickets[i].id);
    }
}

// Returns 1 if database is empty, 0 in other case
int emptyDatabase(TicketDatabase database)
{
    return database.index==0;
}

// Prints the database
void showDatabaseTickets(TicketDatabase database)
{
    for(int i=0; i<database.index; i++)
    {
        printf("Ticket %d: %s\n",i+1,database.tickets[i].id);
    }
}

// Deletes the ticket from wallet. The last ticket will fill the deleted ticket position
void deleteTicketFromWallet(TicketWallet * wallet, int n)
{
    strcpy(wallet->tickets[n-1].id,wallet->tickets[wallet->index-1].id);
    wallet->tickets[n-1].isChecked = wallet->tickets[wallet->index-1].isChecked;
    wallet->index--;
}

//
int searchTicketInDatabase(char * id, TicketDatabase database)
{
    int index = 0;
    for(int i=0; i<database.index; i++)
    {
        if(strcmp(id,database.tickets[i].id)==0)
            return index;
        index++;
    }
    return index;
}

// Deletes the ticket from database. The last ticket will fill the deleted ticket position
void deleteTicketFromDatabase(TicketDatabase * database, int n)
{
    strcpy(database->tickets[n-1].id,database->tickets[database->index-1].id);
    database->tickets[n-1].isChecked = database->tickets[database->index-1].isChecked;
    database->index--;
}

// Returns 1 if the ticket is valid and hasn't been validated, 0 if it's no valid and 2 if it had been already validated
int checkTicketByID(Ticket ticket, TicketDatabase database)
{
    for(int i=0; i<database.index; i++)
    {
        if(strcmp(database.tickets[i].id,ticket.id)==0 && database.tickets[i].isChecked==0)
            return 1;
        else if(strcmp(database.tickets[i].id,ticket.id)==0 && database.tickets[i].isChecked==1)
            return 2;
    }
    return 0;
}

// Searchs for the ticket in the database and puts it valid int to 1
void validateTicketInDatabase(char * id, TicketDatabase * database)
{
    for(int i=0; i<database->index; i++)
        if(strcmp(id,database->tickets[i].id)==0)
            database->tickets[i].isChecked=1;
}








