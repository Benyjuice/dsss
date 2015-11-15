#ifndef DSSS_GLOBAL_H
#define DSSS_GLOBAL_H
#include "common.h"
#define HW_MTU  20  //max transmit bits in hardware packet
#define HW_SSF  7    // spread-spectum factor
#define HW_PTC  0.002f// pn-code time period
#define HW_SFS  24000// receiver sample-frequenvy
#define HW_PNT  480 // points per pn-code-time-period = HW_SFS*HW_PTC

/*
 *API functions to access global variables
 */

#define  gGetRecvBufferSize() (HW_PNT*HW_MTU*HW_SSF*2)
#define  gGetHW_MTU() HW_MTU
#define  gGetHW_SSF() HW_SSF
#define  gGetHW_PTC() HW_PTC
#define  gGetHW_SFS() HW_SFS
#define  gGetHW_PNT() HW_PNT

char *gGetRecvBufferHandle();

int gFillRecvBuffer(const char *data,u_int16_t len);
void gClearRecvBuffer();

recv_status_t gGetStatus(void);

void gSetHW_MTU(u_int16_t mtu);
void gSetHW_SSF(u_int16_t ssf);
void gSetHW_PTC(double ptc);
void gSetHW_SPS(u_int16_t sfs);
void gSetHW_PNT(u_int16_t pnt);

void gSetStatus(recv_status_t nextStatus);


// local LFM
double *gGetLocalLFMHandle();
int gGetLocalLFMLength();

#endif
