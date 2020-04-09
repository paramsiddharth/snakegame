# Snake Game
The snake is controlled by the WASD keys. The source files are written in C++ and are not portable across different operating system environments. 

Each filename (excluding the extension .cpp) sufficed by *_win* is to be compiled and run in Windows (utilizing the DOS terminal) since it uses **Sleep()** from the **windows.h** header file., while each sufficed *_unix* must be compiled and run in a UNIX OS e. g. Linux and Mac[hintosh] (utilizing the UNIX terminal) since it would use **nanosleep()** from the **unistd.h** header file.

The source files marked **HQ** utilize wide characters (`wchar_t`), which not all consoles might support, while the source files not marked **HQ** utilize simple ASCII characters.
