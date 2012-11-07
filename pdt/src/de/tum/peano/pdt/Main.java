// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org.
package de.tum.peano.pdt;

import java.io.File;

public class Main {
	public static void printUsage() {
		System.out.println("Peano Developement Toolkit (PDT)");
		System.out.println("(C) 2010 Tobias Weinzierl");
		System.out.println("");
		System.out.println("Usage: de.tum.peano.pdt.Main  peano-specification-file component-output-directory peano-kernel-directory [template-directory]");
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		boolean createSpacetreegrid = false;
		boolean createRegulargrid   = false;
		if (args.length < 3 || args.length > 4) {
			printUsage();
		} else {
			try {
				String inputFileName         = args[0];
				String outputDirectoryName   = args[1];
				String kernelDirectoryName   = args[2];
				String templateDirectoryName = args.length == 4 ? args[3] : null;

				java.io.File outputDirectory = new java.io.File(outputDirectoryName);
				if (!outputDirectory.isDirectory()) {
					System.err.println("output directory " + outputDirectory.getAbsolutePath() + " is no valid directory");
					System.exit(-1);
				}

				java.io.File kernelDirectory = new java.io.File(kernelDirectoryName);
				if (!outputDirectory.isDirectory()) {
					System.err.println("kernel directory " + kernelDirectory.getAbsolutePath() + " is no valid directory");
					System.exit(-1);
				}


				java.io.File templateDirectory = null;
				if (templateDirectoryName!=null) {
					templateDirectory = new java.io.File(templateDirectoryName);
					if (!templateDirectory.isDirectory()) {
						System.err.println("template directory " + templateDirectory.getAbsolutePath() + " is no valid directory");
						System.exit(-1);
					}
				}

				System.out.print("read input file " + inputFileName);
				de.tum.peano.pdt.parser.Parser parser = new de.tum.peano.pdt.parser.Parser(
                  new de.tum.peano.pdt.lexer.Lexer(
					new java.io.PushbackReader(
					  new java.io.FileReader(inputFileName)
					)
			      )
                );
				de.tum.peano.pdt.node.Start document = parser.parse();
				System.out.println(" ... ok");

				System.out.print("generate output directories");
				de.tum.peano.pdt.generators.DirectoryGenerator dirGenerator = new de.tum.peano.pdt.generators.DirectoryGenerator(
				  outputDirectory
				);
				document.apply(dirGenerator);
				System.out.println(" ... ok");
				
//				Log.setFileForGeneratedFiles(new File(dirGenerator
//						.getComponentDirectoryAbsolute(), GENERATED_FILES_LOG)
//						.getAbsolutePath());
//
//				System.out.print("fill translation table");
//				TranslationTable translationTable = new TranslationTable(templateDirectory);
//				document.apply(translationTable);
//				System.out.println(" ... ok");
//
//				System.out.print("generate doxys files");
//				Log.writeGeneratedFile("!!! Doxys Files\n");
//				document
//						.apply(new de.tum.peano.peprot.generators.DoxySGenerator(
//								dirGenerator, translationTable));
//				System.out.println(" ... ok");
//
//				Log.writeGeneratedFile("\n\n!!! DoF-File Wrapper (Blueprints)\n");
//				System.out.print("generate dof file wrapper for DaStGen");
//				document
//						.apply(new de.tum.peano.peprot.generators.DaStGenFileGenerator(
//								dirGenerator, translationTable));
//				System.out.println(" ... ok");
//
//				System.out.print("invoke DaStGen");
//				Log.writeGeneratedFile("\n\n!!! DaStGen Records (Do not change!)\n");
//				document
//						.apply(new de.tum.peano.peprot.generators.DaStGenGenerator(
//								dirGenerator, translationTable));
//				System.out.println(" ... ok");
//
//				System.out
//						.print("generate blueprints for vertices, cells, states, and mappings");
//				Log
//						.writeGeneratedFile("\n\n!!! Vertices, Cells, States and Mappings (Blueprints)\n");
//				document
//						.apply(new de.tum.peano.peprot.generators.BluePrintGenerator(
//								dirGenerator, translationTable, createSpacetreegrid, createRegulargrid));
//				System.out.println(" ... ok");
//
//				System.out.print("generate repositories");
//				Log.writeGeneratedFile("\n\n!!! Repositories (Do not change!)\n");
//				document
//						.apply(new de.tum.peano.peprot.generators.RepositoryGenerator(
//								dirGenerator, translationTable, createSpacetreegrid, createRegulargrid));
//				System.out.println(" ... ok");
//
//				System.out.print("generate configurations");
//				Log.writeGeneratedFile("\n\nConfiguration:\n");
//				document
//						.apply(new de.tum.peano.peprot.generators.ConfigurationGenerator(
//								dirGenerator, translationTable, createSpacetreegrid, createRegulargrid));
//				System.out.println(" ... ok");
//
//				System.out.print("generate runners");
//				Log.writeGeneratedFile("\n\n!!! Runners (Blueprints)\n");
//				document
//						.apply(new de.tum.peano.peprot.generators.RunnerGenerator(
//								dirGenerator, translationTable, createSpacetreegrid, createRegulargrid));
//				System.out.println(" ... ok");
//
//				System.out.print("generate adapters");
//				Log.writeGeneratedFile("\n\n!!! Adapters (Do not change!)\n");
//				document
//						.apply(new de.tum.peano.peprot.generators.AdapterGenerator(
//								dirGenerator, translationTable, createSpacetreegrid, createRegulargrid));
//				System.out.println(" ... ok");
//
//				System.out.print("generate CCA files");
//				Log.writeGeneratedFile("\n\n!!! Adapters (Do not change!)\n");
//				document
//						.apply(new de.tum.peano.peprot.generators.CCAFileGenerator(
//								dirGenerator, translationTable, createSpacetreegrid, createRegulargrid));
//				System.out.println(" ... ok");
//
//				System.out.print("generate makefiles");
//				Log.writeGeneratedFile("\n\n!!! Makefiles\n");
//				document
//						.apply(new de.tum.peano.peprot.generators.MakefileGenerator(
//								dirGenerator, translationTable));
//				System.out.println(" ... ok");
//
//				System.out.print("generate tests");
//				Log.writeGeneratedFile("\n\nTests:\n");
//				document
//						.apply(new de.tum.peano.peprot.generators.TestCaseGenerator(
//								dirGenerator, translationTable));
//				System.out.println(" ... ok");

			} catch (Exception e) {
				System.out.println(e.getClass() + " " + e.getMessage() + "\n");
				e.printStackTrace();
				System.out.println("Use option -h to display help message.");
			}
		}
	}
}
