#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.c"


int dumpCode = 0;

void printUsage(void) {
  printf("Usage: kplc input output [-dump]\n");
  printf("   input: input kpl program\n");
  printf("   output: executable\n");
  printf("   -dump: code dump\n");
}

int analyseParam(char* param) {
  if (strcmp(param, "-dump") == 0) {
    dumpCode = 1;
    return 1;
  } 
  return 0;
}


/******************************************************************/

// int main(int argc, char *argv[]) {
//   int i; 

//   if (argc <= 1) {
//     printf("kplc: no input file.\n");
//     printUsage();
//     return -1;
//   }

//   if (argc <= 2) {
//     printf("kplc: no output file.\n");
//     printUsage();
//     return -1;
//   }

//   for ( i = 3; i < argc; i ++) 
//     analyseParam(argv[i]);

//   initCodeBuffer();

//   if (compile(argv[1]) == IO_ERROR) {
//     printf("Can\'t read input file!\n");
//     return -1;
//   }

//   if (serialize(argv[2]) == IO_ERROR) {
//     printf("Can\'t write output file!\n");
//     return -1;
//   }

//   if (dumpCode) printCodeBuffer();
    
//   cleanCodeBuffer();

//   return 0;
// }

int main() {
  int i;

  analyseParam("test\\example2.kpl");

  initCodeBuffer();

  if (dumpCode) printCodeBuffer();
    
  cleanCodeBuffer();

  return 0;
}


