#include "imgUtils.c"

// This lets the driver code override the image size if it needs to. Make sure 
// you don't hard-code these values anywhere!
#ifndef SIZEX
  #define SIZEX 512
  #define SIZEY 512
#endif 

/*---------------------------------------------------------------------------*/

/**
 * This struct contains one node of the linked list, which represents a single 
 * command to the Turtle. It's field should include:
 * 
 *  - cmd   : A char array of size 10 holding the command name
 * 
 *  - val   : An integer that stores a parameter for the command (like forward,
 *            backward and colour). 
 * 
 *  - next  : A pointer to a struct of the same type, this is used for the 
 *            linked list
 * 
 * TODO: Complete this struct definition
 ****/

typedef struct CmdNode {
	char cmd[10];
	int val;
	struct CmdNode* loop_head;
	struct CmdNode* next;
} CmdNode;

/*---------------------------------------------------------------------------*/

CmdNode *newCmdNode(char cmd[10], int val) {
  /** 
   * This function allocates a new CmdNode struct and initializes it's values 
   * based on the input paramaters given. The next pointer is always 
   * initialized to NULL.
   * 
   * If the 'cmd' parameter is not a correct command, then print
   * "Invalid command.\n" and return NULL.
   * 
   * Note that we will always pass in a value here, even if the 
   * command doesn't need one. In this case, we can just ignore 
   * it. It saves us from having to make separate functions to 
   * deal with this.
   * 
   * TODO: Implement this function
   */

	
	
	if( strcmp("forward",cmd) == 0 || strcmp("backward",cmd) == 0 || strcmp("pendown",cmd) == 0 || strcmp("colour",cmd) == 0 || strcmp("penup",cmd) == 0 || strcmp("right",cmd) == 0 ||strcmp("left",cmd) == 0 ) {

		CmdNode *newNode = malloc(sizeof(CmdNode));
		strncpy(newNode->cmd,cmd,10);
		newNode->val = val;
		newNode->loop_head = NULL;
		newNode->next = NULL;
		return newNode;
	}
	
	else if( strcmp("loop",cmd) == 0 ) {
		CmdNode *newNode = malloc(sizeof(CmdNode));
		strncpy(newNode->cmd,cmd,10);
		newNode->val = val;
		newNode->loop_head = NULL;
		newNode->next = NULL;
		return newNode;
	}
	
	else {
		printf("Invalid Command.\n");
		return NULL;
	}
}

/*---------------------------------------------------------------------------*/

void printCommandList(CmdNode *head) {
  /**
   * This function prints out each command in the linked list one after the 
   * other. Each command MUST also have a line number printed before it, this 
   * is what you will be using to modify / delete them. To do this, initialize 
   * a counter and then increment it for each command.
   * 
   * Depending on whether or not the command needs an additional value 
   * (like forward, backward and colour), use one of the following statements 
   * to print out the information for each node: 
   *            [ The format is "linenumber: command value" ]
   * 
   * printf("%3d: %s %d\n", ... );     [With a value]
   * 
   * printf("%3d: %s\n", ... );        [Without a value]
   * 
   * Obviously, you also need to pass in the correct parameters to the print 
   * function yourself, this is just so you have the correct format.
   * 
   * TODO: Implement this function
   */

	int counter = 0;
	CmdNode* temp = head;
	
	while(temp != NULL) {
		if(temp->val != 0)
			printf("%3d: %s %d\n", counter, temp->cmd, temp->val);
		
		else 
			printf("%3d: %s\n", counter, temp->cmd);

		if(temp->loop_head != NULL) {
			CmdNode *tempLoop = temp->loop_head;

			while(tempLoop != NULL) {
				counter++;
				if(tempLoop->val != 0)
					printf("%3d:   %s %d\n", counter, tempLoop->cmd, tempLoop->val);
				else 
					printf("%3d:   %s\n", counter, tempLoop->cmd);
				tempLoop = tempLoop->next;
			}	
		}
		temp = temp->next;
		counter++;
	}

}

/*---------------------------------------------------------------------------*/

