/* -*- mode: java; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*

  Modified version of Compiler.java, which is...

  Part of the Processing project - http://processing.org

  Copyright (c) 2004-08 Ben Fry and Casey Reas
  Copyright (c) 2001-04 Massachusetts Institute of Technology

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

package processing.app.debug;

import static processing.app.debug.Compiler.createFolder;

import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;

import processing.app.Base;
import processing.app.Sketch;


public class ArmCompiler extends Compiler {

  public ArmCompiler() { }

  private boolean messagesNonError = false; // THIS IS SUCH A HACK.
  private List<String> hackErrors = null;

  // well, if we're using fields as a global variable hack, we might
  // as well be consistent
  private Map<String, String> boardPrefs;
  private File corePath;

  private boolean verboseOut = false;//[ROBOTIS CHANGE]
  static byte checksumBinary = 0;
  /**
   * Compile for ARM with make
   *
   * @param sketch Sketch object to be compiled.
   * @param buildPath Where the temporary files live and will be built from.
   * @param primaryClassName the name of the combined sketch file w/ extension
   * @return true if successful.
   * @throws RunnerException iff there's a problem.
   */
  @Override
    public boolean compile
    (Sketch sketch, String buildPath, String primaryClassName,
     boolean verbose, List<String> compileErrors)
    throws RunnerException {
	
    this.sketch = sketch;
    this.buildPath = buildPath;
    createFolder(new File(buildPath));
    this.primaryClassName = primaryClassName;
    this.verbose = verbose;
    this.hackErrors = compileErrors;
    sketchIsCompiled = false; //[ROBOTIS]add to notify when this compile is finished
    // the pms object isn't used for anything but storage
    MessageStream pms = new MessageStream(this);
    verboseOut = verbose;
    try {
      this.boardPrefs = Base.getBoardPreferences();
    } catch (NullPointerException npe) {
      Base.showWarning("No board selected",
                       "please choose one from the Tools menu.",
                       npe);
      return false;
    }
    
    String core = boardPrefs.get("build.core");
    if (core.indexOf(':') == -1) {
      Target t = Base.getTarget();
      File coreFolder = new File(new File(t.getFolder(), "cores"), core);
      this.corePath = new File(coreFolder.getAbsolutePath());
    } else {
      Target t = Base.targetsTable.get(core.substring(0, core.indexOf(':')));
      File coresFolder = new File(t.getFolder(), "cores");
      File coreFolder = new File(coresFolder,
                                 core.substring(core.indexOf(':') + 1));
      this.corePath = new File(coreFolder.getAbsolutePath());
    }

    List<File> objectFiles = new ArrayList<File>();
    List<File> includePaths = new ArrayList<File>(Arrays.asList(corePath));

    sketch.setCompilingProgress(10);
    
    // 1. compile the core (e.g. libmaple for a Maple target),
    // outputting .o files to buildPath.
    //System.out.println("[ARM Compiler] #### 1. compile the core ####");
    objectFiles.addAll(compileFiles(buildPath, includePaths,
                                    corePath.getAbsolutePath(), true));
    
    // 2. compile the libraries, updating includePaths as necessary.
    //System.out.println("[ARM Compiler] #### 2. compile the libraries ####");
    objectFiles.addAll(compileLibraries(includePaths));
    sketch.setCompilingProgress(60);
    
    // 3. compile the sketch (already in the buildPath)
    //System.out.println("[ARM Compiler] #### 3. compile the sketch  ####");
    objectFiles.addAll(compileFiles(buildPath, includePaths,
                                    buildPath, false));
    sketch.setCompilingProgress(70);
    // 4. link it all together into the .bin file
    File binFile = linkFiles(objectFiles);
   // System.out.println("[ARM Compiler] #### 4. link it all together into the .bin file ####");
    
    sketch.setCompilingProgress(80);
    
    // 5. compute binary sizes and report to user
   // System.out.println("[ArmCompiler] #####5. compute binary sizes and report to user ####");
    sizeBinary(binFile);
    //[ROBOTIS][START] 2012-12-18 to limit binary size for each board.
    long sizeOfBinary = binFile.length();
    System.out.println("\n[ARM Compiler] #### binary size : "+sizeOfBinary+" Bytes ####");
    long maxSizeOfBinary = Integer.parseInt(boardPrefs.get("upload.maximum_size"));
    float percentageOfTotalSize = ((sizeOfBinary*100)/maxSizeOfBinary);
    if(boardPrefs.get("name") != null)
    	System.out.println( boardPrefs.get("name")+
    					   " Max binary size : "+ maxSizeOfBinary +" Bytes"+
    					   "("+percentageOfTotalSize+"%)");
    else
    	System.out.println("[ROBOTIS] "+
				   " Max binary size : "+ maxSizeOfBinary +" Bytes"+
				   "("+percentageOfTotalSize+"%)");
    
    if(sizeOfBinary > maxSizeOfBinary ){
    	System.out.println("[ROBOTIS] Binary size is too big to download to your board");
    	return false; // exception
    }
  //[ROBOTIS][END] 2012-12-18 to limit binary size for each board.
    
    //calculate checksum data form binary file for download
    checksumBinary = CalculateChecksumFromBinary(binFile);
    
    //[ROBOTIS] size limit code to be added 
    sketchIsCompiled = true;
    
    sketch.setCompilingProgress(90);
    
    return true;
  }
  //[ROBOTIS] added for mac os checksum error
  public static byte getChecksumOfBinary(){
	  return checksumBinary;
  }
  
  @Override
  protected void execAsynchronously(List<String> commandList)
    throws RunnerException {
   // if (DEBUG) System.out.println("*** execAsynchronously: " + commandList);
    super.execAsynchronously(commandList);
  }

  /**
   * @return List of object paths created as a result of compilation.
   */
  private List<File> compileFiles(String buildPath, List<File> includePaths,
                                  String sourcePath, boolean recurse)
    throws RunnerException {

	  
    // getCommandCompilerFoo will destructively modify objectPaths
    // with any object files the command produces.
    List<File> objectPaths = new ArrayList<File>();

  //  System.out.println("[ArmCompiler]compileFiles() includePaths : "+includePaths+"sourcePath : "+sourcePath);
    // Compile assembly files
    for (File file : findFilesInPath(sourcePath, "S", recurse)) { //[ROBOTIS] changed "S" -> "s" to compile startup assembly code
      if(verboseOut != true)
    	  System.out.print(".");
      execAsynchronously(getCommandCompilerS(includePaths,
                                             file.getAbsolutePath(),
                                             buildPath,
                                             objectPaths));
    }

    if (recurse == true)
    	sketch.setCompilingProgress(20);
    // Compile C files
    for (File file : findFilesInPath(sourcePath, "c", recurse)) {
      //System.out.println("[ArmCompiler]compileFiles() file name : "+file);
      if(verboseOut != true)
    	  System.out.print(".");
      execAsynchronously(getCommandCompilerC(includePaths,
                                             file.getAbsolutePath(),
                                             buildPath,
                                             objectPaths));
    }

    if (recurse == true)
    	sketch.setCompilingProgress(40);
    // Compile C++ files
    for (File file : findFilesInPath(sourcePath, "cpp", recurse)) {
      if(verboseOut != true)
      	  System.out.print(".");
      execAsynchronously(getCommandCompilerCPP(includePaths,
                                               file.getAbsolutePath(),
                                               buildPath,
                                               objectPaths));
    }

    if (recurse == true)
    	sketch.setCompilingProgress(50);
    return objectPaths;
  }

  /**
   * Destructively modifies includePaths to reflect any library
   * includes, which will be of the form
   *   <buildPath>/<library>/
   *
   * @return List of object files created.
   */
  private List<File> compileLibraries(List<File> includePaths)
    throws RunnerException {
	//System.out.println("[ArmCompiler]******* compileLibraries() ********");
    List<File> objectFiles = new ArrayList<File>();

    List<File> importedLibs = sketch.getImportedLibraries();
    if (!importedLibs.isEmpty()) {
      List<String> libNames = new ArrayList<String>();
      for (File lib: importedLibs) libNames.add(lib.getName());
      String libString = libNames.toString();
      libString = libString.substring(1, libString.length()-1);
      System.out.println("\tCompiling libraries: " + libString);

      // use library directories as include paths for all libraries
      includePaths.addAll(importedLibs);

      for (File libraryFolder: importedLibs) {
        File outputFolder = new File(buildPath, libraryFolder.getName());
        File utilityFolder = new File(libraryFolder, "utility");
        createFolder(outputFolder);
        // libraries can have private includes in their utility/ folders
        includePaths.add(utilityFolder);

        objectFiles.addAll
          (compileFiles(outputFolder.getAbsolutePath(), includePaths,
                        libraryFolder.getAbsolutePath(), false));

        outputFolder = new File(outputFolder, "utility");
        createFolder(outputFolder);

        objectFiles.addAll
          (compileFiles(outputFolder.getAbsolutePath(), includePaths,
                        utilityFolder.getAbsolutePath(), false));

        // other libraries should not see this library's utility/ folder
        includePaths.remove(includePaths.size() - 1);
      }
    } else {
      System.out.println("\n\tNo libraries to compile.");
    }

    return objectFiles;
  }

  /**
   * Runs the linker script on the compiled sketch.
   * @return the .bin file generated by the linker script.
   */
  private File linkFiles(List<File> objectFiles) throws RunnerException {
    //System.out.println("[ArmCompiler]linkFiles() -> Linking...");
    //System.out.println("[ArmCompiler]linkFiles() corePath : "+corePath+"build.linker : "+boardPrefs.get("build.linker"));
    ///[ROBOTIS]임시땜빵 코드임  -> 링커를 하드코딩함!^^;;
    File linkerScript = new File(corePath, boardPrefs.get("build.linker"));
    File elf = new File(buildPath, primaryClassName + ".elf");
    File bin = new File(buildPath, primaryClassName + ".bin");

    // Run the linker
    List<String> linkCommand = new ArrayList<String>
      (Arrays.asList
       (Base.getArmBasePath() + "arm-none-eabi-g++",
        "-T" + linkerScript.getAbsolutePath(),
        "-L" + corePath.getAbsolutePath(),
        "-mcpu=cortex-m3",
        "-mthumb",
        "-Xlinker",
        "--gc-sections",
        "--print-gc-sections",
        "--march=armv7-m",
        "-Wall",
        "-o", elf.getAbsolutePath()));

    for (File f: objectFiles) linkCommand.add(f.getAbsolutePath());

    linkCommand.add("-L" + buildPath);

    execAsynchronously(linkCommand);

    // Run objcopy
    List<String> objcopyCommand = new ArrayList<String>
      (Arrays.asList
       (Base.getArmBasePath() + "arm-none-eabi-objcopy",
        "-v",
        "-Obinary",
        elf.getAbsolutePath(),
        bin.getAbsolutePath()));

    execAsynchronously(objcopyCommand);

    return bin;
  }

  private void sizeBinary(File binFile) throws RunnerException {
    System.out.println("\tComputing sketch size...");

    List<String> command = new ArrayList<String>
      (Arrays.asList(Base.getArmBasePath() + "arm-none-eabi-size",
    		  		 "-A",
                     "--target=binary",
                     binFile.getAbsolutePath()));

    messagesNonError = true;
    System.out.println();
    execAsynchronously(command);
   
    messagesNonError = false;
  }
 
  private byte CalculateChecksumFromBinary(File binFile){
	   
	byte checkSumByte=0;
    DataInputStream binaryInput = null;
    try {
    	binaryInput = new DataInputStream(new FileInputStream(binFile));
	} catch (FileNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
    byte[] buff = new byte[4096];
    
	int size;
	
	
	try {
		while((size = binaryInput.read(buff)) > -1){
			//fileSize += size;
			for(int i=0 ; i < size ; i++){
				checkSumByte += buff[i];
			}
		
		}
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	/*String outTemp = String.format("0x%x", checkSumByte);
	
	System.out.println("############ Checksum : "+outTemp+" ##############");*/
	try {
		binaryInput.close();
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
		
	return checkSumByte;
}

  /////////////////////////////////////////////////////////////////////////////

  private List<String> getCommandCompilerS
    (List<File> includePaths, String sourceName, String buildPath,
     List<File> hackObjectPaths) {
	 
    String buildBase = getBuildBase(sourceName);
    File depsFile = new File(buildBase + ".d");
    File objFile = new File(buildBase + ".o");

    hackObjectPaths.add(objFile);

    List<String> command = new ArrayList<String>();

    command.addAll
      (Arrays.asList
       (Base.getArmBasePath() + "arm-none-eabi-gcc",
        "-mcpu=cortex-m3",
        "-march=armv7-m",
        "-mthumb",
        "-DBOARD_" + boardPrefs.get("build.board"),
        "-DMCU_" + boardPrefs.get("build.mcu"),
        "-D" + boardPrefs.get("build.density"),
        "-DERROR_LED_PORT=" + boardPrefs.get("build.error_led_port"),
        "-DERROR_LED_PIN=" + boardPrefs.get("build.error_led_pin"),
        //"-DMAPLE_IDE",
        "-x", "assembler-with-cpp",
        "-o", objFile.getAbsolutePath(),
        "-c",
        sourceName));
    //System.out.println("[S]command -> "+command);
    return command;
  }


  private List<String> getCommandCompilerC
    (List<File> includePaths, String sourceName, String buildPath,
     List<File> hackObjectPaths) {

    String buildBase = getBuildBase(sourceName);
    File depsFile = new File(buildBase + ".d");
    File objFile = new File(buildBase + ".o");

    hackObjectPaths.add(objFile);

    List<String> command = new ArrayList<String>();

    command.addAll
      (Arrays.asList
       (Base.getArmBasePath() + "arm-none-eabi-gcc",
        "-Os",
        "-g",
        "-mcpu=cortex-m3",
        "-mthumb",
        "-march=armv7-m",
        "-nostdlib",
        "-ffunction-sections",
        "-fdata-sections",
        "-Wl,--gc-sections",
        "-DBOARD_" + boardPrefs.get("build.board"),
        "-DMCU_" + boardPrefs.get("build.mcu"),
        "-D" + boardPrefs.get("build.vect"),
        "-D" + boardPrefs.get("build.density"),
        "-DERROR_LED_PORT=" + boardPrefs.get("build.error_led_port"),
        "-DERROR_LED_PIN=" + boardPrefs.get("build.error_led_pin")
        //,"-DMAPLE_IDE",
        //"-DARDUINO=" + Base.REVISION
        ));

    for (File i: includePaths) {
      command.add("-I" + i.getAbsolutePath());
    }

    command.addAll
      (Arrays.asList
       ("-o", objFile.getAbsolutePath(),
        "-c",
        sourceName));
   // System.out.println("[C]command -> "+command);
    return command;
  }

  private List<String> getCommandCompilerCPP
    (List<File> includePaths, String sourceName, String buildPath,
     List<File> hackObjectPaths) {

    String buildBase = getBuildBase(sourceName);
    File depsFile = new File(buildBase + ".d");
    File objFile = new File(buildBase + ".o");

    hackObjectPaths.add(objFile);

    List<String> command = new ArrayList<String>();

    command.addAll
      (Arrays.asList
       (Base.getArmBasePath() + "arm-none-eabi-g++",
        "-Os",
        "-g",
        "-mcpu=cortex-m3",
        "-mthumb",
        "-march=armv7-m",
        "-nostdlib",
        "-ffunction-sections",
        "-fdata-sections",
        "-Wl,--gc-sections",
        "-DBOARD_" + boardPrefs.get("build.board"),
        "-DMCU_" + boardPrefs.get("build.mcu"),
        "-D" + boardPrefs.get("build.density"),
        "-D" + boardPrefs.get("build.vect"),
        "-DERROR_LED_PORT=" + boardPrefs.get("build.error_led_port"),
        "-DERROR_LED_PIN=" + boardPrefs.get("build.error_led_pin")
        //,"-DMAPLE_IDE"
        ));

    for (File i: includePaths) {
      command.add("-I" + i.getAbsolutePath());
    }

    command.addAll(Arrays.asList("-fno-rtti", "-fno-exceptions", "-Wall"));

    command.addAll
      (Arrays.asList
       ("-o", objFile.getAbsolutePath(),
        "-c",
        sourceName));
    //System.out.println("[Cpp]command -> "+command);
    return command;
  }

  private String getBuildBase(String sourceFile) {
    File f = new File(sourceFile);
    String s = f.getName();
    return buildPath + File.separator + s.substring(0, s.lastIndexOf('.'));
  }

  /**
   * Part of the MessageConsumer interface, this is called
   * whenever a piece (usually a line) of error message is spewed
   * out from the compiler. The errors are parsed for their contents
   * and line number, which is then reported back to Editor.
   */
  public void message(String s) {
    // This receives messages as full lines, so a newline needs
    // to be added as they're printed to the console.
    //System.err.print(s);
	 
    this.hackErrors.add(s);
    // SUCH A HACK
    if (messagesNonError) {
      System.out.print(s);
      return;
    }

    // ignore cautions
    if (s.indexOf("warning") != -1) return;

    // ignore this line; the real error is on the next one
    if (s.indexOf("In file included from") != -1) return;

    // ignore obj copy
    if (s.indexOf("copy from ") != -1) return;

    String buildPathSubst = buildPath + File.separatorChar;

    String partialTempPath = null;
    int partialStartIndex = -1; //s.indexOf(partialTempPath);
    int fileIndex = -1;  // use this to build a better exception

    // check the main sketch file first.
    partialTempPath = buildPathSubst + primaryClassName;
    partialStartIndex = s.indexOf(partialTempPath);

    if (partialStartIndex != -1) {
      fileIndex = 0;
    } else {
      // wasn't there, check the other (non-pde) files in the sketch.
      // iterate through the project files to see who's causing the trouble
      for (int i = 0; i < sketch.getCodeCount(); i++) {
        if (sketch.getCode(i).isExtension("pde")) continue;

        partialTempPath = buildPathSubst + sketch.getCode(i).getFileName();
        //System.out.println(partialTempPath);
        partialStartIndex = s.indexOf(partialTempPath);
        if (partialStartIndex != -1) {
          fileIndex = i;
          //System.out.println("fileIndex is " + fileIndex);
          break;
        }
      }
      //+ className + ".java";
    }

    // if the partial temp path appears in the error message...
    //
    //int partialStartIndex = s.indexOf(partialTempPath);
    if (partialStartIndex != -1) {

      // skip past the path and parse the int after the first colon
      //
      String s1 = s.substring(partialStartIndex +
                              partialTempPath.length() + 1);
      //System.out.println(s1);
      int colon = s1.indexOf(':');

      if (s1.indexOf("In function") != -1 || colon == -1) {
        System.err.print(s1);
        //firstErrorFound = true;
        return;
      }

      int lineNumber;
      try {
        lineNumber = Integer.parseInt(s1.substring(0, colon));
      } catch (NumberFormatException e) {
        System.err.print(s1);
        return;
      }

      //System.out.println("pde / line number: " + lineNumber);

      if (fileIndex == 0) {  // main class, figure out which tab
        for (int i = 1; i < sketch.getCodeCount(); i++) {
          if (sketch.getCode(i).isExtension("pde")) {
            if (sketch.getCode(i).getPreprocOffset() < lineNumber) {
              fileIndex = i;
              //System.out.println("i'm thinkin file " + i);
            }
          }
        }
        // OLD to do: DAM: if the lineNumber is less than
        // sketch.getCode(0).getPreprocOffset() we shouldn't subtract
        // anything from it, as the error is above the location where
        // the function prototypes and #include "WProgram.h" were
        // inserted.
        lineNumber -= sketch.getCode(fileIndex).getPreprocOffset();
      }

      //String s2 = s1.substring(colon + 2);
      int err = s1.indexOf(":");
      if (err != -1) {

        // if the first error has already been found, then this must be
        // (at least) the second error found
        if (firstErrorFound) {
          secondErrorFound = true;
          return;
        }

        // if executing at this point, this is *at least* the first error
        firstErrorFound = true;

        err += ":".length();
        String description = s1.substring(err);
        description = description.trim();
        System.err.print(description);

        //System.out.println("description = " + description);
        //System.out.println("creating exception " + exception);
        exception = new RunnerException(description, fileIndex, lineNumber-1, -1, false);

        // NOTE!! major change here, this exception will be queued
        // here to be thrown by the compile() function
        //editor.error(exception);

      } else {
        System.err.println("i suck: " + s);
      }

    } else {
      // this isn't the start of an error line, so don't attempt to parse
      // a line number out of it.

      // if the second error hasn't been discovered yet, these lines
      // are probably associated with the first error message,
      // which is already in the status bar, and are likely to be
      // of interest to the user, so spit them to the console.
      //
      if (!secondErrorFound) {
        System.err.println(s);
      }
    }
  }

}

