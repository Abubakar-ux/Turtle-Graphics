#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct image {
  /**
   * The pixel data here is stored in row major order an unsigned char simply
   * stores numbers from 0-255, you can treat it as an int otherwise, just make
   * sure you **don't** assign values < 0 or > 255, or else you will get
   * unexpected results
   */
  unsigned char *data;

  int sx; // Width of image
  int sy; // Height of image (assume they are the same for this assignment)

} Image;

Image *newImage(int sx, int sy) {
  Image *im;

  im = (Image *)calloc(1, sizeof(Image));
  if (im != NULL) {
    im->sx = sx;
    im->sy = sy;
    im->data = (unsigned char *)calloc(im->sx * im->sy, sizeof(int));
    if (im->data != NULL) {
      memset(im->data, 255, sx * sy);
      return im;
    }
  }
  printf("Error: Unable to allocate memory for new image\n");
  return (NULL);
}

void deleteImage(Image *im) {
  free(im->data);
  free(im);
  return;
}

void drawLine(Image *im, int x1, int y1, int x2, int y2, int col) {
  /* Draws a horizontal or vertical line from (x1, x2) to (y1, y2)
     Expect either x1 == x2 or y1 == y2 */

  if (x1 < 0 || x1 > im->sx || x2 < 0 || x2 > im->sx)
    return;
  if (y1 < 0 || y1 > im->sy || y2 < 0 || y2 > im->sy)
    return;

  int src, end, i;
  if (x1 == x2) {
    src = y1 < y2 ? y1 : y2;
    end = y1 < y2 ? y2 : y1;
    for (i = src; i <= end; i++)
      im->data[x1 + i * im->sx] = col;

  } else if (y1 == y2) {
    src = x1 < x2 ? x1 : x2;
    end = x1 < x2 ? x2 : x1;
    for (i = src; i <= end; i++)
      im->data[i + y1 * im->sx] = col;
  }

  return;
}

/* Outputs an image from the Image struct to a .pgm file */
void imageOutput(Image *im, const char *filename) {
  FILE *f;

  if (im != NULL)
    if (im->data != NULL) {
      f = fopen(filename, "wb+");
      if (f == NULL) {
        printf("Error: Unable to open file %s for output! No image written\n",
               filename);
        return;
      }
      fprintf(f, "P5\n");
      fprintf(f, "# Output from turtle.c\n");
      fprintf(f, "%d %d\n", im->sx, im->sy);
      fprintf(f, "255\n");
      fwrite(im->data, im->sx * im->sy * sizeof(unsigned char), 1, f);
      fclose(f);
      return;
    }
  printf("Error: imageOutput(): Specified image is empty. Nothing output\n");
}
