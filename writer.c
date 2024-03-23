#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

/* Writer program to demonstrate writing to shared memory using a character
 * device. */

int main() {
  const char *device_path = "/dev/shmem";
  int fd;
  void *mapped_mem;
  int page_size = getpagesize(); // Get system's page size

  // Open the character device for reading and writing
  fd = open(device_path, O_RDWR);
  if (fd < 0) {
    perror("Failed to open the device");
    return EXIT_FAILURE;
  }

  // Map one page of memory
  mapped_mem = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (mapped_mem == MAP_FAILED) {
    perror("Failed to map memory");
    close(fd);
    return EXIT_FAILURE;
  }

  // Write a message to the shared memory
  const char *message = "Hello from Writer!";
  strncpy(mapped_mem, message,
          strlen(message) + 1); // +1 to include null terminator

  printf("Message written to shared memory: %s\n", message);

  // Cleanup
  munmap(mapped_mem, page_size);
  close(fd);

  return EXIT_SUCCESS;
}
