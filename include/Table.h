#pragma once
#include <string>
#include <vector>
#include <iostream>

enum class FieldType { INT, FLOAT, STRING };

struct Field {
    std::string name;
    FieldType type;
};

class Table {
private:
    std::string tableName;
    std::vector<Field> schema;
    std::vector<std::vector<std::string>> records; // each row is a vector of strings
public:
    Table(const std::string& name, const std::vector<Field>& fields)
        : tableName(name), schema(fields) {
    }

    std::string getName() const { return tableName; }

    void addRecord(const std::vector<std::string>& row) {
        if (row.size() != schema.size()) {
            std::cout << "Error: Record does not match schema!\n";
            return;
        }
        records.push_back(row);
    }

    void listRecords() const {
        for (const auto& f : schema)
            std::cout << f.name << "\t";
        std::cout << "\n------------------------\n";
        for (const auto& r : records) {
            for (const auto& val : r)
                std::cout << val << "\t";
            std::cout << "\n";
        }
    }

    int getColumnCount() const { return schema.size(); }

    const std::vector<Field>& getSchema() const { return schema; }
};
