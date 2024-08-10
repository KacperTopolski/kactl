/**
 * Author: UJ Lib
 * Description: Gray code: $\text{gray}(0),\dots, \text{gray}(2^n-1)$ - permutation
 * in which each two consecutive (cyclically) numbers
 * differ in exactly one bit.
 */
#pragma once

unsigned gray(unsigned n) { return n^n>>1; }
unsigned igray(unsigned n) {
	n^=n>>1; n^=n>>2; n^=n>>4; n^=n>>8; n^=n>>16; return n;
}
