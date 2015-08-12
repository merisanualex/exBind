# exBind
Function signature elongator
***
Short story short: this allows you to "add" parameters to functions by returning a callable proxy object.

View [example.cpp](https://github.com/R3AL/exBind/blob/master/example.cpp) for a use-case.


Diagnostics
You can define one of the following macros before including 'ex_bind.hpp' to enable 'better' error messages:

+ EX_BIND_DIAGNOSTIC_STATIC_ASSERT
+ EX_BIND_DIAGNOSTIC_ENABLE_IF

I, for one, prefer the enable_if macro when using Visual Studio.
