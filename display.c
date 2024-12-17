#include "inverted.h"

int display(file_t* head, main_node *arr[]) {
    // Print the table header
    printf("%-5s %-15s %-10s %-15s %s\n", "Index", "Word", "FileCount", "Filename", "WordCount");
    printf("---------------------------------------------------------------\n");

    int i = 0;
    while (i < 28) {
        if (arr[i] != NULL) {
            main_node *temp = arr[i];

            // Print the details of the main node
            printf("%-5d %-15s %-10d", i, temp->word, temp->filecount);

            sub_node *sub_temp = temp->sub_link;
            if (sub_temp != NULL) {
                // Print the first sub_node details in the same line
                printf(" %-15s %d", sub_temp->filename, sub_temp->wordcount);
                sub_temp = sub_temp->sub_link1;
            }
            printf("\n");

            // Print remaining sub_nodes, if any
            while (sub_temp != NULL) {
                printf("%-32s %-15s %d\n", "", sub_temp->filename, sub_temp->wordcount);
                sub_temp = sub_temp->sub_link1;
            }

            main_node *mlink_temp = temp->mlink;

            // Traverse and print linked main nodes
            while (mlink_temp != NULL) {
                printf("%-5s %-15s %-10d", "", mlink_temp->word, mlink_temp->filecount);

                sub_node *sub_mlink_temp = mlink_temp->sub_link;
                if (sub_mlink_temp != NULL) {
                    printf(" %-15s %d", sub_mlink_temp->filename, sub_mlink_temp->wordcount);
                    sub_mlink_temp = sub_mlink_temp->sub_link1;
                }
                printf("\n");

                // Print remaining sub_nodes for this main node
                while (sub_mlink_temp != NULL) {
                    printf("%-32s %-15s %d\n", "", sub_mlink_temp->filename, sub_mlink_temp->wordcount);
                    sub_mlink_temp = sub_mlink_temp->sub_link1;
                }
                mlink_temp = mlink_temp->mlink;
            }
        }
        i++;
    }
    printf("---------------------------------------------------------------\n");
    return SUCCESS;
}
