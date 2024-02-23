#include <stdlib.h>/*malloc*/
#include <fcntl.h> /* open */
#include <stdio.h>/*print*/
#include <unistd.h>

#include "../include/EXT2.h"
void Program(void)
{
	handle_t *handle;
	inode_t ino;
	char path[1024];
	char select[2] = {"1"};
	char *buffer = (char *)malloc(8192);
	size_t temp;
	printf("Hello user, please enter a file's path: ");
	scanf("%s", path);
	printf("\n");

	handle = EXT2Open("/dev/ram0");
	while('\0' != select)
	{
		ino = EXT2GetFileDescriptor(handle, path);
		printf("What would you like to do?\n1 - read a file\n2 - get file size\n3 - read superblock\n4 - read file's group descriptor\n0 - leave\n");
		scanf("%s", select);
		switch (select[0])
		{
		case '0':
			free(buffer);
			buffer = NULL;
			return;
		case '1':
			printf("write number of bytes to read,\nwe support up to 8192 bytes: ");
			scanf("%lu", &temp);
			buffer = (char *)EXT2ReadBytes(handle, ino, buffer, temp);
			buffer[temp] = '\0';
			printf("%s\n\n", buffer);
			break;
		case '2':
			printf("file %s size is %ld\n\n\n", path, EXT2GetFileSize(handle, ino));
			break;
		case '3':
			EXT2PrintSuperblock(handle);
			printf("\n\n");
			break;
		case '4':
			EXT2PrintGroupDescriptor(handle, ino);
			printf("\n\n");
			break;
		default:
			break;
		}
		
	}
	free(buffer);
	buffer = NULL;
}

int main(void)
{
	handle_t *handle = EXT2Open("/dev/ram0");
	long size;
	int i = 0;
	void *buffer;
	inode_t fd = EXT2GetFileDescriptor(handle, "/ll/shlomi.txt");
	size = EXT2GetFileSize(handle,fd);
	buffer = malloc(size + 1);
	buffer = EXT2ReadBytes(handle, fd, buffer, size);
	*((char *)buffer + size) = '\0';
	/*Program();*/
	printf("%s", (char *)buffer);
	
	EXT2Chmod(handle, fd, 0777);
	
	free(buffer);
	i = EXT2Close(handle);
	return (0);
}

