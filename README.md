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

