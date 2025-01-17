/**
 * @file
 * @author Matt "MateoConLechuga" Waltz
 * @brief Optimized (de)compression routines
 */

#ifndef COMPRESSION_H
#define COMPRESSION_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Decompress a block of zx7 encoded data
 *
 * @param[in] dst Pointer to destination for uncompressed data
 * @param[in] src Pointer to compressed data
*/
void zx7_Decompress(void *dst, const void *src);

#ifdef __cplusplus
}
#endif

#endif

