#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    setreuid(geteuid(), geteuid());
    system("id");
    return 0;
}

/*
file owner: ngườii muốn print id ra

(root)
g++ bai2.cpp -o bai2
sudo chown user2 bai2
sudo chmod +x bai2
sudo chmod +s bai2

(user1)
./bai2
*/
