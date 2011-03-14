#ifndef omap3_h
#define omap3_h
/*******************************************************************************
lpc210xh - Register defs for Philips LPC210X: LPC2104, LPC2105 and LPC2106

           
THE SOFTWARE IS DELIVERED "AS IS" WITHOUT WARRANTY OR CONDITION OF ANY KIND, 
EITHER EXPRESS, IMPLIED OR STATUTORY. THIS INCLUDES WITHOUT LIMITATION ANY 
WARRANTY OR CONDITION WITH RESPECT TO MERCHANTABILITY OR FITNESS FOR ANY 
PARTICULAR PURPOSE, OR AGAINST THE INFRINGEMENTS OF INTELLECTUAL PROPERTY RIGHTS 
OF OTHERS.
           
This file may be freely used for commercial and non-commercial applications, 
including being redistributed with any tools.

If you find a problem with the file, please report it so that it can be fixed.

Created by Sten Larsson (sten_larsson at yahoo com)

Edited by Richard Barry.
*******************************************************************************/

/* GPIO Structure */
struct gpio{
	unsigned char res1[0x34];	//reserve 34bytes
	unsigned int oe; 		//offset 0x34
	unsigned int datain;		//offset 0x38
	unsigned char res2[0x54];	//reserver 0x54bytes -> up to 0x8C
	unsigned int cleardataout;	//offset 0x90
	unsigned int setdataout;	//offset 0x94
};

#define REG32 (volatile unsigned int*)


/*##############################################################################
## MISC
##############################################################################*/

        /* Constants for data to put in IRQ/FIQ Exception Vectors */
#define VECTDATA_IRQ  0xE51FFFF0 /* LDR PC,[PC,#-0xFF0 */
#define VECTDATA_FIQ  /* __TODO */
#define QUARTER_SIZE               0x40000000

#define QUARTER0                   0x00000000

#define QUARTER1                   0x40000000
#define Q1_ON_CHIP_MEMORY            0x40000000
#define Q1_ON_CHIP_MEMORY_SIZE       0x08000000
#define Q1_OCM_BOOT_ROM_SECURE         0x40000000
#define Q1_OCM_BOOT_ROM_SECURE_SIZE    0x00014000
#define Q1_OCM_BOOT_ROM_PUBLIC         0x40014000
#define Q1_OCM_BOOT_ROM_PUBLIC_SIZE    0x00008000
#define Q1_OCM_RESERVED1               0x4001c000
#define Q1_OCM_RESERVED1_SIZE          0x001e4000
#define Q1_OCM_SRAM_INTERNAL           0x40200000
#define Q1_OCM_SRAM_INTERNAL_SIZE      0x00010000
#define Q1_OCM_RESERVED2               0x40210000
#define Q1_OCM_RESERVED2_SIZE          0x07df0000
#define Q1_L4_INTERCONNECT           0x48000000
#define Q1_L4_INTERCONNECT_SIZE      0x08000000
#define Q1_L4_INT_CORE                 0x48000000
#define Q1_L4_INT_CORE_SIZE            0x01000000
#define SYS_CONTROL_MODULE               0x48002000
#define SYS_CONTROL_MODULE_SIZE          0x00002000
#define CLOCK_MANAGER                    0x48004000
#define CLOCK_MANAGER_SIZE               0x00004000
#define SDMA                             0x48056000
#define SDMA_SIZE                        0x00002000
#define UART1                            0x4806a000
#define UART1_SIZE                       0x00002000
#define UART2                            0x4806c000
#define UART2_SIZE                       0x00002000
#define INTERRUPT_CONTROLLER             0x48200000
#define INTERRUPT_CONTROLLER_SIZE        0x00001000
#define L4_CORE_WAKEUP_INT               0x48300000
#define L4_CORE_WAKEUP_INT_SIZE          0x00040FFF
#define PRM                                0x48306000
#define PRM_SIZE                           0x00004000
#define GPIO1                              0x48310000
#define GPIO1_SIZE                         0x00002000
#define WDTIMER2                           0x48314000
#define WDTIMER2_SIZE                      0x00002000
#define GPTIMER1                           0x48318000
#define GPTIMER1_SIZE                      0x00002000
#define TIMER_32K                          0x48320000
#define TIMER_32K_SIZE                     0x00002000
#define Q1_L4_INT_PER                  0x49000000
#define Q1_L4_INT_PER_SIZE             0x00100000
#define UART3                            0x49020000
#define UART3_SIZE                       0x00002000
#define GPTIMER2                         0x49032000
#define GPTIMER2_SIZE                    0x00002000
#define GPIO2_BASE                       0x49050000
#define GPIO2_SIZE                       0x00002000
#define GPIO3_BASE                       0x49052000
#define GPIO3_SIZE                       0x00002000
#define GPIO4_BASE                       0x49054000
#define GPIO4_SIZE                       0x00002000
#define GPIO5_BASE                       0x49056000
#define GPIO5_SIZE                       0x00002000
#define GPIO6_BASE                       0x49058000
#define GPIO6_SIZE                       0x00002000
#define Q1_L4_INT_PER_SIZE             0x00100000
#define Q1_L4_INT_RESERVED             0x49100000
#define Q1_L4_INT_RESERVED_SIZE        0x06F00000
#define Q1_SLAVE_GRAPHICS            0x50000000
#define Q1_SLAVE_GRAPHICS_SIZE       0x04000000
#define Q1_L4_EMULATION              0x54000000
#define Q1_L4_EMULATION_SIZE         0x04000000
#define Q1_RESERVED1                 0x58000000
#define Q1_RESERVED1_SIZE            0x04000000
#define Q1_IVA22_IMMU                0x5c000000
#define Q1_IVA22_IMMU_SIZE           0x04000000
#define Q1_RESERVED2                 0x60000000
#define Q1_RESERVED2_SIZE            0x08000000
#define Q1_L3_INTERCONNECT           0x68000000
#define Q1_L3_INTERCONNECT_SIZE      0x08000000
#define Q1_L3_GPMC                     0x6E000000
#define Q1_L3_GPMC_SIZE                0x01000000
#define Q1_SDRC_SMS                  0x70000000
#define Q1_SDRC_SMS_SIZE             0x10000000

