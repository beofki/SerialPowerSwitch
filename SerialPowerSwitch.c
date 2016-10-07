#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

void closeSerial(int fd)
{
  if (close(fd) < 0)
  {
    perror("closeserial()");
  }
}

int openSerial(char *devicename)
{
  int fd;
  struct termios attr;

  if ((fd = open(devicename, O_RDWR)) == -1)
  {
    perror("openserial(): open()");
    return 0;
  }
  if (tcgetattr(fd, &attr) == -1)
  {
    perror("openserial(): tcgetattr()");
    return 0;
  }
  attr.c_cflag |= CRTSCTS | CLOCAL;
  attr.c_oflag = 0;
  if (tcflush(fd, TCIOFLUSH) == -1)
  {
    perror("openserial(): tcflush()");
    return 0;
  }
  if (tcsetattr(fd, TCSANOW, &attr) == -1)
  {
    perror("initserial(): tcsetattr()");
    return 0;
  }
  return fd;
}

int setDTR(int fd, int level)
{
  int status;

  if (ioctl(fd, TIOCMGET, &status) == -1)
  {
    perror("setDTR(): TIOCMGET");
    return 0;
  }
  if (level)
  {
    status |= TIOCM_DTR;
  }
  else
  {
    status &= ~TIOCM_DTR;
  }
  if (ioctl(fd, TIOCMSET, &status) == -1)
  {
    perror("setDTR(): TIOCMSET");
    return 0;
  }
  return 1;
}

int main(int argc, char *argv[])
{
  char *device = "/dev/ttyUSB0";
  int level = 1;
  int fd;

  if(argc != 3)
  {
    fprintf(stdout,"%s uses DTR on usb serial port to control a powerswitch\n", argv[0]);
    fprintf(stdout,"Usage  : %s <port> <level>\n", argv[0]);
    fprintf(stdout,"Example: %s %s %d\n", argv[0], device, level);
    return 1;
  }

  device = argv[1];
  fd = openSerial(device);
  if (!fd)
  {
    fprintf(stderr, "Error while initializing %s.\n", device);
    return 2;
  }

  level = atoi(argv[2]);
  level = !level;
  setDTR(fd, level);
  closeSerial(fd);
  return 0;
}
