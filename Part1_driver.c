
#define SIZEX 512
#define SIZEY 512

#include "turtle.c"

int checkNode(CmdNode *a, char cmd[10], int val) {
  return (strcmp(a->cmd, cmd) == 0 && a->val == val);
}

int main() {
  Image *im;
  CmdNode *head = NULL;
  CmdNode *tmp = NULL;
  CmdNode *tmp2 = NULL;
  int val, i, j, ex, ey;

  printf("Running tests...\n");

  /*-------------------------------------------------------------------------*/

  // Test 0, Creating a node with valid and invalid commands
  tmp = newCmdNode("forward", 100);
  printf("Expecting \"Invalid command.\"\n>    ");
  tmp2 = newCmdNode("forwrd", 100);  // Typo
  if (tmp == NULL || tmp2 != NULL) {
    printf("Test 0 failed, newCmdNode() did not initialize node properly.\n");
    return 1;
  } else if (!checkNode(tmp, "forward", 100) || tmp->next != NULL) {
    printf("Test 0 failed, Incorrect data in new node.\n");
    return 1;
  }
  printf("Test 0 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Test 1, Inserting into an empty list at the tail
  head = insertCommand(head, tmp);
  if (head == NULL) {
    printf("Test 1 failed, head is still NULL.\n");
    return 1;
  } else if (!checkNode(head, "forward", 100) || tmp->next != NULL) {
    printf("Test 1 failed, Incorrect data in the head of list.\n");
    return 1;
  }
  printf("Test 1 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Test 2, Inserting into a list with one element at the tail
  tmp = newCmdNode("colour", 150);
  head = insertCommand(head, tmp);
  if (head == NULL) {
    printf("Test 2 failed, head is NULL.\n");
    return 1;
  } else if (head->next == NULL) {
    printf("Test 2 failed, list only has one node.\n");
    return 1;
  } else if (!checkNode(head->next, "colour", 150) ||
             head->next->next != NULL) {
    printf("Test 2 failed, node not added in the right location\n");
    return 1;
  }
  printf("Test 2 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Test 3, Inserting into a list with two elements in between
  tmp = newCmdNode("right", 0);
  head = insertCommandBefore(head, tmp, 1);
  if (head == NULL) {
    printf("Test 3 failed, head is NULL.\n");
    return 1;
  } else if (!checkNode(head, "forward", 100) ||
             !checkNode(head->next, "right", 0) ||
             !checkNode(head->next->next, "colour", 150) ||
             head->next->next->next != NULL) {
    printf("Test 3 failed, node not inserted correctly in the middle.\n");
    return 1;
  }
  printf("Test 3 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Test 4, Inserting at the head of the list
	
	

  tmp = newCmdNode("penup", 0);
  head = insertCommandBefore(head, tmp, 0);
	

  if (head == NULL) {
    printf("Test 4 failed, head is NULL.\n");
    return 1;
  } else if (!checkNode(head, "penup", 0) ||
             !checkNode(head->next, "forward", 100) ||
             !checkNode(head->next->next, "right", 0) ||
             !checkNode(head->next->next->next, "colour", 150) ||
             head->next->next->next->next != NULL) {
    printf("Test 4 failed, node not inserted correctly at the head.\n");
    return 1;
  }
  printf("Test 4 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Test 5, Updating a the node in the middle of the list, and also
  //         checking if it ignores invalid commands
  updateCommand(head, 1, "backward", 40);
  printf("Expecting \"Invalid command.\"\n>    ");
  printCommandList(head);
  updateCommand(head, 2, "notvalid", 101);
  if (!checkNode(head, "penup", 0) || 
      !checkNode(head->next, "backward", 40) ||
      !checkNode(head->next->next, "right", 0) ||
      !checkNode(head->next->next->next, "colour", 150) ||
      head->next->next->next->next != NULL) {
    printf("Test 5 failed, node not correctly updated.\n");
    return 1;
  }

  printf("Test 5 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Test 6, Deleting a node in the middle of the list
  head = deleteCommand(head, 2);
  if (!checkNode(head, "penup", 0) || 
      !checkNode(head->next, "backward", 40) ||
      !checkNode(head->next->next, "colour", 150)) {
    printf("Test 6 failed, node not deleted properly.\n");
    return 1;
  }
  printf("Test 6 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Test 7, Deleting the head of the list
  head = deleteCommand(head, 0);
  if (head == NULL) {
    printf("Test 7 failed, head is NULL.\n");
    return 1;
  } else if (!checkNode(head, "backward", 40) ||
             !checkNode(head->next, "colour", 150)) {
    printf("Test 7 failed, node not deleted properly.\n");
    return 1;
  }
  printf("Test 7 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Test 8, Counting the number of commands
  val = countCommands(head);
  if (val != 2) {
    printf("Test 8 failed, countCommands() did not return correct value.\n");
    return 1;
  }
  printf("Test 8 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Test 9, Deleting the list
  head = deleteCommandList(head);
  if (head != NULL) {
    printf("Test 9 failed, head is not NULL after deleting list.\n");
    return 1;
  } else if ((val = countCommands(head))) {
    printf("Test 9 failed, countCommands() says %d commands in list.\n", val);
    return 1;
  }
  printf("Test 9 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Test 10, Turtle should always remain within bounds in run()
  head = insertCommand(head, newCmdNode("right", 0));
  head = insertCommand(head, newCmdNode("right", 0));
  head = insertCommand(head, newCmdNode("forward", 100));
  head = insertCommand(head, newCmdNode("right", 0));
  head = insertCommand(head, newCmdNode("forward", 100));
  im = newImage(SIZEX, SIZEY);
  run(im, head, &ex, &ey);
  deleteImage(im);
  if (ex != 0 && ey != 0) {
    printf("Test 10 failed, should turtle should not go out of bounds.\n");
    return 1;
  }
  head = deleteCommandList(head);
  printf("Test 10 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Setting up a list of commands that draws a square in the middle of the
  // image
  head = insertCommand(head, newCmdNode("penup", 0));
  head = insertCommand(head, newCmdNode("forward", 100));
  head = insertCommand(head, newCmdNode("right", 0));
  head = insertCommand(head, newCmdNode("forward", 100));
  head = insertCommand(head, newCmdNode("pendown", 0));
  head = insertCommand(head, newCmdNode("forward", 300));
  head = insertCommand(head, newCmdNode("left", 0));
  head = insertCommand(head, newCmdNode("forward", 300));
  head = insertCommand(head, newCmdNode("left", 0));
  head = insertCommand(head, newCmdNode("forward", 300));
  head = insertCommand(head, newCmdNode("left", 0));
  head = insertCommand(head, newCmdNode("forward", 300));

  im = newImage(SIZEX, SIZEY);

  /*-------------------------------------------------------------------------*/

  // Test 11, testing the run() function. This should draw a square on the
  // image with the corners (100,100), (100,400), (400,400) and (400, 100)
  // The turtle should end back up on pixel (100, 100)
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
    printf("Test 11 failed, end location of the turtle should be (100, 100)\n");
    return 1;
  }
  deleteImage(im);
  printf("Test 11 passed.\n");

  /*-------------------------------------------------------------------------*/

  // Test 12, printing out the command list
  printf("Test 12, check this yourself!\n");
  /* This needs to be inspected manually. Here is the expected output:
    0: penup
    1: forward 100
    2: right
    3: forward 100
    4: pendown
    5: forward 300
    6: left
    7: forward 300
    8: left
    9: forward 300
   10: left
   11: forward 300
  */
  printCommandList(head);

  /*-------------------------------------------------------------------------*/

  // Test 13, querying the list for "forward"
  printf("Test 13, check this yourself!\n");
  /* This needs to be inspected manually. Here is the expected output:
    1: forward 100
    3: forward 100
    5: forward 300
    7: forward 300
    9: forward 300
   11: forward 300
  */
  queryByCommand(head, "forward");

  /*-------------------------------------------------------------------------*/

  // Congratulations! your solution passed all the test cases here. This does 
  // NOT mean it is fully correct, however. Remember to run your own tests as 
  // well to make sure your code works under all conditions


  deleteCommandList(head);
  return 0;  // All good
}
