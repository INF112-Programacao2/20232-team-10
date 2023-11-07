#include <string>

class Actor {
 protected:
  std::string _name;
  int _hp;
  int _hp_max;
  int _STR;
  int _DEX;
  int _CON;
  int _INT;
  int _WIS;
  int _CHA;

 public:
  Actor(std::string name, int hp_max);
  void heal(int x);
  void damage(int x);
  void die();
  int get_STR();
  int get_DEX();
  int get_CON();
  int get_INT();
  int get_WIS();
  int get_CHA();
};