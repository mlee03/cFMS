#ifndef TEST_CFMS_H_
#define TEST_CMFS_H_

#include <c_fms.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAIL 1

int any(int n, int* array, int value)
{
  for(int i=0 ; i<n ; i++){
    if(value == array[i]) return TRUE;
  }
  return FALSE;
}
                            
int errmsg_int(int answer, int test, char *message)
{
  printf("\nEXPECTED %d BUT GOT %d FOR %s\n", answer, test, message);
  printf("HEREHERE %d\n", FATAL);
  cFMS_error(FATAL, "GOODBYE!");
  exit(FAIL);
}

#endif
