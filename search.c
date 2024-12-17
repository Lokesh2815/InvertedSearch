#include "inverted.h"
void search(char *word, main_node *arr[]) {
    int index, found = 0;
    if (word[0] >= 'a' && word[0] <= 'z') 
    {
        index = word[0] - 'a';
    } 
    else if (word[0] >= 'A' && word[0] <= 'Z') 
    {
        index = word[0] - 'A';
    } 
    else if (word[0] >= '0' && word[0] <= '9') 
    {
        index = 26;
    } 
    else 
    {
        index = 27;
    }
    
    if (arr[index] != NULL) 
    {
        main_node *temp = arr[index];
        while (temp != NULL) 
        {
            if (strcmp(temp->word, word) == 0) 
            {
                // word found
                printf("%s",word);
                printf(" Found at %d ",index);
                printf(" In %d Files\n",temp->filecount);
                sub_node *sub_temp = temp->sub_link;
                while (sub_temp != NULL) 
                {
                    printf("%s ", sub_temp->filename);
                    sub_temp = sub_temp->sub_link1; 
                    printf("; %d\n",temp->sub_link->wordcount);
                }
                
                found = 1;
            }
            temp = temp->mlink;
        }
    }

    if (!found) 
    {
        printf("Word not found.\n");
    }
}