#include "inverted.h"
int validate(file_t** head, char* filename[]) 
{
    int i = 1;
    while (filename[i] != NULL) 
    {
        char *ext;
        if (ext=strstr(filename[i], ".txt")) 
        {
            if(*(ext+4)=='\0')
            {
                printf("File is .txt file\n");
            }
            else
            {
                printf("ERROR: The file %s is not a .txt file\n", filename[i]);
            }
            FILE* fptr = fopen(filename[i], "r");
            if (fptr == NULL) 
            {
                printf("ERROR: The file %s is not present.\n INFO: So, this file cannot be added into database.\n", filename[i]);
                
            } 
            else
            {
                fseek(fptr, 0L, SEEK_END);
                int pos = ftell(fptr);

                if (pos == 0) 
                {
                    printf("ERROR: The file %s is an empty file\n", filename[i]);
                    fclose(fptr);
                } 
                else 
                {
                    fclose(fptr);
                    file_t* temp = *head;
                    int is_duplicate = 0;
                    while (temp != NULL) 
                    {
                        if (strcmp(filename[i], temp->file) == 0) 
                        {
                            printf("ERROR: The file %s is a duplicate file\n", filename[i]);
                            is_duplicate = 1;
                            break;
                        }
                        temp = temp->link;
                    }
                    if (!is_duplicate) 
                    {
                        file_t* new = malloc(sizeof(file_t));
                        if (new == NULL) 
                        {
                            return FAILURE;
                        }
                        
                        strcpy(new->file, filename[i]);
                        new->link = NULL;

                        if (*head == NULL) 
                        {
                            *head = new;
                        } 
                        else 
                        {
                            file_t* temp = *head;
                            while (temp->link != NULL) 
                            {
                                temp = temp->link;
                            }
                            temp->link = new;
                        }
                    }
                }
            }
        } 
        else 
        {
            printf("ERROR: The file %s is not a .txt file\n", filename[i]);
        }
        i++;
    }
    return SUCCESS;
}
