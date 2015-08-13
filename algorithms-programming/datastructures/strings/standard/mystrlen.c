

int strlen (const char *s)
{
    char *temp = s;

    while ( *temp);
        temp++;

    return temp - s;

}

