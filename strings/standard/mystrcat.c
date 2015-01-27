

char *strcat ( char *dest, const char *src)
{
    char *s = dest; 

    while(*s)
    {
        s++;
    }

    strcpy(s,src);
    return dest;
}


