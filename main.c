//Name:A V Ajay
//Date:25 sep 2024
//Description: C program to create an addressbook which contains contact with constitutents as name, phone, number and email ID.Also includes functions like create new contact,edit,delete and search.
#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        
        switch (choice) 
		{
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                 
                break;
            case 6:
                saveContactsToFile(&addressBook);
                printf("Saving and Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");

        }
    } while (choice != 6);
    
       return 0;
}
