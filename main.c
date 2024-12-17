#include "inverted.h"
#include<stdio.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("ERROR: Invalid number of arguments\n");
        printf("INFO: Usage ./inverted_index <file.txt> <file1.txt> ...\n");
        return FAILURE;
    }
    
    file_t *head = NULL;
    main_node *arr[28] = {NULL};
    int option, ret, res, flag = 0, flag1 = 0;
    char choice;
    
    // Validate the input files and build the linked list 'head'
    int result = validate(&head, argv);
    if (result != SUCCESS)
    {
        printf("ERROR: Validation of files failed\n");
        return FAILURE;
    }
    printf("INFO: Validation of files successful\n");

    while (1)
    {
        printf("-----------------------------------------\n");
        printf("Select your choice among following options :\n");
        printf(" 1. Create DATABASE\n 2. Display Database\n 3. Update Database\n 4. Search\n 5. Save Database\n 6. Exit\n");
        printf("Enter your Choice\n");
        if (scanf("%d", &option) != 1) 
        {
            printf("ERROR: Invalid input. Please enter a number between 1 to 6.\n");
            // Clear the input buffer
            while (getchar() != '\n');
            continue;
        }
        
        switch (option)
        {
            case 1:
                if (flag == 0)
                {
                    ret = create_DB(head, arr);
                    if (ret == SUCCESS)
                    {
                        printf("INFO: Database Creation Successful.\n");
                        flag = 1;
                    }
                    else
                    {
                        printf("ERROR: Database Creation Failed.\n");
                    }
                }
                else
                {
                    printf("ERROR: Create Database operation already done\n");
                }
                break;
                
            case 2:
                if (flag == 1 || flag1 == 1)
                {
                    int re = display(head, arr);
                    if (re == SUCCESS)
                    {
                        printf("Display Database done\n");
                    }
                    else
                    {
                        printf("ERROR: Failed to display database\n");
                    }
                }
                else
                {
                    printf("ERROR: Cannot display the database. Database has not been created or updated.\n");
                }
                break;
                
            case 3:
                if (flag == 0 && flag1 == 0)
                {
                    char fname[20];
                    printf("Enter the File Name to be Updated in the Database: \n");
                    scanf("%s", fname);
                    res = update(&head, arr, fname);
                    if (res == SUCCESS)
                    {
                        flag1 = 1;
                        printf("INFO: The database is updated successfully\n");
                    }
                    else
                    {
                        flag1 = 0;
                        printf("ERROR: Database is not updated.\n");
                    }
                }
                else
                {
                    printf("ERROR: Cannot update database after it's been created or updated.\n");
                }
                break;
                
            case 4:
                {
                    char word[10];
                    printf("Enter the word to Search\n");
                    scanf("%s", word);
                    search(word, arr);
                }
                break;
                
            case 5:
                {
                    int resu;
                    if(flag == 1 || flag1 == 1)
                    {
                        resu = save(arr);
                        if (resu == SUCCESS)
                        {
                            printf("INFO: Save database is successful\n");
                        }
                        else
                        {
                            printf("ERROR: Save database not completed\n");
                        }
                    }
                    else
                    {
                        printf("Cannot save database without creating or updating\n");
                    }
                    
                }
                break;
                
            case 6:
                printf("Exit\n");
                return SUCCESS;
                
            default:
                printf("ERROR: Invalid Choice. Please enter a number between 1 to 6\n");
                break;
        }
    }
}
