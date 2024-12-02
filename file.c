#include <stdio.h>
#include "file.h"
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;
    fp = fopen("contacts.csv", "w");
    int i=0;
    if (fp == NULL)
    {
        printf("File does not exit");
        return;
    }
    else
    {
        for ( i = 0; i < addressBook->contactCount; i++)
        {
            fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp;
        fp = fopen("contacts.csv", "r");
    int i=0;
    if (fp == NULL)
    {
        printf("File does not exit");
        return;
    }
    else
    {
        while (fscanf(fp, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email) != EOF)
        {

            i++;
        }
    }
    fclose(fp);
     addressBook->contactCount = i;
    
}
