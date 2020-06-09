// cstd
#include <stdbool.h>

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

/*  E - enable signal (strob)
    RS - register select 0:command 1:data
    RW - read/write 0:write 1:read
*/

/*
    have to define
    DISP_RS_PIN
    DISP_E_PIN
    DISP_D4_PIN
    DISP_D5_PIN
    DISP_D6_PIN
    DISP_D7_PIN
*/

//#define I2C_DISP            // for using i2c

void InitDisp(void);
void ClrScr(void);          // wait at least 2ms after it
void MoveToLine2(void);
void MoveTo(int x, int y);  // start (0, 0)
void MoveScreen(bool dir);  // true -> false <-
void WriteChar(char);
void WriteString(char * str, int n);
void WriteLine(char * str);

void WriteCommandNibble(uint8_t);
void WriteDataNibble(uint8_t);
void WriteCommandByte(uint8_t);
void WriteDataByte(uint8_t);

void BacklightOn(void);
void BacklightOff(void);

// japanese
#define a_ "\261"
#define i_ "\262"
#define u_ "\263"
#define e_ "\264"
#define o_ "\265"
#define ka_ "\266"
#define ki_ "\267"
#define ku_ "\270"
#define ke_ "\271"
#define ko_ "\272"
#define sa_ "\273"
#define si_ "\274"
#define su_ "\275"
#define se_ "\276"
#define so_ "\277"
#define ta_ "\300"
#define ti_ "\301"
#define tu_ "\302"
#define te_ "\303"
#define to_ "\304"
#define na_ "\305"
#define ni_ "\306"
#define nu_ "\307"
#define ne_ "\310"
#define no_ "\311"
#define ha_ "\312"
#define hi_ "\313"
#define hu_ "\314"
#define he_ "\315"
#define ho_ "\316"
#define ma_ "\317"
#define mi_ "\320"
#define mu_ "\321"
#define me_ "\322"
#define mo_ "\323"
#define ya_ "\324"
#define yu_ "\325"
#define yo_ "\326"
#define ra_ "\327"
#define ri_ "\330"
#define ru_ "\331"
#define re_ "\332"
#define ro_ "\333"
#define wa_ "\334"
#define n_ "\335"
#define nigori_ "\336"
#define long_ "\260"
#define lil_ya_ "\254"
#define lil_yu_ "\255"
#define lil_yo_ "\256"

#endif
