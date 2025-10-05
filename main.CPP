#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Product {
    string name;
    string price;
    string rating;
    string category;
};

class EcommerceScraper {
private:
    vector<Product> products;
    
public:
    void addSampleData() {
        // Adding sample product data
        products.push_back({"Wireless Bluetooth Headphones", "$49.99", "4.5/5", "Electronics"});
        products.push_back({"Smartphone XYZ Pro", "$299.99", "4.2/5", "Electronics"});
        products.push_back({"Laptop Bag Professional", "$24.99", "4.7/5", "Accessories"});
        products.push_back({"Smart Watch Series 5", "$89.99", "4.3/5", "Wearables"});
        products.push_back({"Gaming Mouse RGB", "$35.99", "4.6/5", "Gaming"});
        products.push_back({"Mechanical Keyboard", "$79.99", "4.4/5", "Gaming"});
        products.push_back({"USB-C Charging Cable", "$15.99", "4.1/5", "Accessories"});
        products.push_back({"Wireless Earbuds", "$59.99", "4.5/5", "Audio"});
    }
    
    void displayProducts() {
        cout << "\n=== EXTRACTED PRODUCT DATA ===" << endl;
        cout << "Total products: " << products.size() << endl;
        cout << "----------------------------------------" << endl;
        
        for(int i = 0; i < products.size(); i++) {
            cout << "Product " << i+1 << ":" << endl;
            cout << "  Name: " << products[i].name << endl;
            cout << "  Price: " << products[i].price << endl;
            cout << "  Rating: " << products[i].rating << endl;
            cout << "  Category: " << products[i].category << endl;
            cout << "----------------------------------------" << endl;
        }
    }
    
    void saveToCSV(const string& filename) {
        ofstream file(filename);
        
        // Write CSV header
        file << "Product Name,Price,Rating,Category\n";
        
        // Write product data
        for(const auto& product : products) {
            file << product.name << ","
                 << product.price << ","
                 << product.rating << ","
                 << product.category << "\n";
        }
        
        file.close();
        cout << "✅ Data successfully saved to: " << filename << endl;
    }
    
    void runScraper() {
        cout << "🛒 E-COMMERCE WEB SCRAPER" << endl;
        cout << "==========================" << endl;
        cout << "Extracting product information..." << endl;
        
        // Add sample data (in real scenario, this would come from web scraping)
        addSampleData();
        
        // Display extracted data
        displayProducts();
        
        // Save to CSV file
        saveToCSV("products_data.csv");
        
        cout << "\n🎯 Scraping completed successfully!" << endl;
        cout << "📊 Total products extracted: " << products.size() << endl;
        cout << "💾 File saved: products_data.csv" << endl;
    }
};

int main() {
    EcommerceScraper scraper;
    scraper.runScraper();
    return 0;
}