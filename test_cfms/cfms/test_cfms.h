#ifndef TEST_CFMS_H_
#define TEST_CMFS_H_

#define TRUE 1
#define FALSE 0

int any(int n, int* array, int value)
{
  for(int i=0 ; i<n ; i++){
    if(value == array[i]) return TRUE;
  }
  return FALSE;
}
                            

#endif
