#include <Arduino.h>
#include <communication.h>

void freeMessage(Message *message)
{
    free(message->payload);
    free(message->topic);
    free(message);
}

MessageQueue *messageQueueInitialize()
{
    MessageQueue *queue = (MessageQueue *)malloc(sizeof(MessageQueue));
    queue->start = NULL;
    queue->end = NULL;
    return queue;
}

void messageQueuePush(MessageQueue *queue, Message *message)
{
    MessageNode *node = (MessageNode *)malloc(sizeof(MessageNode));
    node->next = NULL;

    node->message = message;

    if (queue->start == NULL)
    {
        queue->start = node;
    }

    if (queue->end == NULL)
    {
        queue->end = node;
    }
    else
    {
        queue->end->next = node;
        queue->end = node;
    }
}

Message *messageQueueShift(MessageQueue *queue)
{
    if (queue->start == NULL)
    {
        return NULL;
    }

    MessageNode *nextNode = queue->start;
    Message *nextMessage = nextNode->message;

    if (nextNode->next == NULL)
    {
        queue->start = NULL;
        queue->end = NULL;
    }
    else
    {
        queue->start = nextNode->next;
    }

    free(nextNode);

    return nextMessage;
}