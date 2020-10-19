/** @file scope.h
 * Operations over scopes.
 *
 * @copyright (C) 2020 Henrique Silva
 *
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 *
 * @section LICENSE
 *
 * This file is subject to the terms and conditions defined in the file
 * 'LICENSE', which is part of this source code package.
 *
 * @section DESCRIPTION
 *
 * This module uses elements from all other sources in this subdirectory
 * to efectivelly  create a  static scope  abstraction using  stacks and
 * hash tables.  Therefore, this module  aims to hide away  any possible
 * implementation  details  so  utilization   inside  Bison  actions  is
 * smoother and cleaner.
 */

#ifndef _SCOPE_H_
#define _SCOPE_H_

#include "semantics/list.h"
#include "semantics/map.h"
#include "semantics/stack.h"
#include "semantics/values.h"

/**
 * The  scope variable  is global,  as  everything in  Bison is  global.
 * Basically, all code  here is going to interact with  this variable in
 * one way or another.
 */
extern cc_stack_t* scope;

/* --------------------------------------------------------------------------- */
/* Function prototypes: */

/**
 * Initializes the global scope variable.
 *
 * @returns a pointer to an initialized scope variable in heap memory.
 */
cc_stack_t* cc_init_global_scope(void);

/**
 * Adds all symbols in the given list to the current scope.
 *
 * @param stack the scope stack.
 * @param list the list of pairs between symbols and names to be added.
 *
 * @return a pointer to the scope stack.
 */
cc_stack_t* cc_add_list_scope(cc_stack_t* stack, cc_list_t* list);

#endif /* _SCOPE_H_ */
