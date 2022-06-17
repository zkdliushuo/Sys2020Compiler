#ifndef IRBACKEND_BITMAGIC_H
#define IRBACKEND_BITMAGIC_H
#include <algorithm>
#include <functional>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <vector>

constexpr int k_max_length = 65536;
typedef unsigned int Uint32;
typedef unsigned long long Uint64;
static int g_cost[k_max_length];
static int g_valid[k_max_length];
static int g_op[k_max_length];
static Uint32 g_parent[k_max_length];

static const Uint32 g_magic_s[] = {1, 2, 4, 8, 16};
static const Uint32 g_magic_b[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};

static const int MultiplyDeBruijnBitPosition[32] = {0, 9,  1,  10, 13, 21, 2,  29, 11, 14, 16, 18, 22, 25, 3, 30,
                                                    8, 12, 20, 28, 15, 17, 24, 7,  19, 27, 23, 6,  26, 5,  4, 31};

static const int MultiplyDeBruijnBitPosition2[32] = {0,  1,  28, 2,  29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4,  8,
                                                     31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6,  11, 5,  10, 9};

namespace bitmagic {

inline int NormalLog(int v) {
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  return MultiplyDeBruijnBitPosition[(unsigned int)(v * 0x07C4ACDDU) >> 27];
}

inline int NormalLog(Uint32 v) {
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  return MultiplyDeBruijnBitPosition[(unsigned int)(v * 0x07C4ACDDU) >> 27];
}

inline int SpecialLog(int v) { return MultiplyDeBruijnBitPosition2[(unsigned int)(v * 0x077CB531U) >> 27]; }
inline int SpecialLog(Uint32 v) { return MultiplyDeBruijnBitPosition2[(unsigned int)(v * 0x077CB531U) >> 27]; }

inline int BitCount(Uint32 v) {
  Uint32 c = v - ((v >> 1) & g_magic_b[0]);
  c = ((c >> g_magic_s[1]) & g_magic_b[1]) + (c & g_magic_b[1]);
  c = ((c >> g_magic_s[2]) + c) & g_magic_b[2];
  c = ((c >> g_magic_s[3]) + c) & g_magic_b[3];
  c = ((c >> g_magic_s[4]) + c) & g_magic_b[4];
  return (int)c;
}

inline int Makeodd(int num) {
  while (~num & 1)
    num >>= 1;
  return num;
}

inline Uint32 Makeodd(Uint32 num) {
  while (~num & 1)
    num >>= 1;
  return num;
}

enum g_opcode { factoradd = 0, factorsub, shiftadd, shiftsub, shift };

int MultCoverPostive(int num, int depth);
std::vector<std::pair<int, int>> GetSolution(int num);
void PrintSolution(int num);
int MultCover(int num);

std::pair<int, int> DivCover(int num);
int BitMagicDivision(int n, int d);
} // namespace bitmagic
#endif