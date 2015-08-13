/*
You're given an array containing integer values. 
You need to print the fraction of count of positive numbers, 
negative numbers and zeroes to the total numbers. Print 
the value of the fractions correct to 3 decimal places.
*/


int main() {
    int p=0,n=0,z=0,a,i,j;
    cin>>j;
    for(i=0;i<j;i++){
        cin>>a;
        
        if(a>0)
            p++;
        else if(a<0)
            n++;
        else
            z++;
    }
    
    printf("%.3f\n",(float)p/j);
    printf("%.3f\n",(float)n/j);
    printf("%.3f",(float)z/j);
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}

