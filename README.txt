Team Members:
Nam Trinh: trinh064
Cal Carlson: carl5362
Jessica Cunningham: cunni536

Contributions:
Nam: ls.c, command parsing, file redirection, pipes
Cal: cd.c, execution logic, exit
Jessica: wc.c, README

Known Bugs:
Produces malloc error when random input is entered into the shell.
Ls does not function once cd has change current directory. Because it relies on ls.c 

Test Cases:
  For wc.c-
Ran the following commands
./wc input1.txt
./wc -l input1.txt
./wc -w input1.txt
./wc -c input1.txt
Which output the following to the terminal (in the same order as the inputs)
3    9    44
3
9
44
Using a file named input1.txt containing the text
Hello Zoey
Zoey says meow
Zoey is best girl
  For cd.c-
Ran the following commands
./cd <path>
./cd ..
./cd test/test2
  For ls.c-
Ran the following commands
./ls <path>
./ls -R <path>

Special Instructions:
ls does not accept no input. It needs to be given the current directory as an input in the form of "." 
