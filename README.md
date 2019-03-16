# Introduction 

This is a small piece of C++ 11 library code implementing the well known **Singleton Design Pattern**. 

With C++ templates, the usually proposed and widely discussed solution is so simple, that it would not justify even this project. Such simple solution looks as follows:

    // template class to provide singleton functionality
    template<typename T> class Singleton
    {
        public: static T* get() 
        { 
          static T thesingleton; 
          return &thesingleton; 
        }
    };
 
    // sample class implementing singleton
    class Sample : public Singleton<Sample>
    {
        // implementation of sample class...
    };

    // usage:
    Sample* sample= Sample::get();
           
This works fine in general unless you start accessing the same singleton objects 
from within different Windows DLLs or a Windows DLL and the main executable. 
Although running in one process, the singletons retrieved are singletons "per DLL/Executable". 
The reason for this is simply spoken that Windows DLLs dispose of an own data segment for global 
variables. This is different with shared libraries under GNU/Linux or macOS, which by design behave 
exactly like statically linked libraries do. 

# The Solution

The code provided with this repository creates true singleton objects, even when 
Windows OS DLLs are used. 
This is achieved by creating a static (global) hash map only once and collecting all singletons therein. 
The C++ runtime type information struct **std::type_info** is used as the key to the singletons in 
the hash map. Note that the hashmap is searched only once per DLL/main executable.

As a side effect, the singletons created can be "dumped out" for debug purposes by iterating 
the hash table. A corresponding debug method is provided with this implementation.

As this approach imposes some overhead in respect to code size, the code includes an alternative 
implementation that omits the use of the hash map.
 
The code selects the "right" implementation depending on the platform it is compiled on. 
In addition, the implementation can be forced to one of the two modes, using compiler symbol 
**ALIB_FEAT_SINGLETON_MAPPED_ON**. 
This is may be used for example:
- to switch the hash-map usage off for windows projects that do not use a DLL.
- to switch the hash-map usage with GNU/Linux platform, to allow listings of all 
  instantiations of singletons.   

# Restrictions / Penalties

- The singleton class needs to have a default (parameterless) constructor. 
  (This might be overcome with a simple extension of the class, but is not implemented here) 
- The singleton class is virtual and hence all derived classes become virtual. 
  (This is needed for having a virtual destructor.)   
- There is a marginal performance penalty in comparison to more simple implementations of the 
  singleton design pattern: Each *'code entity'* (DLL or main executable) needs to retrieve a 
  singleton, which was potentially already created by another code entity, **once**. 
  In other words, the first request for a specific singleton incorporates two small performance 
  penalties for 
  1. setting and releasing a thread lock (mutex)
  2. retrieving the singleton or inserting the singleton if not retrieved.
- The memory penalty is also quite minimal and imposed by the creation of a static hash table, 
  which holds a pointer to each Singleton.
- Upon exit of the process, programmers might want to explicitly free the hash table to avoid the 
  detection of memory leaks by metrics tools like [Valgrind](http://valgrind.org/). 
  (Otherwise this can be omitted, as the memory is cleaned by the OS probably much faster when 
  a process exits).
- In general, it is advised to think twice before using the singleton design pattern. 
  Often, this is considered bad code design. However, there can be very good reasons for having 
  singletons in software.
  And do not be frustrated if "very wise people" tell you that you must never use a singleton. 
  Your answer to them is: Each and every created instance of a virtual C++ class contains a 
  pointer to a singleton, namely the [vtable](https://en.wikipedia.org/wiki/Virtual_method_table)!


# Documentation
This code is an extraction from some bigger library (see below). 
Use [this deep link](https://alexworx.github.io/ALib-Class-Library/alib_mod_singletons.html) into the 
documentation of [ALib for C++](https://alexworx.github.io/ALib-Class-Library/index.html).

# Changelog / Version History
Changes are documented in [ALib for C++](https://alexworx.github.io/ALib-Class-Library/index.html) 
library's [changelog](https://alexworx.github.io/ALib-Class-Library/alib_changelog.html). 

# Requirements and Usage

**Requirements to use the code are:**

* C++ compilers supporting C++11 language level. Compilers tested are
  - GNU C++ V. 8.2.1 
  - Clang V. 7.0.1 
  - Microsoft Visual Studio 2017, V. 15.9.4
* The code was tested under
  - GNU/Linux 32 and 64 bit
  - Microsoft Windows 32 and 64 bit
  - Mac OSX 64 bit
* The code compiles without warnings on maximum warning levels.   

**Usage options:**

1. Copy the code into your project, make changes as you wish 
   (rename the types, adopt your own namespace, improve, etc.).
2. Compile the code to a library and add it to your project.
3. Forget about this tiny repository and read next section! 
   
# ALib Main Distribution 
The code found in this repository represents a so called *"ALib Module"*, which means it is an 
extracted subset of [ALib for C++](https://alexworx.github.io/ALib-Class-Library/index.html). 
The effort to extract this module and make its sources available as a "stand alone" project 
is made to allow full source inclusion of this tiny singleton thing in a user's project. 
This way, compilation and deployment dependencies get eliminated. 
Also, updates are not automatically deployed into a user's project source tree, what protects 
from possible unwanted effects of such updates. 
Finally, a user might modify the sources and maintain a separate version, with no future update 
from the original.     

**Note:**
Of-course, the aforementioned reasons for extracting the code to this tiny project are 
considered disadvantages in many scenarios. The choice is yours... 


# Testing
The software is duly tested with Unit Tests. However, those are not part of this distribution.

# Alternatives
The following alternatives may be worth mentioning:

- Probably the class code given as a sample above: 
  This works well on GNU/Linux (even with shared libraries) and also with monolithic 
  Windows OS executables. 
- Many code sample repositories, programming books, design pattern collections etc. are offering 
  implementations of the Singleton Design Pattern. But be careful: most of these solutions do 
  not work with windows DLLs!
- Create an abstract virtual singleton "interface" class and implement its virtual abstract method 
  in each class you want to equip with a singleton. 
  Return a private static instance of itself which you add as a member. 
  - Advantage: No need for having a hash map
  - Disadvantage: No templated approach. 
    In [ALib for C++](https://alexworx.github.io/ALib-Class-Library/index.html), we are using the 
    Singleton nested in another template class which is inherintly instantiated by a user's code. 
    Therefore, this was no option for us, because it would impose the need to manually add static 
    specialized template object instances to be fed to the linker with each new template specialization.
- [Loki](https://sourceforge.net/projects/loki-lib/)  Design Pattern Library. 
  (It seems to be DLL-safe, but we have not tested that.)








