#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t team1_sem, team2_sem;
int max = 6;
int nteam1 = 0;
int nteam2 = 0;

struct Data
{
    int number;
    float speed;
    char *team;
};

void *correr(struct Data *info, int teamCode)
{
    int time = info->speed;
    sleep(time);
    
    if (teamCode == 0)
    {
        nteam1++;
        if (nteam1 >= max)
        {
            printf("El equipo %s es ganador!\n", info->team);
            exit(0);
        }
    }
    else
    {
        nteam2++;
        if (nteam2 >= max)
        {
            printf("El equipo %s es ganador!\n", info->team);
            exit(0);
        }
    }
    return NULL;
}

void *iniciarCarreraTeam1(void *arg)
{
    struct Data *info = (struct Data *)arg;
    sem_wait(&team1_sem);
    printf("El corredor %d de %s está corriendo\n", info->number, info->team);
    correr(info, 0);
    sem_post(&team1_sem);
}

void *iniciarCarreraTeam2(void *arg)
{
    struct Data *info = (struct Data *)arg;
    sem_wait(&team2_sem);
    printf("El corredor %d de %s está corriendo\n", info->number, info->team);
    correr(info, 1);
    sem_post(&team2_sem);
}

int main(int argc, char const *argv[])
{
    int max = 6;
    struct Data team1Players[max], team2Players[max];
    pthread_t team1[max], team2[max];
    
    sem_init(&team1_sem, 0, 1);
    sem_init(&team2_sem, 0, 1);

    for (int i = 0; i < max; i++)
    {
        team1Players[i].team = "SKZ";
        team1Players[i].number = i + 1;
        team1Players[i].speed = rand() % 6;

        team2Players[i].team = "BT21";
        team2Players[i].number = max + i;
        team2Players[i].speed = rand() % 6;

        pthread_create(&team1[i], NULL, iniciarCarreraTeam1, &team1Players[i]);
        pthread_create(&team2[i], NULL, iniciarCarreraTeam2, &team2Players[i]);
    }
    for (int i = 0; i < max; i++)
    {
        pthread_join(team1[i], NULL);
        pthread_join(team2[i], NULL);
    }

    return 0;
}