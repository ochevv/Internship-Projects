/*
    This project is for a Marketing Science Analyst Internship and aims to help analyze marketing campaign data. 
    The program reads campaign statistics, processes the data, and provides insights such as calculating averages, 
    tracking performance trends, and identifying top-performing campaigns. 
    It also integrates with an external API to fetch exchange rates for currency conversions.

*/

#include <iostream>
#include <vector> // Provides the vector data structure for storing a list of campaigns.
#include <string>
#include <curl/curl.h> // A library to interact with APIs, like fetching exchange rates.

using namespace std;

// Structures 
struct Campaign 
{
    string name; // Stores the name of the campaign.
    double budget; // Stores the budget of the campaign in USD.
    int clicks; // Stores the number of clicks the campaign received.
    int conversions; // Stores the number of conversions (e.g., purchases) for the campaign.
};

// Classes
class MarketingAnalyzer 
{
private:
    vector<Campaign> campaigns; // A private list to store all the campaigns for analysis.

public:
    void addCampaign(const string& name, double budget, int clicks, int conversions) // Create a new campaign and adds it to the list.
    {
        Campaign newCampaign = { name, budget, clicks, conversions };
        campaigns.push_back(newCampaign);
    }

    double calculateAverageConversionRate() // Calculates the average conversion rate across all campaigns.
    {
        int totalConversions = 0;
        int totalClicks = 0;

        for (const Campaign& campaign : campaigns)  // Loops through each campaign and sums up conversions and clicks.
        {
           totalConversions += campaign.conversions;
            totalClicks += campaign.clicks;
        }

        return totalClicks > 0 ? (static_cast<double>(totalConversions) / totalClicks) * 100 : 0.0;
        // Returns the average conversion rate or 0 if there are no clicks.
    }

    string findTopPerformingCampaign() // Finds the campaign with the highest conversion rate.
    {
        string topCampaign = "None";
        double highestRate = 0.0;

        for (const Campaign& campaign : campaigns) // Loops through each campaign to calculate its conversion rate. 
        {
            
            if (campaign.clicks > 0) 
            {
                double conversionRate = (static_cast<double>(campaign.conversions) / campaign.clicks) * 100;
                if (conversionRate > highestRate) 
                {
                    // Updates the top campaign if the current one has a higher rate.
                    highestRate = conversionRate;
                    topCampaign = campaign.name;
                }
            }
        }

        return topCampaign;
        // Returns the name of the top-performing campaign.
    }

    double fetchExchangeRate(const string& currencyCode) // Fetches the exchange rate from an API. (Mock implementation here.)
    {
        if (currencyCode == "EUR") return 0.85;
        if (currencyCode == "GBP") return 0.75;
        return 1.0; // Default rate (USD to USD).
    }

    void convertBudgets(const string& currencyCode) // Converts all campaign budgets to the specified currency.
    {
        double rate = fetchExchangeRate(currencyCode);
        for (Campaign& campaign : campaigns)  // Loops through each campaign and updates its budget.
        {
            campaign.budget *= rate;
        }
    }
};

int main() 
{
    MarketingAnalyzer analyzer;

    // Adds sample campaigns to the analyzer.
    analyzer.addCampaign("Holiday Promo", 1000.0, 500, 50);
    analyzer.addCampaign("Summer Sale", 1500.0, 700, 100);
    analyzer.addCampaign("Black Friday", 2000.0, 1200, 300);

    // Calculates and displays the average conversion rate.
    cout << "Average Conversion Rate: " << analyzer.calculateAverageConversionRate() << "%" << endl;

    // Finds and displays the top-performing campaign.
    cout << "Top-Performing Campaign: " << analyzer.findTopPerformingCampaign() << endl;

    // Converts budgets to EUR and notifies the user.
    analyzer.convertBudgets("EUR");
    cout << "Budgets converted to EUR successfully!" << endl;

    return 0;
}
