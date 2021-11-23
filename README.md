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


# Usage

Thake a look at the **Example** sub-project. Basic simulation is described
there in comments. Documentation is on my list of TODOs ...
