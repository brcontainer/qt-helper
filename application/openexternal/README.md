Prevent freeze (or crash) apps with `QDesktopServices::openUrl`

Usage:
```cpp
openExternal::local("C:", this);//Open default file manager (explorer in window and Finder in Mac)
openExternal::url("http://github.com", this); //Open default web-browser
```
