
#ifndef I2C_H
#define	I2C_H

#include <xc.h> 

void I2C_Master_Init(const unsigned long c){
  SSPCON = SSPCON | (_SSPCON_SSPEN_MASK);  // Enables the serial port and configures the SDA and
                                           // and SCL pins as the source of the serial port pins
  SSPCONbits.SSPM = 0b1000;                    // I2C Master mode
  
  SSPSTAT = SSPSTAT | (_SSPSTAT_SMP_MASK);  // I2C Slew rate control disabled for standard speed mode (100kHz))
  
  SSPCON2 = 0;                             // Idle 
  SSPADD = (_XTAL_FREQ/(4*c))-1;
  
  TRISC3 = 1;        //Setting as input as given in datasheet
  TRISC4 = 1;        //Setting as input as given in datasheet
}

void I2C_Master_Wait(){
  while ((SSPSTAT & _SSPSTAT_R_nW_MASK)); // Wait while Transmit in progress || 
}

void I2C_Master_Start(){
    I2C_Master_Wait();
    SEN = 1;
}

void I2C_Master_RepeatedStart(){
  I2C_Master_Wait();
  RSEN = 1;
}

void I2C_Master_Stop(){
  I2C_Master_Wait();
  PEN = 1;
}

void I2C_Master_Write(unsigned d){
  I2C_Master_Wait();
  SSPBUF = d;
}

unsigned short I2C_Master_Read(unsigned short a){
  unsigned short temp;
  I2C_Master_Wait();
  RCEN = 1;
  I2C_Master_Wait();
  temp = SSPBUF;
  I2C_Master_Wait();
  ACKDT = (a)?0:1;
  ACKEN = 1;
  return temp;
}
// ============================================================================

#endif	/* XC_HEADER_TEMPLATE_H */

