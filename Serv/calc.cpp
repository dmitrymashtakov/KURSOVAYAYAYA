#include "calc.h"
#include "error.h"
calc::calc(std::vector<float> chisla) {
  if (chisla.empty()) {
  throw no_crit_err("Должен быть хотя бы один элемент в векторе");
  }
  float sum = 0;
  for (float i : chisla) {
    sum += i;
  }
  res = sum / chisla.size();
}
float calc::send_res() {
  return res;
}

