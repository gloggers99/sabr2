# sabr2 (wip)
## whats sabr2?
sabr2 is a remake of an old build system I wrote in C++ [sabr](https://github.com/gloggers99/sabr), it was very unoptomized and not very "correct".. in the way compilers and build systems should work. Anyways im putting my years of proper learning and knowledge of C back into a remake.
## features? (all coming soon)
- [X] Basic project detailing and structure
- [ ] Building
- [ ] Tests
- [ ] Distributing
- [ ] Library handling/Linking
- [ ] CMakeLists.txt dummy file generation so clion and other IDE's stop complaining about adding things to projects
## usage? (poc)
`/your/project/root/build.sabr`:
```
cc(autodetect)
cc_options(-std=c89 -O3)

target(sabr main.c sabr.c sabr_builtins.c)
```
then run `sabr` or `sabr.exe` on windows.