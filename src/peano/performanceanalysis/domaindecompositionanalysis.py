#!/usr/bin/env python
import argparse
from argparse import RawTextHelpFormatter


import performanceanalysis_parser
import performanceanalysis_output
import performanceanalysis_global_plotter
import performanceanalysis_analysis
import performanceanalysis_dd


import gc
import re
import os


########################################################################
# START OF THE PROGRAM
########################################################################
help = '''
Creates a brief overview of the domain decomposition
\n\n
Sample usages:\n
python domain-decomposition-analysis.py -file 112x16-0.results -dimension 2 -domainoffset 0.0 0.0 -domainsize 15.0 15.0\n
'''

parser = argparse.ArgumentParser(description=help,formatter_class=RawTextHelpFormatter)
parser.add_argument('-file',required=True,help="Input file")
parser.add_argument('-domainoffset',nargs="+",required=True,help="Offset of bounding box.")
parser.add_argument('-domainsize',nargs="+",required=True,help="Size of domain's bounding box.")
args   = parser.parse_args();

scriptLocation = os.path.realpath(__file__)[:os.path.realpath(__file__).rfind("/")]

performanceanalysis_output.createOutputDirectory(args.file);

outFile         = performanceanalysis_output.getOutputFile(args.file)

numberOfRanks   = performanceanalysis_parser.getNumberOfRanks(args.file)
numberOfThreads = performanceanalysis_parser.getNumberOfThreads(args.file)
dim             = performanceanalysis_parser.getDimensions(args.file)

if len(args.domainoffset)!=dim:
  print "dimensions of offset does not match dimensions. If input file is for dimension 2, then we need two offset values separated by a space"
  exit(-1)

if len(args.domainsize)!=dim:
  print "dimensions of domain size does not match dimensions. If input file is for dimension 2, then we need two size values separated by a space"
  exit(-1)

performanceanalysis_output.writeHeader(outFile,args.file,numberOfRanks,numberOfThreads);

(parents,levels,offset,volume,nodes) = performanceanalysis_parser.getLogicalTopology(numberOfRanks,dim,args.file,".");
(volumes,overlaps,work)              = performanceanalysis_analysis.computeVolumesOverlapsWork(numberOfRanks,parents,offset,volume,dim,args.domainoffset,args.domainsize)

maxWork         = max(work)
rankWithMaxWork = work.index(maxWork)
minWork         = min(w for w in work if w > 0)
rankWithMinWork = work.index(minWork)

idleRanks = [p for p in parents if p < 0]

loadImbalance = maxWork/minWork

print "idle ranks = %i" % (len(idleRanks))
print "rank with maximum work (geometric), maximum work (geometric) = %i, %f" % (rankWithMaxWork, maxWork)
print "rank with minimum work (geometric), minimum work (geometric) = %i, %f" % (rankWithMinWork, minWork)
print "(geometric) load imbalance = %f" % loadImbalance

tree = performanceanalysis_analysis.buildTree(parents,offset,volume,levels)
performanceanalysis_global_plotter.plotHeatMap(performanceanalysis_output.getOutputDirectory(args.file)+"/heatmap",tree,max(levels)-1,work,dim)

performanceanalysis_global_plotter.plotLogicalTopology(numberOfRanks,performanceanalysis_output.getOutputDirectory(args.file)+"/topology",parents,levels,offset,volume);

performanceanalysis_global_plotter.plotWorkloadAndResponsibilityDistributionPerRank(numberOfRanks,performanceanalysis_output.getOutputDirectory(args.file)+"/workload-per-rank",volumes,overlaps,work);
performanceanalysis_global_plotter.plotWorkloadAndResponsibilityDistributionPerNode(numberOfRanks,performanceanalysis_output.getOutputDirectory(args.file)+"/workload-per-node",work,nodes);

memoryUsages = performanceanalysis_parser.getMemoryUsagePerRank(args.file,numberOfRanks)

performanceanalysis_global_plotter.plotMemoryUsagePerRank(performanceanalysis_output.getOutputDirectory(args.file)+"/memory-per-rank",memoryUsages);

for l in range(1,max(levels)+1):
 if dim==2:
  performanceanalysis_dd.plot2dDomainDecompositionOnLevel(l,numberOfRanks,args.domainoffset,args.domainsize,offset,volume,levels,nodes,performanceanalysis_output.getOutputDirectory(args.file)+"/dd")
 if dim==3:
  performanceanalysis_dd.plot3dDomainDecompositionOnLevel(l,numberOfRanks,args.domainoffset,args.domainsize,offset,volume,levels,nodes,performanceanalysis_output.getOutputDirectory(args.file)+"/dd")

if dim==2:
  performanceanalysis_dd.plot2dDomainDecomposition(numberOfRanks,args.domainoffset,args.domainsize,offset,volume,levels,nodes,performanceanalysis_output.getOutputDirectory(args.file)+"/dd")
#if dim==3:
#  performanceanalysis_dd.plot3dDomainDecomposition(numberOfRanks,args.domainoffset,args.domainsize,offset,volume,levels,nodes,performanceanalysis_output.getOutputDirectory(args.file)+"/dd")


performanceanalysis_dd.printNodeTable(outFile,numberOfRanks,parents,nodes)

params = {"_IMAGE_DIRECTORY_" : performanceanalysis_output.getOutputDirectory(args.file)}

outputDir = performanceanalysis_output.getOutputDirectory(args.file)
value = ""
for l in range(2,max(levels)+1):
  value += "\n<a href=\"%s/heatmap-level-%i.pdf\"><img src=\"%s/heatmap-level-%i.png\" /></a>" % (outputDir,l,outputDir,l)
params["_HEAT_MAPS_PER_LEVEL_"] = value

performanceanalysis_output.processTemplateFile(
 scriptLocation + "/domaindecompositionanalysis.template",outFile, params
)

performanceanalysis_output.writeTrailer(outFile)

