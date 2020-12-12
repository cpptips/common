#include <stdint.h>
#include <strings.h>

#include <iostream>
using namespace std;

// POD（Plain Old Data）结构体和C语言中的结构体兼容，能够正常使用memcpy memset
// bzero等函数，如下所示Options就是一个POD
// 对POD类/结构体，我们可以在构造函数中使用bzero初始化内存
struct Options {
    Options() { bzero(this, sizeof(*this)); }
    uint16_t tcpport;
    uint16_t udpport;
    uint16_t gperfport;
    int threads;
};

int main(int argc, char const *argv[]) {
    Options options;
    // memset(&options, 0, sizeof(options));
    // memset这一步可以省去，可以让我们在使用对象的时候更便捷
    std::cout << "options.tcpport:" << options.tcpport << std::endl;
    std::cout << "options.udpport:" << options.udpport << std::endl;
    std::cout << "options.gperfport:" << options.gperfport << std::endl;
    std::cout << "options.threads:" << options.threads << std::endl;

    Options *op = new Options();
    std::cout << "op->tcpport:" << op->tcpport << std::endl;
    std::cout << "op->udpport:" << op->udpport << std::endl;
    std::cout << "op->gperfport:" << op->gperfport << std::endl;
    std::cout << "op->threads:" << op->threads << std::endl;
    return 0;
}
// 测试
/*
[root@localhost common]# g++ pod_init.cpp -o pod_init
[root@localhost common]# ./pod_init
options.tcpport:0
options.udpport:0
options.gperfport:0
options.threads:0
op->tcpport:0
op->udpport:0
op->gperfport:0
op->threads:0
*/

// Options from muduo
