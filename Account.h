#ifndef ACCOUNT
#define ACCOUNT

#include <iostream>
using namespace std;

class Message;

class Account
{
protected:
    string email;
    string encryptedpassword;
    string phone;
    string firstName;
    string lastName;
    char gender;
    string dob;
    int accountId;
    bool isBanned;
    Message **inbox;
    int messageCount;
    string memberSince;
    bool emailVerified;

public:
    static int totalAccountsCreated;

    Account() : email(""), encryptedpassword(""), phone(""), firstName(""),
                lastName(""), gender('U'), dob(""), accountId(0), isBanned(false),
                inbox(nullptr), messageCount(0), memberSince("1/1/1970"), emailVerified(false) {}

    Account(string email, string firstName, string lastName, string phone, char gender, string dob)
    {
        this->email = email;
        this->firstName = firstName;
        this->lastName = lastName;
        this->phone = phone;
        this->gender = gender;
        this->dob = dob;
        this->isBanned = false;
        this->accountId = totalAccountsCreated++;
        this->inbox = nullptr;
        this->messageCount = 0;
        this->memberSince = "1/1/1970"; // Default date, can be updated later
        this->emailVerified = false;
    }

    Account(const Account &other)
    {
        email = other.email;
        encryptedpassword = other.encryptedpassword;
        phone = other.phone;
        firstName = other.firstName;
        lastName = other.lastName;
        gender = other.gender;
        dob = other.dob;
        accountId = totalAccountsCreated++;
        isBanned = other.isBanned;
        messageCount = other.messageCount;
        emailVerified = other.emailVerified;

        if (other.messageCount > 0)
        {
            inbox = new Message *[other.messageCount];
            for (int i = 0; i < other.messageCount; i++)
            {
                inbox[i] = other.inbox[i];
            }
        }
        else
        {
            inbox = nullptr;
        }
    }

    Account &operator=(const Account &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] inbox;

        email = other.email;
        encryptedpassword = other.encryptedpassword;
        phone = other.phone;
        firstName = other.firstName;
        lastName = other.lastName;
        gender = other.gender;
        dob = other.dob;
        isBanned = other.isBanned;
        messageCount = other.messageCount;

        if (other.messageCount > 0)
        {
            inbox = new Message *[other.messageCount];
            for (int i = 0; i < other.messageCount; i++)
            {
                inbox[i] = other.inbox[i];
            }
        }
        else
        {
            inbox = nullptr;
        }

        return *this;
    }

    string encryptPassword(string rawpassword)
    {
        string encrypted = "";
        for (char c : rawpassword)
        {
            encrypted += char(c + 3);
        }
        return encrypted;
    }

    bool authenticate(string inputEmail, string inputPassword)
    {
        if (inputEmail == email && encryptPassword(inputPassword) == encryptedpassword)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void updateContact(string newPhone)
    {
        phone = newPhone;
    }

    void verifyEmail()
    {
        cout << "Are you Human? (Y/N): ";
        char response;
        cin >> response;
        if (response == 'Y' || response == 'y')
        {
            cout << "Email verified successfully!" << endl;
            emailVerified = true;
        }
        else
        {
            cout << "Email verification failed. Please try again." << endl;
        }
    }

    void resetPassword(string oldPassword, string newPassword)
    {
        if (authenticate(email, oldPassword))
        {
            setPassword(newPassword);
            cout << "Password reset successful!" << endl;
        }
        else
        {
            cout << "Incorrect current password. Password reset failed." << endl;
        }
    }
    virtual void displayDetails() const
    {
        cout << "Logged in as: " << endl;
        cout << firstName << " " << lastName << endl;
        cout << accountId << endl;
        cout << email << endl;
        cout << phone << endl;
    }

    void setPassword(string password)
    {
        encryptedpassword = encryptPassword(password);
    }

    void setBannedStatus(bool status)
    {
        this->isBanned = status;
    }

    bool getIsBanned() const
    {
        return isBanned;
    }

    int getAccountId() const
    {
        return accountId;
    }

    void receiveMessage(Message *incomingMsg)
    {
        Message **temp = new Message *[messageCount + 1];

        for (int i = 0; i < messageCount; i++)
        {
            temp[i] = inbox[i];
        }

        temp[messageCount] = incomingMsg;
        delete[] inbox;
        inbox = temp;
        messageCount++;

        cout << "Notification for " << firstName << ": You have a new message! (Total: " << messageCount << ")" << endl;
    }

    virtual string getAccountType() const = 0;

    virtual ~Account()
    {
        delete[] inbox;
    }
};

#endif
