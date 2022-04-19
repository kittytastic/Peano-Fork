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
(0:00)
[x] Fix generic beginning - mention per core efficiency and how lots of recent gains have been from that 
[x] Change wording - Exahype abstraction causes problems, can't use domain specific knowledge, there is nothing wrong with tooling.

(2:37)
[x] Refine compiler part - waffling
[-] Refine compiler part - what are compiler good at compiler good at long simple compilers, compilers good at simple loops
[x] Make clear - not writing a compiler, writing something that passes code to the compiler

(3:50)
[x] Add research question - Can code be user friendly and make aggressive optimisations 


## Problem statement
(4:36)
[x] Remove term - HPDE
[x] Fix wording - formula isn't general, it is first oder
[x] Fix formatting - formulas should be embedded into text, full stops and comma at tend of formula, no colons prefacing them 
(6:07)
[-] Clarify - Euler has 2+d unknowns
(6:22)
[x] Refine CCZ4 - 58 unknowns, ref FO-CCZ4 paper
[x] Fix wording - FD derivation isn't a simplification, its a special case its with B as 0
[x] Fix formatting - Refer to equation 1 as (1), don't use the word equation unless starting a sentence.
[x] Fix formatting - Only enumerate equations that you then refer to
[x] Fix missing word - we then
[x] Fix wording - change all the "We thens" in derivation.
(9:25)
[x] Fix formatting - Equation 5, put full stop at the end
[x] Consistency - 6 face 3D, 4 face 2D 

[x] Clarify - "Is a majority of engine code"
[x] Update wording - ExaHyPE uses a functional programming paradigm
(10:42)
[x] Rewrite - Exahype part

## Related Work
[x] Clarify - python templating, not c++ templating
[x] Fix formatting - Use words for numbers less than 12
(12:07)
[x] Fix tone - Remove we believe
[x] Elaborate - Challenge the term optimisation expert as compiler is the expert. Replace them with a transform expert which adds separation of concern

(13:16)
[x] Follow on - YATeTo uses this separation of concern
[x] Elaborate - It is not clear if a compiler or BLAS is better, that needs to be investigated
[x] Clarify - YATeTo only works with linear systems
[x] Elaborate - Not clear if rebuilding matrices at every time step for non-linear would be worth it

(15:40)
???
[x] Add a summary section - Why you study these things? In which way have these things effected decisions?

[ ] Potentially - look at stencil compilers, PLUTO is interesting

## Solution
(17:00)
[x] Refine - only talk about what is done, don't mention SymPy e.t.c.
[x] Refine - Move Architecture overview forward, Context then Depth

## Results
[ ] Look at - Normalization against handopt is weird

## Evaluation section
[] Add  - Evaluation section that discusses results

(19:12)
???

[ ] Mention - What doesnt work
[ ] Mention - Didnt add a front end
[ ] Mention - open question, to which degree challenges approach, are big DAGs bad
(21:00)
[ ] Mention - remove redundant comp -- register presure
[ ] Mention - DAGs could have side effects, mby look at latest ISC poster
[ ] Mention - Not clear if it would work in GPUs
[ ] Mention - Not clear if compilers require for loops, mby compilers like for loops

## Conclusion
(23:30)
[ ] Refine - This is the Q we wanted to answer in into, this is how we answered it
[ ] Add - investigate compilers vs BLAS (14:00)
