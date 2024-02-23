#define _XOPEN_SOURCE 500				   /* pread macro requirments */
#define _POSIX_C_SOURCE 200809L			   /* pread macro requirments */
#include <unistd.h>/*lseek*/
#include <fcntl.h> /*open*/
#include <stdlib.h>/*malloc*/
#include <stdio.h>/*print*/
#include <assert.h>/*assert*/
#include <sys/stat.h>/*lseek*/
#include <unistd.h>/*pread*/
#include <time.h>/*print time stamps */
#include <math.h>/*pow*/
#include <sys/types.h>
#include "../../include/EXT2.h"
#include "../../include/ext2_linux.h" /*EXT2 strucs*/

#define MIN2(a, b) ((a) > (b) ? (b) : (a))
#define FREE_MEMORY(ptr) {free(ptr); (ptr) = NULL;}

typedef struct ext2_dir_entry_2 dir_entry;
typedef struct ext2_super_block superblock_t;
typedef struct ext2_group_desc groupd_t;
typedef struct ext2_inode inode_struct_t;
struct process
{
	int file_desc; /*file_descriptor*/
	superblock_t superblock;
	unsigned int block_size;
};


static int read_dir(handle_t *process, inode_t ino, char *file_name);
static int read_inode(handle_t *process, inode_t inode_no, inode_struct_t *inode);
static int read_group_descriptor(handle_t *process, inode_t inode_no, groupd_t *group_desc);
static char *isolate_file_name_from_path(char *dest, char *src);



/* Status : approved.
 * Reviewer : shany.
 * Description : EXT2Open opens a process in a device's ext2 filesystem. 	
 * Arguments : device - device path name.
 * Return : pointer to process handler.
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
handle_t *EXT2Open(char *device)
{
	ssize_t a = 0, fd = 0;
	handle_t *ext2 = (handle_t *)malloc(sizeof(handle_t));
	if (NULL == ext2)
	{
		return NULL;
	}

	fd = open(device, O_RDWR);/*open sessiosn*/
	if (-1 == fd) 
	{
		FREE_MEMORY(ext2);
		return NULL;	
	}	
	/*read super block info into super block member*/
	a = pread(fd, &ext2->superblock, sizeof(superblock_t),EXT2_MIN_BLOCK_SIZE);
	if (-1 == a)
	{
		FREE_MEMORY(ext2);
		close(fd);
		return NULL;
	}
	ext2->block_size = EXT2_BLOCK_SIZE(&ext2->superblock);
	ext2->file_desc = fd;
	return ext2;
}


/* 
 *Status : approved
 * Reviewer : shany
 * Description : EXT2Close closes a process opened at EXT2Open.
 * Arguments : process - handler recieved when user call EXT2Open.
 * Return : 0 for success, -1 for failure
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 */
int EXT2Close(handle_t *process)
{
	int res = close(process->file_desc);
	FREE_MEMORY(process);
	return res;
}


/* 
 *Status : approved
 * Reviewer : shany
 * Description : EXT2GetFileDescriptor returns the inode number of a file.
 * Arguments : process - pointer to handler returned by EXT2Open, file_path
 * - complete fila path originating in fs root directory.
 * Return : file_desc in read-write mode. negative integer indicates an 
 * error
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
inode_t EXT2GetFileDescriptor(handle_t *process, char *file_path)
{
	inode_t inode_no = EXT2_ROOT_INO;
	char *current_path = file_path;
	char path_temp[EXT2_NAME_LEN];
	/* traverse the path until find the file_path inode*/
	while ('\0' != *current_path)
	{
		current_path += 1;
		current_path = isolate_file_name_from_path(path_temp, current_path);
		/*send root inode number and our path_temp(wich is specific directory at a time) to read dir helper func*/
		if (0 > (inode_no = read_dir(process, inode_no, path_temp)))
		{
			return -1;
		}
	}
	return inode_no;		
}



/* Status : approved.
 * Reviewer : shany.
 * Description : find a file's size
 * Arguments : handler and an inode number
 * Return : size of a file in bytes or -1 if error
 */
long EXT2GetFileSize(handle_t *process, inode_t inode_no)
{
	long a = 0;
	inode_struct_t inode;	
	
	/*read inode_no inode, to inode var*/
	a = read_inode(process, inode_no, &inode);
	if (-1 == a)
	{
		return -1;
	}
	return inode.i_size;
}


