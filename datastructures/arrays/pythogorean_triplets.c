

bool Pyth_triplets :: find_triplets()
{
   bool found = false;  
   if ( array == NULL) {
    return false;
   }
   int i = 0;
   int j = i + 1;   
   int k = size - 1;

        
   while ( k > 0) {
    i = 0;
    j = k - 1;
                
    while ( i < j) {
        if ( (array[i]*array[i] + array[j]*array[j])  == array[k]*array[k]) {
        cout << array[i] << array[j] << array[k];
        j--;
        i++;
        found = true;
        } 
        else if ( (array[i]*array[i] + array[j]*array[j]) < array[k]*array[k]) {
        i++;
        }else{
        j--;
        }
    }
    cout<<endl;
    k--;         
   }
   return found;
}


