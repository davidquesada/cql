#include "coltype.h"
#include "cql.h"
#include <string>

#include "to_string_patch.cpp"

using namespace std;

coltype::coltype(coltype_class c_)
: cl(c_)
{
}

coltype::coltype(coltype_class c_, int len_)
: cl(c_), length(len_)
{
}

coltype create_char_coltype(int length)
{
	if (length == DEFAULT_COL_LENGTH)
		return coltype(CC_CHAR, 1);
	return coltype(CC_CHAR, length);
}

coltype &coltype::setLength(int len)
{
	this->length = len;
	return *this;
}

string coltype::getDescription() const
{
	switch (this->cl)
	{
		case CC_INTEGER: return getName() + " INTEGER";
		case CC_DOUBLE: return getName() + " DOUBLE";
		case CC_CHAR: return getName() + " CHAR (" + to_string(this->length) + ")";
	}
	return getName() + " OTHER";
}

void coltype::setName(const string &name_)
{
	this->name = name_;
}

const string &coltype::getName() const
{
	return this->name;
}

int coltype::getDataOffset() const
{
	return this->dataOffset;
}

void coltype::setDataOffset(int o)
{
	this->dataOffset = o;
}

int coltype::getDataSize() const
{
	switch (this->cl)
	{
		case CC_INTEGER: return 4;
		case CC_DOUBLE: return 8;
		case CC_CHAR: return length;
	}
	return 4;
}

int coltype::getDisplayWidth() const
{
    int prefwidth = getPreferredDisplayWidth();
    
    if (prefwidth < (int)getName().length())
        return getName().length();
    
    if (prefwidth > 30)
        return 30;
    
    return prefwidth;
}

int coltype::getPreferredDisplayWidth() const
{
    switch (this->cl)
    {
        case CC_INTEGER: return 10;
        case CC_DOUBLE: return 10;
        case CC_CHAR: return length;
    }
    return 10;
}

const char *coltype::getCurrentRecord()
{
    return ownerTable->getCurrentRecord();
}

string coltype::formatData(const char *data) const
{
    switch (this->cl)
    {
        // TODO: Might there be alignment issues?
        case CC_INTEGER: return to_string(*(int *)data);
        case CC_DOUBLE: return to_string(*(double *)data);
        case CC_CHAR: return string(data);
    }
    return "";
}

// Join-related stuff.

bool operator==(coltype &col, const coltype &other)
{
	return col.compareAgainstColumn(other) == 0;
}

bool coltype::operator=(coltype &other)
{
	return compareAgainstColumn(other) == 0;
}

int coltype::compareAgainstColumn(const coltype &other)
{
	coltype &col = (coltype&)other; // delete const;
	
	switch (this->cl)
	{
		// This makes the assumption that users won't try to compare
		// columns of different types.
		case CC_INTEGER: return this->compareCurrentValue<int>(col);
		case CC_DOUBLE:	 return this->compareCurrentValue<double>(col);
		case CC_CHAR:	 return this->compareCurrentValue<const char *>(col);
	}
	
	return 0;
}

