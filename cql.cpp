#include "cql.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string.h> // memcpy
using namespace std;


CREATE TABLE Boolean2 SCHEMA ( value CHAR (6) );



vector<unique_ptr<customTable>> table_heap;

table::table() : recordSize(0)
{
}

table::table(const table &other) 
: recordSize(other.recordSize), columns(other.columns)
{
	this->columnMap.clear();
	for (coltype *col : this->columns)
	{
		this->columnMap[col->getName()] = col;
	}
}

table::~table()
{
	//cout << "~table" << endl;	
	truncate();
}

table_writer *table::createDefaultWriter()
{
	if (defaultWriter)
		defaultWriter = nullptr;
	table_writer *writer = new table_writer(this);
	writer->appendAllAttributes();
	defaultWriter = shared_ptr<table_writer>(writer);
	return writer;
}

customTable::customTable()
{
    table_heap.push_back(unique_ptr<customTable>(this));
}

customTable::~customTable()
{
	// Destruct each of the columns in this table.
	for (int i = 0; i < (int)columns.size(); ++i)
		columnAtIndex(i)->~coltype();
}

customTable &customTable::appendColumnRaw(string name, coltype &&ctype)
{
	//cout << "In appendColumnRaw(name,ctype): name = " << name << " " << ctype.getDescription() << endl;
	
	ctype.setName(name);
	ctype.setDataOffset(this->recordSize);
    ctype.ownerTable = this;
	this->recordSize += ctype.getDataSize();
	
	coltype *dest = this->nextColumn();
	
	dest = new (dest) coltype(move(ctype));
	//*dest = ctype;
	
	
	this->columns.push_back(dest);
	this->columnMap[name] = columns.back();
	
	return *this;
}

customTable &customTable::appendColumnRaw(std::string name, coltype (*fn)(int))
{
	return appendColumnRaw(name, fn(DEFAULT_COL_LENGTH));
}

customTable &customTable::appendColumnRaw()
{
	//cout << "In appendColumnRaw()" << endl;
	return *this;
}

void table::truncate()
{
	for (char *rec : this->records)
	{
		delete []rec;
	}
	this->records.clear();
}

table_writer table::createWriter()
{
	return table_writer(this);
}

table_writer::table_writer(table *tbl)
: destinationTable(tbl), valid(true), currentAttribute(0)
{
	record = new char[tbl->recordSize];
	//memset(record, 0, sizeof(this->record));
	tbl->records.push_back(record);
}

bool table_writer::isValid()
{
	return valid && (attributes.size() != 0);
}

table_writer &table_writer::appendAttribute(const string &attr)
{
	//cout << "Appending attribute for insert writer: " << attr << endl;
		
	if (membership.find(attr) != membership.end())
	{
		cout << "Duplicate attribute " << attr << " for insert." << endl;
		valid = false;
	}
	if (destinationTable->columnMap.find(attr) == destinationTable->columnMap.end())
	{
		cout << "Invalid attribute (Doesn't belong to table): " << attr << endl;
		valid = false;
	}
	if (valid)
	{
		attributes.push_back(attr);
		membership.insert(attr);
	}
		
	return *this;
}

table_writer &table_writer::appendAllAttributes()
{
	for (coltype *col : destinationTable->columns)
		attributes.push_back(col->getName());
	return *this;
}

template<>
table_writer &table_writer::writeValue<int>(const int &val)
{
	if (currentAttribute >= (int)destinationTable->columns.size())
	{
		cout << "Attempting to write too many values" << endl;
		return *this;
	}
	
	//TODO: Check types better.
	
	const coltype *col = destinationTable->columnMap[this->attributes.at(currentAttribute++)];
	
	memcpy(record + col->getDataOffset(), &val, col->getDataSize());
	return *this;
}

template<>
table_writer &table_writer::writeValue<double>(const double &val)
{
	if (currentAttribute >= (int)destinationTable->columns.size())
	{
		cout << "Attempting to write too many values" << endl;
		return *this;
	}
	
	//TODO: Check types better.
	
	const coltype *col = destinationTable->columnMap[this->attributes.at(currentAttribute++)];
	
	memcpy(record + col->getDataOffset(), &val, col->getDataSize());
	return *this;
}

table_writer &table_writer::writeValue(const char *val)
{
	const coltype *col = destinationTable->columnMap[this->attributes.at(currentAttribute++)];
	
	int len = strlen(val) + 1;
	if (len > col->getDataSize())
		len = col->getDataSize();
	
	memcpy(record + col->getDataOffset(), val, len);
	return *this;
}

template<typename T>
T record::getT(int index)
{
	T retval;
	memcpy(&retval, record + offsets[index], sizeof(retval));
	return retval;
}

int record::getInteger(int index)
{
	return getT<int>(index);
}

double record::getDouble(int index)
{
	return getT<double>(index);
}

string record::getString(int index)
{
	return string(getCString(index));
}

const char *record::getCString(int index)
{
	return this->record + offsets[index];
}
