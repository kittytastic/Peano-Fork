package de.tum.peano.pdt;


import java.io.FileNotFoundException;

import de.tum.peano.pdt.analysis.DepthFirstAdapter;
import de.tum.peano.pdt.node.*;


public class TranslationTable extends DepthFirstAdapter {

  private static final String MULTIPLE_REPLACEMENT_LINE_PREFIX = "__x";
  private static final String MULTIPLE_REPLACEMENT_LINE_PREFIX_WITH_COMMA = "__xc";

  private static final String _KEYWORD_COMPONENT_NAME       = "__COMPONENT_NAME__";

  private static final String _KEYWORD_INCLUDE_GUARD_PREFIX = "__INCLUDE_GUARD_PREFIX__";

  private static final String _KEYWORD_DOF_DASTGEN_DEFINITION_CELL = "__DOF_DASTGEN_DEFINITION_CELL__";
  private static final String _KEYWORD_DOF_DASTGEN_DEFINITION_STATE = "__DOF_DASTGEN_DEFINITION_STATE__";
  private static final String _KEYWORD_DOF_DASTGEN_DEFINITION_VERTEX = "__DOF_DASTGEN_DEFINITION_VERTEX__";
  
//  private static final String _KEYWORD_FULL_QUALIFIED_TYPE_NAME_OF_CELL       = "__FULL_QUALIFIED_TYPE_NAME_OF_CELL__";
//  private static final String _KEYWORD_FULL_QUALIFIED_TYPE_NAME_OF_STATE      = "__FULL_QUALIFIED_TYPE_NAME_OF_STATE__";
//  private static final String _KEYWORD_FULL_QUALIFIED_TYPE_NAME_OF_VERTEX     = "__FULL_QUALIFIED_TYPE_NAME_OF_VERTEX__";
//  private static final String _KEYWORD_FULL_QUALIFIED_TYPE_NAME_OF_REPOSITORY = "__FULL_QUALIFIED_TYPE_NAME_OF_REPOSITORY__";
//
//  private static final String _KEYWORD_UNQUALIFIED_TYPE_NAME_OF_CELL       = "__UNQUALIFIED_TYPE_NAME_OF_CELL__";
//  private static final String _KEYWORD_UNQUALIFIED_TYPE_NAME_OF_STATE      = "__UNQUALIFIED_TYPE_NAME_OF_STATE__";
//  private static final String _KEYWORD_UNQUALIFIED_TYPE_NAME_OF_VERTEX     = "__UNQUALIFIED_TYPE_NAME_OF_VERTEX__";
//  private static final String _KEYWORD_UNQUALIFIED_TYPE_NAME_OF_REPOSITORY = "__UNQUALIFIED_TYPE_NAME_OF_REPOSITORY__";
//
//  private static final String _KEYWORD_PATH_OF_CELL       = "__PATH_OF_CELL__";
//  private static final String _KEYWORD_PATH_OF_STATE      = "__PATH_OF_STATE__";
//  private static final String _KEYWORD_PATH_OF_VERTEX     = "__PATH_OF_VERTEX__";
//  private static final String _KEYWORD_PATH_OF_REPOSITORY = "__PATH_OF_REPOSITORY__";
//
//  private static final String _KEYWORD_FULL_QUALIFIED_TYPE_NAME_OF_DASTGEN_CELL   = "__FULL_QUALIFIED_TYPE_NAME_OF_DASTGEN_CELL__";
//  private static final String _KEYWORD_FULL_QUALIFIED_TYPE_NAME_OF_DASTGEN_STATE  = "__FULL_QUALIFIED_TYPE_NAME_OF_DASTGEN_STATE__";
//  private static final String _KEYWORD_FULL_QUALIFIED_TYPE_NAME_OF_DASTGEN_VERTEX = "__FULL_QUALIFIED_TYPE_NAME_OF_DASTGEN_VERTEX__";
//
//  private static final String _KEYWORD_UNQUALIFIED_TYPE_NAME_OF_DASTGEN_CELL   = "__UNQUALIFIED_TYPE_NAME_OF_DASTGEN_CELL__";
//  private static final String _KEYWORD_UNQUALIFIED_TYPE_NAME_OF_DASTGEN_STATE  = "__UNQUALIFIED_TYPE_NAME_OF_DASTGEN_STATE__";
//  private static final String _KEYWORD_UNQUALIFIED_TYPE_NAME_OF_DASTGEN_VERTEX = "__UNQUALIFIED_TYPE_NAME_OF_DASTGEN_VERTEX__";
//
//  private static final String _KEYWORD_PATH_OF_DASTGEN_CELL   = "__PATH_OF_DASTGEN_CELL__";
//  private static final String _KEYWORD_PATH_OF_DASTGEN_STATE  = "__PATH_OF_DASTGEN_STATE__";
//  private static final String _KEYWORD_PATH_OF_DASTGEN_VERTEX = "__PATH_OF_DASTGEN_VERTEX__";
//
//  private static final String _KEYWORD_FULL_QUALIFIED_TYPE_NAME_OF_TEST          = "__FULL_QUALIFIED_TYPE_NAME_OF_TEST__";
//  private static final String _KEYWORD_FULL_QUALIFIED_TYPE_NAME_OF_RUNNER        = "__FULL_QUALIFIED_TYPE_NAME_OF_RUNNER__";
//  private static final String _KEYWORD_FULL_QUALIFIED_TYPE_NAME_OF_CONFIGURATION = "__FULL_QUALIFIED_TYPE_NAME_OF_CONFIGURATION__";
//
//  private static final String _KEYWORD_UNQUALIFIED_TYPE_NAME_OF_TEST          = "__UNQUALIFIED_TYPE_NAME_OF_TEST__";
//  private static final String _KEYWORD_UNQUALIFIED_TYPE_NAME_OF_RUNNER        = "__UNQUALIFIED_TYPE_NAME_OF_RUNNER__";
//  private static final String _KEYWORD_UNQUALIFIED_TYPE_NAME_OF_CONFIGURATION = "__UNQUALIFIED_TYPE_NAME_OF_CONFIGURATION__";
//
//  private static final String _KEYWORD_PATH_OF_TEST          = "__PATH_OF_TEST__";
//  private static final String _KEYWORD_PATH_OF_RUNNER        = "__PATH_OF_RUNNER__";
//  private static final String _KEYWORD_PATH_OF_ADAPTER       = "__PATH_OF_ADAPTER__";
//  private static final String _KEYWORD_PATH_OF_MAPPINGS      = "__PATH_OF_MAPPINGS__";
//  private static final String _KEYWORD_PATH_OF_CONFIGURATION = "__PATH_OF_CONFIGURATION__";

