#pragma once

/// The maximum length of table's name.
static const int TABLE_NAME_MAX = 256;

/// The maximum length of the value's length.
static const int VALUE_LENGTH_MAX = 256;

enum class ColumnType
{
	INT,
	DOUBLE,
	STRING
};

#define DISABLE_COPY(className) className(const className&); className& operator=(const className&);