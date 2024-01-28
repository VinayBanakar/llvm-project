### building llvm

`mkdir build`
```
cmake -G "Ninja" -DCMAKE_C_COMPILER=$(which clang) -DCMAKE_CXX_COMPILER=$(which clang++) -S llvm -B build -DLLVM_ENABLE_PROJECTS='clang;lld;lldb' -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD="X86" -DBUILD_SHARED_LIBS=OFF -DLLVM_CCACHE_BUILD=ON -DLLVM_LINK_LLVM_DYLIB=ON
```
`ninja -j15 all`
### building compiler-rt

`mkdir build-compiler-rt; cd build-compiler-rt`
```
cmake ../compiler-rt -DLLVM_CMAKE_DIR=/usr/local/google/home/vny/Documents/llvm-project/build -DLLVM_CONFIG_PATH=/usr/local/google/home/vny/Documents/llvm-project/build/bin/llvm-config -DCOMPILER_RT_BUILD_MEMPROF=ON -DCOMPILER_RT_BUILD_Profile=ON -DCOMPILER_RT_BUILD_SANITIZERS=ON
```
`make`

#### Linking lib files to llvm lib path
```
cd build/lib/clang/18/lib/linux/
ln -s /usr/local/google/home/vny/Documents/llvm-project/build-compiler-rt/lib/linux/libclang_rt.memprof-x86_64.a libclang_rt.memprof-x86_64.a
ln -s /usr/local/google/home/vny/Documents/llvm-project/build-compiler-rt/lib/linux/libclang_rt.memprof_cxx-x86_64.a libclang_rt.memprof_cxx-x86_64.a
ln -s /usr/local/google/home/vny/Documents/llvm-project/build-compiler-rt/lib/linux/libclang_rt.profile-x86_64.a libclang_rt.profile-x86_64.a
```

### example build step
```
bin/clang++ ../../basic_bench.cc -O2 -fprofile-generate=./memprof -gmlt -fmemory-profile=memprof -fno-omit-frame-pointer -fdebug-info-for-profiling -fno-optimize-sibling-calls -m64 -Wl,-build-id -fuse-ld=lld -Wl,--no-rosegment -o basic_bench
```
For the symbolizer to work you need to add `/build/bin` to the path.
## example profdata step
```
bin/llvm-profdata show --memory --profiled-binary=hello memprof/memprof.profraw.482740
```

### debug profdata
Add printfs and debug `./llvm/lib/ProfileData/RawMemProfReader.cpp:488

### periodic dump
Shell file to build and test memprof:
`llvm/test/tools/llvm-profdata/Inputs/update_memprof_inputs.sh`
