#include "Intercomm.h"
#include <print_scan.h>

uint8_t storedData[CHUNK_LENGTH * 30];
State current_state = Idle;

//Primary function from which everything else here is called
void handleInput(USART_TypeDef *dev, uint8_t chunk[]) {
	//Command must be the first char
	switch (chunk[0]) {
		case DownloadData: downloadData(dev, chunk); break;
		case UploadData: uploadData(dev, chunk, sizeof storedData); break;
		case SendState: sendState(dev); break;
		case TransferToGround: transferToGround(dev, chunk); break;
		case KillAll: killAll(dev); break;
	}
}

//Receive data from PFC
void downloadData(USART_TypeDef *dev, uint8_t chunk[]) {
	uint8_t n_chunks = chunk[1];

	crc_chunked_read(dev, &storedData[0], CHUNK_LENGTH, n_chunks);
	uint8_t remainder = chunk[2];

	int totalBytes = (n_chunks-1) * CHUNK_LENGTH + remainder;

	printMsg("GOT: ");
	for(int i = 0; i<totalBytes; i++){
		printMsg("%c", storedData[i]);
	}
	printMsg("\r\n");

	// usart_transmitBytes(dev, storedData, CHUNK_LENGTH*4);
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
	uint8_t first_chunk[4];

	//temp transfer data and size
	//i know how to spell, i just didn't include apostrophes bc that's extra work
	uint8_t data[229] = "Hola hola, Ive come all this way, from radio all across the UART channels to talk to you, on Intellisat. You know, youre such a cool person, youre so good at debugging and not crying when bugs start popping up everywhere. cheers!";
	uint8_t data_len = 229;

	first_chunk[0] = UploadData; // Tell PFC this is an upload request
	first_chunk[1] = (data_len - 1) / CHUNK_LENGTH + 1; //How many more chunks it should expect
	first_chunk[2] = data_len % CHUNK_LENGTH;
	if(first_chunk[2] == 0)
		first_chunk[2] = CHUNK_LENGTH;
	first_chunk[3] = Unflagged; //No actual upload flags were made yet

	crc_transmit(dev, first_chunk, 4);

	crc_chunked_transmit(dev, &data, data_len, CHUNK_LENGTH);

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
	uint8_t state_chunk[1];
	state_chunk[0] = current_state;

	crc_transmit(dev, state_chunk, 1);
}

//Transfer data to ground station
void transferToGround(USART_TypeDef *dev, uint8_t chunk[]) {
	current_state = TXactive;

	uint8_t n_chunks = chunk[1];
	radio_transmit(n_chunks * CHUNK_LENGTH, storedData, UHF_SPI);

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