/* 
 *Status : approved
 * Reviewer : shany
 * Description : EXT2ReadBytes reads n bytes from a file into a user buffer. 
 * Arguments : process - pointer to handler returned by EXT2Open, 
 * file_descriptor - returned by EXT2GetFileDescriptor, buffer - user 
 * destination buffer, nbytes - number of bytes to read from file.
 * Return : pointer to buffer, NULL if an error occured.
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
void *EXT2ReadBytes(handle_t *process, inode_t inode_no, void *buffer,
					size_t nbytes)
{
	int a = -1;
	size_t i = 0, bytes_read = 0, bytes_to_read;
	inode_struct_t inode;
	/*read inode mumber inode, to inode var*/
	a = read_inode(process, inode_no, &inode);
	if (-1 == a)
	{
		return NULL;
	}

	while (0 < inode.i_block[i] && i < 12)
	{
		bytes_to_read = MIN2(nbytes, process->block_size);
		a = pread(process->file_desc, (char *)buffer + bytes_read, bytes_to_read,
							   (inode.i_block[i] * process->block_size));
		if (-1 == a)
		{
			return NULL;
		}
		++i;
		nbytes -= bytes_to_read;
		bytes_read += bytes_to_read;
	}
	return buffer;
}


/*helper func for chmod*/
size_t OctalToDecimal(size_t num)
{
    size_t decimal = 0, i = 0;
    while (num != 0)
    {
        decimal =  decimal +(num % 10)* pow(8, i++);
        num = num / 10;
    }
    return decimal;
}
/*
 *Status : approved.
 * Reviewer : shany.
 * Description : EXT2Chmod changes the permission of a file.
 * Arguments : fs - pointer to handler returned by EXT2Open, 
 *                 file_inode - inode number returned by EXT2GetFileDescriptor.
 *                 new_mod - mode number is 4 digits, each one is 0-7.
 * Return : 0 on success, non-zero upon failure.
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 */
int EXT2Chmod(handle_t *fs, inode_t file_inode, size_t new_mod)
{
	inode_struct_t inode;
	groupd_t group_desc;
	short unsigned mod = new_mod;
	if (new_mod > 511)/*then we need conversion cuase the first of the four digits is not 0*/
	{
		mod = OctalToDecimal(new_mod);
	}
	if (-1 == read_inode(fs, file_inode, &inode))
	{
		return -1;
	}
	if (-1 == read_group_descriptor(fs, file_inode, &group_desc))
	{
		return -1;
	}
	/*reset 12 bits represent curr file permissions*/ 
	inode.i_mode = ((inode.i_mode >> 12) << 12 );
	/*make mod bits of i_mode and mod combine, and then it's ready to insert to inode.i_mode*/
	mod = inode.i_mode | mod; 
	
	if (-1 == pwrite(fs->file_desc, &mod, sizeof(inode.i_mode), (group_desc.bg_inode_table * 
				fs->block_size) + ((file_inode - 1) * fs->superblock.s_inode_size)))
	   {
			return -1;
	   }	
	return 0;	
}





/* reads inode by inode number */
/* read directory entries to a buffer */
static int read_dir(handle_t *process, inode_t ino, char *file_name)
{
	int inode_no;
	void *block;
	ssize_t file_size;
	inode_struct_t inode;
	dir_entry *entry;
	read_inode(process, ino, &inode);
	file_size = inode.i_size;
	if ((block = malloc(file_size + 1)) == NULL)
	{
		return -1;
	}
	/*read file_size bytes from the file with inode_num ino, to block var*/
	EXT2ReadBytes(process, ino, block, file_size);
	entry = (dir_entry *)block;
	while (0 != entry->inode)
	{
		if (!strcmp(entry->name, file_name))
		{
			inode_no = entry->inode;
			FREE_MEMORY(block);
			return inode_no;
		}
		entry = (dir_entry *)((char *)entry + entry->rec_len);
	}
	FREE_MEMORY(block);
	return -1;
}


/* read an inode to a buffer */
static int read_inode(handle_t *process, inode_t inode_no, inode_struct_t *inode)
{
	int valid = -1;
	groupd_t group_desc;
	valid = read_group_descriptor(process, inode_no, &group_desc);
	if (-1 == valid)
	{
		return -1;
	}
	/*move fd to the inode entry at the inode table, and read it to inode arg*/
	valid = pread(process->file_desc, inode, 
				sizeof(inode_struct_t), (group_desc.bg_inode_table * 
				process->block_size) + ((inode_no - 1) * 
				process->superblock.s_inode_size));
	return valid;
} 


/* helpers to EXT2GetFileDescriptor */
/* isolate path directories */
static char *isolate_file_name_from_path(char *dest, char *src)
{
	int i = 0;
	for (i = 0; '/' != *src && '\0' != *src ; ++i)
	{
		dest[i] = *src;
		++src;
	}
	dest[i] = '\0';
	return src;
}


/* read a group descriptor to a group_desc arg */
static int read_group_descriptor(handle_t *process, inode_t inode_no, groupd_t *group_desc)
{
	int a = pread(process->file_desc, group_desc, sizeof(groupd_t), process->block_size + (process->block_size * ((inode_no - 1) / 
				process->superblock.s_inodes_per_group)));
	return (a == -1)? -1 : 0;
}



/*
 *Status : approved
 * Reviewer : shany
 *description: print super block fields*/
