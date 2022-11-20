#include <stdio.h>



// #ifdef __cplusplus
// extern "C"{
// #endif

static inline bool isLittleEndian(void){
    int x = 1;
    return (*((char*)&x))==1;
}

void clock_init(void){


}


// #ifdef __cplusplus
// }
// #endif

int main( int argc, char const *argv[]){
  union{
        struct{
          uint32_t PLLM          : 6;
          uint32_t PLLN          : 9;
          uint32_t reserved15    : 1;
          uint32_t PLLP          : 2;
          uint32_t reserved21_18 : 4;
          uint32_t PLLSRC        : 1;
          uint32_t reserved23    : 1;
          uint32_t PLLQ          : 4;
          uint32_t reserved31_28 : 4;
        }bit;
        uint32_t data;
      }PLLCFGR;
    uint32_t CR  = 0xf0000000;
    PLLCFGR.data = 0x00000000;
    PLLCFGR.bit.PLLM = 25;
    printf("%d\n", isLittleEndian());

  while(1){
    
  }


}



