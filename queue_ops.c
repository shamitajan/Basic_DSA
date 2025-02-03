#include <stdio.h>

int full(int rear, int size) { 
    if(rear == size - 1)
        return 1;
    else
        return 0;
}

int empty(int rear, int front) { 
    if(rear == front)
        return 1;
    else
        return 0;
}

void AddQ(int q[], int *rear, int size, int elem) {
    if(full(*rear, size))
        printf("Queue is full\n");
    else { 
        *rear=*rear+1;
        q[*rear] = elem;
    }
}

int DelQ(int q[], int *rear, int *front) {
    int elem;
    if(empty(*rear, *front))
        return -1;
    else { 
        *front=*front+1;
        elem = q[*front];
        return elem;
    }
}

void accept(int n, int q[]) {
    for(int i = 0; i < n; i++) {
        printf("Enter element %d: ", (i + 1));
        scanf("%d", &q[i]);
    }
}

void display(int q[], int front, int rear) {
    if(empty(rear, front) == 1) {
        printf("Queue is empty\n");
    } else {
        printf("Queue elements are: ");
        for(int i = front + 1; i <= rear; i++) {
            printf("%d ", q[i]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    int rear = -1;
    int front = -1;
    int elem;
    
    printf("Enter no. of elements: ");
    scanf("%d", &n);
    int q[n];

    while(1) {
        printf("Enter 1 to add element, 2 to delete element, 0 to exit: ");
        int x;
        scanf("%d", &x);

        switch(x) {
            case 1:
                printf("Enter element to be added: ");
                scanf("%d", &elem);
                AddQ(q, &rear, n, elem);
                break;

            case 2:
                elem = DelQ(q, &rear, &front);  
                if(elem == -1) {
                    printf("Queue is empty, cannot delete element\n");
                } else {
                    printf("Deleted element: %d\n", elem);
                }
                break;
            
            case 0:
                printf("Exiting...\n");
                return 0;

            default:
                printf("INVALID\n");
        }
        display(q, front, rear);
    }
    
    return 0;
}
