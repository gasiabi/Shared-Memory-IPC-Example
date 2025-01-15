#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#define BUF_SIZE 100
#define SHM_KEY 0x1234
#define NUM_SEGMENTS 5 // Number of messages

struct shmseg {
   int cnt;
   int complete;
   char buf[BUF_SIZE];
   int numer;
};

int main() {
   int shmid;
   struct shmseg *shmp;
   char msg[BUF_SIZE];
	
	int smid_size=sizeof(struct shmseg) * NUM_SEGMENTS;
   shmid = shmget(SHM_KEY, smid_size, 0644 | IPC_CREAT);// robimy pamiec wspolna rozmiarem smid_size
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }
   
   shmp = shmat(shmid, NULL, 0);
   if (shmp == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }
	printf("Mozna napisac tylko 5 wiadomosci\n");
   for (int i = 0; i < NUM_SEGMENTS; ++i) {
      
      printf("Numer wiadomosci = %d/5\n", i);
      printf("Wprowadz wiadomosc\n> ");
      if (fgets(msg, BUF_SIZE, stdin) == NULL) {
         perror("msg error");
         return 1;
      }

      strncpy(shmp[i].buf, msg, BUF_SIZE);
      shmp[i].cnt = strlen(shmp[i].buf);
      shmp[i].numer = i;

      printf("Rozmiar wiadomosci - %d bytes\n", shmp[i].cnt);

      shmp[i].complete = 1; // flaga dla readera, ze jest wiadomosc do odebrania
      sleep(1);
   }

   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }

   printf("Nie mozna wiecej wysylac\n");
   return 0;
}