  private static final String _KEYWORD_NAMESPACE       = "__NAMESPACE__";
  private static final String _KEYWORD_OPEN_NAMESPACE  = "__OPEN_NAMESPACE__";
  private static final String _KEYWORD_CLOSE_NAMESPACE = "__CLOSE_NAMESPACE__";

  private static final String _KEYWORD_REPOSITORY_ACTION_ENUM = "__REPOSITORY_ACTION_ENUM__";

  private static final String _MULTIPLE_LINE_KEYWORD_FULL_QUALIFIED_ADAPTER_TYPE = "__FULL_QUALIFIED_ADAPTER_TYPE__";
  private static final String _MULTIPLE_LINE_KEYWORD_NONQUALIFIED_ADAPTER_TYPE = "__NONQUALIFIED_ADAPTER_TYPE__";

  private static final String _MULTIPLE_LINE_KEYWORD_READ_SCALAR_OPERATION = "__READ_SCALAR_OPERATION__";
  private static final String _MULTIPLE_LINE_KEYWORD_READ_VECTOR_OPERATION = "__READ_VECTOR_OPERATION__";
  private static final String _MULTIPLE_LINE_KEYWORD_READ_VECTOR_TWO_POW_D_OPERATION = "__READ_VECTOR_TWO_POW_D_OPERATION__";
  private static final String _MULTIPLE_LINE_KEYWORD_READ_STENCIL_OPERATION = "__READ_STENCIL_OPERATION__";
  private static final String _MULTIPLE_LINE_KEYWORD_WRITE_SCALAR_OPERATION = "__WRITE_SCALAR_OPERATION__";
  private static final String _MULTIPLE_LINE_KEYWORD_WRITE_VECTOR_OPERATION = "__WRITE_VECTOR_OPERATION__";
  private static final String _MULTIPLE_LINE_KEYWORD_WRITE_VECTOR_TWO_POW_D_OPERATION = "__WRITE_VECTOR_TWO_POW_D_OPERATION__";
  private static final String _MULTIPLE_LINE_KEYWORD_WRITE_STENCIL_OPERATION = "__WRITE_STENCIL_OPERATION__";

