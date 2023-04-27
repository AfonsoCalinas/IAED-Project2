# Projecto 2 - IAED 2022/2023

## Enunciado

O enunciado do projecto está disponível em [enunciado.md](enunciado.md). 

## Data de entrega: 14 de abril de 2023, às 19h59

Informações detalhadas sobre o processo de submissão estão disponíveis em [informacoes.md](informacoes.md).



# Evaluation

2023-04-14T19:10:14

## Test 1: [+ Accepted+].
## Test 2: [+ Accepted+].
## Test 3: [+ Accepted+].
## Test 4: [+ Accepted+].
## Test 5: [+ Accepted+].
## Test 6: [+ Accepted+].
## Test 7: [+ Accepted+].
## Test 8: [+ Accepted+].
## Test 9: [- Wrong Answer-].


## Test 10: [- Wrong Answer-].


## Test 11: [- Wrong Answer-].


## Test 12: [- Wrong Answer-].


## Test 13: [- Wrong Answer-].


## Test 14: [- Wrong Answer-].


## Test 15: [- Wrong Answer-].


## Test 16: [- Wrong Answer-].


## Test 17: [- Wrong Answer-].


## Test 18: [- Wrong Answer-].


## Test 19: [- Command terminated by signal (11: SIGSEGV)-].

## Test 20: [- Command terminated by signal (11: SIGSEGV)-].

## Test 21: [- Wrong Answer-].


## Test 22: [- Command terminated by signal (6: SIGABRT)-].

## Test 23: [- Command terminated by signal (11: SIGSEGV)-].

## Test 24: [- Wrong Answer-].


## Test 25: [- Command terminated by signal (11: SIGSEGV)-].

## Test 26: [- Command terminated by signal (11: SIGSEGV)-].

## Test 27: [- Command terminated by signal (6: SIGABRT)-].

## Test 28: [- Command terminated by signal (6: SIGABRT)-].

## Test 29: [- Memory Limit Exceeded-].

## Test 30: [- Memory Limit Exceeded-].

## Test 31: [- Memory Limit Exceeded-].

## Test 32: [+ Accepted+].


## Number of passed tests: 9/32


## Valgrind Output:


```
==11833== Memcheck, a memory error detector
==11833== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==11833== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==11833== Command: ./proj.out
==11833== 
==11833== Invalid read of size 4
==11833==    at 0x10AEB0: removeStop (project2.c:925)
==11833==    by 0x1094BA: main (project2.c:242)
==11833==  Address 0x4c55620 is 0 bytes after a block of size 32 alloc'd
==11833==    at 0x4837D7B: realloc (vg_replace_malloc.c:826)
==11833==    by 0x10A54A: createConnection (project2.c:637)
==11833==    by 0x10943E: main (project2.c:215)
==11833== 
==11833== Invalid read of size 8
==11833==    at 0x10AFA4: removeStop (project2.c:952)
==11833==    by 0x1094BA: main (project2.c:242)
==11833==  Address 0x4b94580 is 0 bytes inside a block of size 48 free'd
==11833==    at 0x48369AB: free (vg_replace_malloc.c:530)
==11833==    by 0x1096D8: main (project2.c:159)
==11833==  Block was alloc'd at
==11833==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==11833==    by 0x109A91: addRoute (project2.c:381)
==11833==    by 0x1096D8: main (project2.c:159)
==11833== 
==11833== Use of uninitialised value of size 8
==11833==    at 0x10A9E6: showIntersections (project2.c:830)
==11833==    by 0x109466: main (project2.c:224)
==11833== 
==11833== Invalid read of size 1
==11833==    at 0x4A6CFA0: __strcpy_sse2_unaligned (strcpy-sse2-unaligned.S:47)
==11833==    by 0x10AFAB: removeStop (project2.c:952)
==11833==    by 0x1094BA: main (project2.c:242)
==11833==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==11833== 
==11833== 
==11833== Process terminating with default action of signal 11 (SIGSEGV)
==11833==  Access not within mapped region at address 0x0
==11833==    at 0x4A6CFA0: __strcpy_sse2_unaligned (strcpy-sse2-unaligned.S:47)
==11833==    by 0x10AFAB: removeStop (project2.c:952)
==11833==    by 0x1094BA: main (project2.c:242)
==11833==  If you believe this happened as a result of a stack
==11833==  overflow in your program's main thread (unlikely but
==11833==  possible), you can try to increase the size of the
==11833==  main thread stack using the --main-stacksize= flag.
==11833==  The main thread stack size used in this run was 8388608.
==11833== 
==11833== HEAP SUMMARY:
==11833==     in use at exit: 787,984 bytes in 51 blocks
==11833==   total heap usage: 131 allocs, 80 frees, 805,344 bytes allocated
==11833== 
==11833== LEAK SUMMARY:
==11833==    definitely lost: 569 bytes in 29 blocks
==11833==    indirectly lost: 0 bytes in 0 blocks
==11833==      possibly lost: 0 bytes in 0 blocks
==11833==    still reachable: 787,415 bytes in 22 blocks
==11833==         suppressed: 0 bytes in 0 blocks
==11833== Rerun with --leak-check=full to see details of leaked memory
==11833== 
==11833== For counts of detected and suppressed errors, rerun with: -v
==11833== Use --track-origins=yes to see where uninitialised values come from
==11833== ERROR SUMMARY: 15 errors from 4 contexts (suppressed: 0 from 0)

```


Your code will not be reevaluated if you submit before 2023-04-14 19:20:14 @ Lisbon, Portugal. You need to wait 10 minute(s).

