#include "fworker.h"

int n_files();
float black_percentage(BMPImage* image);
BMPImage* classify(BMPImage* image, float umbral);
void write_bmp(const char* filename, BMPImage* image);
void new_folder(const char *foldername);
void move_file(const char *filename, const char *foldername);
void new_csv(const char *filename);
void write_csv(BMPImage *image,const char *csvname);
char** file_names(const char *prefix);
