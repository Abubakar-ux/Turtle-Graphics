#define SIZEX 512
#define SIZEY 512

#include "turtle-pro.c"

int checkNode(CmdNode *a, char cmd[10], int val) {
  return (strcmp(a->cmd, cmd) == 0 && a->val == val);
}

int main() {
  Image *im;
  CmdNode *head = NULL;
  CmdNode *tmp = NULL;
  int val, i, j, ex, ey;

  printf("Running tests...\n");

  /*-------------------------------------------------------------------------*/


  // These should work exactly the same as the turtle.c, nothing has changed.
  head = insertCommand(head, newCmdNode("penup", 0));
  head = insertCommand(head, newCmdNode("forward", 100));
  head = insertCommand(head, newCmdNode("right", 0));
  head = insertCommand(head, newCmdNode("forward", 100));
  head = insertCommand(head, newCmdNode("pendown", 0));

  // Test 0, Creating a node with "loop" command
  tmp = newCmdNode("loop", 4);
  if (tmp == NULL) {
    printf("Test 0 failed, newCmdNode() did not initialize node properly.\n");
    return 1;
  } else if (!checkNode(tmp, "loop", 4) || tmp->next != NULL ||
             tmp->loop_head != NULL) {
    printf("Test 0 failed, Incorrect data in new node.\n");
    return 1;
  }
  printf("Test 0 passed.\n");

  /*-------------------------------------------------------------------------*/


  // Test 1, Inserting elements into an empty loop-list at the tail
  insertCommandLoop(tmp, newCmdNode("forward", 300));
  insertCommandLoop(tmp, newCmdNode("left", 0));
  head = insertCommand(head, tmp);
  if (tmp->loop_head == NULL) {
    printf("Test 1 failed, loop_head is still NULL.\n");
    return 1;
  } else if (!checkNode(tmp->loop_head, "forward", 300) ||
             !checkNode(tmp->loop_head->next, "left", 0) ||
             tmp->loop_head->next->next != NULL) {
    printf(
        "Test 1 failed, failed to insert correctly into the list for loop.\n");
    return 1;
  }
  printf("Test 1 passed.\n");

  /*-------------------------------------------------------------------------*/


  // Test 2, Counting the number of commands in the nested lists
  val = countCommands(head);
  if (val != 8) {
    printf("Test 2 failed, countCommands() did not return correct value.\n");
     return 1;
  }
  printf("Test 2 passed.\n");

  /*-------------------------------------------------------------------------*/


  // Test 3, Testing the run function. Result should be identical to
  //          test #10 from the Part 1 driver.

  im = newImage(SIZEX, SIZEY);
  run(im, head, &ex, &ey);

  // The image should be exactly as expected, this checks every pixel to
  // make sure it matches.
  for (i = 0; i < SIZEX; i++) {
    for (j = 0; j < SIZEY; j++) {
      if (((i == 100 || i == 400) && j >= 100 && j <= 400) ||
          ((j == 100 || j == 400) && i >= 100 && i <= 400)) {
        if (im->data[i + j * SIZEX] != 0) {
          printf("Test 11 failed, Pixel at (%d, %d) is %d, should be 0\n", i, j,
                 im->data[i + j * SIZEX]);
          return 1;
        }
      } else if (im->data[i + j * SIZEX] != 255) {
        printf("Test 11 failed, Pixel at (%d, %d) is %d, should be 255\n", i, j,
               im->data[i + j * SIZEX]);
        return 1;
      }
    }
  }
  if (ex != 100 || ey != 100) {
    printf("Test 3 failed, end location of the turtle should be (100, 100)\n");
    return 1;
  }
  deleteImage(im);
  printf("Test 3 passed.\n");

  /*-------------------------------------------------------------------------*/


  // Test 4, printing out the command list
  printf("Test 4, check this yourself!\n");
  /* This needs to be inspected manually. Here is the expected output:
    0: penup
    1: forward 100
    2: right
    3: forward 100
    4: pendown
    5: loop 4
    6:   forward 300            // Indented by 2 spaces more than the
    7:   left                   // lines outside the loop
  */
  printCommandList(head);

  /*-------------------------------------------------------------------------*/


  // Test 5, querying the list for "forward"
  printf("Test 5, check this yourself!\n");
  /* This needs to be inspected manually. Here is the expected output:
    1: forward 100
    3: forward 100
    6: forward 300            // Note that there's no indent
  */
  queryByCommand(head, "forward");
  
  /*-------------------------------------------------------------------------*/


  // Test 6, Deleting the list
  head = deleteCommandList(head);
  if (head != NULL) {
    printf("Test 6 failed, head is not NULL after deleting list.\n");
    return 1;
  } else if ((val = countCommands(head))) {
    printf("Test 6 failed, countCommands() says %d commands in list.\n", val);
    return 1;
  }
  printf("Test 6 passed.\n");


  /*-------------------------------------------------------------------------*/

  
  // Congratulations! your solution passed all the test cases here. This does 
  // NOT mean it is fully correct, however. Remember to run your own tests as 
  // well to make sure your code works under all conditions

  return 0;  // All good
}
