#ifndef LOCK_MANAGER_H
#define LOCK_MANAGER_H

#include <map>
#include <vector>
#include <string>

namespace db {
    class Transaction;

    class LockManager {
    public:
        enum LockMode { SHARED, EXCLUSIVE };

        struct Lock {
            int transactionID;
            LockMode mode;
        };

        bool acquireLock(int recordID, int transactionID, LockMode mode);
        void releaseLock(int recordID, int transactionID);
        void releaseAllLocks(int transactionID);

    private:
        std::map<int, std::vector<Lock>> locks; // recordID to list of locks

        bool areCompatible(LockMode mode, const std::vector<Lock>& existingLocks);
    };
}

#endif // LOCK_MANAGER_H