  private static final String _MULTIPLE_LINE_KEYWORD_MAPPINGS = "__MAPPINGS__";

  private static final String _TEMPORARY_KEYWORD_TYPENAME = "__THIS_TYPENAME__";
  private static final String _TEMPORARY_KEYWORD_FULL_QUALIFIED_TYPENAME = "__THIS_QUALIFIED_TYPENAME__";
  
  private static final String _KEYWORD_NUMBER_OF_ADAPTERS_ = "__NUMBER_OF_ADAPTERS__";

  private java.io.File _templateDirectory;

  /**
   * All the mappings from keywords to concrete names.
   */
  private java.util.HashMap<String, String> _mapping;

  /**
   * All the mappings from keywords to several names.
   */
  private java.util.HashMap<String, java.util.Vector<String>> _multiMappings;

  /**
   * List of all the adapters associated to the project.
   */
  private java.util.Vector<String> _adapters;

  public TranslationTable(java.io.File templateDirectory) {
    _mapping = new java.util.HashMap<String, String>();
    _templateDirectory = templateDirectory;
    for (String p : _mapping.keySet()) {
      _mapping.put(p, "UNDEF");
    }
    _adapters = new java.util.Vector<String>();
    _multiMappings = new java.util.HashMap<String, java.util.Vector<String>>();

    _multiMappings.put(_MULTIPLE_LINE_KEYWORD_READ_SCALAR_OPERATION,
        new java.util.Vector<String>());
    _multiMappings.put(_MULTIPLE_LINE_KEYWORD_READ_VECTOR_OPERATION,
        new java.util.Vector<String>());
    _multiMappings.put(_MULTIPLE_LINE_KEYWORD_READ_VECTOR_TWO_POW_D_OPERATION,
            new java.util.Vector<String>());
    _multiMappings.put(_MULTIPLE_LINE_KEYWORD_READ_STENCIL_OPERATION,
        new java.util.Vector<String>());
    _multiMappings.put(_MULTIPLE_LINE_KEYWORD_WRITE_SCALAR_OPERATION,
        new java.util.Vector<String>());
    _multiMappings.put(_MULTIPLE_LINE_KEYWORD_WRITE_VECTOR_OPERATION,
        new java.util.Vector<String>());
    _multiMappings.put(_MULTIPLE_LINE_KEYWORD_WRITE_VECTOR_TWO_POW_D_OPERATION,
            new java.util.Vector<String>());
    _multiMappings.put(_MULTIPLE_LINE_KEYWORD_WRITE_STENCIL_OPERATION,
        new java.util.Vector<String>());
  }

  public void inAReadScalarOperation(AReadScalarOperation node) {
    _multiMappings.get(_MULTIPLE_LINE_KEYWORD_READ_SCALAR_OPERATION).add(
        node.getName().toString().trim());
  }

  public void inAReadVectorOperation(AReadVectorOperation node) {
    _multiMappings.get(_MULTIPLE_LINE_KEYWORD_READ_VECTOR_OPERATION).add(
        node.getName().toString().trim());
  }

  public void  inAReadVectorTwoPowDOperation(AReadVectorTwoPowDOperation node) {
    _multiMappings.get(_MULTIPLE_LINE_KEYWORD_READ_VECTOR_TWO_POW_D_OPERATION).add(
        node.getName().toString().trim());
  }

  public void inAReadStencilOperation(AReadStencilOperation node) {
    _multiMappings.get(_MULTIPLE_LINE_KEYWORD_READ_STENCIL_OPERATION).add(
        node.getName().toString().trim());
  }
  
  public void inAWriteVectorOperation(AWriteVectorOperation node) {
    _multiMappings.get(_MULTIPLE_LINE_KEYWORD_WRITE_VECTOR_OPERATION).add(
        node.getName().toString().trim());
  }
  
