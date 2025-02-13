#include <iostream>
#include <string>
using namespace std;

class gnode {
protected:
    int user_id;
    string name;
    gnode *next;

    gnode() : user_id(-1), next(NULL) {} // Default constructor

    friend class graph;
};

class Stack {
private:
    int data[10]; // Fixed size for simplicity
    int top;

public:
    Stack() : top(-1) {}

    void push(int value) {
        if (top >= 9) {
            cout << "Stack overflow!\n";
            return;
        }
        data[++top] = value;
    }

    void pop() {
        if (top == -1) {
            cout << "Stack underflow!\n";
            return;
        }
        --top;
    }

    int peek() {
        return (top == -1) ? -1 : data[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

class Queue {
private:
    int data[10];
    int front, rear;

public:
    Queue() : front(-1), rear(-1) {}

    void enqueue(int value) {
        if (rear >= 9) {
            cout << "Queue overflow!\n";
            return;
        }
        if (front == -1) front = 0;
        data[++rear] = value;
    }

    void dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue underflow!\n";
            return;
        }
        front++;
    }

    int peek() {
        return (front == -1 || front > rear) ? -1 : data[front];
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }
};

class graph {
private:
    gnode *head[10];
    int n;
    bool visited[10];

public:
    graph() {
        cout << "Enter the number of users (max 10): ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            head[i] = new gnode;
            head[i]->user_id = i;
            cout << "Enter the name for user " << i << ": ";
            cin >> head[i]->name;
            head[i]->next = NULL;
        }
    }

    void create() {
        for (int i = 0; i < n; i++) {
            gnode *temp = head[i];
            char ch;

            cout << "Add friends for user " << head[i]->name << " (user_id: " << i << ")\n";

            do {
                int v;
                cout << "Enter the user_id of the friend: ";
                cin >> v;

                if (v < 0 || v >= n || v == i) {
                    cout << "Invalid user_id. Please try again.\n";
                } else {
                    gnode *curr = new gnode;
                    curr->user_id = v;
                    curr->name = head[v]->name;
                    curr->next = NULL;
                    temp->next = curr;
                    temp = curr;
                }

                cout << "Do you want to add more friends for " << head[i]->name << "? (Y/N): ";
                cin >> ch;
            } while (ch == 'Y' || ch == 'y');
        }
    }

    void display() {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < n; i++) {
            cout << head[i]->name << " (user_id: " << head[i]->user_id << ") -> ";
            gnode *temp = head[i]->next;
            while (temp != NULL) {
                cout << temp->name << " (user_id: " << temp->user_id << ") -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }

    void DFS_recursive(int v) {
        if (visited[v]) return;
        cout << head[v]->name << " (user_id: " << v << ")\n";
        visited[v] = true;
        gnode *temp = head[v]->next;
        while (temp) {
            DFS_recursive(temp->user_id);
            temp = temp->next;
        }
    }

    void DFS_non_rec(int v) {
        bool visited[10] = {false};
        Stack s;
        s.push(v);
        cout << "\nDFS starting from " << head[v]->name << ":\n";
        while (!s.isEmpty()) {
            int curr = s.peek();
            s.pop();
            if (!visited[curr]) {
                visited[curr] = true;
                cout << head[curr]->name << " (user_id: " << curr << ")\n";
            }
            gnode *temp = head[curr]->next;
            while (temp) {
                if (!visited[temp->user_id]) {
                    s.push(temp->user_id);
                }
                temp = temp->next;
            }
        }
    }

    void BFS(int v) {
        bool visited[10] = {false};
        Queue q;
        visited[v] = true;
        q.enqueue(v);
        cout << "\nBFS starting from " << head[v]->name << ":\n";
        while (!q.isEmpty()) {
            int curr = q.peek();
            q.dequeue();
            cout << head[curr]->name << " (user_id: " << curr << ")\n";
            gnode *temp = head[curr]->next;
            while (temp) {
                if (!visited[temp->user_id]) {
                    visited[temp->user_id] = true;
                    q.enqueue(temp->user_id);
                }
                temp = temp->next;
            }
        }
    }

    void DFS_rec_start(int v) {
        fill(begin(visited), end(visited), false);
        cout << "\nDFS (Recursive) starting from " << head[v]->name << ":\n";
        DFS_recursive(v);
    }
};

int main() {
    graph g;
    g.create();
    int choice;
    do {
        cout << "\nMenu:\n1. Display the graph\n2. DFS (Non-Recursive)\n3. DFS (Recursive)\n4. BFS\n5. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            g.display();
            break;
        case 2:
            int start;
            cout << "Enter the starting user_id for DFS: ";
            cin >> start;
            g.DFS_non_rec(start);
            break;
        case 3:
            cout << "Enter the starting user_id for DFS (Recursive): ";
            cin >> start;
            g.DFS_rec_start(start);
            break;
        case 4:
            cout << "Enter the starting user_id for BFS: ";
            cin >> start;
            g.BFS(start);
            break;
        case 5:
            cout << "Exited program\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);
    return 0;
}
