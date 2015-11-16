#include "dsss-global.h"

//static uint16_t mtu=HW_MTU;
//static uint16_t ssf=HW_SSF;
//static double   ptc=HW_PTC;
//static uint16_t sfs=HW_SFS;
//static uint16_t pnt=HW_PNT;
static recv_status_t status=DEFAULT;


// efficient signal data buffer
// buffer size = HW_PNT*HW_MTU*HW_SSF*2
static double signalRecv[HW_PNT*HW_MTU*HW_SSF];

#define LFM_LENGTH  400
static double localLFM[LFM_LENGTH]={0.0f};

/*cannot set global*/
void gSetHW_MTU(u_int16_t mtu){return;}
void gSetHW_SSF(u_int16_t ssf){return;}
void gSetHW_PTC(double ptc){return;}
void gSetHW_SPS(u_int16_t sfs){return;}
void gSetHW_PNT(u_int16_t pnt){return;}

recv_status_t gGetStatus()
{
    return status;
}

void gSetStatus(recv_status_t nextStatus)
{
    status = nextStatus;
}

double *gGetRecvBufferHandle()
{
    return signalRecv;
}


static int head=0;
int gFillRecvBuffer(const double *data, u_int16_t len)
{
    /*
    * copy data's data to signalRecvBuffer,return the size that copied
    * if buffer is full,return the size that copied
    * if buffer not full,return -1
    */

    if (head+len >= gGetRecvBufferSize() ) {
        len = gGetRecvBufferSize()-head;

        //TODO chage it to arm_cpy()
        memcpy(signalRecv+head,data,len*sizeof(double));
        head = 0;
        return len;
    }

    memcpy(signalRecv+head,data,len*sizeof(double));
    head += len;
    return -1;
}

void gClearRecvBuffer()
{
    head = 0;
}

double *getLocalLFMHandle()
{
    return localLFM;
}

int gGetLocalLFMLength()
{
    return LFM_LENGTH;
}
