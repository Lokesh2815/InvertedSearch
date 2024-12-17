#ifndef INVERTED_H
#define INVERTED_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define FAILURE -1
#define EMPTYLIST -2
#define FILE_EMPTY -3
#define DUPLICATE -4

typedef struct main
{
    int filecount;
    char word[20];
    struct main *mlink;
    struct sub *sub_link;
}main_node;

typedef struct sub
{
    int wordcount;
    char filename[20];
    struct sub * sub_link1;
}sub_node;

typedef struct file
{
    char file[20];
    struct file * link;
}file_t;

int validate(file_t **, char* []);
int display(file_t* head,main_node *arr[]);
int create_DB(file_t *, main_node **);
void search(char *word, main_node *arr[]);
int save(main_node **arr);
int update(file_t**, main_node**, char*);

#endif