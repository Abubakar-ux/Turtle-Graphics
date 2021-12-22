#define SIZEX 512
#define SIZEY 512

#include "turtle-pro.c"  // <--- This will import your code so we can
                         //	use your solution to create a linked
                         //	list of movie reviews for testing!

CmdNode *loadCommands_pro(const char *fileName) {
  CmdNode *head = NULL;
  CmdNode *forN = NULL;
  CmdNode *temp = NULL;

  char buffer[1024];
  char *buf;

  FILE *f = fopen(fileName, "r");
  while (fgets(&buffer[0], 1024, f) != NULL) {
    temp = NULL;
    buf = &buffer[0];

    if (strncmp(buf, "  ", 2) && forN != NULL) forN = NULL;
    if (forN != NULL) buf = buf + 2;  // Skip over indents

    if      (!strncmp(buf, "backward", 8)) temp = newCmdNode("backward", atoi(&buf[9]));
    else if (!strncmp(buf, "forward", 7)) temp = newCmdNode("forward", atoi(&buf[8]));
    else if (!strncmp(buf, "pendown", 7)) temp = newCmdNode("pendown", 0);
    else if (!strncmp(buf, "colour", 6)) temp = newCmdNode("colour", atoi(&buf[7]));
    else if (!strncmp(buf, "penup", 5)) temp = newCmdNode("penup", 0);
    else if (!strncmp(buf, "right", 5)) temp = newCmdNode("right", 0);
    else if (!strncmp(buf, "left", 4)) temp = newCmdNode("left", 0);
    if (!strncmp(buf, "loop", 4)) forN = newCmdNode("loop", atoi(&buf[5]));

    if (temp != NULL && forN != NULL) insertCommandLoop(forN, temp);
    else if (temp != NULL) head = insertCommand(head, temp);
    else if (forN != NULL) head = insertCommand(head, forN);
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
  CmdNode *temp2 = NULL;
  Image *im;
  int choice = 0;
  char cmd[10], fileName[1024];
  int val, ex, ey;



  while (choice != 7) {
    printf("------------------------------------------------\n");

    printf("Please choose one of the following options:\n");
    printf("0 - Insert a new command.\n");
    printf("1 - Insert a loop command.\n");
    printf("2 - Print list of commands.\n");
    printf("3 - Query by command type.\n");
    printf("4 - Load commands from file.\n");
    printf("5 - Run commands and draw image.\n");
    printf("6 - Reset the list.\n");
    printf("7 - Delete list and exit.\n");
    
    getInt("Enter choice", &choice);
    printf("------------------------------------------------\n");

    // Read in review information from terminal where needed.
    if (choice == 0) {
      getCommand(cmd, &val);
      temp = newCmdNode(cmd, val);
      head = insertCommand(head, temp);
    }

    if (choice == 1 ) {
      getInt("Number of times to loop", &val);
      temp = newCmdNode("loop", val);

      cmd[0] = '\0';
      printf("------------------------------------------------\n");
      printf("Enter the commands in the loop one by one, enter 'done' when finished.\n");
      // This is to build the list of commands in the loop
      while (1) {
        getStr("Command / done", cmd);
        if (strcmp(cmd, "done") == 0) break;
        getInt("Value", &val);
        temp2 = newCmdNode(cmd, val);
        insertCommandLoop(temp, temp2);
        printf("------------------------------------------------\n");
      }

      head = insertCommand(head, temp);
    }

    if (choice == 2) {
      printCommandList(head);
    }

    if (choice == 3) {
      getStr("Command", cmd);
      queryByCommand(head, cmd);
    }

    if (choice == 4) {
      getStr("Filename", fileName);
      head = deleteCommandList(head);
      head = loadCommands_pro(fileName);
      printf("Loaded commands.\n");
    }

    if (choice == 5) {
      im = newImage(SIZEX, SIZEY);
       // Ignore the return values for now
      run(im, head, &ex, &ey);
      imageOutput(im, "output-pro.pgm");
      deleteImage(im);
      printf("Image saved to output-pro.pgm.\n");
    }

    if (choice == 6) {
      head = deleteCommandList(head);
      printf("List is deleted.\n");
    }
  }

  head = deleteCommandList(head);
  printf("Done!\n");
  return 0;
}
