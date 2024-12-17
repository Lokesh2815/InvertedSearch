#include "inverted.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 100
#define KEYWORD_SIZE 30
#define FILE_NAME_SIZE 30

int update(file_t** head, main_node** arr, char* fname) 
{
    int index;
    FILE *fptr = fopen(fname, "r");
    if (fptr == NULL) 
    {
        printf("The file doesn't exist\n");
        return FAILURE;
    }

    fseek(fptr, 0L, SEEK_END);
    int off = ftell(fptr);
    if (off == 0) {
        printf("Given database is empty\n");
        fclose(fptr);
        return FAILURE;
    }
    
    rewind(fptr);
    char word[WORD_SIZE];
    
    while (fscanf(fptr, "%s", word) != EOF)
    {
        int length = strlen(word);
        if (word[0] != '#' && word[length - 1] != '#')
        {
            printf("Error: This is not a backup file.\n");
            fclose(fptr);
            return FAILURE;
        }
        char* token = strtok(word, "#;");
        if (token == NULL) 
            continue;
        
        index = atoi(token);
        char keyword[KEYWORD_SIZE];
        
        token = strtok(NULL, ";");
        if (token == NULL)
            continue;
        strcpy(keyword, token);
        
        token = strtok(NULL, ";");
        if (token == NULL)
            continue;
        int filecount = atoi(token);
        
        for (int i = 0; i < filecount; i++) 
        {
            token = strtok(NULL, ";");
            if (token == NULL) 
                break;
            char file_name[FILE_NAME_SIZE];
            strcpy(file_name, token);
            
            token = strtok(NULL, ";#");
            if (token == NULL) 
                continue;
            int wordcount = atoi(token);                 

            // Process the main node and sub nodes
            if (arr[index] == NULL) 
            {
                // Create a new main node
                main_node* new_node = malloc(sizeof(main_node));
                if (new_node == NULL) {
                    fclose(fptr);
                    return FAILURE;
                }
                new_node->filecount = 1;
                strcpy(new_node->word, keyword);
                new_node->mlink = NULL;
                
                // Create a new sub node
                new_node->sub_link = malloc(sizeof(sub_node));
                if (new_node->sub_link == NULL) {
                    free(new_node);
                    fclose(fptr);
                    return FAILURE;
                }
                new_node->sub_link->wordcount = wordcount;
                strcpy(new_node->sub_link->filename, file_name);
                new_node->sub_link->sub_link1 = NULL;
                arr[index] = new_node;
            } 
            else 
            {
                main_node* temp = arr[index];
                while (temp != NULL)
                {
                    if (strcmp(keyword, temp->word) == 0) 
                    {
                        // Keyword already exists, update or add the sub node
                        sub_node* temp_sub = temp->sub_link;
                        while (temp_sub != NULL) 
                        {
                            if (strcmp(temp_sub->filename, file_name) == 0) 
                            {
                                temp_sub->wordcount += wordcount;
                                break;
                            }
                            temp_sub = temp_sub->sub_link1;
                        }
                        if (temp_sub == NULL) 
                        {
                            // Add new sub node
                            sub_node* new_sub = malloc(sizeof(sub_node));
                            if (new_sub == NULL) {
                                fclose(fptr);
                                return FAILURE;
                            }
                            new_sub->wordcount = wordcount;
                            strcpy(new_sub->filename, file_name);
                            new_sub->sub_link1 = temp->sub_link;
                            temp->sub_link = new_sub;
                            temp->filecount++;
                        }
                        break;
                    }
                    else if (temp->mlink == NULL)
                    {
                        // Create a new main node and link it
                        main_node* new_node = malloc(sizeof(main_node));
                        if (new_node == NULL) {
                            fclose(fptr);
                            return FAILURE;
                        }
                        new_node->filecount = 1;
                        strcpy(new_node->word, keyword);
                        new_node->mlink = NULL;
                        
                        // Create a new sub node
                        new_node->sub_link = malloc(sizeof(sub_node));
                        if (new_node->sub_link == NULL) {
                            free(new_node);
                            fclose(fptr);
                            return FAILURE;
                        }
                        new_node->sub_link->wordcount = wordcount;
                        strcpy(new_node->sub_link->filename, file_name);
                        new_node->sub_link->sub_link1 = NULL;
                        temp->mlink = new_node;
                        break;
                    }
                    temp = temp->mlink;
                }
            }

            // Update the head list based on the presence of file_name
            file_t* current = *head;
            file_t* prev = NULL;
            int found = 0;
            
            while (current != NULL) 
            {
                if (strcmp(current->file, file_name) == 0) 
                {
                    found = 1;
                    break;
                }
                prev = current;
                current = current->link;
            }

            if (found) 
            {
                if (prev == NULL) 
                {
                    *head = current->link;
                } 
                else 
                {
                    prev->link = current->link;
                }
                free(current);
            }
            else 
            {
                file_t* new_file = malloc(sizeof(file_t));
                if (new_file == NULL) 
                {
                    fclose(fptr);
                    return FAILURE;
                }
                strcpy(new_file->file, file_name);
                new_file->link = *head;
                *head = new_file;
            }
        }
    }

    fclose(fptr);
    return SUCCESS;
}
