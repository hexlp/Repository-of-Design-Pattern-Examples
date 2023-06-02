
#include <iostream>
#include <vector>
#include <fstream>

// Abstract base class
class DataFormatHandler {
public:
    // Template method for importing data
    void importData(const std::string& filename) {
        std::vector<std::string> data = readFile(filename);
        parseData(data);
        processData();
    }

    // Template method for exporting data
    void exportData(const std::string& filename) {
        std::vector<std::string> data = prepareData();
        writeFile(filename, data);
    }

protected:
    // Abstract methods
    virtual std::vector<std::string> readFile(const std::string& filename) = 0;
    virtual void parseData(const std::vector<std::string>& data) = 0;
    virtual void processData() = 0;
    virtual std::vector<std::string> prepareData() = 0;
    virtual void writeFile(const std::string& filename, const std::vector<std::string>& data) = 0;
};

// Concrete subclass for CSV data format
class CSVDataHandler : public DataFormatHandler {
protected:
    std::vector<std::string> readFile(const std::string& filename) override {
        // Read CSV file and return data as vector of strings
        std::cout << "Reading CSV file: " << filename << std::endl;
        // Read implementation specific to CSV format
        return { "John,Doe,30", "Jane,Smith,25", "Bob,Johnson,35" };
    }

    void parseData(const std::vector<std::string>& data) override {
        // Parse CSV data and process it accordingly
        std::cout << "Parsing CSV data" << std::endl;
        // Parse implementation specific to CSV format
    }

    void processData() override {
        // Process CSV data
        std::cout << "Processing CSV data" << std::endl;
        // Process implementation specific to CSV format
    }

    std::vector<std::string> prepareData() override {
        // Prepare CSV data for export
        std::cout << "Preparing CSV data for export" << std::endl;
        // Prepare implementation specific to CSV format
        return { "John,Doe,30", "Jane,Smith,25", "Bob,Johnson,35" };
    }

    void writeFile(const std::string& filename, const std::vector<std::string>& data) override {
        // Write CSV data to file
        std::cout << "Writing CSV data to file: " << filename << std::endl;
        // Write implementation specific to CSV format
    }
};

// Concrete subclass for JSON data format
class JSONDataHandler : public DataFormatHandler {
protected:
    std::vector<std::string> readFile(const std::string& filename) override {
        // Read JSON file and return data as vector of strings
        std::cout << "Reading JSON file: " << filename << std::endl;
        // Read implementation specific to JSON format
        return { "{\"name\": \"John\", \"age\": 30}", "{\"name\": \"Jane\", \"age\": 25}", "{\"name\": \"Bob\", \"age\": 35}" };
    }

    void parseData(const std::vector<std::string>& data) override {
        // Parse JSON data and process it accordingly
        std::cout << "Parsing JSON data" << std::endl;
        // Parse implementation specific to JSON format
    }

    void processData() override {
        // Process JSON data
        std::cout << "Processing JSON data" << std::endl;
        // Process implementation specific to JSON format
    }

    std::vector<std::string> prepareData() override {
        // Prepare JSON data for export
        std::cout << "Preparing JSON data for export" << std::endl;
        // Prepare implementation specific to JSON format
        return { "{\"name\": \"John\", \"age\": 30}", "{\"name\": \"Jane\", \"age\": 25}", "{\"name\": \"Bob\", \"age\": 35}" };
    }

    void writeFile(const std::string& filename, const std::vector<std::string>& data) override {
        // Write JSON data to file
        std::cout << "Writing JSON data to file: " << filename << std::endl;
        // Write implementation specific to JSON format
    }
};

int main() {
    DataFormatHandler* csvDataHandler = new CSVDataHandler();
    csvDataHandler->importData("data.csv");
    std::cout << "-------------" << std::endl;
    csvDataHandler->exportData("exported_data.csv");

    std::cout << "-------------" << std::endl;

    DataFormatHandler* jsonDataHandler = new JSONDataHandler();
    jsonDataHandler->importData("data.json");
    std::cout << "-------------" << std::endl;
    jsonDataHandler->exportData("exported_data.json");

    delete csvDataHandler;
    delete jsonDataHandler;

    return 0;
}