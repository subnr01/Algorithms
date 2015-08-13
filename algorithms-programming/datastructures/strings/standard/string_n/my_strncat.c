

char *strncat ( char *s1, char *s2, int n)
{

    char *temp = s2;
    int n = count;

    while (*temp)
        temp++;

    
    while ( *s1 != '\0' && count != 0 )
    {
        *temp++ = *s1++;
        count--;
    }
    *temp = '\0';

    return s2;

}
