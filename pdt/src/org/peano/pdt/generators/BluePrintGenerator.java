package org.peano.pdt.generators;

import org.peano.framework.analysis.DepthFirstAdapter;

import de.tum.peano.pdt.node.*;

public class BluePrintGenerator extends DepthFirstAdapter {
  private org.peano.pdt.generators.DirectoryGenerator _directoryGenerator;
  private org.peano.pdt.TranslationTable              _translationTable;

  public BluePrintGenerator(
    org.peano.pdt.generators.DirectoryGenerator directoryGenerator,
    org.peano.pdt.TranslationTable              translationTable
  ) {
    _directoryGenerator   = directoryGenerator;
    _translationTable     = translationTable;
  }


  public void inADescription(ADescription node) {
  }

  
  public void inAVertex(AVertex node) {
    final String headerTemplate         = "VertexHeader.template";
    final String implementationTemplate = "VertexImplementation.template";
    
    final String headerFileName         = _directoryGenerator.getProjectDirectoryAbsolute() + "/Vertex.h";
    final String implementationFileName = _directoryGenerator.getProjectDirectoryAbsolute() + "/Vertex.cpp";

    _translationTable.convertTemplateFile( headerTemplate,         headerFileName,         false);
    _translationTable.convertTemplateFile( implementationTemplate, implementationFileName, false);
	}
  

  public void inACell(ACell node) {
    final String headerTemplate         = "CellHeader.template";
    final String implementationTemplate = "CellImplementation.template";
    
    final String headerFileName         = _directoryGenerator.getProjectDirectoryAbsolute() + "/Cell.h";
    final String implementationFileName = _directoryGenerator.getProjectDirectoryAbsolute() + "/Cell.cpp";

    _translationTable.convertTemplateFile( headerTemplate,         headerFileName,         false);
    _translationTable.convertTemplateFile( implementationTemplate, implementationFileName, false);
  }


  public void inAState(AState node) {
    final String headerTemplate         = "StateHeader.template";
    final String implementationTemplate = "StateImplementation.template";
    
    final String headerFileName         = _directoryGenerator.getProjectDirectoryAbsolute() + "/State.h";
    final String implementationFileName = _directoryGenerator.getProjectDirectoryAbsolute() + "/State.cpp";

    _translationTable.convertTemplateFile( headerTemplate,         headerFileName,         false);
    _translationTable.convertTemplateFile( implementationTemplate, implementationFileName, false);
  }

  
  public void inAEventMapping(AEventMapping node) {
    final String headerTemplate         = "MappingHeader.template";
    final String implementationTemplate = "MappingImplementation.template";
    
    final String headerFileName         = _directoryGenerator.getMappingsDirectory() + "/" + node.getName().getText().trim() + ".h";
    final String implementationFileName = _directoryGenerator.getMappingsDirectory() + "/" + node.getName().getText().trim() + ".cpp";

    _translationTable.convertTemplateFile( headerTemplate,         headerFileName,         false);
    _translationTable.convertTemplateFile( implementationTemplate, implementationFileName, false);
  }
}
