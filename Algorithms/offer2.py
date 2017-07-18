# 用两个栈模拟队列(牛客网-剑指offer)
# 用两个栈来实现一个队列，完成队列的Push和Pop操作。 
# 队列中的元素为int类型

class Queue:

    def __init__(self):
        self.stack1 = [] # 队首在栈底, 低索引为栈底
        self.stack2 = [] # 队首在栈顶
    
    def __len__(self):
        return len(self.stack1) + len(self.stack2)

    def pop(self):
        # 如果 stack 1 中不为空
        if len(self.stack1):
            self.transfer(self.stack1, self.stack2)
            return self.stack2.pop()
        else:
            # 如果为空会抛出异常
            return self.stack2.pop()

    def push(self, value):
        # 如果 stack2 中不为空
        if len(self.stack2):
            self.transfer(self.stack2, self.stack1)
        return self.stack1.append(value)     

    def transfer(self, stack1, stack2):
        while(len(stack1)):
            stack2.append(stack1.pop())


if __name__ == '__main__':
    queue = Queue()
    queue.push(1)
    queue.push(2)
    print(queue.pop())
    queue.push(3)
    print(queue.pop())
    print(queue.pop())
