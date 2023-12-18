Catch — C++ Automated Test Cases in Headers — is an open-source, C++ testing framework that is used in hundreds of C++ software libraries. We use it to help you test your C++ code in CS 225.

For every assignment, you can compile the test cases by running:

```
make test
```

This will usually generate a program called test, which can be run by running:

```
./test
```

If you pass all test cases, you will see a green bar and a report that shows you passed 100% of the test cases. If you fail some test cases, you may want to have Catch report and abort on the first failure. To do this, run:

```
./test -a
```

Catch will show you information about the test you failed:
```
$ ./test -a

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
test is a Catch v1.9.7 host application.
Run with -? for options

-------------------------------------------------------------------------------
createSpotlight
  Spotlight creates a completely dark pixel >200 pixels away
-------------------------------------------------------------------------------
tests/basic.cpp:46
...............................................................................

tests/basic.cpp:47: FAILED:
  REQUIRE( result.getPixel(320, 50)->l == 0 )
with expansion:
  0.5 == 0

===============================================================================
test cases: 1 | 1 failed
assertions: 5 | 4 passed | 1 failed
```

Below the first dashed line will be the name of the test (createSpotlight), a description of the purpose of the test (Spotlight creates a completely dark pixel >200 pixels away), the source of the test case (tests/basic.cpp:46), followed shortly by the test we ran inside of a REQUIRE() statement (result.getPixel(320, 50)->l == 0), and finally the value of the expression that failed (0.5 == 0).

In the context of the MP or Lab, this should provide you details about how to go about fixing your code.
