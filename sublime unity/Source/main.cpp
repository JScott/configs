//
// The Unity External Script Editor Helper is distributed under the New BSD license:
//
// Copyright (c) 2011, Anomalous Underdog
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Anomalous Underdog nor the names of the Unity External
//       Script Editor Helper's contributors may be used to endorse or promote
//       products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY ANOMALOUS UNDERDOG ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL ANOMALOUS UNDERDOG BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <windows.h>

#include "inih/cpp/INIReader.h"

//#define DEBUG_ARGUMENTS

using namespace std;

//
// Unity gives MonoDevelop.exe these arguments:
//
// 0: C:\Program Files\Unity\Editor\..\MonoDevelop\bin\MonoDevelop.exe
// 1: --nologo
// 2: E:\path\to\project\UnityProject.sln
// 3: E:\path\to\project\script\script.cs;59
//
// its the 4th one we're interested in
//

vector<string> &split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    return split(s, delim, elems);
}

int main(int argc, char** argv)
{
//#define DEBUG_CALL
#ifdef DEBUG_CALL
    string cmdt = "C:/Program Files/Notepad++/notepad++.exe";
    string argt = "\"C:\\log.txt\" -n2";

    ShellExecute(NULL, "open", cmdt.c_str(), argt.c_str(), NULL, TRUE);

    return 0;
#endif

#ifdef DEBUG_ARGUMENTS
    ofstream log;
    log.open("C:/log.txt");
#endif


#ifdef DEBUG_ARGUMENTS
    log << "Unity External Script Editor Helper" << endl;
    log << endl;
    log << "argc: " << argc << endl;
    for (int n = 0; n < argc; ++n)
    {
        log << n << ": " << argv[n] << endl;
    }
    log << endl;
#endif

    if (argc < 1)
    {
        return 0;
    }

    string dir = argv[0];
    int lastslash = dir.find_last_of("/\\");
    dir = dir.substr(0, lastslash+1);
#ifdef DEBUG_ARGUMENTS
    log << dir << endl;
#endif

    INIReader reader(dir + "wrapper.ini");
    if (reader.ParseError() < 0) {
#ifdef DEBUG_ARGUMENTS
        log << "Can't load 'wrapper.ini'\n";
#endif
        return 1;
    }

#ifdef DEBUG_ARGUMENTS
    log << "Got application: " << reader.Get("Settings", "Application", "") << endl;
    log << "Got argument format: " << reader.Get("Settings", "Arguments", "") << endl;
#endif


    if (argc < 4)
    {
        return 0;
    }

    string argin = argv[3];
    vector<string> args = split(argin, ';');

    if (args.size() < 2)
    {
        return 0;
    }

#ifdef DEBUG_ARGUMENTS
    log << "Got arguments:" << endl;
    log << endl;
    log << "1: " << args[0] << endl;
    log << "2: " << args[1] << endl;
#endif

    string cmd = reader.Get("Settings", "Application", "");
    string argnew = reader.Get("Settings", "Arguments", ""); //"\"" + args[0] + "\" -n" + args[1];

    int filet = argnew.find("*file*");
    argnew.replace(filet, 6, args[0]);

    int linenumt = argnew.find("*linenumber*");
    argnew.replace(linenumt, 12, args[1]);

#ifdef DEBUG_ARGUMENTS
    log << "Processed arguments:" << argnew << endl;
#endif

    ShellExecute(NULL, "open", cmd.c_str(), argnew.c_str(), NULL, TRUE);


#ifdef DEBUG_ARGUMENTS
    log.close();
#endif

    return 0;
}
