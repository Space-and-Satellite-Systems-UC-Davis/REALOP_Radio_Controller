//This file was written in cpp before ??

#include "Intercomm.h"
#include "radio.h"

typedef enum State {
    Idle = 'o',
    TransferToRadio = 'T',
    TransferToGroundStation = 't',
	RXactive = 'r',
	Acknowledge = 'A',
};

State current_state = Idle;

void handleIdle(char input) {
    // Transition based on input
    switch (input) {
        case TransferToGroundStation: // Transfer to Ground Station
        case TransferToRadio: // Transfer to Radio
            currentState = input;
            break;
        case RXactive: // Get Radio State
            received_State_of_Radio_Request();
            break;
        default:
        	//UNKNOWN INPUT, SHOULD HAVE A WARNING
            break;
    }
}

void handleTransferToRadio(){
    current_state = TransferToRadio;
    int* receivedBytes = transferToRadioRequest();
    current_state = Idle;
    if (receivedBytes) { 
        free(receivedBytes);
    }
}

void handlereceived_Transfer_GroundStation_Request(){
    current_state = TransferToGroundStation;
    received_Transfer_GroundStation_Request();
    current_state = Idle;
}

// received Request for PFC to send data to Radio MCU
int* transferToRadioRequest(){
    int arr[1];
    int numberOfBytesToReceive[1];
    int size = 0;
    int count = 0;

    // Receives T.
    // while (size != 1) {
    // size = usart_receiveBytes(USART1, arr, 1);
    // count++;
    // if (count > 1000) {                
    //     break;                         
    // }
    // }

    // Receives number of bytes to receive. 
    while (size != 1) {
        size = usart_receiveBytes(USART1, numberOfBytesToReceive, 1);
        count++;
        if (count > 1000) {                
            return nullptr;                         
        }
    }

    usart_transmitChar(USART1, 'A');

    int bytesToReceive = numberOfBytesToReceive[0];
    if (bytesToReceive <= 0 || bytesToReceive > 1024) { // don't know what max size is supposed to be.
        return nullptr;
    }
    int* receivedBytes = &bytesToReceive;
    int number_received = usart_recieveBytes(USART1, receivedBytes, numberOfBytesToReceive[0]);
    usart_transmitBytes(USART1, number_received);
    usart_transmitChar(USART1, 'A');
    return receivedBytes; // will cause a memory leak if not cleared.
}

// Rad
	//As a new person on this, I agree ^^^
void received_Transfer_GroundStation_Request(){
    int check_size  = 0;
    int check_count = 0;
    int receiveArray[1];
    while (check_size != 1)
    {
        check_size = usart_recieveBytes(USART1, receiveArray, 1);
        check_count++;
        if (check_count > 1000) {                
            break;                         
        }
    }
    int lengthOfMessage = receiveArray[0];


    check_count = 0;
    check_size = 0;
    while (check_size != 1)
    {
        check_size = usart_recieveBytes(USART1, receiveArray, 1);
        check_count++;
        if (check_count > 1000) {                
            break;                         
        }
    }
    int repetitionOfMessage = receiveArray[0];
    
    // while im receiving this message x times, am i just making sure that im receiving the right amount of data, 
    // or am i checking like every byte that comes in against the bytes in the array
    // that i already have

    return;
    
}


void received_State_of_Radio_Request(){
    //  how do i get the state of the Radio, no radio.c in the loggers branch
//    char state;
//    switch (current_state)
//    {
//    case State::Idle:
//        state = 'o';
//        break;
//    case State::TransferToGroundStation:
//        state = 't';
//        break;
//    case State::TransferToRadio:
//        state = 'T';
//        break;
//    default:
//        return;
//    }
    while (size == 0)
    {
        count = 0;
        usart_transmitChar(USART1, current_state);
        // continue sending until receie an A, check everytime i transmit
        size = usart_recieveBytes(USART1, arr, 1);
        if (count  > 1000){break;}
    }
}

int main(){
    char arr[1]; // im receiving a character here right?
    while (1)
    {
        size = usart_recieveBytes(USART1, arr, 1);
        if (size > 0){
            handleIdle(arr[0]); // only acts if receives something
            switch (current_state) {
            case TransferToGroundStation:
                handlereceived_Transfer_GroundStation_Request();
                break;
            case TransferToGroundStation:
                handlereceived_Transfer_GroundStation_Request();
            default:
                break;
            }
            
        }
        
    }
    
    // how is the state switch going to work how can i reenter the main functino 
    // whle another function is running and send a state 
}
