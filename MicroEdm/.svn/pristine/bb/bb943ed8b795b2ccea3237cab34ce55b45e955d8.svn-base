/*此代码为实现循环队列的数据抽象*/
#include "queue.h"

int QueueInit(queueCDT *queue)
{
	queue->count = 0;
	queue->head = queue->tail = 0;
	return 0;
}

int EnQueue(queueCDT *queue,unsigned char element)
{
    if (QueueIsFull(queue))
    {
      return -1; 
    }
    queue->elements[queue->tail] = element;
    queue->tail = (queue->tail +1)% QUEUE_MAX_SIZE;
    queue->count++;
    return 0;
}

int DeQueue(queueCDT *queue,unsigned char *result)
{
  	//unsigned char result = 0;
	if (QueueIsEmpty(queue))
	{
	   return -1;
	}
	*result = queue->elements[queue->head];
	queue->head = (queue->head + 1) % QUEUE_MAX_SIZE;
	queue->count--;
	return 0;
}

int QueueIsEmpty(queueCDT *queue)
{
  return (queue->head == queue->tail && queue->count == 0);
}

int QueueIsFull(queueCDT *queue)
{
  return ((queue->tail + 1)% QUEUE_MAX_SIZE == queue->head && queue->count == QUEUE_MAX_SIZE);
}

int QueueLength(queueCDT  *queue)
{
  return (queue->count);
}
int ClearQueueBuffer(queueCDT  *queue)
{
   queue->count = 0;
   queue->tail = queue->head = 0;
   return 0;
}
