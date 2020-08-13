// Amitai Popovsky 312326218

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <wait.h>
#include <time.h>
#define MAX_SIZE 900
#define NEWFILE (O_WRONLY | O_CREAT | O_TRUNC )
#define MODE600 (S_IRUSR | S_IWUSR)

// Take substring.
void substring(char s[], char sub[], int p, int l) {
  int c = 0;
  while (c < l) {
    sub[c] = s[p + c - 1];
    c++;
  }
  sub[c] = '\0';
}

// Get path to file and delete him.
void deleteFile(char *pathToFile) {
  int status = 0;
  pid_t pid = fork();
  // In case of error in fork.
  if (pid < 0) {
    char *msg = "Error in system call\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
  }
  // The child.
  if (pid == 0) {
    char *argv[] = {"rm", "-rf", pathToFile, NULL};
    if (execvp("rm", argv) < 0) {
      char *msg = "Error in system call\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    }
  } else if (pid > 0) { // The father.
    int wait = waitpid(pid, &status, 0);
    if (wait < 0) {
      char *msg = "Error in system call of wait\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    }
  }
}

// Get the arguments and files and compile and run the c file of the students. return the grade.
int callExecvp(char **tokensGcc, int inputFile, int outputFile, int errorFile, char *fileNameOutput, char *pathToFile) {
  int status = 0;
  time_t start, end;
  // Open the file for the output of the students.
  if ((outputFile = open(pathToFile, NEWFILE, MODE600)) == -1) {
    char *msg = "error in open file outputFile\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
  }
  pid_t pid = fork();
  // In case of problem at fork.
  if (pid < 0) {
    char *msg = "Error in system call\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
  } else if (pid == 0) {
    // Call the execvp.
    int val = 0;
    // Compile the student c file.
    val = execvp(tokensGcc[0], tokensGcc);
    if (val < 0) {
      char *msg = "Error in system call\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    }
  } else if (pid > 0) {
    // Call wait.
    int wait = waitpid(pid, &status, 0);
    // In case of fail in wait.
    if (wait < 0) {
      char *msg = "Error in system call of wait\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    }
    // Chae status.
    if (status != 0) {
      // Delete the file.
      deleteFile(pathToFile);
      if (close(outputFile) < 0) {
        char *msg = "After close\n";
        if (write(2, msg, strlen(msg)) < 0) {
        }
      }
      // Compile error.
      return 10;
    }
    // Check the time.
    if (time(&start) < 0) {
      char *msg = "Error in system call\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    }
    pid_t pid2 = fork();
    // In case of problem at fork.
    if (pid2 < 0) {
      char *msg = "Error in system call\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    } else if (pid2 == 0) { // The child case.
      // Change the input file with dup2.
      if (dup2(inputFile, 0) < 0) {
        char *msg = "Error in dup2\n";
        if (write(2, msg, strlen(msg)) < 0) {
        }
      }
      // Change the output file with dup2.
      if (dup2(outputFile, 1) < 0) {
        char *msg = "Error in dup2\n";
        if (write(2, msg, strlen(msg)) < 0) {
        }
      }
      // Change the error file with dup2.
      if (dup2(errorFile, 2) < 0) {
        char *msg = "Error in dup2\n";
        if (write(2, msg, strlen(msg)) < 0) {
        }
      }
      int val = 0;
      // Run the out file of the students.
      char *args2[2] = {"./student.out", NULL};
      val = execvp("./student.out", args2);
      if (val < 0) {
        char *msg = "Error in system call\n";
        if (write(2, msg, strlen(msg)) < 0) {
        }
      }
    } else if (pid2 > 0) {
      // Call to wait.
      int wait = waitpid(pid2, &status, 0);
      if (wait < 0) {
        char *msg = "Error in system call of wait\n";
        if (write(2, msg, strlen(msg)) < 0) {
        }
      }
      // To know that the time stop.
      if (time(&end) < 0) {
        char *msg = "Error in system call\n";
        if (write(2, msg, strlen(msg)) < 0) {
        }
      }
      // Check the time of the running.
      if (difftime(end, start) > 3) {
        // Delete the file.
        deleteFile(pathToFile);
        if (close(outputFile) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
        return 20;
      }
      // Arguments for running ex31.c
      char *args[] = {"./comp.out", fileNameOutput, pathToFile, NULL};
      int val = 0;
      pid_t pid3 = fork();
      if (pid3 < 0) {
        char *msg = "Error in system call\n";
        if (write(2, msg, strlen(msg)) < 0) {
        }
      }
      if (pid3 == 0) {
        // Call to exec.
        val = execvp("./comp.out", args);
        if (val < 0) {
          char *msg = "Error in system call\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
        // Call lseek to know the size of the file.
        int sizeFile = lseek(outputFile, 0, SEEK_END);
        if (sizeFile < 0) {
          char *msg = "After lseek\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
        if (lseek(outputFile, 0, SEEK_SET) < 0) {
          char *msg = "After lseek\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
      } else if (pid3 > 0) {
        int wait = waitpid(pid3, &status, 0);
        if (wait < 0) {
          char *msg = "Error in system call of wait\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
        // To know the exit status of ex31.c
        int exitStatus = WEXITSTATUS(status);
        deleteFile(pathToFile);
        if (close(outputFile) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
        // Return the grades.
        switch (exitStatus) {
          case 1:return 100;
            break;
          case 2:return 50;
            break;
          case 3:return 75;
            break;
          default:return 0;
            break;
        }
      }
    }
  }
  // Delete the file. the default case.
  deleteFile(pathToFile);
  if (close(outputFile) < 0) {
    char *msg = "After close\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  int getGrade = 0;
  int isEnterToInnerFolder = 0;
  char temp[MAX_SIZE];
  char firstPath[MAX_SIZE];
  getcwd(firstPath, MAX_SIZE);
  // Open file descriptor.
  int fdin = open(argv[1], O_RDONLY);
  if (fdin < 0) /* means file open did not take place */
  {
    char *msg = "After open\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    exit(-1);
  }
  // Check the size of the file.
  int sizeFile = lseek(fdin, 0, SEEK_END);
  if (sizeFile < 0) {
    char *msg = "After lseek\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    if (close(fdin) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    }
    exit(-1);
  }
  // Return to the right place.
  if (lseek(fdin, 0, SEEK_SET) < 0) {
    char *msg = "After lseek\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    if (close(fdin) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    }
    exit(-1);
  }
  // Buffer to the config.
  char confi[sizeFile + 1];
  // Read the config file.
  if (read(fdin, confi, sizeFile) < 0) {
    char *msg = "After read\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    if (close(fdin) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    }
    exit(-1);
  }
  if (close(fdin) < 0) {
    char *msg = "After close\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
  }
  // Tokens from config.
  char token1[MAX_SIZE];
  char token2[MAX_SIZE];
  char token3[MAX_SIZE];
  int i = 0;
  int index1 = 0;
  int index2 = 0;
  int index3 = 0;
  // To know how to cut the tokens.
  for (i = 0; i < sizeFile; i++) {
    if (confi[i] == '\n') {
      if (index1 == 0) {
        index1 = i;
      } else if (index2 == 0) {
        index2 = i;
      } else {
        index3 = i;
      }
    }
  }
  // Take substring for the tokens from the config.
  substring(confi, token1, 1, index1);
  substring(confi, token2, index1 + 2, index2 - index1 - 1);
  substring(confi, token3, index2 + 2, index3);
  // In case of a problem in the input.
  token1[strlen(token1)] = '\0';
  token2[strlen(token2)] = '\0';
  token3[index3 - index2 - 1] = '\0';
  // Open the file.
  int checkInput = open(token2, O_RDONLY);
  if (checkInput < 0) /* means file open did not take place */
  {
    char *msg = "Input File not exist\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    exit(-1);
  }
  // Open the file for the output.
  int checkOutput = open(token3, O_RDONLY);
  if (checkOutput < 0) /* means file open did not take place */
  {
    char *msg = "Output File not exist\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    if (close(checkInput) < 0) {
      char *msg = "After close\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    }
    exit(-1);
  }
  // Close the file.
  if (close(checkInput) < 0) {
    char *msg = "After close\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
  }
  if (close(checkOutput) < 0) {
    char *msg = "After close\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
  }
  struct stat stat_p;
  char *filename = token1;
  int fileStat = 0;
  if (fileStat = stat(filename, &stat_p) == -1)  //declare the 'stat' structure
  {
    char *msg = "Not a valid directory\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    exit(-1);
  }
  // Check if folder.
  if (!S_ISDIR(stat_p.st_mode)) {
    char *msg = "Not a valid directory\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
    exit(-1);
  }
  DIR *pDir;
  struct dirent *pDirent;
  // Check the dir.
  if ((pDir = opendir(token1)) == NULL) {
    char *msg = "Not a valid directory\n";
    if (write(2, msg, strlen(msg)) < 0) {

    }
    exit(-1);
  }
  int out;
  char tempPath[MAX_SIZE];
  char tempPath2[MAX_SIZE];
  // Open result.csv file.
  strcpy(tempPath, firstPath);
  strcat(tempPath, "/results.csv");
  if ((out = open(tempPath, NEWFILE, MODE600)) == -1) {
    char *msg = "error in open file output\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
  }
  int isThereCFile = 0;
  // Read the dir.
  while ((pDirent = readdir(pDir)) != NULL) {
    int flag = 0;
    getGrade = 0;
    // In case of cd .. or cd .
    if (!strcmp(pDirent->d_name, "..") || !strcmp(pDirent->d_name, ".")) {
      continue;
    }
    // Make the string for get in the folders of the user names.
    strcpy(temp, token1);
    strcat(temp, "/");
    strcat(temp, pDirent->d_name);
    DIR *pDirIn;
    struct dirent *pDirentIn;
    // Open the dir of the student.
    if ((pDirIn = opendir(temp)) == NULL) {
      if (isEnterToInnerFolder) {
        continue;
      } else {
        char *msg = "Not a valid directory\n";
        if (write(2, msg, strlen(msg)) < 0) {
        }
        if (close(out) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
        if (closedir(pDirIn) < 0) {
          char *msg = "After close Pdir\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
        if (closedir(pDir) < 0) {
          char *msg = "After close\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
        exit(-1);
      }
    } else {
      isEnterToInnerFolder = 1;
    }
    // Read the dir of the student.
    while ((pDirentIn = readdir(pDirIn)) != NULL) {
      if (!strcmp(pDirentIn->d_name, "..") || !strcmp(pDirentIn->d_name, ".")) {
        continue;
      }
      char sub[MAX_SIZE];
      substring(pDirentIn->d_name, sub, strlen(pDirentIn->d_name) - 1, 2);
      if (!(strcmp(sub, ".c"))) {
        isThereCFile = 1;
        flag = 0;
      }
      // The path to the c file.
      char pathToOutFile[MAX_SIZE];
      char buf[MAX_SIZE];
      strcpy(buf, token1);
      strcat(buf, "/");
      strcat(buf, pDirent->d_name);
      strcat(buf, "/");
      strcpy(pathToOutFile, buf);
      strcat(buf, pDirentIn->d_name);
      strcat(buf, "\0");
      // The tokens for the exec for gcc.
      char *tokensGcc[] = {"gcc", "-o", "student.out", buf, NULL};
      if (!flag && isThereCFile) {
        int outputFile = 0;
        int inputFile;
        int errorFile;
        // Open the input file.
        inputFile = open(token2, O_RDONLY);
        if (inputFile < 0) /* means file open did not take place */
        {
          char *msg = "After open inputFile\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
          if (close(out) < 0) {
            char *msg = "After close out\n";
            if (write(2, msg, strlen(msg)) < 0) {
            }
          }
          if (closedir(pDirIn) < 0) {
            char *msg = "After close Pdir\n";
            if (write(2, msg, strlen(msg)) < 0) {
            }
          }
          if (closedir(pDir) < 0) {
            char *msg = "After close Pdir\n";
            if (write(2, msg, strlen(msg)) < 0) {
            }
          }
          exit(-1);
        }
        // Open the errors file.
        strcpy(tempPath, firstPath);
        strcat(tempPath, "/errorFile.txt");
        if ((errorFile = open(tempPath, NEWFILE, MODE600)) == -1) {
          char *msg = "Error in open file errorFile\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
        // Find the path for the outfile.
        strcpy(tempPath2, firstPath);
        strcat(tempPath2, "/outputFile.txt");
        getGrade =
            callExecvp(tokensGcc, inputFile, outputFile, errorFile, token3, tempPath2);
        flag = 1;
        // Delete errorFiles.
        deleteFile(tempPath);
        deleteFile(tempPath2);
        strcpy(pathToOutFile, firstPath);
        strcat(pathToOutFile, "/student.out\0");
        // Delete student.out.
        deleteFile(pathToOutFile);
        if (close(errorFile) < 0) {
          char *msg = "After close error file\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
        if (close(inputFile) < 0) {
          char *msg = "After close input file\n";
          if (write(2, msg, strlen(msg)) < 0) {
          }
        }
      }
    }
    if (closedir(pDirIn) < 0) {
      char *msg = "After close Pdir\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    }
    // Take the strings for printing to the result.csv.
    char buf[MAX_SIZE] = "";
    strcpy(buf, pDirent->d_name);
    switch (getGrade) {
      case 0:strcat(buf, ",NO_C_FILE,0\n");
        break;
      case 10:strcat(buf, ",COMPILATION_ERROR,10\n");
        break;
      case 20:strcat(buf, ",TIMEOUT,20\n");
        break;
      case 50:strcat(buf, ",WRONG,50\n");
        break;
      case 75:strcat(buf, ",SIMILAR,75\n");
        break;
      case 100:strcat(buf, ",EXCELLENT,100\n");
        break;
      default:break;
    }
    // Close files.
    if (write(out, buf, strlen(buf)) < 0) {
      char *msg = "After write\n";
      if (write(2, msg, strlen(msg)) < 0) {
      }
    }
    isThereCFile = 0;
  }
  // Close the dir.
  if (closedir(pDir) < 0) {
    char *msg = "After close Pdir\n";
    if (write(2, msg, strlen(msg)) < 0) {
    }
  }
  return 0;
}

