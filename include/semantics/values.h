/** @file values.h
 * Semantic values of a language.
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
 * Definition of semantic values, i.e.  their meaning and content, to be
 * used in the hash map.
 */

#ifndef _VALUES_H_
#define _VALUES_H_

#include <stdbool.h>
#include <stdint.h>

#include "ast/ast.h"
#include "lexer/location.h"
#include "semantics/list.h"
#include "semantics/types.h"
#include "utils/memory.h"

/* --------------------------------------------------------------------------- */
/* Type definitions: */

typedef enum {
    cc_symb_var,
    cc_symb_func,
    cc_symb_array
} cc_symb_kind_t;

typedef union {
    uint16_t quantity;
    cc_list_t* parameters;
} cc_symb_opt;

typedef struct {
    cc_location_t location;
    cc_symb_kind_t kind;
    cc_type_t type;
    uint8_t size;
    bool initialized;
    cc_symb_opt optional_info;
} cc_symb_t;

typedef struct {
    cc_symb_t* symbol;
    char* name;
} cc_symb_pair_t;

/* --------------------------------------------------------------------------- */
/* Function prototypes: */

/**
 * Creates and initializes a new symbol in dynamic memory.
 *
 * @param location the location (line and column) of the symbol.
 * @param kind whether its a variable, an array or a function.
 *
 * @return a new symbol allocated in the heap.
 *
 * @see the header "lexer/location.h".
 */
cc_symb_t* cc_create_symbol(cc_location_t location, cc_symb_kind_t kind);

/**
 * Given a valid  lexic value of a identifier, create  a name and symbol
 * pair. After operation, the given `lexic_value` pointer is invalid, as
 * it is free'd in the process.
 *
 * @param lexic_value a lexic value given by the lexer.
 * @param kind whether its a variable, an array or a function.
 *
 * @return a `cc_symb_t` and `char*` pair.
 */
cc_symb_pair_t* cc_create_symbol_pair(cc_lexic_value_t* lexic_value, cc_symb_kind_t kind);

/**
 * Given an existing symbol, initialize its type parameter.
 *
 * @param symbol the symbol to add type info to.
 * @param type the type itself (int, char, bool, string, float).
 *
 * @return an indication of success.
 */
bool cc_init_type_symbol(cc_symb_t* symbol, cc_type_t type);

/**
 * Initializes a symbol of an array, given an already existing symbol.
 *
 * @param symbol the symbol to add info to.
 * @param lexic_value lexic value of the array size integer.
 */
void cc_init_array_symbol(cc_symb_t* symbol, cc_lexic_value_t* lexic_value);

/**
 * Initializes a symbol of a function, given an already existing symbol.
 *
 * @param symbol the symbol to add info to.
 * @param names the names of the parameters, to be used as keys.
 */
void cc_init_func_symbol(cc_symb_t* symbol, cc_list_t* parameters);

/**
 * Initializes a symbol of a string, given an already existing symbol.
 *
 * @param symbol the symbol to add info to.
 * @param lenght the lenght of the string value.
 */
void cc_init_string_symbol(cc_symb_t* symbol, uint32_t lenght);

#endif /* _VALUES_H_ */
