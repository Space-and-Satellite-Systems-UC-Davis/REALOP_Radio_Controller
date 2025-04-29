//This file was written in cpp before ??

#include "Intercomm.h"

typedef enum {
    DownloadData = 'D', //Receive data from PFC
    UploadData = 'U', //Transfer data to PFC
	TransferToGround = 't', //Transfer data to ground station
	SendState = 's', //Send state to PFC
} MessageType;

typedef enum {
    TXactive = 't', //Busy tranceiving data to ground station
	RXactive = 'r', //Busy receiving data from ground station
    Idle = 'o', //Not busy
} State;

State current_state = Idle;

//Length of chunks being sent in bytes
//Later adjust to account for PCP overhead
const size_t CHUNK_LENGTH = 8;


//this is a function FOR NOW. See if needed to retransmit often.
int sendChunk(PCPDevice *dev, uint8_t chunk[]) {
    int response = pcp_transmit(dev, chunk, CHUNK_LENGTH);

    return response;
}
void downloadData(PCPDevice *dev) {

}

void uploadData(PCPDevice *dev) {

}

void transferToGround(PCPDevice *dev) {

}

void sendState(PCPDevice *dev) {
	uint8_t state_chunk[CHUNK_LENGTH];
	state_chunk[0] = current_state;

	sendChunk(dev, state_chunk);
}

//Primary function from which everything else here is called
void handleInput(PCPDevice *dev, char input) {
	switch (input) {
		case DownloadData: downloadData(dev); break;
		case UploadData: uploadData(dev); break;
		case SendState: sendState(dev); break;
		case TransferToGround: transferToGround(dev); break;
	}
}


//Old code
//void prepareToRX(PCPDevice *dev) {
//	current_state = RXactive;
//
//	packet_length = receiveByte(dev);
//	n_packets = receiveByte(dev);
//
//	sendChar(dev, Acknowledge);
//}
//void handleIdle(char input) {
//    // Transition based on input
//    switch (input) {
//        case TransferToGroundStation:
//        case TransferToRadio:
//            currentState = input;
//            break;
//        case RXactive: // Get Radio State
//            received_State_of_Radio_Request();
//            break;
//        default:
//        	//UNKNOWN INPUT, SHOULD HAVE A WARNING
//            break;
//    }
//}
//
//void handleTransferToRadio(){
//    current_state = TransferToRadio;
//    int* receivedBytes = transferToRadioRequest();
//    current_state = Idle;
//    if (receivedBytes) {
//        free(receivedBytes);
//    }
//}
//
//void handlereceived_Transfer_GroundStation_Request(){
//    current_state = TransferToGroundStation;
//    received_Transfer_GroundStation_Request();
//    current_state = Idle;
//}
//
//// received Request for PFC to send data to Radio MCU
//int* transferToRadioRequest(){
//    int arr[1];
//    int numberOfBytesToReceive[1];
//    int size = 0;
//    int count = 0;
//
//    // Receives T.
//    // while (size != 1) {
//    // size = usart_receiveBytes(USART1, arr, 1);
//    // count++;
//    // if (count > 1000) {
//    //     break;
//    // }
//    // }
//
//    // Receives number of bytes to receive.
//    while (size != 1) {
//        size = pcp_receive(pcp, numberOfBytesToReceive);
//        count++;
//        if (count > 1000) {
//            return nullptr;
//        }
//    }
//
//    sendAck(pcp);
//
//    int bytesToReceive = numberOfBytesToReceive[0];
//    if (bytesToReceive <= 0 || bytesToReceive > 1024) { // What is max size?.
//        return nullptr;
//    }
//    int* receivedBytes = &bytesToReceive;
//    int number_received = pcp_receive(pcp, receivedBytes);
//    usart_transmitBytes(USART1, number_received); //TODO: ????????????
//    sendAck(pcp);
//    return receivedBytes; // will cause a memory leak if not cleared.
//}
//
//// Rad
//	//As a new person on this, I agree ^^^
//void received_Transfer_GroundStation_Request(){
//    int check_size  = 0;
//    int check_count = 0;
//    int receiveArray[1];
//    while (check_size != 1)
//    {
//        check_size = pcp_receive(pcp, receiveArray);
//        check_count++;
//        if (check_count > 1000) {
//            break;
//        }
//    }
//    int lengthOfMessage = receiveArray[0];
//
//
//    check_count = 0;
//    check_size = 0;
//    while (check_size != 1)
//    {
//        check_size = pcp_receive(pcp, receiveArray);
//        check_count++;
//        if (check_count > 1000) {
//            break;
//        }
//    }
//    int repetitionOfMessage = receiveArray[0];
//
//    // while im receiving this message x times, am i just making sure that im
//    // receiving the right amount of data,
//    // or am i checking like every byte that comes in against the bytes in the array
//    // that i already have
//
//    return;
//
//}
//
//
//void received_State_of_Radio_Request(){
//	int count = 0;
//    char response[1];
//    while (response[0] != Acknowledge) {
//
//        char payload[1];
//        payload[0] = current_state;
//        pcp_transmit(pcp, payload);
//
//        // continue sending until receive an A, check everytime i transmit
//        pcp_receive(pcp, response);
//
//        count++;
//
//        if (count  > 1000){break;} //rudimentary timeout, maybe replace later
//    }
//}
