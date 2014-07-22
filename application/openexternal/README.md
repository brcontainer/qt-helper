Prevent freeze (or crash) apps with `QDesktopServices::openUrl`

Usage:
```cpp
openExternal::local("C:", this);//Open default file manager ("explorer" in Windows and "Finder" in MacOSX)
openExternal::local("C:/file.txt", this);//Open default file manager (if explorer.exe select/highlight file - like this `explorer /select,C:\file.txt`)
openExternal::url("http://github.com", this); //Open default web-browser
```