  public void inAWriteVectorTwoPowDOperation(AWriteVectorTwoPowDOperation node) {
    _multiMappings.get(_MULTIPLE_LINE_KEYWORD_WRITE_VECTOR_TWO_POW_D_OPERATION).add(
        node.getName().toString().trim());
  }

  public void inAWriteScalarOperation(AWriteScalarOperation node) {
    _multiMappings.get(_MULTIPLE_LINE_KEYWORD_WRITE_SCALAR_OPERATION).add(
        node.getName().toString().trim());
  }

  public void inAWriteStencilOperation(AWriteStencilOperation node) {
    _multiMappings.get(_MULTIPLE_LINE_KEYWORD_WRITE_STENCIL_OPERATION).add(
        node.getName().toString().trim());
  }

  public void setThisTypenameToMappingTypename(String typename) {
    _mapping.put(_TEMPORARY_KEYWORD_TYPENAME, typename);
    _mapping.put(_TEMPORARY_KEYWORD_FULL_QUALIFIED_TYPENAME,
        _mapping.get(_KEYWORD_NAMESPACE) + "::mappings::" + typename);
  }

  public void setThisTypenameToAdapterTypename(String typename,
      java.util.Vector<String> mappings) {
    _mapping.put(_TEMPORARY_KEYWORD_TYPENAME, typename);
    _mapping.put(_TEMPORARY_KEYWORD_FULL_QUALIFIED_TYPENAME,
        _mapping.get(_KEYWORD_NAMESPACE) + "::adapters::" + typename);

    _multiMappings.put(_MULTIPLE_LINE_KEYWORD_MAPPINGS, mappings);
  }

  private String getOpeningNamespace(String fullQualifiedName) {
    String namespace = fullQualifiedName;
    String result = "";
    int count = 0;
    while (namespace.length() != 0) {
      for (int i = 0; i < count; i++) {
        result += " ";
      }
      result += "namespace ";
      if (namespace.indexOf("::") != -1) {
        result += namespace.substring(0, namespace.indexOf("::"));
        namespace = namespace.substring(namespace.indexOf("::") + 2);
        count += 2;
        result += " { \n";
      } else {
        result += namespace;
        namespace = "";
        result += " {";
      }
    }
    return result;
  }

  private String getClosingNamespace(String fullQualifiedName) {
    String namespace = fullQualifiedName;
    String result = "";
    while (namespace.indexOf("::") != -1) {
      result += "}\n";
      namespace = namespace.substring(namespace.indexOf("::") + 2);
    }
    result += "}";
    return result;
  }
  
  public void inADescription(ADescription node) {
    _mapping.put(_KEYWORD_NAMESPACE, node.getNamespace().getText().trim());
    _mapping.put(_KEYWORD_INCLUDE_GUARD_PREFIX, _mapping
        .get(_KEYWORD_NAMESPACE).replaceAll("::", "_").toUpperCase());
    _mapping.put(_KEYWORD_COMPONENT_NAME, node.getName().getText().trim());

    _mapping.put(_KEYWORD_OPEN_NAMESPACE,
        getOpeningNamespace(_mapping.get(_KEYWORD_NAMESPACE)));
    _mapping.put(_KEYWORD_CLOSE_NAMESPACE,
        getClosingNamespace(_mapping.get(_KEYWORD_NAMESPACE)));
//
//    _mapping.put(_KEYWORD_PATH_OF_ADAPTER, _mapping.get(_KEYWORD_NAMESPACE)
//        .replaceAll("::", "/") + "/adapters/");
//    _mapping.put(_KEYWORD_PATH_OF_MAPPINGS, _mapping.get(_KEYWORD_NAMESPACE)
//        .replaceAll("::", "/") + "/mappings/");
  }

  public void inAAdapter(AAdapter node) {
    _adapters.add(node.getName().getText().trim());
  }

  public void inAVertex(AVertex node) {
    _mapping.put(_KEYWORD_DOF_DASTGEN_DEFINITION_VERTEX, node.getFilename().getText().trim());
  }

  public void inACell(ACell node) {
    _mapping.put(_KEYWORD_DOF_DASTGEN_DEFINITION_CELL, node.getFilename().getText().trim());
  }

