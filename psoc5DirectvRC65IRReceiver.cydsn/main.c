/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include "RC65X.h"

char * keyLabel(uint16_t v) {
    switch (v) {
        // case RC65X_KEYTVINPUT:           return "KEYTVINPUT";   break;
        case RC65X_KEYPWR:               return "KEYPWR";       break;
        // case RC65X_KEYON:                return "KEYON";        break;
        case RC65X_KEYFORMAT:            return "KEYFORMAT";    break;
        // case RC65X_KEYOFF:               return "KEYOFF";       break;
        case RC65X_KEYPREVIOUS:          return "KEYPREVIOUS";  break;
        case RC65X_KEYREPLAY:            return "KEYREPLAY";    break;
        case RC65X_KEYSTOP:              return "KEYSTOP";      break;
        case RC65X_KEYADVANCE:           return "KEYADVANCE";   break;
        case RC65X_KEYNEXT:              return "KEYNEXT";      break;
        case RC65X_KEYPLAY:              return "KEYPLAY";      break;
        case RC65X_KEYPAUSE:             return "KEYPAUSE";     break;
        case RC65X_KEYRECORD:            return "KEYRECORD";    break;
        case RC65X_KEYGUIDE:             return "KEYGUIDE";     break;
        case RC65X_KEYACTIVE:            return "KEYACTIVE";    break;
        case RC65X_KEYLIST:              return "KEYLIST";      break;
        case RC65X_KEYEXIT:              return "KEYEXIT";      break;
        case RC65X_KEYUP:                return "KEYUP";        break;
        case RC65X_KEYRIGHT:             return "KEYRIGHT";     break;
        case RC65X_KEYDOWN:              return "KEYDOWN";      break;
        case RC65X_KEYLEFT:              return "KEYLEFT";      break;
        case RC65X_KEYSELECT:            return "KEYSELECT";    break;
        // case RC65X_KEYSELECT_UP:         return "KEYSELECT";    break;
        case RC65X_KEYBACK:              return "KEYBACK";      break;
        case RC65X_KEYMENU:              return "KEYMENU";      break;
        case RC65X_KEYINFO:              return "KEYINFO";      break;
        case RC65X_KEYRED:               return "KEYRED";       break;
        case RC65X_KEYGREEN:             return "KEYGREEN";     break;
        case RC65X_KEYYELLOW:            return "KEYYELLOW";    break;
        case RC65X_KEYBLUE:              return "KEYBLUE";      break;
        // case RC65X_KEYVOLUMEUP:       return "KEYVOLUMEUP";  break;
        // case RC65X_KEYVOLUMEDOWN:     return "KEYVOLUMEDOWN";break;
        case RC65X_KEYCHANUP:            return "KEYCHANUP";    break;
        case RC65X_KEYCHANDOWN:          return "KEYCHANDOWN";  break;
        // case RC65X_KEYMUTE:           return "KEYMUTE";      break;
        case RC65X_KEYPREV:              return "KEYPREV";      break;
        case RC65X_KEY1:                 return "KEY1";         break;
        case RC65X_KEY2:                 return "KEY2";         break;
        case RC65X_KEY3:                 return "KEY3";         break;
        case RC65X_KEY4:                 return "KEY4";         break;
        case RC65X_KEY5:                 return "KEY5";         break;
        case RC65X_KEY6:                 return "KEY6";         break;
        case RC65X_KEY7:                 return "KEY7";         break;
        case RC65X_KEY8:                 return "KEY8";         break;
        case RC65X_KEY9:                 return "KEY9";         break;
        case RC65X_KEYDASH:              return "KEYDASH";      break;
        case RC65X_KEY0:                 return "KEY0";         break;
        case RC65X_KEYENTER:             return "KEYENTER";     break;
    }
    return ""; // could be the default buttons for tv only or junk
}

void isr_IR_Handler() {
    char buf[20],label[20];
    uint16_t v = DecoderShiftReg_ReadRegValue();
    strcpy(label,keyLabel(v));
    //if (strlen(label)) {
        sprintf(buf,"0x%04X %s\r\n",v,label);
        UART_PutString(buf);
    //}
    DecoderShiftReg_WriteRegValue(0x00);
    IRDurationTimer_ReadStatusRegister(); // clears interrupt
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    DecoderShiftReg_Start();
    IRDurationTimer_Start();
    UART_Start();
       
    UART_PutString("\r\n\r\ndirectv main\r\n");
    
    isr_IR_StartEx(isr_IR_Handler);
    for (;;) {
    };
}
