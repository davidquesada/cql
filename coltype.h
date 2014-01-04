#ifndef __COLTYPE_H_
#define __COLTYPE_H_
#include <string>
#include <utility>
#include <iostream>
using namespace std::rel_ops;

enum coltype_class
{
	CC_INTEGER,
	CC_DOUBLE,
	CC_CHAR,
};

#define DEFAULT_COL_LENGTH		0

class table;

class coltype
{
public:
	coltype(coltype_class c_);
	coltype(coltype_class c_, int len_);
	coltype(coltype &&) = default;
private:
	coltype(const coltype &) = delete;
	coltype() = delete;
		
public:
	
	std::string getDescription() const;
	
	coltype &setLength(int len);
	
	void setName(const std::string &name_);
	const std::string &getName() const;
	
	int getDataSize() const;
	int getDataOffset() const;
    int getDisplayWidth() const;
	
	void setDataOffset(int o);
	
	coltype &operator()(int newlen) { return setLength(newlen); }
	
	template<typename T>
	bool operator=(const T &val) { return (*this == val); }
	
	
	bool operator=(coltype &other);// { return false; }
	
public:
    std::string formatData(const char *data) const;
    
    template<typename T>
    int compareCurrentValue(const T& otherval)
    {
        // Default implementation that will probably work for numeric types
        return getCurrentValue<T>() - otherval; 
    }
    
    template<typename T>
    int compareCurrentValue(coltype &other)
    {
        return compareCurrentValue<T>(other.getCurrentValue<T>());
    }
    
	// Uses the column type to determine which type of comparison to use,
	// and dispatches to the appropriate template instantiation.
	int compareAgainstColumn(const coltype &other);
	
    template<typename T>
    T getCurrentValue();
	
	
	
	
	#if 0
	coltype(coltype &&other)
	:name(std::move(other.name)),
	cl(other.cl),
	length(other.length),
	dataOffset(other.dataOffset),
	ownerTable(other.ownerTable),
	
	{
		std::cout << "coltypeMoveConstructor" <<std::endl;
	}
	#endif
	
protected:
	std::string name;
	coltype_class cl;
	int length;
	
	int dataOffset;
    table *ownerTable;
    
    friend class customTable;
    friend class select_statement;
    int getPreferredDisplayWidth() const;
    
    const char *getCurrentRecord();
};

template<typename T>
T operator-(const T& val, const coltype &col)
{
    return val - col.getCurrentValue<T>();
}

template<typename T>
T coltype::getCurrentValue()
{
    const char *currentRec = getCurrentRecord();
    return *((T *)(currentRec + getDataOffset()));
}

template<typename B>
bool operator==(coltype &c, coltype &c2)
{
    return c.compareCurrentValue(c2.getCurrentValue<B>());
}
template<typename T>
bool operator==(coltype &col, const T& val)
{
    return col.compareCurrentValue(val) == 0;
}

// for joins.
bool operator==(coltype &col, const coltype &val);

template<typename T>
bool operator<(coltype &col, const T& val)
{
    return col.compareCurrentValue(val) < 0;
}

template<typename T>
bool operator<(const T& val, coltype &col)
{
    return col.compareCurrentValue(val) > 0;
}

template <class T> bool operator!= (coltype& x, const T& y) { return !(x==y); }
template <class T> bool operator>  (coltype& x, const T& y) { return y<x; }
template <class T> bool operator<= (coltype& x, const T& y) { return !(y<x); }
template <class T> bool operator>= (coltype& x, const T& y) { return !(x<y); }


#endif//__COLTYPE_H_