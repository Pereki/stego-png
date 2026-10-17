#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <stdio.h>

void decode(unsigned char *pixels, int lenght) {
  for (int i = 0; i < lenght; i++) {
    printf("%u", pixels[i * 3 + 2] & 1);
  }
}

void encode(unsigned char *pixels, int message[], int size, int w, int h,
            char *output) {
  for (int i = 0; i < size; i++) {
    pixels[i * 3 + 2] = (pixels[i * 3 + 2] & 0xFE) | message[i];
  }
  stbi_write_png(output, w, h, 3, pixels, w * 3);
}

int main(int argc, char *argv[]) {
  int w, h, channels;
  int msg[5] = {1, 0, 0, 1, 1};
  char *mode = argv[1];
  char *input_file = argv[2];
  char *output_file = argv[3];

  unsigned char *pixels = stbi_load(input_file, &w, &h, &channels, 3);
  if (!strcmp(mode, "encode")) {
    printf("encoding %s...", input_file);
    encode(pixels, msg, 5, w, h, output_file);

  } else {
    printf("Decoded Message with length %i is:\n", 5);
    decode(pixels, 5);
  }

  stbi_image_free(pixels);
}
