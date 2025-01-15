#include "LockManager.h"
#include <algorithm>

namespace db {

    bool LockManager::areCompatible(LockMode mode, const std::vector<Lock>& existingLocks) {
        for (const auto& lock : existingLocks) {
            if (mode == EXCLUSIVE || lock.mode == EXCLUSIVE) {
                return false;
            }
        }
        return true;
    }

    bool LockManager::acquireLock(int recordID, int transactionID, LockMode mode) {
        std::vector<Lock>& recordLocks = locks[recordID];
        if (areCompatible(mode, recordLocks)) {
            recordLocks.push_back({transactionID, mode});
            return true;
        }
        return false;
    }

    void LockManager::releaseLock(int recordID, int transactionID) {
        auto& recordLocks = locks[recordID];
        recordLocks.erase(std::remove_if(recordLocks.begin(), recordLocks.end(),
                                         [transactionID](const Lock& lock) { return lock.transactionID == transactionID; }),
                          recordLocks.end());
    }

    void LockManager::releaseAllLocks(int transactionID) {
        for (auto& pair : locks) {
            auto& recordLocks = pair.second;
            recordLocks.erase(std::remove_if(recordLocks.begin(), recordLocks.end(),
                                             [transactionID](const Lock& lock) { return lock.transactionID == transactionID; }),
                              recordLocks.end());
        }
    }

}