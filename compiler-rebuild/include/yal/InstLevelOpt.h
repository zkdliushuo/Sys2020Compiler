#ifndef CODEGEN_INSTLEVELOPT_H
#define CODEGEN_INSTLEVELOPT_H

static const int LimiRange = 65536;
static const int MultSplitPos[LimiRange] = {};
static const int MultSplitNeg[LimiRange] = {};

static const int MultiplyDeBruijnBitPosition[32] = {0, 9,  1,  10, 13, 21, 2,  29, 11, 14, 16, 18, 22, 25, 3, 30,
                                                    8, 12, 20, 28, 15, 17, 24, 7,  19, 27, 23, 6,  26, 5,  4, 31};

static const int MultiplyDeBruijnBitPosition2[32] = {0,  1,  28, 2,  29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4,  8,
                                                     31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6,  11, 5,  10, 9};

inline int NormalLog(int v) {
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  return MultiplyDeBruijnBitPosition[(unsigned int)(v * 0x07C4ACDDU) >> 27];
}

inline int SpecialLog(int v) { return MultiplyDeBruijnBitPosition2[(unsigned int)(v * 0x077CB531U) >> 27]; }

#endif