#include"Tickets.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#define MAX_WALLET_TICKETS 10
#define MAX_DATABASE_TICKETS 100
#define ID_LENGTH 3
#define MAX_OPTION 7

int isValidOption(int a)
{
    while(getchar()!='\n');
    return (a>=1 && a<=MAX_OPTION);
}

int isValidAscii(char c)
{
    char values[35] = "ABCDEFGHIJKLMNOPQRSTUVWXY0123456789";
    for(int i=0; i<35; i++)
        if(c==values[i])
            return 1;
    return 0;
}

int isValidID(char * id)
{
    for(int i=0; i<ID_LENGTH; i++)
        if(!isValidAscii(id[i]))
            return 0;
    return 1;
}

char randomAsciiChar()
{
    char * values = "ABCDEFGHIJKLMNOPQRSTUVWXY0123456789";
    char ascii = values[rand()%35];
    return ascii;
}

char * generateTicketID()
{
    char * id = malloc(sizeof(char)*ID_LENGTH);
    for(int i=0; i<ID_LENGTH; i++)
        id[i]=randomAsciiChar();
    return id;
}

void addTicketToWallet(char * ticketID, TicketWallet * wallet)
{
    wallet->tickets[wallet->index].isChecked=0;
    for(int i=0; i<ID_LENGTH; i++)
        wallet->tickets[wallet->index].id[i]=ticketID[i];
    wallet->index++;
}

void addTicketToDatabase(char * ticketID, TicketDatabase * database)
{
    database->tickets[database->index].isChecked=0;
    for(int i=0; i<ID_LENGTH; i++)
        database->tickets[database->index].id[i]=ticketID[i];
    database->index++;
}

int emptyWallet(TicketWallet wallet)
{
    return wallet.index==0;
}

void showWalletTickets(TicketWallet wallet)
{
    for(int i=0; i<wallet.index; i++)
    {
        printf("Ticket %d: %s\n",i+1,wallet.tickets[i].id);
    }
}

int emptyDatabase(TicketDatabase database)
{
    return database.index==0;
}

void showDatabaseTickets(TicketDatabase database)
{
    for(int i=0; i<database.index; i++)
    {
        printf("Ticket %d: %s\n",i+1,database.tickets[i].id);
    }
}

void deleteTicketFromWallet(TicketWallet * wallet, int n)
{
    strcpy(wallet->tickets[n-1].id,wallet->tickets[wallet->index-1].id);
    wallet->tickets[n-1].isChecked = wallet->tickets[wallet->index-1].isChecked;
    wallet->index--;
}

void deleteTicketFromDatabase(TicketDatabase * database, int n)
{
    strcpy(database->tickets[n-1].id,database->tickets[database->index-1].id);
    database->tickets[n-1].isChecked = database->tickets[database->index-1].isChecked;
    database->index--;
}

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

void validateTicketInDatabase(char * id, TicketDatabase * database)
{
    for(int i=0; i<database->index; i++)
        if(strcmp(id,database->tickets[i].id)==0)
            database->tickets[i].isChecked=1;
}








