#ifndef UART_H
#define	UART_H

#include <xc.h>  

// ____________________________________________________________________________
// =================  Comunicación UART   =================
// ============================================================================
//Configurando la transmisión EUSART
#define _TXEN  1   //Activa EUSART
#define _SYNC  0   //Comunicación asíncrona
#define _SPEN  1  // Configura TX como salida digital
#define _BRGH  0  //Activar sólo si se utiliza frecuencia de procesador de más de 4MHz
#define _BRG16 1  // Activar para enviar un dato de 16 bits, por default envía uno de 8bits

 //  SET_BAUDRATE(9600);
void SET_BAUDRATE(int br){
   uint16_t Set_BaudRate;
   Set_BaudRate = (_XTAL_FREQ / (16*br)) - 1;
   SPBRG = Set_BaudRate;
   BRGH = 1;
}

void Initialize_UART(){
   //Set the pins of RX and TX/
    TRISC6 = 1;
    TRISC7 = 1;
    
    SET_BAUDRATE(9600);
    
    //****Enable Asynchronous serial port*******//
    SYNC  = 0;    // Asynchronous
    SPEN  = 1;    // Enable serial port pins
    //_____Asynchronous serial port enabled_______//

    //**Lets prepare for transmission & reception**//
    TXEN  = 1;    // enable transmission
    CREN  = 1;    // enable reception
    //__UART module up and ready for transmission and reception__//
    
    //**Select 8-bit mode**//  
    TX9   = 0;    // 8-bit reception selected
    RX9   = 0;    // 8-bit reception mode selected
    //__8-bit mode selected__//     

    //Enable global and ph. interrupts//
    GIE = 1;
    PEIE= 1;

    //Enable interrupts for Tx. and Rx.//
    RCIE=1;
    TXIE=1;
}

//**Function to send one byte of date to UART**//
void UART_send_char(char byte){
    TXREG = byte;
    while(!TXIF);  
    while(!TRMT);
}

void UART_send_string(char* string){
    while(*string)
    UART_send_char(*string++);
}


//Function to broadcast data from RX. buffer//
void broadcast_BT(){
  TXREG = 13;  
  __delay_ms(500);
}

char BT_get_char(void)   {
    if(OERR){ // check for over run error 
        CREN = 0;
        CREN = 1; //Reset CREN
    }

    if(RCIF==1){ //if the user has sent a char return the char (ASCII value)
        while(!RCIF);  
        return RCREG;
    }
    else //if user has sent no message return 0
        return 0;
}

#endif	/* XC_HEADER_TEMPLATE_H */

