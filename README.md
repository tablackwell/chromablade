# chromablade
A project for CSCI 437 Introduction to Game Design and Development.

### Resources
- [Simple and Fast Multimedia Library (SFML)](https://www.sfml-dev.org/)
- [CMake](wwww.cmake.org)

### Members
- Thomas Blackwell
- Louisa Doyle
- Jason Kimko
- Liang Wu

### Compile

Make a subdirectory 'Debug'. In 'Debug' type 'cmake ..' to generate a makefile.
If SFML is not installed in standard location, you will need to set the LIB and
INCLUDE environment variables. For example if SFML is installed in ~/SFML, then
you can adjust the environment variables (assuming linux and a BASH-shell) by:

export LIB=$LIB:~/SFML/lib
export INCLUDE=$INCLUDE:~/SFML/include

These environment variables are only valid in your current terminal. To make
them permanent, add the above two lines to your '~/.profile' file.

If SFML is installed, and the environment variables are correctly set, then
running 'cmake ..' from 'Debug' will produce something like:

-- The C compiler identification is GNU 4.8.5
-- The CXX compiler identification is GNU 4.8.5
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found SFML .. in /path/to/SFML/include
-- Out-source building. Build type set to: DEBUG
-- Adding executable: GameApp
-- Configuring done
-- Generating done
-- Build files have been written to: /path/to/Debug

Now that the Makefile has been succesfully generated, you can compile with 'make'.
This will produce a 'GameApp' executable that will open the game.
