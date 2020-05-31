#ifndef KCCMP_CONFIG_HPP
#define KCCMP_CONFIG_HPP
/*----------------------------------------------------------------------
 * $Id: config.hpp,v 1.4 2012-02-12 01:31:30 salem Exp $             
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

#include <QRegExp>
#include <map>
#include <set>
#include <string>

#include "config_value.hpp"

///@brief configuration data
class config {
public:
    config();
    config( const char* filename );
    ~config();

public:
    typedef std::map<std::string, config_value> map;
    typedef map::const_iterator const_iterator;

public:
    void read( const char* filename );
    ///\brief delete all entries
    void clear();
    void add( const std::string& key, const config_value& cv );
    const config_value* find( const std::string& key ) const;
    const_iterator begin() const;
    const_iterator end() const;

public:
    static void analyze( const config& c1, const config& c2,
        std::set<std::string>& cunion,
        std::set<std::string>& diff,
        std::set<std::string>& in1,
        std::set<std::string>& in2 );
    friend class config_test;

protected:
    QRegExp get_regex() const;
    bool parse( QRegExp& exp,
        const char* line,
        std::string& key,
        config_value& cv );

protected:
    map m_map;
};

std::ostream& operator<<( std::ostream&, const config& );

#endif
