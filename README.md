# memoizer
## What it is 
A header-only implementetion of a class, that incapsulates memoization technic by making a proxy call to the function, it was created for.
Result of each call to particular memoizer object is stored in an individual for this object hash-table only if table doesn't already 
contain the key, that arguments produce (class hases args as a std::tuple).
## Requierments
1.  C++17 and later.

2.  Each parameter to the function (func) is hashable,that is can be used as a key.

```c++
T func(Args...args){...}
...
std::unorderd_map<T, Args>//    size_t std:: struct hash<T>::operator()(const T &x) const
```

3. Each parameter to the function is equality comparable.

```c++
(Args{...}==Args{...})//    bool Args::operator==(const Args&) const
```

## How to use


## Your Feetback
