#include "inverted.h"

int create_DB(file_t *head, main_node **arr) 
{
    char word[50];
    int index;
    file_t *temp_head = head; 
    
    while (temp_head != NULL) 
    {
        FILE* fptr = fopen(temp_head->file, "r");
        if (fptr == NULL) 
        {
            printf("ERROR: Could not open file %s\n", temp_head->file);
            return FAILURE;
        }

        // Read each word from the file
        while (fscanf(fptr, "%s", word) != EOF) 
        {
            // Calculate the index for the array
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

            // Check if there's already a main_node at this index
            main_node *temp = arr[index];
            main_node *prev_main = NULL;
            int found_main_node = 0;

            while (temp != NULL)
            {
                if (strcmp(temp->word, word) == 0) 
                {
                    // The word exists, update or add the sub_node
                    sub_node *temp_sub = temp->sub_link;
                    sub_node *prev_sub = NULL;
                    int found_sub_node = 0;

                    while (temp_sub != NULL) 
                    {
                        if (strcmp(temp_sub->filename, temp_head->file) == 0) 
                        {
                            temp_sub->wordcount++; // Increment word count
                            found_sub_node = 1;
                            break;
                        }
                        prev_sub = temp_sub;
                        temp_sub = temp_sub->sub_link1;
                    }

                    if (!found_sub_node) 
                    {
                        // File name not found in sub_node, create a new sub_node
                        sub_node* new_sub = malloc(sizeof(sub_node));
                        if (new_sub == NULL) 
                        {
                            fclose(fptr);
                            return FAILURE;
                        }
                        new_sub->wordcount = 1;
                        strcpy(new_sub->filename, temp_head->file);
                        new_sub->sub_link1 = NULL;

                        // Append new_sub at the end of the sub_link list
                        if (prev_sub != NULL)
                        {
                            prev_sub->sub_link1 = new_sub;
                        }
                        else
                        {
                            temp->sub_link = new_sub;
                        }
                        temp->filecount++;
                    }

                    found_main_node = 1;
                    break;
                }
                
                prev_main = temp;
                temp = temp->mlink;
            }

            if (!found_main_node) 
            {
                // Create a new main_node
                main_node *new_main = malloc(sizeof(main_node));
                if (new_main == NULL) 
                {
                    fclose(fptr);
                    return FAILURE;
                }

                strcpy(new_main->word, word);
                new_main->filecount = 1;
                new_main->mlink = NULL;

                // Create the first sub_node
                sub_node *new_sub = malloc(sizeof(sub_node));
                if (new_sub == NULL) 
                {
                    free(new_main);
                    fclose(fptr);
                    return FAILURE;
                }

                new_sub->wordcount = 1;
                strcpy(new_sub->filename, temp_head->file);
                new_sub->sub_link1 = NULL;

                // Link the new main_node with its sub_node
                new_main->sub_link = new_sub;

                // Insert the new_main node in the array or list
                if (prev_main == NULL) 
                {
                    arr[index] = new_main;
                }
                else 
                {
                    prev_main->mlink = new_main;
                }
            }
        }

        fclose(fptr);
        temp_head = temp_head->link; // Move to the next file_t node
    }

    return SUCCESS;
}
