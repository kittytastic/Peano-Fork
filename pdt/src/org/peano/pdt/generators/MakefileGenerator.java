package org.peano.pdt.generators;

import org.peano.framework.analysis.DepthFirstAdapter;

import de.tum.peano.pdt.node.ADescription;

public class MakefileGenerator extends DepthFirstAdapter {
  private org.peano.pdt.generators.DirectoryGenerator _directoryGenerator;
  private org.peano.pdt.TranslationTable              _translationTable;

  public MakefileGenerator(
    org.peano.pdt.generators.DirectoryGenerator directoryGenerator,
    org.peano.pdt.TranslationTable translationTable) {
    _directoryGenerator = directoryGenerator;
    _translationTable = translationTable;
  }

  
  public void inADescription(ADescription node) {
    _translationTable.convertTemplateFile( 
      "Makefile.template",
      "makefile",
      false
    );
  }
}
