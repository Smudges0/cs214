#ifndef INIT_READ_FILE
#define INIT_READ_FILE

#define INIT_READ(fileName)                          \
  int fd = open(fileName, O_RDONLY);                 \
  if (fd == -1)                                      \
  {                                                  \
    perror("File Read Error");                       \
    exit(EXIT_FAILURE);                              \
  }                                                  \
  int tokenBufSize = 10;                             \
  char *tokenBuf = (char *)malloc(tokenBufSize);     \
  if (tokenBuf == NULL)                              \
  {                                                  \
    fprintf(stderr, "out of memory for tokenBuf\n"); \
    close(fd);                                       \
    exit(EXIT_FAILURE);                              \
  }                                                  \
  int readBufSize = 1;                               \
  char *readBuf = (char *)malloc(readBufSize);       \
  if (readBuf == NULL)                               \
  {                                                  \
    fprintf(stderr, "out of memory for readBuf\n");  \
    close(fd);                                       \
    exit(EXIT_FAILURE);                              \
  }                                                  \
  int bytes_read;                                    \
  int tokenLength = 0;                               \
  int reachedEnd = 0;

#endif