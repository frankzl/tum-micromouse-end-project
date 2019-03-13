#ifndef DMA_H
#define	DMA_H

extern unsigned int adcData[32]__attribute__((space(dma)));//data is copied directly from ADC buffers/register to adcData
void initDmaChannel4();

#endif	/* DMA_H */
