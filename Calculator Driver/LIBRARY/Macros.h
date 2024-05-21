/*
 * Macros.h
 *
 *  Created on: Feb 1, 2024
 *      Author: abo32
 */

#ifndef LIBRARY_MACROS_H_
#define LIBRARY_MACROS_H_

#define SET_BIT( REG , PIN )	( REG |= (1<<PIN) )
#define CLR_BIT( REG , PIN )	( REG &= ~(1<<PIN) )
#define TOG_BIT( REG , PIN )	( REG ^= (1<<PIN) )
#define RED_BIT( REG , PIN )	( (REG & (1<<PIN)) >> PIN )

#endif /* LIBRARY_MACROS_H_ */
