/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
    printf("[-----[Seo han bit]   [2019038043]-----]\n");

	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)                              //head가 NULL이 아니면 head를 메모리 해제
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));           //head에 메모리 할당
	(*h)->left = NULL;	/* root */              //head의 left를 NULL로 초기화
	(*h)->right = *h;                           //head의 right는 어차피 쓰지 않을것이라서 자기 자신을 가리키든 NULL값으로 초기화 해주던 크게 상관이 없음.
	(*h)->key = -9999;                          //right를 쓰지 않기로 했기때문에 head의 key값 보다 작은값이 없다는 것을 알려주기위해 임의의 값 -9999로 초기화
	return 1;
}



void inorderTraversal(Node* ptr)                //중위 운행법
{
    if(ptr) {                                   //중위 운행법은 Left->Root->Right 순으로 읽는다.
		inorderTraversal(ptr->left);            //재귀함수를 통해서 가장 왼쪽인 Left로 가서 Left를 읽고 그 Left부터 운행법 순으로 Root와 Right를 읽으면서 운행한다
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)               //전위 운행법
{
    if(ptr) {                                   //전위 운행법은 root->left->right 순으로 읽는다.
		printf(" [%d] ", ptr->key);             //똑같이 재귀함수를 쓰는데 대신에 Root값을 읽어주고 left로 넘어가는 식으로 가장 왼쪽의 left로 가서 left를 읽은 후 운행법 순으로 right를 읽는다
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)              //후위 운행법
{
    if(ptr) {                                   //후위 운행법은 left->right->root 순으로 읽는다.
		postorderTraversal(ptr->left);          //재귀함수를 통해 가장 왼쪽인 left로 가서 left를 읽고 right와 root 순으로 읽으면서 운행한다.
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
    Node* newNode = (Node*)malloc(sizeof(Node));        //새로운 node를 하나 만들어 메모리 할당
	newNode->key = key;                                 //새로운 node의 key 값에 사용자로부터 받아온 key값 초기화
	newNode->left = NULL;                               //node의 left와 right를 모두 NULL값으로 초기화
	newNode->right = NULL;

	if (head->left == NULL) {                           //head의 left가 NULL을 가리키고 있으면 아직 아무것도 없다는 것을 의미하므로
		head->left = newNode;                           //head의 left가 newNode를 가리키게 만듬
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;                             //ptr이 head->left가 가리키는 곳이 되게 함

	Node* parentNode = NULL;                            //parentNode를 NULL값으로 초기화 시켜줌
	while(ptr != NULL) {                                //ptr이 NULL값이 될때까지 돌아가는 while문

		if(ptr->key == key) return 1;                   //ptr의 key값과 받아온 key값이 같다면 함수 종료

		parentNode = ptr;                               //parentNode가 ptr이 되게함

		if(ptr->key < key)                              //ptr->key의 값이 받아온 key의 값보다 작다면
			ptr = ptr->right;                           //ptr이 ptr->right가 가리키는 곳이 되게 함
		else                                            //아니면
			ptr = ptr->left;                            //ptr->left가 가리키는 곳이 되게 함
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)                           //부모노드의 key값이 받아온 key값보다 클 경우
		parentNode->left = newNode;                     //left가 newNode를 가리키게 하고
	else                                                //작을 경우
		parentNode->right = newNode;                    //right가 newNode를 가리키게 함
	return 1;
}

int deleteLeafNode(Node* head, int key)                 
{
    
	
}

Node* searchRecursive(Node* ptr, int key)           //recursive 방식으로 검색
{
    
}

Node* searchIterative(Node* head, int key)          //iterative 방식으로 검색
{
                    
}
void freeNode(Node* ptr)                    
{
	
}

int freeBST(Node* head)
{

	
}






