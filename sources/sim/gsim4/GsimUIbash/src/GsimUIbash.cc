//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// Id: GsimUIbash.cc,v 1.1.1.1 2005/09/21 14:11:07 nanjo Exp 
// GEANT4 tag Name:  
//
// $Id: GsimUIbash.cc,v 1.2 2005/12/06 14:07:10 nanjo Exp $
//
// $Log: GsimUIbash.cc,v $
// Revision 1.2  2005/12/06 14:07:10  nanjo
// ommit function argument variable at uibash_completion to stop warning in make
//
// Revision 1.1  2005/11/01 15:15:55  yamaga
// New MC baseed on Geant4 by Nanjo-san.
//

#include "GsimUIbash/GsimUIbash.h"
#include "GsimPersistency/GsimPersistencyManager.h"

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "G4UIcommandTree.hh"
#include "G4StateManager.hh"
#include "G4UIcommandStatus.hh"
#include "G4UIArrayString.hh"
#include "G4VBasicShell.hh"

// terminal color string
static const G4String strESC= '\033';
static const G4String TermColorString[8] ={ 
  strESC+"[30m", strESC+"[31m", strESC+"[32m", strESC+"[33m", 
  strESC+"[34m", strESC+"[35m", strESC+"[36m", strESC+"[37m"
};

char* dupstr (const char *s);

char* command_generator (const char* text, int state);
char** uibash_completion (const char *text,int start, int end);
char* uibash_completion_function (const char *text, int state );

GsimUIbash* GsimUIbash::fUIbash = NULL;

GsimUIbash* GsimUIbash::GetUIbash() {
  static GsimUIbash theUtil;
  if(!fUIbash) fUIbash = &theUtil;
  return fUIbash;
}

///////////////////////////////////////////////////////////////////
GsimUIbash::GsimUIbash(const G4String& prompt)
  : promptSetting(prompt), promptString(""), nColumn(80),  
    lsColorFlag(FALSE), directoryColor(BLACK), commandColor(BLACK),
    currentCommandDir("/")
///////////////////////////////////////////////////////////////////
{

  char* env = std::getenv("HOME");
  G4String shome = G4String(env);

  histfile = shome;
  histfile += "/.g4hist";
  std::string line;
  int state = read_history(histfile.c_str());
  if(state!=0) {
    write_history(histfile);
  }
  rl_attempted_completion_function = uibash_completion;
  //rl_completion_entry_function = uibash_completion_function;
  
}

/////////////////////////
GsimUIbash::~GsimUIbash()
/////////////////////////
{
  write_history(histfile.c_str());
  history_truncate_file(histfile.c_str(),500);
}

/////////////////////////////
void GsimUIbash::MakePrompt(const char* msg) 
/////////////////////////////
{
  if(promptSetting.length()<=1) {
    promptString= promptSetting;
    return;
  }

  promptString="";
  G4int i;
  for(i=0; i<G4int(promptSetting.length())-1; i++){
    if(promptSetting[(size_t)i]=='%'){
      switch (promptSetting[(size_t)(i+1)]) {
      case 's':  // current application status
	{
           G4String stateStr;
           if(msg)
           { stateStr = msg; }
           else
           {
	     G4StateManager* statM= G4StateManager::GetStateManager();
	     stateStr= statM-> GetStateString(statM->GetCurrentState());
           }
	   promptString.append(stateStr);
	   i++;
	}
        break;
      case '/':  // current working directory
	promptString.append(currentCommandDir);
	i++;
        break;
      default:
	promptString.append(G4String(promptSetting[(size_t)i]));
        break;
      }           
    } else {
      promptString.append(G4String(promptSetting[(size_t)i]));
    }
  }

  // append last chaacter
  if(i == G4int(promptSetting.length())-1) 
    promptString.append(G4String(promptSetting[(size_t)i]));
}


