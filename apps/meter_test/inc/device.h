#ifndef __DEVICE_H__
#define __DEVICE_H__

int device_open(char *filename);
void device_close(int fd);

#endif
