# Linux Project 1

* Part 1 (100 points):
The kernel address space of all processes maps into the same physical address space.
How does the kernel maintains the above property?
You need to design and write code to proof your claim.
### Hint:
The process list is a circular doubly linked list that links the process descriptors of all existing thread group leaders:
Each task_struct structure includes a tasks field of type list_head whose prev and next fields point, respectively, to the previous and to the next task_struct element's tasks field.
The head of the process list is the init_task task_struct descriptor; it is the process descriptor of the so-called process 0 or swapper.
 
* Part 2 (70 points):
After a person uses Fix-Mapped Linear Addresses to map a 4K kernel address space to a 4k page frame, will existing processes get this new mapping?
If your answer is yes, how does the kernel complete this mapping?
You need to design and write code to proof your claim.
