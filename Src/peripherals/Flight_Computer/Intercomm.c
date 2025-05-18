#include "Intercomm.h"

//Length of chunks being sent in bytes between PFC, Radio, and Ground
const int CHUNK_LENGTH = 8;

State current_state = Idle;

//Primary function from which everything else here is called
void handleInput(PCPDevice *dev, uint8_t chunk[]) {
	//Command must be the first char
	switch (chunk[0]) {
		case DownloadData: downloadData(dev, chunk); break;
		case UploadData: uploadData(dev); break;
		case SendState: sendState(dev); break;
		case TransferToGround: transferToGround(dev, chunk); break;
	}
}

//Receive data from PFC
void downloadData(PCPDevice *dev, uint8_t chunk[]) {
	uint8_t n_chunks = chunk[1];

	for (int i = 0; i < n_chunks; i++) {
		int read_status = pcp_read(dev, chunk);
		if (read_status != -1) {
			// // ECHO
			//usart_transmitBytes(USART1, chunk, CHUNK_LENGTH);

			//HERE BE DRAGONS
			//Whenever radio memory is finished, put these chunks into memory
		}
	}
}

//Transfer data to PFC
void uploadData(PCPDevice *dev) {
	uint8_t first_chunk[CHUNK_LENGTH];
	initEmptyChunk(first_chunk);

	const uint8_t n_chunks = 1;

	first_chunk[0] = UploadData; // Tell PFC this is an upload request
	first_chunk[1] = n_chunks; //How many more chunks it should expect
	first_chunk[2] = Unflagged; //No actual upload flags were made yet

	pcp_transmit(dev, first_chunk, CHUNK_LENGTH);

	for (int i = 0; i < n_chunks; i++) {
		nop(1000);

		uint8_t chunk[CHUNK_LENGTH];
		initEmptyChunk(chunk);

		//HERE BE DRAGONS
		//Once memory access is implemented, the radio would retrieve memory and put it here

		//rat
		chunk[0]='R';
		chunk[1]='A';
		chunk[2]='T';

		pcp_transmit(dev, chunk, CHUNK_LENGTH);
	}
}

//Send state to PFC
void sendState(PCPDevice *dev) {
	uint8_t state_chunk[CHUNK_LENGTH];
	initEmptyChunk(state_chunk);

	state_chunk[0] = current_state;

	pcp_transmit(dev, state_chunk, CHUNK_LENGTH);
}

//Transfer data to ground station
void transferToGround(PCPDevice *dev, uint8_t chunk[]) {
	current_state = TXactive;

	uint8_t n_chunks = chunk[1];

	for (int i = 0; i < n_chunks; i++) {
		int read_status = pcp_read(dev, chunk);
		if (read_status != -1) {
			// // ECHO
			//usart_transmitBytes(USART1, chunk, CHUNK_LENGTH);

			//HERE BE DRAGONS
			//Whenever ground communication is written it will go here
				//Send n_chunks of radio memory to ground
				//May change based on ground comm interface
		}
	}

	current_state = Idle;
}

//Utility to initialize a chunk to all zeros
//Otherwise it might be random data and result in unpredictable behavior
void initEmptyChunk(uint8_t chunk[]) {
	for (size_t i = 0; i < CHUNK_LENGTH; i++) {
		chunk[i] = 0;
	}
}
