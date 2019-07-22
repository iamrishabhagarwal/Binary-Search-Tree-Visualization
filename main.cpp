
#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#include<GL/glut.h>
#include "constants.h"

// A variable used to establish a distance between two option boxes
float offset = 0.0;
int flag=0;
int flag1=0;
// A variable used to check whether input is given after an option has been selected
bool box_clicked = false;
void delay(int abc)
{
    for(int i=0;i<abc;i++)
        for(int j=0;j<abc;j++);
}
//Variables used to store the previously searched item in order to clear the search
int temp_x, temp_y, temp_item;
bool prev_search = false;

// Integer color code for RGB
enum color_code {RED, GREEN, BLUE};
int sb;

// Function to count digits in numbers
int count_digit(int n){
	return (n==0)?0:floor(log10(n)+1);
}
void display_string(char s[], float x, float y, float z = 0.0){
	glRasterPos3f(x, y, z);
	for(int i=0; s[i]; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	glFlush();
}


void frontscreen(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(0,0,1);
 display_string("JSS ACADEMY OF TECHNICAL EDUCATION",300, 450,0.0);
 glColor3f(0.7,0,1);
 display_string("DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING",200, 400,0.0);
 glColor3f(1,0.5,0);
 display_string("COMPUTER GRAPHICS PROJECT",350, 350,0.0);
 glColor3f(1,0,0);
 display_string("Topic: Binary Search Tree and Traversals",80,150,0.0);
 glColor3f(0.5,0,0.5);
 display_string("Rishabh Agarwal: 1JS16CS083",80,100,0.0);
 display_string("Sachin Kumar : 1JS16CS086",80,50,0.0);
 glColor3f(1,0.1,1);
 display_string("PRESS ENTER TO START",500,100,0.0);
 glColor3f(0.7,0.7,1);
 display_string("(Press 'r' to reset the tree after any traversal)",500,50,0.0);
 glFlush();
}

// Function which converts a given number into a string
void to_string(char *s, int num){
	int r, d;
	d = count_digit(abs(num));
	if(num==0)
		s[0]='0';
	if(num<0){
		s[0] = '-';
		d++;
	}
	s[d]='\0';
	num = abs(num);
	while(num!=0){
		r = num%10;
		s[--d] = r+'0';
		num/=10;
	}
}

// Function to display the data on the node



// Function used to clear the input region after the input has been processed
void clear_input_region(){
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(80, 580);
		glVertex2f(80, 650);
		glVertex2f(580, 650);
		glVertex2f(580, 580);
	glEnd();
	glFlush();
}


/*
 * =============================================================================
 *
 * A class which is the blueprint of the binary search tree.
 * It has methods to perform the operation of insert search and delete
 *
 * =============================================================================
 */

class binary_search_tree {

	public:
		NODE root;
		int root_centre_x, root_centre_y;
		int node_width;
		float line_color[3];

		// Method used to get the minimum valued node in the specified subtree
		NODE get_minimum(NODE temp, NODE *par){
			if(temp->left == NULL)
				return temp;
			*par = temp;
			return get_minimum(temp->left, par);
		}

	public:

		// Constructor used to initialize all the properties of the tree
		binary_search_tree(){
			root = NULL;
			root_centre_x = 500;
			root_centre_y = 500;
			node_width = 30;
			line_color[RED] = 0.0;
			line_color[GREEN] = 0.7;
			line_color[BLUE] = 0.0;
		}

		// method used to draw a node and put the value at the given co-ordinate
		void draw_node(int item, int centre_x, int centre_y, bool write_value = true){
			char data_string[10];
			glBegin(GL_POLYGON);
				glVertex2f(centre_x + node_width, centre_y + node_width);
				glVertex2f(centre_x - node_width, centre_y + node_width);
				glVertex2f(centre_x - node_width, centre_y - node_width);
				glVertex2f(centre_x + node_width, centre_y - node_width);
			glEnd();
			if(write_value){
				to_string(data_string, item);
				glColor3f(1.0, 1.0, 0.0);
				display_string(data_string, centre_x - node_width + 10, centre_y);
			}
		}

		// method used to draw a line between a parent and a child
		void draw_arrow(int par_x, int par_y, int node_x, int node_y, bool color = true){
			if(color)
				glColor3f(line_color[RED], line_color[GREEN], line_color[BLUE]);
			else
				glColor3f(BG_R, BG_G, BG_B);
			glBegin(GL_LINES);
				glVertex2f(par_x, par_y - node_width);
				glVertex2f(node_x, node_y + node_width);
			glEnd();
		}

		// method used to insert an element into the tree and call the draw_node method
		NODE insert(int item){
			int num_of_nodes = 1;
			int node_x = root_centre_x, node_y = root_centre_y;
			int par_x, par_y;
			NODE temp, par = NULL, new_node;
			if(root == NULL){
				root = (NODE)malloc(sizeof(struct node));
				if(root == NULL){
					printf("There was an error in creating the node\n");
					return NULL;
				}
				root->data = item;
				root->left = root->right = NULL;
				glColor3f(node_color[RED], node_color[GREEN], node_color[BLUE]);
				draw_node(item, node_x, node_y);
				return root;
			}
			temp = root;
			while(temp != NULL){
				num_of_nodes *= 2;
				par_x = node_x;
				par_y = node_y;
				node_y -= 100;
				par = temp;
				if(item < temp->data) {
					temp = temp->left;
					node_x -= root_centre_x/num_of_nodes;
				}
				else {
					temp = temp->right;
					node_x += root_centre_x/num_of_nodes;
				}
			}
			new_node = (NODE)malloc(sizeof(struct node));
			if(new_node == NULL){
					printf("There was an error in creating the node\n");
					return NULL;
				}
			new_node->data = item;
			new_node->left = new_node->right = NULL;
			if(item < par->data)
				par->left = new_node;
			else
				par->right = new_node;
			glColor3f(node_color[RED], node_color[GREEN], node_color[BLUE]);
			draw_node(item, node_x, node_y);
			draw_arrow(par_x, par_y, node_x, node_y);
			glFlush();
			return root;
		}


		// Method used to search for the first node with a given value in the tree
		NODE search(int item){
			int num_of_nodes = 1;
			int node_x = root_centre_x, node_y = root_centre_y;
			int par_x, par_y;
			NODE temp, par = NULL, new_node;
			if(root == NULL){
				glColor3f(1.0, 0.0, 0.0);
				display_string(not_found, 100, 600);
				return root;
			}
			temp = root;
			while(temp != NULL){
				num_of_nodes *= 2;
				par_x = node_x;
				par_y = node_y;
				par = temp;
				if(item == temp->data){
					prev_search = true;
					temp_x = node_x;
					temp_y = node_y;
					temp_item = item;
					glColor3f(1.0, 0.0, 0.0);
					draw_node(item, node_x, node_y);
					glFlush();
					return temp;
				}
				else if(item < temp->data) {
					temp = temp->left;
					node_y -= 100;
					node_x -= root_centre_x/num_of_nodes;
				}
				else {
					temp = temp->right;
					node_y -= 100;
					node_x += root_centre_x/num_of_nodes;
				}
			}
			glColor3f(1.0, 0.0, 0.0);
			display_string(not_found, 100, 600);
			glFlush();
			return temp;
		}

		void pre_order(NODE temp, binary_search_tree temp_tree){
			if(temp != NULL){
				temp_tree.insert(temp->data);
				pre_order(temp->left, temp_tree);
				pre_order(temp->right, temp_tree);
			}
		}

		void draw_tree(){
			binary_search_tree temp_tree;
			if(flag==0)
                display();
            else
                display1();
			pre_order(root, temp_tree);
		}

		// Method used to delete the first node with the given value
		NODE remove(int item){
			bool found = false;
			int num_of_nodes = 1;
			int node_x = root_centre_x, node_y = root_centre_y;
			int par_x, par_y;
			NODE temp = root, par = root, new_node;
			if(root == NULL){
				glColor3f(1.0, 0.0, 0.0);
				display_string(not_found, 100, 600);
				return root;
			}
			while(temp != NULL){
				if(item == temp->data){
					found = true;
					if(temp == root){
						if(temp->left == NULL && temp->right == NULL){
							root = NULL;
							free(temp);
						}
						if(temp->left != NULL && temp->right != NULL){
							par = temp;
							NODE min_node = get_minimum(temp->right, &par);
							temp->data = min_node->data;
							temp = min_node;
							item = min_node->data;
							continue;
						}
						if(temp->left != NULL){
							root = temp->left;
							free(temp);
						}
						if(temp->right != NULL){
							root = temp->right;
							free(temp);
						}
					}
					else if(temp->left == NULL && temp->right == NULL){
						if(par->left == temp)
							par->left = NULL;
						else
							par->right = NULL;
						free(temp);
					}
					else if(temp->left != NULL && temp->right != NULL){
						par = temp;
						NODE min_node = get_minimum(temp->right, &par);
						temp->data = min_node->data;
						temp = min_node;
						item = min_node->data;
						continue;
					}
					else {
						if(temp->left != NULL)
							(par->left == temp) ? (par->left = temp->left) : (par->right = temp->left);
						else
							(par->left == temp) ? (par->left = temp->right) : (par->right = temp->right);
						free(temp);
					}
					break;
				}
				par = temp;
				if(item < temp->data)
					temp = temp->left;
				else
					temp = temp->right;
			}
			if(!found){
				glColor3f(1.0, 0.0, 0.0);
				display_string(not_found, 100, 600);
			}
			else
            {
                flag=1;
                draw_tree();
            }

		}
};

//Object of class binary_search_tree which is used to manipulate the tree
binary_search_tree tree;


//A member function pointer used to decide the method to be called at runtime
NODE (binary_search_tree::*operation)(int) = NULL;

/*
 * =============================================================================
 *
 * A class which is the blueprint of an option box which is displayed at the top
 * right corner. It holds all the information related to constructing an option
 * box.
 *
 * =============================================================================
 */

class option_box {

	private:
		float bottom_corner_x, bottom_corner_y;
		float bc;
		float height, width;
		float color[3];
		char option_name[20];

	public:

		// Empty Constructor
		option_box(){
			bottom_corner_x = 0;
			bottom_corner_y = 0;
			width = 0;
			height = 0;
			color[RED] = 0.0;
			color[GREEN] = 0.0;
			color[BLUE] = 1.0;
			strcpy(option_name, "");
		}

		// Constructor used to initialize all the properties of the option box
		option_box(const char name[]){
			bottom_corner_x = 600;
			bottom_corner_y = 600;
			width = 100;
			height = 50;
			color[RED] = 0.4;
			color[GREEN] = 0.4;
			color[BLUE] = 0.9;
			strcpy(option_name, name);
		}

		// method used to draw the option box and call the display_string method
		void draw_box(){
			bottom_corner_x += offset;
			bc = bottom_corner_x;
			glColor3f(color[RED], color[GREEN], color[BLUE]);
			glBegin(GL_POLYGON);
				glVertex2f(bottom_corner_x, bottom_corner_y);
				glVertex2f(bottom_corner_x + width, bottom_corner_y);
				glVertex2f(bottom_corner_x + width, bottom_corner_y + height);
				glVertex2f(bottom_corner_x, bottom_corner_y + height);
			glEnd();
			offset += 120.0;
			glColor3f(1.0, 1.0, 0.0);
			display_string(option_name, bottom_corner_x + 10.0, bottom_corner_y + 20.0);
		}

		// A function to check whether mouse was clicked on this box given the co-ordinates
		bool clicked(int x, int y){
			if( x > bc && x < bc + width)
				if( y > bottom_corner_y && y < bottom_corner_y + height){
					box_clicked = true;
					return true;
				}
			return false;
		}
};

option_box insert_box, search_box, delete_box;

/*
 * =============================================================================
 *
 * init function is used to initialize the co-ordinate mode and to clear the
 * background process.
 *
 * =============================================================================
 */

void init() {
	glClearColor(BG_R, BG_G, BG_B, BG_A);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,SCREEN_SIZE_X,0.0,SCREEN_SIZE_Y);
}

