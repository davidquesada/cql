cql
===

A silly library that allows you to embed SQL queries in C++ code

Creating Tables
===============

Creating tables with cql is easy, and very closeley resembles standard SQL syntax for creating a table. The only exception is the need to include an additional keyword 'SCHEMA'.

```cpp
int main(int argc, const char **argv)
{
    CREATE TABLE Classes SCHEMA
    (
        id INTEGER,
        department CHAR(10),
        number INTEGER,
        title CHAR(120),
        
        difficulty DOUBLE
    );
    
    DROP TABLE Classes;
}
```

Or you can also create global tables:

```cpp
CREATE TABLE Points SCHEMA ( x DOUBLE, y DOUBLE );

int main(int argc, const char **argv)
{
    loadPoints();
    computeStuffWithPoints();
    
    DROP TABLE Points;
}
```

INSERT Operations
=================

Insert operations in cql are similar to those in SQL, except they are slightly more restrictive in syntax and, like CREATE TABLE operations, require an additional keyword, in this case ATTRIBUTES.

```cpp
void loadPoints()
{
    INSERT INTO Points ATTRIBUTES(x, y) VALUES (10, 25);
    INSERT INTO Points ATTRIBUTES(y, x) VALUES (30, -51);
}

void loadEECS()
{
    INSERT INTO Classes ATTRIBUTES(id, department, number) VALUES (1, "EECS", 370);
    INSERT INTO Classes ATTRIBUTES(id, title, difficulty, department, number)
        VALUES (2, "Data Structures & Algorithms", 2.81, "EECS", 281);
    INSERT INTO Classes ATTRIBUTES(id, department, number, title)
        VALUES (3, "MATH", 417, "Matrix Algebra");
}
```

SELECT Queries
==============

TODO: Document this.

UPDATE Operations
=================

are currently not implemented.

DELETE Operations
=================

are currently not implemented.

Supported Types
===============

Currently, the following types are supported for columns in tables:
- INTEGER
- CHAR(n)
- CHAR 
- DOUBLE

The following types will be added "soon":
- FLOAT
- ENUM

Compiler Support
================

This project (ab)uses several C++11 features and may not work in compilers with poor support for C++11 (*Visual Studio...*).
I currently develop this project in GCC 4.8, and am 80% sure it will work in GCC 4.7, but I'll need to test that.
I don't know about clang. I hear that has better support for C++11 (and also generates MB's less of template error messages, but who really wants that?)

Caveats (Some to be fixed later)
================================

- The CREATE TABLE command depends on (and increments twice) the __COUNTER__ macro. The value of __COUNTER__ must be even before the CREATE TABLE command is called. If you aren't using the __COUNTER__ macro in your code, then you don't need to worry about this.
- Be careful when printing out tables / result sets containing CHAR typed columns. Currently, attempting to print a result set containing a column of type CHAR (not of type CHAR(n) ) is equivalent to printing a char* starting at the location in memory of the first (and only) character and may (usually) result in printing extraneous characters. This will be fixed and shouldn't be a problem 
- UPDATE and DELETE aren't implemented yet, but who really uses those?
- The performance and code quality aren't great, but who really needs those?


