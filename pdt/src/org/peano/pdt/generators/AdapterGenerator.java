package org.peano.pdt.generators;

import org.peano.framework.analysis.DepthFirstAdapter;

import de.tum.peano.pdt.node.*;


public class AdapterGenerator extends DepthFirstAdapter {
  private org.peano.pdt.generators.DirectoryGenerator _directoryGenerator;
  private org.peano.pdt.TranslationTable              _translationTable;


  public AdapterGenerator(
    org.peano.pdt.generators.DirectoryGenerator directoryGenerator,
    org.peano.pdt.TranslationTable              translationTable
  ) {
    _directoryGenerator = directoryGenerator;
    _translationTable   = translationTable;
  }

    
  public void inAAdapter(AAdapter node) {
    java.util.Vector<String> mappings = new java.util.Vector<String>();
    for (int i=0; i<node.getUserDefined().size(); i++) {
      mappings.add( node.getUserDefined().get(i).getText().trim() );
    }

    if (node.getPredefinedDefined().size()>0) {
      System.err.println( "predefined adapters not supported yet" );
    }

    String mappingTypeName   = node.getName().getText().trim();
    _translationTable.setThisTypenameToAdapterTypename( mappingTypeName, mappings );

    _translationTable.convertTemplateFile( 
      "AdapterHeader.template",
      _directoryGenerator.getAdaptersDirectory() + "/" + mappingTypeName + ".h",
      true
    );
    _translationTable.convertTemplateFile( 
      "AdapterImplementation.template",
      _directoryGenerator.getAdaptersDirectory() + "/" + mappingTypeName + ".h",
      true
    );
  }
}
