#ifndef TICKETS_H_INCLUDED
#define TICKETS_H_INCLUDED

#define MAX_WALLET_TICKETS 10
#define MAX_DATABASE_TICKETS 100
#define ID_LENGTH 3
#define MAX_OPTION 7

struct TicketRep
{
    int isChecked;
    char id[ID_LENGTH];
};
typedef struct TicketRep Ticket;

struct TicketDatabaseRep
{
    int index;
    Ticket tickets[MAX_DATABASE_TICKETS];
};
typedef struct TicketDatabaseRep TicketDatabase;

struct TicketWalletRep
{
    int index;
    Ticket tickets[MAX_WALLET_TICKETS];
};
typedef struct TicketWalletRep TicketWallet;

int isValidOption(int a);

int isValidAscii(char c);

int isValidID(char * id);

char randomAsciiChar();

char * generateTicketID();

void addTicketToWallet(char * ticketID, TicketWallet * wallet);

void addTicketToDatabase(char * ticketID, TicketDatabase * database);

int emptyWallet(TicketWallet wallet);

void showWalletTickets(TicketWallet wallet);

int emptyDatabase(TicketDatabase database);

void showDatabaseTickets(TicketDatabase database);

void deleteTicketFromWallet(TicketWallet * wallet, int n);

void deleteTicketFromDatabase(TicketDatabase * database, int n);

int checkTicketByID(Ticket ticket, TicketDatabase database);

void validateTicketInDatabase(char * id, TicketDatabase * database);




#endif // TICKETS_H_INCLUDED
