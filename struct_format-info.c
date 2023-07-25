#include <stdlib.h>
#include "main.h"

/**
 * init_format_info - initializing struct called format info
 * @spec: Format-info to be initialized
 */
void init_format_info(fmt_info_t *spec)
{
	if (spec)
	{
		spec->prec = 1;
		spec->width = 0;
		spec->spec = FALSE;
		spec->is_long_double = FALSE;
		spec->is_long_long = FALSE;
		spec->is_long = FALSE;
		spec->is_short = FALSE;
		spec->is_char = FALSE;
		spec->is_precision_set = FALSE;
		spec->is_width_set = FALSE;
		spec->alt = FALSE;
		spec->space = FALSE;
		spec->left = FALSE;
		spec->show_sign = FALSE;
		spec->group = FALSE;
		spec->pad = ' ';
	}
}

/**
 * new_format_info - Creating new format-info structure
 *
 * Return: Null or
 * Pointer to newly created format-info structure
 */
fmt_info_t *new_format_info()
{
	fmt_info_t *spec;

	spec = malloc(sizeof(fmt_info_t));
	if (spec)
		init_format_info(spec);
	return (spec);
}

/**
 * new_float_info - Initializes new float_info struct
 * @exponent_size: Exponent's number of bits
 * @mantissa_size: Total bits in the mantissa
 *
 * Return: Null or
 * A pointer to newly created struct
 */
float_info_t *new_float_info(ushort_t exponent_size, ushort_t mantissa_size)
{
	float_info_t *float_info;

	float_info = malloc(sizeof(float_info_t));
	if (float_info != NULL)
	{
		float_info->exponent = malloc(sizeof(char) * (exponent_size + 1));
		if (float_info->exponent == NULL)
			free(float_info);
		float_info->mantissa = malloc(sizeof(char) * (mantissa_size + 1));
		if (float_info->mantissa == NULL)
		{
			free(float_info->exponent);
			free(float_info);
		}
	}
	return (float_info);
}

/**
 * free_float_info - Frees the allocated memory
 * of a given pointer
 *
 * @flt_info: Given pointer
 */
void free_float_info(float_info_t *flt_info)
{
	if (flt_info != NULL)
	{
		if (flt_info->exponent != NULL)
			free(flt_info->exponent);
		if (flt_info->mantissa != NULL)
			free(flt_info->mantissa);
		free(flt_info);
	}
}
