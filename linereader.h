/**
 *  @file linereader.h
 *  @version 1.1.1-dev0
 *  @see https://github.com/crowja/linereader
 *  @date Sun Feb 16, 2020 04:44:08 PM CST
 *  @copyright 2019-2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#ifndef LINEREADER_H
#define LINEREADER_H

struct linereader;

/**
 *  @brief Create and return a new linereader object
 *  @details Creates a new linereader from the file named fname, stdin if NULL.
 *  If linereader was built with Zlib support, the input stream can be
 *  standard text or Libz compressed, e.g. gzipped. Otherwise, if linereader was
 *  built without Zlib support, specifying a compressed stream is an error.
 *  and linereader_new() will return NULL.
 *  @param[in] fname Filename to read from. If NULL use stdin.
 *  @returns Pointer to a struct linereader. On error NULL is returned.
 */
struct linereader *linereader_new(char *fname);

/**
 *  @brief Clean up and free a linereader structure
 *  @param[in,out] pp Reference to a linereader pointer created by
 *  linereader_new(). Set to NULL.
 */
void        linereader_free(struct linereader **pp);

/**
 *  @brief Return the version of this package
 */
const char *linereader_version(void);

/**
 *  @brief Return the next line of text pointed at by the linereader object.
 *  @param p Pointer to a linereader object created by linereader_new().
 *  @returns String, NULL on error or EOF.
 */
const char *linereader_next(struct linereader *p);

#endif
