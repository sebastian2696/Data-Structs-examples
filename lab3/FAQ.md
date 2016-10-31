
#### Undefined reference to some math functions like 'pow'?
Append the following flag when you run gcc

```
-lm
```

#### What is the expected result for example ' 4 3 + 2 8 - * p '?
For the stack-based implementation, we should confine to the [standard calculator dc] (http://linux.die.net/man/1/dc), 
so the correct answer is -42.000000, for the queue-based implementation, depending on the order of your operands for 
'-' '/' or '%', answer '40.000000' and '-40.000000' are all acceptable for this exercise.