void queryByCommand(CmdNode *head, char cmd[10]) {
  /**
   * This function looks for commands in the linked list that match the input 
   * query. It prints them out in the same format as the printCommandList() 
   * function.
   * 
   * Make sure that the line number of the commands that match is the same as 
   * the line number that would be printed by the printCommandList() function.
   * 
   * --------------------------------------------------------------------------
   * 
   * For instance, if your printCommandList function outputs
   * 
   *    0: penup
   *    1: forward 200
   *    2: right
   *    3: forward 50
   * 
   * Then, if this function is called with the same list and cmd = "forward", 
   * then your output here should be
   * 
   *    1: forward 200
   *    3: forward 50
   * 
   * TODO: Implement this function
   */
		
	int counter = 0;
	CmdNode* temp = head;
	
	while(temp != NULL) {
		if(temp->val != 0 && strcmp(temp->cmd,cmd) == 0)
			printf("%3d: %s %d\n", counter, temp->cmd, temp->val);
		else if (strcmp(temp->cmd,cmd) == 0) 
			printf("%3d: %s\n", counter, temp->cmd);			
			
		if(temp->loop_head != NULL) {
			CmdNode *tempLoop = temp->loop_head;
			while(tempLoop != NULL) {
				counter++;
				if(tempLoop->val != 0 && strcmp(tempLoop->cmd,cmd) == 0)
					printf("%3d: %s %d\n", counter, tempLoop->cmd, tempLoop->val);
				else if(strcmp(tempLoop->cmd,cmd) == 0)
					printf("%3d: %s\n", counter, tempLoop->cmd);
				tempLoop = tempLoop->next;
				
			}
		}
		temp = temp->next;
		counter++;
	}

  return;
}

/*---------------------------------------------------------------------------*/

int countCommands(CmdNode *head) {
  /**
   * This function counts and returns the length of the linked list. It 
   * requires list traversal.
   * 
   * TODO: Implement this function
   */

	CmdNode *temp = head;	
	int listSize = 0;
	
	while(temp != NULL) {
		listSize++;
		if(temp->loop_head != NULL) {
			CmdNode *tempLoop = temp->loop_head;
			while(tempLoop != NULL) {
				listSize++;
				tempLoop = tempLoop->next;
			}	
		}
		 
		temp = temp->next;
	}

	return listSize;
}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommand(CmdNode *head, CmdNode *new_CmdNode) {
  /**
   * This function inserts the node new_CmdNode *at the tail* of the linked 
   * list. (You are adding a command at the end).
   * 
   * If head == NULL, then the linked list is still empty.
   * 
   * It returns a pointer to the head of the linked list with the new node 
   * added into it.
   * 
   * TODO: Implement this function
   */
	
	
	
	if(head == NULL) {
		head = new_CmdNode;
		return head;
	}
	else {
		CmdNode *temp = head;
		while(temp->next != NULL) {
			temp = temp->next;
		}	
		temp->next = new_CmdNode;
		return head;	
	}
		
  	
}

