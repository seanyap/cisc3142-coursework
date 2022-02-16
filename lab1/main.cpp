/* Class: CISC 3142 
   Author: Sean Yap
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>

using namespace std; 

int main() {
  // define variables
  string sku, brand, category, year, price; 
  vector<int>vSKU;
  vector<string>vBrand;
  vector<string>vCategory;
  vector<int>vYear;
  vector<float>vPrice;

  ifstream in_stream; //create a stream object 
  in_stream.open("data.csv", ios_base::in); //opening the file; returns void

  // check if input file is open
  if (in_stream.is_open()) { 
    int row_count = 0;
    while (true) {
      string line, col_data;
      if (!(in_stream >> line)) break; //EOF check 
      if (row_count == 0) { // skip reading header row into vector
        row_count += 1;
        continue;
      }

      stringstream s(line); //break line into words
      // read from every column of a row into a var "col_data"
      vector<string> row;
      while (getline(s, col_data, ',')) {
        row.push_back(col_data);
      }

      // insert column values into their respective vectors
      stringstream ssku(row[0]); 
      int iSKU = 0;
      ssku >> iSKU;
      vSKU.push_back(iSKU);

      vBrand.push_back(row[1]);
      vCategory.push_back(row[2]);

      stringstream syear(row[3]);
      int iYear;
      syear >> iYear;
      vYear.push_back(iYear);

      stringstream sprice(row[4]);
      float fPrice;
      sprice >> fPrice;
      vPrice.push_back(fPrice);

      row_count += 1;
    }

    // create output stream object
    ofstream out_stream;
    out_stream.open("output.txt", ios_base::out);

    if (out_stream.is_open()) {
      // calculate average price per brand
      map <string, vector<float> > brand2prices; 
      // populate map data structure: brand(key) -> prices(values)
      for (int i=0; i<vPrice.size(); i++) {
        brand2prices[vBrand[i]].push_back(vPrice[i]);
      }
      
      // iterate map to sum prices for each brand and find the average price
      map<string, vector<float> >::iterator brand_it;
      out_stream << "--Average Price for Brands--" << endl;
      for (brand_it = brand2prices.begin(); brand_it != brand2prices.end(); brand_it++) {
        float price_sum = 0.0;
        vector<float> brand2prices = brand_it->second;
        for (int i=0; i<brand2prices.size(); i++) { // sum the prices for current brand
          price_sum += brand2prices[i];
        }
        out_stream << brand_it->first << ": " << price_sum / brand2prices.size() << endl;
      }
	    out_stream << endl;

      // calculate average price per category
      map <string, vector<float> > category2prices; 
      // populate map data structure: category(key) -> prices(values)
      for (int i=0; i<vPrice.size(); i++) {
        category2prices[vCategory[i]].push_back(vPrice[i]);
      }
      
      // iterate map to sum prices for each category and find the average price
      map<string, vector<float> >::iterator category_it;
      out_stream << "--Average Price for Categories--" << endl;
      for (category_it = category2prices.begin(); category_it != category2prices.end(); category_it++){
        float price_sum = 0.0;
        vector<float> category2prices = category_it->second;
        for (int i=0; i<category2prices.size(); i++) {  // sum the prices for current category
          price_sum += category2prices[i];
        }
        out_stream << category_it->first << ": " << price_sum / category2prices.size() << endl;
      }
	    out_stream << endl;

      // list skus and their count for each unique year 
      map <int, vector<string> > year2sku; // year -> sku
      for (int i=0; i<vYear.size(); i++) {
        ostringstream sku_str;
        sku_str << vSKU[i];
        year2sku[vYear[i]].push_back(sku_str.str());
      }

      // create map data structure to relate relationships between unique year and sku
      map<int, vector<string> >::iterator year_it;
      out_stream << "--Unique Year and SKUs--" << endl;
      for (year_it = year2sku.begin(); year_it != year2sku.end(); year_it++){
        vector<string> cur_year_skus = year_it->second;
        out_stream << year_it->first << " (" << cur_year_skus.size() << ") : ";
        for (int i=0; i<cur_year_skus.size(); i++){ // print all the skus for current year
          out_stream << cur_year_skus[i] << " ";
        }
        out_stream << endl;
      }
    } else {
      cout << "Unable to open output file";
    }

    in_stream.close(); 
    out_stream.close();

  } else {
    cout << "Unable to open input file"; 
  }
  return 0;
}