#define SIZE 100
#define PM_PASSWORD 0x5a000000
#define PM_RSTC 0x3F10001c
#define PM_WDOG 0x3F100024

char command[][100] = { "help", "hello", "gettime", "reboot"};
void hello();
void help();
void shell();
