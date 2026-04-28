# include <fstream>
# include <iostream>
# include "include/linkedList.hpp"
# include "include/sortedArraySet.hpp"
# include "include/hashTable.hpp"
# include "include/binaryHeap.hpp"
# include "include/avl.hpp"
# include <string>
# include <vector>
# include <filesystem>

using namespace std;

// Struct to represent an operation from workload file
struct Operation {
    string op;
    int value;
};

// Function to parse workload file
vector<Operation> parse_workload(ifstream& infile);

// Function to perform operations on data structure
template <typename DS>
void run_workload(ifstream& infile, string workload_file, ofstream& outfile, const string& structure_name);

// Overload for BinaryHeap since it uses different methods
//
//  When workload file wants to insert, we call push()
//  When workload file wants to delete a certain value, we ignore the value and pop the top element
//  When workload file wants to search for a value, we ignore the value and just call top()
//
void run_workload(ifstream& infile, string workload_file, ofstream& outfile);

// Function to record counters to output file
template <typename DS>
void record(const DS& ds, string workload_file, ofstream& outfile, const string& structure_name);

int main(int argc, char** argv)
{
    // argc - count of arguments
    // argv - array of arguments
    
    // ./main <data_structure> <wordload_file> <output_file>
    // argv[1] - data_structure
    // argv[2] - workload_file
    // argv[3] - output_file
    // argv[0] - program name

    // Check for correct number of arguments
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <data_structure> <workload_file> <output_file>\n";
        return 1;
    }

    // Get command line arguments
    string structure = argv[1];
    string workload_file = argv[2];
    string output_file = argv[3];

    // Check if output file already has content (before opening it)
    bool write_header = false;
    {
        ifstream check(output_file);
        write_header = !check.good() || check.peek() == EOF;
    }

    // Open files
    ifstream infile(workload_file);
    ofstream outfile(output_file, std::ios::app);  // append mode

    // Check if files opened successfully
    if (!infile.is_open()) {
        std::cerr << "Error opening workload file: " << workload_file << "\n";
        return 1;
    }

    if (!outfile.is_open()) {
        std::cerr << "Error opening output file: " << output_file << "\n";
        return 1;
    }

    // Only write header if file was empty or didn't exist
    if (write_header) {
        outfile << "Data Structure,Workload,Comparisons,Structural Ops,Inserts,Deletes,Lookups,Resize Events\n";
    }

    // Create data structure based on argument
    if (structure == "list")
        run_workload<LinkedList>(infile, workload_file, outfile, "list");

    else if (structure == "array")
        run_workload<SortedArraySet>(infile, workload_file, outfile, "array");

    else if (structure == "hash")
        run_workload<HashTable>(infile, workload_file, outfile, "hash");

    else if (structure == "bst")
        run_workload<Bst>(infile, workload_file, outfile, "bst");

    else if (structure == "heap")
        run_workload(infile, workload_file, outfile);

    else if (structure == "avl")
        run_workload<Avl>(infile, workload_file, outfile, "avl");

    else
    {
        std::cerr << "Unknown data structure: " << structure << "\n";
        return 1;
    }

    // Close files
    infile.close();
    outfile.close();
}


// ******   FUNCTIONS   ****** \\


template <typename DS>
void run_workload(ifstream& infile, string workload_file, ofstream& outfile, const string& structure_name)
{
    // Create instance of data structure
    DS ds;

    // Parse workload file into vector of operations
    vector<Operation> operations = parse_workload(infile);

    // Execute operations on data structure
    for (const Operation& op : operations)
    {
        if (op.op == "insert")
            ds.insert(op.value);

        else if (op.op == "delete")
            ds.erase(op.value);

        else if (op.op == "contains")
            ds.contains(op.value);
    }

    // Record counters to output file
    record(ds, workload_file, outfile, structure_name);
}

void run_workload(ifstream& infile, string workload_file, ofstream& outfile)
{
    // Create instance of data structure
    BinaryHeap ds;

    // Parse workload file into vector of operations
    vector<Operation> operations = parse_workload(infile);

    // Execute operations on data structure
    for (const Operation& op : operations)
    {
        if (op.op == "insert")
        {
            ds.push(op.value);
        }
        else if (op.op == "delete")
        {
            ds.pop();
        }
        else if (op.op == "contains")
        {
            ds.top();
        }
    }

    // Record counters to output file
    record(ds, workload_file, outfile, "heap");
}

template <typename DS>
void record(const DS& ds, string workload_file, ofstream& outfile, const string& structure_name)
{
    // Get counters from data structure
    const Counters& c = ds.get_counters();

    // remove folder name and file extension from file
    string file_name = filesystem::path(workload_file).stem().string();

    // Output structure name and counters to csv file
    outfile << structure_name << ","
            << file_name << ","
            << c.comparisons << ","
            << c.structural_ops << ","
            << c.inserts << ","
            << c.deletes << ","
            << c.lookups << ","
            << c.resize_events << "\n";
}


vector<Operation> parse_workload(ifstream& infile) // Get this from Claude AI
{
    // Vector to hold operation and value
    vector<Operation> operations;
    
    // variable to hold whole file
    string line;

    // Read entire line from workload file (Whole file)
    getline(infile, line);

    // variable to store position of current parsing
    size_t pos = 0;

    // Loop to find all { } blocks in the line
    // and extract operation and value from each block
    while (pos < line.size())
    {
        // Find next {...} block
        size_t start = line.find('{', pos);
        size_t end   = line.find('}', start);

        // If no more blocks, break
        if (start == string::npos || end == string::npos) break;

        // Extract the block as a string
        string token = line.substr(start, end - start + 1);

        // Extract op
        size_t op_start = token.find("\"op\":\"") + 6;
        size_t op_end   = token.find("\"", op_start);
        string operation = token.substr(op_start, op_end - op_start);

        // Extract value
        size_t val_start = token.find("\"value\":") + 8;
        size_t val_end   = token.find('}', val_start);
        int value = stoi(token.substr(val_start, val_end - val_start));

        // Add operation and value to vector
        operations.push_back({operation, value});
        pos = end + 1;
    }

    // Return vector of operations
    return operations;
}