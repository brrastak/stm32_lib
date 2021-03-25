// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

// user
#include "i2c.h"
#include "main.h"
#include "gpio.h"

// Local variables
// Data
static uint8_t* transmit_buf;
//static uint8_t* receive_buf;
// Data transmit address
static uint8_t addr;
// Number of data
static int to_transmit = 0;
//static int to_receive = 0;
// Flags
static volatile bool transmitted = true;
static volatile bool received = true;

// I2C interrupt
void I2C2_EV_IRQHandler(void)
{   
    // Start condition generated
    if ((I2C2->SR1 & I2C_SR1_SB) != 0) {
        
        (void)I2C2->SR1;                // clear flags
        I2C2->DR = addr;                // send I2C address
    }
    // Address sent
    if ((I2C2->SR1 & I2C_SR1_ADDR) != 0) {
        
        (void)I2C2->SR1;                // clear flags
        (void)I2C2->SR2;
        I2C2->DR = transmit_buf[0];     // send first data byte
        transmit_buf++;
        to_transmit--;
    }
    // Transmitter register empty
    if ((I2C2->SR1 & I2C_SR1_TXE) != 0) {
        
        if (to_transmit == 0) {         // no more data to send

            I2C2->CR2 &= ~I2C_CR2_ITBUFEN;      // buffer interrupt disable
        }
        else {
            
            I2C2->DR = transmit_buf[0];         // send data byte
            transmit_buf++;
            to_transmit--;
        }
    }
    // Transmission completed
    if (((I2C2->SR1 & I2C_SR1_BTF) != 0) && (to_transmit == 0)) {
        
        I2C2->CR2 &= ~I2C_CR2_ITEVTEN;      // event interrupt disable
        I2C2->CR1 |= I2C_CR1_STOP;          // generate stop condition
        transmitted = true;
    }

}
void InitI2c(void)
{
    // Transmitter in master mode
    I2C2->CR2 = 36;                     // RCC 36MHz
    I2C2->CCR |= 180;                   // 100kHz
    I2C2->TRISE = 0x55;                 // 1000ns
    I2C2->CR1 |= I2C_CR1_PE;            // peripheral enable
}
void TransmitI2c(uint8_t i2c_addr, uint8_t* buf, int num)
{
    to_transmit = num;
    addr = i2c_addr;
    transmit_buf = buf;
    transmitted = false;
    
    I2C2->CR2 |=    I2C_CR2_ITEVTEN |   // event interrupt enable
                    I2C_CR2_ITBUFEN;    // buffer interrupt enable
    
    // Generate start condition
    I2C2->CR1 |= I2C_CR1_START;
}
bool TransmittedI2c(void)
{
    return transmitted;
}
bool ReceivedI2c(void)
{
    return received;
}
void WaitForTransmitI2c(void)
{
    while (! transmitted)
        ;
}
void WaitForReceiveI2c(void)
{
    while (! received)
        ;
}
