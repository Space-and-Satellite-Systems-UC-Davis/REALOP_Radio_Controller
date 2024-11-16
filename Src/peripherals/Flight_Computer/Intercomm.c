#include "Intercomm.h"

void received_State_of_Radio_Request(){
    int arr[1];
    int numberOfBytesToReceive[1];
    int size = 0;
    int count = 0;

    // Receives T.
    while (size != 1) {
    size = usart_receiveBytes(USART1, arr, 1);
    count++;
    if (count > 1000) {                
        break;                         
    }
    }

    // Receives number of bytes to receive. 
    count = 0;
    size = 0;
    while (size != 1) {
        size = usart_receiveBytes(USART1, numberOfBytesToReceive, 1);
        count++;
        if (count > 1000) {                
            break;                         
        }
    }

    // how do I make sure that whatever information is received is returned to the original function? should i just use a pointer?
    usart_transmitChar(USART1, 'A');

    int receivedBytes[numberOfBytesToReceive[0]];
    int number_received = usart_recieveBytes(USART1, receivedBytes, numberOfBytesToReceive[0]);

    usart_transmitBytes(USART1, number_received);
    usart_transmitChar(USART1, 'A');
    return  
}


void received_Transfer_GroundStation_Request(){
    int check_size  = 0;
    int check_count = 0;
    int receiveArray[1];
    while (check_size != 1)
    {
        check_size = usart_recieveBytes(USART1, receiveArray, 1);
        count++;
        if (count > 1000) {                
            break;                         
        }
    }
    int lengthOfMessage = receiveArray[0];


    check_count = 0
    check_size = 0
    while (check_size != 1)
    {
        check_size = usart_recieveBytes(USART1, receiveArray, 1);
        count++;
        if (count > 1000) {                
            break;                         
        }
    }
    int repetitionOfMessage = receiveArray[0];
    

    // while im receiving this message x times, am i just making sure that im receiving the right amount of data, 
    //or am i checking like every byte that comes in against the bytes in the array
    // that i already have

    return
    
}


void received_State_of_Radio_Request(){
    //  how do i get the state of the Radio, no radio.c in the loggers branch

    int size = 0;
    int arr[1];
    char state = 't' // default value for now
    // receives back acknowledgement to stop
    while (size == 0)
    {
        usart_transmitChar(USART1, state)
        // continue sending until receie an A, check everytime i transmit
        size = usart_recieveBytes(USART1, arr, 1);
    }
    return

    



}
