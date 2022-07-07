# memoizer
## What it is 
A header-only implementetion of a class, that incapsulates memoization technic by making a proxy call to the function, it was created for.
Result of each call to particular memoizer object is stored in an individual for this object hash-table only if table doesn't already 
contain the key, that arguments produce (class hases args as a std::tuple).
## Requierments
-  C++17 and later.

-  Each parameter to the function (func) is hashable,that is can be used as a key.

```c++
T func(Args...args){...}
...
std::unorderd_map<T, Args>  //    size_t std:: struct hash<T>::operator()(const T &x) const
```

- Each parameter to the function is equality comparable.

```c++
(Args{...} == Args{...}) //    bool Args::operator==(const Args&) const
```
Optional: Googletest for testing. 

## How to get
You can just use clone(no submodules requiered) :

```bash
git clone https://github.com/artomartom/memoizer/tree/main  
```
Or checkout only all_in_one header file, without all the examples and tests

```bash
# works for  bash and powershell 
git clone "https://github.com/artomartom/memoizer" --no-checkout  --depth 1
cd memoizer
git sparse-checkout init
echo /source/all_in_one/ >> ".\.git\info\sparse-checkout" 
git checkout "origin/main"
```

## How to use

Take a pure function
> **_NOTE:_**   https://en.wikipedia.org/wiki/Pure_function

>   In computer programming, a pure function is a function that has the following properties:
>   -   the function return values are identical for identical arguments (no variation with local static variables, non-local variables, mutable reference arguments or input streams), and
>   
>   -   the function application has no side effects (no mutation of local static variables, non-local variables, mutable reference arguments or input/output streams).
>   
# License
    \(-__-)/

## PS
Your issues, pulls, recomendations and/or any other form of feedback is welcome.:smiley:

