#include "definitii.h"

char *copyString(char *source)
{
    if(source==NULL)
        return NULL;
    char *copy=(char*)malloc(strlen(source)+1);
    if(!allocWorked(copy,"copyString(copy)"))
        return NULL;
    strcpy(copy,source);
    return copy;
}

int allocWorked(void *pointer,char *function)
{
    if(pointer==NULL)
    {
        printf("Nu s-a putut aloca memorie in %s\n",function);
        return 0;
    }
    return 1;
}

int verifyFile(FILE *file,char *fileName)
{
    if(file==NULL)
    {
        printf("Nu s-a putut deschide fisierul %s.\n",fileName);
        return 1;
    }
    return 0;
}

int powerOf2(int n)
{
    if(n<1)
        return 0;
    int rezultat=1;
    for(int i=0;i<8*sizeof(int);i++)    //i merge pana la numarul de biti al n
    {
        int incercare=1<<i;             //incercam fiecare putere a lui 2
        if(incercare>n)
            break;
        rezultat=incercare;
    }
    return rezultat;
}

void truncateWhiteSpace(char *name)
{
    if(name==NULL)
        return;
    int length=strlen(name);
    while(length>0 && (name[length-1]==' ' || name[length-1]=='\n'  || name[length-1]=='\r'))
        length--;
    name[length]='\0';
}

void teamPoints(Team *team)
{
    float points=0;
    for(int i=0;i<team->numberOfPlayers;i++)
        points+=team->player[i].points;
    team->points=points/team->numberOfPlayers;
}

char *readTeamName(FILE *input)
{
    char name[MAX_LENGTH];
    fgets(name,MAX_LENGTH,input);
    truncateWhiteSpace(name);
    return copyString(name);
}

char *readName(FILE *input)
{
    char name[MAX_LENGTH];
    fscanf(input,"%s",name);
    truncateWhiteSpace(name);
    return copyString(name);
}

Player readPlayer(FILE *input)
{
    Player empty;
    empty.firstName=empty.secondName=NULL;
    empty.points=0;
    Player newPlayer;
    newPlayer.firstName=readName(input);
    if(!allocWorked(newPlayer.firstName,"readPlayer(newPlayer.firstName)"))
        return empty;

    newPlayer.secondName=readName(input);
    if(!allocWorked(newPlayer.secondName,"readPlayer(newPlayer.secondName)"))
        return empty;

    fscanf(input,"%d",&(newPlayer.points));
    return newPlayer;
}

Player *copyPlayers(Player *source,int numberOfPlayers)
{
    if(source==NULL)
        return NULL;
    
    Player *newPlayers=(Player*)malloc(numberOfPlayers*sizeof(Player));
    if(!allocWorked(newPlayers,"copyPlayers(newPlayers)"))
        return NULL;
        
    for (int i=0;i<numberOfPlayers;i++) 
    {
        newPlayers[i].firstName=copyString(source->firstName);
        if(!allocWorked(newPlayers[i].firstName,"copyTeam(newPlayers[i].firstName)"))
        {
            freePlayers(newPlayers,i);
            return NULL;
        }

        newPlayers[i].secondName=copyString(source->secondName);
        if(!allocWorked(newPlayers[i].secondName,"copyTeam(newPlayers[i].secondName)"))
        {
            free(newPlayers[i].firstName);
            freePlayers(newPlayers,i);
            return NULL;
        }

        newPlayers[i].points=source[i].points;
    }
    return newPlayers;
}

void freePlayers(Player *players,int numberOfPlayers)
{
    for(int i=0;i<numberOfPlayers;i++)
    {
        if(players[i].firstName!=NULL)
            free(players[i].firstName);
        if(players[i].secondName!=NULL)
            free(players[i].secondName);
    }
    free(players);
}

Team *allocTeam()
{
    Team *newTeam=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newTeam,"allocTeam(newTeam)"))
        return NULL; 

    return newTeam;
}

Team *readTeam(FILE *input)
{
    Team *newTeam=allocTeam();
    if(newTeam==NULL)
        return NULL;

    fscanf(input,"%d",&(newTeam->numberOfPlayers));
    fgetc(input);   //scapa de spatiul dintre numarul de jucatori si numele echipei

    newTeam->name=readTeamName(input);
    if(!allocWorked(newTeam->name,"readTeam(newTeam->name)"))
    {
        free(newTeam);
        return NULL;
    }

    newTeam->player=(Player*)malloc(newTeam->numberOfPlayers*sizeof(Player));
    if(!allocWorked(newTeam->player,"readTeam(newTeam->player)"))
    {
        free(newTeam->name);
        free(newTeam);
        return NULL;
    }
    
    for(int i=0;i<newTeam->numberOfPlayers;i++)
    {
        newTeam->player[i]=readPlayer(input);
        if(newTeam->player[i].firstName==NULL || newTeam->player[i].secondName==NULL)
        {
            freePlayers(newTeam->player,i);
            free(newTeam->name);
            free(newTeam);
        }
    } 
    teamPoints(newTeam);
    return newTeam;
}

void copyTeam(Team *source, Team *destination) 
{
    if(source==NULL || destination==NULL)
        return;
        
    destination->name=(char*)malloc((strlen(source->name)+1)*sizeof(char));
    if(!allocWorked(destination->name,"copyTeam(destination->name)"))
        return;
    strcpy(destination->name,source->name);

    destination->numberOfPlayers=source->numberOfPlayers;
    destination->points=source->points;

    destination->player=copyPlayers(source->player,source->numberOfPlayers);
    if(!allocWorked(destination->player,"copyTeam(destination->player)"))
    {
        free(destination->name);
        return;
    }
}