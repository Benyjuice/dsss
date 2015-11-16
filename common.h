#ifndef COMMON_H
#define COMMON_H
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "sys/types.h"
extern "C" {
typedef enum {
    IDLE,
    SYNCD,
    CAPTURED,
    OTHER,
    DEFAULT
} recv_status_t;


int searchLFMSync(const double *data, int len);

void despread(const double *data, int len);

void process_line(const double *data,int len);

}

#endif // COMMON_H

