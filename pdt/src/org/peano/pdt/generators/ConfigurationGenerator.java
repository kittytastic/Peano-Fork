package org.peano.pdt.generators;

import org.peano.framework.analysis.DepthFirstAdapter;

import de.tum.peano.pdt.node.*;

public class ConfigurationGenerator extends DepthFirstAdapter {
  private org.peano.pdt.generators.DirectoryGenerator _directoryGenerator;
  private org.peano.pdt.TranslationTable              _translationTable;

  public ConfigurationGenerator(
    org.peano.pdt.generators.DirectoryGenerator  directoryGenerator,
    org.peano.pdt.TranslationTable               translationTable
  ) {
    _directoryGenerator   = directoryGenerator;
    _translationTable     = translationTable;
  }

  
  public void inADescription(ADescription node) {
    _translationTable.convertTemplateFile( 
      "Configuration.template",
      "run" + node.getName().getText().trim() + ".xml",
      false
    );

    _translationTable.convertTemplateFile( 
      "ConfigurationHeader.template",
      _directoryGenerator.getConfigurationsDirectory() + "/Configuration.h",
      false
    );
    _translationTable.convertTemplateFile( 
      "ConfigurationImplementation.template",
      _directoryGenerator.getConfigurationsDirectory() + "/Configuration.cpp",
      false
    );
  }
}
