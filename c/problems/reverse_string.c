#include <stdio.h>
#include <string.h>

const char * reverse(char *str){
    size_t len = strlen(str);
    for(int i = len - 1, j = 0; j < len / 2; i--, j++)
    {
        char c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
    return str;
}


int main(int argc, char *argv[])
{
    char *str = strdup("hello");
    printf("%s", reverse(str));
    return 0;
}
