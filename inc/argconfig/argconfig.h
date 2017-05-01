////////////////////////////////////////////////////////////////////////
//
// Copyright 2014 PMC-Sierra, Inc.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//
//   Author: Logan Gunthorpe <logang@deltatee.com>
//           Logan Gunthorpe
//
//   Date:   Oct 23 2014
//
//   Description:
//     Header file for argconfig.c
//
////////////////////////////////////////////////////////////////////////

#ifndef argconfig_H
#define argconfig_H

#include <string.h>
#include <getopt.h>
#include <stdarg.h>

#ifndef COMPLETE_ENV
#define COMPLETE_ENV "ARGCONFIG_COMPLETE"
#endif

enum {
	optional_positional = 20,
	required_positional = 21,
};

enum argconfig_types {
	CFG_NONE,
	CFG_STRING,
	CFG_INT,
	CFG_SIZE,
	CFG_LONG,
	CFG_LONG_SUFFIX,
	CFG_DOUBLE,
	CFG_BOOL,
	CFG_BYTE,
	CFG_SHORT,
	CFG_POSITIVE,
	CFG_INCREMENT,
	CFG_FILE_A,
	CFG_FILE_W,
	CFG_FILE_R,
	CFG_FILE_AP,
	CFG_FILE_WP,
	CFG_FILE_RP,
	CFG_FD_RD,
	CFG_FD_WR,
	CFG_CHOICES,
	CFG_MULT_CHOICES,
	CFG_MASK,
	CFG_MASK_8,
	CFG_MASK_16,
	CFG_MASK_32,
	CFG_MASK_64,
	CFG_CUSTOM,
	_CFG_MAX_TYPES,
};

struct argconfig_choice {
	const char *name;
	int value;
	const char *help;
};

struct argconfig_options {
	const char *option;
	const char short_option;
	const char *meta;
	enum argconfig_types cfg_type;
	void *value_addr;
	int argument_type;
	const char *help;
	int (*custom_handler)(const char *optarg, void *value_addr,
			      const struct argconfig_options *opt);
	const char *force_default;
	const char *complete;
	struct argconfig_choice *choices;
	int require_in_usage;
	const char *env;
};

#define MAX_HELP_FUNC 20


#ifdef __cplusplus
extern "C" {
#endif

typedef void argconfig_help_func();
void argconfig_append_usage(const char *str);
int argconfig_parse(int argc, char *argv[], const char *program_desc,
		    const struct argconfig_options *options,
		    void *config_out, size_t config_size);

void argconfig_print_usage(const struct argconfig_options *options);
void argconfig_print_help(const char *program_desc,
			  const struct argconfig_options *options);
void argconfig_register_help_func(argconfig_help_func * f);

void print_word_wrapped(const char *s, int indent, int start);

int argconfig_parse_comma_range(const char *str, int *res, int max_nums);

#ifdef __cplusplus
}
#endif
#endif
