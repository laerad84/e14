/**
 *  @file  GsimUIbash.hh
 *  @brief GsimUIbash
 *
 * ********************************************************************
 * * DISCLAIMER                                                       *
 * *                                                                  *
 * * The following disclaimer summarizes all the specific disclaimers *
 * * of contributors to this software. The specific disclaimers,which *
 * * govern, are listed with their locations in:                      *
 * *   http://cern.ch/geant4/license                                  *
 * *                                                                  *
 * * Neither the authors of this software system, nor their employing *
 * * institutes,nor the agencies providing financial support for this *
 * * work  make  any representation or  warranty, express or implied, *
 * * regarding  this  software system or assume any liability for its *
 * * use.                                                             *
 * *                                                                  *
 * * This  code  implementation is the  intellectual property  of the *
 * * GEANT4 collaboration.                                            *
 * * By copying,  distributing  or modifying the Program (or any work *
 * * based  on  the Program)  you indicate  your  acceptance of  this *
 * * statement, and all its terms.                                    *
 * ********************************************************************
 *
 *
 * Id: GsimUIbash.hh,v 1.1.1.1 2005/09/21 14:11:07 nanjo Exp 
 * GEANT4 tag Name:  
 *
 * $Id: GsimUIbash.hh,v 1.2 2006/06/13 16:42:58 jfiggins Exp $
 *
 * $Log: GsimUIbash.hh,v $
 * Revision 1.2  2006/06/13 16:42:58  jfiggins
 * Added Javadoc-style Doxygen comments.
 *
 * Revision 1.1  2005/11/01 15:15:55  yamaga
 * New MC baseed on Geant4 by Nanjo-san.
 */

#ifndef GsimUIbash_h
#define GsimUIbash_h 1

#include "G4VUIshell.hh"
#include "globals.hh"

#include <cstdio>
#include <cstdlib>


extern "C" {
#include "readline/readline.h"
#include "readline/history.h"
}



/**
 *  @class GsimUIbash
 *  @brief This class is one of the UI classes which emulate bash.
 *
 *  GetCommadLine() returns a command string input from a commad line.
 *
 *  Two pre-inplemented shell commands are also included, 
 *    ShowCurrentDirectory()   ... show current directory
 *    ListCommand()            ... list commands
 *
 *  [prompt string substitution] (default)
 *  %s ... current application status
 *  %/ ... current working directory
 */

class G4UIcommandTree;

class GsimUIbash : public G4VUIshell {

public:
  /**
   *  @function GetUIbash
   */
  static GsimUIbash* GetUIbash();
  /**
   *  @function GetCommandTree
   *  @brief Get tree node.
   *  @param dir The absolute path.
   */
  G4UIcommandTree* GetCommandTree(const G4String& dir) const;
  /**
   *  @function GetAbsCommandDirPath
   *  @brief Absolute path name (ignore command).
   *  @param apath The absolute path.
   *
   *  If apath is not the absolute path, the current command directory
   *  is appended to the front of apath.
   */
  G4String GetAbsCommandDirPath(const G4String& apath) const;   
  /**
   *  @function GetCommandPathTail
   *  @brief Tail of path ( xxx/xxx/zzz -> zzz, truncated //// -> /).
   *  @param apath The absolute path.
   */
  G4String GetCommandPathTail(const G4String& apath) const;
  /**
   *  @function GetCwd
   *  @brief Get current working directory.
   */
  inline G4String GetCwd() {return currentCommandDir;}
  
private:
  /**
   *  @brief fUIbash
   */
  static GsimUIbash* fUIbash;
  /**
   *  @brief Name of the history file.
   */
  G4String histfile;
  /**
   *  @brief The prompt setting including the %-directive.
   */
  G4String promptSetting;
  /**
   *  @brief The prompt string.
   */
  G4String promptString;
  /**
   *  @function MakePrompt
   *  @brief Make the prompt string.
   *  @param msg The message to use.
   */
  virtual void MakePrompt(const char* msg=0);
  /**
   *  @brief Column size of the terminal. The default is 80.
   */
  G4int nColumn;

  /**
   *  @brief Color code support.
   *
   *  This is effective if your terminal supports color code. The default
   *  setting is off.
   */
  G4bool lsColorFlag; // color flag for list command
  /**
   *  @brief The directory color.
   */
  TermColorIndex directoryColor;
  /**
   *  @brief The command color.
   */
  TermColorIndex commandColor;

  /**
   *  @brief For treating G4 command tree...
   */
  G4String currentCommandDir; // current command directory (absolute path)


public:
  /**
   *  @function GsimUIbash
   *  @brief Constructor for GsimUIbash.
   *  @param prompt The prompt symbol. If omitted, the default is "> ".
   */
  GsimUIbash(const G4String& prompt="> ");
  /**
   *  @function ~GsimUIbash
   *  @brief Destructor for GsimUIbash.
   */
  virtual ~GsimUIbash();


  /**
   *  @function SetNColumn
   *  @brief Set the number of columns to use.
   *  @param ncol The number of columns.
   */
  void SetNColumn(G4int ncol);
  /**
   *  @function SetPrompt
   *  @brief Set the command prompt to use.
   *  @param prompt The prompt to use.
   */
  void SetPrompt(const G4String& prompt);
  /**
   *  @function SetCurrentDirectory
   *  @brief Set the current directory.
   *  @param ccd The directory to use.
   */
  void SetCurrentDirectory(const G4String& ccd);

  // shell commands
  /**
   *  @function ShowCurrentDirectory
   *  @brief Prints the current working directory.
   */
  virtual void ShowCurrentDirectory() const;
  /**
   *  @function ListCommand
   *  @brief List the available commands.
   *  @param input The directory to use.
   *  @param candidate The command to list. If blank, all commands are listed. Defaults to "".
   *
   *  "candidate" is specified with the full path.
   */
  virtual void ListCommand(const G4String& input, 
			   const G4String& candidate="") const;

  /**
   *  @function GetCommandLine
   *  @brief Returns the command string from the current commandline.
   *  @param msg The prompt message.
   */
  virtual G4String GetCommandLine(const char* msg=0);
};


// inlines...
inline void GsimUIbash::SetNColumn(G4int ncol)
{
  nColumn= ncol;
}

inline void GsimUIbash::SetPrompt(const G4String& prompt)
{
  promptSetting= prompt;
}

inline void GsimUIbash::SetCurrentDirectory(const G4String& dir)
{
  currentCommandDir= dir;
}

inline void GsimUIbash::ShowCurrentDirectory() const
{
  G4cout << currentCommandDir << G4endl;
}

#endif
