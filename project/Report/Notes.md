# Project








# OLD - Project Prep
## Sources
Exhype: https://www.sciencedirect.com/science/article/pii/S001046552030076X?via%3Dihub
Exahype templating: https://arxiv.org/pdf/1911.06817.pdf

YATeTo: https://dl.acm.org/doi/pdf/10.1145/3406835
YATeTo GPU: https://dl.acm.org/doi/pdf/10.1145/3432261.3436753

Seisol small Tensor contractions: http://mediatum.ub.tum.de/doc/1461411/file.pdf
Seisol GB finalist: https://ieeexplore.ieee.org/document/7012188


Roofline Model: https://www.osti.gov/servlets/purl/1407078/
GEMM-like T T: https://dl.acm.org/doi/pdf/10.1145/3157733

Tensors for FV: https://www.ams.org/journals/mcom/2012-81-280/S0025-5718-2012-02574-9/S0025-5718-2012-02574-9.pdf


Tensor Contraction Engine, comp chem: https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=1386652 
COFFEE: https://dl.acm.org/doi/10.1145/2687415
Cyclops: https://ieeexplore.ieee.org/document/6569864
Tensors using BLAS (NVIDA): https://arxiv.org/pdf/1606.05696.pdf

## Other
SIMD in DG methods: https://dl.acm.org/doi/pdf/10.1145/3424144
Tensors using BLIS: https://arxiv.org/pdf/1607.00291.pdf
matrix free DG: https://arxiv.org/pdf/1711.10885.pdf
InTensLi: https://dl.acm.org/doi/pdf/10.1145/2807591.2807671

interesting other: https://dl.acm.org/doi/pdf/10.1145/3295500.3357157
quantum tunneling: https://dl.acm.org/doi/pdf/10.1145/3295500.3357156

PDE texbook, is it good?: http://www.math.toronto.edu/ivrii/PDE-textbook/PDE-textbook.pdf

recap on 100yr galerkin: https://www.degruyter.com/document/doi/10.1515/cmam-2017-0013/html

PDE a-z: http://www.scholarpedia.org/article/Partial_differential_equation#:~:text=A%20partial%20differential%20equation%20(or,respect%20to%20the%20independent%20variables.

# Feedback - TODO
## Intro
Generic beginning - Mention per core efficiency, lots of preformance from increase per core capabilities

Exahype - abstraction, performance, nothing can use domain specific knowledge <-- not tooling

problem statement, compiler good at long simple compilers, compilers good at simple loops,


intro - specific research question, something doesnt work: can me keep user friendly and aggressive 

## Problem statement
bin Hpde

formula is first order - not general

formula embedded in text, no colons

Euler has 2+d unknowns

CCz4 59 - olinda 

example of FD formula

Dont write equation 1, (1), only equation when you start sentance with

Equations 1-5, dont enuerate all equation, only named

First problem statement, remove we thens!
Equation 5, put a full stop at the end
6 face cube, 4 face .

Is a majority of engine code.

Functional programming patten.
??? 11:25


## Related Work
python templating, not c++ templating
numbers less than 12 as words
we belive - bin
challenge term optimisation expert, compiler is the expert, need a transform expert, adds seperation of concern

(13:40)
YATeTo likes this seperation of code
It is not clear if compiler or BLAS is better <--- add need to investigate
YATeTo only works with linear systems
Not clear if rebuilding

(15:40)
General, why you study these things, 
in which way have these things effected decisions

Could look at stencil compilers.

## Solution
move data
DAG, what is done, SymPy doesnt exist
move D forward

## Results
Normalization again base line is weird

## Evaluation section
Add discussion about results

(19:12)
???

What doesnt work,
open question, to which degree challenges approach
(21:00)
remove redundant comp -- register presure

DAGs could have side effects, mby look at latest ISC poster

Not clear if it would work in GPUs
Not clear if compilers require for loops, mby compilers like for loops

## Conclusion
(23:30)
This is the Q we wanted to answer in into - this is how we answered it