/*
 * =============================================================================
 *
 * Displays 3 boxes for operations in the upper right corner
 * The 3 operations are : Insert, Search, Delete
 *
 * =============================================================================
 */

 void displayOptions(){
 	option_box insert_box("Insert"), delete_box("Delete");
 	offset = 0.0;
	insert_box.draw_box();
	delete_box.draw_box();
	::insert_box = insert_box;
	::delete_box = delete_box;
 }

/*
 * =============================================================================
 *
 * init function is used to initialize the co-ordinate mode and to clear the
 * background process.
 *
 * =============================================================================
 */
void mydisplay(void)
{
 //glClear(GL_COLOR_BUFFER_BIT);
 if(flag1==0)
   frontscreen ();
 if(flag1==1)
  display();
}

void display() {
	//glClear(GL_COLOR_BUFFER_BIT);
	displayOptions();
	glFlush();
}

void display1()
{
   glClear(GL_COLOR_BUFFER_BIT);
	displayOptions();
	glFlush();
}


/*
 * =============================================================================
 *
 * A mouse call back function used to get the co-ordinates of a mouse click
 * This callback is used to check on which option the user has clicked and calls
 * the corresponding function accordingly
 *
 * =============================================================================
 */

void mouse(int button, int state, int x, int y){
	y = SCREEN_SIZE_Y - y;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(prev_search == true){
			glColor3f(node_color[RED], node_color[GREEN], node_color[BLUE]);
			tree.draw_node(temp_item, temp_x, temp_y);
			prev_search = false;
		}
		if(insert_box.clicked(x, y)){
			operation = &binary_search_tree::insert;
			clear_input_region();
			glColor3f(1.0, 0.0, 0.0);
			display_string(query_string, 100, 600);
			glFlush();
		}
		if(search_box.clicked(x, y)){
			operation = &binary_search_tree::search;
			clear_input_region();
			glColor3f(1.0, 0.0, 0.0);
			display_string(query_string, 100, 600);
			glFlush();
		}
		if(delete_box.clicked(x, y)){
			operation = &binary_search_tree::remove;
			clear_input_region();
			glColor3f(1.0, 0.0, 0.0);
			display_string(query_string, 100, 600);
			glFlush();
		}
	}

}


