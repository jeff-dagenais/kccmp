#ifndef KCCMP_CONFIG_VALUE
#define KCCMP_CONFIG_VALUE
/*----------------------------------------------------------------------
 * $Id: config_value.hpp,v 1.2 2005-09-24 19:36:58 ganzhorn Exp $             
 *
 *
 * Copyright (C)   2005            Salem Ganzhorn <eyekode@yahoo.com>
 *
 * This file is part of kccmp - Kernel Config CoMPare
 *                                                                      
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *----------------------------------------------------------------------*/

#include <string>
#include <iostream>

class config_value {
public:
    typedef enum {
	No,
	Yes,
	Module
    } value_constant;
    
public:
    config_value();
    config_value( const config_value &cv );
    config_value( value_constant vs );
    config_value( int i );
    config_value( const std::string &str );
    config_value( double d );
    ~config_value();

    const config_value& operator= ( const config_value &cv );
    const config_value& operator= ( int i );
    const config_value& operator= ( double d );
    const config_value& operator= ( const std::string & str );
    const config_value& operator= ( value_constant vc );
    
    bool operator== (const config_value &cv ) const;
    friend std::ostream& operator<< (std::ostream&,const config_value&);
    
protected:
    ///\brief free resources
    void free();
    
protected:
    typedef enum {
	Real,
	Integer,
	ValueConstant,
	String
    } type;
    type m_type;
    union {
	double         real;
	int            integer;
	value_constant vc;
	std::string   *str;
    } m_data;
};

std::ostream& operator<< (std::ostream& out, const config_value&);

#endif

