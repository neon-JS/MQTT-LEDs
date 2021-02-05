#include <communication.h>

#define SERIAL_BUFFER_LENGTH 64

#define PROTOCOL_SPLIT_CHAR ";"
#define PROTOCOL_TERMINATING_CHAR '\n'

void initializeSerialBuffer();