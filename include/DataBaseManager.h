#pragma once
#include "Table.h"
#include <string>
#include <map>
#include <memory>

class DatabaseManager {
private:
    std::map<std::string, std::shared_ptr<Table>> mountedTables;
public:
    bool mountTable(const std::string& name, const std::vector<Field>& schema) {
        if (mountedTables.find(name) != mountedTables.end()) {
            std::cout << "Table already mounted!\n";
            return false;
        }
        mountedTables[name] = std::make_shared<Table>(name, schema);
        std::cout << "Table " << name << " mounted.\n";
        return true;
    }

    bool unmountTable(const std::string& name) {
        if (mountedTables.find(name) == mountedTables.end()) {
            std::cout << "Table not found!\n";
            return false;
        }
        mountedTables.erase(name);
        std::cout << "Table " << name << " unmounted.\n";
        return true;
    }

    std::shared_ptr<Table> getTable(const std::string& name) {
        if (mountedTables.find(name) == mountedTables.end()) return nullptr;
        return mountedTables[name];
    }

    void listMountedTables() const {
        std::cout << "Mounted Tables:\n";
        for (const auto& pair : mountedTables) {
            std::cout << pair.first << "\n";
        }
    }
};
