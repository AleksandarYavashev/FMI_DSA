#pragma once
#include "ColumnInt.h"
#include "ColumnDouble.h"
#include "ColumnString.h"
#include <fstream>

class Table
{
private:
	char* name;
	Column** column;
	int size;
	int capacity;

public:
	Table() : column(nullptr), size(0), capacity(0), name(nullptr) {}
	Table(const char* tableName);
	~Table();

public:
	int getNumberColumns() const { return size; }
	Column* getColumn(int columnIndex) const { return column[columnIndex]; }

	const char* getName() const;

	Column* createColumn(ColumnType);

	void serialize(const char*);
	void deSerialize(const char*);

	void addColumn(Column*);

	void print();
	
	int search(int, const char*);
	void deleteRow(int);
	void deleteRows(int, const char*);

	void rename(const char*);
	int count(int, const char*);

	void describe();
	void update(int, const char*,int, const char*);

public:
	void resize();

private:
	DISABLE_COPY(Table);
};
