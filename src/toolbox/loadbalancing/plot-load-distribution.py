# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org
import argparse
import os


import matplotlib.pyplot as plt


def get_ranks_and_threads( filename ):
  ranks = 1
  threads = 1
  file = open( filename, "r" )
  for line in file:
    if "build:" in line and "no mpi" in line: 
      print( "code does not use MPI" )
      ranks = 1
    if "build:" in line and "threads" in line: 
      threads = int( line.split( "threads" )[0].split( "(" )[-1])
      print( "code uses " + str(threads) + " threads per rank" )
    if "manually reset number of threads used to" in line: 
      threads = int( line.split( "to" )[1])
      print( "code sets number of threads manually to " + str(threads) )
    if "build:" in line and "ranks)" in line: 
      ranks = int( line.split( "ranks)" )[0].split("(")[1])
      print( "code uses " + str(ranks) + " ranks" )
      
  return (ranks, threads)


#
# @todo Wir sollten nach Ranks unterscheiden und fuer jeden Rank einmal plotten (mit anderer Farbe)
#
def parse_file( filename, rank ):
  """
    Returns tuple of (x_data,y_data_local,y_data_remote)
    
    x_data is a series of time stamps
    y_data is a series of corresponding entries. Each entry is an array again as there might be many trees


    filename File to parse (what a surprise)
    rank     Rank number of extract data for (can be -1 if you run serially)
    
  """
  file = open( filename, "r" )
  x_data        = []
  y_data_local  = []
  y_data_remote = []
  for line in file:
    is_in_line = "toolbox::loadbalancing::dumpStatistics" in line
    if rank>1:
      is_in_line = is_in_line and "rank:" + str(rank ) in line
      
    if is_in_line:
      x_data.append( float( line.strip().split(" ")[0] ) )
      y_data_local.append( [] )
      y_data_remote.append( [] )
      for entry in line.split( "(#")[1:-1]:
        y_data_local[-1].append( float(entry.split(":")[1].split("/")[0]) )
        y_data_remote[-1].append( float(entry.split("/")[1].split(")")[0]) )
  return ( x_data, y_data_local, y_data_remote )


def local_optimal_average( x_data, y_data_local, cores ):
  """
   
    When I split partitions, I typically get (temporary) subtrees with weight
    0. I have to be aware that the average thus can fall below 1.
    
  """
  pruned_x_data = []
  y_data = []
  for j in range(0,len(y_data_local)):
    y_data.append( 0.0 )
    for i in y_data_local[j]:
      y_data[-1] += i
    y_data[-1] /= cores
    if y_data[-1]>16:
      pruned_x_data.append( x_data[j] )
    else:
      y_data = y_data[0:-1]
  return (pruned_x_data,y_data)
   

if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='Peano 4 load balancing plotter')
  parser.add_argument("file",   help="filename of the file to parse (should be a text file)")
  parser.add_argument("-v", "--verbose", help="increase output verbosity", default=False)
  args = parser.parse_args()

  plt.clf()

  (ranks,threads) = get_ranks_and_threads( args.file )


  #
  # Should be one colour per rank
  #
  Colours = [ "#0000ff", "#00ff00", "#ff0000", "#00ffff", "#ff00ff", "#ffff00", "#aaaaaa" ]
  Symbols = [ "o",       "s",       "<",       ">",       "^",       "v",       "x"       ]

  Ranks   = range(0,ranks)
  if ranks<=1: 
    Ranks = [-1]
  
  symbol_counter = 0
  for rank in Ranks:
    ( x_data, y_data_local, y_data_remote ) = parse_file( args.file, rank )
    for i in range(0,len(x_data)):
      one_snapshot_x_data = [ x_data[i] for j in y_data_local[i]]
      if i==0 and rank>=0:
        plt.scatter(one_snapshot_x_data, y_data_local[i], marker=Symbols[symbol_counter], color=Colours[symbol_counter],  alpha=0.2, label="Rank " + str(rank) )  
      elif i==0:
        plt.scatter(one_snapshot_x_data, y_data_local[i], marker=Symbols[symbol_counter], color=Colours[symbol_counter],  alpha=0.2, label="Load per tree" )  
      else:
        plt.scatter(one_snapshot_x_data, y_data_local[i], marker=Symbols[symbol_counter], color=Colours[symbol_counter],  alpha=0.2)  
      plt.scatter(one_snapshot_x_data, y_data_remote[i], marker=Symbols[symbol_counter], color=Colours[symbol_counter], alpha=0.2, facecolors='none')
      
    if len(Ranks)==1:
      optimal_x_data = local_optimal_average(x_data,y_data_local,threads)[0]
      optimal_y_data = local_optimal_average(x_data,y_data_local,threads)[1]
      plt.plot(optimal_x_data, optimal_y_data, "-", color=Colours[symbol_counter] )
      optimal_y_data = [i/2 for i in optimal_y_data]
      plt.plot(optimal_x_data, optimal_y_data, "--", color=Colours[symbol_counter] )
      optimal_y_data = [i/2 for i in optimal_y_data]
      plt.plot(optimal_x_data, optimal_y_data, ":", color=Colours[symbol_counter] )
      
    symbol_counter += 1
    if symbol_counter>len(Colours):
      symbol_counter = 0


  plt.xlabel( "time" )
  plt.ylabel( "cells per tree" )
  plt.yscale( "log", basey=2 )
  #plt.yscale( "log" )
  plt.legend()
  plt.savefig( args.file + ".pdf" )
  plt.savefig( args.file + ".png" )
  
