#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>

int isValidName(const char *name);
int isValidPhone(const char *phone, AddressBook *addressBook);
int isValidEmail(const char *email, AddressBook *addressBook);


void listContacts(AddressBook *addressBook)
{
    // check if any contact exist
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available.\n");
        return;
    }
    // Display sorted contacts
    printf("\nList of Contacts:\n");
    printf("-------------------------------------------------------------\n");
    printf("%-20s %-15s %-25s\n", "Name", "Phone", "Email");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-20s %-15s %-25s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

    }

    printf("-------------------------------------------------------------\n");

}

void initialize(AddressBook *addressBook)
 {
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    Contact newContact;

    do
    {
        printf("Enter name: ");
        scanf(" %[^\n]", newContact.name);
        if (!isValidName(newContact.name))
        {
            printf("Invalid name! Only letters and spaces allowed.\n");
        }
    } while (!isValidName(newContact.name));

    do
    {
        printf("Enter the phone number : ");
        scanf(" %[^\n]", newContact.phone);
        if (!isValidPhone(newContact.phone, addressBook))
        {
            printf("Invalid phone number! Must be 10 digits and unique.\n");
        }
    } while (!isValidPhone(newContact.phone, addressBook));

    do
    {
        printf("Enter the mail id : ");
        scanf(" %[^\n]", newContact.email);
        if (!isValidEmail(newContact.email, addressBook))
        {
            printf("Invalid email! Must contain '@gmail.com' and 'minimum two letters and one number' and be unique.\n");
        }
    } while (!isValidEmail(newContact.email, addressBook));

    // Save contact
    addressBook->contacts[addressBook->contactCount++] = newContact;
    printf("Contact added successfully! \nTotal number of contacts: %d\n", addressBook->contactCount);
}

