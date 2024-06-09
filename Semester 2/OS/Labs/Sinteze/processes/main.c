#include <stdio.h>

int main(int argc, char** argv) {
 FILE* fp;
 fp = popen("mkdir", "w");
 fprintf(fp, "exemplu");
 pclose(fp);
 return 0;
}
