package org.peano.pdt.generators;

import org.peano.framework.analysis.DepthFirstAdapter;

import de.tum.peano.pdt.node.ADescription;
import de.tum.peano.pdt.node.Start;

public class RepositoryGenerator extends DepthFirstAdapter {
  private org.peano.pdt.generators.DirectoryGenerator _directoryGenerator;
  private org.peano.pdt.TranslationTable              _translationTable;

  public RepositoryGenerator(
    org.peano.pdt.generators.DirectoryGenerator directoryGenerator,
    org.peano.pdt.TranslationTable              translationTable
  ) {
    _directoryGenerator  = directoryGenerator;
    _translationTable    = translationTable;
  }

  public void inADescription(ADescription node) {
    _translationTable.convertTemplateFile( 
      "RepositoryFactoryHeader.template",
      "RepositoryFactory.h",
      true
    );
    _translationTable.convertTemplateFile( 
      "RepositoryFactoryImplementation.template",
      "RepositoryFactory.cpp",
      true
    );

    _translationTable.convertTemplateFile( 
      "RepositoryHeader.template",
      "Repository.h",
      true
    );

    _translationTable.convertTemplateFile( 
      "RepositoryArrayStackHeader.template",
      "RepositoryArrayStack.h",
      true
    );
    _translationTable.convertTemplateFile( 
      "RepositoryArrayStackImplementation.template",
      "RepositoryArrayStack.cpp",
      true
    );

    _translationTable.convertTemplateFile( 
      "RepositorySTDStackHeader.template",
      "RepositorySTDStack.h",
      true
    );
    _translationTable.convertTemplateFile( 
      "RepositorySTDStackImplementation.template",
      "RepositorySTDStack.cpp",
      true
    );
  }
}
