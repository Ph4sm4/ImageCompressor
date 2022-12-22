#ifndef YCBCRFORMAT_H
#define YCBCRFORMAT_H

struct YCbCrFormat {
    YCbCrFormat(int l, int bc, int rc): luminance(l), blueChrominance(bc), redChrominance(rc) {}
    int luminance;
    int blueChrominance;
    int redChrominance;
};

#endif // YCBCRFORMAT_H
