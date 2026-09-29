#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("file.csv","w");  //opening new file to save contacts

    if(fptr == NULL)
    {
        perror("");
        return;
    }

    fprintf(fptr,"#%d#\n",addressBook->contactCount);

    for(int i=0;i<addressBook->contactCount;i++) //saving all contacts to file pointer
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("file.csv", "r");
    if (fptr == NULL)
    {
        perror("");
        return;
    }
    addressBook->contactCount = 0;

    if (fscanf(fptr, " #%d#\n", &addressBook->contactCount) != 1)
    {
        addressBook->contactCount = 0;
        fclose(fptr);
        return;
    }

    for (int i=0; i<addressBook->contactCount; i++)
    {
        if (fscanf(fptr, " %[^,], %[^,], %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email) != 3)
        {
            addressBook->contactCount = i;           //adjust actual count
            break;
        }
    }
    fclose(fptr);
}
