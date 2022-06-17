#ifndef SVN_H
#define SVN_H
// If REGISTER_VERSION is on, then we only work for registers.
#define REGISTER_VERSION

#include <algorithm>
#include <initializer_list>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace svn {
typedef std::pair<std::string, int> chrono_label_t;

inline chrono_label_t QuickWrap(const std::string str, const int num) { return make_pair(str, num); }

struct SvnInstBundle {
  chrono_label_t oprand_1;
  chrono_label_t oprand_2;
  int opcode;

  SvnInstBundle(const chrono_label_t lab1, const chrono_label_t lab2, const int op)
      : oprand_1(lab1), oprand_2(lab2), opcode(op) {}
};

class SvnOperandLabel {
private:
  std::map<std::string, int> chronicle;
  std::unordered_map<SvnInstBundle, bool> maper;
};
} // namespace svn

#endif