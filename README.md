# Assignment 2: PakWheels

## Submitted by:
- Name: Syed Muhammad Abbas
- Roll: 25K-0023
- Course: Object Oriented Programming

# 1. Overview

By using fundamentals of Object Oriented Programming, I have developed a Car Marketplace system similar to PakWheels or you could say I tried to implement PakWheels in my own way. However, I only implemented the back-end and it is open for front-end implementation.

The code is organized into a header/source structure: `Vehicle.h` defines an abstract `Vehicle` base class and `Account.h` defines an abstract `Account` base class. The main implementation file `PakWheels.cpp` contains derived classes such as `Car`, `Bike`, `Truck`, `Seller`, `Buyer`, `Admin`, as well as supporting classes like `Listing`, `Message`, `Review`, `InspectionReport`, and `Marketplace`.

I have replicated some features or atleast tried to by implementing some OOP features like encapsulation, inheritance, abstraction, aggregation & composition, etc. I tried to recreate the vehicle searching feature along with the options to add listings to favourites and messaging across the marketplace, I have also implemented an account creation system and the option for admin to approve or delete listings and even ban users.

---
### I am gonna do a comparison of the actual website and my code:

## PakWheels Homepage

![PakWheels Homepage](pakwheels_homepage.png)

```cpp
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
```
This function allows the user to freely search the Marketplace for listings and add them to favourites.

## Posting listings

![Posting a Listing](post_an_ad.png)

```cpp
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
```
While it might seem like a very complex function but in reality it is quite simple, it just increments the amount of listings across the Marketplace and adds the listing to the array of listings after checking a few conditions.

## Listings

![Vehicle Listings](listings.jpeg)
This is how it looks after listings are posted however I have made a search based system, implementing this was not really my cup of tea.

---


### 1.1 Homepage Listing Layout
The system dynamically displays structural marketplace entities using standard PakWheels layout markers:
* **Identity Headers:** Vehicle brand, model year, and explicit manufacturing type.
* **Pricing Parameters:** Local currency conversion formatted as PKR values.
* **Geographic Placement:** Granular location tracking per advertisement.
* **Performance Metrics:** Direct evaluation of mileage (`km`) and transmission configs.

### 1.2 Search and Filter System
Mirroring real-world engine searching mechanics, the platform avoids basic flat-string matching. The `filterSearchResults()` algorithm in the `Marketplace` context handles complex logical queries with optional evaluations for:
* Manufacturing Brand & Model names
* Dynamic price bounds (Floor/Ceiling limits)
* Mileage wear constraints and minimum creation years

### 1.3 User Messaging System
The communications sub-system mirrors the transactional messaging system used on PakWheels. Peer-to-peer dialogues are handled by dynamically allocated and expanding message queues associated with user identities.

---

## 2. Classes Implemented
The platform utilizes an architecture consisting of 13 interconnected classes:

### Core Management & Infrastructure
1. `Marketplace`: The main orchestrator managing global state arrays for accounts and advertisements.
2. `InspectionReport`: A diagnostic tool evaluating core vehicle components with conditional certification logic.
3. `Message`: Custom communication blocks with metadata, tracking timelines, and read/unread statuses.
4. `Review`: Quantifiable performance feedback metrics complete with helpfulness evaluation counters.
5. `Listing`: The core listing entity that holds a polymorphic vehicle reference alongside target seller associations.

### Polymorphic Vehicle Subsystem
6. `Vehicle` *(Abstract Base Class)*: The core vehicle attribute definition block.
7. `Car` *(Derived from Vehicle)*: Adds specific passenger specifications (`doors`, `seatingCapacity`).
8. `Bike` *(Derived from Vehicle)*: Adds custom two-wheeler definitions (`engineCC`, `hasSidecar`).
9. `Truck` *(Derived from Vehicle)*: Captures heavy-freight configurations (`cargoCapacity`, `axles`, `cargoType`).

### Identity & Account Subsystem
10. `Account` *(Abstract Base Class)*: Encapsulates baseline security, profile details, and private message collections.
11. `Seller` *(Derived from Account)*: Manages merchant ratings, tracking metrics, and dynamic arrays of customer reviews.
12. `Buyer` *(Derived from Account)*: Features target utility arrays tracking individual favorite listings.
13. `Admin` *(Derived from Account)*: High-clearance profile containing functional hooks to override system states and issue user bans.

---

## 3. Constructors and Design Decisions

### 3.1 Pure Virtual Functions & Abstract Frameworks
To guarantee type safety, both `Vehicle` and `Account` are explicitly engineered as **Abstract Base Classes** using pure virtual functions:
* `virtual string getVehicleType() const = 0;`
* `virtual string getAccountType() const = 0;`

This explicitly blocks developers from accidentally instantiating a raw `Vehicle` or generic `Account` object, forcing all platform objects to safely take on specialized sub-types.

### 3.2 Parameterized Constructors
Parameterized constructors are explicitly used across all 13 structures to guarantee structural integrity. Default states are guarded with explicit parameters, ensuring that empty or invalid structural models cannot corrupt runtime arrays.

### 3.3 Explicit Copy Constructors & Deep Memory Assignment
Because `Account`, `Seller`, and `Buyer` manage dynamic raw pointer collections (`Message** inbox`, `Review** reviews`, `Listing** favourites`), default memory copying would trigger catastrophic dangling references and double-deletion faults. 

