struct Message
{
    char *topic;
    char *payload;
};

struct MessageNode
{
    Message *message;
    MessageNode *next;
};

struct MessageQueue
{
    MessageNode *start;
    MessageNode *end;
};

void freeMessage(Message *);

MessageQueue *messageQueueInitialize();
void messageQueuePush(MessageQueue *queue, Message *message);
Message *messageQueueShift(MessageQueue *queue);