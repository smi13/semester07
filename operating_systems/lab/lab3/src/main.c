/* 3.4. Напишите программу-демон, получающую в качестве аргумента число N и
  через N минут после запуска отправляющую пользователю, от чьего имени она
  запущена, письмо с произвольным текстом (запустите программу mail).*/

#include <stdio.h>
#include <stdlib.h>

#include <syslog.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>

int prepare_daemon( void )
{
	pid_t pid, sid;

	pid = fork();

	if (pid < 0)
	{
		return -1;
	}
	else if (pid > 0)
	{
		exit(EXIT_SUCCESS);
	}

	umask(0);

	/* It is possible to open log file here */

	sid = setsid();

	if (sid < 0)
	{
		exit(EXIT_FAILURE);
	}

	if (chdir("/") < 0)
	{
		exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void print_help( void )
{
	printf("Usage: lab3 N\n");
}

int main( int argc, char *argv[] )
{
	int N;
	struct passwd *pwd = getpwuid(getuid());
	char *user_name = pwd->pw_name;

	if (argc < 2)
	{
		print_help();
		return EXIT_FAILURE;
	}

	N = atoi(argv[1]);

	if (N == 0)
	{
		printf("Incorrect input number\n");
		return EXIT_FAILURE;
	}

	printf("Everything is OK. Going start daemon for %i seconds.\n", N * 60);

	if (prepare_daemon() == -1)
	{
		printf("Error preparing daemon for work\n");
		return EXIT_FAILURE;
	}

	sleep(N * 60);

	{
		char Buf[300];

		sprintf(Buf, "echo \"%s\\n\\nLet me introduce myself. I am daemon.\" | mail -s \"Greetings.\" ", user_name);
		system(Buf);
	}

	exit(EXIT_SUCCESS);

	return EXIT_SUCCESS;
}
