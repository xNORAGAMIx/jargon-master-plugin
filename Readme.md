```
clang-tidy -list-checks \
  -load ./build/libMyClangTidyPlugin.so \
  -checks="hscaa-*"
```

```
clang-tidy test.cpp \
  -load ./build/libMyClangTidyPlugin.so \
  -checks="hscaa-*,hscai-*"
```