#include "TableHandler.h"

void TableHandler::serialize(const char* fileName, const char* tableName) const
{
	Table* table = nullptr;
	bool isOk = whichTable(tableName, table);
	if (isOk == false)
	{
		std::cout << "Wrong input(table name).\n";
		return;
	}

	table->serialize(fileName);
}

void TableHandler::deSerialize(const char* fileName)
{
	Table* table = new Table;
	table->deSerialize(fileName);
	addTable(table);
}

void TableHandler::addTable(Table* table)
{
	if (capacity == size)
	{
		resize();
	}
	arr[size] = table;
	++size;
}

void TableHandler::describe(const char* tableName) const
{
	Table* table = nullptr;
	bool isOk = whichTable(tableName, table);
	if (isOk == false) 
	{
		std::cout << "Wrong input(table name).\n";
		return;
	}

	table->describe();
}

void TableHandler::showNames() const
{
	for (int i = 0; i < size; ++i)
		std::cout << i << ". " << arr[i]->getName() << "\n";
}

void TableHandler::resize()
{
	Table** tablePtr = new Table*[(2*size) + 1];
	for (int i = 0; i < size; ++i)
	{
		tablePtr[i] = arr[i];
	}

	capacity = 2 * size + 1;

	delete[]arr;
	arr = tablePtr;
}

bool TableHandler::whichTable(const char * name, Table*& table) const
{
	for (int i = 0; i < size; ++i)
	{
		if (strcmp(name, arr[i]->getName()) == 0)
		{
			table = arr[i];
			return true;
		}
	}
	return false;
}

void TableHandler::addColumn(const char* tableName, ColumnType colType)
{
	Table* table = nullptr;
	if (whichTable(tableName, table) == false)
	{
		std::cout << "Wrong input(table name).\n";
		return;
	}

 	Column* column = table->createColumn(colType);
	table->addColumn(column);
}

void TableHandler::print(const char *tableName) const
{
	Table* table = nullptr;
	bool isOk = whichTable(tableName, table);
	if (isOk == false)
	{
		std::cout << "Wrong input(table name).\n";
		return;
	}

	table->print();
}

void TableHandler::update(int searchedColumn, const char* searchedValue, int targetColumn, const char* targetValue, const char* tableName)
{
	Table* table = nullptr;
	bool isOk = whichTable(tableName, table);
	if (isOk == false)
	{
		std::cout << "Wrong input(table name).\n";
		return;
	}

	table->update(searchedColumn, searchedValue, targetColumn, targetValue);
}

void TableHandler::deleteRows(int searchedColumn, const char* searchedValue, const char* tableName)
{
	Table* table = nullptr;
	bool isOk = whichTable(tableName, table);
	if (isOk == false)
	{
		std::cout << "Wrong input(table name).\n";
		return;
	} 

	table->deleteRows(searchedColumn, searchedValue);
}

void TableHandler::rename(const char* oldName, const char* newName)
{
	Table* table = nullptr;
	bool isOk = whichTable(oldName, table);
	if (isOk == false)
	{
		std::cout << "Wrong input(table name).\n";
		return;
	}

	for (int i = 0; i < size; ++i)
	{
		if (strcmp(newName, arr[i]->getName()))
		{
			std::cout << "New name is not uniqe!";
			return;
		}
		
		table->rename(newName);
	}
}

void TableHandler::count(int searchColumn, const char* searchedValue, const char* tableName) const
{
	Table* table = nullptr;
	bool isOk = whichTable(tableName, table);
	if (isOk == false)
	{
		std::cout << "Wrong input(table name).\n";
		return;
	}

	int count = table->count(searchColumn, searchedValue);
	std::cout << count << "rows in the column have same value.\n";
}

void TableHandler::create(const char* name)
{
	Table* table = new Table(name);
	addTable(table);
}