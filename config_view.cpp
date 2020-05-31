/*----------------------------------------------------------------------
 * $Id: config_view.cpp,v 1.6 2012-02-12 01:31:30 salem Exp $             
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
#include "config_view.hpp"

#include <QDir>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QListWidget>
#include <QTabWidget>
#include <QTableWidget>

#include <sstream>

using namespace std;

config_view::~config_view() { }

config_view::config_view(
    QWidget* parent )
    : QFrame( parent )
{
}

void config_view::compare(
    const string& filename1,
    const string& filename2 )
{
    {
        const QObjectList& trash = children();
        QObjectList::const_iterator i = trash.begin();
        while ( trash.end() != i ) {
            QObjectList::const_iterator j = i;
            ++i;
            delete *j;
        }
    }

    config c1;
    config c2;
    c1.read( filename1.c_str() );
    c2.read( filename2.c_str() );
    set<string> cunion, diff, in1, in2;
    config::analyze( c1, c2, cunion, diff, in1, in2 );

    QTabWidget* tab = new QTabWidget( this );
    QLayout* l = new QHBoxLayout( this );
    l->addWidget( tab );

    QFileInfo fi1( filename1.c_str() );
    QFileInfo fi2( filename2.c_str() );
    QDir d1 = fi1.absoluteDir();
    QDir d2 = fi2.absoluteDir();
    QString id1 = d1.dirName();
    QString id2 = d2.dirName();
    if ( id1 == id2 ) {
        id1 = fi1.fileName();
        id2 = fi2.fileName();
        if ( id1 == id2 ) {
            id1 = "first file";
            id2 = "second file";
        }
    }
    add_diff_tab( tab, diff, c1, c2, id1, id2 );
    add_set_tab( tab, in1, c1, id1 );
    add_set_tab( tab, in2, c2, id2 );
}

namespace {
QTableWidget* new_table_widget( QWidget* parent )
{
    QTableWidget* view = new QTableWidget( parent );
    view->setAlternatingRowColors( true );
    view->setSelectionMode( QAbstractItemView::MultiSelection );
    view->setSelectionBehavior( QAbstractItemView::SelectItems );
    view->verticalHeader()->hide();
    return view;
}
}

void config_view::add_diff_tab(
    QTabWidget* tab,
    const set<string>& diff,
    const config& c1,
    const config& c2,
    const QString& dir1,
    const QString& dir2 )
{
    QWidget* add_to_tab = NULL;
    if ( diff.size() ) {
        QTableWidget* view = new_table_widget( tab );
        view->setColumnCount( 3 );
        view->setRowCount( diff.size() );
        QStringList labels;
        labels << "Config Var" << dir1 << dir2;
        view->setHorizontalHeaderLabels( labels );
        stringstream ss;
        view->setAlternatingRowColors( true );
        set<string>::const_iterator i = diff.begin();
        int row = 0;
        while ( diff.end() != i ) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText( i->c_str() );
            view->setItem( row, 0, item );
            ss << *c1.find( *i );
            item = new QTableWidgetItem();
            item->setText( ss.str().c_str() );
            view->setItem( row, 1, item );
            ss.str( "" );
            ss << *c2.find( *i );
            item = new QTableWidgetItem();
            item->setText( ss.str().c_str() );
            view->setItem( row, 2, item );
            ss.str( "" );
            ++row;
            ++i;
        }
        view->resizeColumnToContents( 0 );
        view->resizeColumnToContents( 1 );
        view->resizeColumnToContents( 2 );
        add_to_tab = view;
    } else {
        QLabel* l = new QLabel( "N/A", tab );
        add_to_tab = l;
    }
    tab->addTab( add_to_tab, "Different Values" );
}

void config_view::add_set_tab(
    QTabWidget* tab,
    const set<string>& info,
    const config& c,
    const QString& id )
{
    QWidget* add_to_tab = 0;

    if ( info.size() ) {
        QTableWidget* view = new_table_widget( tab );
        view->setColumnCount( 2 );
        view->setRowCount( info.size() );
        QStringList labels;
        labels << "Config Var"
               << "Value";
        view->setHorizontalHeaderLabels( labels );
        stringstream ss;
        set<string>::const_iterator i = info.begin();
        int row = 0;
        while ( info.end() != i ) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText( i->c_str() );
            view->setItem( row, 0, item );
            ss << *c.find( *i );
            item = new QTableWidgetItem();
            item->setText( ss.str().c_str() );
            view->setItem( row, 1, item );
            ss.str( "" );
            ++row;
            ++i;
        }
        view->resizeColumnToContents( 0 );
        view->resizeColumnToContents( 1 );
        add_to_tab = view;
    } else {
        QLabel* l = new QLabel( "N/A", tab );
        add_to_tab = l;
    }
    tab->addTab( add_to_tab, "Only in " + id );
}