  public void inAState(AState node) {
    _mapping.put(_KEYWORD_DOF_DASTGEN_DEFINITION_STATE, node.getFilename().getText().trim());
  }

  public void outStart(Start node) {
    String enumDeclaration = "enum Action { WriteCheckpoint, ReadCheckpoint, Terminate";
    for (String p : _adapters) {
      enumDeclaration += ",UseAdapter";
      enumDeclaration += p;
    }
    enumDeclaration += "}";

    _mapping.put(_KEYWORD_REPOSITORY_ACTION_ENUM, enumDeclaration);

    _multiMappings.put(_MULTIPLE_LINE_KEYWORD_FULL_QUALIFIED_ADAPTER_TYPE,
        new java.util.Vector<String>());
    _multiMappings.put(_MULTIPLE_LINE_KEYWORD_NONQUALIFIED_ADAPTER_TYPE,
        new java.util.Vector<String>());

    for (String p : _adapters) {
      String typeName = p;
      String qualifiedTypeName = _mapping.get(_KEYWORD_NAMESPACE)
          + "::adapters::" + p;
      _multiMappings.get(_MULTIPLE_LINE_KEYWORD_NONQUALIFIED_ADAPTER_TYPE).add(
          typeName);
      _multiMappings.get(_MULTIPLE_LINE_KEYWORD_FULL_QUALIFIED_ADAPTER_TYPE)
          .add(qualifiedTypeName);
    }

    _mapping.put(_KEYWORD_NUMBER_OF_ADAPTERS_, java.lang.Integer.toString(_adapters.size()));
  }

  static public String getCellUnqualifiedName() {
    return "Cell";
  }

  static public String getStateUnqualifiedName() {
    return "State";
  }

  static public String getVertexUnqualifiedName() {
    return "Vertex";
  }

  static public String getRepositoryStateUnqualifiedName() {
    return "RepositoryState";
  }

  private String replaceKeywords(String line) {
    String text = line;
    for (String p : _mapping.keySet()) {
      text = text.replaceAll(p, _mapping.get(p));
    }
    return text;
  }

  public void copyTemplateFile(
    String    templateFile, 
    String    destinationFile,
    boolean   overwrite
  ) {
	destinationFile = destinationFile.replaceAll("\\\\", "/");
	if ((new java.io.File(destinationFile)).exists() && !overwrite) {
		System.out.print("\n " + destinationFile + " already exists)");
	} else {
      try {
		java.io.OutputStreamWriter writer = new java.io.OutputStreamWriter(
			new java.io.FileOutputStream(destinationFile));
		String text = new String();
   		java.io.BufferedReader reader = getBufferedReaderForStdTemplate(templateFile);

		while ((text = reader.readLine()) != null) {
		  writer.write(text);
          writer.write("\n");
        }
		writer.close();
		reader.close();
      } catch (Exception e) {
		System.out.println(e.getClass() + " " + e.getMessage() + "\n");
		e.printStackTrace();
	  }
	}
  }


