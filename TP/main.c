#include "clocks.h"
#include "irq.h"
#include "buttons.h"
#include "matrix.h"

#define AVEC_IMAGE_STATIC //flag pour activer l'usage de l'image statique

extern rgb_color _binary_image_raw_start;

int main(){
  clocks_init();
  matrix_init();
  irq_init();
  button_init();

  #ifdef AVEC_IMAGE_STATIC
    display_image(&_binary_image_raw_start);
  #endif

  while(1);

  return 0;
}