void insertCommandLoop(CmdNode *loopNode, CmdNode *newCmdNode) {
	
	if(loopNode->loop_head == NULL) {
		loopNode->loop_head = newCmdNode; 
	}
	else {
		CmdNode *temp = loopNode->loop_head;
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newCmdNode;
	}

}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommandBefore(CmdNode *head, CmdNode *new_CmdNode, int cmdNum) {
  /**
   * This function inserts a new node *before* a given Node in the linked list. 
   * 
   * 'cmdNum' is an integer that corresponds to the line number of a command 
   * from the printCommandList() function. Your task is to insert new_CmdNode 
   * *before* the corresponding node in the linked list.
   *
   * --------------------------------------------------------------------------
   *  
   * For instance, if your initial list was
   * 
   *    0: penup
   *    1: forward 200
   *    2: right
   *    3: forward 50
   * 
   * And you added "pendown" before cmdNum = 2, then you will have
   * 
   *    0: penup
   *    1: forward 200
   *    2: pendown
   *    3: right
   *    4: forward 50
   * 
   * --------------------------------------------------------------------------
   * 
   * If there is no command with the given cmdNum (cmdNum >= list size), 
   * then print "Invalid Command Number.\n" to the screen and *do not* 
   * insert the new node.
   * 
   * Returns a pointer to the head of the linked list with the new node added 0-> 1-> 4-> 2-> 3 4->3
   * into it.
   * 
   * TODO: Implement this function
   */
	
	if(cmdNum == 0 && head != NULL) {
		CmdNode* next = head;
		new_CmdNode->next = next;
		head = new_CmdNode;
		return head;
	}

	CmdNode *temp = head;
	int listSize = 0;
	

	while(temp->next != NULL) {
		temp = temp->next;
		listSize++;
	}

	if(cmdNum > listSize) {
		printf("Invalid Command Number.\n");
	}	
	else {
		temp = head;
		CmdNode *prev = NULL;
		int counter = 0;
		
		//printf("%s ",temp->cmd);
		while(counter < cmdNum) {
			counter++;
			prev = temp;
			temp = temp->next;
		}		
		
		//printf("%s ",prev->cmd);
		prev->next = new_CmdNode;
		new_CmdNode->next = temp;
		//printf("%s ",temp->cmd);

	}
	
  return head;
}

/*---------------------------------------------------------------------------*/

void updateCommand(CmdNode *head, int cmdNum, char cmd[10], int val) {
  /**
   * This function updates a specific node in the linked list based on the 
   * input parameters.
   * 
   * 'cmdNum' is an integer that corresponds to the line number of a command 
   * from the printCommandList() function. Your task is to update the 'cmd' and 
   * 'val' fields of this node.
   * 
   * If there is no command with the given cmdNum, then print 
   * "Invalid Command Number.\n" to the screen, and if 'cmd' is not a correct 
   * command, then print "Invalid command.\n". In both these cases, do *not* 
   * modify the list.
   * 
   * TODO: Implement this function
   */

	int counter = 0;
	CmdNode *temp = head;
	
	while(counter < cmdNum) {
		counter++;
		temp = temp->next;
	}
	
	CmdNode* Node = malloc(sizeof(CmdNode));
	Node = newCmdNode(cmd,val);
	
	if(Node->cmd == NULL) {
		return;	
	}
	
	
	strncpy(temp->cmd,cmd,10);
	temp->val = val;
}

/*---------------------------------------------------------------------------*/


CmdNode *deleteCommand(CmdNode *head, int cmdNum) {
  /**
   * This function deletes the node from the linked list that corresponds to 
   * the line number cmdNum. If there is no command with the given cmdNum, then 
   * the function does nothing.
   * 
   * Returns a pointer to the head of the linked list (which may have changed 
   * as a result of the deletion)
   *
   * TODO: Implement this function
   */

	CmdNode *temp = head;
	CmdNode *prev;
	int listSize = 0;
	

	while(temp->next != NULL) {
		temp = temp->next;
		listSize++;
	}

	if(cmdNum > listSize) {
		return head;
	}

	else {
		int counter = 0;
		temp = head;
		prev = NULL;
		
		if(cmdNum == 0) {
			head = temp->next;
			free(temp);
			return head;
		}

		while(counter < cmdNum) {
			counter++;
			prev = temp;
			temp = temp->next;
		}

		if(temp == NULL)
			return head;

		prev->next = temp->next;
		free(temp);
		
		return head;
	}	
}

/*---------------------------------------------------------------------------*/


CmdNode *deleteCommandList(CmdNode *head) {
  /**
   * This function deletes the linked list of commands, releasing all the 
   * memory allocated to the nodes in the linked list.
   * 
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   * 
   * TODO: Implement this function
   */
	CmdNode *temp = head;
	while(temp != NULL) {
		head = head->next;
		free(temp);
		free(temp->loop_head);
		temp = head;
	}

	head = NULL;
	
  return head;
}

/*---------------------------------------------------------------------------*/

