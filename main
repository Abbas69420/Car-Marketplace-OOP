#include <iostream>
#include <cmath>
#include "Vehicle.h"
#include "Account.h"
using namespace std;

class Car;
class Bike;
class Truck;
class Message;
class Review;
class Listing;
class Seller;
class Buyer;
class Admin;
class InspectionReport;
class Marketplace;

class Car : public Vehicle
{
private:
    int doors;
    int seatingCapacity;

public:
    Car() : Vehicle(), doors(4), seatingCapacity(5) {}

    Car(string brand, string model, int year, int mileage, string colour, string transmission, int doors, int seatingCapacity)
        : Vehicle(brand, model, year, mileage, colour, transmission), doors(doors), seatingCapacity(seatingCapacity) {}

    void displayDetails() const override
    {
        Vehicle::displayDetails();
        cout << "Vehicle Type: Car" << endl;
        cout << "Doors: " << doors << endl;
        cout << "Seating Capacity: " << seatingCapacity << " persons" << endl;
    }

    string getVehicleType() const override
    {
        return "Car";
    }

    int getDoors() const
    {
        return doors;
    }

    int getSeatingCapacity() const
    {
        return seatingCapacity;
    }
};

class Bike : public Vehicle
{
private:
    int engineCC;
    bool hasSidecar;

public:
    Bike() : Vehicle(), engineCC(0), hasSidecar(false) {}

    Bike(string brand, string model, int year, int mileage, string colour, string transmission, int engineCC, bool hasSidecar)
        : Vehicle(brand, model, year, mileage, colour, transmission), engineCC(engineCC), hasSidecar(hasSidecar) {}

    void displayDetails() const override
    {
        Vehicle::displayDetails();
        cout << "Vehicle Type: Bike" << endl;
        cout << "Engine CC: " << engineCC << " cc" << endl;
        cout << "Has Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
    }

    string getVehicleType() const override
    {
        return "Bike";
    }

    int getEngineCC() const
    {
        return engineCC;
    }

    bool getHasSidecar() const
    {
        return hasSidecar;
    }
};

class Truck : public Vehicle
{
private:
    double cargoCapacity;
    int axles;
    string cargoType;

public:
    Truck() : Vehicle(), cargoCapacity(0), axles(2), cargoType("General") {}

    Truck(string brand, string model, int year, int mileage, string colour, string transmission, double cargoCapacity, int axles, string cargoType)
        : Vehicle(brand, model, year, mileage, colour, transmission), cargoCapacity(cargoCapacity), axles(axles), cargoType(cargoType) {}

    void displayDetails() const override
    {
        Vehicle::displayDetails();
        cout << "Vehicle Type: Truck" << endl;
        cout << "Cargo Capacity: " << cargoCapacity << " tons" << endl;
        cout << "Number of Axles: " << axles << endl;
        cout << "Cargo Type: " << cargoType << endl;
    }

    string getVehicleType() const override
    {
        return "Truck";
    }

    double getCargoCapacity() const
    {
        return cargoCapacity;
    }

    int getAxles() const
    {
        return axles;
    }

    string getCargoType() const
    {
        return cargoType;
    }
};

class Message
{
    int messageId;
    Account *sender;
    Account *receiver;
    string content;
    string timestamp;
    bool isRead;
    static int totalMessages;

public:
    Message(Account *from, Account *to, string text)
    {
        this->messageId = totalMessages++;
        this->sender = from;
        this->receiver = to;
        this->content = text;
        this->timestamp = "01/01/1970 00:00 PKT";
        this->isRead = false;
    }

    void markAsRead()
    {
        isRead = true;
    }

    void editContent(string newContent)
    {
        content = newContent + " (Edited)";
    }

    bool getReadStatus() const
    {
        return isRead;
    }

    friend istream &operator>>(istream &input, Message &m);
};

istream &operator>>(istream &input, Message &m)
{
    cout << "\n--- Message #" << m.messageId << " ---" << endl;
    cout << "Date: " << m.timestamp << (m.isRead ? " [Read]" : " [Unread]") << endl;
    cout << "Message: " << m.content << endl;
    cout << "-------------------" << endl;
}