  public void convertTemplateFile(
    String    templateFile, 
    String    destinationFile,
    String[]  replaceAdditionalString,
    String[]  withString,
    boolean   overwrite
  ) {
  	destinationFile = destinationFile.replaceAll("\\\\", "/");
	

//		// Log generated file
//		String relativeFileName = new File(destinationFile).getAbsolutePath()
//				.replaceFirst(rootDirectory, "");
//		Log.writeGeneratedFile(relativeFileName);

		if ((new java.io.File(destinationFile)).exists() && !overwrite) {
			System.out.print("\n  (blueprint of " + destinationFile
					+ " already exists)");
		} else {
			try {
				java.io.OutputStreamWriter writer = new java.io.OutputStreamWriter(
						new java.io.FileOutputStream(destinationFile));
				String text = new String();
			  	java.io.BufferedReader reader = getBufferedReaderForStdTemplate(templateFile);

				while ((text = reader.readLine()) != null) {
					for (String p : _multiMappings.keySet()) {
					  boolean isPattern   = false;
					  boolean appendComma = false;
					  String  textToRemove = "";

					  if (text.contains(MULTIPLE_REPLACEMENT_LINE_PREFIX_WITH_COMMA + p )) {
	            isPattern     = true;
	            appendComma   = true;
	            textToRemove  = MULTIPLE_REPLACEMENT_LINE_PREFIX_WITH_COMMA + p;
	          }
					  else if (text.contains(MULTIPLE_REPLACEMENT_LINE_PREFIX + p)) {
					    isPattern = true;
              textToRemove  = MULTIPLE_REPLACEMENT_LINE_PREFIX + p;
					  }
					  
						if (isPattern) {
							String modifiedText = text.replaceAll(textToRemove, "");
							text = "";
							int numberOfOustandingReplacements = _multiMappings.get(p).size();
							for (String replacement : _multiMappings.get(p)) {
								text += modifiedText.replaceAll(p, replacement);
								numberOfOustandingReplacements--;
		            if (appendComma && numberOfOustandingReplacements>0) {
	                text += ", \n";
		            }
		            else {
	                text += "\n";
		            }
							}
						}
					}

					text = replaceKeywords(text);

					if (replaceAdditionalString!=null) {
						for (int i=0; i<replaceAdditionalString.length; i++) {
							text = text.replaceAll(replaceAdditionalString[i], withString[i]);
						}
					}

					writer.write(text);
					writer.write("\n");
				}

				writer.close();
				reader.close();
			} catch (Exception e) {
				System.out.println(e.getClass() + " " + e.getMessage() + "\n");
				e.printStackTrace();
			}
		}
  }

  private java.io.BufferedReader getBufferedReaderForStdTemplate(String templateFile)
		throws FileNotFoundException {
	templateFile = "/stdtemplates/" + templateFile;
    java.io.InputStream stream = Main.class.getResourceAsStream(templateFile);
    if (stream==null) {
      throw new FileNotFoundException(templateFile);
    }
	java.io.BufferedReader reader = new java.io.BufferedReader(
	  new java.io.InputStreamReader(stream));
	return reader;
  }

  private java.io.BufferedReader getBufferedReaderForUserTemplate(String templateFile)
		throws FileNotFoundException {
	templateFile = _templateDirectory + "/" + templateFile;
	templateFile = templateFile.replaceAll("\\\\", "/");
	java.io.BufferedReader reader = new java.io.BufferedReader(
			new java.io.FileReader(new java.io.File(templateFile)));
	return reader;
  }

  /**
   * Read a template file, replace all the keywords in it with the value, and
   * write the resulting file to destinationFile.
   * 
   * @param destinationFile
   * @param rootDirectory
   * @param templateFile
   */
  public void convertTemplateFile(
    String  templateFile, 
    String  destinationFile,
    boolean overwrite
  ) {
    convertTemplateFile(templateFile,destinationFile,null,null,overwrite);
  }
  
//
//  
//  public String getRegularStateDefinitionFilePath(String rootSourceDirectory) {
//	return rootSourceDirectory + File.separator + _mapping.get( _KEYWORD_DOF_DASTGEN_DEFINITION_STATE );
//  }
//
//  public String getRegularVertexDefinitionFilePath(String rootSourceDirectory) {
//	return rootSourceDirectory + File.separator + _mapping.get( _KEYWORD_DOF_DASTGEN_DEFINITION_STATE );
//  }
//
//  public String getRegularCellDefinitionFilePath(String rootSourceDirectory) {
//	return rootSourceDirectory + File.separator + _mapping.get( _KEYWORD_DOF_DASTGEN_DEFINITION_STATE );
//  }
//
//  public String getSpacetreeStateDefinitionFilePath(String rootSourceDirectory) {
//	return rootSourceDirectory + File.separator + _mapping.get( _KEYWORD_DOF_DASTGEN_DEFINITION_STATE );
//  }
//
//  public String getSpacetreeVertexDefinitionFilePath(String rootSourceDirectory) {
//	return rootSourceDirectory + File.separator + _mapping.get( _KEYWORD_DOF_DASTGEN_DEFINITION_STATE );
//  }
//
//  public String getSpacetreeCellDefinitionFilePath(String rootSourceDirectory) {
//	return rootSourceDirectory + File.separator + _mapping.get( _KEYWORD_DOF_DASTGEN_DEFINITION_STATE );
//  }
}
