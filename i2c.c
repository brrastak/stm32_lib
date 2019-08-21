// STM32F103
#include "stm32f10x.h"

// user
#include "i2c.h"

uint8_t i2c_addr;
uint8_t i2c_data;
int i2c_byte_to_send;

void InitI2C(void)
{
    I2C2->CR2 = 36;                     // RCC 36MHz
    I2C2->CCR |= 180;                   // 100kHz
    I2C2->TRISE = 0x55;                 // 1000ns
    I2C2->CR1 |= I2C_CR1_PE;            // peripheral enable
    I2C2->CR2 |=    I2C_CR2_ITEVTEN |   // event interrupt enable
                    I2C_CR2_ITBUFEN;    // buffer interrupt enable
}

inline void I2CWrite(uint8_t addr, uint8_t data, int num)
{
    i2c_byte_to_send = num;
    i2c_addr = addr;
    i2c_data = data;
    I2C2->CR1 |= I2C_CR1_START;
}

// I2C interrupt
void I2C2_EV_IRQHandler(void)
{   
    if (I2C2->SR1 | I2C_SR1_SB) {
        (void)I2C2->SR1;
        I2C2->DR = i2c_addr;
    }
    if (I2C2->SR1 | I2C_SR1_ADDR) {
        (void)I2C2->SR1;
        (void)I2C2->SR2;
        I2C2->DR = i2c_data;
    }
    if ((I2C2->SR1 | I2C_SR1_BTF)&&(I2C2->SR1 | I2C_SR1_TXE)) {
        (void)I2C2->SR1;
        if (i2c_byte_to_send == 0) {
            I2C2->CR1 |= I2C_CR1_STOP;
        }
        else
            i2c_byte_to_send--;
    }
}