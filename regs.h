// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2017 Andrea Loi                                                *
 */

#ifndef __regs_h__
#define __regs_h__

#include <stdint.h>

struct SIG {
	volatile uint16_t F_SIZE;
	volatile uint16_t RESERVED_1[3];
	volatile uint16_t U_ID_15_0;
	volatile uint16_t U_ID_31_16;
	volatile uint16_t U_ID_63_48;
	volatile uint16_t U_ID_47_32;
	volatile uint16_t U_ID_95_80;
	volatile uint16_t U_ID_79_64;
};

struct TIM2 {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RESERVED_1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t RESERVED_2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
};

struct RTC {
	volatile uint32_t CRH;
	volatile uint32_t CRL;
	volatile uint32_t PRLH;
	volatile uint32_t PRLL;
	volatile uint32_t DIVH;
	volatile uint32_t DIVL;
	volatile uint32_t CNTH;
	volatile uint32_t CNTL;
	volatile uint32_t ALRH;
	volatile uint32_t ALRL;
};

struct WWDG {
	volatile uint32_t CR;
	volatile uint32_t CFR;
	volatile uint32_t SR;
};

struct IWDG {
	volatile uint32_t KR;
	volatile uint32_t PR;
	volatile uint32_t RLR;
	volatile uint32_t SR;
};

struct SPI {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
};

struct USART {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
};

struct I2C {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
};

struct USB {
	volatile uint32_t EP0R;
	volatile uint32_t EP1R;
	volatile uint32_t EP2R;
	volatile uint32_t EP3R;
	volatile uint32_t EP4R;
	volatile uint32_t EP5R;
	volatile uint32_t EP6R;
	volatile uint32_t EP7R;
	volatile uint32_t RESERVED_1[8];
	volatile uint32_t CNTR;
	volatile uint32_t ISTR;
	volatile uint32_t FNR;
	volatile uint32_t DADDR;
	volatile uint32_t BTABLE;
};

struct CAN {
	volatile uint32_t CAN_MCR;
	volatile uint32_t CAN_MSR;
	volatile uint32_t CAN_TSR;
	volatile uint32_t CAN_RF0R;
	volatile uint32_t CAN_RF1R;
	volatile uint32_t CAN_IER;
	volatile uint32_t CAN_ESR;
	volatile uint32_t CAN_BTR;
	volatile uint32_t RESERVED_1[88];
	volatile uint32_t CAN_TI0R;
	volatile uint32_t CAN_TDT0R;
	volatile uint32_t CAN_TDL0R;
	volatile uint32_t CAN_TDH0R;
	volatile uint32_t CAN_TI1R;
	volatile uint32_t CAN_TDT1R;
	volatile uint32_t CAN_TDL1R;
	volatile uint32_t CAN_TDH1R;
	volatile uint32_t CAN_TI2R;
	volatile uint32_t CAN_TDT2R;
	volatile uint32_t CAN_TDL2R;
	volatile uint32_t CAN_TDH2R;
	volatile uint32_t CAN_RI0R;
	volatile uint32_t CAN_RDT0R;
	volatile uint32_t CAN_RDL0R;
	volatile uint32_t CAN_RDH0R;
	volatile uint32_t CAN_RI1R;
	volatile uint32_t CAN_RDT1R;
	volatile uint32_t CAN_RDL1R;
	volatile uint32_t CAN_RDH1R;
	volatile uint32_t RESERVED_2[12];
	volatile uint32_t CAN_FMR;
	volatile uint32_t CAN_FM1R;
	volatile uint32_t RESERVED_3;
	volatile uint32_t CAN_FS1R;
	volatile uint32_t RESERVED_4;
	volatile uint32_t CAN_FFA1R;
	volatile uint32_t RESERVED_5;
	volatile uint32_t CAN_FA1R;
	volatile uint32_t RESERVED_6[8];
	volatile uint32_t F0R1;
	volatile uint32_t F0R2;
	volatile uint32_t F1R1;
	volatile uint32_t F1R2;
	volatile uint32_t F2R1;
	volatile uint32_t F2R2;
	volatile uint32_t F3R1;
	volatile uint32_t F3R2;
	volatile uint32_t F4R1;
	volatile uint32_t F4R2;
	volatile uint32_t F5R1;
	volatile uint32_t F5R2;
	volatile uint32_t F6R1;
	volatile uint32_t F6R2;
	volatile uint32_t F7R1;
	volatile uint32_t F7R2;
	volatile uint32_t F8R1;
	volatile uint32_t F8R2;
	volatile uint32_t F9R1;
	volatile uint32_t F9R2;
	volatile uint32_t F10R1;
	volatile uint32_t F10R2;
	volatile uint32_t F11R1;
	volatile uint32_t F11R2;
	volatile uint32_t F12R1;
	volatile uint32_t F12R2;
	volatile uint32_t F13R1;
	volatile uint32_t F13R2;
};

