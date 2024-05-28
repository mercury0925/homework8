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

typedef struct node { // 구조체 정의
	int key; // 노드의 key 값 
	struct node *left; // 왼쪽 자식 노드를 가리킬 포인터
	struct node *right; // 오른쪽 자식 노드를 가리킬 포인터
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
	char command; // 사용자 입력을 받을 변수
	int key; // 키 값을 저장할 변수
	Node* head = NULL; // 트리의 루트 노드를 가리킬 포인터
	Node* ptr = NULL;	/* temp */  // 현재 노드를 가리킬 포인터

	printf("-----------------[HanKangmin] [2023078040]----------------");
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
		scanf(" %c", &command); // 사용자 입력을 받음

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
			ptr = searchIterative(head, key); // 반복적 탐색
			if(ptr != NULL) // 찾으려는 키가 트리에 있는 경우
				printf("\n node [%d] found at %p\n", ptr->key, ptr); // 찾은 노드의 key 값과 주소 출력
			else // 찾으려는 키가 트리에 없는 경우
				printf("\n Cannot find the node [%d]\n", key); // 찾으려는 키가 트리에 없음을 알리는 메시지 출력
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key); // 재귀적 탐색
			if(ptr != NULL) // 찾으려는 키가 트리에 있는 경우
				printf("\n node [%d] found at %p\n", ptr->key, ptr); // 찾은 노드의 key 값과 주소 출력
			else // 찾으려는 키가 트리에 없는 경우
				printf("\n Cannot find the node [%d]\n", key); // 찾으려는 키가 트리에 없음을 알리는 메시지 출력
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
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

// 중위 순회
void inorderTraversal(Node* ptr)
{
	if(ptr) { // ptr이 NULL이 아닐 때
		inorderTraversal(ptr->left); // 왼쪽 자식 노드로 이동, 왼쪽 자식 노드가 NULL이 될 때까지 반복
		printf("[%d] ", ptr->key); // 왼쪽 자식 노드가 NULL이 되면 현재 노드의 key값 출력
		inorderTraversal(ptr->right); // 오른쪽 자식 노드로 이동, 오른쪽 자식 노드가 NULL이 될 때까지 반복
	}
}

// 전위 순회
void preorderTraversal(Node* ptr)
{
	if(ptr) { // ptr이 NULL이 n아닐 때
		printf("[%d] ", ptr->key); // 현재 노드의 key값 출력
		preorderTraversal(ptr->left); // 왼쪽 자식 노드로 이동, 왼쪽 자식 노드가 NULL이 될 때까지 반복
		preorderTraversal(ptr->right); // 오른쪽 자식 노드로 이동, 오른쪽 자식 노드가 NULL이 될 때까지 반복
	}
}

