
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10

struct student {
    int rno;
    char name[20];
    int div;
};

void accept(struct student s[], int n) {
    int i;
    printf("Enter student Info:\n");
    for(i = 0; i < n; i++) {
        printf("For student %d:\n", i + 1);
        printf("Enter Roll No: ");
        scanf("%d", &s[i].rno);
        printf("Name: ");
        scanf("%s", s[i].name);
        printf("Division: ");
        scanf("%d", &s[i].div);
        printf("\n");
    }
}

void display(struct student s[], int n) {
    int i;
    printf("Student Info are as follows:\n");
    printf("SrNo.\tRoll No.\tName\t\tDivision\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t\t%s\t\t%d\n\n", i + 1, s[i].rno, s[i].name, s[i].div);
    }
}

void bubblesort(struct student s[], int n) {
    int i, j;
    struct student temp;
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - 1 - i; j++) {
            if(s[j].rno > s[j + 1].rno) {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

void selectionsort(struct student s[], int n) {
    int i, j, minpos;
    struct student temp;
    for(i = 0; i < n - 1; i++) {
        minpos = i;
        for(j = i + 1; j < n; j++) {
            if(s[j].rno < s[minpos].rno) {
                minpos = j;
            }
        }
        if(minpos != i) {
            temp = s[i];
            s[i] = s[minpos];
            s[minpos] = temp;
        }
    }
}

void insertionsort(struct student s[], int n) {
    int i, j;
    struct student key;
    for(i = 1; i < n; i++) {
        key = s[i];
        j = i - 1;
        while(j >= 0 && s[j].rno > key.rno) {
            s[j + 1] = s[j];
            j = j - 1;
        }
        s[j + 1] = key;
    }
}

int main() {
    struct student s[MAX_STUDENTS];
    int n, choice, select;

    do {
        printf("Select Type of Sort:\n1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n");
        scanf("%d", &choice);

        printf("Enter no. of students: ");
        scanf("%d", &n);
        if (n > MAX_STUDENTS) {
            printf("Number of students should be less than or equal to %d\n", MAX_STUDENTS);
            continue;
        }

        accept(s, n);

        switch (choice) {
            case 1:
                bubblesort(s, n);
                break;
            case 2:
                selectionsort(s, n);
                break;
            case 3:
                insertionsort(s, n);
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }

        display(s, n);

        printf("\nDo you want to Sort again?\n1. Yes\n2. No\n");
        scanf("%d", &select);
    } while(select == 1);
    return 0;
}