#include "calc.h"
calc::calc(std::vector<float> chisla) {
  float sum = 0;
  for (float i : chisla) {
    sum += i;
  }
  res = sum / chisla.size();
}
float calc::send_res() {
  return res;
}