// --------------------------------------------------------------------
//      G4command operations
// --------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////
G4UIcommandTree* GsimUIbash::GetCommandTree(const G4String& input) const
////////////////////////////////////////////////////////////////////////
{
  G4UImanager* UI= G4UImanager::GetUIpointer();

  G4UIcommandTree* cmdTree= UI-> GetTree();  // root tree

  G4String absPath= input; // G4String::strip() CONST !!
  absPath= GetAbsCommandDirPath(absPath.strip(G4String::both));

  // parsing absolute path ...
  if(absPath.length()==0) return NULL;
  if(absPath[absPath.length()-1] != '/') return NULL; // error??
  if(absPath=="/") return cmdTree;

  for(G4int indx=1; indx<G4int(absPath.length())-1; ) {
    G4int jslash= absPath.index("/", indx);  // search index begin with "/" 
    if(jslash != G4int(G4String::npos)) {
      if(cmdTree != NULL)
        cmdTree= cmdTree-> GetTree(G4String(absPath(0,jslash+1)));
    }
    indx= jslash+1;
  }

  if(cmdTree == NULL) return NULL;
  else return cmdTree;
}

//////////////////////////////////////////////////////////////////////
G4String GsimUIbash::GetAbsCommandDirPath(const G4String& apath) const
//////////////////////////////////////////////////////////////////////
{
  if(apath.empty()) return apath;  // null string

  // if "apath" does not start with "/", 
  //   then it is treared as relative path
  G4String bpath= apath;
  if(apath[(size_t)0] != '/') bpath= currentCommandDir + apath;

  // parsing...
  G4String absPath= "/";
  for(G4int indx=1; indx<=G4int(bpath.length())-1; ) {
    G4int jslash= bpath.index("/", indx);  // search index begin with "/"
    if(jslash != G4int(G4String::npos)) {
      if(bpath(indx,jslash-indx) == ".."){  // directory up
        if(absPath.length() >=1) {
          absPath.remove(absPath.length()-1);  // remove last  "/"
          G4int jpre= absPath.last('/');
          if(jpre != G4int(G4String::npos)) absPath.remove(jpre+1);
        }
      } else if(bpath(indx,jslash-indx) == "."){  // nothing to do
      } else { // add
        if( !(jslash==indx && bpath(indx)=='/') ) // truncate "////"
          absPath+= bpath(indx, jslash-indx+1);
          // better to be check directory existence. (it costs!)
      }
    } else { // directory ONLY (ignore non-"/" terminated string)
    }
    indx= jslash+1;
  }
  return  absPath;
}


////////////////////////////////////////////////////////////////////
G4String GsimUIbash::GetCommandPathTail(const G4String& apath) const
////////////////////////////////////////////////////////////////////
{   // xxx/xxx/zzz -> zzz, trancate /// -> /
  if(apath.empty()) return apath;

  G4int lstr= apath.length();

  // for trancating "/"
  G4bool Qsla= FALSE;
  if(apath[(size_t)(lstr-1)]=='/') Qsla= TRUE;

  // searching last '/' from tail
  G4int indx= -1;
  for(G4int i=lstr-1; i>=0; i--) {
    if(Qsla && apath[(size_t)i]!='/') Qsla= FALSE; // break "/" flag!!
    if(apath[(size_t)i]=='/' && !Qsla) {
      indx= i;
      break;
    } 
  }

  if(indx==-1) return apath;  // not found

  if(indx==0  && lstr==1) { // "/"
    G4String nullStr;
    return nullStr;
  } else {  
    //G4String newPath= apath(indx+1,lstr-indx-1); 
    G4String newPath= apath;
    newPath= newPath(indx+1,lstr-indx-1);
    return newPath;
  }
}

// --------------------------------------------------------------------
//      shell commands
// --------------------------------------------------------------------
/////////////////////////////////////////////////////////////
void GsimUIbash::ListCommand(const G4String& dir, 
			     const G4String& candidate) const