// 후위 순회
void postorderTraversal(Node* ptr)
{
	if(ptr) { // ptr이 NULL이 아닐 때
		postorderTraversal(ptr->left); // 왼쪽 자식 노드로 이동, 왼쪽 자식 노드가 NULL이 될 때까지 반복
		postorderTraversal(ptr->right); // 오른쪽 자식 노드로 이동, 오른쪽 자식 노드가 NULL이 될 때까지 반복
		printf("[%d] ", ptr->key); // 왼쪽 자식 노드와 오른쪽 자식 노드가 NULL이 되면 현재 노드의 key값 출력
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // 새 노드를 위한 메모리 할당
	newNode->key = key; // 새 노드의 key 값 설정
	newNode->left = NULL; // 새 노드의 왼쪽 자식 노드를 NULL로 초기화
	newNode->right = NULL; // 새 노드의 오른쪽 자식 노드를 NULL로 초기화

	if(head->left == NULL) { // 트리가 비어있는 경우
		head->left = newNode; // 새 노드를 루트 노드로 설정
		return 1;
	}
	
	Node* parent = NULL; // 부모 노드를 가리킬 포인터
	Node* ptr = head->left; // 현재 노드를 가리킬 포인터

	while(ptr != NULL) { // 현재 노드가 NULL이 아닐 때까지 반복 (트리의 적절한 위치를 찾기 위해)
		if(ptr->key == key) { // 현재 노드의 키가 삽입하려는 키와 같은 경우
			printf("The key is already in the tree."); // 이미 트리에 존재하는 키임을 알리는 오류 메시지 출력
			free(newNode); // 새 노드 메모리 해제
			return 0;
		}
		parent = ptr; // 부모 노드를 현재 노드로 설정     
		if(ptr->key > key) { // 현재 노드의 키 > 삽입하려는 키
			ptr = ptr->left; // 현재 노드를 왼쪽 자식 노드로 이동
		}
		else {	// 현재 노드의 키 < 삽입하려는 키
			ptr = ptr->right; // 현재 노드를 오른쪽 자식 노드로 이동
		}
	}

	if(parent->key > key) { // 부모 노드의 키 > 삽입하려는 키
		parent->left = newNode; // 새 노드를 부모 노드의 왼쪽 자식으로 설정
	}
	else { // 부모 노드의 키 < 삽입하려는 키
		parent->right = newNode; // 새 노드를 부모 노드의 오른쪽 자식으로 설정
	}
	return 1;
}

int deleteLeafNode(Node* head, int key)
{	
	if(head == NULL) { // 트리가 비어있는 경우
		printf("There is no node to delete."); // 삭제할 노드가 없음을 알리는 오류 메시지 출력
		return 0;
	}

	Node* parent = NULL; // 부모 노드를 가리킬 포인터 초기화
	Node* ptr = head->left; // 현재 노드를 가리킬 포인터

	while(ptr != NULL) { // 현재 노드가 NULL이 아닐 때까지 반복 
		if(ptr->key == key) { // 현재 노드의 키가 삭제하려는 키와 같은 경우
			if(ptr->left == NULL && ptr->right == NULL) { // 현재 노드가 리프 노드인 경우
				if(parent == NULL) { // 현재 노드가 루트 노드인 경우
					head->left = NULL; // 루트 노드 삭제
				}
				else if(parent->left == ptr) { // 현재 노드가 부모 노드의 왼쪽 자식인 경우
					parent->left = NULL; // 부모 노드의 왼쪽 자식 노드 삭제
				}
				else { // 현재 노드가 부모 노드의 오른쪽 자식인 경우
					parent->right = NULL; // 부모 노드의 오른쪽 자식 노드 삭제
				}
				free(ptr); // 현재 노드 메모리 해제
				ptr = NULL; // 현재 노드 NULL로 초기화
				return 1; // 삭제 성공
			}
			else { // 현재 노드가 리프 노드가 아닌 경우
				printf("The node [%d] is not a leaf.", key); // 리프 노드가 아님을 알리는 오류 메시지 출력
				return 0;
			}
		}
		else if(ptr->key > key) { // 현재 노드의 키 > 삭제하려는 키
			parent = ptr; // 부모 노드를 현재 노드로 설정
			ptr = ptr->left; // 현재 노드를 왼쪽 자식 노드로 이동
		}
		else { // 현재 노드의 키 < 삭제하려는 키
			parent = ptr; // 부모 노드를 현재 노드로 설정
			ptr = ptr->right; // 현재 노드를 오른쪽 자식 노드로 이동
		}
	}
	return 0;
}

// 이원 탐색 트리의 재귀적 탐색
Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // 현재 노드가 NULL인 경우(트리가 비어있는 경우)
		return NULL; // NULL 반환
	if(ptr->key == key) // 현재 노드의 키가 찾으려는 키와 같은 경우
		return ptr; // 현재 노드 반환
	else if(ptr->key > key) // 현재 노드의 키 > 찾으려는 키
		return searchRecursive(ptr->left, key); // 왼쪽 서브트리 탐색
	else // 현재 노드의 키 < 찾으려는 키
		return searchRecursive(ptr->right, key); // 오른쪽 서브트리 탐색
}

// 이원 탐색 트리의 반복적 탐색
Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left; // 현재 노드를 루트 노드로 설정
	while(ptr != NULL) { // 현재 노드가 NULL이 아닐 때까지 반복
		if(key == ptr->key) { // 현재 노드의 키가 찾으려는 키와 같은 경우
			return ptr; // 현재 노드 반환
		}
		else if(key < ptr->key) { // 현재 노드의 키 > 찾으려는 키
			ptr = ptr->left; // 왼쪽 서브트리로 이동
		}
		else { // 현재 노드의 키 < 찾으려는 키
			ptr = ptr->right; // 오른쪽 서브트리로 이동
		}
	}
	return NULL; // 찾으려는 키가 트리에 없는 경우 NULL 반환
}

int freeBST(Node* head)
{
	if(head != NULL) // 현재 노드가 NULL이 아닌 경우
    {
        freeBST(head->left); // 왼쪽 서브트리에 대해 재귀적으로 메모리 해제
        freeBST(head->right); // 오른쪽 서브트리에 대해 재귀적으로 메모리 해제
        free(head); // 현재 노드에 할당된 메모리 해제
    }
	return 1; 
}