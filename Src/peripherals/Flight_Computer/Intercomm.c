#include "Intercomm.h"

uint8_t storedData[CHUNK_LENGTH * 4];
State current_state = Idle;

//Primary function from which everything else here is called
void handleInput(USART_TypeDef *dev, uint8_t chunk[]) {
	//Command must be the first char
	switch (chunk[0]) {
		case DownloadData: downloadData(dev, chunk); break;
		case UploadData: uploadData(dev); break;
		case SendState: sendState(dev); break;
		case TransferToGround: transferToGround(dev, chunk); break;
		case KillAll: killAll(dev); break;
	}
}

//Receive data from PFC
void downloadData(USART_TypeDef *dev, uint8_t chunk[]) {
	uint8_t n_chunks = chunk[1];

	crc_chunked_read(dev, storedData, CHUNK_LENGTH, n_chunks);
	// for (int i = 0; i < n_chunks; i++) {
	// 	int read_status = crc_read(dev, chunk);
	// 	if (read_status != -1) {
	// 		// // ECHO
	// 		//usart_transmitBytes(USART1, chunk, CHUNK_LENGTH);

	// 		//HERE BE DRAGONS
	// 		//Whenever radio memory is finished, put these chunks into memory
	// 		memcpy(&storedData[CHUNK_LENGTH*i], chunk, CHUNK_LENGTH);
	// 	}
	// }
}

//Transfer data to PFC
void uploadData(USART_TypeDef *dev) {
	uint8_t first_chunk[CHUNK_LENGTH];
	initEmptyChunk(first_chunk);

	first_chunk[0] = UploadData; // Tell PFC this is an upload request
	first_chunk[1] = (sizeof storedData - 1) / CHUNK_LENGTH + 1; //How many more chunks it should expect
	first_chunk[2] = Unflagged; //No actual upload flags were made yet

	crc_transmit(dev, first_chunk, CHUNK_LENGTH);

	crc_chunked_transmit(dev, storedData, sizeof storedData, CHUNK_LENGTH);

	// for (int i = 0; i < n_chunks; i++) {
	// 	nop(1000);

	// 	uint8_t packet[CHUNK_LENGTH + 1];
	// 	uint8_t *chunk = &packet[1];
	// 	packet[0] = i;
	// 	initEmptyChunk(chunk);

	// 	//HERE BE DRAGONS
	// 	//Once memory access is implemented, the radio would retrieve memory and put it here
	// 	memcpy(chunk, &storedData[CHUNK_LENGTH * i], CHUNK_LENGTH);

	// 	// //rat
	// 	// chunk[0]='R';
	// 	// chunk[1]='A';
	// 	// chunk[2]='T';

	// 	crc_transmit(dev, packet, CHUNK_LENGTH + 1);
	// }
}

//Send state to PFC
void sendState(USART_TypeDef*dev) {
	uint8_t state_chunk[CHUNK_LENGTH];
	initEmptyChunk(state_chunk);

	state_chunk[0] = current_state;

	crc_transmit(dev, state_chunk, CHUNK_LENGTH);
}

//Transfer data to ground station
void transferToGround(USART_TypeDef *dev, uint8_t chunk[]) {
	current_state = TXactive;

	uint8_t n_chunks = chunk[1];

	for (int i = 0; i < n_chunks; i++) {
		int read_status = crc_read(dev, chunk);
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

void killAll(USART_TypeDef *dev) {
	// TODO: Here Be Dragons
}

//Utility to initialize a chunk to all zeros
//Otherwise it might be random data and result in unpredictable behavior
void initEmptyChunk(uint8_t chunk[]) {
	for (size_t i = 0; i < CHUNK_LENGTH; i++) {
		chunk[i] = 0;
	}
}
