#pragma once

#ifndef ACCOUNT_LIST_ITERATORS_H
#define CUSTOMER_LIST_ITERATORS_H

#include <vector>
#include "Account/Account.h"
#include "AccountList/AccountList.h"

typedef std::vector<Account*>::iterator account_iterator;
typedef std::vector<Account*>::const_iterator account_const_iterator;


#endif // ACCOUNT_LIST_ITERATORS_H
