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

/* GP Timer Structure */
struct gptimer {
	int tidr;	/* 0x00 r */
	char res[0xc];
	int tiocp_cfg;	/* 0x10 rw */
	int tistat;	/* 0x14 r */
	int tisr;	/* 0x18 rw */
	int tier;	/* 0x1c rw */
	int twer;	/* 0x20 rw */
	int tclr;	/* 0x24 rw */
	int tcrr;	/* 0x28 rw */
	int tldr;	/* 0x2c rw */
	int ttgr;	/* 0x30 rw */
	int twpc;	/* 0x34 r*/
	int tmar;	/* 0x38 rw*/
	int tcar1;	/* 0x3c r */
	int tcicr;	/* 0x40 rw */
	int tcar2;	/* 0x44 r */
};

struct InterruptController
{
  unsigned char res1[0x10];
  unsigned int intcSysConfig;
  unsigned int intcSysStatus;
  unsigned char res2[0x28];
  unsigned int intcSirIrq; //0x40
  unsigned int intcSirFiq; //0x44
  unsigned int intcControl;//0x48
  unsigned int intcProtection;//0x4c
  unsigned int intcIdle;//0x50
  unsigned char res3[0xC];
  unsigned int intcIrqPriority;//0x60
  unsigned int intcFiqPriority;//0x64
  unsigned int intcThreshold;//0x68
  unsigned char res4[0x14];
  unsigned int intcItr0; // 0x80
  unsigned int intcMir0; //0x84
  unsigned int intcMirClear0; //0x88
  unsigned int intcMirSet0;//0x8C
  unsigned int intcIsrSet0;//0x90
  unsigned int intcIsrClear0;//0x94
  unsigned int intcPendingIrq0;//0x98
  unsigned int intcPendingFiq0;//0x9C
  unsigned int intcItr1;//0xA0
  unsigned int intcMir1;//0xA4
  unsigned int intcMirClear1;//0xA8
  unsigned int intcMirSet1;//0xAC
  unsigned int intcIsrSet1;//0xB0
  unsigned int intcIsrClear1;//0xB4
  unsigned int intcPendingIrq1;//0xB8
  unsigned int intcPendingFiq1;//0xBC
  unsigned int intcItr2;//0xC0
  unsigned int intcMir2;//0xC4
  unsigned int intcMirClear2;//0xC8
  unsigned int intcMirSet2;//0xCC
  unsigned int intcIsrSet2;//0xD0
  unsigned int intcIsrClear2;//0xD4
  unsigned int intcPendingIrq2;//0xD8
  unsigned int intcPendingFiq2; // 0xDC
  unsigned char res5[0x22];
  unsigned int intcIlr0;	// 0x100
  unsigned int intcIlr1;
  unsigned int intcIlr2;
  unsigned int intcIlr3;
  unsigned int intcIlr4;
  unsigned int intcIlr5;
  unsigned int intcIlr6;
  unsigned int intcIlr7;
  unsigned int intcIlr8;
  unsigned int intcIlr9;
  unsigned int intcIlr10;
  unsigned int intcIlr11;
  unsigned int intcIlr12;
  unsigned int intcIlr13;
  unsigned int intcIlr14;
  unsigned int intcIlr15;
  unsigned int intcIlr16;
  unsigned int intcIlr17;
  unsigned int intcIlr18;
  unsigned int intcIlr19;
  unsigned int intcIlr20;
  unsigned int intcIlr21;
  unsigned int intcIlr22;
  unsigned int intcIlr23;
  unsigned int intcIlr24;
  unsigned int intcIlr25;
  unsigned int intcIlr26;
  unsigned int intcIlr27;
  unsigned int intcIlr28;
  unsigned int intcIlr29;
  unsigned int intcIlr30;
  unsigned int intcIlr31;
  unsigned int intcIlr32;
  unsigned int intcIlr33;
  unsigned int intcIlr34;
  unsigned int intcIlr35;
  unsigned int intcIlr36;
  unsigned int intcIlr37;
  unsigned int intcIlr38;
  unsigned int intcIlr39;
  unsigned int intcIlr40;
  unsigned int intcIlr41;
  unsigned int intcIlr42;
  unsigned int intcIlr43;
  unsigned int intcIlr44;
  unsigned int intcIlr45;
  unsigned int intcIlr46;
  unsigned int intcIlr47;
  unsigned int intcIlr48;
  unsigned int intcIlr49;
  unsigned int intcIlr50;
  unsigned int intcIlr51;
  unsigned int intcIlr52;
  unsigned int intcIlr53;
  unsigned int intcIlr54;
  unsigned int intcIlr55;
  unsigned int intcIlr56;
  unsigned int intcIlr57;
  unsigned int intcIlr58;
  unsigned int intcIlr59;
  unsigned int intcIlr60;
  unsigned int intcIlr61;
  unsigned int intcIlr62;
  unsigned int intcIlr63;
  unsigned int intcIlr64;
  unsigned int intcIlr65;
  unsigned int intcIlr66;
  unsigned int intcIlr67;
  unsigned int intcIlr68;
  unsigned int intcIlr69;
  unsigned int intcIlr70;
  unsigned int intcIlr71;
  unsigned int intcIlr72;
  unsigned int intcIlr73;
  unsigned int intcIlr74;
  unsigned int intcIlr75;
  unsigned int intcIlr76;
  unsigned int intcIlr77;
  unsigned int intcIlr78;
  unsigned int intcIlr79;
  unsigned int intcIlr80;
  unsigned int intcIlr81;
  unsigned int intcIlr82;
  unsigned int intcIlr83;
  unsigned int intcIlr84;
  unsigned int intcIlr85;
  unsigned int intcIlr86;
  unsigned int intcIlr87;
  unsigned int intcIlr88;
  unsigned int intcIlr89;
  unsigned int intcIlr90;
  unsigned int intcIlr91;
  unsigned int intcIlr92;
  unsigned int intcIlr93;
  unsigned int intcIlr94;
  unsigned int intcIlr95;
};

