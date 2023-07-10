#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include"Tickets.h"

void printFullDatabaseInfo(TicketDatabase database)
{
    for(int i=0; i<database.index; i++)
        printf("%d | %s\n",database.tickets[i].isChecked,database.tickets[i].id);
}

//###############################################################################################################################################

int main()
{
    TicketDatabase database = {0};
    TicketWallet wallet = {0};
    srand(time(NULL));
    int option;

    // main loop
    do
    {
        printf("##################################################\n");
        printf("###     TICKET SYSTEM MANAGEMENT AND CHECK     ###\n");
        printf("##################################################\n\n");
        printf("CHOOSE AN OPTION:\n\t1. Buy tickets\n\t2. Add ticket manually\n\t3. See my ticket wallet\n\t4. See ticket database");
        printf("\n\t5. Sell tickets\n\t6. Ticket check\n\t7. Exit\nOption: ");
        scanf("%d",&option);
        if(isValidOption(option)!=1)
            printf("That is not a valid option.\n\n");
        else
        {
            switch(option)
            {
            case 1:
            {
                // ADD A AUTO-GENERATED TICKET TO YOUR WALLET. YOU BUY TICKETS ON A WEB AND THEY ARE ADDED TO YOUR WALLET AND
                // THEIR DATABASE
                int how_many;
                printf("\nHow many tickets do you want to buy?\nAnswer: ");
                scanf("%d",&how_many);
                for(int i=0; i<how_many; i++)
                {
                    char * id;
                    id = generateTicketID();
                    addTicketToWallet(id,&wallet);
                    addTicketToDatabase(id,&database);
                }
                printf("\nYour tickets had been added to your account.\nYou can check them in option 3 'See my ticket wallet'\n");
                break;
            }
            case 2:
            {
                // ADD AN INVENTED TICKET TO YOUR WALLET. PROBABLY IT WON'T BE ON THE DATABASE
                // THE PROGRAM ASK YOU FOR AN INVENTED ID
                char id[ID_LENGTH];
                do
                {
                    printf("Enter the ticket ID (only the three first inputs will be added): ");
                    scanf("%s",id);
                    if(!isValidID(id))
                        printf("That ID is not valid.\n\n");
                }
                while(!isValidID(id));
                addTicketToWallet(id,&wallet);
                printf("Your ticket has been successfully added manually.");
                break;
            }
            case 3:
            {
                // SHOWS ALL MY WALLED TICKETS: BOUGHT AND ADDED MANUALLY
                printf("\n====== YOUR WALLET ======\n");
                if(!emptyWallet(wallet))
                    showWalletTickets(wallet);
                else
                    printf("You don't have any tickets.");
                break;
            }
            case 4:
            {
                // SHOWS DATABASE TICKETS. OBVIOUSLY IT ONLY STORES THE TICKETS THAT WERE BOUGHT, NOT THE MANUALLY ADDED ONES
                printf("\n====== DATABASE ======\n");
                if(!emptyDatabase(database))
                    //showDatabaseTickets(database);
                    printFullDatabaseInfo(database);
                else
                    printf("The database is empty.");
                break;
            }
            case 5:
            {
                // SELLS THE PROVIDED TICKET BY STORE NUMBER. IT MOVES THE LAST TICKET TO THE EMPTY TICKET POSITION
                if (!emptyWallet(wallet))
                {
                    int n;
                    printf("This is your ticket list:\n\n");
                    showWalletTickets(wallet);
                    do
                    {
                        printf("Which ticket do you want to sell?\nNumber: ");
                        scanf("%d",&n);
                    }
                    while(n<1 || n>wallet.index);
                    deleteTicketFromWallet(&wallet,n);
                    deleteTicketFromDatabase(&database,n);
                    printf("Your ticket %d has been sold.\n",n);
                }
                else
                    printf("You don't have any tickets.");
                break;
            }
            case 6:
            {
                // CHECKS ALL THE TICKETS IN YOUR WALLET AND SAYS A MESSAGE
                if(!emptyWallet(wallet))
                {
                    for(int i=0; i<wallet.index; i++)
                    {
                        if(checkTicketByID(wallet.tickets[i],database)==1)
                        {
                            printf("The ticket %s has been succesfully validated.\n",wallet.tickets[i].id);
                            wallet.tickets[i].isChecked = 1;
                            validateTicketInDatabase(wallet.tickets[i].id,&database);
                        }
                        else if(checkTicketByID(wallet.tickets[i],database)==2)
                            printf("The ticket %s has already been validated.\n",wallet.tickets[i].id);
                        else
                            printf("The ticket %s could not been validated.\n",wallet.tickets[i].id);
                    }
                }
                else
                    printf("You don't have any tickets.");
                break;
            }

            }

        }
        printf("\n\nPress any key to continue.\n");
        getch();
        system("cls");
    }
    while(option!=MAX_OPTION);
}