#pragma once
#include "TableHandler.h"

class CmdHandler
{
public:
	void run()
	{
		char arg[128];

		while (std::cin >> arg)
			callCommand(arg);
	}

private:
	TableHandler tableHandler;

private:
	//derserializes a table from a fime - "fileName"
	void load()
	{
		char fileName[FILENAME_MAX];
		std::cin >> fileName;

		std::cout << "Load seccessful!\n";
	}

	//prints the names of all tables that are currently loaded
	void showTables()
	{
		tableHandler.showNames();
	}

	//prints table's column types
	void describe()
	{
		char tableName[TABLE_NAME_MAX];
		std::cin >> tableName;

		tableHandler.describe(tableName);
	}

	void print()
	{
		char tableName[TABLE_NAME_MAX];
		std::cin >> tableName;

		tableHandler.print(tableName);
	}

	// saves table(tableName) in a file.
	void save()
	{
		char tableName[TABLE_NAME_MAX], fileName[FILENAME_MAX];
		std::cin >> tableName >> fileName;

		tableHandler.serialize(fileName, tableName);
	}

	void select()
	{
		int columnN;
		char value[VALUE_LENGTH_MAX]; //int, double, char* !!!
		char tableName[TABLE_NAME_MAX];
		std::cin >> columnN >> value >> tableName;

		//Table::printRow();
		//select the rows with value in the columnN column.
	}

	ColumnType getColumnTypeFromString(const char *columnTypeString)
	{
		ColumnType result;
		if (strcmp(columnTypeString, "int") == 0)
		{
			result = ColumnType::INT;
		}
		else if (strcmp(columnTypeString, "double") == 0)
		{
			result = ColumnType::DOUBLE;
		}
		else if (strcmp(columnTypeString, "string") == 0)
		{
			result = ColumnType::STRING;
		}

		return result;
	}

	//adds column to table(tableName)
	void addColumn()
	{
		char tableName[TABLE_NAME_MAX], columnTypeString[16];
		std::cin >> tableName >> columnTypeString;

		ColumnType columnType = getColumnTypeFromString(columnTypeString);

		tableHandler.addColumn(tableName, columnType);
	}

	// update
	void update()
	{
		char tableName[TABLE_NAME_MAX];
		int searchedColumn;
		char searchedValue[VALUE_LENGTH_MAX];
		int targetColumn;
		char targetValue[VALUE_LENGTH_MAX];
		std::cin >> tableName >> searchedColumn >>
			searchedValue >> targetColumn >> targetValue;

		tableHandler.update(searchedColumn, searchedValue, targetColumn, targetValue, tableName);

	}

	void deleteRows()
	{
		char tableName[TABLE_NAME_MAX];
		int searchedColumn;
		char searchedValue[VALUE_LENGTH_MAX];

		std::cin >> tableName >> searchedColumn >>
			searchedValue;

		tableHandler.deleteRows(searchedColumn, searchedValue, tableName);
		//delete.
	}

	void insert()
	{
		char tableName[TABLE_NAME_MAX];
		std::cin >> tableName;

		Table* table;
		if (tableHandler.whichTable(tableName, table) == false)
		{
			std::cout << "There is no such table!\n";
			return;
		}

		int numColumns = table->getNumberColumns();

		char value[VALUE_LENGTH_MAX];
		for (int i = 0; i < numColumns; ++i)
		{
			std::cin >> value;

			table->getColumn(i)->addElement(value);
		}
	}

	void innerJoin()
	{
		//opraqi sa brat.
	}

	// rename.
	void rename()
	{
		char oldTableName[TABLE_NAME_MAX], newTableName[TABLE_NAME_MAX];
		std::cin >> oldTableName >> newTableName;

		tableHandler.rename(oldTableName, newTableName);
	}

	void count()
	{
		char tableName[TABLE_NAME_MAX];
		int searchColumn;
		char searchedValue[VALUE_LENGTH_MAX];
		std::cin >> tableName >> searchColumn >> searchedValue;

		tableHandler.count(searchColumn, searchedValue, tableName);
		//count.
	}

	void aggregate()
	{
		char tableName[TABLE_NAME_MAX];
		int searchColumn;
		char searchedValue[VALUE_LENGTH_MAX];
		int targetColumn;
		char operationString[64];
		std::cin >> tableName >> searchColumn >> searchedValue >>
			targetColumn >> operationString;

		//aggregate.
	}

	void create()
	{
		char tableName[TABLE_NAME_MAX];
		std::cin >> tableName;

		tableHandler.create(tableName);
	}

	void callCommand(const char* command)
	{
		if (strcmp(command, "Load") == 0)
		{
			load();
		}
		else if (strcmp(command, "Showtables") == 0)
		{
			showTables();
		}
		else if (strcmp(command, "Describe") == 0)
		{
			describe();
		}
		else if (strcmp(command, "Print") == 0)
		{
			print();
		}
		else if (strcmp(command, "Save") == 0)
		{
			save();
		}
		else if (strcmp(command, "Select") == 0)
		{
			select();
		}
		else if (strcmp(command, "AddColumn") == 0)
		{
			addColumn();
		}
		else if (strcmp(command, "Update") == 0)
		{
			update();
		}
		else if (strcmp(command, "Delete") == 0)
		{
			deleteRows();
		}
		else if (strcmp(command, "Insert") == 0)
		{
			insert();
		}
		else if (strcmp(command, "InnerJoin") == 0)
		{
			innerJoin();
		}
		else if (strcmp(command, "Rename") == 0)
		{
			rename();
		}
		else if (strcmp(command, "Count") == 0)
		{
			count();
		}
		else if (strcmp(command, "Aggregate") == 0)
		{
			aggregate();
		}
		else if (strcmp(command, "Create") == 0)
		{
			create();
		}
		else
		{
			std::cout << "Wrong command input.\n";
		}
	}
};
