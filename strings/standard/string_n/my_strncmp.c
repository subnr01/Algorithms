
int my_strncmp( const char *s1, const char *s2, int n)
{
    unsigned char temp1;
    unsigned char temp2;

    if (!n)
        return 0;

    while ( n-- != 0 && *s1 == *s2)
    {
        if ( n1 == 0 || *s1 == '\0')
        {   
            return 0;
        }
        s1++;
        s2++;
    }

    temp1 = *(unsigned char *)s1;
    temp2 = *(unsigned char *)s2;

    return ( temp1 < temp2) ? -1 : (temp1 > temp2);
    
    

}