void searchContact(AddressBook *addressBook)

    /* Define the logic for search */
    {
    int choice;
    char str[100];
    int found = 0;

    if (addressBook->contactCount == 0) {
        printf("No contacts available.\n");
        return;
    }

    do
    {
    printf("Select to search:\n");
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);
    }while(choice < 1 || choice > 3);

    if(choice==1)
    {
        char str[100];
        do
        {
	        printf("Enter name : ");
	        scanf(" %[^\n]",str);

            if (!isValidName(str))
            {
                printf("Invalid name! Only letters and spaces allowed.\n");
            }
        }while(!isValidName(str));

        printf("\n");

        printf("Matched Contacts: \n");

	    for(int i=0;i<addressBook->contactCount;i++)
	    {
	        if(strcmp(addressBook->contacts[i].name,str)==0)
	        {
	            printf("\nName: %s\nMObile No: %s\nMail id: %s\n",
         	        addressBook->contacts[i].name,
	                addressBook->contacts[i].phone,
	                addressBook->contacts[i].email);
	        }
	    }

    }

    else if(choice==2)
    {
        char str[100];

	    printf("Enter phone : ");
	    scanf(" %s",str);
        printf("\n");

        printf("Matched Contacts: \n");

	    for(int i=0;i<addressBook->contactCount;i++)
	    {
	        if(strcmp(addressBook->contacts[i].phone,str)==0)
	        {
	            printf("\nName: %s\nMobile No: %s\nMail id: %s\n",
         	    addressBook->contacts[i].name,
	            addressBook->contacts[i].phone,
	            addressBook->contacts[i].email);
	        }
	    }
    }

    else if(choice==3)
    {
        char str[30];
	    printf("Enter email : ");
	    scanf("%s",str);

	    for(int i=0;i<addressBook->contactCount;i++)
	    {
	        if(strcmp(addressBook->contacts[i].email,str)==0)
	        {

	            printf("Name: %s\nMObile No: %s\nMail id:%s\n",
        	    addressBook->contacts[i].name,
	            addressBook->contacts[i].phone,
	            addressBook->contacts[i].email);
	        }
	    }
    }

    else
    {
	    printf("invalid choice\n");
    }

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

    int choice;
    do
    {
        printf("\nEdit Contact by:\n1. Name\n2. phone\n3. Email\nEnter choice: ");
        scanf("%d", &choice);
    }while(choice < 1 || choice > 3);

    int matchingindex[50];
    int matchcount = 0 ;                // variable to count

    if(choice==1)
    {
        char name[30];
        printf("Enter the name: ");
        scanf(" %[^\n]", name);

        // operation for searching the name
        for(int i = 0;i < addressBook->contactCount;i++)
        {
            if(strstr(addressBook->contacts[i].name,name)!= NULL)
            {
                matchingindex[matchcount++]=i;
            }
        }

    }
    else if(choice==2)
    {
        char phone[10];
        printf("Enter the phone number: ");
        scanf(" %[^\n]", phone);
        for(int i = 0;i < addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].phone,phone) == 0)
            {
                matchingindex[matchcount++]=i;
            }
        }
    }

    else
    {
        char mail[50];
        printf("Enter the mail id : ");
        scanf(" %[^\n]", mail);
        for(int i = 0;i < addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].email,mail) == 0)
            {
                matchingindex[matchcount++]=i;
            }
        }

    }

    if(matchcount == 0)
    {
        printf("No Matching contact found\n");
        return;
    }

    printf("Matching C0ntacts\n");

    for(int i=0;i < matchcount;i++)
	{
        int idx = matchingindex[i];


	    printf("%d. Name: %s | MObile No: %s | EMail id: %s\n",i+1,
        addressBook->contacts[idx].name,
	    addressBook->contacts[idx].phone,
	    addressBook->contacts[idx].email);

	}


    int selectindex;

    do
    {
        printf("Enter the number of the contact you want to edit: ");
        scanf("%d", &selectindex);
    }while(selectindex < 1 || selectindex > matchcount);

    int index = matchingindex[selectindex - 1];

    int editfield;
    do
    {
        printf("Edit:\n1. Name\n2. phone\n3. Email\nEnter choice: ");
        scanf("%d", &editfield);
    }while(editfield < 1 || editfield > 3);

    if(editfield == 1)
    {
        char newname[30];
        printf("Enter newname : ");
        scanf(" %[^\n]", newname);

        if(isValidName(newname))
        {
             if(isValidName(newname))
             {
                strcpy(addressBook->contacts[index].name,newname);
                printf("Name updated successfully\n");
             }
             else
             {
                printf("Error! Invalid name\n");
             }
        }
    }

    else if(editfield == 2)
    {
        char newphone[30];
        do
        {
            printf("Enter newphone : ");
            scanf(" %[^\n]", newphone);
            if(!isValidPhone(newphone, addressBook))
            {
                printf("Error! Invalid phone number");
            }
        }while(!isValidPhone(newphone, addressBook));

        strcpy(addressBook->contacts[index].phone,newphone);
        printf("phone number updated successfully\n");

    }

    else
    {
         char newmail[30];
        do
        {
            printf("Enter newmail to edit: ");
            scanf(" %[^\n]", newmail);
            if(!isValidEmail(newmail, addressBook))
            {
                printf("Error! Invalid ");
            }
        }while(!isValidEmail(newmail, addressBook));

        strcpy(addressBook->contacts[index].email,newmail);
        printf("Email id updated successfully\n");
    }

}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

    int choice;
    do
    {
        printf("\nDelete Contact by:\n1. Name\n2. phone\n3. Email\nEnter choice: ");
        scanf("%d", &choice);
    }while(choice < 1 || choice > 3);

    int matchingindex[50];
    int matchcount = 0 ;                // variable to count

    if(choice==1)
    {
        char name[30];
        printf("Enter the name: ");
        scanf(" %[^\n]", name);

        // operation for searching the name
        for(int i = 0;i < addressBook->contactCount;i++)
        {
            if(strstr(addressBook->contacts[i].name,name)!= NULL)
            {
                matchingindex[matchcount++]=i;
            }
        }
        // if found store it in a variable

    }

    else if(choice==2)
    {
        char phone[10];
        printf("Enter the phone number: ");
        scanf(" %[^\n]", phone);
        for(int i = 0;i < addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].phone,phone) == 0)
            {
                matchingindex[matchcount++]=i;
            }
        }
    }
    else
    {
        char mail[50];
        printf("Enter the mail id : ");
        scanf(" %[^\n]", mail);
        for(int i = 0;i < addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].email,mail) == 0)
            {
                matchingindex[matchcount++]=i;
            }
        }

    }

    if(matchcount == 0)
    {
        printf("No Matching contact found\n");
        return;
    }

    printf("Matching C0ntacts\n");

    for(int i=0;i < matchcount;i++)
	{
        int idx = matchingindex[i];


	          printf("%d. Name: %s | MObile No: %s | EMail id: %s\n",i+1,
        	  addressBook->contacts[idx].name,
	          addressBook->contacts[idx].phone,
	          addressBook->contacts[idx].email);

	}


    int selectindex;

    do
    {
        printf("Enter the number of the contact you want to delete: ");
        scanf("%d", &selectindex);
    }while(selectindex < 1 || selectindex > matchcount);

    int index = matchingindex[selectindex - 1];

    for(int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Deleted Succussfully!");

}

// Validation functions
int isValidName(const char *name)
{
    for (int i = 0; i < strlen(name); i++)
    {
        if(!isalpha(name[i]) && name[i] != ' ')
            return 0;
    }
    return 1;
}

int isValidPhone(const char *phone, AddressBook *addressBook)
{
    if (strlen(phone) != 10)
    return 0;

    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(phone[i]))
        return 0;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
            return 0;
    }
    return 1;
}

int isValidEmail(const char *email, AddressBook *addressBook)
{
	int j=0,k=0;
    if (!strstr(email,"@gmail.com"))
    {
	j=1;
    }
     for (int i = 0; i<=2; i++)
    {
        if (!isdigit(email[i])&&!isalpha(email[i]))
	{
		k++;
		return 0;
	}
    }
     if(j==1&&k>=1)
     {
	     return 0;
     }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
            return 0;
    }
    return 1;
}
