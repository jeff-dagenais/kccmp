/*----------------------------------------------------------------------
 * $Id: config_value.cpp,v 1.2 2005-09-24 19:36:58 ganzhorn Exp $             
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

#include "config_value.hpp"

#include <assert.h>

config_value::config_value()
    : m_type( Integer )
{
    m_data.integer = 0;
}

config_value::config_value(
    const config_value& cv )
    : m_type( Integer )
{
    m_data.str = NULL;
    *this = cv;
}

config_value::config_value(
    value_constant vc )
    : m_type( ValueConstant )
{
    m_data.vc = vc;
}

config_value::config_value(
    int i )
    : m_type( Integer )
{
    m_data.integer = i;
}

config_value::config_value(
    double d )
    : m_type( Real )
{
    m_data.real = d;
}

config_value::config_value(
    const std::string& str )
    : m_type( String )
{
    m_data.str = new std::string( str );
}

config_value::~config_value()
{
    free();
}

void config_value::free()
{
    if ( String == m_type ) {
        delete m_data.str;
    }
}

const config_value&
config_value::operator=( const config_value& cv )
{
    free();
    m_type = cv.m_type;
    switch ( cv.m_type ) {
    case Real:
        m_data.real = cv.m_data.real;
        break;
    case Integer:
        m_data.integer = cv.m_data.integer;
        break;
    case ValueConstant:
        m_data.vc = cv.m_data.vc;
        break;
    case String:
        m_data.str = new std::string( *cv.m_data.str );
        break;
    default:
        assert( 0 );
    }
    return *this;
}

const config_value&
config_value::operator=( int i )
{
    free();
    m_type = Integer;
    m_data.integer = i;
    return *this;
}

const config_value&
config_value::operator=( double d )
{
    free();
    m_type = Real;
    m_data.real = d;
    return *this;
}

const config_value&
config_value::operator=( const std::string& str )
{
    if ( String == m_type ) {
        *m_data.str = str;
    } else {
        m_type = String;
        m_data.str = new std::string( str );
    }
    return *this;
}

const config_value&
config_value::operator=( value_constant vc )
{
    free();
    m_type = ValueConstant;
    m_data.vc = vc;
    return *this;
}

bool config_value::operator==(
    const config_value& cv ) const
{
    if ( m_type == cv.m_type ) {
        switch ( m_type ) {
        case Real:
            return ( m_data.real == cv.m_data.real );
            break;
        case Integer:
            return ( m_data.integer == cv.m_data.integer );
            break;
        case ValueConstant:
            return ( m_data.vc == cv.m_data.vc );
            break;
        case String:
            return ( *m_data.str == *cv.m_data.str );
            break;
        default:
            assert( 0 );
            return false;
        }
    } else {
        return false;
    }
}

std::ostream&
operator<<(
    std::ostream& out,
    const config_value& cv )
{
    switch ( cv.m_type ) {
    case config_value::Real:
        out << cv.m_data.real;
        break;
    case config_value::Integer:
        out << cv.m_data.integer;
        break;
    case config_value::ValueConstant:
        switch ( cv.m_data.vc ) {
        case config_value::Yes:
            out << "Yes";
            break;
        case config_value::No:
            out << "No";
            break;
        case config_value::Module:
            out << "Module";
            break;
        }
        break;
    case config_value::String:
        out << *cv.m_data.str;
        break;
    }
    return out;
}
