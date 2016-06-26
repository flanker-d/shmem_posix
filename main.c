#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
#define SHARMEME_NAME "/test.shm"
#define SHMEM_SIZE 1048576
  int shmid = shm_open(SHARMEME_NAME, (O_CREAT | O_RDWR), 0666);
  if(shmid == -1)
  {
    perror("Ошибка при создании общей памяти: ");
    return -1;
  }

  int res = ftruncate(shmid, SHMEM_SIZE);
  if(res == -1)
  {
    perror("Ошибка при изменении размера общей памяти: ");
    return -1;
  }

  char *region_ptr = mmap(NULL, SHMEM_SIZE, (PROT_READ | PROT_WRITE), MAP_SHARED, shmid, 0);
  if(region_ptr == MAP_FAILED)
  {
    perror("Ошибка отображения файла в память: ");
    return -1;
  }
  int i = 0;
  for(i = 0; i < SHMEM_SIZE; i++)
  {
    region_ptr[i] = 0x0D;
  }

  return 0;
}
