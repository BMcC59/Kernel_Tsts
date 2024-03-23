#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

/* Reader program to demonstrate reading from shared memory using a character device. */

int main() {
    const char *device_path = "/dev/shmem";
    int fd;
    void *mapped_mem;
    int page_size = getpagesize(); // Get system's page size

    // Open the character device for reading
    fd = open(device_path, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }

    // Map one page of memory
    mapped_mem = mmap(NULL, page_size, PROT_READ, MAP_SHARED, fd, 0);
    if (mapped_mem == MAP_FAILED) {
        perror("Failed to map memory");
        close(fd);
        return EXIT_FAILURE;
    }

    // Read the message from shared memory
    printf("Message read from shared memory: %s\n", (char *)mapped_mem);

    // Cleanup
    munmap(mapped_mem, page_size);
    close(fd);

    return EXIT_SUCCESS;
}
