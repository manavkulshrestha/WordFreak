PROJECT 3 - WORD_FREAK

Manav Kulshrestha, Anthony Rinaldi

    For this project, we implemented an array-based HashMap to organize text files word by word and
output the number of times each one occured. The HashMap is a structure of HashBins, which contain
each word as a string and the frequency of each word as an integer pointer in the HashBin struct.
We use some convienient commands in the makefile to compile the .c and .h files properly. The way
the program runs is based off whether the WORD_FREAK environment variable is declared, as well as 
the value of argc in main. The program will accept files in the form of command line arguments of 
the form:

$ ./wordfreak aladdin.txt holmes.txt newton.txt


, standard input of the form:

$ cat aladdin.txt holmes.txt newton.txt | ./wordfreak


, and an environment variable WORD_FREAK=<path to single file>:

$ WORD_FREAK=aladdin.txt ./wordfreak


The HashMap includes a constructor, a hash function, an add function (to be called for each word), 
a print function, and a destructor. We typedef the size of this HashMap, as well as the maximum character
length. The output is aligned as specified, and gives the correct frequncies of each word in the files
specified. For this output, we write to STDOUT using the write() system call. We only use system calls
and sprintf() for any I/O, and check for erros in each call to any system of library call. Variables are
dynamically allocated and freed as necessary using malloc() and free().

Video For Project 3:
https://docs.google.com/document/d/1kxdB1V0PJvMia7OB8RzZwuANXVRQBMDDy5__HI2PYuY/edit?usp=sharing