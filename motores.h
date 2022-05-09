/*   ========================================================================
 *
 *     Esta librería controla 3 motores con 3 puentes H y el servomotor.
 *   También contiene funciones para asegurarse de que el hardware funcione
 *                           
     =======================================================================*/

#ifndef MOTORES_H
#define	MOTORES_H

#include <xc.h>  

#define DETENER   0b00001

#define APAGAR    0b00001
#define DERECHA   0b00010  
#define IZQUIERDA 0b00100
#define ADELANTE  0b01000
#define ATRAS     0b10000

// ____________________________________________________________________________
// =====================  Control de motores ON-OFF  ==========================
// ============================================================================
void vehiculo(unsigned op){
    if (op & DETENER){
        PORTAbits.RA7  = 0;        // Rueda Derecha atras
        PORTCbits.RC1  = 0;
    
        PORTAbits.RA6  = 0;        // Rueda Izquierda atras
        PORTCbits.RC2 = 0;
    }
    if (op & DERECHA){
        PORTAbits.RA7  = 1;        // Rueda Derecha avanza
        PORTCbits.RC1  = 0;
    
        PORTAbits.RA6 = 0;        // Rueda Izquierda se detiene
        PORTCbits.RC2 = 0;
    }
    if (op & IZQUIERDA){
        PORTAbits.RA7  = 0;        // Rueda Derecha se detiene
        PORTCbits.RC1  = 0;
    
        PORTAbits.RA6  = 1;        // Rueda Izquierda avanza
        PORTCbits.RC2 = 0;
    }
    if (op & ADELANTE){
        PORTAbits.RA7 = 1;        // Rueda Derecha avanza
        PORTCbits.RC1 = 0;
    
        PORTAbits.RA6 = 1;        // Rueda Izquierda avanza
        PORTCbits.RC2 = 0;
    }
    if (op & ATRAS){
        PORTAbits.RA7  = 0;        // Rueda Derecha atras
        PORTCbits.RC1  = 1;
    
        PORTAbits.RA6  = 0;        // Rueda Izquierda atras
        PORTCbits.RC2 = 1;
    }
}

void direccional(unsigned op){
    if (op & DERECHA){
        PORTAbits.RA0 = 1;
        PORTAbits.RA1 = 0;
    }
    if (op & IZQUIERDA){
        PORTAbits.RA0 = 0;
        PORTAbits.RA1 = 1;
    }
    if (op & APAGAR){
        PORTAbits.RA0 = 0;
        PORTAbits.RA1 = 0; 
    }
}

//  >>>>>>>>>>>>>>>>>>>> Función de prueba <<<<<<<<<<<<<<<<<<<<<<<<<< 
//                      <<    Motores    >>
void probar_motores_mov(){
    //Probar los modos de movimiento
    vehiculo(ATRAS);
    __delay_ms(1000);
    
    vehiculo(DERECHA);
    direccional(DERECHA);
    __delay_ms(1000);
    
    vehiculo(IZQUIERDA);
    direccional(IZQUIERDA);
    __delay_ms(1000);
    
    vehiculo(DETENER);
    direccional(APAGAR);
    __delay_ms(1000);
}
// ============================================================================

// ____________________________________________________________________________
// =======  Generación de PWM para servo (50Hz / 5-10% Duty Cycle)  ===========
// ============================================================================

const unsigned _0 = 0;
const unsigned _90 = 90;
const unsigned _180 = 180;

void posicionar_servo(unsigned degrees){
    for(int i = 0; i < 6; i++){
     PORTCbits.RC0 = 1;
        __delay_us(1000);
        switch(degrees){    
            case 0:                       //Total de 1ms
             break;   
            case 90:  __delay_us(500);    //Total de 1.5ms
             break;
            case 180: __delay_us(1000);   //Total de 2ms
             break;
            default:  __delay_us(500);   
        }    
     PORTCbits.RC0 = 0;
        switch(degrees){    
            case 0:    __delay_us(1000);
             break;
            case 90:   __delay_us(500);    
             break;
            case 180:
             break;      
            default:   __delay_us(500);    //Posición neutral (90°)
        }
        __delay_us(18000);
     }
}

//  >>>>>>>>>>>>>>>>>>>> Función de prueba <<<<<<<<<<<<<<<<<<<<<<<<<< 
//                     <<   Servomotor   >>
void probar_servomotor(){
    __delay_ms(1000);
     posicionar_servo(_0);
     
     __delay_ms(1000);
     posicionar_servo(_90);
     
     __delay_ms(1000);
     posicionar_servo(_180);
     
    __delay_ms(1000);
     posicionar_servo(_90);
}
// ============================================================================


#endif	

