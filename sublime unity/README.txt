Edit: you can do this all internally within Unity now. or maybe you always could

Edit -> Preferences...

External Tools tab

Set External Script Editor to your Sublime Text executable

Set External Script Editor Args to `"$(File)":$(Line)`

===

Just some quick changes by Jacob Pennock to change the default editor
to Sublime Text 2 (64-bit on Windows). Original readme below


Unity External Script Editor Helper 1.0

Copyright (c) 2011, Anomalous Underdog
All rights reserved.


Unity (as of version 3.4) unfortunately doesn't pass the line number to other script editors except whichever is designated as the built-in editor (which is MonoDevelop as of Unity version 3.4).

So, we have this program which fakes itself as MonoDevelop but in reality will pass the arguments from Unity into a script editor of your choosing, complete with the line number so that your script editor will jump to the proper line number.


TO USE:

1. Edit the wrapper.ini:
1.1 Change Application to whatever script editor you plan on using. The default is using Notepad++ on a 32-bit Windows system
1.2 Change Arguments to however your script editor takes in a file and linenumber when opened. *file* will be replaced with the actual file string and *linenumber* will be replaced with the actual line number. The default is configured for Notepad++

2. Copy wrapper.ini and UnityExternalScriptEditorHelper.exe to where your Unity MonoDevelop.exe resides. (C:\Program Files\Unity\MonoDevelop\bin for example)
2.1 Create a backup of your current MonoDevelop.exe or rename it to another filename
2.2 Rename UnityExternalScriptEditorHelper.exe into MonoDevelop.exe

3. Set Unity to use the built-in editor.

4. Try it, it should now open your specified scripting editor at the proper line number!