struct BKP {
	volatile uint32_t DR1;
	volatile uint32_t DR2;
	volatile uint32_t DR3;
	volatile uint32_t DR4;
	volatile uint32_t DR5;
	volatile uint32_t DR6;
	volatile uint32_t DR7;
	volatile uint32_t DR8;
	volatile uint32_t DR9;
	volatile uint32_t DR10;
	volatile uint32_t RTCCR;
	volatile uint32_t CR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED_1[2];
	volatile uint32_t DR11;
	volatile uint32_t DR12;
	volatile uint32_t DR13;
	volatile uint32_t DR14;
	volatile uint32_t DR15;
	volatile uint32_t DR16;
	volatile uint32_t DR17;
	volatile uint32_t DR18;
	volatile uint32_t DR19;
	volatile uint32_t DR20;
	volatile uint32_t DR21;
	volatile uint32_t DR22;
	volatile uint32_t DR23;
	volatile uint32_t DR24;
	volatile uint32_t DR25;
	volatile uint32_t DR26;
	volatile uint32_t DR27;
	volatile uint32_t DR28;
	volatile uint32_t DR29;
	volatile uint32_t DR30;
	volatile uint32_t DR31;
	volatile uint32_t DR32;
	volatile uint32_t DR33;
	volatile uint32_t DR34;
	volatile uint32_t DR35;
	volatile uint32_t DR36;
	volatile uint32_t DR37;
	volatile uint32_t DR38;
	volatile uint32_t DR39;
	volatile uint32_t DR40;
	volatile uint32_t DR41;
	volatile uint32_t DR42;
};

struct PWR {
	volatile uint32_t CR;
	volatile uint32_t CSR;
};

struct AFIO {
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED_1;
	volatile uint32_t MAPR2;
};

struct EXTI {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
};

struct GPIO {
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
};

struct ADC {
	volatile uint32_t SR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMPR1;
	volatile uint32_t SMPR2;
	volatile uint32_t JOFR1;
	volatile uint32_t JOFR2;
	volatile uint32_t JOFR3;
	volatile uint32_t JOFR4;
	volatile uint32_t HTR;
	volatile uint32_t LTR;
	volatile uint32_t SQR1;
	volatile uint32_t SQR2;
	volatile uint32_t SQR3;
	volatile uint32_t JSQR;
	volatile uint32_t JDR1;
	volatile uint32_t JDR2;
	volatile uint32_t JDR3;
	volatile uint32_t JDR4;
	volatile uint32_t DR;
};

struct TIM {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
};

struct DMA {
	volatile uint32_t ISR;
	volatile uint32_t IFCR;
	volatile uint32_t CCR1;
	volatile uint32_t CNDTR1;
	volatile uint32_t CPAR1;
	volatile uint32_t CMAR1;
	volatile uint32_t RESERVED_1;
	volatile uint32_t CCR2;
	volatile uint32_t CNDTR2;
	volatile uint32_t CPAR2;
	volatile uint32_t CMAR2;
	volatile uint32_t RESERVED_2;
	volatile uint32_t CCR3;
	volatile uint32_t CNDTR3;
	volatile uint32_t CPAR3;
	volatile uint32_t CMAR3;
	volatile uint32_t RESERVED_3;
	volatile uint32_t CCR4;
	volatile uint32_t CNDTR4;
	volatile uint32_t CPAR4;
	volatile uint32_t CMAR4;
	volatile uint32_t RESERVED_4;
	volatile uint32_t CCR5;
	volatile uint32_t CNDTR5;
	volatile uint32_t CPAR5;
	volatile uint32_t CMAR5;
	volatile uint32_t RESERVED_5;
	volatile uint32_t CCR6;
	volatile uint32_t CNDTR6;
	volatile uint32_t CPAR6;
	volatile uint32_t CMAR6;
	volatile uint32_t RESERVED_6;
	volatile uint32_t CCR7;
	volatile uint32_t CNDTR7;
	volatile uint32_t CPAR7;
	volatile uint32_t CMAR7;
};

