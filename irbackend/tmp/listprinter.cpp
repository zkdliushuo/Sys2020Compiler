#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

constexpr int N = 32;
constexpr int k_max_length = 65536;

typedef unsigned int Uint32;
typedef unsigned long long Uint64;

int g_cost[k_max_length];
int g_valid[k_max_length];
int g_op[k_max_length];
int g_parent[k_max_length];

static const int g_magic_s[] = {1, 2, 4, 8, 16};
static const int g_magic_b[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};

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

inline int count(unsigned int v) {
  unsigned int c = v - ((v >> 1) & g_magic_b[0]);
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

enum g_opcode { factoradd = 0, factorsub, shiftadd, shiftsub, shift };

int Cover(int num, int lower, int upper);

bool TryCover(int parent, int num, int &cost, int &lower, int &upper) {
  int temp_cost = Cover(parent, lower + 2, upper);
  if (temp_cost < cost || !g_valid[num]) {
    cost = temp_cost;
    upper = cost;
    return true;
  }
  return false;
}

int Cover(int num, int lower, int upper) {
  if (num > 65535)
    return 65535;

  int cost = lower + g_cost[num];
  if (cost > upper)
    return upper;
  if (g_valid[num])
    return cost;

  if (num != Makeodd(num)) {
    int temp_cost = Cover(Makeodd(num), lower + 1, upper) + 1;
    g_valid[num] = 1;
    g_op[num] = g_opcode::shift;
    g_cost[num] = temp_cost;
    g_parent[num] = Makeodd(num);
    return temp_cost;
  }

  int factor = 4;
  int parent = 0;
  int op;

  while (factor < (num >> 1)) {
    parent = 0;
    if (num % (factor - 1) == 0) {
      parent = num / (factor - 1);
      op = g_opcode::factorsub;
    }
    if (num % (factor + 1) == 0) {
      parent = num / (factor + 1);
      op = g_opcode::factoradd;
    }

    factor <<= 1;
    if (!parent)
      continue;

    bool flag = TryCover(parent, num, cost, lower, upper);
    if (flag) {
      g_parent[num] = parent;
      g_op[num] = op;
      g_cost[num] = g_cost[parent] + 2;
    }
  }

  parent = num - 1;
  op = g_opcode::shiftadd;
  if (TryCover(parent, num, cost, lower, upper)) {
    g_parent[num] = parent;
    g_op[num] = op;
    g_cost[num] = g_cost[parent] + 2;
  }
  parent = num + 1;
  op = g_opcode::shiftsub;
  if (TryCover(parent, num, cost, lower, upper)) {
    g_parent[num] = parent;
    g_op[num] = op;
    g_cost[num] = g_cost[parent] + 2;
  }
  g_valid[num] = true;
  return cost;
}

void PrintSolution(int num) {
  if (num == 1) {
    return;
  }
  PrintSolution(g_parent[num]);
  string opnum = g_parent[num] == 1 ? "orig" : "num";
  if (g_op[num] == g_opcode::factoradd) {
    int fac = num / g_parent[num];
    fac--;
    fac = SpecialLog(fac);
    cout << "num = add " << opnum << ", " << opnum << " shift" << fac << endl;
  }
  if (g_op[num] == g_opcode::factorsub) {
    int fac = num / g_parent[num];
    fac++;
    fac = SpecialLog(fac);
    cout << "num = rsb " << opnum << ", " << opnum << " shift" << fac << endl;
  }
  if (g_op[num] == g_opcode::shiftadd) {
    cout << "num = num + orig" << endl;
  }
  if (g_op[num] == g_opcode::shiftsub) {
    cout << "num = num - orig" << endl;
  }
  if (g_op[num] == g_opcode::shift) {
    cout << "num = " << opnum << " << " << SpecialLog(num / Makeodd(num)) << endl;
  }
}

int main() {
  int case_count;
  // std::fill(g_cost, g_cost + k_max_length, k_max_length);
  // cout << g_cost[3];
  cin >> case_count;
  g_valid[1] = 1;
  g_cost[1] = 0;
  g_parent[1] = 1;
  Cover(case_count, 0, 65535);
  PrintSolution(case_count);
}