/*
 * =============================================================================
 *
 * A Keyboard call back function used to get the key pressed and the co-ordinates
 * of the location. This callback is used to take input of the value to be inserted
 * searched and deleted
 *
 * =============================================================================
 */

void keyboard(unsigned char key, int x, int y){
	char s[2];
	char a=key;
	static int digit = 0;
	static int number = 0;
	static int sign = 1;
	if(a==13)
    {
        if(flag1==0)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            flag1=1;
        }

        mydisplay();
    }
	if(a=='r')
        tree.draw_tree();
	if(!box_clicked)
		return ;
	if(digit == 0 && key == '-'){
		s[0]=key;
		s[1]='\0';
		glColor3f(1.0, 0.0, 0.0);
		display_string(s, 420 + (15*digit), 600);
		glFlush();
		sign = -1;
	}
	else if(key != 13 && isdigit(key)){
		digit++;
		number = (number*10) + key - '0';
		s[0]=key;
		s[1]='\0';
		glColor3f(1.0, 0.0, 0.0);
		display_string(s, 420 + (15*digit), 600);
		glFlush();
	}
	else if(key != 13 && !isdigit(key))
		;
	else{
		digit = 0;
		clear_input_region();
		(tree.*operation)(sign*number);
		number = 0;
		sign = 1;
		box_clicked = false;
	}
}

