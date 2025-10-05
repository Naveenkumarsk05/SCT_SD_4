#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Structure to hold product information
struct Product {
    string name;
    double price;
    double rating;
};

// Function to save products to CSV file
void saveToCSV(const vector<Product>& products, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }
    file << "Product Name,Price,Rating\n";
    for (const auto& product : products) {
        file << "\"" << product.name << "\"," 
             << product.price << "," 
             << product.rating << "\n";
    }
    file.close();
    cout << "Data successfully saved to " << filename << endl;
}

// Generate sample data
vector<Product> generateSampleData() {
    return {
        {"Wireless Bluetooth Headphones", 49.99, 4.5},
        {"Smart Watch Pro", 199.99, 4.7},
        {"USB-C Charging Cable", 12.99, 4.2},
        {"Laptop Stand Adjustable", 34.99, 4.6},
        {"Mechanical Gaming Keyboard", 89.99, 4.8},
        {"Wireless Mouse", 24.99, 4.3},
        {"HD Webcam 1080p", 59.99, 4.4},
        {"Phone Case Premium", 15.99, 4.1},
        {"Portable Power Bank", 29.99, 4.5},
        {"Screen Protector Pack", 9.99, 4.0}
    };
}

int main() {
    cout << "=== Product Data Generator ===\n\n";

    vector<Product> products = generateSampleData();

    cout << "Generated " << products.size() << " sample products\n";

    // Save to CSV
    string filename = "products.csv";
    saveToCSV(products, filename);

    // Display products
    cout << "\n=== Products ===\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << (i + 1) << ". " << products[i].name 
             << " - $" << products[i].price 
             << " - Rating: " << products[i].rating << "/5\n";
    }

    return 0;
}
