#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void createContact(AddressBook *addressBook)
{
    // Declare a flag variable to control the name input loop
    int flag = 1;

    // Loop to read and validate the name
    while (flag)
    {
        // Declare a string to hold the name input
        char name[200];

        // Prompt the user to enter a name
        printf("Enter the name:");

        // Read the input string including spaces
        scanf(" %[^\n]", name);

        // Initialize index for name validation
        int i = 0;

        // Validate the name to check if its only alphabets or spaces
        while (name[i] != '\0')
        {
            if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || (name[i] == ' '))
            {
                flag = 0; // Name is valid,set flag to 0 to stop further validation
            }
            else
            {
                // Invalid name, display error and reset flag to 1 to loop again
                printf("INFO: Name validation is failed\n");
                flag = 1;
                break;
            }
            i++;
        }

        // If the name is valid, copy it to the structure
        if (flag == 0)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name);
            break; // Exit the loop after copying the name
        }
    }

    // Initialize a variable to control mobile number validation loop
    int valid = 1;
    while (valid)
    {
        // Read the Mobile number from the user
        char phone[200];
        printf("Enter the mobile no:");
        scanf(" %[^\n]", phone);
        // validate the length of the mobile number(should be exactly 10 digits)
        int len = strlen(phone);
        if (len != 10)
        {
            printf("please enter 10 digits only\n");
            valid = 1;
            continue; // Continue loop if length is not 10
        }

        // validate that the mobile number contains only digits
        for (int i = 0; i < len; i++)
        {
            if (!isdigit(phone[i]))
            {
                printf("Invalid number : please enter the digit only\n");
                valid = 1; // Loop again if non-digit is found
                break;
            }
            else
            {
                valid = 0; // valid number
            }
        }

        // Check if the mobile number already exists in the contact list
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            {
                printf("Existing Number\n");
                valid = 1; // Reset loop if number exists
                break;
            }
            else
            {
                valid = 0; // No duplicate number found
            }
        }

        // If mobile number is valid and unique, copy it to the structure
        if (valid == 0)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
        }
    }

    // Reset flag for email validation loop
    flag = 1;
    while (flag)
    {
        // Read email from the user
        char check[200] = "@gmail.com"; // Pattern to check if email ends with "@gmail.com"
        char email[200];
        printf("Enter the email:");
        scanf(" %[^\n]", email);

        // Validate email address by checking for "@gmail.com" domain
        if (!(strstr(email, check)))
        {
            printf("Invalid email id \n");
            flag = 1; // Loop again if email doesn't contain "@gmail.com"
            continue;
        }

        // Check if the email already exists in the contact list
        for (int i = 0; i < addressBook->contactCount + 1; i++)
        {
            if (strcmp(addressBook->contacts[i].email, email) == 0)
            {
                printf("Existing email\n");
                flag = 1; // Loop again if duplicate email is found
                break;
            }
            else
            {
                flag = 0; // Loop again if duplicate email is found
            }
        }

        // If email is valid and unique, copy it to the structure
        if (flag == 0)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].email, email);
        }
    }
    addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook)  
{
    int flag = 1;  
    int n;     
    while (flag)  
    {
        // Read the choice from the user
        printf("Enter the choice:\n1.Name\n2.Mobile number\n3.Email\n4.Exit\n");
        scanf("%d", &n);  
        int i = 0;      
        if (n == 4)   // Exit condition for the loop
        {
            flag=0;    // Set flag to 0 to exit the loop
        }
        char name[200];
        char phone[200];
        char email[200];
        int found = 0;
        int count = 0;
        switch (n)
        {
        case 1:
            // Read the name from the user
            printf("Enter the name:");
            scanf("  %[^\n]", name);
            for (i = 0; i < addressBook->contactCount; i++)    // Loop through contacts
            {
                if (strcasecmp(addressBook->contacts[i].name, name) == 0)   // Validate if the name matches
                {
                    found = 1;
                    count++;   // Keep count of contacts with the same name
                    printf("Name: %s\t", addressBook->contacts[i].name);
                    printf("Mobile number: %s\t", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);
                }
                else if ((strcasestr(addressBook->contacts[i].name, name)))   // Partial match of name
                {
                    found = 1;
                    printf("Name: %s\t", addressBook->contacts[i].name);
                    printf("Mobile number: %s\t", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);
                    
                }
            }
            // same names are found
            if (count > 1)
            {
                printf("Similar contacts found\n");
            }
            if(count==1)
            {
                flag=0;
                break;
            }
            // name not found
            if (!found)
            {
                printf("Contact not found\n");
                flag = 1;
                break;
            }

        case 2:
            // Read the mobile number from the user
            printf("Enter the mobile number:");
            scanf("  %[^\n]", phone);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, phone) == 0) // validating the name is present or not
                {
                    printf("Contact found\n");
                    printf("Name: %s\t", addressBook->contacts[i].name);
                    printf("Mobile number: %s\t", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);
                    found = 1;
                    flag=0;
                    break;   // Exit loop once contact is found
                }
            }
            // mobile number is not found
            if (!found)
            {
                printf("Contact not found\n");
                flag = 1; // continue search
            }
            break;

        case 3:
            // Read the email from the user
            printf("Enter the email:");
            scanf("  %[^\n]", email);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, email) == 0) // validating the email is present or not
                {
                    printf("Contact found\n");
                    printf("Name: %s\t", addressBook->contacts[i].name);
                    printf("Mobile number: %s\t", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);
                    found = 1;
                    flag=0;
                    break;
                }
            }
            // email is not found
            if (!found)
            {
                printf("Contact not found\n");
                flag = 1;
            }
            break;
        }
    }
}

