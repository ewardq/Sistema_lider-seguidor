
#ifndef ENCODER_H
#define	ENCODER_H

#include <xc.h>  
    bool E1; 
    bool E1_old;               //Esta variable se usa para no incrementar dos veces con el mismo pulso
    bool E2; 
    bool E2_old;
    
   uint16_t Encoder1 = 0;      // Contador para Encoder derecho
   uint16_t Encoder2 = 0;      // Contador para Encoder derecho
    
void bucle_encender_LED_cada_vuelta(){    // NO SE PUEDE DETENER <<<<<
    vehiculo(ADELANTE);
    while(1){
        E1 = PORTBbits.RB0;
        if ((E1_old != E1) & (E1 == 1)){
            Encoder1++;}
        E1_old = E1;
        
        if (Encoder1 == 2100){        // Encender el LED cada vuelta y esperar un poco antes de apagarlo
            PORTBbits.RB7 = 1;
            vehiculo(DETENER);
            __delay_ms(500);
            Encoder1 = 0;
            vehiculo(ADELANTE);
            PORTBbits.RB7 = 0;
        }
    }
}

#endif	/* XC_HEADER_TEMPLATE_H */

