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

#include <stdbool.h>

#include "semantics/list.h"
#include "semantics/map.h"
#include "semantics/stack.h"
#include "semantics/values.h"

typedef enum {
    cc_declared_current,
    cc_declared_previous,
    cc_undeclared
} cc_declaration_t;

typedef struct {
    cc_declaration_t where;
    cc_symb_t* symbol;
} cc_query_answer_t;

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
 * Pushes a new empty  scope to the stack. In other  words, create a new
 * hash map and push it to the scope stack.
 */
void cc_push_new_scope(void);

/**
 * Pops the current scope into oblivion.
 */
void cc_pop_top_scope(void);

/**
 * Adds all symbols in the given list to the current global scope.
 *
 * @param list the list of pairs between symbols and names to be added.
 *
 * @see the global variable `scope`.
 */
void cc_add_list_scope(cc_list_t* list);

/**
 * Adds the pair name and symbol to the current scope.
 *
 * @param pair the pair of types `char*` and `cc_symb_t*`
 */
void cc_add_pair_scope(cc_symb_pair_t* pair);

/**
 * Unwinds  the scope  stack  searching  for the  existance  of a  given
 * identifier  node. In  other words,  we check  to see  if it  has been
 * declared at any point.
 *
 * @param name the name of the identifier.
 *
 * @return the  query answer, containing  where it was declared  and the
 *         symbol itself.
 */
cc_query_answer_t cc_check_id_existence_scope(char const* name);

/**
 * Checks the  usage of the  given name in  the current scope  stack and
 * compares it to the expected kind  of declaration that the name should
 * be bound to.
 *
 * @param name the name of the identifier.
 * @param kind the type of declaration (variable, array or function).
 */
void cc_check_name_usage_scope(
    char const*    name,
    cc_symb_kind_t kind);

#endif /* _SCOPE_H_ */
