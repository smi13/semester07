/*
 * Задачи необходимо решить с использованием потоков POSIX.
 *
 * 4.3. Напишите программу, моделирующую решение задачи «спящего брадобрея».*/

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

int chair_number, haircut_duration;

int customers, barbershop;
pthread_mutex_t mutex_customers, mutex_barbershop;
sem_t customer, barber, haircut;

void printHelp( char *program_name )
{
	printf("Barbershop problem simulation program\n"
			 "Usage: %s <chair number> <haircut duration in seconds>\n", program_name);
}

int mygetch( ) 
{
	struct termios oldt, newt;
	int ch;

	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

	return ch;
}

void get_haircut( int id )
{
	printf("Barber is mastering Mr. %i`s haircut.\n", id);
	sleep(haircut_duration);
	sem_post(&haircut);
}

void cut_hair( void )
{
	sem_wait(&haircut);
	printf("Barber finished another haircut.\n");
}

void *customer_procedure( void *arg )
{
	pthread_t self_thread_id = pthread_self();

	unsigned int self_id = (unsigned long)self_thread_id % 30;

	printf("Mr. %i arrives to the barbershop.\n", self_id);

	pthread_mutex_lock(&mutex_customers);

	if (customers == chair_number)
	{
		printf("There is no free chair to wait for Mr. %i. He leaves the barbershop.\n", self_id);
		pthread_mutex_unlock(&mutex_customers);
		pthread_exit(NULL);
	}

	customers++;
	printf("Mr. %i took a seat. (%i/%i)\n", self_id, customers, chair_number);

	pthread_mutex_unlock(&mutex_customers);

	sem_post(&customer);
	sem_wait(&barber);

	pthread_mutex_lock(&mutex_customers);

	customers--;

	pthread_mutex_unlock(&mutex_customers);

	printf("Mr. %i is going to get a new haircut. (%i/%i)\n", self_id, customers, chair_number);

   get_haircut(self_id);

	printf("Mr. %i got a new haircut. He leaves the barbershop. (%i/%i)\n", self_id, customers, chair_number);

	pthread_exit(NULL);
}

void *barber_procedure( void *arg )
{
	printf("Barbershop is open.\n");

	while (1)	
	{
		int cur_customers;

		pthread_mutex_lock(&mutex_customers);
		cur_customers = customers;
		pthread_mutex_unlock(&mutex_customers);

		if (cur_customers == 0)
			printf("Barber is sleeping, waiting for the customer.\n");

		sem_wait(&customer);

		if (cur_customers == 0)
			printf("Barber woke up. Going to work.\n");

		sem_post(&barber);
		cut_hair();
	}

	return NULL;
}

void init_semaphores( void )
{
	barbershop = 1;
	customers = 0;
	pthread_mutex_init(&mutex_barbershop, NULL);
	pthread_mutex_init(&mutex_customers, NULL);
	sem_init(&barber, 0, 0);
	sem_init(&customer, 0, 0);
	sem_init(&haircut, 0, 0);
}

void destroy_semaphores( void )
{
	pthread_mutex_destroy(&mutex_barbershop);
	pthread_mutex_destroy(&mutex_customers);
	sem_destroy(&barber);
	sem_destroy(&customer);
	sem_destroy(&haircut);
}

void new_customer( void )
{
	pthread_t customer_thread;

	pthread_create(&customer_thread, NULL, customer_procedure, NULL);
}

int main( int argc, char *argv[] )
{
	int flag = 1;

	if (argc < 3)
	{
		printHelp(argv[0]);
		return EXIT_FAILURE;
	}

	pthread_t barber_thread;

	chair_number = atoi(argv[1]);
	haircut_duration = atoi(argv[2]);

   pthread_create(&barber_thread, NULL, barber_procedure, NULL);

	init_semaphores();

	while (flag)
	{
		char c = mygetch();

		switch (c)
		{
		case 'c':
			flag = 0;
			pthread_cancel(barber_thread);
			break;
		case 'a':
			new_customer();
			break;
		}
	}

	destroy_semaphores();

	pthread_exit(NULL);

	return EXIT_SUCCESS;
}