#define REG32 (volatile unsigned int*)
#define FALSE 0
#define TRUE 1

/*##############################################################################
## MISC
##############################################################################*/


#define GPIO5_BASE	0x49056000
#define GPIO6_BASE	0x49058000
#define GPT1		0x48318000
#define MPU_INTC	0x48200000

/* Serial Configuration */
#define SERIAL_BASE     0x49020000
#define TRANSMIT_HOLDING_REG_OFFSET 0x00000000
#define LINE_STATUS_REG_OFFSET 0x00000014

#define LINE_STATUS_REG_TX_HOLD     0x20

#define LINE_FEED              0xA
#define CARRIAGE_RETURN        0xD
#define PRINTABLE_START        0x20
#define PRINTABLE_END          0x7E

void serial_putchar(char c);
void serial_putstring(char * c);
void serial_newline(void);
void serial_putlong(unsigned long nr);
void serial_putint(unsigned int nr);
void serial_putint_nozeros(unsigned int nr);
void serial_putbyte(unsigned char nr);
int printableChar(char c);


/* Default RAM Exception handlers
 * Custom Handlers So I will use 
 * secondary addresses */
#define E_UNDEFINED	(*(REG32 (0x4020FFE4)))
#define E_SWI		(*(REG32 (0x4020FFE8)))
#define E_PREFETCH	(*(REG32 (0x4020FFEC)))
#define E_DATA_ABRT	(*(REG32 (0x4020FFF0)))
#define E_UNUSED	(*(REG32 (0x4020FFF4)))
#define E_IRQ		(*(REG32 (0x4020FFF8)))
#define E_FIQ		(*(REG32 (0x4020FFFC)))


/* GPTIMER1 REGISTERS */
#define GPTI1_TIDR	(*(REG32 (0x48318000)))
#define GPTI1_TIOCP_CFG (*(REG32 (0x48318010)))
#define GPTI1_TISTAT	(*(REG32 (0x48318014)))
#define GPTI1_TISR	(*(REG32 (0x48318018)))
#define GPTI1_TIER	(*(REG32 (0x4831801C)))
#define GPTI1_TWER	(*(REG32 (0x48318020)))
#define GPTI1_TCLR	(*(REG32 (0x48318024)))
#define GPTI1_TCRR	(*(REG32 (0x48318028)))
#define GPTI1_TLDR	(*(REG32 (0x4831802C)))
#define GPTI1_TTGR	(*(REG32 (0x48318030)))
#define GPTI1_TWPS	(*(REG32 (0x48318034)))
#define GPTI1_TMAR	(*(REG32 (0x48318038)))
#define GPTI1_TCAR1	(*(REG32 (0x4831803C)))
#define GPTI1_TSICR	(*(REG32 (0x48318040)))
#define GPTI1_TCAR2	(*(REG32 (0x48318044)))
#define GPTI1_TPIR	(*(REG32 (0x48318048)))
#define GPTI1_TNIR	(*(REG32 (0x4831804C)))
#define GPTI1_TCVR	(*(REG32 (0x48318050)))
#define GPTI1_TOCR	(*(REG32 (0x48318054)))
#define GPTI1_TOWR	(*(REG32 (0x48318058)))

