#######
#
# Common Lib Makefile
#

targetSo      = libhelloworld.so
targetA       = libhelloworld.a
targetTestSo  = testSo
targetTestA   = testA

src = helloworld.c
srcTest = test.c

obj = $(src:.c=.o)
objTest = $(srcTest:.c=.o)

#####
all : $(targetSo) $(targetTestSo) $(targetA) $(targetTestA)

# .so file
$(targetSo) : $(obj)
	gcc -Wall -shared -o $@ $(obj)

$(targetTestSo) : $(objTest)
	gcc -Wall -o $@ $(objTest) -L. -lhelloworld

# .a file
$(targetA) : $(obj)
	ar cru $@ $(obj)

$(targetTestA) : $(objTest)
	gcc -Wall -o $@ $(objTest) -L. -static -lhelloworld

.c.o:
	gcc -Wall -o $@ -c $<

#####
clean : 
	rm $(targetSo) $(targetTestSo) $(obj) $(objTest) $(targetA) $(targetTestA)


#
# By so file, test result
#
# 1)
# mcc@ubuntu:~/git/MyGit/sampleSo$ ./test 
# ./test: error while loading shared libraries: libhelloworld.so: cannot open shared object file: No such file or directory
#
# 2)
# mcc@ubuntu:~/git/MyGit/sampleSo$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
# mcc@ubuntu:~/git/MyGit/sampleSo$ ./test 
# In test process, use lib.
# Hello World.
# 
# 3)
# mcc@ubuntu:~/git/MyGit/sampleSo$ ./testA
# In test process, use lib.
# Hello World.
