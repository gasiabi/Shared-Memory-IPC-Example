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
#define NUM_SEGMENTS 5 // ile widomosci mozna wyslac

struct shmseg {
   int cnt;
   int complete;
   char buf[BUF_SIZE];
   int numer;
};

int main() {
   int shmid;
   struct shmseg *shmp;
	int smid_size=sizeof(struct shmseg) * NUM_SEGMENTS;
   shmid = shmget(SHM_KEY, smid_size, 0644 | IPC_CREAT);
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }
   shmp = shmat(shmid, NULL, 0);
   if (shmp == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }

   for (int i = 0; i < NUM_SEGMENTS; ++i) {
      // reader czeka na falage od writer'a
      while (shmp[i].complete != 1) {

      }

      printf("Numer segmentu: %d\n", shmp[i].numer);
      printf("Odczytano: %d bytes\n", shmp[i].cnt);
      printf("Wiadomosc: \n\"%s\"\n", shmp[i].buf);

      shmp[i].complete = 0; // teraz writer znowu moze czytac
      sleep(1);
   }

   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }

   printf("Wszystie wiadomosci odczytane\n");
   return 0;
}
