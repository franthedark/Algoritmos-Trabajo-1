#include "busbi.h"


int binarySearchRec ( int X [] , int l , int r , int key ){
if (l > r)
return -1;
else
{
int mid = l + (r - l) / 2;
if (X[ mid ] == key )
return mid ;
if (X[ mid ] > key )
return binarySearchRec (X , l , mid - 1, key );
else
return binarySearchRec (X , mid + 1, r , key );
}
}


int binarySearchIt ( int X [] , int l , int r , int key ){
while (l <= r ){
int mid = l + (r - l) / 2;
if (X[ mid ] == key )
return mid ;
if (X[ mid ] < key )
l = mid + 1;
else
r = mid - 1;
}
return -1;
}