/////////////////////////////////////////////////////////////
{
  // specified directpry
  G4String input= dir; // ...
  input= input.strip(G4String::both);

  // command tree of "user specified directory"
  G4String vpath= currentCommandDir;
  G4String vcmd;

  G4int len= input.length();
  if(! input.empty()) {
    G4int indx= -1;
    for(G4int i=len-1; i>=0; i--) { // search last '/'
      if(input[(size_t)i]=='/') {
        indx= i;
        break;
      }   
    }
    // get abs. path
    if(indx != -1) vpath= GetAbsCommandDirPath(input(0,indx+1));
    if(!(indx==0  && len==1)) vcmd= input(indx+1,len-indx-1); // care for "/"
  }

  // check "vcmd" is directory?
  G4String inputpath= vpath+vcmd;
  if(! vcmd.empty()){
    G4String tmpstr= inputpath + "/";
    if(GetCommandTree(tmpstr) != NULL) {
      vpath= tmpstr;
      vcmd= "";
    }
  }
      
  // check "vpath" directory exists?
  G4UIcommandTree* atree= GetCommandTree(vpath);  
  if(atree == NULL) {
    G4cout << "<" << input << ">: No such directory" << G4endl;
    return;
  }

  // list matched directories/commands
  G4String stream;
  G4bool isMatch= FALSE;

  G4int Ndir= atree-> GetTreeEntry();
  G4int Ncmd= atree-> GetCommandEntry();
  if(Ndir==0 && Ncmd==0) return;  // no contents
  
  // directory ...
  for(G4int idir=1; idir<=Ndir; idir++) {
    if(idir==1 && lsColorFlag) stream+= TermColorString[directoryColor];
    G4String fpdir= atree-> GetTree(idir)-> GetPathName();
    // matching test
    if(candidate.empty()) { // list all
      if(vcmd=="" || fpdir==inputpath) {
	stream+= GetCommandPathTail(fpdir); stream+= "  ";
	isMatch= TRUE;
      }
    } else { // list only matched with candidate
      if( fpdir.index(candidate, 0) == 0) {
	stream+= GetCommandPathTail(fpdir); stream+= "  ";
      }
    }
  }
  
  // command ...
  for(G4int icmd=1; icmd<=Ncmd; icmd++){
    if(icmd==1 && lsColorFlag) stream+= TermColorString[commandColor];
    G4String fpcmd= atree-> GetPathName() +
             atree-> GetCommand(icmd) -> GetCommandName();
    // matching test
    if(candidate.empty()) { // list all
      if(vcmd=="" || fpcmd==inputpath) {
	stream+= GetCommandPathTail(fpcmd); stream+= "*  ";
	isMatch= TRUE;
      }
    } else {  // list only matched with candidate
      if( fpcmd.index(candidate, 0) == 0) {
	stream+= GetCommandPathTail(fpcmd); stream+= "*  ";
      }
    }
  }
  
  // waring : not matched
  if(!isMatch && candidate.empty()) 
    G4cout << "<" << input 
	   << ">: No such directory or command" << std::flush;

  // display
  G4UIArrayString arrayString(stream);
  arrayString.Show(nColumn);
}

G4String GsimUIbash::GetCommandLine(const char* msg) {

  
  G4String newCommand;

  MakePrompt(msg);
  char* buffer = readline(promptString.c_str());
  
  if(buffer != 0) {
    if (buffer[0] != '\0') {
      add_history(buffer);
    }
  }
  newCommand = buffer;
  free(buffer);
  
  if (!G4cin.good()) {
    G4cin.clear(); 
    newCommand= "exit";
    return newCommand;
  }
  newCommand = newCommand.strip(1,'\r'); // fix for odd behavior on Windows

  
  if(newCommand!="") {
    GsimPersistencyManager* persistencyManager
      = GsimPersistencyManager::getPersistencyManager();
    persistencyManager->readCommand(newCommand.data());
  }

  return newCommand;
}





// 

//   static int obarray_idx, text_len;
//   if ( text[0] == '\0' ) return (char *)NULL; /* Ignore tab after whitespace */
//   if ( !state ) {
//     obarray_idx = 0;
//     text_len = strlen(text);
//   }
//   while ( obarray_idx < 5 ) {
//     char * name=0;
//     sprintf(name,"is%d",obarray_idx);
//     obarray_idx++;
//     return dupstr(name);

//   }
//   return (char *)NULL;
// }



char** uibash_completion (const char *text,int start, int ) {

  char ** matches = (char **)NULL;

  if (start == 0)  
    matches = rl_completion_matches (text, command_generator);

  return (matches);

}