The architecture implements robust custom copy constructors and overloaded assignment operators (`operator=`). These loop through existing elements to perform explicit heap re-allocations, isolating memory addresses across distinct instances.

```cpp
Account(const Account &other) {
    // Member copying...
    if (other.messageCount > 0) {
        inbox = new Message *[other.messageCount];
        for (int i = 0; i < other.messageCount; i++) {
            inbox[i] = other.inbox[i];
        }
    } else {
        inbox = nullptr;
    }
```

### 3.4 Virtual Destructors

To maintain strict memory hygiene across deep inheritance lines, the `Account` and `Vehicle` base classes feature explicit `virtual` destructors. This ensures that when a derived object is wiped from memory via a base pointer, the complete chain of derived destructors fires down the line, stopping memory leaks in their tracks.

---

## 4. Constants and Constant Functions

System invariants are strictly protected via the `const` declaration framework:

* **System Safeguards:** Global rules like `PLATFORM_NAME` and `MAX_LISTINGS_PER_USER` are locked as constants inside the `Marketplace` class.
* **State Verification Safety:** Evaluation methods, search displays, and string lookups are explicitly marked as constant functions (`const`). This prevents accidental state changes or data mutations during data reads.

---

## 5. Static Class Members

Global telemetry tracking and ID generation tracking are managed securely without relying on global variables by using static variables:

* `totalAccountsCreated`
* `totalListings`
* `totalMessages`
* `totalReviews`
* `totalReports`

Every constructor call captures the atomicity of the post-increment operator (`totalListings++`), assigning absolute, collision-free identifiers to new platform records.

---

## 6. Composition and Aggregation

### 6.1 Aggregation Relationships (Polymorphic Association)

* **Listing to Vehicle Selection (`Vehicle* car`):** The code uses a polymorphic base pointer to point to generic vehicles. Because a listing holds a pointer to a vehicle created elsewhere, this represents an **Aggregation** relationship. This is a critical design choice: it allows a listing to point to a `Car`, `Bike`, or `Truck` dynamically at runtime.
* **Listing to Seller Identity (`Account* seller`):** Listings maintain non-owning reference pointers tracking merchant accounts. If a specific listing is cleared from the database, the underlying user profile persists.

### 6.2 Composition Relationships (Strong Ownership)

* **Seller to Review Collection (`Review reviews`):** The `Seller` class maintains absolute ownership over its collection of customer review logs. When a merchant profile is purged, its entire tracking array of reviews is deleted directly inside the `~Seller()` destructor.

---

## 7. Dynamic Pointer Array Resizing

Rather than relying on fixed abstractions, memory expansion is managed entirely through dynamic raw pointer array reconfiguration logic. When adding an entry (such as posting a listing or adding a favorite), the system follows a safe memory adjustment pattern:

1. Allocates a new tracking pointer array on the heap with size $N+1$.
2. Migrates the existing memory addresses safely from the original tracking array into the staging array.
3. Appends the new target object reference onto the terminal block ($N$).
4. Calls `delete[]` on the old array container to clear obsolete collection references.
5. Points the internal pointer reference safely to the newly allocated memory address.

---

## 8. System Functionalities

### 8.1 Listing Moderation Workflows

* **Polymorphic Insertion:** Supports safe submissions for Cars, Bikes, and Trucks.
* **Volume Control:** Restricts active accounts from exceeding posting thresholds.
* **Admin Verification:** Gives staff clear paths to approve items or issue removals.

### 8.2 Search, Filtering, and Localization

* Handles multi-tiered string evaluations to sort data arrays by manufacturer categories.
* Looks up criteria across structural sub-objects, ensuring the system safely checks specific derived attributes without data truncation errors.

### 8.3 Buyer, Seller, and Moderation Tools

* **Buyer Hub:** Simplifies bookmark interactions by allowing users to add or remove listings from their personal favorites array.
* **Seller Hub:** Automatically recalculates seller satisfaction scores whenever a client appends a new numeric review.
* **Admin Hub:** Features security controls to flag malicious users and issue global account bans.

---

## 9. Important Code Snippets and Reasoning

### 9.1 Polymorphic Method Overriding

```cpp
class Car : public Vehicle {
public:
    void displayDetails() const override {
        Vehicle::displayDetails(); // Reuses base logic cleanly
        cout << "Vehicle Type: Car" << endl;
        cout << "Doors: " << doors << endl;
    }
};

```

**Reason:** Allows the program to safely execute class-specific printing rules behind uniform interfaces, decoupling formatting layout code from general data searches.

### 9.2 Pure Virtual Interfaces (Abstract Verification)

```cpp
virtual string getAccountType() const = 0;

```

**Reason:** Prevents empty or incomplete parent class objects from polluting runtime memory arrays, ensuring every created user has a clearly defined platform role.

### 9.3 Stream Representation Utilities

```cpp
friend istream &operator>>(istream &input, Listing &l);

```

**Reason:** Grants stream operators direct visibility into hidden class properties, turning complex object data displays into clean, readable console outputs.

---

## 10. Conclusion

This architecture successfully delivers a scalable, highly secure vehicle marketplace. By transitioning into abstract hierarchies, the application safely manages data models, enforces cross-object communication rules, and provides a clear blueprint for real-world production projects.
