*This project has been created as part of the 42 curriculum by ysantos-.*  

# PushSwap

## Description

Push swap is a program that will sort the integers in ascending order with the following operations being used.  
| **Command**	| **Description**	| **Execution** |
| ---			|		---			|		---		|
| **sa**	| swap `a`					| Swap the first 2 elements at the top of stack `a`. *Do nothing if there is only one element or none.*	|
| **sb**	| swap `b`					| Swap the first 2 elements at the top of stack `b`. *Do nothing if there is only one element or none.*	|
| **ss**	| `sa` and `sb` at the same time| 	|
| **pa**	| push `a`					| Take the first element at the top of `b` and put it at the top of `a`. *Do nothing if `b` is empty.*	|
| **pb**	| push `b`					| Take the first element at the top of `a` and put it at the top of `b`. *Do nothing if `a` is empty.*	|
| **ra**	| rotate `a`					| Shift up all elements of stack `a` by 1. *The first element becomes the last one.*	|
| **rb**	| rotate `b`					| Shift up all elements of stack `b` by 1. *The first element becomes the last one.*	|
| **rr**	| `ra` and `rb` at the same time| 	|
| **rra**	| reverse rotate `a`			| Shift down all elements of stack `a` by 1. *The last element becomes the first one.*	|
| **rrb**	| reverse rotate `b`			| Shift down all elements of stack `b` by 1. *The last element becomes the first one.*	|
| **rrr**	|`rra` and `rrb` at the same time| 	|

## Instructions

## Resources

libft  ***************

External Funtions used:
| **Function**	| **Description**	|
|		---		|			---		|
| **read(int fd, void buf[.count], size_t count)**	| Attempts to read up to `count` bytes from file descriptor `fd` into the buffer starting at `buf`.	|
| **write(fd, buffer, n)** | Writes up to amount of `n` bytes from the `buffer` to the file referred to by the `fd` file descriptor. |
| **void \*malloc(size_t size)**	|  Allocates `size` bytes and returns a pointer to the allocated memory.	|
| **void free(void \*ptr);**	| Frees the memory space pointed to by `ptr`.	|
| **void exit(int status)**	| Causes normal process termination and the least significant byte of `status` (max of 255, i.e., status & 0xFF) is returned to the parent.	|


## Algorithm

The `in_order()` is called before any algorithm is, and if a stack is in order but just out of place, it already rotates to fix it. For only two numbers, if they're out of order, the function will always fix it.  
From this point, there are 3 different algorithms to work with different amount of numbers to put in order.  

### Sort Three

Before this command is called, the `in_order()` function was already called. So the cases that numbers are in order but don't have the lowest number on top were already solved.  
Then it does a check-up in what number is bigger or than the others to see what type of command should be given.  
*Let's treat the numbers on the current order as **n0**, **n1** and **n2**.*  

|	Case	|	Command	|
|	----	|	----	|
| **n0 > n1 && n0 < n2** | Swap 2 first numbers. |
| **n0 < n1 && n0 < n2** | Swap 2 first numbers and rotate the stack. |
| **n0 > n1 && n0 > n2** | Rotate the stack and swap 2 first numbers. |

### Sort Five
This works with five or four numbers, by pushing the 2 (or 1 in case of 4 arguments) lowests numbers to stack b. It will push using the least amount of rotation possible, so if the lowest end on top of stack `b`, it'll be flagged to rotate. The rotation is needed so that when they are pushed back to `a` everything will be already on order.    
After it'll organize stack `a` by calling `in_order()` and if that didin't solved, it'll call `sort_three()`. Sorthing the three, the `rotate_b` flag, signalizes if a double rotation can be done, using in that case 1 less command. After that, all that's left is to push number(s) in `b` back to `a`.  