struct RCC {
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
};

struct FLASH {
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t AR;
	volatile uint32_t RESERVED_1;
	volatile uint32_t OBR;
	volatile uint32_t WRPR;
};

struct CRC {
	volatile uint32_t DR;
	volatile uint32_t IDR;
	volatile uint32_t CR;
};

struct NVIC {
	volatile uint32_t RESERVED_1;
	volatile uint32_t ICTR;
	volatile uint32_t RESERVED_2[62];
	volatile uint32_t ISER0;
	volatile uint32_t ISER1;
	volatile uint32_t RESERVED_3[30];
	volatile uint32_t ICER0;
	volatile uint32_t ICER1;
	volatile uint32_t RESERVED_4[30];
	volatile uint32_t ISPR0;
	volatile uint32_t ISPR1;
	volatile uint32_t RESERVED_5[30];
	volatile uint32_t ICPR0;
	volatile uint32_t ICPR1;
	volatile uint32_t RESERVED_6[30];
	volatile uint32_t IABR0;
	volatile uint32_t IABR1;
	volatile uint32_t RESERVED_7[62];
	volatile uint32_t IPR0;
	volatile uint32_t IPR1;
	volatile uint32_t IPR2;
	volatile uint32_t IPR3;
	volatile uint32_t IPR4;
	volatile uint32_t IPR5;
	volatile uint32_t IPR6;
	volatile uint32_t IPR7;
	volatile uint32_t IPR8;
	volatile uint32_t IPR9;
	volatile uint32_t IPR10;
	volatile uint32_t IPR11;
	volatile uint32_t IPR12;
	volatile uint32_t IPR13;
	volatile uint32_t IPR14;
	volatile uint32_t RESERVED_8[689];
	volatile uint32_t STIR;
};

struct STK {
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
};

struct SCB {
	volatile uint32_t CPUID;
	volatile uint32_t ICSR;
	volatile uint32_t VTOR;
	volatile uint32_t AIRCR;
	volatile uint32_t SCR;
	volatile uint32_t CCR;
	volatile uint32_t SHPR1;
	volatile uint32_t SHPR2;
	volatile uint32_t SHPR3;
	volatile uint32_t SHCRS;
	volatile uint32_t CFSR;
	volatile uint32_t HFSR;
	volatile uint32_t RESERVED_1;
	volatile uint32_t MMAR;
	volatile uint32_t BFAR;
};

struct DBG {
	volatile uint32_t IDCODE;
	volatile uint32_t CR;
};

#define SIG           ((struct SIG *)   0x1FFFF7E0)
#define TIM2          ((struct TIM *)   0x40000000)
#define TIM3          ((struct TIM *)   0x40000400)
#define TIM4          ((struct TIM *)   0x40000800)
#define RTC           ((struct RTC *)   0x40002800)
#define WWDG          ((struct WWDG *)  0x40002C00)
#define IWDG          ((struct IWDG *)  0x40003000)
#define SPI2          ((struct SPI *)   0x40003800)
#define USART2        ((struct USART *) 0x40004400)
#define USART3        ((struct USART *) 0x40004800)
#define I2C1          ((struct I2C *)   0x40005400)
#define I2C2          ((struct I2C *)   0x40005800)
#define USB           ((struct USB *)   0x40005C00)
#define CAN1          ((struct CAN *)   0x40006400)
#define BKP           ((struct BKP *)   0x40006C00)
#define PWR           ((struct PWR *)   0x40007000)
#define AFIO          ((struct AFIO *)  0x40010000)
#define EXTI          ((struct EXIT *)  0x40010400)
#define GPIOA         ((struct GPIO *)  0x40010800)
#define GPIOB         ((struct GPIO *)  0x40010C00)
#define GPIOC         ((struct GPIO *)  0x40011000)
#define GPIOD         ((struct GPIO *)  0x40011400)
#define ADC1          ((struct ADC *)   0x40012400)
#define ADC2          ((struct ADC *)   0x40012800)
#define TIM1          ((struct TIM *)   0x40012C00)
#define SPI1          ((struct SPI *)   0x40013000)
#define USART1        ((struct USART *) 0x40013800)
#define DMA1          ((struct DMA *)   0x40020000)
#define RCC           ((struct RCC *)   0x40021000)
#define FLASH         ((struct FLASH *) 0x40022000)
#define CRC           ((struct DRC *)   0x40023000)
#define NVIC          ((struct NVIC *)  0xE000E000)
#define STK           ((struct STK *)   0xE000E010)
#define SCB           ((struct SCB *)   0xE000ED00)
#define DBG           ((struct DBG *)   0xE0042000)

