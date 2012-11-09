package de.tum.peano.pdt.generators;

import de.tum.peano.pdt.TranslationTable;
import de.tum.peano.pdt.analysis.DepthFirstAdapter;
import de.tum.peano.pdt.node.*;


public class DaStGenGenerator extends DepthFirstAdapter {
  private de.tum.peano.pdt.generators.DirectoryGenerator _directoryGenerator;
  private de.tum.peano.pdt.TranslationTable              _translationTable;

  public DaStGenGenerator(
    de.tum.peano.pdt.generators.DirectoryGenerator directoryGenerator,
    de.tum.peano.pdt.TranslationTable              translationTable
  ) {
    _directoryGenerator = directoryGenerator;
    _translationTable   = translationTable;
  }
  

  public void inADescription(ADescription node) {
    String fileName                    = _directoryGenerator.getDaStGenDirectory()  
                                       + "/" 
                                       + TranslationTable.getRepositoryStateUnqualifiedName() 
                                       + ".def";
    String repositoryStateTemplateName = "DaStGenRepositoryState.template";

    _translationTable.convertTemplateFile(
      repositoryStateTemplateName,
      fileName, 
      true
    );
  }

  
  public void inAVertex(AVertex node) {
    String vertexFileName     = _directoryGenerator.getDaStGenDirectory()
                              + "/"
                              + TranslationTable.getVertexUnqualifiedName() 
                              + ".def";
    String vertexTemplateName = "DaStGenVertex.template";

    _translationTable.convertTemplateFile(
       vertexTemplateName,
       vertexFileName, 
       true
     );
  }

  
  public void inACell(ACell node) {
    String cellFileName     = _directoryGenerator.getDaStGenDirectory()
                            + "/"
                            + TranslationTable.getCellUnqualifiedName() 
                            + ".def";
    String cellTemplateName = "DaStGenCell.template";

    _translationTable.convertTemplateFile(
      cellTemplateName,
      cellFileName, 
      true
    );
  }


  public void inAState(AState node) {
    String stateFileName     = _directoryGenerator.getDaStGenDirectory()
                             + "/"
                             + TranslationTable.getStateUnqualifiedName() 
                             + ".def";
    String stateTemplateName = "DaStGenState.template";

    _translationTable.convertTemplateFile(
      stateTemplateName,
      stateFileName, 
      true
    );
  }     
}
