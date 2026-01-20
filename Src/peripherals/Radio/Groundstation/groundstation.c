#include <UART/uart.h>

#define RadioUart             USART1
#define RadioUartBaudRate     9600
#define ReceiveBufferSize    1024
#define 

void groundstation_init(bool isGS) {
    if !isGs return;

    test()


}

void board_to_Pi() {


}

void Pi_to_board() {


}

void test() {
    usart_init(RadioUart, RadioUartBaudRate);

    uint8_t *data = "Some characters";
    usart_transmitBytes(RadioUart, data)

    uint8_t buffer[ReceiveBufferSize] = {}
    uint16_t amount_read = usart_receiveBytes(RadioUart, )


}