/* Define MPU_INTC */
#define MPU_INTC_BASE		(*(REG32 (0x48200000)))
#define INTCPS_REVISION		0x0
#define INTCPS_SYSCONFIG 	0x10
#define INTCPS_SYSSTATUS 	0x14
#define INTCPS_SIR_IRQ 		0x40
#define INTCPS_SIR_FIQ 		0x44
#define INTCPS_CONTROL		0x48
#define INTCPS_PROTECTION	0x4C
#define INTCPS_IDLE		0x50
#define INTCPS_IRQ_PRIORITY	0x60
#define INTCPS_FIQ_PRIORITY	0x64
#define INTCPS_THRESHOLD	0x68
#define INTCPS_ITR0		0x80
#define INTCPS_MIR0		0x84
#define INTCPS_MIR_CLEAR0	0x88
#define INTCPS_MIR_SET0		0x8C
#define INTCPS_ISR_SET0		0x90
#define INTCPS_ISR_CLEAR0	0x94
#define INTCPS_PENDING_IRQ0	0x98
#define INTCPS_PENDING_FIQ0	0x9C
#define INTCPS_ITR1		0xA0
#define INTCPS_MIR1		0xA4
#define INTCPS_MIR_CLEAR1	0xA8
#define INTCPS_MIR_SET1		0xAC
#define INTCPS_ISR_SET1		0xB0
#define INTCPS_ISR_CLEAR1	0xB4
#define INTCPS_PENDING_IRQ1	0xB8
#define INTCPS_PENDING_FIQ1	0xBC
#define INTCPS_ITR2		0xC0
#define INTCPS_MIR2		0xC4
#define INTCPS_MIR_CLEAR2	0xC8
#define INTCPS_MIR_SET2		0xCC
#define INTCPS_ISR_SET2		0xD0
#define INTCPS_ISR_CLEAR2	0xD4
#define INTCPS_PENDING_IRQ2	0xD8
#define INTCPS_PENDING_FIQ2	0xDc
#define INTCPS_ILSR0		0x100
#define INTCPS_ILSR1		0x104
#define INTCPS_ILSR2		0x108
#define INTCPS_ILSR3		0x10C
#define INTCPS_ILSR4		0x110
#define INTCPS_ILSR5		0x114
#define INTCPS_ILSR6		0x118
#define INTCPS_ILSR7		0x11C
#define INTCPS_ILSR8		0x120
#define INTCPS_ILSR9		0x124
#define INTCPS_ILSR10		0x128
#define INTCPS_ILSR11		0x12C
#define INTCPS_ILSR12		0x130
#define INTCPS_ILSR13		0x134
#define INTCPS_ILSR14		0x138
#define INTCPS_ILSR15		0x13C
#define INTCPS_ILSR16		0x140
#define INTCPS_ILSR17		0x144
#define INTCPS_ILSR18		0x148
#define INTCPS_ILSR19		0x14C
#define INTCPS_ILSR20		0x150
#define INTCPS_ILSR21		0x154
#define INTCPS_ILSR22		0x158
#define INTCPS_ILSR23		0x15C
#define INTCPS_ILSR24		0x160
#define INTCPS_ILSR25		0x164
#define INTCPS_ILSR26		0x168
#define INTCPS_ILSR27		0x16C
#define INTCPS_ILSR28		0x170
#define INTCPS_ILSR29		0x174
#define INTCPS_ILSR30		0x178
#define INTCPS_ILSR31		0x17C
#define INTCPS_ILSR32		0x180
#define INTCPS_ILSR33		0x184
#define INTCPS_ILSR34		0x188
#define INTCPS_ILSR35		0x18C
#define INTCPS_ILSR36		0x190
#define INTCPS_ILSR37		0x194
#define INTCPS_ILSR38		0x198
#define INTCPS_ILSR39		0x19C
#define INTCPS_ILSR40		0x1A0
#define INTCPS_ILSR41		0x1A4
#define INTCPS_ILSR42		0x1A8
#define INTCPS_ILSR43		0x1AC
#define INTCPS_ILSR44		0x1B0
#define INTCPS_ILSR45		0x1B4
#define INTCPS_ILSR46		0x1B8
#define INTCPS_ILSR47		0x1BC
#define INTCPS_ILSR48		0x1C0
#define INTCPS_ILSR49		0x1C4
#define INTCPS_ILSR50		0x1C8
#define INTCPS_ILSR51		0x1CC
#define INTCPS_ILSR52		0x1D0
#define INTCPS_ILSR53		0x1D4
#define INTCPS_ILSR54		0x1D8
#define INTCPS_ILSR55		0x1DC
#define INTCPS_ILSR56		0x1E0
#define INTCPS_ILSR57		0x1E4
#define INTCPS_ILSR58		0x1E8
#define INTCPS_ILSR59		0x1EC
#define INTCPS_ILSR60		0x1F0
#define INTCPS_ILSR61		0x1F4
#define INTCPS_ILSR62		0x1F8
#define INTCPS_ILSR63		0x1FC
#define INTCPS_ILSR64		0x200
#define INTCPS_ILSR65		0x204
#define INTCPS_ILSR66		0x208
#define INTCPS_ILSR67		0x20C
#define INTCPS_ILSR68		0x210
#define INTCPS_ILSR69		0x214
#define INTCPS_ILSR70		0x218
#define INTCPS_ILSR71		0x21C
#define INTCPS_ILSR72		0x220
#define INTCPS_ILSR73		0x224
#define INTCPS_ILSR74		0x228
#define INTCPS_ILSR75		0x22C
#define INTCPS_ILSR76		0x230
#define INTCPS_ILSR77		0x234
#define INTCPS_ILSR78		0x238
#define INTCPS_ILSR79		0x23C
#define INTCPS_ILSR80		0x240
#define INTCPS_ILSR81		0x244
#define INTCPS_ILSR82		0x248
#define INTCPS_ILSR83		0x24C
#define INTCPS_ILSR84		0x250
#define INTCPS_ILSR85		0x254
#define INTCPS_ILSR86		0x258
#define INTCPS_ILSR87		0x25C
#define INTCPS_ILSR88		0x260
#define INTCPS_ILSR89		0x264
#define INTCPS_ILSR90		0x268
#define INTCPS_ILSR91		0x26C
#define INTCPS_ILSR92		0x270
#define INTCPS_ILSR93		0x274
#define INTCPS_ILSR94		0x278
#define INTCPS_ILSR95		0x27C

