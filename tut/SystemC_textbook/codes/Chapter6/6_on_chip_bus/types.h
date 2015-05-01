
#ifndef __types_h
#define __types_h

#include <stdio.h>
#include <systemc.h>

enum status { TRANSFER_OK = 0
			 ,TRANSFER_REQUEST
			 ,TRANSFER_WAIT
			 ,TRANSFER_ERROR};

// needed for more readable debug output
extern char status_str[4][20]; 

struct request;
typedef sc_pvector<request *> request_vec;

extern int sb_fprintf(FILE *, const char *, ...);

//Frame struct for wireless LAN
struct frame{
unsigned short frame_control;
unsigned short duration_id;
char addr1[6];
char addr2[6];
char addr3[6];
char addr4[6];
unsigned short sequence_control;
char body[2312];
unsigned fcs;

//Offset Parameters for UART port
#define STATUS_PORT 0
#define CONFIG_PORT 1
};

#endif
