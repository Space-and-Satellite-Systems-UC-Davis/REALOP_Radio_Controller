#include "Intercomm.h"

void received_State_of_Radio_Request(){
    int arr[1];
    int numberOfBytesToReceive[1]
    int size = 0
    int count = 0

    // Receives T.
    while (size != 1) {
    size = usart_receiveBytes(USART1, arr, 1);
    count++;
    if (count > 1000) {                
        break;                         
    }
    }

    // Receives number of bytes to receive. 
    count = 0
    size = 0
    while (size != 1) {
        size = usart_receiveBytes(USART1, numberOfBytesToReceive, 1);
        count++;
        if (count > 1000) {                
            break;                         
        }
    }

    usart_transmitChar(USART1, 'A');

    int receivedBytes[numberOfBytesToReceive[0]];
    int number_received = usart_recieveBytes(USART1, receivedBytes, numberOfBytesToReceive[0]);

    usart_transmitBytes(USART1, number_received);
    usart_transmitChar(USART1, 'A');
    return  
}


void received_Transfer_GroundStation_Request(){
    
}

