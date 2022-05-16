#ifndef UART_H
#define	UART_H

#include <xc.h>  

// ____________________________________________________________________________
// =================  Comunicaci�n UART   =================
// ============================================================================
//Configurando la transmisi�n EUSART
#define _TXEN  1   //Activa EUSART
#define _SYNC  0   //Comunicaci�n as�ncrona
#define _SPEN  1  // Configura TX como salida digital
#define _BRGH  0  //Activar s�lo si se utiliza frecuencia de procesador de m�s de 4MHz
#define _BRG16 1  // Activar para enviar un dato de 16 bits, por default env�a uno de 8bits

 //  SET_BAUDRATE(9600);
void SET_BAUDRATE(int br){
   SPBRG = 25;             
   //SPBRG = (_XTAL_FREQ / (16*br)) - 1;
   BRGH = 1;
}

void Initialize_UART(){
   //Set the pins of RX and TX/
    TRISC6 = 1;
    TRISC7 = 1;
    
    SET_BAUDRATE(9600);
    
    // Habilita el puerto serial asincrono //
    SYNC  = 0;    // Asynchronous
    SPEN  = 1;    // Enable serial port pins


    // Habilita los registros correspondientes //
    TXEN  = 1;    // enable transmission
    CREN  = 1;    // enable reception
  
    
    // Selecciona la transmision de 8bits //  
    TX9   = 0;    // 8-bit reception selected
    RX9   = 0;    // 8-bit reception mode selected
}

// Envia un byte //
void UART_send_char(char byte){
    TXREG = byte;
  //  while(!TXIF);    //Habilitar cuando se use la interrupcion
    while(!TRMT);
}

// Enviar una cadena de bytes //
void UART_send_string(char* string){
    while(*string)
    UART_send_char(*string++);
}

char BT_get_char(void)   {
    if(OERR){ // over run error ?
        CREN = 0;
        CREN = 1; //Reset CREN
    }

    if(TRMT==1){   // si el usuario ha enviado un mensaje, entonces la funcion regresa ese valor char (ASCII)
        while(!TRMT);  
        return RCREG;
    }
    else // si el usuario no ha enviado un mensaje, no regrese nada
        return 0;
}

#endif	/* XC_HEADER_TEMPLATE_H */

