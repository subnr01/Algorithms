#ifndef _NO_ECODE_H
#define _NO_ECODE_H

#include <ureg.h>

void DE_wrapper();
void DB_wrapper();
void BP_wrapper();
void OF_wrapper();
void BR_wrapper();
void UD_wrapper();
void NM_wrapper();
void MF_wrapper();
void MC_wrapper();
void XF_wrapper();

void DE_handler(ureg_t context);

#endif // for #ifndef _NO_ECODE_H
