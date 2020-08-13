// Amitai Popovsky 312326218

#include <stdio.h>
#include <sys/fcntl.h>
#include<stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
  int fdin1;           /* input file descriptor */
  int fdin2;          /* input file descriptor */
  int bigFile;
  int smallFile;
  int sizeBigFile;
  int sizeSmallFile;
  int counter = 0;
  int charsr1;          /* how many chars were actually red */
  int charsr2;
  // Open file desctiptors.
  fdin1 = open(argv[1], O_RDONLY);
  fdin2 = open(argv[2], O_RDONLY);
  if (fdin1 < 0) /* means file open did not take place */
  {
    char *msg = "After open\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    exit(-1);
  }
  if (fdin2 < 0) /* means file open did not take place */
  {
    char *msg = "After open\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    if (close(fdin1) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }      /* free allocated structures */
    exit(-1);
  }
  // To know who is the bigger file.
  int sizeFile1 = lseek(fdin1, 0, SEEK_END);
  int sizeFile2 = lseek(fdin2, 0, SEEK_END);
  // In case of problems in lseek.
  if (sizeFile1 < 0) {
    char *msg = "After lseek\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    if (close(fdin1) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }        /* free allocated structures */
    if (close(fdin2) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }
    exit(-1);
  }
  // In case of problems in lseek.
  if (sizeFile2 < 0) {
    char *msg = "After lseek\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    if (close(fdin1) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }       /* free allocated structures */
    if (close(fdin2) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }
    exit(-1);
  }
  // Change back the file descriptor to the start.
  if (lseek(fdin1, 0, SEEK_SET) < 0) {
    char *msg = "After lseek\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    if (close(fdin1) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }       /* free allocated structures */
    if (close(fdin2) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }
    exit(-1);
  }
  // Change back the file descriptor to the start.
  if (lseek(fdin2, 0, SEEK_SET) < 0) {
    char *msg = "After lseek\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    if (close(fdin1) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }       /* free allocated structures */
    if (close(fdin2) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }
    exit(-1);
  }
  // Check who is the bigger file.
  if (sizeFile1 > sizeFile2) {
    bigFile = fdin1;
    sizeBigFile = sizeFile1;
    smallFile = fdin2;
    sizeSmallFile = sizeFile2;
  } else {
    bigFile = fdin2;
    sizeBigFile = sizeFile2;
    smallFile = fdin1;
    sizeSmallFile = sizeFile1;
  }
  int i = 0;
  int j = 0;
  // Buffers for reading.
  char bufBig[sizeBigFile + 1];
  char bufSmall[sizeSmallFile + 1];
  // In case of that the small file in size 0.
  if (sizeSmallFile == 0) {
    if (close(fdin1) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }        //free allocated structures
    if (close(fdin2) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }
    // In case of both of the files in size 0.
    if (sizeBigFile == 0) {
      exit(1);
    }
    exit(3);
  }
  // Reading the files.
  charsr1 = read(bigFile, bufBig, sizeBigFile);
  charsr2 = read(smallFile, bufSmall, sizeSmallFile);
  // In problem of reading the files.
  if (charsr1 < 0 || charsr2 < 0) {
    char *msg = "After read\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    if (close(fdin1) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }       /* free allocated structures */
    if (close(fdin2) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }
    exit(-1);
  }
  // Counter of the same characters from one side.
  for (i = 0; i < sizeBigFile; i++) {
    for (j = 0; j < sizeSmallFile; j++) {
      if (i + j >= sizeBigFile || j >= sizeSmallFile) {
        break;
      }
      if (bufBig[i + j] == bufSmall[j]) {
        counter++;
      }
    }
    // Check if there is a similliar with half of the charecters of the small file.
    if (counter * 2 >= sizeSmallFile && counter != 0) {
      if (counter == sizeBigFile && counter == sizeSmallFile) {
        if (close(fdin1) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
          exit(-1);
        }       /* free allocated structures */
        if (close(fdin2) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
          exit(-1);
        }
        exit(1);
      } else {
        if (close(fdin1) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
          exit(-1);
        }       /* free allocated structures */
        if (close(fdin2) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
          exit(-1);
        }
        exit(3);
      }
      break;
    } else {
      counter = 0;
    }
  }
  // Counter of the same characters from other side.
  for (i = 0; i < sizeSmallFile; i++) {
    for (j = 0; j < sizeBigFile; j++) {
      if (i + j >= sizeSmallFile || j >= sizeBigFile) {
        break;
      }
      if (bufBig[j] == bufSmall[i + j]) {
        counter++;
      }
    }
    // Check if there is a similliar with half of the charecters of the small file.
    if (counter * 2 >= sizeSmallFile && counter != 0) {
      if (counter == sizeBigFile && counter == sizeSmallFile) {
        if (close(fdin1) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
          exit(-1);
        }       /* free allocated structures */
        if (close(fdin2) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
          exit(-1);
        }
        exit(1);
      } else {
        if (close(fdin1) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
          exit(-1);
        }       /* free allocated structures */
        if (close(fdin2) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
          exit(-1);
        }
        exit(3);
      }
      break;
    } else {
      counter = 0;
    }
  }
  if (close(fdin1) < 0) {
    char *msg = "After close\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    if (close(fdin2) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
      exit(-1);
    }
    exit(-1);
  }       /* free allocated structures */
  if (close(fdin2) < 0) {
    char *msg = "After close\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    exit(-1);
  }
  // The default case.
  exit(2);
}