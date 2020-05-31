/*----------------------------------------------------------------------
 * $Id: config.cpp,v 1.4 2012-02-12 01:31:30 salem Exp $
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

#include "config.hpp"

#include <fstream>
#include <stdexcept>

config::config(
    const char* filename )
    : filename( filename )
{
}

void config::read()
{
    std::ifstream in;
    in.open( filename );
    if ( !in ) {
        char buffer[1024];
        sprintf( buffer, "cound not load file: %s", filename );
        throw std::runtime_error( buffer );
    }
    char buffer[256];
    QRegExp cline = get_regex();
    std::string key;
    config_value cv;
    while ( in.getline( buffer, 255 ) ) {
        if ( parse( cline, buffer, key, cv ) ) {
            m_map.insert( map::value_type( key, cv ) );
        }
    }
}

config::const_iterator
config::begin() const
{
    return m_map.begin();
}

config::const_iterator
config::end() const
{
    return m_map.end();
}

void config::clear()
{
    m_map.erase( m_map.begin(), m_map.end() );
}

void config::add(
    const std::string& key,
    const config_value& cv )
{
    m_map[key] = cv;
}

const config_value*
config::find(
    const std::string& str ) const
{
    const_iterator i = m_map.find( str );
    if ( m_map.end() == i ) {
        return nullptr;
    } else {
        return &i->second;
    }
}

void config::analyze(
    const config& c1,
    const config& c2,
    std::set<std::string>& cunion,
    std::set<std::string>& diff,
    std::set<std::string>& in1,
    std::set<std::string>& in2 )
{
    cunion.clear();
    diff.clear();
    in1.clear();
    in2.clear();
    config::const_iterator i = c1.begin();
    while ( c1.end() != i ) {
        const config_value* cv = c2.find( i->first );
        if ( cv ) {
            if ( i->second == *cv ) {
                cunion.insert( i->first );
            } else {
                diff.insert( i->first );
            }
        } else {
            in1.insert( i->first );
        }
        ++i;
    }
    i = c2.begin();
    while ( c2.end() != i ) {
        if ( !c1.find( i->first ) ) {
            in2.insert( i->first );
        }
        ++i;
    }
}

QRegExp
config::get_regex() const
{
    return QRegExp( "(# )?CONFIG_([^= ]+)[ =]+([^\n]+)" );
}

bool config::parse(
    QRegExp& exp,
    const char* line,
    std::string& key,
    config_value& cv )
{
    if ( -1 != exp.indexIn( line ) ) {
        key = exp.cap( 2 ).toStdString();
        std::string value = exp.cap( 3 ).toStdString();
        if ( "# " == exp.cap( 1 ) ) {
            cv = config_value::No;
        } else {
            if ( "m" == value || "M" == value ) {
                cv = config_value::Module;
            } else if ( "y" == value || "Y" == value ) {
                cv = config_value::Yes;
            } else if ( "n" == value || "N" == value ) {
                cv = config_value::No;
            } else {
                cv = value;
            }
        }
        return true;
    }
    return false;
}

std::ostream&
operator<<(
    std::ostream& out,
    const config& c )
{
    config::const_iterator i = c.begin();
    while ( c.end() != i ) {
        out << i->first << "\t=>\t" << i->second << std::endl;
        ++i;
    }
    return out;
}
