/*
 * 2.6. [2] Напишите простой архиватор (программу, объединяющую несколько файлов в
 *    один), сохраняющий атрибуты файла (владельца, группу, права доступа, дату     
 *    последнего изменения) и восстанавливающий их при распаковке архива.
 * */

#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <utime.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
									    Utils
********************************************************************************/

typedef unsigned char byte;

void print_help()
{
	printf("Usage: ./fz [file1] [file2] ... [file_n] <file_out> | -e <file>\n"
			 "Options: \n   -e, --extract   Extract files from <file> \n");
			 //"If first argument is -e, second is considered name of \nfile, which was compressed using fz early\n");
}

/*******************************************************************************
									    Extracting functions
********************************************************************************/

int extract_file( int file_des )
{
	int name_length, f_out;
	char *file_name = NULL;
	void *file_buf = NULL;
	struct stat stat_buf;

	/* File name.. */
	if (read(file_des, &name_length, sizeof(int)) == -1)
		goto extract_error;

	file_name = malloc(name_length);

	if (file_name == NULL)
		goto extract_error;

	if (read(file_des, file_name, name_length) == -1)
		goto extract_error;

	/* ..owner.. */
	if (read(file_des, &stat_buf.st_uid, sizeof(uid_t)) == -1)
		goto extract_error;

	/* ..group.. */
	if (read(file_des, &stat_buf.st_gid, sizeof(gid_t)) == -1)
		goto extract_error;

	/* ..permission bits.. */
	if (read(file_des, &stat_buf.st_mode, sizeof(mode_t)) == -1)
		goto extract_error;

	/* ..last time when file content was changed.. */
	if (read(file_des, &stat_buf.st_mtime, sizeof(time_t)) == -1)
		goto extract_error;

	/* ..size of file.. */
	if (read(file_des, &stat_buf.st_size, sizeof(off_t)) == -1)
		goto extract_error;

	/* ..content of file.. */
	file_buf = (byte *)malloc(stat_buf.st_size);

	if (file_buf == NULL)
		goto extract_error;

	if (read(file_des, file_buf, stat_buf.st_size) == -1)
		goto extract_error;

	f_out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT);

	if (f_out < 0)
		goto extract_error;

	write(f_out, file_buf, stat_buf.st_size);

	fchmod(f_out, stat_buf.st_mode);
	fchown(f_out, stat_buf.st_uid, stat_buf.st_gid);

	/* Maybe it is temporary solution */
	{
		struct utimbuf utim_buf;
		utim_buf.modtime = stat_buf.st_mtime;		

		utim_buf.modtime = stat_buf.st_mtime;		
		utime(file_name, &utim_buf);
	}

	printf("%s.. Complete.\n", file_name);

	return 0;

extract_error:

	close(f_out);	

	if (file_name != NULL)
		free(file_name);

	if (file_buf != NULL)
		free(file_buf);

	return -1;
}

int unpack_files( char *file_name )
{
	int f_out = open(file_name, O_RDONLY), count, i;

	if (f_out < 0)
		return -1;

	read(f_out, &count, sizeof(int));

	for (i = 0; i < count; i++)
		if (extract_file(f_out) == -1)
		{
			close(f_out);
			return -1;
		}

	close(f_out);

	return 0;
}

/*******************************************************************************
									    Archiving functions
********************************************************************************/

int add_file( char *file_name, int file_des )
{
	int f_out = open(file_name, O_RDONLY), res;
	struct stat stat_buf;
	void *file_buf;

	if (f_out < 0)
		return -1;

	res = fstat(f_out, &stat_buf);

	if (res < 0)
		return -1;

	res = (int)strlen(file_name);

	/* File name.. */
	write(file_des, &res, sizeof(int));
	write(file_des, file_name, sizeof(byte) * res);

	/* ..owner.. */
	write(file_des, &stat_buf.st_uid, sizeof(uid_t));

	/* ..group.. */
	write(file_des, &stat_buf.st_gid, sizeof(gid_t));

	/* ..permission bits.. */
	write(file_des, &stat_buf.st_mode, sizeof(mode_t));

	/* ...last time when files content was changed.. */
	write(file_des, &stat_buf.st_mtime, sizeof(time_t));

	/* ..size of file.. */
	write(file_des, &stat_buf.st_size, sizeof(off_t));

	/* ..content of file.. */
	file_buf = (byte *)malloc(stat_buf.st_size);

	if (file_buf == NULL)
	{
		close(f_out);
		return -1;
	}

	read(f_out, file_buf, stat_buf.st_size);
	write(file_des, file_buf, stat_buf.st_size);

	free(file_buf);
	close(f_out);

	return 0;
}

int archive_files( char *names[], int count, char *out_file_name )
{
	int f_out = open(out_file_name, O_CREAT | O_TRUNC | O_WRONLY), i;

	if (f_out < 0)
		return -1;

	write(f_out, &count, sizeof(int));

	for (i = 0; i < count; i++)
	{	
		int res;

		printf("%s", names[i]);

		res = add_file(names[i], f_out);

		if (res == -1)
			printf("... Failed, skipped.\n");
		else
			printf("... Complete.\n");		
	}

	fchmod(f_out, S_IRUSR | S_IROTH | S_IRGRP);
	close(f_out);

	return 0;
}

int main( int argc, char *argv[] )
{
   int i;

   if (argc <= 2)
   {
   	print_help();
      return EXIT_FAILURE;
   }

	int a = strcmp(argv[1], "-e"), b = strcmp(argv[1], "--extract"), res;

	if (a == 0 || b == 0)
	{
		res = unpack_files(argv[2]);

		if (res == -1)
		{
			printf("Error occured during files unpacking.\n");
			return EXIT_FAILURE;
		}
	}
	else
	{
		res = archive_files(argv + 1, argc - 2, argv[argc - 1]);

		if (res == -1)
			return EXIT_FAILURE;
	}

   return EXIT_SUCCESS;
}
