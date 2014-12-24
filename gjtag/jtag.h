#ifndef __JTAG_H__
#define __JTAG_H__

#include "ppt.h"

#define LOW 			 '0'               
#define HIGH			 '1'
   

/*// Pin Connections
//   TCK   :DATA[0]   (2) 
//   TDI   :DATA[1]   (3) 
//   TMS   :DATA[2]   (4) 
//   TDO   :STATUS[7] (11)

#define TCK_H		0x01
#define TDI_H		0x40              
#define TMS_H		0x02
*/

// 2014-11-23 这是按我手里的244小板改的
// Pin Connections
//   TMS   :DATA[1]   
//   TCK   :DATA[2]   
//   TDI   :DATA[3]  
//   TDO   :STATUS[7]   // 这个不知道对不对，应该是BUSY脚,LPT1(11脚).
#define TMS_H		0x02
#define TCK_H		0x04	            
#define TDI_H		0x08 


#define TCK_L		0x00
#define TDI_L		0x00              
#define TMS_L		0x00
#define JTAG_SET(value)	OutputPpt(value)

#define JTAG_GET_TDO()	( (InputPpt()&(1<<7)) ? LOW:HIGH )  //STATUS7 is read inverted. 		


// JTAG Instruction Definition
#define EXTEST		"100"  //LSB...MSB
#define BYPASS		"111"
#define IDCODE		"001"
#define SCANN		"0100"
#define INTEST		"110"
#define SAMPLE_PRELOAD	"101"

extern int delayLoopCount;

void JTAG_ReadId(void);
void JTAG_RunTestldleState(void);
void JTAG_ShiftIRState(char *wrIR);
void JTAG_ShiftDRState(char *wrDR, char *rdDR);
void  JTAG_ShiftDRStateNoTdo(char *wrDR);
void Delay(int count);
#endif //__JTAG_H__