/* GPIO */

#define GPIO_REVISION		0x0
#define GPIO_SYSCONFIG		0x10
#define GPIO_SYSSTATUS		0x14
#define GPIO_IRQSTATUS1		0x18
#define GPIO_IRQ_ENABLE1	0x1C
#define GPIO_WAKEUPENABLE	0x20
#define GPIO_IRQSTATUS2		0x28
#define GPIO_IRQENABLE2		0x2C
#define GPIO_CTRL		0x30
#define GPIO_OE			0x34
#define GPIO_DATAIN		0x38
#define GPIO_DATAOUT		0x3C
#define GPIO_LEVELDETECT0	0x40
#define GPIO_LEVELDETECT1	0x44
#define GPIO_RISINGDETECT	0x48
#define GPIO_FALLINGDETECT	0x4C
#define GPIO_DEBOUNCENABLE	0x50
#define GPIO_DEBOUNCEINGTIME	0x54
#define GPIO_CLEARIRQENABLE1	0x60
#define GPIO_SETIRQENABLE1	0x64
#define GPIO_CLEARIRQENABLE2	0x70
#define GPIO_SETIRQENABLE2	0x74
#define GPIO_CLEARWKUENA	0x80
#define GPIO_SETWKUENA		0x84
#define GPIO_CLEARDATAOUT	0x90
#define GPIO_SETDATAOUT		0x94



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
