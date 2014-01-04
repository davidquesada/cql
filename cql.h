#ifndef __CQL_H_
#define __CQL_H_

#if 1
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include "coltype.h"
#include <utility>
#include <memory>
#include <ostream>
#include <functional>
#endif

/// OPTIONS

/// Compiler compatibility

// If your compiler doesn't support alignas(x). e.g. GCC <4.8
//#define NO_ALIGNAS


/// UTILITIES

#define PP_ARG_N( \
          _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10, \
         _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
         _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
         _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
         _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
         _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
         _61, _62, _63, N, ...) N

#define PP_RSEQ_N()                                        \
         63, 62, 61, 60,                                   \
         59, 58, 57, 56, 55, 54, 53, 52, 51, 50,           \
         49, 48, 47, 46, 45, 44, 43, 42, 41, 40,           \
         39, 38, 37, 36, 35, 34, 33, 32, 31, 30,           \
         29, 28, 27, 26, 25, 24, 23, 22, 21, 20,           \
         19, 18, 17, 16, 15, 14, 13, 12, 11, 10,           \
          9,  8,  7,  6,  5,  4,  3,  2,  1,  0

#define PP_NARG_(...)    PP_ARG_N(__VA_ARGS__)    

#define PP_NARG(...)     PP_NARG_(__VA_ARGS__, PP_RSEQ_N())



///
//#define INIT()
#define INIT_2(nm,tp) 		.appendColumnRaw(#nm, tp)
#define INIT_4(nm,tp,...)	.appendColumnRaw(#nm, tp) 	INIT_2(__VA_ARGS__)
#define INIT_6(nm,tp,...)	.appendColumnRaw(#nm, tp) 	INIT_4(__VA_ARGS__)
#define INIT_8(nm,tp,...)	.appendColumnRaw(#nm, tp) 	INIT_6(__VA_ARGS__)
#define INIT_10(nm,tp,...)	.appendColumnRaw(#nm, tp) 	INIT_8(__VA_ARGS__)
#define INIT_12(nm,tp,...)	.appendColumnRaw(#nm, tp) 	INIT_10(__VA_ARGS__)
#define INIT_14(nm,tp,...)	.appendColumnRaw(#nm, tp) 	INIT_12(__VA_ARGS__)
#define INIT_16(nm,tp,...)	.appendColumnRaw(#nm, tp) 	INIT_14(__VA_ARGS__)
#define INIT_18(nm,tp,...)	.appendColumnRaw(#nm, tp) 	INIT_16(__VA_ARGS__)
#define INIT_20(nm,tp,...)	.appendColumnRaw(#nm, tp) 	INIT_18(__VA_ARGS__)

#define ATTR_1(attr)		.appendAttribute(#attr)
#define ATTR_2(attr,...)	.appendAttribute(#attr)		ATTR_1(__VA_ARGS__)
#define ATTR_3(attr,...)	.appendAttribute(#attr)		ATTR_2(__VA_ARGS__)
#define ATTR_4(attr,...)	.appendAttribute(#attr)		ATTR_3(__VA_ARGS__)
#define ATTR_5(attr,...)	.appendAttribute(#attr)		ATTR_4(__VA_ARGS__)
#define ATTR_6(attr,...)	.appendAttribute(#attr)		ATTR_5(__VA_ARGS__)
#define ATTR_7(attr,...)	.appendAttribute(#attr)		ATTR_6(__VA_ARGS__)
#define ATTR_8(attr,...)	.appendAttribute(#attr)		ATTR_7(__VA_ARGS__)
#define ATTR_9(attr,...)	.appendAttribute(#attr)		ATTR_8(__VA_ARGS__)

#define INSERT_1(val)		.writeValue(val)
#define INSERT_2(val,...)	.writeValue(val)			INSERT_1(__VA_ARGS__)
#define INSERT_3(val,...)	.writeValue(val)			INSERT_2(__VA_ARGS__)
#define INSERT_4(val,...)	.writeValue(val)			INSERT_3(__VA_ARGS__)
#define INSERT_5(val,...)	.writeValue(val)			INSERT_4(__VA_ARGS__)
#define INSERT_6(val,...)	.writeValue(val)			INSERT_5(__VA_ARGS__)
#define INSERT_7(val,...)	.writeValue(val)			INSERT_6(__VA_ARGS__)

