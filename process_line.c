#include "common.h"
#include "dsss-global.h"

void process_line(const double *data,int len)
{
    /*
    * entry of data process
    */

    if (len <= 0) {
        return;
    }
    // searching for lfw sync

    int pos;
    int ret;
    switch (gGetStatus()) {
    case IDLE:

        pos = searchLFMSync(data,len);
        if (pos < 0) // no SYNC found
            return;

        gSetStatus(SYNCD);

        ret = gFillRecvBuffer(data+pos,len-pos);
        if (ret < 0) // buffer not full
            return;

        gSetStatus(IDLE);
        despread(gGetRecvBufferHandle(),gGetRecvBufferSize());

        process_line(data+pos+ret, len-pos-ret);
        break;

    case SYNCD:
        ret = gFillRecvBuffer(data+pos,len-pos);
        if (ret < 0) // buffer not full
            return;

        gSetStatus(IDLE);
        despread(gGetRecvBufferHandle(),gGetRecvBufferSize());

        process_line(data+pos+ret, len-pos-ret);
    default:
        break;
    }

}
