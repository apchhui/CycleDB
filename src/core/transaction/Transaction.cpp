#include "Transaction.h"
#include "src/core/storage/Record.h"

namespace db {

    int Transaction::nextTransactionID = 0;

    Transaction::Transaction(LockManager& lockManager)
        : lockManager(lockManager), transactionID(nextTransactionID++), isActive(false) {}

    Transaction::~Transaction() {
        if (isActive) {
            rollback();
        }
    }

    void Transaction::begin() {
        isActive = true;
        // Initialize transaction state
    }

    void Transaction::commit() {
        if (!isActive) {
            return;
        }
        // Apply changes permanently
        rollbackJournal.clear();
        lockManager.releaseAllLocks(transactionID);
        isActive = false;
    }

    void Transaction::rollback() {
        if (!isActive) {
            return;
        }
        // Revert changes using rollback journal
        for (auto it = rollbackJournal.rbegin(); it != rollbackJournal.rend(); ++it) {
            switch (it->type) {
                case INSERT:
                    // Delete the inserted record
                    break;
                case UPDATE:
                    // Restore the original record
                    break;
                case DELETE:
                    // Reinsert the deleted record
                    break;
            }
        }
        rollbackJournal.clear();
        lockManager.releaseAllLocks(transactionID);
        isActive = false;
    }

    bool Transaction::insertRecord(Table& table, const Record& record) {
        if (!isActive) {
            return false;
        }
        int recordID = table.getNextRecordID();
        if (!lockManager.acquireLock(recordID, transactionID, LockManager::EXCLUSIVE)) {
            return false;
        }
        table.insertRecord(record);
        rollbackJournal.push_back({INSERT, recordID, Record()});
        return true;
    }

    bool Transaction::updateRecord(Table& table, int recordID, const Record& record) {
        if (!isActive) {
            return false;
        }
        if (!lockManager.acquireLock(recordID, transactionID, LockManager::EXCLUSIVE)) {
            return false;
        }
        table.updateRecord(recordID, record);
        // Record original record for rollback
        rollbackJournal.push_back({UPDATE, recordID, Record()});
        return true;
    }

    bool Transaction::deleteRecord(Table& table, int recordID) {
        if (!isActive) {
            return false;
        }
        if (!lockManager.acquireLock(recordID, transactionID, LockManager::EXCLUSIVE)) {
            return false;
        }
        table.deleteRecord(recordID);
        // Record deleted record for rollback
        rollbackJournal.push_back({DELETE, recordID, Record()});
        return true;
    }

}