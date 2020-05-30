/*----------------------------------------------------------------------
 * $Id: test.cpp,v 1.2 2005-09-24 19:36:58 ganzhorn Exp $             
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

#include <sstream>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "../config_value.hpp"
using boost::unit_test_framework::test_suite;

using namespace std;

#define CV_CHECK(x,y) \
do { cout << x << " =? " << y << endl;BOOST_TEST(x==y); } while(0)

void test_value( const config_value &cv, string value )
{
    stringstream ss;
    ss << cv;
    CV_CHECK(ss.str(),value);
}

void test_config_value()
{
    config_value empty;
    config_value integer(5);
    config_value real(3.14);
    config_value str("Foo");
    config_value yes(config_value::Yes);
    config_value no(config_value::No);
    config_value module(config_value::Module);
    cout << "Testing constructor && operator <<" << endl;
    test_value( empty,"0" );
    test_value( integer,"5" );
    test_value( real,"3.14" );
    test_value( str,"Foo" );
    test_value( yes,"Yes" );
    test_value( no,"No" );
    test_value( module,"Module" );
    // test copies
    cout << "Testing copy constructor" << endl;
    test_value( config_value(empty),"0" );
    test_value( config_value(integer),"5" );
    test_value( config_value(real),"3.14" );
    test_value( config_value(str),"Foo" );
    test_value( config_value(yes),"Yes" );
    test_value( config_value(no),"No" );
    test_value( config_value(module),"Module" );
}

test_suite*
init_unit_test_suite(
    int argc,
    char **argv
    )
{
    (void)argc;
    (void)argv;
    test_suite* test = BOOST_TEST_SUITE("config_value suite");
    test->add( BOOST_TEST_CASE( &test_config_value ) );
    return test;
}
