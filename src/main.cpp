#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include "Table.h"
#include "DatabaseManager.h"

int main() {
    DatabaseManager dbManager;
    std::string input;

    std::cout << "Welcome to the DB.\nType HELP for commands.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input.empty()) continue;

        std::istringstream ss(input);
        std::string command;
        ss >> command;

        if (command == "EXIT") {
            std::cout << "Exiting CLI.\n";
            break;
        }
        else if (command == "HELP") {
            std::cout << "Commands:\n";
            std::cout << "MOUNT <TableName> <Col1>:<Type1> <Col2>:<Type2> ...\n";
            std::cout << "UNMOUNT <TableName>\n";
            std::cout << "INSERT <TableName> <Val1> <Val2> ...\n";
            std::cout << "SELECT <TableName>\n";
            std::cout << "LIST\n";
            std::cout << "EXIT\n";
        }
        else if (command == "MOUNT") {
            std::string tableName;
            ss >> tableName;
            std::vector<Field> schema;
            std::string colDef;
            while (ss >> colDef) {
                size_t pos = colDef.find(':');
                if (pos == std::string::npos) continue;
                std::string name = colDef.substr(0, pos);
                std::string typeStr = colDef.substr(pos + 1);
                FieldType type = FieldType::STRING;
                if (typeStr == "INT") type = FieldType::INT;
                else if (typeStr == "FLOAT") type = FieldType::FLOAT;
                schema.push_back({ name, type });
            }
            dbManager.mountTable(tableName, schema);
        }
        else if (command == "UNMOUNT") {
            std::string tableName;
            ss >> tableName;
            dbManager.unmountTable(tableName);
        }
        else if (command == "INSERT") {
            std::string tableName;
            ss >> tableName;
            auto table = dbManager.getTable(tableName);
            if (!table) {
                std::cout << "Table not mounted!\n";
                continue;
            }
            std::vector<std::string> values;
            std::string val;
            while (ss >> val) values.push_back(val);
            table->addRecord(values);
            std::cout << "Record inserted.\n";
        }
        else if (command == "SELECT") {
            std::string tableName;
            ss >> tableName;
            auto table = dbManager.getTable(tableName);
            if (!table) {
                std::cout << "Table not mounted!\n";
                continue;
            }
            table->listRecords();
        }
        else if (command == "LIST") {
            dbManager.listMountedTables();
        }
        else {
            std::cout << "Unknown command! Type HELP for commands.\n";
        }
    }

    return 0;
}
