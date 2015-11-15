#include "common.h"
#include "dsss-global.h"

#include "fftw3.h"
#include "qmath.h"

double averangeFftwComplex(const fftw_complex *data,int len)
{
    if (len < 0)
        return 0;

    double temp=0.0f;
    for (int i=0;i<len;i++) {
        temp+=qSqrt(data[i][0]*data[i][0]+data[i][1]*data[i][1]);
    }
    temp /= len;
    return temp;
}

void maxFftwComplex(const fftw_complex *data,int len, double *maxV, int *pos)
{
    if (len < 0)
        return 0;

    double temp,max=0.0f;
    int posTemp=0;
    for (int i=0;i<len;i++) {
        temp = Sqrt(data[i][0]*data[i][0]+data[i][1]*data[i][1]);
        if (max < temp) {
            max = temp;
            posTemp = i;
        }
    }

    *maxV = max;
    *pos = posTemp;

}

int searchLFMSync(const char *data, int len)
{
    /*
     * return -1 if no SYNC found
     * return position of signal start if found
    */

    fftw_plan p;
    fftw_complex *in1,*out1,*in2,*out2;
    u_int16_t *data1 = (u_int16_t *)data;
    u_int16_t *data2 = (u_int16_t *)gGetLocalLFMHandle();

    int len1=len;
    int len2=gGetLocalLFMLength();
    unsigned int fftLen = len1+len2;

    // 2^(nextpow(fftLen))
    fftLen--;
    fftLen |= fftLen >> 1;
    fftLen |= fftLen >> 2;
    fftLen |= fftLen >> 4;
    fftLen |= fftLen >> 8;
    fftLen |= fftLen >> 16;
    fftLen++;

    if (fftLen > 65536) {
        printf("too large of data length\n");
        return;
    }

    // malloc memory
    in1 = fftw_malloc(sizeof(fftw_complex) * fftLen);
    in2 = fftw_malloc(sizeof(fftw_complex) * fftLen);
    out1 = fftw_malloc(sizeof(fftw_complex) * fftLen);
    out2 = fftw_malloc(sizeof(fftw_complex) * fftLen);

    //init data
    for (int i=0;i<len1;i++) {
        in1[i][0] = data1[i]/1.0;
        in1[i][1]=0;
    }

    for (int i=0;i<len2;i++) {
        in2[i][0] = data2[len2-i-1]/1.0;
        in2[i][1] = 0;
    }

    // compute fft
    p = fftw_plan(fftLen,in1,out1,FFTW_FORWARD,FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    p = fftw_plan(fftLen,in2,out2,FFTW_FORWARD,FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);

    // compute complex mul
    for (int i=0;i<fftLen;i++) {
        in1[i][0]=out1[i][0]*out2[i][0]-out1[i][1]*out2[i][1];
        in1[i][1]=out1[i][0]*out2[i][1]+out1[i][1]*out2[i][0];
    }

    // compute ifft
    p = fftw_plan(fftLen,in1,out1,FFTW_BACKWARD,FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);

    //free memory
    fftw_free(out2);
    fftw_free(in2);
    fftw_free(in1);

    // search LFM
    double maxV;
    int maxPos;
    maxFftwComplex(out1,fftLen,&maxV,&maxPos);

    double power = averangeFftwComplex(out1,fftLen);
    out1[maxPos][0]=0.0;
    out1[maxPos][1]=0.0;

    if (power < 1.414*averangeFftwComplex(out1,fftLen)) {
        maxPos = -1;
    }

    fftw_free(out1);
    return maxPos;

}

void despread(const char *data,int len)
{
    /*
     * despread demod etc.
    */
    // step 1. passband to bassband


    // step 2. resample


    // step 3. despread


    // step 4. demod
}
