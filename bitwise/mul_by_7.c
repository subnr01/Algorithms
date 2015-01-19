int multiplyBySeven(unsigned int n)
{  
    /* Note the inner bracket here. This is needed 
       because precedence of '-' operator is higher 
       than '<<' */
    return ((n<<3) - n); //8n -n
}