struct TIM_BB {
	volatile uint32_t CR1[32];
	volatile uint32_t CR2[32];
	volatile uint32_t SMCR[32];
	volatile uint32_t DIER[32];
	volatile uint32_t SR[32];
	volatile uint32_t EGR[32];
	volatile uint32_t CCMR1[32];
	volatile uint32_t CCMR2[32];
	volatile uint32_t CCER[32];
	volatile uint32_t CNT[32];
	volatile uint32_t PSC[32];
	volatile uint32_t ARR[32];
	volatile uint32_t RESERVED_1[32];
	volatile uint32_t CCR1[32];
	volatile uint32_t CCR2[32];
	volatile uint32_t CCR3[32];
	volatile uint32_t CCR4[32];
	volatile uint32_t RESERVED_2[32];
	volatile uint32_t DCR[32];
	volatile uint32_t DMAR[32];
};

struct RTC_BB {
	volatile uint32_t CRH[32];
	volatile uint32_t CRL[32];
	volatile uint32_t PRLH[32];
	volatile uint32_t PRLL[32];
	volatile uint32_t DIVH[32];
	volatile uint32_t DIVL[32];
	volatile uint32_t CNTH[32];
	volatile uint32_t CNTL[32];
	volatile uint32_t ALRH[32];
	volatile uint32_t ALRL[32];
};

struct WWDG_BB {
	volatile uint32_t CR[32];
	volatile uint32_t CFR[32];
	volatile uint32_t SR[32];
};

struct IWDG_BB {
	volatile uint32_t KR[32];
	volatile uint32_t PR[32];
	volatile uint32_t RLR[32];
	volatile uint32_t SR[32];
};

struct SPI_BB {
	volatile uint32_t CR1[32];
	volatile uint32_t CR2[32];
	volatile uint32_t SR[32];
	volatile uint32_t DR[32];
	volatile uint32_t CRCPR[32];
	volatile uint32_t RXCRCR[32];
	volatile uint32_t TXCRCR[32];
	volatile uint32_t I2SCFGR[32];
	volatile uint32_t I2SPR[32];
};

struct USART_BB {
	volatile uint32_t SR[32];
	volatile uint32_t DR[32];
	volatile uint32_t BRR[32];
	volatile uint32_t CR1[32];
	volatile uint32_t CR2[32];
	volatile uint32_t CR3[32];
	volatile uint32_t GTPR[32];
};

struct I2C_BB {
	volatile uint32_t CR1[32];
	volatile uint32_t CR2[32];
	volatile uint32_t OAR1[32];
	volatile uint32_t OAR2[32];
	volatile uint32_t DR[32];
	volatile uint32_t SR1[32];
	volatile uint32_t SR2[32];
	volatile uint32_t CCR[32];
	volatile uint32_t TRISE[32];
};

struct USB_BB {
	volatile uint32_t EP0R[32];
	volatile uint32_t EP1R[32];
	volatile uint32_t EP2R[32];
	volatile uint32_t EP3R[32];
	volatile uint32_t EP4R[32];
	volatile uint32_t EP5R[32];
	volatile uint32_t EP6R[32];
	volatile uint32_t EP7R[32];
	volatile uint32_t RESERVED_1[8][32];
	volatile uint32_t CNTR[32];
	volatile uint32_t ISTR[32];
	volatile uint32_t FNR[32];
	volatile uint32_t DADDR[32];
	volatile uint32_t BTABLE[32];
};

