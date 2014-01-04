#include "cql.h"
#include <string.h>
#include <iostream>
#include <map>
#include <utility>
#include <tuple>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>
#include <memory>
#include <iomanip>
using namespace std;

//static map<int, select_statement> allocatedSelectStatements;
static vector<unique_ptr<select_statement>> select_heap;

select_statement &select_statement::create()
{
    select_statement *stmt = new select_statement();
    //select_heap.push_back(unique_ptr<select_statement>(stmt));
    return *stmt;
}

select_statement::select_statement()
: projections(0), projectionOffsets(0), fromTables(0), records(0)
{
	//cout << "select_statement default constructor" << endl;
	hasCalculated = false;
	index = 0;
}

select_statement::select_statement(const select_statement &other)
:
projections(other.projections),
projectionOffsets(other.projectionOffsets),
fromTable(other.fromTable),
fromTables(other.fromTables),
hasCalculated(other.hasCalculated),
records(0),
index(other.index),
filters(other.filters)
{
	//cout << "select_statement copy constructor" << endl;
}

select_statement::select_statement(select_statement &&other)
{
	
	projections.swap(other.projections);
	projectionOffsets.swap(other.projectionOffsets);
	fromTable = other.fromTable;
	fromTables.swap(other.fromTables);
	hasCalculated = other.hasCalculated;
	records.swap(other.records);
	index = other.index;
    filters.swap(other.filters);
    
	//cout << "select_statement move constructor" << endl;
}

select_statement::~select_statement()
{
    for (char *rec : this->records)
        delete [] rec;
	//cout << "~select_statement" << endl;
}

void select_statement::calculate()
{
	if (hasCalculated) return;
	hasCalculated = true;
    
    // If there aren't any columns to project (i.e. SELECT *), load all columns
    // from all source tables.
	if (projections.size() == 0)
	{
        //cout << "Need to copy all columns (*)" << endl;
		//printf("fromTable: %p\n", (void*)fromTable);
		//printf("fromTables:");
		//for (table * tbl : fromTables)
		//	printf(" %p", (void*)tbl);
		//printf("\n");
	
		//cout << "I'm HERE" << endl;
		projections.clear();
		
		if (fromTables.size() == 1253)
		{
			//auto tbl = fromTable;
			//copy(tbl->columns.begin(), tbl->columns.end(), back_inserter(projections));
		}
		else
		{
			for (table * tbl : fromTables)
			{
                for (coltype *col : tbl->columns)
                {
                    // TODO: Eventually, this statement should go somewhere more reasonable
                    projections.push_back(col);
                }
				//tbl += 0;
				//	copy(tbl->columns.begin(), tbl->columns.end(), back_inserter(projections));
			}
		}
		//cout << "I got here.";
	}
	
	int recordSize = 0;
	//vector<projection_t> proj;
    proj.clear();
	
	projectionOffsets.clear();
	
	// Calculate the table that maps data locations in the original tables
	// to data locations in the calculated table.
	for (const coltype *pcol : projections)
	{
		const coltype &col = *pcol;
		
		projectionOffsets.push_back(recordSize);
	
		projection_t desc;
		desc.sourceOffset = col.getDataOffset();
		desc.destinationOffset = recordSize;
		desc.dataSize = col.getDataSize();
        
        desc.tableIndex = 0;
        while (fromTables.at(desc.tableIndex) != col.ownerTable)
            ++desc.tableIndex;
        
		proj.push_back(desc);
		
		recordSize += desc.dataSize;
	}
	
	records.clear();
    
    
    // TODO: I think I need some recursive solution for joins.
    if (fromTables.size() == 1)
    {
        for (char *record : fromTable->records)
        {
            fromTable->setCurrentRecord(record);
            
            if (!filters.size() || filters.at(0)())
            {
                char *myRecord = new char[recordSize];
                for (const projection_t p : proj)
                    memcpy(myRecord + p.destinationOffset, record + p.sourceOffset, p.dataSize);
                records.push_back(myRecord);
            }
        }
    } else if (fromTables.size()== 2)
    {
        for (char *record0 : fromTables.at(0)->records)
        {
            fromTables.at(0)->setCurrentRecord(record0);
            for (char *record1 : fromTables.at(1)->records)
            {
                fromTables.at(1)->setCurrentRecord(record1);
                if (!filters.size() || filters.at(0)())
                {
                    char *myRecord = new char[recordSize];
                    for (const projection_t p : proj)
                    {
                        char *origin = p.tableIndex ? record1 : record0;
                        memcpy(myRecord + p.destinationOffset, origin + p.sourceOffset, p.dataSize);
                    }
                    records.push_back(myRecord);
                }
            }
        }
    }
	//cout << "WOOP\n";
	index = 0;
}

