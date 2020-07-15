#pragma once

#ifndef CUSTOMER_LIST_ITERATORS_H
#define CUSTOMER_LIST_ITERATORS_H

#include <vector>
#include "CustomerList/CustomerList.h"
#include "Customer/Customer.h"

typedef std::vector<Customer>::iterator customer_iterator;
typedef std::vector<Customer>::const_iterator customer_const_iterator;


#endif // CUSTOMER_LIST_ITERATORS_H
