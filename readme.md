LLD interview preparations

Design Pattern Directory Structure - 
1. Design Pattern folder name
    - Implementation with comments and use for notes
    - User folder
        - Kachra Implementation bina comment k push maro, interview ni niklega shayad :fire:


Using googletest with nvim in this repo with MacOs

With macOs nvim doesnt resolve googletest on its own, to provide path for it create a symbolic link to compile_commands.json thats created with cmake
How to create it?
```
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```

The symlink should be added to the root of the project, root can be seen in :LspInfo run from a c++ project file.
```
ln -s compile_commands.json <build_path>
```
