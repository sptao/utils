#include <sys/mman.h>
#include <stdio.h>
#include <memory.h>
#include <sys/time.h>
#include <stdlib.h>
#define PAGE_SIZE (1024 * 1024 * 2)
#define NUM_REPEAT 100

void mem_speed_test(void *addr, size_t size, unsigned n_repeat, char *name)
{
	struct timeval t1, t2;
	double cost;
	double speed;
	int i;
	if (addr == NULL || size == 0 || n_repeat == 0 || name == NULL) {
		printf("Test failed, params error\n");
	}

	gettimeofday(&t1, 0);
	for (i = 0; i < NUM_REPEAT; i++) {
		memset(addr, 0, size);
	}
	gettimeofday(&t2, 0);
	cost = ((t2.tv_sec - t1.tv_sec) * 1000 * 1000 + (t2.tv_usec - t1.tv_usec)) / 1.0e6;
	speed = size * NUM_REPEAT / cost / (1024 * 1024);
	printf("Test for %s: speed = %.3lfMB/s, time cost = %.3lf\n", name, speed, cost);
}
 
int main(int argc, char *argv[]) {
	void *m_huge = NULL, *m_norm = NULL;
	size_t s = 61 * PAGE_SIZE;
			 
	m_norm = malloc(s); 
	m_huge = mmap(NULL, s, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);
	if (m_huge == MAP_FAILED) {
		perror("map mem");
		m_huge = NULL;
		return 1;
	}

	mem_speed_test(m_norm, s, NUM_REPEAT, "normal page");
	mem_speed_test(m_huge, s, NUM_REPEAT, "huge page");
				   
	printf("map_hugetlb ok, press ENTER to quit!\n");
	//getchar();
	
	free(m_norm);
	munmap(m_huge, s);
	return 0;
}