#define PROP_2(name,type)		coltype name;
#define PROP_4(name,type,...)	coltype name;			PROP_2(__VA_ARGS__)
#define PROP_6(name,type,...)	coltype name;			PROP_4(__VA_ARGS__)
#define PROP_8(name,type,...)	coltype name;			PROP_6(__VA_ARGS__)
#define PROP_10(name,type,...)	coltype name;			PROP_8(__VA_ARGS__)
#define PROP_12(name,type,...)	coltype name;			PROP_10(__VA_ARGS__)
#define PROP_14(name,type,...)	coltype name;			PROP_12(__VA_ARGS__)
#define PROP_16(name,type,...)	coltype name;			PROP_14(__VA_ARGS__)
#define PROP_18(name,type,...)	coltype name;			PROP_16(__VA_ARGS__)
#define PROP_20(name,type,...)	coltype name;			PROP_18(__VA_ARGS__)
#define PROP_22(name,type,...)	coltype name;			PROP_20(__VA_ARGS__)
#define PROP_24(name,type,...)	coltype name;			PROP_22(__VA_ARGS__)
#define PROP_26(name,type,...)	coltype name;			PROP_24(__VA_ARGS__)

#define PP_CONCAT2(A,B)		A##B
#define PP_CONCAT(A,N)		PP_CONCAT2(A, N)

#define TBL_INIT(...)		PP_CONCAT(INIT_,PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#define TBL_PROPS(...)		PP_CONCAT(PROP_,PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#define TBL_ATTR(...)	 	PP_CONCAT(ATTR_,PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#define TBL_INSERT(...)		PP_CONCAT(INSERT_,PP_NARG(__VA_ARGS__))(__VA_ARGS__)

#define EMPTY()
#define DEFER(id) id EMPTY()
#define EXPAND(...) __VA_ARGS__

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__






#define MAX_COLUMNS 10

#define TBLNAME __ctable<__COUNTER__/2>

template<int tableID>
struct __ctable;

#define CREATE struct TBLNAME &
#define TABLE 
#define SCHEMAT(className,...)\
		= *(className *)&(new customTable())->ref() TBL_INIT(__VA_ARGS__); \
	template<> \
	struct className : public table \
	{					\
	public:				\
		TBL_PROPS(__VA_ARGS__) \
	}
#define SCHEMA(...) SCHEMAT(TBLNAME,__VA_ARGS__)


// For insert, we are going to put the result into a variable, so we are allowed to
// make inserts in the global scope. Unfortunately, with this, we won't be able to
// use the INSERT query in an expression, like we can with select.
// - We're using __COUNTER__ twice, so we don't get out of phase for our
//	 CREATE TABLE macro, which depends on sequential calls to __COUNTER__
#define INSERT_VAR_NAME CAT(___insert_,CAT(__COUNTER__,__COUNTER__))
#define INSERT auto &&INSERT_VAR_NAME = 
#define INTO

// We can't really "drop" anything. Let's just clean up the records.
#define DROP		table_truncate() = 
#define TRUNCATE    table_truncate() = 

#define SELECT		select_statement().appendProjection(
//#define SELECT		select_statement::create().appendProjection(

#define FROM	*from_specifier()  ) *
//#define WHERE(...)   ,   ([&]()->bool{return(    __VA_ARGS__     );})
#define WHERE(...)   ,   (std::function<bool()>)([&]()->bool{return bool(    __VA_ARGS__     );})



#define AND     ) && (
#define OR      ) || (

//#define SCHEMA(...) = table() TBL_INIT(__VA_ARGS__)
#define ATTRIBUTES(...)		.createWriter() TBL_ATTR(__VA_ARGS__)
#define VALUES(...)			TBL_INSERT(__VA_ARGS__)

#define INTEGER , coltype(CC_INTEGER)
#define DOUBLE	, coltype(CC_DOUBLE)
#define CHAR	, create_char_coltype





coltype create_char_coltype(int length);

class table;

class table_writer
{
public:
	table_writer(table *tbl);
	table_writer &appendAttribute(const std::string &attr);
	table_writer &appendAllAttributes();
	
	bool isValid();
	
	template<typename T>
	table_writer &writeValue(const T &value);
	
	table_writer &writeValue(const char *val);
	
protected:
	std::vector<std::string> attributes;
	std::set<std::string> membership;
	table *destinationTable;
	bool valid;
	
	char *record;
	
	int currentAttribute;
};



class table
{
public:
	table_writer createWriter();
	
	table();
	table(const table & other);
	~table();
	
	void truncate();
    
    const char *getCurrentRecord() { return currentRecord; }
	
protected:
	friend class table_writer;
	friend class select_statement;
	
    void setCurrentRecord(char *rec) { currentRecord = rec; }
    table_writer *createDefaultWriter();
    
	
	
    char *currentRecord; // Used in WHERE clauses
    
	int recordSize;
	std::vector<char *> records;
	
