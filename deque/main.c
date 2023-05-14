#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 50
#define MAX_SIZE 50


typedef char element;

typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}DequeType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	return;
}

void init_deque(DequeType* q) {
	q->front = q->rear = 0;
}

int is_empty(DequeType* q) {
	return (q->front == q->rear);
}

int is_full(DequeType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void deque_print(DequeType* q) {
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("Queue Full!");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("Queue Empty!");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element get_front(DequeType* q) {
	if (is_empty(q))
		error("Queue Empty!");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void add_front(DequeType* q, element val) {
	if (is_full(q))
		error("Queue Full!");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q) {
	int prev = q->rear;
	if (is_empty(q))
		error("Queue Empty!");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

element get_rear(DequeType* q) {
	if (is_empty(q))
		error("Queue Empty!");
	return q->data[q->rear];
}

char change(char ch) {
	if (ch >= 'A' && ch <= 'Z') {
		return ch + 32;
	}
	else {
		return ch;
	}
}

int alpha(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}


int check(char str[]){
	DequeType d;
	init_deque(&d);
	int count = 0, check = 1;
	char ch;
	for (int i = 0; i < strlen(str); i++) {
		ch = str[i];
		if (alpha(ch)) {
			ch = change(ch);
			add_rear(&d, ch);
			count++;
		}
	}

	for (int i = 0; i < count / 2; i++) {
		if (delete_front(&d) != delete_rear(&d)) {
			check = 0;
			break;
		}
	}
	return check;
}



int main(void){
	DequeType q;
	while (1) {
		init_deque(&q);
		char str[MAX_SIZE];

		printf("Enter a string (or input 'exit') : ");
		fgets(str, MAX_SIZE, stdin);

		str[strlen(str) - 1] = '\0';

		if (strcmp(str, "exit") == 0) {
			printf("Program exit\n");
			break;
		}
		else {
			if (check(str) == 1) {
				printf("%s is a palindrome.\n", str);
			}
			else {
				printf("%s is not a palindrome.\n", str);
			}
		}
		printf("\n");
	}
	return 0;
}