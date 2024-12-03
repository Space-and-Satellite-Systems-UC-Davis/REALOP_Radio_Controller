#include "Intercomm.h"
#include "radio.h"

enum class State{
    Idle,
    TransferToRadio,
    TransferToGroundStation
} 

State current_state = State::Idle;

void handleTransferToRadio(){
    current_state = State::TransferToRadio;
    int* receivedBytes = transferToRadioRequest();
    current_state = State::Idle;
    if (receivedBytes) { 
        delete[] receivedBytes; 
    }
}

void handlereceived_Transfer_GroundStation_Request(){
    current_state = State::TransferToGroundStation;
    received_Transfer_GroundStation_Request();
    current_state = State::Idle;
}

void handleIdle(char input) {
    // Transition based on input
    switch (input) {
        case 't': // Transfer to Ground Station
            currentState = State::TransferToGroundStation;
            break;
        case 'T': // Transfer to Radio
            currentState = State::TransferToRadio;
            break;
        case 'r': // Get Radio State
            received_State_of_Radio_Request();
            break;
        default:
            break;
    }
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

    int bytesToReceive = numberOfBytesToReceive[0]
    if (bytesToReceive <= 0 || bytesToReceive > 1024) { // don't know what max size is supposed to be.
        return nullptr;
    }
    int* receivedBytes = new int[bytesToReceive];
    int number_received = usart_recieveBytes(USART1, receivedBytes, numberOfBytesToReceive[0]);
    usart_transmitBytes(USART1, number_received);
    usart_transmitChar(USART1, 'A');
    return receivedBytes; // will cause a memory leak if not cleared.
}

// Rad
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
    //or am i checking like every byte that comes in against the bytes in the array
    // that i already have

    return;
    
}


void received_State_of_Radio_Request(){
    //  how do i get the state of the Radio, no radio.c in the loggers branch
    char state;
    switch (current_state)
    {
    case State::Idle:
        state = 'o';
        break;
    case State::TransferToGroundStation:
        state = 't';
        break;
    case State::TransferToRadio:
        state = 'T';
        break;  
    default:
        return;
    }
    while (size == 0)
    {
        count = 0;
        usart_transmitChar(USART1, state);
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
            switch (current_state)
            {
            case State::TransferToGroundStation:
                handlereceived_Transfer_GroundStation_Request();
                break;
            case State::TransferToGroundStation:
                handlereceived_Transfer_GroundStation_Request();
            default:
                break;
            }
            
        }
        
    }
    
    // how is the state switch going to work how can i reenter the main functino 
    // whle another function is running and send a state 
}
