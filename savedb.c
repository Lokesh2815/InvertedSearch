#include "inverted.h"
#include "inverted.h"
int save(main_node *arr[])
{
    int i=0;
    char word[20];
    printf("Enter a file name to save the database (with .txt extension)\n");
    scanf("%s",word);
    if(strstr(word, ".txt") != NULL)
    {
        FILE* fptr = fopen(word,"w");
        if(fptr == NULL)
        {
            printf("ERROR: The file cannot open %s.\n", word);
            return FAILURE;
        }
        else
        {
            while(i<28)
            {
                if (arr[i] != NULL) 
                {
                    main_node *temp = arr[i];
                    fprintf(fptr, "#%d;%s;%d;", i, temp->word, temp->filecount);
                    sub_node *sub_temp = temp->sub_link;
                    while (sub_temp != NULL) 
                    {
                        fprintf(fptr, "%s;%d;", sub_temp->filename, sub_temp->wordcount);
                        sub_temp = sub_temp->sub_link1;
                    }
                    fprintf(fptr, "#\n");
                    main_node *mlink_temp = temp->mlink;
                    while (mlink_temp != NULL) 
                    {
                        fprintf(fptr, "#%d;%s;%d;",i, mlink_temp->word, mlink_temp->filecount);
                        sub_node *sub_mlink_temp = mlink_temp->sub_link;
                        while (sub_mlink_temp != NULL) 
                        {
                            fprintf(fptr, "%s;%d;", sub_mlink_temp->filename, sub_mlink_temp->wordcount);
                            sub_mlink_temp = sub_mlink_temp->sub_link1;
                        }
                        fprintf(fptr, "#\n");
                        mlink_temp = mlink_temp->mlink;
                    }                
                }
                i++;
            }
            fclose(fptr);
            return SUCCESS;
        }
    }
    else
    {
        printf("Entered File is not a valid .txt file\n");
        return FAILURE;
    }
}