#define QUARTER2                   0x80000000
#define Q2_SDRC_SMS                  0x80000000
#define Q2_SDRC_SMS_SIZE             0x40000000

#define QUARTER3                   0xC000000
#define Q3_RESERVED                  0xC0000000
#define Q3_RESERVED_SIZE             0x20000000
#define Q3_SDRC_SMS                  0xE0000000
#define Q3_SDRC_SMS_SIZE             0x20000000




/**********************************************
 * 		GPIO Interface
 * Register definitions
 * *******************************************/

#define GPIO_REVISION            0x000

#define GPIO_SYSCONFIG           0x010
#define GPIO_SYSCONFIG_RESERVED     0xFFFFFFE0
#define GPIO_SYSCONFIG_IDLEMODE     0x00000018
#define GPIO_SYSCONFIG_ENAWAKEUP    0x00000004
#define GPIO_SYSCONFIG_SOFTRESET    0x00000002
#define GPIO_SYSCONFIG_AUTOIDLE     0x00000001

#define GPIO_SYSSTATUS           0x014
#define GPIO_SYSSTATUS_RESERVED     0xFFFFFFFE
#define GPIO_SYSSTATUS_RESETDONE    0x00000001

#define GPIO_IRQSTATUS1          0x018
#define GPIO_IRQENABLE1          0x01C
#define GPIO_WAKEUPENABLE        0x020
#define GPIO_IRQSTATUS2          0x028
#define GPIO_IRQENABLE2          0x02C

#define GPIO_CTRL                0x030
#define GPIO_CTRL_RESERVED          0xFFFFFFF8
#define GPIO_CTRL_GATERATIO         0x00000006
#define GPIO_CTRL_DISABLEMOD        0x00000001

#define GPIO_OE                  0x034
#define GPIO_DATAIN              0x038
#define GPIO_DATAOUT             0x03C
#define GPIO_LEVELDETECT0        0x040
#define GPIO_LEVELDETECT1        0x044
#define GPIO_RISINGDETECT        0x048
#define GPIO_FALLINGDETECT       0x04C
#define GPIO_DEBOUNCENABLE       0x050
#define GPIO_DEBOUNCINGTIME      0x054
#define GPIO_CLEARIRQENABLE1     0x060
#define GPIO_SETIRQENABLE1       0x064
#define GPIO_CLEARIRQENABLE2     0x070
#define GPIO_SETIRQENABLE2       0x074
#define GPIO_CLEARWKUENA         0x080
#define GPIO_SETWKUENA           0x084
#define GPIO_CLEARDATAOUT        0x090
#define GPIO_SETDATAOUT          0x094







/* define pins. I will use them for GPIO but I assume 
 * I can extent their usage for other modules as well */
#define PIN0		(0x1 << 0)
#define PIN1		(0x1 << 1)
#define PIN2		(0x1 << 2)
#define	PIN3		(0x1 << 3)
#define PIN4		(0x1 << 4)
#define PIN5		(0x1 << 5)
#define PIN6		(0x1 << 6)
#define PIN7		(0x1 << 7)
#define PIN8		(0x1 << 8)
#define PIN9		(0x1 << 9)
#define PIN10		(0x1 << 10)
#define PIN11		(0x1 << 11)
#define PIN12		(0x1 << 12)
#define PIN13		(0x1 << 13)
#define PIN14		(0x1 << 14)
#define PIN15		(0x1 << 15)
#define PIN16		(0x1 << 16)
#define PIN17		(0x1 << 17)
#define PIN18		(0x1 << 18)
#define PIN19		(0x1 << 19)
#define PIN20		(0x1 << 20)
#define PIN21		(0x1 << 21)
#define PIN22		(0x1 << 22)
#define PIN23		(0x1 << 23)
#define PIN24		(0x1 << 24)
#define PIN25		(0x1 << 25)
#define PIN26		(0x1 << 26)
#define PIN27		(0x1 << 27)
#define PIN28		(0x1 << 28)
#define PIN29		(0x1 << 29)
#define PIN30		(0x1 << 30)
#define PIN31		(0x1 << 31)














#endif /* omap3_h */
