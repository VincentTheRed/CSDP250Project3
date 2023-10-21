/******************************************
 * Author: Vincent Bardinelli
 * Date: 10/21/2023
 * Class: CSDP 250 Fall 2023
 * Assignment: Project 3
 *
 * Decimal to Binary Converter
 *
 * This program takes a decimal number as input,
 * splits it into its integer and fractional parts,
 * and then converts each part into its binary
 * equivalent using a stack for the integer part
 * and a queue for the fractional part.
 ******************************************/

#include<iostream>
#include<cmath>
#include<string>
using namespace std;

struct Node {
    int data;
    Node* next;
};

//Stack class using linked list
class Stack {
public:
    Node* top;

    //Constructor
    Stack() {
        top = nullptr;
    }

    //Push data onto the stack
    void push(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = top;
        top = newNode;
    }

    //Pop data from the stack
    int pop() {
        if (top == nullptr) {
            return -1;
        }
        Node* temp = top;
        top = top->next;
        int data = temp->data;
        delete temp;
        return data;
    }

    //Check if stack is empty
    bool isEmpty() {
        return top == nullptr;
    }
};

//Queue class using linked list
class Queue {
public:
    Node* front;
    Node* rear;

    //Constructor
    Queue() {
        front = rear = nullptr;
    }

    //Enqueue data onto the queue
    void enqueue(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = nullptr;
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    //Dequeue data from the queue
    int dequeue() {
        if (front == nullptr) {
            return -1;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        int data = temp->data;
        delete temp;
        return data;
    }

    //Check if queue is empty
    bool isEmpty() {
        return front == nullptr;
    }
};

//Convert integer to binary using stack
string integerToBinary(int n) {
    if (n == 0) {
        return "0";
    }
    Stack s;
    while (n > 0) {
        s.push(n % 2);
        n /= 2;
    }
    string binary = "";
    while (!s.isEmpty()) {
        binary += to_string(s.pop());
    }
    return binary;
}

//Convert decimal to binary using queue
string decimalToBinary(const string& decimalStr) {
    double fractional = stod("0." + decimalStr);
    Queue q;
    while (fractional > 0) {
        fractional *= 2;
        int bit = static_cast<int>(fractional);
        q.enqueue(bit);
        fractional -= bit;
    }
    string binary = "";
    while (!q.isEmpty()) {
        binary += to_string(q.dequeue());
    }
    return binary;
}


int main() {
    string numberStr;
    cout << "Enter a decimal number: ";
    cin >> numberStr;

    size_t decimalPos = numberStr.find('.');
    int integerPart = stoi(numberStr.substr(0, decimalPos));
    string decimalStr = (decimalPos != string::npos) ? numberStr.substr(decimalPos + 1) : "0";

    string binaryInteger = integerToBinary(integerPart);  //Convert integer part to binary
    string binaryFractional = decimalToBinary(decimalStr);  //Convert fractional part to binary

    cout << "Integer Part: " << binaryInteger << endl;
    cout << "Decimal Part: " << binaryFractional << endl;

    return 0;
}
