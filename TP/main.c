#include "clocks.h"
#include "matrix.h"

extern rgb_color _binary_image_raw_start;

int main(){
  clocks_init();
  matrix_init();
  test_pixels();  
  return 0;
}
