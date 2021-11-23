starlib
---

This project contains library StarLib, that defines set of tools for numerical
integration of particle motion, e.g. planets or stars.

# Installation

## Requirements:

* premake5
* gtest
* yaml-cpp

```bash
git clone https://github.com/perkun/starlib.git
cd starlib
premake5 gmake
make
make config=release
```

The last command compiles the optimized code without debugging symbols.

# Tests

Go to `tests` folder and run

```bash
./run_all_tests.sh
```

Everything should be green :)



# Usage

Take a look at the **Example** sub-project. Basic simulation is described
there in comments. Documentation is on my list of TODOs ...


# Define your own programs

You can install the library in your system (by hand :] ) or, just add another
sub-project in the `starlib` folder. Create a folder and a `src` sub-folder, then
copy `premake5.lua` from other project (e.g. `passing_star`) and edit the first
line, containing project name. Then, add new project to the main `premake5.lua`
file at the bottom. Run `premake5 gmake & make`. Done.
