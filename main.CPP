#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <sstream>
#include <regex>

using namespace std;

// Structure to hold product information
struct Product {
    string name;
    double price;
    double rating;
};

// Callback function to write data received from curl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to download HTML content from URL
string downloadHTML(const string& url) {
    CURL* curl;
    CURLcode res;
    string htmlContent;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlContent);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
        
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }
        
        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
    return htmlContent;
}

// Function to extract product information using regex
vector<Product> extractProducts(const string& html) {
    vector<Product> products;
    
    // Example regex patterns - these need to be adjusted based on actual website structure
    // Pattern for product name (looking for common e-commerce patterns)
    regex namePattern(R"(<h[2-4][^>]*class=[^>]*product[^>]*>([^<]+)</h[2-4]>)", regex::icase);
    
    // Pattern for price (looking for dollar amounts)
    regex pricePattern(R"(\$([0-9]+\.?[0-9]*))");
    
    // Pattern for rating (looking for rating values)
    regex ratingPattern(R"(rating[\"']?\s*[:=]\s*[\"']?([0-5]\.?[0-9]*))", regex::icase);
    
    // Split HTML into product sections (basic approach)
    regex productSectionPattern(R"(<div[^>]*class=[^>]*product[^>]*>.*?</div>)", regex::icase);
    
    auto sections_begin = sregex_iterator(html.begin(), html.end(), productSectionPattern);
    auto sections_end = sregex_iterator();
    
    for (sregex_iterator i = sections_begin; i != sections_end; ++i) {
        smatch section_match = *i;
        string section = section_match.str();
        
        Product product;
        product.name = "Unknown";
        product.price = 0.0;
        product.rating = 0.0;
        
        // Extract name
        smatch name_match;
        if (regex_search(section, name_match, namePattern)) {
            product.name = name_match[1].str();
        }
        
        // Extract price
        smatch price_match;
        if (regex_search(section, price_match, pricePattern)) {
            product.price = stod(price_match[1].str());
        }
        
        // Extract rating
        smatch rating_match;
        if (regex_search(section, rating_match, ratingPattern)) {
            product.rating = stod(rating_match[1].str());
        }
        
        if (product.name != "Unknown") {
            products.push_back(product);
        }
    }
    
    return products;
}

// Function to save products to CSV file
void saveToCSV(const vector<Product>& products, const string& filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }
    
    // Write CSV header
    file << "Product Name,Price,Rating\n";
    
    // Write product data
    for (const auto& product : products) {
        file << "\"" << product.name << "\"," 
             << product.price << "," 
             << product.rating << "\n";
    }
    
    file.close();
    cout << "Data successfully saved to " << filename << endl;
}

// Alternative: Simulated data for demonstration purposes
vector<Product> generateSampleData() {
    vector<Product> products;
    
    products.push_back({"Wireless Bluetooth Headphones", 49.99, 4.5});
    products.push_back({"Smart Watch Pro", 199.99, 4.7});
    products.push_back({"USB-C Charging Cable", 12.99, 4.2});
    products.push_back({"Laptop Stand Adjustable", 34.99, 4.6});
    products.push_back({"Mechanical Gaming Keyboard", 89.99, 4.8});
    products.push_back({"Wireless Mouse", 24.99, 4.3});
    products.push_back({"HD Webcam 1080p", 59.99, 4.4});
    products.push_back({"Phone Case Premium", 15.99, 4.1});
    products.push_back({"Portable Power Bank", 29.99, 4.5});
    products.push_back({"Screen Protector Pack", 9.99, 4.0});
    
    return products;
}

int main() {
    cout << "=== E-commerce Product Data Extractor ===\n\n";
    
    int choice;
    cout << "Select mode:\n";
    cout << "1. Extract from URL (requires libcurl)\n";
    cout << "2. Use sample data (demonstration)\n";
    cout << "Enter choice (1 or 2): ";
    cin >> choice;
    cin.ignore();
    
    vector<Product> products;
    
    if (choice == 1) {
        string url;
        cout << "Enter e-commerce website URL: ";
        getline(cin, url);
        
        cout << "Downloading webpage...\n";
        string html = downloadHTML(url);
        
        if (html.empty()) {
            cerr << "Error: Could not download webpage\n";
            return 1;
        }
        
        cout << "Extracting product information...\n";
        products = extractProducts(html);
        
        cout << "Found " << products.size() << " products\n";
    } else {
        cout << "Generating sample product data...\n";
        products = generateSampleData();
        cout << "Generated " << products.size() << " sample products\n";
    }
    
    // Save to CSV
    string filename = "products.csv";
    saveToCSV(products, filename);
    
    // Display extracted products
    cout << "\n=== Extracted Products ===\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << (i + 1) << ". " << products[i].name 
             << " - $" << products[i].price 
             << " - Rating: " << products[i].rating << "/5\n";
    }
    
    return 0;
}