void editContact(AddressBook *addressBook)
{
    int n;
    int flag = 1;
    while (flag)
    {
        // search the contact to edit
        printf("Search the contact by:\n1.Name\n2.Mobile number\n3.Email\n4.Exit\n");
        scanf("%d", &n);
        if (n == 4) // Exit condition
        {
            flag = 0; 
        }
        char name[200];
        char phone[200];
        char email[200];
        int i = 0;
        int j;
        int found = 0;
        int count = 0;
        switch (n)
        {
        case 1:
            // Searching by name
            printf("Enter the current contact name:\n");
            scanf(" %[^\n]", name);
            for (int i = 0; i < addressBook->contactCount; i++)  // Loop to find the contact by name
            {
                if (strcasecmp(addressBook->contacts[i].name, name) == 0)
                {
                    found = 1;
                    j = i;    // Store the index of the contact
                    count++;
                    printf("Name: %s\t", addressBook->contacts[j].name);
                    printf("Mobile number: %s\t", addressBook->contacts[j].phone);
                    printf("Email : %s\n", addressBook->contacts[j].email);
                }
            }
            // similar contacts found
            if (count > 1)
            {
                printf("Similar names found!!!\n");
                break;
            }
            // contact not found
            if (!found)
            {
                printf("Contact not found\n");
                break;
            }
            int m;
            // Ask user what to edit
            printf("What need to edit?\n1.Name\n2.Mobile number\n3.Email\n4.Exit\n");
            scanf("%d", &m);
            switch (m)
            {
            case 1:
            //Edit name
                printf("Enter the new name:\n");
                scanf(" %[^\n]", name);
                while (name[i] != '\0')  // Validate name (should only contain letters and spaces)
                {
                    if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || (name[i] == ' '))
                    {
                        flag = 0; // validate name
                    }
                    else
                    {
                        printf("Enter the valid name\n");
                        flag = 1; // Invalid name
                        break;
                    }
                    i++;
                }
                if (flag == 0)
                {
                    strcpy(addressBook->contacts[j].name, name);  // copy new name  to contact
                }
                break;

            case 2:
                printf("Enter the new mobile number:");
                scanf(" %[^\n]", phone);
                int len = strlen(phone);
                if (len != 10) // Validate mobile number length
                {
                    printf("please enter 10 digits only\n");
                    flag = 1;
                    continue;
                }
                else
                {
                    flag = 0;
                }
                for (int i = 0; i < len; i++)   // Check if all digits
                {
                    if (!isdigit(phone[i]))
                    {
                        printf("Invalid number : please enter the digit only\n");
                        flag = 1;
                        break;
                    }
                    else
                    {
                        flag = 0;
                    }
                }
                if (flag == 0)
                {
                    strcpy(addressBook->contacts[j].phone, phone);  // Copy new phone number
                }
                break;

            case 3:
            // Edit email
                char check[200] = "@gmail.com";
                printf("Enter the new email:");
                scanf(" %[^\n]", email);
                if (!(strstr(email, check))) // Validate email format
                {
                    printf("Invalid\n");
                    flag = 1;
                    continue;
                }
                else
                {
                    flag = 0;
                }
                for (int i = 0; i < addressBook->contactCount; i++)   // Check if email already exists
                {
                    if (strcmp(addressBook->contacts[i].email, email) == 0)
                    {
                        printf("Existing email\n");
                        flag = 1;
                        break;
                    }
                    else
                    {
                        flag = 0;
                    }
                }
                if (flag == 0)
                {
                    strcpy(addressBook->contacts[j].email, email);  // Copy new email to contact
                }
                break;
            }

            break;

        case 2:
            // search by mobile number
            printf("Enter the current contact mobile number:");
            scanf(" %[^\n]", phone);
            for (int i = 0; i < addressBook->contactCount; i++)  // Loop to find contact by mobile number
            {
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    j = i;
                    found = 1;
                }
            }
            if (!found)
            {
                printf("Contact not found\n");
                flag = 1;
            }
            if (found == 1)
            {
                printf("Name: %s\t", addressBook->contacts[j].name);
                printf("Mobile number: %s\t", addressBook->contacts[j].phone);
                printf("Email : %s\n", addressBook->contacts[j].email);
                int a;
                printf("What need to edit?\n1.Name\n2.Mobile number\n3.Email\n4.Exit\n");
                scanf("%d", &a);
                switch (a)
                {
                case 1:
                    printf("Enter the new name:\n");
                    scanf(" %[^\n]", name);
                    while (name[i] != '\0')
                    {
                        if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || (name[i] == ' '))
                        {
                            flag = 0;
                        }
                        else
                        {
                            printf("Enter the valid name\n");
                            flag = 1;
                            break;
                        }
                        i++;
                    }
                    if (flag == 0)
                    {
                        strcpy(addressBook->contacts[j].name, name); // copy new name
                    }
                    break;

                case 2:
                    printf("Enter the new mobile number:");
                    scanf(" %[^\n]", phone);
                    int len = strlen(phone);
                    if (len != 10)
                    {
                        printf("please enter 10 digits only\n");
                        flag = 1;
                        continue;
                    }
                    else
                    {
                        flag = 0;
                    }
                    for (int i = 0; i < len; i++)
                    {
                        if (!isdigit(phone[i]))
                        {
                            printf("Invalid number : please enter the digit only\n");
                            flag = 1;
                            break;
                        }
                        else
                        {
                            flag = 0;
                        }
                    }
                    if (flag == 0)
                    {
                        strcpy(addressBook->contacts[j].phone, phone);   // copy new phone number
                    }
                    break;

                case 3:
                    char check[200] = "@gmail.com";
                    printf("Enter the new email:");
                    scanf(" %[^\n]", email);
                    if (!(strstr(email, check)))
                    {
                        printf("Invalid\n");
                        flag = 1;
                        continue;
                    }
                    else
                    {
                        flag = 0;
                    }
                    for (int i = 0; i < addressBook->contactCount; i++)
                    {
                        if (strcmp(addressBook->contacts[i].email, email) == 0)
                        {
                            printf("Existing email\n");
                            flag = 1;
                            break;
                        }
                        else
                        {
                            flag = 0;
                        }
                    }
                    if (flag == 0)
                    {
                        strcpy(addressBook->contacts[j].email, email);  // copy new email
                    }
                    break;
                }
            }
            break;

        case 3:
        //search by gmail
            printf("Enter the current contact email:");
            scanf(" %[^\n]", email);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, email) == 0)
                {
                    j = i;
                    found = 1;
                }
            }
            if (!found)
            {
                printf("Contact not found\n");
                flag = 1;
            }
            if (found == 1)
            {
                printf("Name: %s\t", addressBook->contacts[j].name);
                printf("Mobile number: %s\t", addressBook->contacts[j].phone);
                printf("Email : %s\n", addressBook->contacts[j].email);
                int a;
                printf("What need to edit?\n1.Name\n2.Mobile number\n3.Email\n4.Exit\n");
                scanf("%d", &a);
                switch (a)
                {
                case 1:
                    printf("Enter the new name:\n");
                    scanf(" %[^\n]", name);
                    while (name[i] != '\0')
                    {
                        if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || (name[i] == ' '))
                        {
                            flag = 0;
                        }
                        else
                        {
                            printf("Enter the valid name\n");
                            flag = 1;
                            break;
                        }
                        i++;
                    }
                    if (flag == 0)
                    {
                        strcpy(addressBook->contacts[j].name, name); // copy a new name
                    }
                    break;

                case 2:
                    printf("Enter the new mobile number:");
                    scanf(" %[^\n]", phone);
                    int len = strlen(phone);
                    if (len != 10)
                    {
                        printf("please enter 10 digits only\n");
                        flag = 1;
                        continue;
                    }
                    else
                    {
                        flag = 0;
                    }
                    for (int i = 0; i < len; i++)
                    {
                        if (!isdigit(phone[i]))
                        {
                            printf("Invalid number : please enter the digit only\n");
                            flag = 1;
                            break;
                        }
                        else
                        {
                            flag = 0;
                        }
                    }
                    if (flag == 0)
                    {
                        strcpy(addressBook->contacts[j].phone, phone); // copy a new phone number
                    }
                    break;

                case 3:
                    char check[200] = "@gmail.com";
                    printf("Enter the new email:");
                    scanf(" %[^\n]", email);
                    if (!(strstr(email, check)))
                    {
                        printf("Invalid\n");
                        flag = 1;
                        continue;
                    }
                    else
                    {
                        flag = 0;
                    }
                    for (int i = 0; i < addressBook->contactCount; i++)
                    {
                        if (strcmp(addressBook->contacts[i].email, email) == 0)
                        {
                            printf("Existing email\n");
                            flag = 1;
                            break;
                        }
                        else
                        {
                            flag = 0;
                        }
                    }
                    if (flag == 0)
                    {
                        strcpy(addressBook->contacts[j].email, email);  // copy a new email
                    }
                    break;
                }
            }
            break;
        }
    }
}

