#include<stdio.h>
#define SCREEN_SIZE_X 1000
#define SCREEN_SIZE_Y 700
#define BG_R 1.0
#define BG_G 1.0
#define BG_B 1.0
#define BG_A 1.0

struct node {
	int data;
	struct node *left;
	struct node *right;
};

typedef struct node* NODE;

NODE root = NULL;

char query_string[] = "Enter an Integer and Hit Enter : ";

char not_found[] = "Item Not found";

float node_color[3] = {0.1, 0.0, 0.0};
void mydisplay();
void display();
void display1();