class Review
{
private:
    int reviewId;
    Account *reviewer;
    Account *reviewee;
    double rating;
    string comment;
    int helpfulVotes;
    static int totalReviews;

public:
    Review(Account *from, Account *to, double stars, string text)
    {
        this->reviewId = totalReviews++;
        this->reviewer = from;
        this->reviewee = to;
        this->rating = max(1.0, min(stars, 5.0));

        if (stars < 1.0 || stars > 5.0)
        {
            cout << "Invalid rating provided. Rating must be between 1 and 5 stars. Defaulting to 3 stars." << endl;
            this->rating = 3.0;
        }

        this->comment = text;
        this->helpfulVotes = 0;
    }

    void addHelpfulVote()
    {
        helpfulVotes++;
    }

    void updateComment(string newText)
    {
        comment = newText;
    }

    double getRating() const
    {
        return rating;
    }

    friend istream &operator>>(istream &input, Review &r);
};

istream &operator>>(istream &input, Review &r)
{
    cout << "\n[User Review #" << r.reviewId << "]" << endl;
    cout << "Rating: " << r.rating << "/5.0 Stars" << endl;
    cout << "Comment: \"" << r.comment << "\"" << endl;
    cout << "Helpful Votes: " << r.helpfulVotes << endl;
}

class Listing
{
private:
    int listingId;
    double price;
    string location;
    string description;
    Account *seller;
    string status;
    Vehicle *car;

public:
    static int totalListings;

    Listing() : listingId(0), price(0), location(""),
                description(""), seller(nullptr), status("Pending"),
                car(nullptr) {}

    Listing(double price, string location, string description, Account *seller, Vehicle *v)
    {
        this->listingId = totalListings++;
        this->price = price;
        this->location = location;
        this->description = description;
        this->seller = seller;
        this->status = "Pending";
        this->car = v;
    }

    void approve()
    {
        this->status = "Active";
    }

    void forceRemove()
    {
        this->status = "Removed by admin";
    }

    friend istream &operator>>(istream &input, Listing &l);

    void updatePrice(double newPrice)
    {
        price = newPrice;
    }

    void toggleStatus()
    {
        if (status == "Active")
        {
            status = "Sold";
        }
        else
        {
            status = "Active";
        }
    }

    void calculateInstallment(double downPaymentPercent, int years, double annualInterestRate) const
    {
        double principal = price * (1 - (downPaymentPercent / 100));
        double monthlyRate = annualInterestRate / 12 / 100;
        int months = years * 12;

        if (monthlyRate == 0)
        {
            cout << "Invalid interest rate." << endl;
            return;
        }

        double emi = (principal * monthlyRate * pow(1 + monthlyRate, months)) / (pow(1 + monthlyRate, months) - 1);

        cout << "\n--- Financing Estimate ---" << endl;
        cout << "Down Payment: PKR " << price * (downPaymentPercent / 100) << endl;
        cout << "Financed Amount: PKR " << principal << endl;
        cout << "Monthly Installment: PKR " << emi << " for " << months << " months" << endl;
    }

    int getListingId() const
    {
        return listingId;
    }

    Vehicle *getVehicle() const
    {
        return car;
    }

    double getPrice() const
    {
        return price;
    }

    string getLocation() const
    {
        return location;
    }

    Account *getSeller() const
    {
        return seller;
    }
};

istream &operator>>(istream &input, Listing &l)
{
    cout << "\n====================" << endl;
    cout << "Listing#" << l.listingId << endl;
    cout << "\n====================" << endl;
    cout << "Seller Details:" << endl;

    if (l.seller != nullptr)
    {
        l.seller->displayDetails();
    }

    cout << "Price: PKR " << l.price << endl;
    cout << "Location: " << l.location << endl;
    cout << "Description: " << l.description << endl;
    cout << "Status: " << l.status << endl;
    cout << "Vehicle Details:" << endl;
    if (l.car != nullptr)
    {
        l.car->displayDetails();
    }
}

