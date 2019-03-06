#ifndef _QUEUE_H
#define _QUEUE_H

#define QUEUE_MAX_SIZE 512
/*队列结构体*/
typedef struct queueCDT
{
	unsigned char elements[QUEUE_MAX_SIZE];
	int head;
	int tail;
	int count;
}queueCDT;

//typedef queueCDT * ptrQueueCDT;
int QueueInit(queueCDT *queue);
int EnQueue(queueCDT *queue,unsigned char element);
int DeQueue(queueCDT *queue,unsigned char *result);
int QueueIsEmpty(queueCDT *queue);
int QueueIsFull(queueCDT *queue);
int QueueLength(queueCDT  *queue);
int ClearQueueBuffer(queueCDT *queue);


#endif 
