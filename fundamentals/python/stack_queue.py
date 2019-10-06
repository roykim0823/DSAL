#!/usr/bin/pyhton3

class Node:
    def __init__(self, data=None, next=None):
        self.data = data
        self.next = next
        
    def __str__(self):
        return str(self.data)   

class LinkedStack:
    def __init__(self):
        self.head = None

    def isEmpty(self):
        return self.head == None

    def push(self, data):
        old_head = self.head
        self.head = Node()
        self.head.data = data
        self.head.next = old_head

    def pop(self):
        data = self.head.data
        self.head = self.head.next
        return data

class ArrayStack:
    def __init__(self):
        self.array = []
    
    def isEmpty(self):
        return len(self.array) == 0
    
    def push(self, data):
        self.array.append(data)        
    
    def pop(self):
        return self.array.pop() # default -1       

def test_stack(stack):
    stack.push(30)
    stack.push(20)
    stack.push(10)
    stack.push(0)
    print(stack.pop())
    print(stack.pop())
    print(stack.pop())
    print(stack.pop())

class LinkedQueue:
    def __init__(self):
        self.head = None
        self.tail = None

    def isEmpty(self):
        return self.head == None

    def enqueue(self, data):
        old_tail = self.tail
        self.tail = Node()
        self.tail.data = data
        self.tail.next = None
        if self.isEmpty():
            self.head = self.tail
        else:
            old_tail.next = self.tail

    def dequeue(self):
        data = self.head.data
        self.head = self.head.next
        if self.isEmpty():
            self.tail = None
        return data

class ArrayQueue:
    def __init__(self):
        self.array = []

    def isEmpty(self):
        return len(self.array) == 0

    def enqueue(self, data):
        self.array.append(data)

    def dequeue(self):
        return self.array.pop(0) # default -1


def test_queue(queue):
    queue.enqueue(30)
    queue.enqueue(20)
    queue.enqueue(10)
    queue.enqueue(0)
    print(queue.dequeue())
    print(queue.dequeue())
    print(queue.dequeue())
    print(queue.dequeue())


def main():
    print('Test LinkedStack()')
    stack = LinkedStack()
    test_stack(stack)
    print('Test ArrayStack()')
    stack = ArrayStack()
    test_stack(stack)
    
    print('Test LinkedQueue()')
    queue = LinkedQueue()
    test_queue(queue)
    print('Test ArrayQueue()')
    queue = ArrayQueue()
    test_queue(queue)


if __name__ == '__main__':
  main()