class Seller : public Account
{
    double sellerRating;
    int totalSales;
    string city;
    string preferredContactMethod;
    int totalListings;
    int activeListings;
    string memberSince;
    bool verified;
    int messages;
    Review **reviews;
    int reviewCount;

public:
    Seller(string email, string firstName, string lastName, string phone, char gender, string dob, string city, string preferredContactMethod, int messages)
        : Account(email, firstName, lastName, phone, gender, dob)
    {
        this->city = city;
        this->preferredContactMethod = preferredContactMethod;
        this->sellerRating = 5.0;
        this->totalSales = 0;
        this->totalListings = 0;
        this->activeListings = 0;
        this->memberSince = "1/1/1970";
        this->verified = false;
        this->messages = 0;
        this->reviews = nullptr;
        this->reviewCount = 0;
    }

    Seller(const Seller &other) : Account(other)
    {
        sellerRating = other.sellerRating;
        totalSales = other.totalSales;
        city = other.city;
        preferredContactMethod = other.preferredContactMethod;
        totalListings = other.totalListings;
        activeListings = other.activeListings;
        memberSince = other.memberSince;
        verified = other.verified;
        messages = other.messages;
        reviewCount = other.reviewCount;

        if (other.reviewCount > 0)
        {
            reviews = new Review *[other.reviewCount];
            for (int i = 0; i < other.reviewCount; i++)
            {
                reviews[i] = other.reviews[i];
            }
        }
        else
        {
            reviews = nullptr;
        }
    }

    Seller &operator=(const Seller &other)
    {
        if (this == &other)
            return *this;
        Account::operator=(other);
        delete[] reviews;

        sellerRating = other.sellerRating;
        totalSales = other.totalSales;
        city = other.city;
        preferredContactMethod = other.preferredContactMethod;
        totalListings = other.totalListings;
        activeListings = other.activeListings;
        memberSince = other.memberSince;
        verified = other.verified;
        messages = other.messages;
        reviewCount = other.reviewCount;

        if (other.reviewCount > 0)
        {
            reviews = new Review *[other.reviewCount];
            for (int i = 0; i < other.reviewCount; i++)
            {
                reviews[i] = other.reviews[i];
            }
        }
        else
        {
            reviews = nullptr;
        }
        return *this;
    }

    void updateSellerRating(double newRating)
    {
        sellerRating = newRating;
    }

    void incrementSales()
    {
        totalSales++;
    }

    void incrementListings()
    {
        totalListings++;
        activeListings++;
    }

    void applyForVerification()
    {
        verified = true;
    }

    void decrementActiveListings()
    {
        if (activeListings > 0)
        {
            activeListings--;
        }
    }

    void displayDetails() const
    {
        cout << firstName << " " << lastName << endl;
        cout << accountId << endl;
        cout << email << endl;
        cout << phone << endl;
        cout << "Seller Rating: " << sellerRating << "/5" << endl;
        cout << "Total Sales: " << totalSales << endl;
        cout << "City: " << city << endl;
        cout << "Preferred Contact Method: " << preferredContactMethod << endl;
    }

    void addReview(Review *newReview)
    {
        Review **temp = new Review *[reviewCount + 1];
        for (int i = 0; i < reviewCount; i++)
        {
            temp[i] = reviews[i];
        }
        temp[reviewCount] = newReview;
        delete[] reviews;
        reviews = temp;
        reviewCount++;
        double totalScore = 0;
        for (int i = 0; i < reviewCount; i++)
        {
            totalScore += reviews[i]->getRating();
        }
        sellerRating = totalScore / reviewCount;

        cout << "New review added for " << firstName << ". Rating updated to: " << sellerRating << "/5.0" << endl;
    }

    void displayReviews() const
    {
        cout << "\n--- Seller Reviews ---" << endl;
        if (reviewCount == 0)
        {
            cout << "No reviews yet." << endl;
            return;
        }
        for (int i = 0; i < reviewCount; i++)
        {
            cout << reviews[i];
            cout << "--------------------" << endl;
        }
    }

