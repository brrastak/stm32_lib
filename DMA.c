// STM32F103
#include "stm32f10x.h"

// cstd
#include <stdbool.h>

//user
#include "DMA.h"


void InitDma(uint32_t mem, uint32_t periph)
{
    // Channel configuration
    // Memory address
    DMA1_Channel2->CMAR = mem;
    // Peripheral address
    DMA1_Channel2->CPAR = periph;
    // Number of transactions
    DMA1_Channel2->CNDTR = 2;
    
    DMA1_Channel2->CCR  =   DMA_CCR2_MEM2MEM    * 0 |   // memory to memory mode
                            DMA_CCR2_MSIZE_0    * 0 |   // memory size 00: 8 bit; 01:16; 11:32
                            DMA_CCR2_MSIZE_1    * 0 |   //
                            DMA_CCR2_PSIZE_0    * 0 |   // peripheral size 00: 8 bit; 01:16; 11:32
                            DMA_CCR2_PSIZE_1    * 0 |   //
                            DMA_CCR2_MINC       * 0 |   // memory increment mode
                            DMA_CCR2_PINC       * 1 |   // peripheral increment mode
                            DMA_CCR2_CIRC       * 1 |   // circular mode
                            DMA_CCR2_DIR        * 1;    // data transfer direction 0: read from peripheral; 1: from memory
    // Channel enable
    DMA1_Channel2->CCR |= DMA_CCR2_EN;
}
