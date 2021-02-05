#include <main.h>

#if USE_SERIAL == true
#include <Arduino.h>
#include <serial.h>

enum SerialBufferStatus
{
    SERIAL_BUFFER_STATUS_OK,
    SERIAL_BUFFER_STATUS_DONE,
    SERIAL_BUFFER_STATUS_OVERFLOW
};

SerialBufferStatus readIntoBuffer();
void handleSerialError();

char serialBuffer[SERIAL_BUFFER_LENGTH];
int serialBufferIndex;
MessageQueue *messageQueue;

void communicationLoop()
{
    switch (readIntoBuffer())
    {
    case SERIAL_BUFFER_STATUS_OVERFLOW:
        handleSerialError();
        return;
    case SERIAL_BUFFER_STATUS_OK:
        return;
    case SERIAL_BUFFER_STATUS_DONE:
        break;
    }

    if (serialBufferIndex == 0)
    {
        return;
    }

    char const *protocolSplitChar = PROTOCOL_SPLIT_CHAR;
    char *separatorPos = strstr(serialBuffer, protocolSplitChar);
    int separator = (separatorPos != NULL) ? separatorPos - serialBuffer : 0;

    if (separator <= 0)
    {
        handleSerialError();
        return;
    }

    char *topic = (char *)malloc(sizeof(char) * (separator + 1));
    char *payload = (char *)malloc(sizeof(char) * (serialBufferIndex - separator));

    strncpy(topic, serialBuffer, separator);
    topic[separator] = '\0';

    strncpy(payload, serialBuffer + separator + 1, serialBufferIndex - separator - 2);
    payload[serialBufferIndex - separator - 2] = '\0';

    Message *nextMessage = (Message *)malloc(sizeof(Message));
    nextMessage->topic = topic;
    nextMessage->payload = payload;

    messageQueuePush(messageQueue, nextMessage);
    initializeSerialBuffer();
}

void communicationInitialize()
{
    Serial.begin(SERIAL_BAUD_RATE);
    while (!Serial)
    {
    }
    initializeSerialBuffer();
    messageQueue = messageQueueInitialize();
}

void initializeSerialBuffer()
{
    serialBufferIndex = 0;

    for (int i = 0; i < SERIAL_BUFFER_LENGTH; i++)
    {
        serialBuffer[i] = (char)0;
    }
}

Message *communicationGetNextMessage()
{
    return messageQueueShift(messageQueue);
}

SerialBufferStatus readIntoBuffer()
{
    if (!Serial.available())
    {
        return SERIAL_BUFFER_STATUS_OK;
    }

    if (serialBufferIndex >= SERIAL_BUFFER_LENGTH)
    {
        return SERIAL_BUFFER_STATUS_OVERFLOW;
    }

    if (((char)Serial.peek()) == PROTOCOL_TERMINATING_CHAR) {
        Serial.read();
        serialBuffer[serialBufferIndex] = '\0';
        serialBufferIndex += 1;
        return SERIAL_BUFFER_STATUS_DONE;
    }

    serialBuffer[serialBufferIndex] = Serial.read();
    serialBufferIndex += 1;

    return SERIAL_BUFFER_STATUS_OK;
}

void handleSerialError()
{
    Serial.write("DEBUG: Error while reading / parsing data! Clearing buffers! Buffer:\n");
    Serial.write(serialBuffer);
    Serial.write("\n");
    Serial.flush();

    initializeSerialBuffer();
    while (Serial.available())
    {
        // Clear remaining incoming data as it will most likely be corrupted!
        Serial.read();
    }
}

#endif