#pragma once

#ifndef CUSTOMER_LIST_ITERATORS_H
#define CUSTOMER_LIST_ITERATORS_H

#include <vector>
#include "CustomerList/CustomerList.h"
#include "Customers/Customer.h"

typedef std::vector<Customer>::iterator iterator;
typedef std::vector<Customer>::const_iterator const_iterator;


#endif // CUSTOMER_LIST_ITERATORS_H
