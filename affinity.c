#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h> /* exit */
#include <unistd.h> /* sysconf */

int main(void) {
    int i, nrcpus;
    cpu_set_t mask;
    unsigned long bitmask = 0;

    // 把0号和1号1CPU加入到mask中
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    CPU_SET(1, &mask);
    // 设置CPU亲和性
    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }

    // 获取CPU情和性
    CPU_ZERO(&mask);
    if (sched_getaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_getaffinity");
        exit(EXIT_FAILURE);
    }

    // 获取逻辑CPU数量
    nrcpus = sysconf(_SC_NPROCESSORS_CONF);
    for (i = 0; i < nrcpus; i++) {
        if (CPU_ISSET(i, &mask)) {
            bitmask |= (unsigned long)0x01 << i;
            printf("processor #%d is set\n", i);
        }
    }

    printf("bitmask = %#lx\n", bitmask);

    exit(EXIT_SUCCESS);
}