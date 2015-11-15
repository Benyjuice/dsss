#ifndef COMMON_H
#define COMMON_H
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "sys/types.h"

typedef enum {
    IDLE,
    SYNCD,
    CAPTURED,
    OTHER,
    DEFAULT
} recv_status_t;


int searchLFMSync(const char *data, int len);

void despread(const char *data,int len);

#endif // COMMON_H

