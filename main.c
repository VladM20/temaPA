#include "headers/liste.h"

void readTeamName(FILE *input,char *dest,int n)
{
    char c;
    for(int i=0;i<n;i++)
    {
        c=fgetc(input);
        if(c=='\n')
            break;
        dest[i]=c;
    }
    dest[n]='\0';
}

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