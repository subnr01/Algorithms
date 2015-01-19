count = 0 
while (n>0) { 
count = count + !(n&1) 
n=n>>1 //Right shift by 1 
} 
return count 


