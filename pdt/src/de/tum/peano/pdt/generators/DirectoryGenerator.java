// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org.
package de.tum.peano.pdt.generators;

import java.io.File;

import de.tum.peano.pdt.analysis.DepthFirstAdapter;
import de.tum.peano.pdt.node.Start;

public class DirectoryGenerator extends DepthFirstAdapter {
  private File   _outputDirectory;

  public DirectoryGenerator(File outputDirectory) {
    _outputDirectory = outputDirectory;
  }
  
//  static public String replaceColonsByFileSeparator( String originalString ) {
//    String fileSeparator   = File.separator;
//    if (fileSeparator.length()==1 && fileSeparator.charAt(0)=='\\') fileSeparator = "\\\\";
//    return originalString.replaceAll("::", fileSeparator);
//  }
  
  public void outStart(Start node) {
    java.io.File dirRecords = new java.io.File( getRecordsDirectory() );
    if (dirRecords.mkdirs()) {
      System.out.print(dirRecords.getAbsolutePath() + " ");
    }

    java.io.File dirAdapter = new java.io.File( getMappingsDirectory() );
    if (dirAdapter.mkdirs()) {
      System.out.print(dirAdapter.getAbsolutePath() + " ");
    }
    
    java.io.File dirRepository = new java.io.File( getRepositoriesDirectory() );
    if (dirRepository.mkdirs()) {
      System.out.print(dirRepository.getAbsolutePath() + " ");
    }
    
    java.io.File dirGlueAdapter = new java.io.File( getAdaptersDirectory() );
    if (dirGlueAdapter.mkdirs()) {
      System.out.print(dirGlueAdapter.getAbsolutePath() + " ");
    }
    
    java.io.File dirRunner = new java.io.File( getRunnersDirectory() );
    if (dirRunner.mkdirs()) {
      System.out.print(dirRunner.getAbsolutePath() + " ");
    }
    
    java.io.File dirConfiguration = new java.io.File( getConfigurationsDirectory() );
    if (dirConfiguration.mkdirs()) {
      System.out.print(dirConfiguration.getAbsolutePath() + " ");
    }
    
    java.io.File dirTests = new java.io.File( getTestsDirectory() );
    if (dirTests.mkdirs()) {
      System.out.print(dirTests.getAbsolutePath() + " ");
    }
    
    java.io.File dastgenTests = new java.io.File( getDaStGenDirectory() );
    if (dastgenTests.mkdirs()) {
      System.out.print(dastgenTests.getAbsolutePath() + " ");
    }
  }
  
  public String getProjectDirectoryAbsolute() {
    return _outputDirectory.getAbsolutePath();
  }
  
  public String getRecordsDirectoryRelativeToComponentDirectory() {
    return "records";
  }
  
  public String getRecordsDirectory() {
    return getProjectDirectoryAbsolute() + File.separator + getRecordsDirectoryRelativeToComponentDirectory();
  }
  
  public String getMappingsDirectoryRelativeToComponentDirectory() {
    return "mappings";
  }

  public String getMappingsDirectory() {
    return getProjectDirectoryAbsolute() + File.separator + getMappingsDirectoryRelativeToComponentDirectory();
  }
  
  public String getRepositoriesDirectoryRelativeToComponentDirectory() {
    return "repositories";
  }

  public String getRepositoriesDirectory() {
    return getProjectDirectoryAbsolute() + File.separator + getRepositoriesDirectoryRelativeToComponentDirectory();
  }

  public String getCCADirectoryRelativeToComponentDirectory() {
    return "cca";
  }

  public String getAdaptersDirectoryRelativeToComponentDirectory() {
    return "adapters";
  }

  public String getAdaptersDirectory() {
    return getProjectDirectoryAbsolute() + File.separator + getAdaptersDirectoryRelativeToComponentDirectory();
  }

  public String getRunnersDirectoryRelativeToComponentDirectory() {
    return "runners";
  }

  public String getRunnersDirectory() {
    return getProjectDirectoryAbsolute() + File.separator + getRunnersDirectoryRelativeToComponentDirectory();
  }

  public String getConfigurationsDirectoryRelativeToComponentDirectory() {
    return "configurations";
  }

  public String getConfigurationsDirectory() {
    return getProjectDirectoryAbsolute() + File.separator + getConfigurationsDirectoryRelativeToComponentDirectory();
  }
  
  public String getTestsDirectoryRelativeToComponentDirectory() {
    return "tests";
  }

  public String getTestsDirectory() {
    return getProjectDirectoryAbsolute() + File.separator + getTestsDirectoryRelativeToComponentDirectory();
  }

  public String getDaStGenDirectoryRelativeToComponentDirectory() {
    return "dastgen";
  }

  public String getDaStGenDirectory() {
    return getProjectDirectoryAbsolute() + File.separator + getDaStGenDirectoryRelativeToComponentDirectory();
  }
}
