#include <stdio.h>

typedef struct Node{

    int data;
    struct Node* link;
    
} Node;

// 1) Insert (begin & end) -> 2) Deletion (Begin & End) -> 3) Display/Traverse -> 4) Search

// Insert at Beginning 

void insertAtBeginning(Node** head, int value){

    Node* newNode = malloc(sizeof(Node));
    newNode -> data = value;

    //single node circle
    if(*head == NULL){

        newNode -> link = newNode; 
        *head = newNode;
        return;
    }

    Node* temp = *head;

    // move to the last node

    while(temp -> link != *head){

        temp = temp -> link;

    }

    newNode -> link = *head;
    temp -> link = newNode;
    *head = newNode;
}

void insertAtBeginning(Node** head, int value){

    Node* newNode = malloc(sizeof(Node));
    newNode -> data = value;

    if(*head == NULL){

        newNode -> link = newNode;
        *head = newNode;
        return;

    }

    Node* temp = *head;

    while(temp -> link != *head){

        temp = temp -> link;
    }

    newNode -> link = *head;
    temp -> link = newNode;
    *head = newNode;
}

void insertAtEnd(Node** head, int value){

    Node* newNode = malloc(sizeof(Node));
    newNode -> data = value;

    if(*head == NULL){

        newNode -> link = *head;
        *head = newNode;
        return;
    }

    Node* temp = *head;

    while(temp -> link != *head){

        temp = temp -> link;
    }

    temp -> link = newNode;
    newNode -> link = *head;
}

void insertAtEnd(Node** head, int value){

    Node* newNode = malloc(sizeof(Node));
    newNode -> data = value;

    if(*head == NULL){

        newNode -> link = *head;
        *head = newNode;
        return;

    }

    Node* temp = *head;

    while(temp -> link != *head){

        temp = temp -> link;

    }

    temp -> link = newNode;
    newNode -> link = *head;

}

void deleteBeginning(Node** head){

    if(*head == NULL) return;

    Node* temp = head; 

    if(temp -> link == *head){

        free(temp);
        *head = NULL;
        return;
        
    }

    Node* last = *head;

    while(last -> link != *head){

        last = last -> link;

    }

    last -> link = temp -> link;
    *head = temp -> link;

    free(temp);
}

void deleteBeginning(Node** head){

    Node* temp = *head; 

    if(temp -> link == *head){

        free(temp);
        *head = NULL;
        return;

    }

    Node* last = *head;

    while(last -> link != *head){

        last = last -> link;
    }

    last -> link = temp -> link;
    *head = temp -> link;

    free(temp);

}

void deleteBeginning(Node** head){

    Node* temp = *head;

    if(temp -> link == *head){

        free(temp);
        *head = NULL;
        return;

    }

    Node* last = *head;

    while(last -> link != *head){

        last = last -> link;

    }

    last -> link = temp -> link;
    *head = temp -> link;

    free(temp);

}

void deleteEnd(Node** head){

    if(*head == NULL) return;

    Node* temp = *head;

    if(temp -> link == *head){

        free(temp);
        *head = NULL;
        return;
    }

    Node* prev = NULL;

    while(temp -> link != *head){

        prev = temp;
        temp = temp -> link;
    }

    prev -> link = *head;
    free(temp);

}

void deleteEnd(Node** head){

    if(*head == NULL) return;

    Node* temp = *head;

    if(temp -> link == *head){

        free(temp);
        *head = NULL;
        return;

    }

    Node* prev = NULL;

    while(temp -> link != *head){

        prev = temp;
        temp = temp -> link;

    }

    prev -> link = *head;
    free(temp);
    
}

void displayList(Node* head){

    Node* temp = head;

    while(temp != head){

        printf("%d -> ", temp -> data);
        temp = temp -> link;

    }

    printf("(head)\n");
    
}

void searchElement(Node* head, int key){

    Node* temp = head;

    int position = 0;

    while(temp != head){

        if(temp -> data == key){

            printf("Element %d found at position %d \n", key, position);
            return;
        }
        
        temp = temp -> link;
        position++;
    }

    printf("Element not found.");
    
}

