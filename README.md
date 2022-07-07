# memorizer
## What it is 
A header-only implementation of a class, that encapsulates a mechanism for applying memorization technic by making a proxy call to the function, it was created for.
The result of each call to a particular memorizer object is stored in an individual for this object hash-table only, if the table doesn't already 
contain the key, that arguments produce (class hases args as a std::tuple).
## Requirements
-  C++17 and later.

-   Each parameter to the function (func) is hashable, that is can be used as a key.

```c++
T func(Args...args){...}
...
std::unorderd_map<T, Args>  //    size_t std:: struct hash<T>::operator()(const T &x) const
```

-   Each parameter to the function is equality comparable.

```c++
(Args{ } == Args{ }) //    bool Args::operator==(const Args&) const
```
Optional: Googletest for testing. 

## How to get
You can just use clone( no submodules required) :

```bash
git clone https://github.com/artomartom/memorizer/tree/main  
```
Or checkout only ./source/all_in_one/ header file, without all the examples and tests

```bash
# works for  bash and powershell 
git clone "https://github.com/artomartom/memorizer" --no-checkout  --depth 1
cd memorizer
git sparse-checkout init
echo /source/all_in_one/ >> ".\.git\info\sparse-checkout" 
git checkout "origin/main"
```

## How to use

```c++
//take a  pure function, taking non-zero number of args with return type not beeing void 
int compute_some_real_quick(int a,string s )    
{
    ...
};
...
//... and create memorizer
Memorizer<compute_some_real_quick> mem{};
//now you can call it!
mem(1,"hello");
mem(-123,"world");
```
(see /example/ for more details)

> **_NOTE:_**   In computer programming, a pure function is a function that has the following properties:
>-   the function return values are identical for identical arguments (no variation with local static variables, non-local variables, mutable reference arguments or input streams), and
>   
>-   the function application has no side effects (no mutation of local static variables, non-local variables, mutable reference arguments or input/output streams).
>(see also: https://en.wikipedia.org/wiki/Pure_function)


## PS
Your issues, pulls, recommendations and/or any other form of feedback is welcome.:smiley: