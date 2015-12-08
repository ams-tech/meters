#ifndef __METER_TEST_H__
#define __METER_TEST_H__

#define DEBUG

#ifdef DEBUG
#define PRINT_DEBUG(x) printf x
#else
#define PRINT_DEBUG(x)
#endif

#define TEST_NAME_LEN	50

typedef int (*meter_test_f)(char * device, int argc, char *argv[]);

typedef struct meter_test_X
{
	char test_name[TEST_NAME_LEN];
	meter_test_f execute;
}meter_test_t;

int test_read_magic_number(char * device, int argc, char*argv[]);

#endif
