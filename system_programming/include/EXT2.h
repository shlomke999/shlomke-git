#ifndef __EXT2_H_CR4__ 
#define __EXT2_H_CR4__ 

#include <stdio.h> /* Used for printing functions */
#include <stdlib.h> /* Used for malloc and free functions */
#include <stddef.h> /* Used for size_t type */
#include <string.h> /* Used for string functions */

#include "ext2_linux.h" /*EXT2 strucs*/


typedef struct process handle_t;
typedef long inode_t;

/* 
 * Description : EXT2Open opens a process in a device's ext2 filesystem. 	
 * Arguments : device - device path name.
 * Return : pointer to process handler.
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
handle_t *EXT2Open(char *device);

/* 
 * Description : EXT2Close closes a process opened at EXT2Open.
 * Arguments : process - handler recieved when user call EXT2Open.
 * Return : 0 for success, non-zero for failure
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 */
int EXT2Close(handle_t *process);

/* 
 * Description : EXT2GetFileDescriptor returns a file descriptor to user in 
 * read-write mode
 * Arguments : process - pointer to handler returned by EXT2Open, file_path
 * - complete fila path originating in fs root directory.
 * Return : file descriptor in read-write mode. negative integer indicates an 
 * error
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
inode_t EXT2GetFileDescriptor(handle_t *process, char *file_path);

/* 
 * Description : EXT2ReadBytes reads n bytes from a file into a user buffer. 
 * Arguments : process - pointer to handler returned by EXT2Open, 
 * file_descriptor - returned by EXT2GetFileDescriptor, buffer - user 
 * destination buffer, nbytes - number of bytes to read from file.
 * Return : pointer to buffer, NULL if an error occured.
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
void *EXT2ReadBytes(handle_t *process, inode_t file_descriptor, void *buffer, 
					size_t nbytes);
/* 
 * Description : EXT2GetFileSize returns a given file size.
 * Arguments : process - pointer to handler returned by EXT2Open, 
 * file_descriptor - returned by EXT2GetFileDescriptor.
 * Return : number of used bytes in a file.
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
long EXT2GetFileSize(handle_t *process, inode_t file_descriptor);

/*
 * Description : EXT2PrintSuperblock prints the content of a device's superblock.	
 * Arguments : process - pointer to handler returned by EXT2Open.	
 * Return : if a valid superblock is found, this function will print it's 
 * content to user's stdout. if not, it will print an error massege.
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 */
void EXT2PrintSuperblock(handle_t *process);

/*
 * Description : EXT2PrintGroupDescriptor prints the content of a file's group 
 * descriptor.	
 * Arguments : process - pointer to handler returned by EXT2Open, file_descriptor - returned by EXT2GetFileDescriptor.	
 * Return : if a valid group descriptor is found, this function will print it's content to stdout. if not, it will print an error massege.
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
void EXT2PrintGroupDescriptor(handle_t *process, inode_t file_descriptor);

/*
 * Description : EXT2Chmod changes the permission of a file.
 * Arguments : fs - pointer to handler returned by EXT2Open, 
 *                 file_inode - inode number returned by EXT2GetFileDescriptor.
 *                 new_mod - mode number is 4 digits, each one is 0-7.
 * Return : 0 on success, non-zero upon failure.
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 */
int EXT2Chmod(handle_t *fs, inode_t file_inode, size_t new_mod);
#endif /* __EXT2_H_CR4__ */




