#define SIZEX 512
#define SIZEY 512

#include "turtle.c"  // <--- This will import your code so we can
                     //	use your solution to create a linked
                     //	list of movie reviews for testing!

CmdNode *loadCommands(const char *fileName) {
  CmdNode *head = NULL;
  CmdNode *temp = NULL;
  char buf[1024];

  FILE *f = fopen(fileName, "r");
  if (f == NULL) return NULL;

  while (fgets(buf, 1024, f) != NULL) {
    temp = NULL;

    if      (!strncmp(buf, "backward", 8)) temp = newCmdNode("backward", atoi(&buf[9]));
    else if (!strncmp(buf, "forward", 7)) temp = newCmdNode("forward", atoi(&buf[8]));
    else if (!strncmp(buf, "pendown", 7)) temp = newCmdNode("pendown", 0);
    else if (!strncmp(buf, "colour", 6)) temp = newCmdNode("colour", atoi(&buf[7]));
    else if (!strncmp(buf, "penup", 5)) temp = newCmdNode("penup", 0);
    else if (!strncmp(buf, "right", 5)) temp = newCmdNode("right", 0);
    else if (!strncmp(buf, "left", 4)) temp = newCmdNode("left", 0);

    if (temp != NULL) head = insertCommand(head, temp);
  }
  fclose(f);
  return head;
}

void getInt(char *prompt, int *var) {
  printf("%s = ", prompt);
  char buf[5];
  fgets(&buf[0], 5, stdin);
  // If no input, default to 0
  if (strlen(buf) == 1) *var = 0;
  else *var = atoi(buf);
}

void getStr(char *prompt, char *var) {
  printf("%s = ", prompt);
  fgets(&var[0], 1024, stdin);
  int i = strlen(&var[0]);
  if (var[i - 1] == '\n') var[i - 1] = '\0';
}

void getCommand(char *cmd, int *val) {
  getStr("Command", cmd);
  getInt("Value", val);
}

int main() {
  CmdNode *head = NULL;
  CmdNode *temp = NULL;
  Image *im;
  int choice = 0;
  int cmdNum;
  char cmd[10], fileName[1024];
  int val, ex, ey;

  while (choice != 9) {
    printf("------------------------------------------------\n");

    printf("Please choose one of the following options:\n");
    printf("0 - Insert a new command.\n");
    printf("1 - Insert a new command in the middle.\n");
    printf("2 - Print list of commands.\n");
    printf("3 - Query by command type.\n");
    printf("4 - Update a command.\n");
    printf("5 - Load commands from file.\n");
    printf("6 - Run commands and draw image.\n");
    printf("7 - Delete a command .\n");
    printf("8 - Reset the list.\n");
    printf("9 - Delete list and exit.\n");
    
    getInt("Enter choice", &choice);
    printf("------------------------------------------------\n");

    // Read in review information from terminal where needed.
    if (choice == 0) {
      getCommand(cmd, &val);
      temp = newCmdNode(cmd, val);
      if (temp == NULL) continue;
      head = insertCommand(head, temp);
    }

    if (choice == 1 ) {
      getInt("Insert before", &cmdNum);
      getCommand(cmd, &val);
      temp = newCmdNode(cmd, val);
      if (temp == NULL) continue;
      head = insertCommandBefore(head, temp, cmdNum);
    }

    if (choice == 2) {
      printCommandList(head);
    }

    if (choice == 3) {
      getStr("Command", cmd);
      queryByCommand(head, cmd);
    }

    if (choice == 4) {
      getInt("Command to update", &cmdNum);
      getCommand(cmd, &val);
      updateCommand(head, cmdNum, cmd, val);
    }

    if (choice == 5) {
      getStr("Filename", fileName);
      head = deleteCommandList(head);
      head = loadCommands(fileName);
      printf("Loaded commands.\n");
    }

    if (choice == 6) {
      im = newImage(SIZEX, SIZEY);
       // Ignore the return values for now
      run(im, head, &ex, &ey);
      imageOutput(im, "output.pgm");
      deleteImage(im);
      printf("Image saved to output.pgm.\n");
    }

    if (choice == 7) {
      getInt("Command to delete", &cmdNum);
      head = deleteCommand(head, cmdNum);
    }

    if (choice == 8) {
      head = deleteCommandList(head);
      printf("List is deleted.\n");
    }
  }

  head = deleteCommandList(head);
  printf("Done!\n");
  return 0;
}