	std::shared_ptr<table_writer> defaultWriter;
	
	
public:
	std::list<coltype *> columns;
	std::map<std::string, coltype *> columnMap;
	
	template<typename T>
	table_writer &writeValue(const T& value)
	{
		return createDefaultWriter()->writeValue(value);
	}
};


struct customTable : public table
{
public:
    customTable();
	~customTable();
    
	customTable &appendColumnRaw(std::string name, coltype &&ctype);
	customTable &appendColumnRaw(std::string name, coltype (*fn)(int)); // For CHAR columns w/o size specified.
	customTable &appendColumnRaw();
	
	customTable &ref() { return *this; }
protected:
	inline coltype *columnAtIndex(int index) { return &((coltype*)(&columnsData[0]))[index]; }
	inline coltype *nextColumn() { return columnAtIndex(columns.size()); }
	
#ifndef NO_ALIGNAS
	alignas(coltype) 
#endif
	char columnsData[16 * sizeof(coltype) / sizeof(char)];
	//char raw
};


class record
{
	
public:
	int getInteger(int index);
	double getDouble(int index);
	const char *getCString(int index);
	std::string getString(int index);
	
	operator bool() { return hasNext; }
	
private:
	const char *record;
	std::vector<int> offsets;
	bool hasNext;
	
	friend class select_statement;
	
	template<typename T>
	T getT(int index);
};


// This is a dummy object that is used in the projections field.
// It responds to operator* to handle cases like "SELECT * FROM",
// in which the code is transformed into something like:
//	appendProjection( * *from_specifier());
class from_specifier
{
public:
	from_specifier operator*() { return *this; }
};
template<typename T>
T &operator*(from_specifier &, T &obj){ return obj; }
template<typename T>
T &operator*(from_specifier , T &obj){ return obj; }
template<typename T>
T &operator*(T &obj, from_specifier &){ return obj; }
template<typename T>
T &operator*(T &obj, from_specifier ){ return obj; }
//from_specifier operator*(from_specifier fr) { return fr; }



struct projection_t
{
    int tableIndex;
    int sourceOffset;
    int destinationOffset;
    int dataSize;
};

class select_statement
{
private:
	static select_statement &alloc();
	
private:
	// eventually make this private.
	select_statement(const select_statement &other);
	
public:
	select_statement();
	static select_statement &create();

	class iterator
	{
	private:
		const select_statement *statement;
		int index;
	public:
		iterator(select_statement *stmt, int idx);
		iterator(const iterator &other);
		iterator &operator++();
		record operator*();
		bool operator!=(const iterator &other) const;
	};
    
    

	
	
public:
	select_statement operator*(table &tbl);	
	
	
	select_statement &&operator*(from_specifier &) { return std::move(*this); }
	select_statement &&operator*(from_specifier) { return std::move(*this); }
	
	bool getNext(record &rec);
	record getNext();
	record getRecord(int index) const;
	
	
	
	select_statement(select_statement &&other);
	~select_statement();
	
	const iterator begin();
	const iterator end();
	
//Should be protected:
	
	void addFromTable(table &tbl);
	
	select_statement &appendProjection(from_specifier);
	select_statement &&appendProjection(coltype &col);
	
	std::ostream &writeToStream(std::ostream &stream);
	
	template<typename... Types>
	select_statement appendProjection(coltype &col, Types&&... rest)
	{
		return appendProjection(col).appendProjection(rest...);
	}
	
	void addFilter(std::function<bool()> filter)
	{
        filters.push_back(filter);
        //return std::move(*this);
    }
	
private:   
	//std::vector<std::string> projections;
	std::vector<coltype *> projections;
	std::vector<int>		projectionOffsets;
    std::vector<projection_t> proj;
	table *fromTable;
	std::vector<table *>fromTables;
	bool hasCalculated;
	std::vector<char *>records;
	int index;
    
    std::vector<std::function<bool()>> filters;
	
	void calculate();
	void copyFromTableRecords();
};



class table_truncate
{
public:
	void operator=(table &tbl) { tbl.truncate(); }
};


select_statement &operator,(select_statement &left, table &right);
select_statement &operator,(select_statement &&left, table &right);
select_statement &operator,(select_statement &left, const table &right);
select_statement &operator,(select_statement &&left, const table &right);

//ostream &operator<<(ostream &stream, select_statement &stmt);
std::ostream &operator<<(std::ostream &stream, const select_statement &stmt);
select_statement operator,(select_statement &left, const std::function<bool()> right);
select_statement operator,(select_statement &&left, const std::function<bool()> right);

#endif//__CQL_H_