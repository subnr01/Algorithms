/*

Remove all duplicates from an input string
Solution 1: Use sorting and inplace removal
*/




 char *removeDupsSorted(char *str)
{
  int i = 1, j = 1;
 
  /* In place removal of duplicate characters*/
  while (str[i])
  {
    if( str[i] != str[i-1])
    {
      str[j] = str[i];
      j++;
    }

    i++;
  }      
 
  str[j] = '\0';
   
  return str;
}



/*
Use hash table and inplace removal
No sorting required here
*/


char *removeDups(char *str)
{
  bool bin_hash[256 = {0};
  int i = 0, j = 0; 
  char temp;    
 
  /* In place removal of duplicate characters*/ 
  while(*(str + i))
  {
    temp = *(str + i);
    if(bin_hash[temp] == 0)
    {
        bin_hash[temp] = 1;
        *(str + j) = *(str + i);
        j++;         
    }
    i++;
  }      
 
  /* After above step string is stringiittg.
     Removing extra iittg after string*/       
  *(str+j) = '\0';   
   
  return str;
}
