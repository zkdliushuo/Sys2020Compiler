#ifndef SIMPLIFYSPILL
#define SIMPLIFYSPILL

namespace YAL {

class Function;

class SimplifySpill {
private:
  Function &F;

public:
  SimplifySpill(Function &F) : F(F) {}

  void run();
};

}

#endif