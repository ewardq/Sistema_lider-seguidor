/*   ========================================================================
 *
 *            Esta librería contiene una función que obtiene 
 *            la distancia en metros sensada por el  HC-SR04
 * 
     =======================================================================*/

#ifndef ULTRASONIC_H
#define	ULTRASONIC_H

#include <xc.h> // include processor files - each processor file is guarded.  

unsigned int get_distancia_ultrasonico(){
    unsigned temp;
    TMR1H = 0;                //Sets the Initial Value of Timer
    TMR1L = 0;                //Sets the Initial Value of Timer

    RA3 = 1;                  //TRIGGER HIGH
    __delay_us(10);           //10uS Delay 
    RA3 = 0;                  //TRIGGER LOW

    while(!RA2);              //Waiting for Echo
    TMR1ON = 1;               //Timer Starts
    while(RA2);               //Waiting for Echo goes LOW
    TMR1ON = 0;               //Timer Stops

    temp = (TMR1L | (TMR1H<<8)); //Reads Timer Value
    temp = temp/29.41;              //Converts Time to Distance
    temp = temp + 1;                //Distance Calibration
    if(temp>=2 && temp<=400) {//Check whether the result is valid or not
        return temp;
     }       
    else return 0;
}

#endif

