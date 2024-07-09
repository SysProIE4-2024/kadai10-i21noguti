/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

// system関数のクローン
char *execpath = "/bin/sh";


int mysystem(char *command) {
  int status = 0;
  
  // ここにプログラムを書く
  int pid = 0;
  if(command == NULL) {
    fprintf(stderr, "commandでエラー発生\n");
    return 1;
  }
  pid = fork();
  if(pid < 0) {
    fprintf(stderr, "forkでsラー発生\n");
    return -1;
  } else if(pid != 0) {
      while(wait(&status) != pid) {
        ;
      }
  }else {
    execl(execpath, "sh", "-c", command, NULL);
    perror(execpath);
    exit(127);
  }
  return status;
}



/* 実行例

ここに実行例を書く
 % make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c

% ls -l
total 616
-rw-r--r--  1 noguchiai  staff     143  7  4 09:42 Makefile
-rw-r--r--  1 noguchiai  staff    2795  7  4 09:42 README.md
-rw-r--r--@ 1 noguchiai  staff  238232  7  4 09:42 README.pdf
-rwxr-xr-x  1 noguchiai  staff   50392  7  9 22:58 mysysmain
-rw-r--r--  1 noguchiai  staff     925  7  4 09:42 mysysmain.c
-rw-r--r--@ 1 noguchiai  staff    2133  7  9 22:58 mysystem.c
-rw-r--r--  1 noguchiai  staff      90  7  4 09:42 mysystem.h

% ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 noguchiai  staff     143  7  4 09:42 Makefile
-rw-r--r--  1 noguchiai  staff    2795  7  4 09:42 README.md
-rw-r--r--@ 1 noguchiai  staff  238232  7  4 09:42 README.pdf
-rwxr-xr-x  1 noguchiai  staff   50392  7  9 22:58 mysysmain
-rw-r--r--  1 noguchiai  staff     925  7  4 09:42 mysysmain.c
-rw-r--r--@ 1 noguchiai  staff    2133  7  9 22:58 mysystem.c
-rw-r--r--  1 noguchiai  staff      90  7  4 09:42 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 noguchiai  staff     143  7  4 09:42 Makefile
-rw-r--r--  1 noguchiai  staff    2795  7  4 09:42 README.md
-rw-r--r--@ 1 noguchiai  staff  238232  7  4 09:42 README.pdf
-rwxr-xr-x  1 noguchiai  staff   50392  7  9 22:58 mysysmain
-rw-r--r--  1 noguchiai  staff     925  7  4 09:42 mysysmain.c
-rw-r--r--@ 1 noguchiai  staff    2133  7  9 22:58 mysystem.c
-rw-r--r--  1 noguchiai  staff      90  7  4 09:42 mysystem.h
retval = 00000000

% ./mysysmain "aaa"
mysystem:
sh: aaa: command not found
retval = 00007f00
system:
sh: aaa: command not found
retval = 00007f00


% ./mysysmain ls -l
使い方 : ./mysysmain コマンド文字列
% ./mysysmain
使い方 : ./mysysmain コマンド文字列


*/