    string getAccountType() const override
    {
        return "Seller";
    }

    ~Seller()
    {
        for (int i = 0; i < reviewCount; i++)
        {
            delete reviews[i];
        }
        delete[] reviews;
    }
};

class Buyer : public Account
{
    Listing **favourites;
    int favouritesT;
    string city;
    int messages;
    string memberSince;
    bool verified;

public:
    Buyer(string email, string firstName, string lastName, string phone, char gender, string dob, string city, int messages)
        : Account(email, firstName, lastName, phone, gender, dob)
    {
        this->favourites = nullptr;
        this->favouritesT = 0;
        this->city = city;
        this->messages = 0;
        this->memberSince = "1/1/1970";
        this->verified = false;
    }

    Buyer(const Buyer &other) : Account(other)
    {
        city = other.city;
        messages = other.messages;
        memberSince = other.memberSince;
        verified = other.verified;
        favouritesT = other.favouritesT;

        if (other.favouritesT > 0)
        {
            favourites = new Listing *[other.favouritesT];
            for (int i = 0; i < other.favouritesT; i++)
            {
                favourites[i] = other.favourites[i];
            }
        }
        else
        {
            favourites = nullptr;
        }
    }

    Buyer &operator=(const Buyer &other)
    {
        if (this == &other)
            return *this;
        Account::operator=(other);
        delete[] favourites;

        city = other.city;
        messages = other.messages;
        memberSince = other.memberSince;
        verified = other.verified;
        favouritesT = other.favouritesT;

        if (other.favouritesT > 0)
        {
            favourites = new Listing *[other.favouritesT];
            for (int i = 0; i < other.favouritesT; i++)
            {
                favourites[i] = other.favourites[i];
            }
        }
        else
        {
            favourites = nullptr;
        }
        return *this;
    }

    void addToFavourites(Listing *listing)
    {
        if (listing == nullptr)
        {
            return;
        }

        Listing **temp = new Listing *[favouritesT + 1];
        for (int i = 0; i < favouritesT; i++)
        {
            temp[i] = favourites[i];
        }
        temp[favouritesT] = listing;
        delete[] favourites;
        favourites = temp;
        favouritesT++;
    }

    void removeFromFavourites(int listingId)
    {
        int removeId = -1;
        for (int i = 0; i < favouritesT; i++)
        {
            if (favourites[i]->getListingId() == listingId)
            {
                removeId = i;
                break;
            }
        }

        if (removeId == -1)
        {
            cout << "Listing not found in favourites." << endl;
            return;
        }

        Listing **temp = new Listing *[favouritesT - 1];
        int j = 0;
        for (int i = 0; i < favouritesT; i++)
        {
            if (i == removeId)
            {
                continue;
            }
            temp[j] = favourites[i];
            j++;
        }
        delete[] favourites;
        favourites = temp;
        favouritesT--;
    }

    void applyForVerification()
    {
        verified = true;
    }

    void displayFavourites() const
    {
        cout << "Favourite Listings:" << endl;
        if (favouritesT == 0)
        {
            cout << "No favourite listings yet." << endl;
            return;
        }
        for (int i = 0; i < favouritesT; i++)
        {
            cout << favourites[i];
            cout << "--------------------" << endl;
        }
    }

    void displayDetails() const
    {
        cout << firstName << " " << lastName << endl;
        cout << accountId << endl;
        cout << email << endl;
        cout << phone << endl;
        cout << "City: " << city << endl;
        cout << "Member Since: " << memberSince << endl;
    }

    string getAccountType() const override
    {
        return "Buyer";
    }

    ~Buyer()
    {
        delete[] favourites;
    }
};

class Admin : public Account
{
    int adminLevel;
    string department;
    int actionsTaken;
    string officeLocation;
    string shift;
    bool canManageAdmins;

public:
    Admin(string email, string firstName, string lastName, string phone, char gender, string dob, int level, string dept)
        : Account(email, firstName, lastName, phone, gender, dob)
    {
        this->adminLevel = level;
        this->department = dept;
        this->actionsTaken = 0;
        this->officeLocation = "Karachi HQ";
        this->shift = "Standard";
        this->canManageAdmins = (level == 2);
    }