void EXT2PrintSuperblock(handle_t *process)
{
	int i;
	time_t stamp;
	char categories[40][255] = {"Filesystem volume name: ",
								"Last mounted on: ",
								"Filesystem UUID: ",
								"Filesystem magic number: ",
								"Filesystem revision #: ",
								"Filesystem features: ",

								"Filesystem state: ",
								"Errors behavior: ",
								"Filesystem OS type: ",
								"Inode count: ",
								"Block count: ",
								"Reserved block count: ",
								"Free blocks: ",
								"Free inodes: ",
								"First block: ",
								"Block size: ",
								"Fragment size: ",
								"Blocks per group: ",
								"Fragments per group: ",
								"Inodes per group: ",
								"Last mount time: ",
								"Last write time: ",
								"Mount count: ",
								"Maximum mount count: ",
								"Last checked: ",
								"Check interval: ",
								"Reserved blocks uid: ",
								"Reserved blocks gid: ",
								"First inode: ",
								"Inode size: "};

	printf("%s%s \n", categories[0], process->superblock.s_volume_name);
	printf("%s%s \n", categories[1], process->superblock.s_last_mounted);
	printf("%s%x", categories[2], process->superblock.s_uuid[0]);
	for (i = 1; i < 16; ++i)
	{
		printf("%x", process->superblock.s_uuid[i]);
	}
	printf("\n");
	printf("%s0x%X \n", categories[3], process->superblock.s_magic);
	printf("%s%u \n", categories[4], process->superblock.s_rev_level);
	printf("%s%u %u %u \n", categories[5],
		   process->superblock.s_feature_ro_compat,
		   process->superblock.s_feature_compat,
		   process->superblock.s_feature_incompat);
	printf("%s%s \n", categories[6], (process->superblock.s_state) ? "unknown" : "not-clean");
	printf("%s%s \n", categories[7], (process->superblock.s_errors) ? "continue" : "unknown");
	printf("%s%s \n", categories[8], (process->superblock.s_creator_os) ? "unknown" : "Linux");
	printf("%s%u \n", categories[9], process->superblock.s_inodes_count);
	printf("%s%u \n", categories[10], process->superblock.s_blocks_count);
	printf("%s%u \n", categories[11], process->superblock.s_r_blocks_count);
	printf("%s%u \n", categories[12], process->superblock.s_free_blocks_count);
	printf("%s%u \n", categories[13], process->superblock.s_free_inodes_count);
	printf("%s%u \n", categories[14], process->superblock.s_first_data_block);
	printf("%s%u \n", categories[15], EXT2_BLOCK_SIZE(&process->superblock));
	printf("%s%d \n", categories[16], EXT2_FRAG_SIZE(&process->superblock));
	printf("%s%u \n", categories[17], process->superblock.s_blocks_per_group);
	printf("%s%u \n", categories[18], process->superblock.s_frags_per_group);
	printf("%s%u \n", categories[19], process->superblock.s_inodes_per_group);
	stamp = process->superblock.s_mtime;
	printf("%s%s", categories[20], asctime(gmtime(&stamp)));
	stamp = process->superblock.s_wtime;
	printf("%s%s", categories[21], asctime(gmtime(&stamp)));
	printf("%s%u \n", categories[22], process->superblock.s_mnt_count);
	printf("%s%d \n", categories[23], process->superblock.s_max_mnt_count);
	stamp = process->superblock.s_lastcheck;
	printf("%s%s", categories[24], asctime(gmtime(&stamp)));
	printf("%s%u \n", categories[25], process->superblock.s_checkinterval);
	printf("%s%u \n", categories[26], process->superblock.s_def_resuid);
	printf("%s%u \n", categories[27], process->superblock.s_def_resgid);
	printf("%s%u \n", categories[28], process->superblock.s_first_ino);
	printf("%s%u \n", categories[29], process->superblock.s_inode_size);
}

/* Status : approved
 * Reviewer : shany
 * Description : prints group descriptor content to terminal
 * Arguments : handle pointer and inode number
 * Return : nothing
 */
void EXT2PrintGroupDescriptor(handle_t *process, inode_t inode_no)
{
	groupd_t group;
	int read_val = read_group_descriptor(process, inode_no, &group);
	if (0 > read_val)
	{
		return;
	}
	printf("group #: %ld \n", ((inode_no - 1) /
							   process->superblock.s_inodes_per_group));
	printf("%s%u \n", "blocks bitmap at: ", group.bg_block_bitmap);
	printf("%s%u \n", "inodes bitmap at: ", group.bg_inode_bitmap);
	printf("%s%u \n", "inode table at: ", group.bg_inode_table);
	printf("%s%u \n", "free blocks: ", group.bg_free_blocks_count);
	printf("%s%u \n", "free inodes: ", group.bg_free_inodes_count);
	printf("%s%u \n", "used directories: ", group.bg_used_dirs_count);
}