void select_statement::copyFromTableRecords()
{

}

void select_statement::addFromTable(table &tbl)
{
	fromTable = &tbl;
	//cout << "Adding FromTable" << endl;
	fromTables.push_back(&tbl);
}

select_statement select_statement::operator*(table &tbl)
{
	addFromTable(tbl);
	return move(*this);
}


bool select_statement::getNext(record &rec)
{
	if (!hasCalculated)
		calculate();
		
	if (index >= (int)records.size())
		return false;
	
	rec.offsets = this->projectionOffsets;
	rec.record = this->records.at(index++);
	
	return true;
}

record select_statement::getRecord(int idx) const
{
	record r;
	r.offsets = this->projectionOffsets;
	r.record = this->records.at(idx);
	return r;
}

select_statement &&select_statement::appendProjection(coltype &col)
{
	//cout << "Projection Column: " << col.getDescription() << endl;
	projections.push_back(&col);
	return move(*this);
}

select_statement &select_statement::appendProjection(from_specifier)
{
	//cout << "Appending" << endl;
	return *this;
}

const select_statement::iterator select_statement::begin()
{
	if (!hasCalculated)
		calculate();
	return iterator(this, 0);
}

const select_statement::iterator select_statement::end()
{
	return iterator(this, records.size());
}

select_statement::iterator::iterator(select_statement *stmt, int idx)
: statement(stmt), index(idx)
{
}

select_statement::iterator::iterator(const select_statement::iterator &other)
: statement(other.statement), index(other.index)
{
}

select_statement::iterator &select_statement::iterator::operator++()
{
	++index;
	return *this;
}

record select_statement::iterator::operator*()
{
	return statement->getRecord(index);
}

bool select_statement::iterator::operator!=(const select_statement::iterator &other) const
{
	return (statement != other.statement) || (index != other.index);
}

/// Output

ostream &select_statement::writeToStream(ostream &stream)
{
    calculate();
    
    vector<int> widths;
    widths.reserve(projections.size());
    
    stream << left;
    
    for (const coltype *col : projections)
    {
        int w;
        widths.push_back(w = col->getDisplayWidth());
        stream << setw(w) << col->getName() << ' ';
    }
    stream << endl;
    
    for (const int &w : widths)
    {
        stream << string((size_t)w, '-') << ' ';
    }
    
    stream << endl << left;
    
    for (const char *rec : records)
    {
        for (unsigned int i = 0; i < projections.size(); i++)
        {
            const coltype &col = *projections[i];
            const projection_t &pr = proj[i];
            stream << setw(widths[i]) << col.formatData(rec + pr.destinationOffset) << ' ';
        }
        stream << endl;
    }
    
    return stream;
}

select_statement &operator,(select_statement &left, table &right)
{
	left.addFromTable(right);
	return left;
}
select_statement &operator,(select_statement &&left, table &right)
{
    left.addFromTable(right);
    return left;
}
select_statement &operator,(select_statement &left, const table &right)
{
	left.addFromTable((table &)right);
	return left;
}
select_statement &operator,(select_statement &&left, const table &right)
{
    left.addFromTable((table&)right);
    return left;
}

ostream &operator<<(ostream &stream, select_statement &stmt)
{
    return stmt.writeToStream(stream);
}

ostream &operator<<(ostream &stream, const select_statement &stmt)
{
    // FUGLY. Making a copy of the results set to be able to print it.
    //select_statement s2 = stmt;
	
	// fuck the const.
	select_statement &s2 = (select_statement&)stmt;
    return s2.writeToStream(stream);
}


select_statement operator,(select_statement &left, const function<bool()> right)
{
	left.addFilter(right);
	return move(left);
}

select_statement operator,(select_statement &&left, const function<bool()> right)
{
    left.addFilter(right);
	return move(left);
}