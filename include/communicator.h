struct Message
{
    char *topic;
    char *payload;
};

struct MessageNode
{
    Message *message;
    MessageNode *next;
    MessageNode *previous;
};

struct MessageQueue
{
    MessageNode *start;
    MessageNode *end;
};

void communicationLoop();
void communicationInitialize();
Message *communicationGetNextMessage();

void freeMessage(Message *);

MessageQueue *messageQueueInitialize();
void messageQueuePush(MessageQueue *queue, Message *message);
Message *messageQueueShift(MessageQueue *queue);