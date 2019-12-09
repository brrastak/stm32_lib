// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

//user
#include "DMA.h"
#include "main.h"
#include "timer.h"
#include "LCD_8bit.h"

// Using channel 2 of DMA1 with TIM2 DMA request

static uint32_t to_transmit;
static uint16_t buf_length;
static bool transmitted = true;


// Interrupt handler
void DMA1_Channel2_IRQHandler()
{
    // Channel 2 transfer complete
    if ((DMA1->ISR & DMA_ISR_TCIF2) != 0) {
        // Clear interrupt flag
        DMA1->IFCR |= DMA_IFCR_CTCIF2;
        
        // All data transmitted
        if (to_transmit == 0) {
            // Disable channel
            DMA1_Channel2->CCR &= ~DMA_CCR2_EN;
            DisableTim2();
            transmitted = true;
            
            DisableDma();
            
            return;
        }
        
        // Disable channel
        DMA1_Channel2->CCR &= ~DMA_CCR2_EN;
        
        // Number of transactions calculation
        if (buf_length >= to_transmit) {
            DMA1_Channel2->CNDTR = to_transmit;
            // Transmit next iteration
            to_transmit = 0;
        }
        else {
            DMA1_Channel2->CNDTR = buf_length;
            // Transmit next iteration
            to_transmit -= buf_length;
        }
        
        // Channel enable
        DMA1_Channel2->CCR |= DMA_CCR2_EN;
    }
}
void InitDma()
{
    // Channel configuration
    // Peripheral address
    DMA1_Channel2->CPAR = (uint32_t)&(PARALLEL_PORT->ODR);
    
    DMA1_Channel2->CCR  =   DMA_CCR2_MEM2MEM    * 0 |   // memory to memory mode
                            DMA_CCR2_MSIZE_1    * 0 |   // memory size 00: 8 bit; 01:16; 11:32
                            DMA_CCR2_MSIZE_0    * 1 |   //
                            DMA_CCR2_PSIZE_1    * 0 |   // peripheral size 00: 8 bit; 01:16; 10:32
                            DMA_CCR2_PSIZE_0    * 1 |   //
                            DMA_CCR2_MINC       * 1 |   // memory increment mode
                            DMA_CCR2_PINC       * 0 |   // peripheral increment mode
                            DMA_CCR2_CIRC       * 0 |   // circular mode
                            DMA_CCR2_DIR        * 1 |   // data transfer direction 0: read from peripheral; 1: from memory
                            DMA_CCR1_TCIE       * 1;    // transfer complete interrupt enable
}
// From buf to PARALLEL_PORT
void TransmitDma(uint16_t * buf, uint16_t buf_size, uint32_t num)
{
    buf_length = buf_size;
    
    // Memory address
    DMA1_Channel2->CMAR = (uint32_t)buf;
    // Number of transactions
    if (buf_size >= num) {
        DMA1_Channel2->CNDTR = num;
        // Transmit next iteration
        to_transmit = 0;
    }
    else {
        DMA1_Channel2->CNDTR = buf_size;
        // Transmit next iteration
        to_transmit = num - buf_size;
    }
        
    // Channel enable
    DMA1_Channel2->CCR |= DMA_CCR2_EN;
    
    EnableTim2();
    
    transmitted = false;
}
void DisableDma(void)
{
    DMA1_Channel2->CCR &= ~DMA_CCR2_EN;
}
bool TransmittedDma()
{
    return transmitted;
}
