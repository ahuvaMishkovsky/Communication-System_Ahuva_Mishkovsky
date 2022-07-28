#ifndef IDD_H
#define IDD_H
//For Data messages
#define DATA_MSG_OPCODE 0xD001 

//For Control Messages
#define MANAGER_TO_AMPLIFIER_CONTROL_MSG_OPCODE  0xA002
#define AMPLIFIER_TO_MANAGER_CONTROL_MSG_OPCODE  0xA003


#define MANAGER_TO_MODEM_CONTROL_MSG_OPCODE 0xA004
#define MODEM_TO_MANAGER_CONTROL_MSG_OPCODE 0xA005

#define MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE 0xA006
#define ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE 0xA007
#define MSG_SYNC 0xAA55

typedef struct {
    unsigned short msgSync;
    unsigned short Opcode;
    unsigned int msgCounter;
} Header;

typedef struct {
    Header header;
    char Ack;
}ControlMessage;

typedef struct {
    Header header;
}DataMessage;

typedef union {
    Header header;
    ControlMessage controlMessage;
    DataMessage dataMessage;
}Message;

typedef struct {
    int toOpCode;
    int fromOpCode;
    int port;
    /*int counter = 0;*/
}Controller_type;



//For Data messages
#define DATA_MSG_OPCODE 0xD001 

//For Control Messages
#define MANAGER_TO_AMPLIFIER_CONTROL_MSG_OPCODE  0xA002
#define AMPLIFIER_TO_MANAGER_CONTROL_MSG_OPCODE  0xA003


#define MANAGER_TO_MODEM_CONTROL_MSG_OPCODE 0xA004
#define MODEM_TO_MANAGER_CONTROL_MSG_OPCODE 0xA005

#define MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE 0xA006
#define ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE 0xA007
#define MSG_SYNC 0xAA55

//Ports
#define MANAGER_TRANSMITTER_PORT 8000
#define ANTENNA_TRANSMITTER_PORT 8001
#define AMPLIFIER_TRANSMITTER_PORT 8002
#define MODEM_TRANSMITTER_PORT 8003

#define MANAGER_RECIEVER_PORT 8004
#define ANTENNA_RECIEVER_PORT 8005
#define MODEM_RECIEVER_PORT 8006
#define MESSAGE_GENERATOR_PORT 8007

//Codes
#define TRANSMITTER 1
#define RECIEVER 2

#endif // !IDD_H