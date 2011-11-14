## Makefile for v4l2 test
## Note:
## 	  Since the infomation of what function the Source File
## 	  want to show is indicated by the name of the directory,
##    the names of the Source Files all the same are called 
##    example.c. Beside all source file include ../include/v4l2-util.h
##    header file, and this file contains all the useful functions.

obj-target := example
obj-src := ${obj-target}.c
out-dir := ../../out/

default:
	gcc -Wall -o ${out-dir}${obj-target} ${obj-src}
clean:
	rm -rf ${obj-target}.o
