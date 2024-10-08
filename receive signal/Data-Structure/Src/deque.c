#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

Deque* createDeque(void)
{
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->front = NULL;
    deque->rear = NULL;
    return deque;
}

void insertFront(Deque* deque, int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = deque->front;
    newNode->prev = NULL;

    if (deque->front == NULL) {
        deque->rear = newNode; // 如果队列为空，rear 指向新节点
    } else {
        deque->front->prev = newNode; // 更新旧队头的前指针
    }
    deque->front = newNode; // 更新队头指针
}

void insertRear(Deque* deque, int value) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = deque->rear;

    if (deque->rear == NULL) {
        deque->front = newNode; // 如果队列为空，front 指向新节点
    } else {
        deque->rear->next = newNode; // 更新旧队尾的后指针
    }
    deque->rear = newNode; // 更新队尾指针
}

int deleteFront(Deque* deque)
{
    if (deque->front == NULL) {
        printf("Deque is empty.\n");
        return -1; // 返回一个标志值，表示队列为空
    }

    Node* temp = deque->front;
    int value = temp->data;

    deque->front = deque->front->next; // 更新队头
    if (deque->front != NULL) {
        deque->front->prev = NULL; // 更新新的队头的前指针
    } else {
        deque->rear = NULL; // 如果队列变为空，rear 也置为 NULL
    }

    free(temp); // 释放旧节点
    return value;
}

int deleteRear(Deque* deque)
{
    if (deque->rear == NULL) {
        printf("Deque is empty.\n");
        return -1; // 返回一个标志值，表示队列为空
    }

    Node* temp = deque->rear;
    int value = temp->data;

    deque->rear = deque->rear->prev; // 更新队尾
    if (deque->rear != NULL) {
        deque->rear->next = NULL; // 更新新的队尾的后指针
    } else {
        deque->front = NULL; // 如果队列变为空，front 也置为 NULL
    }

    free(temp); // 释放旧节点
    return value;
}

void display(Deque* deque)
{
    Node* current = deque->front;
    if (current == NULL) {
        printf("Deque is empty.\n");
        return;
    }

    printf("Deque elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}


