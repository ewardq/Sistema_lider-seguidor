// PIC16F886 Configuration Bit Settings
    
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 4000000      // 4MHz

//Macros
#define MASK(x) ((unsigned char)(1<<x))        //Manipulacion de bits

#include <xc.h>
#include <pic16f886.h>
#include <math.h>
#include <stdbool.h>
#include "ultrasonic.h"
#include "motores.h"
#include "i2c.h"
#include "UART.h"

//Puesto que se van a utilizar con interrupciones, necesitamos que sean variables globales
uint16_t Encoder1 = 0;      // Contador para Encoder derecho
uint16_t Encoder2 = 0;      // Contador para Encoder derecho
float wheelAngle;
bool acc = false;
#include "encoder.h"

void probar_LED();
void enviar_datos();
bool distancia_menor_a_cm();

void main(void) {
    //Configurando puertos
    TRISA = 0b00000100; 
    TRISB = 0b00000011;
    ANSEL = 0x00;
    ANSELH = 0x00;
    TRISC = 0b00011000;
    
    T1CON = 0x10;               // Activar Timer1, necesario para el sensor ultrasonico
   
    const unsigned dist_para_vuelta = 5;  // Distancia necesaria para dar la vuelta en [cm]
    unsigned dist;                        // Variable aux
    unsigned short vx;                    // coordenada x
    unsigned short vy;                    // coordenada y
    unsigned short vR;                    // vel. rueda derecha
    unsigned short vL;                    // vel. rueda izquierda
    unsigned short speed;                 // vel. vehiculo
    
    vehiculo(DETENER);
    direccional(APAGAR);
    PORTBbits.RB7 = 0;          // Apagar LED     
    
    probar_LED();               // Asegurarse de que el LED funcione
    // probar_motores_mov(); 
    probar_servomotor();        // Servo ok?

    Initialize_UART();

    while(1){
        speed = (vR + vL)/ 2;
        vx = speed * cos(wheelAngle);           // Encontrar la posicion [x,y] , <<Se necesita cambiar las funciones trig. por tablas, para 
        vy = speed * sin(wheelAngle);           //                                   que sea mas rapido el programa y no se use tanta RAM >>
        vehiculo(ADELANTE);
        
        enviar_datos();
        acc = false;
        if (distancia_menor_a_cm(10) == true){
            vehiculo(DETENER);
            
            while(acc = false){
            posicionar_servo(0);
            dist = get_distancia_ultrasonico();
            if (dist >= dist_para_vuelta){
                direccional(IZQUIERDA);
                __delay_ms(300);
                direccional(APAGAR);
                vehiculo(ATRAS);
                enviar_datos();
                
                __delay_ms(2000);
                direccional(DERECHA);
                enviar_datos();
                __delay_ms(300);
                direccional(APAGAR);
                
                vehiculo(DERECHA);
                enviar_datos();
                __delay_ms(1000);
                
                acc = true;
            }
            else{
                posicionar_servo(180);
                dist = get_distancia_ultrasonico();
                if (dist >= dist_para_vuelta){
                    direccional(DERECHA);
                    __delay_ms(300);
                    direccional(APAGAR);
                    vehiculo(ATRAS);
                    enviar_datos();
                    __delay_ms(2000);
                
                    direccional(IZQUIERDA);
                    __delay_ms(300);
                    direccional(APAGAR);
                    vehiculo(IZQUIERDA);
                    enviar_datos();
                    __delay_ms(1000);
                
                    acc = true;
                } 
                else{
                    vehiculo(ATRAS);
                    enviar_datos();
                    __delay_ms(2000);
                }
             }
            }
                
            posicionar_servo(90);
            vehiculo(ADELANTE);
        }
    }
    
    return;
}


void probar_LED(){
    for(unsigned i = 0; i < 5; i++){    // Parpadear LED 3 veces
        __delay_ms(500);
        PORTB ^= MASK(7);              // Cambia el estado del bit 7 del puerto B (el LED)
    }
    __delay_ms(700);
     PORTBbits.RB7 = 0;
}

bool distancia_menor_a_cm(unsigned limite){
    unsigned aux = get_distancia_ultrasonico();      // Leer distancia ultrasonico
    if ((aux < limite) & (aux != 0)){                // Obstaculo a menos de 'limite' centimetros?
         PORTBbits.RB7 = 1;                    
        return true;
        }
    else{
        PORTBbits.RB7 = 0;
        return false;
        }
}

void enviar_datos(){
    incrementa_encoders();
    UART_send_char(Encoder1);
    UART_send_char(Encoder2);
    UART_send_char(13);
}


    /*
    unsigned x1 = 0xff;
    unsigned x2 = 0x00;
    
    I2C_Master_Init(100000);
    while(1){
        I2C_Master_Start();
        I2C_Master_Write(0x30);
        I2C_Master_Write(x1);
        I2C_Master_Stop();
        __delay_ms(500);
   
        I2C_Master_Start();
        I2C_Master_Write(0x30);
        I2C_Master_Write(x2);
        I2C_Master_Stop();
        __delay_ms(500);
    }
    */
