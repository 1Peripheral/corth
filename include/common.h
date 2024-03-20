#ifndef COMMON_H_
#define COMMON_H_

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef ASSERT 
  #define ASSERT(e) assert(e)
#endif

#ifndef MALLOC 
  #define MALLOC(e) malloc(e)
#endif

#ifndef FREE 
  #define FREE(e) free(e)
#endif


#endif //COMMON_H_