struct CAN_BB {
	volatile uint32_t CAN_MCR[32];
	volatile uint32_t CAN_MSR[32];
	volatile uint32_t CAN_TSR[32];
	volatile uint32_t CAN_RF0R[32];
	volatile uint32_t CAN_RF1R[32];
	volatile uint32_t CAN_IER[32];
	volatile uint32_t CAN_ESR[32];
	volatile uint32_t CAN_BTR[32];
	volatile uint32_t RESERVED_1[88][32];
	volatile uint32_t CAN_TI0R[32];
	volatile uint32_t CAN_TDT0R[32];
	volatile uint32_t CAN_TDL0R[32];
	volatile uint32_t CAN_TDH0R[32];
	volatile uint32_t CAN_TI1R[32];
	volatile uint32_t CAN_TDT1R[32];
	volatile uint32_t CAN_TDL1R[32];
	volatile uint32_t CAN_TDH1R[32];
	volatile uint32_t CAN_TI2R[32];
	volatile uint32_t CAN_TDT2R[32];
	volatile uint32_t CAN_TDL2R[32];
	volatile uint32_t CAN_TDH2R[32];
	volatile uint32_t CAN_RI0R[32];
	volatile uint32_t CAN_RDT0R[32];
	volatile uint32_t CAN_RDL0R[32];
	volatile uint32_t CAN_RDH0R[32];
	volatile uint32_t CAN_RI1R[32];
	volatile uint32_t CAN_RDT1R[32];
	volatile uint32_t CAN_RDL1R[32];
	volatile uint32_t CAN_RDH1R[32];
	volatile uint32_t RESERVED_2[12][32];
	volatile uint32_t CAN_FMR[32];
	volatile uint32_t CAN_FM1R[32];
	volatile uint32_t RESERVED_3[32];
	volatile uint32_t CAN_FS1R[32];
	volatile uint32_t RESERVED_4[32];
	volatile uint32_t CAN_FFA1R[32];
	volatile uint32_t RESERVED_5[32];
	volatile uint32_t CAN_FA1R[32];
	volatile uint32_t RESERVED_6[8][32];
	volatile uint32_t F0R1[32];
	volatile uint32_t F0R2[32];
	volatile uint32_t F1R1[32];
	volatile uint32_t F1R2[32];
	volatile uint32_t F2R1[32];
	volatile uint32_t F2R2[32];
	volatile uint32_t F3R1[32];
	volatile uint32_t F3R2[32];
	volatile uint32_t F4R1[32];
	volatile uint32_t F4R2[32];
	volatile uint32_t F5R1[32];
	volatile uint32_t F5R2[32];
	volatile uint32_t F6R1[32];
	volatile uint32_t F6R2[32];
	volatile uint32_t F7R1[32];
	volatile uint32_t F7R2[32];
	volatile uint32_t F8R1[32];
	volatile uint32_t F8R2[32];
	volatile uint32_t F9R1[32];
	volatile uint32_t F9R2[32];
	volatile uint32_t F10R1[32];
	volatile uint32_t F10R2[32];
	volatile uint32_t F11R1[32];
	volatile uint32_t F11R2[32];
	volatile uint32_t F12R1[32];
	volatile uint32_t F12R2[32];
	volatile uint32_t F13R1[32];
	volatile uint32_t F13R2[32];
};

