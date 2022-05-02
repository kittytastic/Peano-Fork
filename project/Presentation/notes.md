# Backgroud
- High performance computing

- In particular, PDEs

- Cant solve analytically, so solve them numericaly
Focus on the finite volume method, which I will explain more about in a bit

- Numerical methods are computationally intense -> super computers -> ExaHype

- Exahype is an engine for solving PDEs
- Users describe thier problems
- Exahype makes a pro that can run on laptops to Exa Scale super computers

- Focus on making exahype faster, In particular we will be working on the single core preformance of exahpye

# Problems
- Finite volumes cut the spacial domain into small cells, 
you store the state of every cell
e.g. shallow water equation state is momentum x, momentum y, height of the water.

- Each cell is subject to diffrent influences, It can be on the boundry, source term, ncp, or flux.
flux describes flow

- how a cell changes depends on what flows into and out of it
- sum over cell faces - thats a single cell update

- In Exahype Cells are grouped into patches, usually 3x3 or 3x3x3 
patches are disributed around the compute ndoes and compute cores
all the cells are updated in a patch, which I will call patch update
done on single core
focus on the performance of this process

Why focus here
Lies on the boundry of user and engine code
engine doesnt know about user code,
see preformance issues like duplicated computation, and heap allocation

come from static code gen
what if we use dynamic codegeneration instead


# Related
Boudry has been explored before using templating

Code gen techniques have been used before
Yateto

other

not an exhausive list

# FLAT
compiles input DAGs (Directed Acyclic graphs) into C++
In particualr the c++ it generates in Flat Long and potentially Transfromed, in the region of 1000s to 10,000 of lines long 
 (architecture)

 Flat uses a fairly conventially architecture, as YAteto uses
 *talk through architecture*

 Input domain
 list
 *talk about*

 DAG

 IR

 Compiling a kernel
*quick demo*


 # Results
 *test problems*

 Test in Exahype
 Issue with test problems is memory bound
 So also synthetic test by thrashing kernels
These results were a bit noisy, +/- 10 % - I can explain if youre intresnted

 *kernel compare results*
 *exahype results*

 Why do we get these results?
hand optimised kernel, no heap allocation
*table*

2.31x faster, why is that?

*compiler flags table*
*MAQAO reults*


# Eval/Conclusion
Project went well, created a full working compiler and it worked suprisingly well
It want easy to use
But it did keep its modularity

Big unanswered question is how does it work for big problems?
- would need to add a front end, results validate that

is FLAT the right way to go, maybe some loops would be benificial

how does it compare with other approaches, e.g. YATeTo


# Script
# Background
- Field of HPC
- In particual solving PDEs, of which HPDE
- Cant solve analytically


- The issue here, if I want to solve an EQ got to write an entier program 
- Exahype deals with the orchestraction, solving, 

# FV

- this patch update process is where we look for improvemtn

# Solution

- How it fits into ExaHyPE