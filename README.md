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

To use the program you first need compile the executable, run:

```bash
make
```

The program takes integers as argument and output the movements needed to set them on a increasing order. Any other argument that isn't an integer will result in an error.  

An example of a proper use can be any of the following:  
```bash
./push_swap 3 41234 454 123 5425
./push_swap "3" "41234" "-454 123 5425"
./push_swap 3 41234 "454 -123 5425"
```

## Resources

libft functions used:  

| **Function**	| **Description**	|
|		---		|			---		|
| **ft_isspace()** | Boolean checking if the char received as an argument is a space on the ASCII table. |
| **ft_isdigit()**| Boolean checking for a digit (0 through 9). |
| **ft_putendl_fd()**| Outputs the string `s` to the file descriptor fd followed by a `\n`. |
| **ft_lstsize()**| Returns the number of nodes in the list. |
| **ft_abs()**| Returns the absolute (positive) value of a int. |
| **ft_calloc()**| Allocates memory of `num` elements of size `bytes` each, every byte is set to 0. Returns the pointer to allocated memory. |
| **ft_atoi()**| Converts the initial portion of the string pointed to by str to int. |
| **ft_atoi_overflow()**| Checks if number on the string will result on a int overflow. |

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

### Sort Biggers
For 6 or more arguments the algorithm is the same. Altough it isn't the greatest for large amount of arguments *(500)*, it still handles with the amount of moves asked by the subject.  
It was used the **Longest Incresing Subsequence** *(LIS)*, to find the numbers that are already in order and push the others to stack `B`. It get the LIS starting from each number on the stack, to find the longest LIS possible **but also taking into consideration the amount of rotation needed to get to it**. Before the number is pushed to `B`, it sees if a `swap` can be done, to simplily set that current number on it's right location.  
Then it sees from each node on the `B` stack, how many moves, on `A` and `B`, are needed to set them on the right position. Once we know wich node does less moves it does it, and do it all over until stack B is empty.  
From that, it calls a `in_order()` to rotate the stack `A` in order to leave the lowest number on top, having then the stack on order.  