    void approveListing(Listing *ad)
    {
        if (ad != nullptr)
        {
            ad->approve();
            actionsTaken++;
            cout << "Admin " << firstName << " approved the listing." << endl;
        }
    }

    void removeListing(Listing *ad)
    {
        if (ad != nullptr)
        {
            ad->forceRemove();
            actionsTaken++;
            cout << "Admin " << firstName << " forcefully removed the listing." << endl;
        }
    }

    void banUserAccount(Account *user)
    {
        if (user != nullptr)
        {
            user->setBannedStatus(true);
            actionsTaken++;
            cout << "USER BANNED. Trust & Safety action logged." << endl;
        }
    }

    void displayDetails() const
    {
        cout << "\n[ADMINISTRATOR PROFILE]" << endl;
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Department: " << department << " | Level: " << adminLevel << endl;
        cout << "Moderation Actions Taken: " << actionsTaken << endl;
    }

    string getAccountType() const override
    {
        return "Admin";
    }
};

class InspectionReport
{
private:
    int reportId;
    Vehicle *inspectedCar;
    int engineScore;
    int exteriorScore;
    int interiorScore;
    int suspensionScore;
    string inspectorRemarks;
    string inspectionDate;
    static int totalReports;

public:
    InspectionReport(Vehicle *car, int engine, int exterior, int interior, int suspension, string remarks)
    {
        this->reportId = totalReports++;
        this->inspectedCar = car;
        this->engineScore = engine;
        this->exteriorScore = exterior;
        this->interiorScore = interior;
        this->suspensionScore = suspension;
        this->inspectorRemarks = remarks;
        this->inspectionDate = "01/01/1970"; // Default date, can be updated later
    }

    double getOverallScore() const
    {
        return (engineScore + exteriorScore + interiorScore + suspensionScore) / 4.0;
    }

    bool isCertified() const
    {
        return (getOverallScore() >= 80.0 && engineScore >= 85);
    }

    void updateRemarks(string newRemarks)
    {
        this->inspectorRemarks = newRemarks;
    }

    void displayReport() const
    {
        cout << "\n=======================================" << endl;
        cout << "  PAKWHEELS 200+ POINT INSPECTION" << endl;
        cout << "=======================================" << endl;
        cout << "Report ID: " << reportId << " | Date: " << inspectionDate << endl;

        if (inspectedCar != nullptr)
        {
            cout << "Vehicle: ";
            inspectedCar->displayDetails();
        }

        cout << "\n--- SCORES ---" << endl;
        cout << "Engine & Transmission: " << engineScore << "/100" << endl;
        cout << "Exterior & Body:       " << exteriorScore << "/100" << endl;
        cout << "Interior:              " << interiorScore << "/100" << endl;
        cout << "Suspension & Steering: " << suspensionScore << "/100" << endl;

        cout << "\nOverall Score: " << getOverallScore() << "/100" << endl;
        if (isCertified())
        {
            cout << "*** OFFICIAL PAKWHEELS CERTIFIED ***" << endl;
        }
        cout << "Inspector Remarks: " << inspectorRemarks << endl;
        cout << "=======================================\n"
             << endl;
    }
};

class Marketplace
{
    Account **users;
    int userCount;

    Listing **listings;
    int listingCount;

public:
    const string PLATFORM_NAME = "PakWheels";
    const int MAX_LISTINGS_PER_USER = 10;

    Marketplace()
    {
        users = nullptr;
        userCount = 0;
        listings = nullptr;
        listingCount = 0;
    }

    Marketplace(const Marketplace &) = delete;

    void registerAccount(Account *newAccount)
    {
        Account **temp = new Account *[userCount + 1];
        for (int i = 0; i < userCount; i++)
        {
            temp[i] = users[i];
        }
        temp[userCount] = newAccount;
        delete[] users;
        users = temp;
        userCount++;
    }

