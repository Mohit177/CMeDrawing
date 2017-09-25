# CMeDrawing
ComputerGraphics_Assignment1

enter command on linux:
g++ -std=c++14 main.cpp -lGL -lglfw 
to compile

./a.out to run
./a.out reads input dInstr.txt

Drawing Instructions
In the file dInstr.txt, input format is as follows:
First Line contains no of Graftals to be drawn (t)
For each of the t-cases: 


{no. of rules:int} {axiom:string}
Next N lines have rules described like:
{nonterminal:char}:{rule:string}
Then next line contains,
{no_of_iterations:int} {angle:int} {length:int} {thickness:int}
{starting point x:double} {starting point y:double}
{type}
if(type==1)
Follows input {Lower bound x} {Lower Bound y} {Upper bound x} {Upper Bound y} all double type.
else if(type==0)
Nothing