char* command_generator (const char* text, int state) {
  //state -> # of match
  // start from 0
  
  GsimUIbash* fUIbash = GsimUIbash::GetUIbash();
  static int  list_index;
  static int NumOfMatch;
  static G4String lastdir;
  static bool isDir;
  
  if (!state) {
    list_index = 1;
    NumOfMatch = 0;
  }
  
  // inputting string
  G4String input= G4String(text).strip(G4String::leading);

//   // target token is last token
//   G4int jhead= input.last(' ');

//   if(jhead != G4int(G4String::npos)) {
//     input.remove(0, jhead);
//     input= input.strip(G4String::leading);
//   }
  
//   // command tree of "user specified directory"  
  G4String vpath= fUIbash->GetCwd();
  G4String vcmd;
  
  G4int len= input.length();
  if(!input.empty()) {
    G4int indx= -1;
    for(G4int i=len-1; i>=0; i--) {
      if(input(i)=='/') {
	indx= i;
	break;
      }   
    }
    // get abs. path
    if(indx != -1) vpath= fUIbash->GetAbsCommandDirPath(input(0,indx+1));  
    if(!(indx==0  && len==1)) vcmd= input(indx+1,len-indx-1);  // care for "/"
  }
  
  G4UIcommandTree* atree= fUIbash->GetCommandTree(vpath);
  if(atree != NULL) {
    G4String stream, strtmp;
    G4String inputpath= vpath+vcmd;
    int Ndir= atree-> GetTreeEntry();
    int Ncmd= atree-> GetCommandEntry();
    
    while(list_index <= Ndir) {
      // directory ...
      G4String fpdir= atree-> GetTree(list_index)->GetPathName();
      lastdir = fpdir;
      list_index++;
      // matching test
      if( fpdir.index(inputpath, 0) == 0) {
	isDir=true;
	NumOfMatch++;
	return dupstr(fpdir.c_str());
      }
    }
    
    while(list_index <= Ndir+Ncmd) {
      // command ...
      G4String fpcmd= atree-> GetPathName() +
	atree-> GetCommand(list_index-Ndir) -> GetCommandName();
      list_index++;
      // matching test
      if( fpcmd.index(inputpath, 0) ==0) {
	isDir=false;
	NumOfMatch++;
	return dupstr(fpcmd.c_str());
      }
    }
    
  }

  //real directory search
  
  return ((char *)NULL);
}

char * uibash_completion_function(const char *text, int state ) {
  
  //state -> # of match
  // start from 0
  
  GsimUIbash* fUIbash = GsimUIbash::GetUIbash();
  static int  list_index;
  static int NumOfMatch;
  bool isDir = false;
  
  
  if (!state) {
    list_index = 1;
    NumOfMatch = 0;
  }
  
  // inputting string
  G4String input= G4String(text).strip(G4String::leading);
  
  //   // target token is last token
  //   G4int jhead= input.last(' ');
  
  //   if(jhead != G4int(G4String::npos)) {
  //     input.remove(0, jhead);
  //     input= input.strip(G4String::leading);
  //   }
  
  //   // command tree of "user specified directory"  
  G4String vpath= fUIbash->GetCwd();
  G4String vcmd;
  
  G4int len= input.length();
  if(!input.empty()) {
    G4int indx= -1;
    for(G4int i=len-1; i>=0; i--) {
      if(input(i)=='/') {
	indx= i;
	break;
      }   
    }
    // get abs. path
    if(indx != -1) vpath= fUIbash->GetAbsCommandDirPath(input(0,indx+1));  
    if(!(indx==0  && len==1)) vcmd= input(indx+1,len-indx-1);  // care for "/"
  }

  G4UIcommandTree* atree= fUIbash->GetCommandTree(vpath);
  if(atree != NULL) {
    
    
    
    G4String stream, strtmp;
    G4String inputpath= vpath+vcmd;
    int Ndir= atree-> GetTreeEntry();
    int Ncmd= atree-> GetCommandEntry();


    
    while(list_index <= Ndir) {
      // directory ...
      G4String fpdir= atree-> GetTree(list_index)->GetPathName();
      list_index++;
      // matching test
      if( fpdir.index(inputpath, 0) == 0) {
	isDir=true;
	NumOfMatch++;
	return dupstr(fpdir.c_str());
      }
    }
    
    while(list_index <= Ndir+Ncmd) {
      // command ...
      G4String fpcmd= atree-> GetPathName() +
	atree-> GetCommand(list_index-Ndir) -> GetCommandName();
      list_index++;
      // matching test
      if( fpcmd.index(inputpath, 0) ==0) {
	NumOfMatch++;
	return dupstr(fpcmd.c_str());
      }
    }
    
  }

  //real directory search
  
  return ((char *)NULL);
  
}

char* dupstr (const char *s)
{
  char *r = new char[(strlen (s) + 1)];
  strcpy (r, s);
  return (r);
}