    void postListing(Listing *newListing)
    {
        if (newListing == nullptr || newListing->getSeller() == nullptr)
        {
            cout << "Invalid listing." << endl;
            return;
        }

        int sellerListigns = 0;
        int targetAccountId = newListing->getSeller()->getAccountId();

        for (int i = 0; i < listingCount; i++)
        {
            if (listings[i]->getSeller()->getAccountId() == targetAccountId)
            {
                sellerListigns++;
            }
        }

        if (sellerListigns >= MAX_LISTINGS_PER_USER)
        {
            cout << "You have reached the maximum number of active listings allowed (" << MAX_LISTINGS_PER_USER << ")." << endl;
            return;
        }
        Listing **temp = new Listing *[listingCount + 1];
        for (int i = 0; i < listingCount; i++)
        {
            temp[i] = listings[i];
        }
        temp[listingCount] = newListing;
        delete[] listings;
        listings = temp;
        listingCount++;
        cout << "Successfully posted listing to the marketplace!" << endl;
    }

    void removeListing(int listingId)
    {
        int removeId = -1;
        for (int i = 0; i < listingCount; i++)
        {
            if (listings[i]->getListingId() == listingId)
            {
                removeId = i;
                break;
            }
        }

        if (removeId == -1)
        {
            cout << "Listing not found." << endl;
            return;
        }

        Listing **temp = new Listing *[listingCount - 1];
        int j = 0;
        for (int i = 0; i < listingCount; i++)
        {
            if (i == removeId)
            {
                delete listings[i];
                continue;
            }
            temp[j] = listings[i];
            j++;
        }
        delete[] listings;
        listings = temp;
        listingCount--;
    }

    void searchListings(string brand)
    {
        cout << "Search results for brand: " << brand << endl;
        for (int i = 0; i < listingCount; i++)
        {
            if (listings[i]->getVehicle() != nullptr && listings[i]->getVehicle()->getBrand() == brand)
            {
                cout << listings[i];
                cout << "--------------------" << endl;
            }
        }
    }

    void filterSearchResults(double minPrice = -1, double maxPrice = 1000000000, string model = "", string location = "", int year = -1, int mileage = -1)
    {
        int matchCount = 0;
        for (int i = 0; i < listingCount; i++)
        {
            Listing *current = listings[i];
            bool isMatch = true;

            if (minPrice != -1 && current->getPrice() < minPrice)
                isMatch = false;
            if (maxPrice != -1 && current->getPrice() > maxPrice)
                isMatch = false;

            if (location != "" && current->getLocation() != location)
                isMatch = false;

            const Vehicle *currentCar = current->getVehicle();
            if (currentCar != nullptr)
            {
                if (model != "" && currentCar->getModel() != model)
                    isMatch = false;

                if (year != -1 && currentCar->getYear() < year)
                    isMatch = false;

                if (mileage != -1 && currentCar->getMileage() > mileage)
                    isMatch = false;
            }
            else
            {
                isMatch = false;
            }

            if (isMatch && current->getListingId() != -1)
            {
                cout << current;
                matchCount++;
            }
        }

        if (matchCount == 0)
        {
            cout << "No listings found matching your criteria." << endl;
        }
        else
        {
            cout << "Total matches found: " << matchCount << endl;
        }
    }

    Listing **getListings()
    {
        return listings;
    }

    ~Marketplace()
    {

        if (users != nullptr)
        {
            for (int i = 0; i < userCount; i++)
                delete users[i];
            delete[] users;
        }

        if (listings != nullptr)
        {
            for (int i = 0; i < listingCount; i++)
                delete listings[i];
            delete[] listings;
        }
    }
};

int Account::totalAccountsCreated = 0;
int Listing::totalListings = 0;
int InspectionReport::totalReports = 0;
int Message::totalMessages = 0;
int Review::totalReviews = 0;

int main()
{
    cout << "Welcome to " << Marketplace().PLATFORM_NAME << " - Pakistan's Largest Car Marketplace!" << endl;
}
