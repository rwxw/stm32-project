#ifndef __DEQUE_H__
#define __DEQUE_H__

// 定义双端队列节点
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// 定义双端队列结构体
typedef struct Deque {
    Node* front;
    Node* rear;
} Deque;

Deque* createDeque(void);
void insertFront(Deque* deque, int value);
void insertRear(Deque* deque, int value);
int  deleteFront(Deque* deque);
int  deleteRear(Deque* deque);
void display(Deque* deque);

#endif
