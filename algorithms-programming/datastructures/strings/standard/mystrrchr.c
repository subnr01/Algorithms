/*
 *
 * What is strrchr?
 *
 * strrchr is similar to strchr, except the string is searched right to left.
 *
 */
char *(strchr) (const char *s, int c)
{
    int  len  = strlen (s);
    
    char *temp = s + len;

    while ( len-- != 0)
    {
        if ( *temp-- == (char)c)
            return (char *)temp;
    }
    return NULL;
}

