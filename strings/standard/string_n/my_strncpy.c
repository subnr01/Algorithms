
char *strncpy ( char *s1, char *s2, int n)
{
    char *dst = s1;
    const char *src = s2;

    while ( n-- > 0)
    {
        if ( ( *dst++ = *src++ ) == '\0')
        {
            memset(dst,'\0', n);
            break;
        }
    }
    return s1;
}