struct  BKP_BB {
	volatile uint32_t DR1[32];
	volatile uint32_t DR2[32];
	volatile uint32_t DR3[32];
	volatile uint32_t DR4[32];
	volatile uint32_t DR5[32];
	volatile uint32_t DR6[32];
	volatile uint32_t DR7[32];
	volatile uint32_t DR8[32];
	volatile uint32_t DR9[32];
	volatile uint32_t DR10[32];
	volatile uint32_t RTCCR[32];
	volatile uint32_t CR[32];
	volatile uint32_t CSR[32];
	volatile uint32_t RESERVED_1[2][32];
	volatile uint32_t DR11[32];
	volatile uint32_t DR12[32];
	volatile uint32_t DR13[32];
	volatile uint32_t DR14[32];
	volatile uint32_t DR15[32];
	volatile uint32_t DR16[32];
	volatile uint32_t DR17[32];
	volatile uint32_t DR18[32];
	volatile uint32_t DR19[32];
	volatile uint32_t DR20[32];
	volatile uint32_t DR21[32];
	volatile uint32_t DR22[32];
	volatile uint32_t DR23[32];
	volatile uint32_t DR24[32];
	volatile uint32_t DR25[32];
	volatile uint32_t DR26[32];
	volatile uint32_t DR27[32];
	volatile uint32_t DR28[32];
	volatile uint32_t DR29[32];
	volatile uint32_t DR30[32];
	volatile uint32_t DR31[32];
	volatile uint32_t DR32[32];
	volatile uint32_t DR33[32];
	volatile uint32_t DR34[32];
	volatile uint32_t DR35[32];
	volatile uint32_t DR36[32];
	volatile uint32_t DR37[32];
	volatile uint32_t DR38[32];
	volatile uint32_t DR39[32];
	volatile uint32_t DR40[32];
	volatile uint32_t DR41[32];
	volatile uint32_t DR42[32];
};

struct PWR_BB {
	volatile uint32_t CR[32];
	volatile uint32_t CSR[32];
};

struct AFIO_BB {
	volatile uint32_t EVCR[32];
	volatile uint32_t MAPR[32];
	volatile uint32_t EXTICR1[32];
	volatile uint32_t EXTICR2[32];
	volatile uint32_t EXTICR3[32];
	volatile uint32_t EXTICR4[32];
	volatile uint32_t RESERVED_1[32];
	volatile uint32_t MAPR2[32];
};

struct EXTI_BB {
	volatile uint32_t IMR[32];
	volatile uint32_t EMR[32];
	volatile uint32_t RTSR[32];
	volatile uint32_t FTSR[32];
	volatile uint32_t SWIER[32];
	volatile uint32_t PR[32];
};

struct GPIO_BB {
	volatile uint32_t CRL[32];
	volatile uint32_t CRH[32];
	volatile uint32_t IDR[32];
	volatile uint32_t ODR[32];
	volatile uint32_t BSRR[32];
	volatile uint32_t BRR[32];
	volatile uint32_t LCKR[32];
};

struct ADC_BB {
	volatile uint32_t SR[32];
	volatile uint32_t CR1[32];
	volatile uint32_t CR2[32];
	volatile uint32_t SMPR1[32];
	volatile uint32_t SMPR2[32];
	volatile uint32_t JOFR1[32];
	volatile uint32_t JOFR2[32];
	volatile uint32_t JOFR3[32];
	volatile uint32_t JOFR4[32];
	volatile uint32_t HTR[32];
	volatile uint32_t LTR[32];
	volatile uint32_t SQR1[32];
	volatile uint32_t SQR2[32];
	volatile uint32_t SQR3[32];
	volatile uint32_t JSQR[32];
	volatile uint32_t JDR1[32];
	volatile uint32_t JDR2[32];
	volatile uint32_t JDR3[32];
	volatile uint32_t JDR4[32];
	volatile uint32_t DR[32];
};

