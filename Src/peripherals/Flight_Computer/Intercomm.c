//This file was written in cpp before ??

#include "Intercomm.h"

//TEMPORARY
#include "UART/uart.h"

typedef enum {
    DownloadData = 'D', //Receive data from PFC
    UploadData = 'U', //Transfer data to PFC
	SendState = 's', //Send state to PFC
	TransferToGround = 'T', //Transfer data to ground station
} MessageType;

//Tells PFC what type of data is being sent
//For future flags, try to keep them lowercase and don't step on other enums
typedef enum {
    Unflagged = 'u', //No upload flags were designed yet
} UploadFlag;

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
void downloadData(PCPDevice *dev, uint8_t chunk[]) {
	uint8_t n_chunks = chunk[1];

	for (int i = 0; i < n_chunks; i++) {
		while(1) {
	    	int read_status = pcp_read(dev, chunk);
	    	if (read_status != -1) {
	    		//ECHO
//	    		for (int j = 0; j < CHUNK_LENGTH; j++) {
//		    		usart_transmitBytes(USART1, chunk, CHUNK_LENGTH);
//	    		}

	    		//HERE BE DRAGONS
	    		//Whenever radio memory is finished, put these chunks into memory

	    		break;
	    	}
		}
	}
}

void uploadData(PCPDevice *dev) {
	uint8_t first_chunk[CHUNK_LENGTH];
	const uint8_t n_chunks = 1; //Number of chunks that will be sent

	first_chunk[0] = Unflagged; //No actual upload flags were made yet
	first_chunk[1] = n_chunks;

	pcp_transmit(dev, first_chunk);


	for (int i = 0; i < n_chunks; i++) {
		uint8_t chunk[CHUNK_LENGTH] = {'R', 'A', 'T', 'S'};
		//HERE BE DRAGONS
		//Once memory access is implemented, the radio would retrieve memory and put it here

		pcp_transmit(dev, chunk);
	}
}

void transferToGround(PCPDevice *dev, uint8_t chunk[]) {
	current_state = TXactive;

	uint8_t n_chunks = chunk[1];

	for (int i = 0; i < n_chunks; i++) {
		while(1) {
	    	int read_status = pcp_read(dev, chunk);
	    	if (read_status != -1) {
	    		//ECHO
//	    		for (int j = 0; j < CHUNK_LENGTH; j++) {
//		    		usart_transmitBytes(USART1, chunk, CHUNK_LENGTH);
//	    		}

	    		//HERE BE DRAGONS
	    		//Whenever ground communication is written it will go here
	    			//Send n_chunks of radio memory to ground
	    			//May change based on ground comm interface

	    		break;
	    	}
		}
	}
}

void sendState(PCPDevice *dev) {
	uint8_t state_chunk[CHUNK_LENGTH];
	state_chunk[0] = current_state;

	sendChunk(dev, state_chunk);
}

//Primary function from which everything else here is called
void handleInput(PCPDevice *dev, uint8_t chunk[]) {
	//Character command must be the first char
	switch (chunk[0]) {
		case DownloadData: downloadData(dev, chunk); break;
		case UploadData: uploadData(dev); break;
		case SendState: sendState(dev); break;
		case TransferToGround: transferToGround(dev, chunk); break;
	}
}
