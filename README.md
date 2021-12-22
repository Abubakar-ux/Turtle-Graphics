# Turtle-Graphics (C)


There's only so much you can do with the program we have so far in turtle.c, since 
you have to hard code in every single command so far. We are now going to extend the 
program by adding support for loops! These will give you a lot more power to draw more
complex shapes with some repetitive elements without having to manually specify each
individual move.

We're going to use the same data type (CmdNode) for the loop command, however we will
have to add an additional field to keep track of all of the commands that are a part of
the loop (in - you guessed it - another linked list!). 

The name for this command will simply be "loop", and the value it has will represent the
number of iterations (how many times you will run all the commands in the loop).

We won't quite be implementing all the functions from Part 1 here, because the general
concept of all of them remains the same, however some of them are a lot more tedious to
code out correctly because of the nature of the nested lists. (However, if you were 
needed to, you should still know how to code these out.)

------------------------------------------------------------------------------------------

Here's what you need to do to implement this:

(1) Copy the file turtle.c, call it turtle-pro.c

(2) Add a new field called 'loop_head' to the CmdNode struct which
    is a pointer to a struct of the same type. This will be the head of
    the linked list of commands that are in the loop. It should be set to 
    NULL for commands of any other type.

(3) Add a function called insertCommandLoop(). This function will be used to insert
    a command at the end of the linked list for a 'loop' node. It will take in 2 
    parameters, the first will be a pointer to the loop node, and the second will 
    be a pointer to the new command node that you have to insert into the loop. 
    This function should not return anything, but just update the linked list at 
    the loop node.

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* NOTE: When you insert a 'loop' command into list using the interactive
*       driver, it will then prompt you to enter all the commands that are
*       a part of the loop one by one. Alternatively, you can write all your
*       commands in a text file (look at box-pro.txt) and then load them in
*       through the interactive driver.
*
*       We will NOT be worrying about nested loops for now, you will learn how 
*       to handle that later in the course! 
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

(4) Modify the countCommands() function to now also count each command inside
    any loops you may have. Make sure each CmdNode is counted exactly once.
    For the example below, countCommands() should return 5.

(5) Modify printCommandList() to print out all the commands in your loops as well. 
    Any commands that are inside a loop should be indented by 2 spaces, for example:

"""
  0: forward 100
  1: loop 4
  2:   forward 10
  3:   left
  4: right
  ...
"""

(6) Modify the queryByCommand() function to now also search within the loops. You 
    don't need to worry about indentation here. For example, a query for 'forward' 
    in the above example should give

"""
  0: forward 100
  2: forward 10
"""

(7) Modify deleteCommandList() so that it now also frees all the nodes that are
    in a loop command.

(8) Modify the run() command so you now also run all the commands in the loops the 
    appropriate number of times. For instance, if you have a 'loop 4', then all the
    commands in the loop should be run 4 times.

--- You can remove the insertCommandBefore(), updateCommand() and deleteCommand() functions.
--- Feel free to implement then and leave them in if you want some more practice, however
--- you will NOT be marked on any of them.

------------------------------------------------------------------------------------------

The Part2_driver.c file contains test cases for all of the functions you will be tested on.
Ensure that you see how these tests are set up so you know how your code is expected to run.

------------------------------------------ FIN -------------------------------------------
