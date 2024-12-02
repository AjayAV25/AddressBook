#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
//Creating a contact structure
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

//Creating array of contacts structure
typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

//Function declaration for creating contact
void createContact(AddressBook *addressBook);

//Function decclaration for searching the contact
void searchContact(AddressBook *addressBook);

//Function decclaration for edit the contact
void editContact(AddressBook *addressBook);

//Function decclaration for delete the contact
void deleteContact(AddressBook *addressBook);

//Function decclaration for list all the contacts
void listContacts(AddressBook *addressBook);

//Function decclaration for initialize the contacts to the structure
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void loadContactsFromFile(AddressBook *AddressBook);

#endif
