#include "BitMagic.h"

using namespace bitmagic;

int bitmagic::MultCoverPostive(int num, int depth) {
  if (num == 1)
    return 0;
  if (num > 65535 || num <= 0)
    return 65535;
  if (depth > 14)
    return 65535;

  // cout << "Visiting " << num << endl;

  int cost = 65535;
  if (g_valid[num])
    return g_cost[num];

  int make_odd_num = Makeodd(num);
  if (num != make_odd_num) {
    int temp_cost = MultCoverPostive(make_odd_num, depth + 1);
    if (temp_cost + 1 < cost) {
      cost = temp_cost + 1;
      g_parent[num] = make_odd_num;
      g_op[num] = g_opcode::shift;
      g_cost[num] = g_cost[make_odd_num] + 1;
    }
  }

  int factor = 4;
  int parent = 0;
  int op;
  int temp_cost;
  while (factor < (num >> 1)) {
    if (num % (factor - 1) == 0) {
      temp_cost = MultCoverPostive(num / (factor - 1), depth + 1);
      if (temp_cost + 2 < cost) {
        cost = temp_cost + 2;
        g_parent[num] = num / (factor - 1);
        g_op[num] = g_opcode::factorsub;
        g_cost[num] = g_cost[num / (factor - 1)] + 2;
      }
    }

    if (num % (factor + 1) == 0) {
      temp_cost = MultCoverPostive(num / (factor + 1), depth + 1);
      if (temp_cost + 2 < cost) {
        cost = temp_cost;
        g_parent[num] = num / (factor + 1);
        g_op[num] = g_opcode::factoradd;
        g_cost[num] = g_cost[num / (factor + 1)] + 2;
      }
    }

    factor <<= 1;
    if (!parent)
      continue;
  }

  parent = num - 1;
  op = g_opcode::shiftadd;
  temp_cost = MultCoverPostive(parent, depth + 1);
  if (temp_cost + 1 < cost) {
    cost = temp_cost + 1;
    g_parent[num] = parent;
    g_op[num] = op;
    g_cost[num] = g_cost[parent] + 1;
  }

  parent = num + 1;
  op = g_opcode::shiftsub;
  temp_cost = MultCoverPostive(parent, depth + 1);
  if (temp_cost + 1 < cost) {
    cost = temp_cost + 1;
    g_parent[num] = parent;
    g_op[num] = op;
    g_cost[num] = g_cost[parent] + 1;
  }

  g_cost[num] = cost;
  g_valid[num] = true;
  return cost;
}

std::vector<std::pair<int, int>> bitmagic::GetSolution(int num) {
  std::vector<std::pair<int, int>> solution;
  if (num == 1) {
    solution.push_back(std::make_pair(g_opcode::shift, 0));
    return solution;
  }

  solution = GetSolution(g_parent[num]);

  if (g_op[num] == g_opcode::factoradd) {
    int fac = num / g_parent[num];
    fac--;
    fac = SpecialLog(fac);
    solution.push_back(std::make_pair(g_opcode::factoradd, fac));
  }
  if (g_op[num] == g_opcode::factorsub) {
    int fac = num / g_parent[num];
    fac++;
    fac = SpecialLog(fac);
    solution.push_back(std::make_pair(g_opcode::factorsub, fac));
  }
  if (g_op[num] == g_opcode::shiftadd) {
    solution.push_back(std::make_pair(g_opcode::shiftadd, 1));
  }
  if (g_op[num] == g_opcode::shiftsub) {
    solution.push_back(std::make_pair(g_opcode::shiftsub, 1));
  }
  if (g_op[num] == g_opcode::shift) {
    solution.push_back(std::make_pair(g_opcode::shift, SpecialLog(num / Makeodd(num))));
  }
  return solution;
}

void bitmagic::PrintSolution(int num) {
  if (num == 1) {
    return;
  }
  PrintSolution(g_parent[num]);
  std::string opnum = g_parent[num] == 1 ? "orig" : "num";
  if (g_op[num] == g_opcode::factoradd) {
    int fac = num / g_parent[num];
    fac--;
    fac = SpecialLog(fac);
    std::cout << "num = add " << opnum << ", " << opnum << " shift" << fac << std::endl;
  }
  if (g_op[num] == g_opcode::factorsub) {
    int fac = num / g_parent[num];
    fac++;
    fac = SpecialLog(fac);
    std::cout << "num = rsb " << opnum << ", " << opnum << " shift" << fac << std::endl;
  }
  if (g_op[num] == g_opcode::shiftadd) {
    std::cout << "num = num + orig" << std::endl;
  }
  if (g_op[num] == g_opcode::shiftsub) {
    std::cout << "num = num - orig" << std::endl;
  }
  if (g_op[num] == g_opcode::shift) {
    std::cout << "num = " << opnum << " << " << SpecialLog(num / Makeodd(num)) << std::endl;
  }
}

int bitmagic::MultCover(int num) {
  g_valid[1] = 1;
  g_cost[1] = 0;
  g_parent[1] = 1;
  if (num > 0)
    return MultCoverPostive(num, 0);
  if (num <= 0)
    return 65535;
}

std::pair<int, int> bitmagic::DivCover(int num) {
  Uint32 abs_num = abs(num);
  int log_num = (BitCount(abs_num) == 1) ? NormalLog(abs_num) : NormalLog(abs_num) + 1;
  int l = std::max(log_num, 1);
  Uint64 melt = 1 + (1ll << (32 + l - 1)) / abs_num;
  int final = (int)(melt - (1ll << 32));
  int shpost = l - 1;
  return std::make_pair(final, shpost);
}

// * Here I am going to give a demo for integer division

int BitMagicSRA(int value, int amount) /* Completely portable */
{
  return value < 0 ? ~(~value >> amount) : value >> amount;
}

long long BitMagicSRA(long long value, int amount) /* Completely portable */
{
  return value < 0 ? ~(~value >> amount) : value >> amount;
}

unsigned long long BitMagicSRA(unsigned long long value, int amount) /* Completely portable */
{
  return value >> amount;
}

int BitMagicMULSH(int x, int y) {
  unsigned long long result = ((unsigned long long)x) * ((unsigned long long)y);
  result = result >> 32;
  return (int)result;
}

int BitMagicXSIGN(int x) {
  if (x < 0)
    return -1;
  else
    return 0;
}

int BitMagicDivision(int n, int d) {
  // Calc n / d
  unsigned int absd = abs(d);
  int logd = (BitCount(absd) == 1) ? NormalLog(absd) : NormalLog(absd) + 1;
  int l = std::max(logd, 1);

  unsigned long long m = 1 + (1ll << (32 + l - 1)) / absd;
  int mm = (int)(m - (1ll << 32));
  int shpost = l - 1;

  int q0 = n + BitMagicMULSH(mm, n);
  q0 = BitMagicSRA(q0, shpost) - (n >> 31);
  if (d > 0)
    return q0;
  else
    return ~q0 + 1;
}