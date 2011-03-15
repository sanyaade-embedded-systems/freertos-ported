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
  unsigned int intcSysConfig;
  unsigned int intcSysStatus;
  unsigned int intcSirIrq;
  unsigned int intcSirFiq;
  unsigned int intcControl;
  unsigned int intcProtection;
  unsigned int intcIdle;
  unsigned int intcIrqPriority;
  unsigned int intcFiqPriority;
  unsigned int intcThreshold;
  unsigned int intcItr0;
  unsigned int intcItr1;
  unsigned int intcItr2;
  unsigned int intcMir0;
  unsigned int intcMir1;
  unsigned int intcMir2;
  unsigned int intcMirClear0;
  unsigned int intcMirClear1;
  unsigned int intcMirClear2;
  unsigned int intcMirSet0;
  unsigned int intcMirSet1;
  unsigned int intcMirSet2;
  unsigned int intcIsrSet0;
  unsigned int intcIsrSet1;
  unsigned int intcIsrSet2;
  unsigned int intcIsrClear0;
  unsigned int intcIsrClear1;
  unsigned int intcIsrClear2;
  unsigned int intcPendingIrq0;
  unsigned int intcPendingIrq1;
  unsigned int intcPendingIrq2;
  unsigned int intcPendingFiq0;
  unsigned int intcPendingFiq1;
  unsigned int intcPendingFiq2;
  unsigned int intcIlr0;
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


/*##############################################################################
## MISC
##############################################################################*/


#define GPIO5_BASE	0x49056000
#define GPIO6_BASE	0x49058000
#define GPT1		0x48318000
#define MPU_INTC	0x48200000

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
