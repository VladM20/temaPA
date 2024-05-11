#include <stdio.h>
#include <stdlib.h>


int main(int argc,char* argv[])
{
    FILE* f=fopen(argv[1],"rt");
    char c;
    while(c!=EOF)
    {
        c=fgetc(f);
    }
    fclose(f);
    FILE* o=fopen("r.out","wt");
    fclose(o);
    return 0;
}