void run(Image *im, CmdNode *head, int *endX, int *endY) {
  /**
   * This function runs the list of commands to move the turtle around and draw 
   * the image, and returns the final position of the turtle in the variables 
   * endX and endY.
   * 
   * --------------------------------------------------------------------------
   * 
   * NOTE: In the image we work with, the top-left pixel is (0,0),
   *       - x increases as you go right, up till SIZEX-1
   *       - y increases as you go down, up till SIZEY-1
   * 
   *                 (0,0)                 (SIZEX-1, 0)
   *                   x------------------------x
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |          IMAGE         |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   x------------------------x
   *             (0, SIZEY-1)            (SIZEX-1, SIZEY-1)
   * 
   * The image is in grayscale (black and white), so the colours are numbers 
   * from [0-255] where 0 is black, 255 is white, and the values in between 
   * are varying levels of gray.
   * 
   * You need to understand how the (x,y) values are stored so you know how 
   * they should be updated when you move (down means y increases, etc). You do 
   * not need to use the 'im' variable for anything other than passing it into 
   * the drawLine() function described below.
   * 
   * --------------------------------------------------------------------------
   * 
   * Here's the setup - There is a turtle (with a pen) that walks along the 
   * image. When the pen is down (on the paper), it draws a line along the path 
   * that it walks on. (If you want to play around with this, consider looking 
   * at the `turtle` library in python!)
   * 
   * The turtle initially starts at pixel (0, 0) [at the top left], 
   * facing right (in the positive x direction). The pen starts off
   * as `down`, with the default colour being black (0).
   * 
   * You need to go through the linked list and 'run' the commands to keep 
   * track of the turtles position, and draw the appropriate lines. Here is 
   * what each command should do:
   * 
   *  - penup          : Put the pen up (stop drawing)
   *  - pendown        : Put the pen down (start / continue drawing)
   *  - colour <val>   : Draw lines in colour <val> from now on
   *  - forward <val>  : Move the turtle forward <val> steps (pixels) 
   *                     in the direction it is facing.
   *  - backward <val> : Same as above, except move backwards
   *  - right          : Turn the turtle to the right by 90 degrees
   *  - left           : Turn the turtle to the left by 90 degrees
   * 
   * NOTE: Make sure that you do *not* go outside the image. For this, set the 
   * maximum and minimum values of x and y to be 0 and SIZEX-1 / SIZEY-1 
   * respectively.
   * 
   * For instance, if the turtle is at (0,0) facing right, and your command is
   * `forward 100000`, it will only go forward till (SIZEX-1, 0), and end 
   * up at the rightmost pixel in that row.
   * 
   * IMPORTANT: Once you are done with all the commands, make sure you save the 
   * final (x,y) location of the turtle into the variables endX and endY.
   * 
   * --------------------------------------------------------------------------
   * 
   * We have already implemented a drawLine() function (in imgUtils.c) which 
   * you should use to actually draw the lines. It takes in the following:
   * 
   *      - a pointer to an image struct (use 'im')
   *      - (x,y) location of start point
   *      - (x,y) location of end point
   *      - a colour to draw the line in [0-255]
   *          
   * Note that this function only draws horizontal and vertical lines, so 
   * either the x values or the y values of both points must be the same. 
   * Both these points *must* also be within the image. 
   *          [ 0 <= x < SIZEX,  0 <= y < SIZEY ]
   * 
   * 
   * TODO: Implement this function
   */

	int X1, Y1, X2, Y2, angle, colour;
	
	CmdNode *temp = head;
	X1 = Y1 = 0;
	angle = 0;
	X2 = Y2 = 0;
	int draw = 0;
	colour = 0;
	while(temp != NULL) {
		if(strcmp("forward",temp->cmd) == 0) {
			if(angle == 0) {
				if((X2+temp->val) < 512) {
					X2 += temp->val;
				}
			}
			if(angle == 90) {
				if((Y2+temp->val) < 512) {
					Y2 += temp->val;
				}
			}
			if(angle == 180) {
				if((X2-temp->val) >= 0) {
					X2 -= temp->val;
				}
			}	
			if(angle == 270) {
				if((Y2-temp->val) >= 0) {
					Y2 -= temp->val;
				}
			}
		}

		if(strcmp("backward",temp->cmd) == 0) {
			if(angle == 0) {
				if((X2-temp->val) < 512) {
					X2 -= temp->val;
				}
			}
			if(angle == 90) {
				if((Y2-temp->val) < 512) {
					Y2 -= temp->val;
				}
			}
			if(angle == 180) {
				if((X2+temp->val) >= 0) {
					X2 += temp->val;
				}
			}	
			if(angle == 270) {
				if((Y2+temp->val) >= 0) {
					Y2 += temp->val;
				}
			}
		}
		
		if(strcmp("right",temp->cmd) == 0) {
			if(angle == 270) {
				angle = 0;
			}
			else {
				angle += 90;
			}
		}
		if(strcmp("left",temp->cmd) == 0) {
			if(angle == 0) {
				angle = 270;		
			}
			else {
				angle -= 90;
			}
		}
		
		if(strcmp("pendown",temp->cmd) == 0) {
			draw = 1;
			
		}
		
		if(strcmp("penup",temp->cmd) == 0) {
			draw = 0;
		}
		
		if(strcmp("colour",temp->cmd) == 0) {
			colour = temp->val;
		}
		
		if(strcmp("loop",temp->cmd) == 0) {
				int loopITR = temp->val;
				while(loopITR > 0) {
					CmdNode *loop_head = temp->loop_head;
					while(loop_head != NULL) {
						if(strcmp("forward",loop_head->cmd) == 0) {
							if(angle == 0) {
								if((X2+loop_head->val) < 512) {
									X2 += loop_head->val;
								}
							}

							if(angle == 90) {
								if((Y2+loop_head->val) < 512) {
									Y2 += loop_head->val;
								}
							}

							if(angle == 180) {
								if((X2-loop_head->val) >= 0) {
									X2 -= loop_head->val;
								}
							}	

							if(angle == 270) {
								if((Y2-loop_head->val) >= 0) {
									Y2 -= loop_head->val;
								}
							}
						}

						if(strcmp("backward",loop_head->cmd) == 0) {
							if(angle == 0) {
								if((X2-loop_head->val) < 512) {
									X2 -= loop_head->val;
								}
							}
							if(angle == 90) {
								if((Y2-loop_head->val) < 512) {
									Y2 -= loop_head->val;
								}
							}
							if(angle == 180) {
								if((X2+loop_head->val) >= 0) {
									X2 += loop_head->val;
								}
							}	
							if(angle == 270) {
								if((Y2+loop_head->val) >= 0) {
									Y2 += loop_head->val;
								}
							}
						}
		
						if(strcmp("right",loop_head->cmd) == 0) {
							if(angle == 270) {
								angle = 0;
							}
							else {
								angle += 90;
							}
						}
						if(strcmp("left",loop_head->cmd) == 0) {
							if(angle == 0) {
								angle = 270;		
							}
							else {
								angle -= 90;
							}
						}
		
						if(strcmp("pendown",loop_head->cmd) == 0) {
							draw = 1;
			
						}
		
						if(strcmp("penup",loop_head->cmd) == 0) {
							draw = 0;
						}
		
						if(strcmp("colour",loop_head->cmd) == 0) {
							colour = loop_head->val;
						}
						
						if(draw == 1) {	
							drawLine(im, X1, Y1, X2, Y2, colour);
							printf("(%d,%d) %d ",X2,Y2,angle);
						}	
						
						
						X1 = X2;
						Y1 = Y2;					
						
						loop_head = loop_head->next;
					}

					loopITR--;					
				}

		}
	
		if(draw == 1) {	
			drawLine(im, X1, Y1, X2, Y2, colour);
			printf("(%d,%d) %d ",X2,Y2,angle);
		}
		
	
		X1 = X2;
		Y1 = Y2;
		temp = temp->next;
	}
		*endX = X2;
		*endY = Y2;
  return;
}

/*---------------------------------------------------------------------------*/
// All done!