void deleteContact(AddressBook *addressBook)
{

    int flag = 1;
    int n;
    while (flag)
    {
        // Search for the contact to delete
        printf("Enter the choice:\n1.Name\n2.Mobile number\n3.Email\n4.Exit\n");
        scanf("%d", &n);
        if (n == 4)
        {
            flag = 0; // Exit condition
        }
        char name[200];
        char phone[200];
        char email[200];
        int i = 0;
        int j;
        int found = 0;
        int count = 0;
        switch (n)
        {
        case 1:
            printf("Enter the name:");
            scanf("  %[^\n]", name);
            // find the contact by name
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasecmp(addressBook->contacts[i].name, name) == 0)
                {
                    found = 1;
                    j = i;
                    count++;   // Keep count of contacts with the same name
                    printf("Name: %s\t", addressBook->contacts[j].name);
                    printf("Mobile number: %s\t", addressBook->contacts[j].phone);
                    printf("Email : %s\n", addressBook->contacts[j].email);
                }
            }
            if (count == 1)
            {
                // delete the contact by shifting
                for (i = j; i < addressBook->contactCount; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;
                printf("Contact is deleted\n");
            }
            if (count > 1)
            {
                printf("Similar contacts found\n");
            }
            if (!found)
            {
                printf("Contact not found\n");
                flag = 1;
            }
            break;

        case 2:
            printf("Enter the mobile number:");
            scanf("  %[^\n]", phone);
            // Find the contact by phone number
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    found = 1;
                    j = i;
                    break;
                }
            }
            if (found == 1)
            {
                // Delete the contact by shifting
                for (i = j; i < addressBook->contactCount; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;
                printf("Contact is deleted\n");
            }
            if (!found)
            {
                printf("Contact not found\n");
                flag = 1;
            }
            break;

        case 3:
            printf("Enter the email:");
            //Find the contact by email
            scanf("  %[^\n]", email);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, email) == 0)
                {
                    found = 1;
                    j = i;
                    break;
                }
            }
            if (found == 1)
            {
                // Delete the contact by shifting
                for (i = j; i < addressBook->contactCount; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;
                printf("Contact is deleted\n");
            }
            if (!found)
            {
                printf("Contact not found\n");
                flag = 1;
            }
            break;
        }
    }
}

void listContacts(AddressBook *addressBook)
{
    //Sort the contacts by name using bubble sort
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            if (strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0)
            {
                // Swap the contacts
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
    printf("Name\t\t\t Phone\t\t\t Email\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-20s\t %-20s\t %-20s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}
