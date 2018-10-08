#pragma once
#include "Table.h"

class TableHandler
{
private:
	Table** arr;
	int size;
	int capacity;

public:
	TableHandler() : arr(nullptr), size(0), capacity(0) {}
	~TableHandler() { for (int i = 0; i < size; ++i) delete arr[i]; delete[] arr; }

	void serialize(const char*, const char*) const;
	void deSerialize(const char*);

	void addTable(Table*);
	void addColumn(const char*, ColumnType);

	void print(const char*) const;

	void describe(const char*) const;
	void showNames() const;
	void update(int, const char*, int, const char*, const char*);

	void deleteRows(int, const char*, const char*);
	void rename(const char*, const char*);

	void count(int, const char*, const char*) const;
	
	void create(const char*);
public:
	void resize();
	bool whichTable(const char*, Table*&) const;
};