/*
 * =============================================================================
 *
 * Starting Point of the Program and is used to initialize glut and to create a
 * new glut window and initialize its attributes.
 * Registers the callback functions used in the program
 *
 * =============================================================================
 */

 void levelorder1(struct node* NODE, int level)
{
    if (NODE != NULL)
    {
    if (level == 1)
    {
        operation = &binary_search_tree::search;
        delay(15000);
        printf("%d\t",NODE->data);
        (tree.*operation)(NODE->data);
    }
    else if (level > 1)
    {
        levelorder1(NODE->left, level-1);
        levelorder1(NODE->right, level-1);
    }
    }
}

/* Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
int height(node* NODE)
{
    if (NODE == NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(NODE->left);
        int rheight = height(NODE->right);

        /* use the larger one */
        if (lheight > rheight)
            return(lheight + 1);
        else return(rheight + 1);
    }
}

void preorder1(struct node* NODE)
{
    //static int sign=1;
   if(NODE!=NULL)
{
    operation = &binary_search_tree::search;
    delay(15000);
    printf("%d\t",NODE->data);
    (tree.*operation)(NODE->data);
    preorder1(NODE->left);
    preorder1(NODE->right);
}

}

void postorder(struct node* NODE)
{
    if(NODE!=NULL)
{
    postorder(NODE->left);
    postorder(NODE->right);
    operation = &binary_search_tree::search;
    delay(15000);
    printf("%d\t",NODE->data);
    (tree.*operation)(NODE->data);
}

}

