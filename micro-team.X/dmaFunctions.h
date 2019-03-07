#ifndef DMA_H
#define DMA_H

extern unsigned int adcData[32]__attribute__((space(dma)));//data is copied (automatically) directly from ADC buffers/register to adcData
void initDmaChannel4();

unsigned int getDistance();

#endif /* DMA_H */