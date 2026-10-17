#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <stdio.h>

int main() {
  int w, h, channels;
  unsigned char *pixels = stbi_load("stego.png", &w, &h, &channels, 3);

  int msg[5] = {1, 0, 0, 1, 1};

  for (int i = 0; i < sizeof(msg) / sizeof(msg[0]); i++) {
    printf("%u\n", pixels[i * 3 + 2] & 1);
    pixels[i * 3 + 2] = (pixels[i * 3 + 2] & 0xFE) | msg[i];
  }

  stbi_write_png("stego.png", w, h, 3, pixels, w * 3);
  stbi_image_free(pixels);
}