void inorder(struct node* NODE)
{
    if(NODE!=NULL)
{
    inorder(NODE->left);
    operation = &binary_search_tree::search;
    delay(15000);
    printf("%d\t",NODE->data);
    (tree.*operation)(NODE->data);
    inorder(NODE->right);
}

}

/*void levelorder(struct node* NODE)
{
    if(NODE!=NULL)
{
    levelorder(NODE->left);
    operation = &binary_search_tree::search;
    delay(15000);
    printf("%d\t",NODE->data);
    (tree.*operation)(NODE->data);
    levelorder(NODE->right);
}

}*/

void traversemenu(int id)
{
switch(id)
{
case 1: printf("PreOrder Traversal: ");
    preorder1(tree.root);
    printf("\n");
	break;
case 2: printf("PostOrder Traversal: ");
    postorder(tree.root);
    printf("\n");
	break;
case 3: printf("InOrder Traversal: ");
    inorder(tree.root);
    printf("\n");
	break;
case 4:printf("LevelOrder Traversal: ");
    int h = height(tree.root);
    int i;
    for(i=1;i<=h;i++)
    levelorder1(tree.root,i);
    printf("\n");
	break;
}
}

/*
void myreshape(int w,int h)
{
glViewport(0,0,w,h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
if(w<=h)
gluOrtho2D(-2,2,-2*(GLfloat)h/(GLfloat)w,2*(GLfloat)h/(GLfloat)w);
else
gluOrtho2D(-2*(GLfloat)w/(GLfloat)h,2*(GLfloat)w/(GLfloat)h,-2,2);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}
*/

int main(int argc,char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(SCREEN_SIZE_X,SCREEN_SIZE_Y);
	glutInitWindowPosition(0,0);
	glutCreateWindow("BINARY SEARCH TREE AND TRAVERSALS");
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	//glutReshapeFunc(myreshape);
	init();
    sb=glutCreateMenu(traversemenu);
    glutAddMenuEntry("PreOrder",1);
    glutAddMenuEntry("PostOrder",2);
    glutAddMenuEntry("InOrder",3);
    glutAddMenuEntry("LevelOrder",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