struct DMA_BB {
	volatile uint32_t ISR[32];
	volatile uint32_t IFCR[32];
	volatile uint32_t CCR1[32];
	volatile uint32_t CNDTR1[32];
	volatile uint32_t CPAR1[32];
	volatile uint32_t CMAR1[32];
	volatile uint32_t RESERVED_1[32];
	volatile uint32_t CCR2[32];
	volatile uint32_t CNDTR2[32];
	volatile uint32_t CPAR2[32];
	volatile uint32_t CMAR2[32];
	volatile uint32_t RESERVED_2[32];
	volatile uint32_t CCR3[32];
	volatile uint32_t CNDTR3[32];
	volatile uint32_t CPAR3[32];
	volatile uint32_t CMAR3[32];
	volatile uint32_t RESERVED_3[32];
	volatile uint32_t CCR4[32];
	volatile uint32_t CNDTR4[32];
	volatile uint32_t CPAR4[32];
	volatile uint32_t CMAR4[32];
	volatile uint32_t RESERVED_4[32];
	volatile uint32_t CCR5[32];
	volatile uint32_t CNDTR5[32];
	volatile uint32_t CPAR5[32];
	volatile uint32_t CMAR5[32];
	volatile uint32_t RESERVED_5[32];
	volatile uint32_t CCR6[32];
	volatile uint32_t CNDTR6[32];
	volatile uint32_t CPAR6[32];
	volatile uint32_t CMAR6[32];
	volatile uint32_t RESERVED_6[32];
	volatile uint32_t CCR7[32];
	volatile uint32_t CNDTR7[32];
	volatile uint32_t CPAR7[32];
	volatile uint32_t CMAR7[32];
};

struct RCC_BB {
	volatile uint32_t CR[32];
	volatile uint32_t CFGR[32];
	volatile uint32_t CIR[32];
	volatile uint32_t APB2RSTR[32];
	volatile uint32_t APB1RSTR[32];
	volatile uint32_t AHBENR[32];
	volatile uint32_t APB2ENR[32];
	volatile uint32_t APB1ENR[32];
	volatile uint32_t BDCR[32];
	volatile uint32_t CSR[32];
};

struct FLASH_BB {
	volatile uint32_t ACR[32];
	volatile uint32_t KEYR[32];
	volatile uint32_t OPTKEYR[32];
	volatile uint32_t SR[32];
	volatile uint32_t CR[32];
	volatile uint32_t AR[32];
	volatile uint32_t RESERVED_1[32];
	volatile uint32_t OBR[32];
	volatile uint32_t WRPR[32];
};

struct CRC_BB {
	volatile uint32_t DR[32];
	volatile uint32_t IDR[32];
	volatile uint32_t CR[32];
};

#define TIM2_BB          ((struct TIM_BB *)   0x42000000)
#define TIM3_BB          ((struct TIM_BB *)   0x42008000)
#define TIM4_BB          ((struct TIM_BB *)   0x42010000)
#define RTC_BB           ((struct RTC_BB *)   0x42050000)
#define WWDG_BB          ((struct WDG_BB *)   0x42058000)
#define IWDG_BB          ((struct IWDG_BB *)  0x42060000)
#define SPI2_BB          ((struct SPI_BB *)   0x42070000)
#define USART2_BB        ((struct USART_BB *) 0x42088000)
#define USART3_BB        ((struct USART_BB *) 0x42090000)
#define I2C1_BB          ((struct I2C_BB *)   0x420A8000)
#define I2C2_BB          ((struct I2C_BB *)   0x420B0000)
#define USB_BB           ((struct USB_BB *)   0x420B8000)
#define CAN1_BB          ((struct CAN_BB *)   0x420C8000)
#define BKP_BB           ((struct PKB_BB *)   0x420D8000)
#define PWR_BB           ((struct PWR_BB *)   0x420E0000)
#define AFIO_BB          ((struct AFIO_BB *)  0x42200000)
#define EXTI_BB          ((struct EXTI_BB *)  0x42208000)
#define GPIOA_BB         ((struct GPIO_BB *)  0x42210000)
#define GPIOB_BB         ((struct GPIO_BB *)  0x42218000)
#define GPIOC_BB         ((struct GPIO_BB *)  0x42220000)
#define GPIOD_BB         ((struct GPIO_BB *)  0x42228000)
#define ADC1_BB          ((struct ADC_BB *)   0x42248000)
#define ADC2_BB          ((struct ADC_BB *)   0x42250000)
#define TIM1_BB          ((struct TIM_BB *)   0x42258000)
#define SPI1_BB          ((struct SPI_BB *)   0x42260000)
#define USART1_BB        ((struct USART_BB *) 0x42270000)
#define DMA1_BB          ((struct DMA_BB *)   0x42400000)
#define RCC_BB           ((struct RCC_BB *)   0x42420000)
#define FLASH_BB         ((struct FLASH_BB *) 0x42440000)
#define CRC_BB           ((struct CRC_BB *)   0x42460000)

#endif
