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
BMPImage** split_image(BMPImage *image, int workers);
void free_subimages(BMPImage **subimages, int num_workers);
BMPImage* combine_images(BMPImage **images, int num_images);
BMPImage** send_and_receive(BMPImage** imageSplit, int workers, int filter, float saturation, float thresholdbina,int multisplit);