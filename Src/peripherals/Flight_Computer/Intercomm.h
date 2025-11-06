//This file was written in cpp before ??

/*****************************************************************************
* File:             Intercomm.h
*
* Complete:         2025-05-04
* Description:      Interface for talking to the PFC. See
* 					https://docs.google.com/document/d/1lEWTtAZO5vygF9-GaUQKHPeiQyrCOMVyY5qmEgHYWqY/edit?usp=sharing
* 					for the implementation details
*
*****************************************************************************/

#ifndef PERIPHERALS_INTERCOMM_H_
#define PERIPHERALS_INTERCOMM_H_

#include "Radio/radio.h"
#include "UART/crc.h"

typedef enum {
    DownloadData = 'D', //Receive data from PFC
    UploadData = 'U', //Transfer data to PFC
	SendState = 'S', //Send state to PFC
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

//Primary function from which everything else here is called
void handleInput(USART_TypeDef *dev, uint8_t chunk[]);


//Length of chunks being sent in bytes between PFC, Radio, and Ground
#define CHUNK_LENGTH 8
#define MAX_UINT8_T 255

//DUST:

//Receive data from PFC
void downloadData(USART_TypeDef *dev, uint8_t chunk[]);

//Transfer data to PFC
void uploadData(USART_TypeDef *dev);

//Send state to PFC
void sendState(USART_TypeDefdev);

//Transfer data to ground station
void transferToGround(USART_TypeDef *dev, uint8_t chunk[]);

//Utility to initialize a chunk to all zeros
//Otherwise it might be random data and result in unpredictable behavior
void initEmptyChunk(uint8_t chunk[]);



#endif /* PERIPHERALS_INTERCOMM_H_ */
