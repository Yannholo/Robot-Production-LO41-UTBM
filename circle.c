/* circle.c */
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>

#define NB_CASES 16
#define NB_ATTENDU 1 // nb de robots attendu

int j = 0;

pthread_mutex_t mutex;
pthread_cond_t * cases; // Conditions pour chaques cases
pthread_cond_t cercle; // Condition sur le cercle
pthread_cond_t attente_robots; // Condition d'attete de tout les robots
int * cases_reader; // nb de lecteur par cases (max 1)
int nb_attente; // nb de robot qui ont signale leur fin

pthread_t cercle_tid;

void init_circle() {
    int i;
    nb_attente = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cercle, NULL);
    pthread_cond_init(&attente_robots, NULL);
    cases = malloc(NB_CASES * sizeof(pthread_cond_t));
    cases_reader = malloc(NB_CASES * sizeof(int));
    for (i = 0; i < NB_CASES; i++) {
        cases_reader[i] = 0;
        pthread_cond_init(&cases[i], NULL);
    }
}

// Handle les signaux de fin des robots
void signal_fin_robot_handler() {
    pthread_mutex_lock(&mutex);
    printf("2.1 %d signal_fin_robot_handler : signal robot reçu\n", j++);

    nb_attente++;
    // si tout les robots ont fini on reveille le cercle
    if(nb_attente >= NB_ATTENDU) {
        printf("2.2 %d signal_fin_robot_handler : on debloque le cercle qui attend les robots (%d/%d)\n", j++, nb_attente, NB_ATTENDU);
        pthread_cond_signal(&attente_robots);
	printf("2.2 %d signal_fin_robot_handler : on a debloque le cercle qui attend les robots (%d/%d)\n", j++, nb_attente, NB_ATTENDU);
    }
    pthread_mutex_unlock(&mutex);
}

void * func_circle(void * arg) {
    while(1<=1) {
	/* fait tourner le cercle */
        printf("0.1 func_circle : Fait tourner le cercle\n");

        /* debloque les robots */
        pthread_mutex_lock(&mutex);
        printf("0.2 %d func_circle : on debloque les robots\n", j++);
        pthread_cond_broadcast(&cercle);
        pthread_mutex_unlock(&mutex);

        /* attente de la fin des robots */
        pthread_mutex_lock(&mutex);
        // Si tout les robots n'ont pas fini on attend le reveil du handler
        if(nb_attente < NB_ATTENDU) {
            printf("0.3 %d func_circle : attente arrivée robot (deblocage handler)\n", j++);
            pthread_cond_wait(&attente_robots, &mutex);
            printf("0.4 %d func_circle : le handler nous debloque\n", j++);

        } else {
            printf("0.5 %d func_circle : les robot sont déja la\n", j++);
        }
	nb_attente = 0;
        pthread_mutex_unlock(&mutex);
    }
}

/* mettre dans un autre fichier */
void * func_robot(void * arg) {

    while(1<=1) {
        /* on signale au cercle que l'on l'attend */
        pthread_mutex_lock(&mutex);
        printf("1.1 %d func_robot : signal cercle (SIGUSR1)\n", j++);

        pthread_kill(cercle_tid, SIGUSR1);
        printf("1.2 %d func_robot : attend cercle debloque les robots\n", j++);
        pthread_cond_wait(&cercle, &mutex); // le cercle nous reveille
        pthread_mutex_unlock(&mutex);

        /* regarder la case, faire ce que l'on doit faire */
        printf("1.3 func_robot : faire le robot\n");

    }

}

int main() {

    pthread_t robot_tid;
    printf("main\n");

    signal(SIGUSR1, signal_fin_robot_handler);
    printf("signal\n");

    init_circle();

    printf("init_circle\n");
    pthread_mutex_lock(&mutex);

    printf("pthread_mutex_lock\n");
    pthread_create(&cercle_tid, NULL, func_circle, NULL);

    printf("pthread_create\n");
    pthread_create(&robot_tid, NULL, func_robot, NULL);

    printf("pthread_create\n");
    pthread_mutex_unlock(&mutex);

    printf("pthread_mutex_unlock\n");

    pthread_join(robot_tid, NULL);
    pthread_join(cercle_tid, NULL);
    exit (0);
}
